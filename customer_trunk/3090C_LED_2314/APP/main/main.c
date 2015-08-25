/*--------------------------------------------------------------------------*/
/**@file   main.c
   @brief  ϵͳ������
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
#include "PT2313.h"

extern u8 _idata clock_in;
extern u8 given_device;
extern u16 given_file_number;

extern u8 eq_mode;
extern u8 play_mode;

extern bool pc_connect, udisk_connect, sdmmc_connect;
extern u8 _xdata win_buffer[];
extern u8 _xdata alm_cnt;
u8 _code one_table[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};

bool input_number_en;				///<�Ƿ��������ּ����빦��
bool change_eq_en;					///<�Ƿ������ı�EQ������
u8 work_mode;						///<����ģʽ����
u8 _idata last_work_mode;			///<RTC ����ǰ�Ĺ���ģʽ
bool aux_online;					///<AUX����״̬
bool kv_flag;						///<�������ķ��ͱ��

u8  main_menu;						///<��¼���ֲ�ͬģʽ�µ�������
u8  cur_menu;        				///<��ǰ����
u8  main_menu_conter;				///<�뿪�������ʱ��
bool flash_en;						///<��ʾ��������
u8 bright_counter;
extern void JogDetect(void);
extern u8 sys_main_vol;

/*----------------------------------------------------------------------------*/
/**@brief  Line In��⺯��
   @param  ��
   @return ��
   @note   void aux_check(void)
*/
/*----------------------------------------------------------------------------*/
static void aux_check(void)
{
    static u8 aux_cnt_online;


    P3DIR |= BIT(4); //linein check port
    P3PU |= BIT(4);
    _nop_();
    _nop_();
    //_nop_();
    if (P34)
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
        if (aux_cnt_online > 6)
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
/**@brief   ʹ�ö�����GPIO���SD card����
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
/**@brief  RTC�жϷ������
   @param  ��
   @return ��
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
/**@brief  RTC�жϷ������
   @param  ��
   @return ��
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

   JogDetect();

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
	 //disp_dled();
    }

//    if ((counter0 % 50) == 0)
//    {
//        put_msg_fifo(MSG_100MS);
//    }
    if((counter0 % 100) == 0)
    {
	 //aux_check();
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
/**@brief  ϵͳ������Ϣ�ĳ�ʼ��
   @param  ��
   @return ��
   @note   void sys_info_init(void)
*/
/*----------------------------------------------------------------------------*/
static void sys_info_init(void)
{

    sys_main_vol = read_info(MEM_VOL);

    if ((sys_main_vol > MAX_MAIN_VOL) || (sys_main_vol == 0))              //ÿ�ο���ʱ����Ҫ�������������һ�룬���⿪����������
    {
        sys_main_vol = MAX_MAIN_VOL / 2;

    }
        sys_main_vol = MAX_MAIN_VOL / 2;
	
    dac_init(MAX_MAIN_VOL);
    dsp_set_adc_con((0x0070));
    delay_10ms(200);										//�ȴ�,���USB,SD����״̬
    init_rec_name();
    restore_music_point();

#if 0	
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
#endif
}



/*----------------------------------------------------------------------------*/
/**@brief  ϵͳ��ʼ��
   @param  ��
   @return ��
   @note   void sys_clk_div(u8 arg)
*/
/*----------------------------------------------------------------------------*/
void sys_clk_div(u8 arg)
{
#if ECHO_ENABLE
	static u8 _idata cur_div;
	/*���칦��ʹ�ܺ�ϵͳʱ�ӱ���������48M*/
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
//#define IR_DEBUG
#ifdef IR_DEBUG
extern u16 _idata user_code;   ///<����ң����ȡ���û���
extern u8 _idata irda_state;      ///<IR��ǰ״̬
extern u16 _idata irda_data;   ///<IR��ȡ��ȡ������?
extern u8 keyDetect(void);
void IR_Debug_func()
{

	WDTCON |= BIT(7);
	while(1){

		if(irda_state==32){
		        printf_u16(user_code,'C');
		        deg_str("\r\n");
		        printf_u16(irda_data,'D');
			deg_str("\r\n");
			delay_10ms(50);
		}
	}
		
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief  ϵͳ������
   @param  ��
   @return ��
   @note   void main(void)
*/
/*----------------------------------------------------------------------------*/

void sys_init(void)
{
#if 0
    uart_init();
    deg_str("AC309N-C\n");
#endif	
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
    kv_init(); ///��������ʼ������

#if RTC_ENABLE
    if (rtc_init())			//RTC��ʼ��������Ƿ����ӿ���
    {
        work_mode = RTC_MODE;
    }
#else
    {
        u8 rtc_reg = read_rtc_reg();
        if (rtc_reg & BIT(7))					//����Ƿ����
        {
            rtc_reg &= ~(BIT(7)); 				//����PDFLAG
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
    get_echo_var_ptr(0);///<����0�������û��칦��
#endif
    interrupt_init(15, rtcisr);
    interrupt_init(3, timer3isr);
    interrupt_init(0, timer0isr);
    enable_interrupt();
}
	
void main(void)
{

    amp_mute(1);
    clock_in = T0CNT;									//����ʱ��,define in clock.h

    sys_init();
    power_key_hdlr(SYS_PWR_ON);
    AMUX_P2IE_SET(AMUX0_IE&AMUX1_IE);
    sys_info_init();
    clear_all_event();
    flush_all_msg();
	
    enter_fm_rev();

    PT2313_Init();
	
    work_mode=RTC_MODE;
#ifdef IR_DEBUG
	IR_Debug_func();
#endif

    while (1)
    {
        switch (work_mode)
        {
        case MUSIC_MODE:
            music_decode();
            break;
#if USB_DEVICE_ENABLE
        case USB_DEVICE_MODE:
            usb_audio_massstorage();
            break;
#endif     

#if 1//FM_MODULE                     
        case FM_RADIO_MODE:
            fm_radio();
            break;
#endif

        case AUX_MODE:
            aux_fun();
            break;

#if 1//RTC_ENABLE
        case RTC_MODE:
            rtc_fun();
            break;        
#endif
        case REC_MIC_MODE:
            rec_mic_fun();
            break;			
        case IDLE_MODE:
	     //power_key_hdlr(SYS_PWR_OFF);
            break;			

	     default:
            	work_mode = MUSIC_MODE;
            break;
        }
        write_info(MEM_SYSMODE ,work_mode);
    }
    //*/
}