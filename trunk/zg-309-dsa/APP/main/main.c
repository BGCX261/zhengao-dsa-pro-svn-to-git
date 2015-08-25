/*--------------------------------------------------------------------------*/
/**@file   main.c
   @brief  系统主函数
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"

#include "main.h"
#include "disp.h"
#include "fm_rev.h"
#include "led.h"
#include "music.h"
#include "device.h"
#include "dac.h"
#include "msgfor_usb.h"
#include "clock.h"
#include "led_ind_drv.h"

#include "rtc_mode.h"
#include "pll_sof.h"
#include  "tunch_key.h"
//#include  "start_music.h"
extern u8 _idata clock_in;
extern u8 given_device;
extern u16 given_file_number;

extern u8 eq_mode;
extern u8 play_mode;
extern void check_hprc_sof(void);

extern bool pc_connect, udisk_connect, sdmmc_connect;
extern u8 _bdata device_online;			    ///<设备在线标记

extern u8 _xdata alm_cnt;
u8 _code one_table[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};

bool input_number_en;					///<是否允许数字键输入功能
bool change_eq_en;						///<是否允许改变EQ的设置
extern _xdata SYS_WORK_MODE work_mode;							///<工作模式变量
u8 _idata last_work_mode;				///<RTC 闹钟前的工作模式
bool aux_online;						///<AUX在线状态
bool kv_flag;							///<按键音的发送标记
extern void play_led_flash();
#ifdef AC_SLAVE_ENABLE
extern void DSA_init(void);
extern bool DSA_GETHERING_DATA_ENABLE_BIT;
#endif
u8 _xdata P0_IE;

void port_pnie(void)
{
	P0_IE = 0XFF;
}

#pragma disable
void port_pnie_init(void)
{
	P0IE = P0_IE;	
}

/*----------------------------------------------------------------------------*/
/**@brief  Line In检测函数
   @param  无
   @return 无
   @note   void aux_check(void)
*/
/*----------------------------------------------------------------------------*/
#ifndef NOT_USE_LINE_IN_FUNC
#ifdef USE_LINE_IN_DETECT_FUNC
static void aux_check(void)
{
    static u8 aux_cnt_online;

#ifdef AUX_DETECT_SHARE_WITH_IIC_SCL
    if (iic_busy)
    {
        return;
    }
#endif	

    aux_detect_in();
	
    _nop_();_nop_();_nop_();
	
    if (AUX_DETECT_GPIO)
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
        if (aux_cnt_online > 20)
        {
            if (!aux_online)
            {
                put_msg_lifo(MSG_AUX_IN);
                aux_online = 1;
            }
        }
    }
    aux_detect_in_off(); //linein check port
}
#endif
#endif
/*----------------------------------------------------------------------------*/
/**@brief   使用独立的GPIO检测SD card在线
   @param   void
   @return  void
   @note    void sdmmc_detect(void)
*/
/*----------------------------------------------------------------------------*/
#if SDMMC_GPIO_MODE
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
#endif
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
/**@brief  TIME0中断服务程序
   @param  无
   @return 无
   @note   void timer0isr(void)
*/
/*----------------------------------------------------------------------------*/
void timer0isr(void)
{
    static u8 counter0, counter1;

    PSW = 0x08;
    DPCON = 0x0;
    T0CON &= ~(BIT(7));			//clear pending

    //disp_scan();
    adc_scan();
    counter0++;
    usb_polling();

#ifndef NO_PLAY_STATUS_LED
	//play_led_flash();
#endif
    if ((counter0 % 2) == 0){			//10ms
		DSA_GETHERING_DATA_ENABLE_BIT=1;
    }
	
    if ((counter0 % 5) == 0)			//10ms
    {

        dec_delay_counter();
#if SDMMC_CMD_MODE
        sd_online_check();
#elif SDMMC_CLK_MODE
        sdmmc_online_chk(1);
#elif SDMMC_GPIO_MODE
        sdmmc_detect();
#endif
#ifndef NO_ADKEY_FUNC
        keyScan();
#endif
    }

#if (AMUX_SPECTRUM_EN == 1)
    if ((counter0 % 50) == 0)
    {
        put_msg_fifo(MSG_100MS);
    }
#endif	
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
    u8 tmp;

    tmp = read_info(MEM_VOL);

    if ((tmp > MAX_MAIN_VOL) || (tmp == 0))              //每次开机时，不要超过最大音量的一半，以免开机音量过大
    {
        tmp = 22;

    }
	
#if (VOLUME_DEFUALT>0)
    tmp = VOLUME_DEFUALT;
#endif
    dac_init(tmp);
    delay_10ms(50);										//等待,检测USB,SD在线状态
    restore_music_point();
#if RTC_ENABLE
    if (work_mode != SYS_RTC)
#endif
    {
    	device_check();
#if USB_DEVICE_ENABLE
        if (pc_connect)
            Set_Curr_Func(SYS_USB_DEVICE);
        else if (udisk_connect || sdmmc_connect)
            Set_Curr_Func(SYS_MP3DECODE_USB);
#else
        if (udisk_connect || sdmmc_connect)
            Set_Curr_Func(SYS_MP3DECODE_USB);
#endif
        else
        {
            work_mode = read_info(MEM_SYSMODE);
            if (work_mode > MAX_WORK_MODE)
            {
            		Set_Curr_Func(SYS_MP3DECODE_USB);
            }
        }
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
	port_pnie();
	port_pnie_init();

#ifdef UART_ENABLE	
    uart_init();
    printf("power on\n");
#endif	
    core_power_on();
    OTP_CLK_DIV2();
    DECODER_DIV2();
    SYSTEM_CLK_DIV4();
    init_display();
    sd_speed_init(1,100);

#if SDMMC_CMD_MODE
    sd_chk_ctl(SET_SD_H_CHK);
#endif
    init_port_sd(SD_CLK_P20);      //0：选择P20做为SD卡的CLK脚；1: 选择P30做为SD卡的CLK
    kv_init(); ///按键音初始化函数

#if RTC_ENABLE
    if (rtc_init())		///<RTC初始化，检测是否闹钟开机
    {
            Set_Curr_Func(SYS_RTC);
    }
#else
    {
	        u8 rtc_reg = read_rtc_reg();
	        if (rtc_reg & BIT(7))					//检测是否掉电
	        {
	            rtc_reg &= ~BIT(7); 				//清零PDFLAG
	            write_rtc_reg(rtc_reg);
#if USE_RTC_RAM
	            reset_rtc_ram();
#endif
			//rtc_init();	
	    }
    }
#endif

#ifdef AC_SLAVE_ENABLE
	DSA_init();
#endif
#ifndef NO_ADKEY_FUNC
    key_init();
#endif
    bsp_init();
    interrupt_init(15, rtcisr);
    interrupt_init(3, timer3isr);
    interrupt_init(0, timer0isr);
#if((PLL_IN_HPRC == INPUT_OSC_SELECT) && USE_SOF_PLL)
	interrupt_init(10, sof_isr);
#endif
    enable_interrupt();
#if((PLL_IN_HPRC == INPUT_OSC_SELECT) && USE_SOF_PLL)	   
	check_hprc_sof();
#endif
}
//#define IR_DEBUG
#ifdef IR_DEBUG
extern u16 _idata user_code;   ///<红外遥控提取的用户码
extern u8 _idata irda_state;      ///<IR当前状态
extern u16 _idata irda_data;   ///<IR读取读取出的数?
extern u8 keyDetect(void);
void IR_Debug_func()
{
	while(1){
		keyDetect();
		delay_10ms(20);
	}
		
}
#endif

void Idle_hdlr()
{
    u8 key;
    xd_u8 idle_timer=0,idle_flag=0;
#ifndef USE_MANUAL_IDLE_FUNC
//    set_play_flash(LED_FLASH_STOP);
//    Mute_Ext_PA(MUTE);
//    set_lcd_flash_lock(LOCK);
#endif	

    SYSTEM_CLK_DIV4();
    flush_all_msg();

#ifdef AC_SLAVE_ENABLE
	DSA_init();
#endif	 

    while (1)
    {
        key = app_get_msg();
		
        switch (key)
        {
        case MSG_POWER_DOWN:
	 	Set_Curr_Func(SYS_MP3DECODE_USB);
		return;
//#ifdef NO_DEV_DEFAULT_GO_TO_IDLE		
        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入

	     if(idle_flag==0){
		idle_flag =1;
	 	idle_timer=6;
		break;
	    }
            put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
			
            return;
//#endif			
        //case MSG_NO_DEVICE:
        //	disp_port(MENU_NODEVICE);
         //   	break;	
        //case MSG_SYS_IDLE:
        //	disp_port(MENU_POWER_OFF);
	//	break;

	case MSG_HALF_SECOND :	
		device_check();
		
		if(idle_flag==1){
			
			idle_timer--;
			if(idle_timer==0){
           			 put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
			}
		}
		#if 1
		if((device_online&0x02)>0){
	            put_msg_lifo(MSG_USB_DISK_IN_SEL);
		}
		#endif
            break;			
			
	default:
            ap_handle_hotkey(key);
                break;
        }
    }
}
extern void music_info_init(void);
void main(void)
{
#if((PLL_IN_HPRC == INPUT_OSC_SELECT) && USE_SOF_PLL)
	hprc_otp_cnt = (T1CNT&0x3f);
	if(T1CNT&0x80)
	{
		osc12m_online = 1;	
	}
#endif
    clock_in = T0CNT;									//输入时钟,define in clock.h
    WDT_EN();
//  new_led_gpio_init();
    sys_init();
    //AMUX_P2IE_SET(AMUX0_IE);
    sys_info_init();
    Init_Func_List();
    ext_amp_mute(0);
    //tch_key_init(MAIN_CLK_12M);
    clear_all_event();
    flush_all_msg();
    cipher_init(0x12345678);

#ifdef IR_DEBUG
	IR_Debug_func();
#endif
    	Set_Curr_Func(SYS_IDLE);
    while (1)
    {
    	Set_Curr_Func(work_mode);

        switch (work_mode)
        {
	 case SYS_MP3DECODE_USB:
	 case SYS_MP3DECODE_SD:	 	
#ifdef UART_ENABLE	
	     sys_printf("---> work loop go in decode play");
#endif	 	
            music_decode();
            break;
#if USB_DEVICE_ENABLE
        case SYS_USB_DEVICE:
            usb_audio_massstorage();
            break;
#endif
        case SYS_FMREV:
#ifdef UART_ENABLE	
	     sys_printf("---> main loop go in  SYS_FMREV ");
#endif			
            fm_radio();
            break;

        case SYS_AUX:
#ifdef UART_ENABLE	
	     sys_printf("---> main loop go in  SYS_AUX  ");
#endif			
            aux_fun();
            break;

#ifdef  USE_RTC_FUNC
        case SYS_RTC:
#ifdef UART_ENABLE	
	     sys_printf("---> main loop go in  SYS_RTC  ");
#endif			
            rtc_fun();
            break;
#endif
	 case SYS_IDLE:
#ifdef UART_ENABLE	
	     sys_printf("---> main loop go in  SYS_IDLE  ");
#endif
	     Idle_hdlr();	

	    music_info_init();

	     break;
        default:
            work_mode = SYS_MP3DECODE_USB;
            break;
        }

	if(work_mode !=SYS_IDLE){
        	write_info(MEM_SYSMODE ,work_mode);
	}
    }
}
