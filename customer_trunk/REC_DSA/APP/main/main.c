/*--------------------------------------------------------------------------*/
/**@file   main.c
   @brief  系统主函数
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#include "main.h"
#include "disp.h"
#include "fm_rev.h"
#include "led.h"
#include "music.h"
#include "device.h"
#include "dac.h"
#include "msgfor_usb.h"
#include "clock.h"
#include "disp.h"
#include "rtc_mode.h"
#include "echo.h"
extern u8 _idata clock_in;
extern u8 given_device;
extern u16 given_file_number;
extern xd_u8 DSA_SEL_DEV;
extern u8 eq_mode;
extern u8 play_mode;

extern bool pc_connect, udisk_connect, sdmmc_connect;
extern u8 _xdata win_buffer[];
extern u8 _xdata alm_cnt;
extern u8 _bdata device_online;
u8 _code one_table[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};

bool input_number_en;				///<是否允许数字键输入功能
bool change_eq_en;					///<是否允许改变EQ的设置
u8 work_mode;						///<工作模式变量
u8 _idata last_work_mode;			///<RTC 闹钟前的工作模式
bool aux_online;					///<AUX在线状态
bool kv_flag;						///<按键音的发送标记

u8  main_menu;						///<记录各种不同模式下的主界面
u8  cur_menu;        				///<当前界面
u8  main_menu_conter;				///<离开主界面的时间
bool flash_en;						///<显示闪动允许
u8 bright_counter;

#ifdef AC_SLAVE_ENABLE
extern void DSA_init(void);
extern bool DSA_GETHERING_DATA_ENABLE_BIT;
#endif

/*----------------------------------------------------------------------------*/
/**@brief  Line In检测函数
   @param  无
   @return 无
   @note   void aux_check(void)
*/
/*----------------------------------------------------------------------------*/
static void aux_check(void)
{
    static u8 aux_cnt_online;


    P0DIR |= BIT(7); //linein check port
    P0PU |= BIT(7);
    //_nop_();
    //_nop_();
    //_nop_();
    if (P07)
    {
        aux_cnt_online = 0;

        if (aux_online)
        {
            put_msg_lifo(MSG_AUX_OUT);
            aux_online = 0;
        }
    }
    else
    {
        aux_cnt_online++;
        if (aux_cnt_online > 50)
        {
            if (!aux_online)
            {
                put_msg_lifo(MSG_AUX_IN);
                aux_online = 1;
            }
        }
    }
    //P0DIR &= ~BIT(7); //linein check port

}
/*----------------------------------------------------------------------------*/
/**@brief   使用独立的GPIO检测SD card在线
   @param   void
   @return  void
   @note    void sdmmc_detect(void)
*/
/*----------------------------------------------------------------------------*/
void sdmmc_detect(void)
{
    static u8 sdmmc_cnt_online;
    P3DIR |= BIT(3); //linein check port
    P3PU |= BIT(3);
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    if (P33)
    {
        sdmmc_cnt_online = 0;
        sdmmc_chk_io(0);
    }
    else
    {
        if (sdmmc_cnt_online<51)
        {
            sdmmc_cnt_online++;
        }
        if (sdmmc_cnt_online > 50)
        {
            sdmmc_chk_io(1);
        }
        else
        {
            sdmmc_chk_io(0xff);
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  RTC中断服务程序
   @param  无
   @return 无
   @note   void rtcisr(void)
*/
/*----------------------------------------------------------------------------*/
void rtcisr(void)
{
    PSW = 0x08;
    DPCON = 0x0;
#if BURST_OUT_POINT_SAVE_ENABLE
    burst_out_break_point_save();
#endif

}






/*----------------------------------------------------------------------------*/
/**@brief  RTC中断服务程序
   @param  无
   @return 无
   @note   void rtcisr(void)
*/
/*----------------------------------------------------------------------------*/
void timer0isr(void)
{
    static u8 counter0, counter1;

    PSW = 0x08;
    DPCON = 0x0;
    T0CON &= ~BIT(7);			//clear pending

    disp_scan();
    adc_scan();
    counter0++;
    usb_polling();

    if ((counter0 % 2) == 0){			//10ms
	DSA_GETHERING_DATA_ENABLE_BIT=1;
    }
	
    if ((counter0 % 5) == 0)			//10ms
    {
        dec_delay_counter();
//#if SDMMC_CMD_MODE
//        sd_online_check();
#if SDMMC_CLK_MODE
        sdmmc_online_chk(1);
#elif SDMMC_GPIO_MODE
        sdmmc_detect();
#endif
        keyScan();
		disp_dled();
    }

//    if ((counter0 % 50) == 0)
//    {
//        put_msg_fifo(MSG_100MS);
//    }
    if ((counter0 % 100) == 0)
    {
        put_msg_fifo(MSG_200MS);
        counter0 = 0;
    }
    counter1++;
    if ((counter1 % 250) == 0)
    {
        put_msg_fifo(MSG_HALF_SECOND);
        counter1 = 0;
    }
#if RTC_ENABLE
    if (IRTCON & BIT(7))
    {
        alm_cnt = 1;
        last_work_mode = work_mode;
        put_msg_lifo(MSG_ALM_ON);
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  系统共用信息的初始化
   @param  无
   @return 无
   @note   void sys_info_init(void)
*/
/*----------------------------------------------------------------------------*/
static void sys_info_init(void)
{
#if 0
    u8 tmp;

    tmp = read_info(MEM_VOL);

    if ((tmp > MAX_MAIN_VOL) || (tmp == 0))              //每次开机时，不要超过最大音量的一半，以免开机音量过大
    {
        tmp = MAX_MAIN_VOL / 2;

    }
#endif	
    dac_init(MAX_MAIN_VOL);
    dsp_set_adc_con((0x0070));
    delay_10ms(50);										//等待,检测USB,SD在线状态
    init_rec_name();
    restore_music_point();
#if RTC_ENABLE
    if (work_mode != RTC_MODE)
#endif
    {
    	device_check();
#if USB_DEVICE_ENABLE
        if (pc_connect)
            work_mode = USB_DEVICE_MODE;
        else if (udisk_connect || sdmmc_connect)
            work_mode = MUSIC_MODE;
#else
        if (udisk_connect || sdmmc_connect)
            work_mode = MUSIC_MODE;
#endif
        else
        {
            work_mode = read_info(MEM_SYSMODE);
            if (work_mode > MAX_WORK_MODE)
            {
                work_mode = MUSIC_MODE;
            }
        }
    }
}



/*----------------------------------------------------------------------------*/
/**@brief  系统初始化
   @param  无
   @return 无
   @note   void sys_clk_div(u8 arg)
*/
/*----------------------------------------------------------------------------*/
void sys_clk_div(u8 arg)
{
#if ECHO_ENABLE
	static u8 _idata cur_div;
	/*混响功能使能后，系统时钟必须运行在48M*/
	if (cur_div == arg) 
	{
		return;
	}
    if (echo_ptr->status == BUSY)// && (cur_div != 1)) 
	{
        arg = 1;
	}
	cur_div = arg;
#endif
	switch (arg)
	{
	case 1:
        //deg_str("set sys clk 1\n");
        SYSTEM_CLK_DIV1();
		break;
	case 2:
        //deg_str("set sys clk 2\n");
        SYSTEM_CLK_DIV2();
		break;
	case 4:
        //deg_str("set sys clk 4\n");
        SYSTEM_CLK_DIV4();
		break;

	default:
		break;
	}	
}

/*----------------------------------------------------------------------------*/
/**@brief  系统主函数
   @param  无
   @return 无
   @note   void main(void)
*/
/*----------------------------------------------------------------------------*/

void sys_init(void)
{
    uart_init();
    sys_printf("AC309N-C\n");
    core_power_on();
    OTP_CLK_DIV2();
    DECODER_DIV2();
    sys_clk_div(4);//SYSTEM_CLK_DIV4();
    set_vol_tab_ptr(analog_vol_tab, digital_vol_tab);
                                    
#if (NO_DISP != monitor)
    init_display();
#endif
    sd_speed_init(0,100);

//#if SDMMC_CMD_MODE
//    sd_chk_ctl(SET_SD_H_CHK);
//#endif
    init_port_sd();
    kv_init(); ///按键音初始化函数
    
#ifdef AC_SLAVE_ENABLE
	DSA_init();
#endif

#if RTC_ENABLE
    if (rtc_init())			//RTC初始化，检测是否闹钟开机
    {
        work_mode = RTC_MODE;
    }
#else
    {
        u8 rtc_reg = read_rtc_reg();
        if (rtc_reg & BIT(7))					//检测是否掉电
        {
            rtc_reg &= ~BIT(7); 				//清零PDFLAG
            write_rtc_reg(rtc_reg);
#if USE_RTC_RAM

#if RTC_ENABLE
            reset_rtc_ram();
#else
            {
                u8 i;
                for (i = 0; i < 64; i++)
                {
                    write_rtc_ram(i, 0);
                }
            }
#endif   ///<RTC_ENABLE
            

#endif ///<USE_RTC_RAM
        }
    }
#endif
    key_init();
    bsp_init();
#if ECHO_ENABLE
    dec_analog_vol_sel(1);
    echo_ptr = (REVERB_CTL _xdata *)get_echo_var_ptr(1);
    encode_msg = (ENCODE_MSG _xdata *)get_encode_msg_ptr();
    app_echo.strong = 150;
    app_echo.deep = 40;
#else
    dec_analog_vol_sel(0);
    get_echo_var_ptr(0);///<传参0，不适用混响功能
#endif
    interrupt_init(15, rtcisr);
    interrupt_init(3, timer3isr);
    interrupt_init(0, timer0isr);
    enable_interrupt();
	flashled(0);
}
void Idle_hdlr()
{
    u8 key;

    SYSTEM_CLK_DIV4();
    flush_all_msg();
    key_table_sel(0);

    while (1)
    {
        key = app_get_msg();
		
        switch (key)
        {
        case MSG_POWER_DOWN:
		work_mode = MUSIC_MODE;
		return;
    	case MSG_SDMMC_IN_SEL:
	 	DSA_SEL_DEV=DEVICE_SDMMC0;	
		work_mode = MUSIC_MODE;
		return;		
    	case MSG_USB_DISK_IN_SEL:
	 	DSA_SEL_DEV=DEVICE_UDISK;	
		work_mode = MUSIC_MODE;
		return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
		work_mode = MUSIC_MODE;
            return;

	case MSG_HALF_SECOND :	
		device_check();
            break;					
	default:
            ap_handle_hotkey(key);
                break;
        }
    }
}
void main(void)
{
    clock_in = T0CNT;									//输入时钟,define in clock.h
  //  WDT_EN();
    sys_init();
    AMUX_P2IE_SET(AMUX0_IE&AMUX1_IE);
    sys_info_init();
    clear_all_event();
    flush_all_msg();
    //work_mode=REC_MIC_MODE;
    ///*
    work_mode = IDLE_MODE;
    DSA_SEL_DEV=NO_DEVICE;	

    while (1)
    {
#ifdef AC_SLAVE_ENABLE
	DSA_init();
#endif	 
        switch (work_mode)
        {
        case MUSIC_MODE:
	     sys_printf("MUSIC DECODE MODE ");
            music_decode();
            break;
#if USB_DEVICE_ENABLE
        case USB_DEVICE_MODE:
            usb_audio_massstorage();
            break;
#endif     

        case FM_RADIO_MODE:
	     sys_printf(" AUX  1  MODE ");			
            fm_radio();
            break;

        case AUX_MODE:
	     sys_printf(" AUX  2  MODE ");						
            aux_fun();
            break;
			
        case REC_MIC_MODE:
            rec_mic_fun();
            break;

        case IDLE_MODE:
	     sys_printf(" IDLE   MODE ");									
            Idle_hdlr();
            break;   
			
        default:
            work_mode = MUSIC_MODE;
            break;
        }
        //write_info(MEM_SYSMODE ,work_mode);
    }
    //*/
}
