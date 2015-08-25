/*--------------------------------------------------------------------------*/
/**@file     main.c
   @brief    主流程
   @details
   @author
   @date    2011-3-7
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"
#include "main.h"
#include "clock.h"
#include "music_play.h"
#include "fm_radio.h"
#include "USB_Device_Mode.h"
#include "key.h"
#include "RTC_Mode.h"
#include "RTC_API.h"
#include "msg.h"
#include "iic.h"
#include "device.h"
#include "DAC.h"
#include "get_music_file.h"
#include "usb_host.h"
#include "sdmmc_api.h"
#include "LCD.h"
#include "LED5X7.h"
#include "UI_API.h"
#include "bluetooth_mode.h"
#include "Line_in_mode.h"
#include "LCD_SEG4X8.h"
#include "SPI.h"
#include "LCD_SEG5X9.h"
#include "misc_hdlr_if.h"
#include "gpio_if.h"
#include "hot_msg.h"

#include "play_voice.h"


#ifdef EVENT_50MS_HANDLER_ENABLE
_no_init bool _bit event_50ms_handle;
#endif

_no_init void (_near_func * _pdata int_enter_pro[16])(void) AT(INTERRUPT_TABLE);
_no_init ENUM_WORK_MODE _data work_mode;
_root _no_init u8 _data B_CURRENTBANK @ 0x1F;
_no_init bool _bit Sys_Volume;
_no_init bool _bit Sys_IRInput;
_no_init bool _bit Sys_HalfSec;
_no_init bool _bit alm_on_flag;
_no_init bool _bit set_sd_clk; ///<sd clk检测用，要操作卡时要设置为1,不操作卡时要设置为0，用途是不读卡时把clk脚保持一个稳定的电平
/*----------------------------------------------------------------------------*/
/**@brief   显示设备扫描函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void monitor_scan(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void monitor_scan(void) AT(COMMON_CODE)
{
#ifdef LED_5X7
    LED5X7_scan();
#endif
}

/*----------------------------------------------------------------------------*/
/** @brief: Timer1 中断服务程序
    @param: void
    @return:void
    @author:Change.tsai
    @note:  void Timer1_ISR(void)
*/
/*----------------------------------------------------------------------------*/
_near_func __root void Timer1_ISR(void) AT(COMMON_CODE)
{
    static _no_init u8 _data cnt;

    TMR1_CON0 |= BIT(6);            //clear pending

    dac_check();

#ifndef NOT_DISPLAY_SCAN
    /*UI Update*/
    monitor_scan();
#endif

#ifndef NOT_MOUNT_USB_FUNC
    /*Device Scan*/
    USB_online_otp();
#endif

#ifdef SDMMCA_DET_CLK
     sdmmc_clk_det0();
#endif
#ifdef SDMMCA_DET_CMD
    sdmmc_command_detect();
#endif
    ADC_scan();

#ifdef IR_REMOTE_EN
    /*IR overflow*///if (IR_code.boverflow)
    {
        IR_code.boverflow++;
        if (IR_code.boverflow > 56) //56*2ms = 112ms
        {
            //IR_code.boverflow = 0;
            /*IR Signal Clear*/
            IR_code.bState = 0;
        }
    }
#endif

    cnt++;
    if ((cnt % 5) == 0)             //10ms
    {
        key_scan();
        dec_delay_counter();
    }
	
    if ((cnt % 50) == 0){             //100ms
#ifdef EVENT_DETECTION_THREAD_HDLR
	 detect_event_func_hdlr();
#endif

#ifndef NO_PLAY_STATUS_LED
 	play_status_led_hdlr();
#endif
    }

#ifdef EVENT_50MS_HANDLER_ENABLE
    if ((cnt % 25) == 0){             //50ms
        event_50ms_handle=1;
    }
#endif

    if ((cnt % 250) == 0)
    {
        cnt = 0;
        Sys_HalfSec = !Sys_HalfSec;
        put_msg_fifo(MSG_HALF_SECOND);
    }
#ifdef RTC_ALARM_EN
    if (RTC_CON0 & BIT(7))
    {
        IRTC_WKCLRPND;
        put_event(EVENT_ALM_ON);
    }
#endif
#ifdef SDMMCA_DET_CLK
    sdmmc_clk_det1();
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief   Timer2 中断服务程序
   @param   void
   @return  void
   @author  Change.tsai
   @note    void Timer1_ISR(void)
*/
/*----------------------------------------------------------------------------*/
const u16 timer2_1ms_table[] AT(TABLE_CODE)=
{
    0x20,0x40,0x80,0x2f0,0x178,0x2f0
};
_near_func __root void Timer2_ISR(void) AT(COMMON_CODE)
{
    u16 bCap2;
    u8 cap;

    TMR2_CON |= BIT(6);

    bCap2 = (TMR2_PRDH << 8) | TMR2_PRDL;

    cap = bCap2 / timer2_1ms_table[system_clk];

    if (cap == 1)
    {
        IR_code.wData >>= 1;
        IR_code.bState++;
        IR_code.boverflow = 0;
    }
    else if (cap == 2)
    {
        IR_code.wData >>= 1;
        IR_code.bState++;
        IR_code.wData |= 0x8000;
        IR_code.boverflow = 0;
    }
    /*13ms-Sync*/
    else if ((cap == 13) || (cap < 8) || (cap > 100))
    {
        IR_code.bState = 0;
    }
    else
        IR_code.boverflow = 0;

    if (IR_code.bState == 16)
    {
        IR_code.wUserCode = IR_code.wData;
    }
}
/*----------------------------------------------------------------------------*/
/** @brief: 串口模块初始化
    @param: void
    @return:void
    @author:Juntham
    @note:  void uart_setup(void)
*/
/*----------------------------------------------------------------------------*/
void uart_setup(void) AT(CSTART)
{
#ifdef UART_DEBUG_ENABLE		
    uart_init();
#endif
    set_putchar(my_putchar);
#ifdef UART_DEBUG_ENABLE		
    my_puts(__DATE__);
    my_puts("\n");
    my_puts(__TIME__);
    my_puts("\n");
#endif
}


#ifndef NOT_DISPLAY_SCAN
/*----------------------------------------------------------------------------*/
/**@brief   UI 初始化
   @param   void
   @return  void
   @author  Change.tsai
   @note    void ui_init(void)
*/
/*----------------------------------------------------------------------------*/
static void ui_init(void) AT(CSTART)
{
#if defined LED_5X7
    LED5X7_init();
#endif

#if defined LCD_SEG_4X8 || LCD_SEG_3X9
    LCD_SEG4X8_init();
#endif

#if defined LCD_SEG_5X9
    LCD_SEG5X9_init();
#endif

#if defined LCD_96X32_SERIAL || defined LCD_128X32_SERIAL   \
    || defined LCD_128X64_SERIAL || defined LCD_128X64_PARALLEL
    LCD_init();
#endif
}
#endif


/*----------------------------------------------------------------------------*/
/**@brief   系统初始化
   @param   void
   @return  void
   @author  Change.tsai
   @note    void sys_init(void)
*/
/*----------------------------------------------------------------------------*/
static void sys_init(void) AT(CSTART)
{
    /*IIC I/O init*/
   	iic_init();
#ifndef NO_PLAY_STATUS_LED
    	led_port_init();
#ifdef TWO_PLAY_STATUS_LED
    	led_id2_port_init();
#endif
#endif

#ifndef NOT_DISPLAY_SCAN
    /*UI init*/
    	ui_init();
#endif
    /*Time Base init*/
    	int_enter_pro[TIMER1_INT] = Timer1_ISR;

#ifdef IR_REMOTE_EN
    /*IR Capture init*/
    	int_enter_pro[TIMER2_INT] = Timer2_ISR;
#endif
    /*Timebase interrupt init*/
    	IRTC_init();

    /*SD I/O & Controller init*/
    	sdmmc_init();

    /*ADKey init*/
    	AD_init();

    /*Hello UI*/
#ifndef USE_POWER_KEY
    	UI_menu(MENU_POWER_UP);
#endif

#ifdef AUX_DETECTION_THREAD_ENABLE
    	detect_event_func_register(AUX_PLUG_THREAD,AUX_INVALID_LEVEL,MSG_AUX_IN,MSG_AUX_OUT,
								aux_detect_init,aux_detect_level,aux_detect_release,aux_gpio_protect);
#endif

#ifdef PHONE_DETECTION_THREAD_ENABLE
    	detect_event_func_register(PHONE_PLUG_THREAD,AUX_INVALID_LEVEL,NO_MSG,NO_MSG,
								phone_detect_init,phone_detect_level,phone_detect_release,phone_gpio_protect);
#endif

#ifdef CHARGER_DETECTION_THREAD_ENABLE
    	detect_event_func_register(CHARGER_PLUG_THREAD,CHARGER_INVALID_LEVEL,NO_MSG,NO_MSG,
								charger_detect_init,charger_detect_level,charger_detect_release,charger_gpio_protect);
#endif

    /*ALL interrupt*/
    	EA = 1;

#ifdef USE_POWER_KEY
	power_key_hdlr(SYS_PWR_ON);
#endif
    /*Wait Device steady Plug In...*/
    	delay_n10ms(20);

    /*PLL初始化，会关总中断*/
	pll_init();

#ifdef IR_UART_DEBUG
    	debug_ir_func();
#endif
#ifdef ADKEY_UART_DEBUG
	debug_adkey_func();
#endif

    /*EEPROM verify*/
	eeprom_verify();
	/*DAC 初始化*/
    	DAC_init();
	
#ifdef OTP_MUSIC_FUNC_ENABLE
	voice_play_by_index(0);
#endif

    	init_func_list();
#ifdef SYS_POWER_ON_MEM_WORK_MODE
    	work_mode =(ENUM_WORK_MODE)get_memory(MEM_SYSMODE);
#elif defined(SYS_POWER_ON_FORCE_IN_BT_MODE)
	 func_msg_hdlr(S_FUNC,SYS_BLUETOOTH_MODE);
#else
	work_mode = SYS_USB_MODE;
#endif
	playfile.given_device = NO_DEVICE;
		

#ifdef AMP_GPIO_SEL_AB_D_MODE
	AMP_GPIO_SEL_D_MODE();
#endif		
}
void sys_idle_hdlr(void)
{
    u8 msg;

    Sys_IRInput = 0;
    Sys_Volume = 0;

    ext_pa_mute(PA_MUTE);   

    SET_UI_MAIN(MENU_IDLE_MAIN);
    UI_menu(MENU_IDLE_MAIN);
    key_table_sel(0);
    system_clk_div(CLK_1M);
	
#ifdef NO_DEVICE_DEFAULT_IDLE_MODE
    set_play_status_led(LED_SPARK_ON);
#else	
    set_play_status_led(LED_SPARK_STOP);
#endif

    while (1)
    {
        msg = app_get_msg();
		
	 event_halfsecond_hdlr(msg);
        switch (msg)
        {
#ifdef USE_BT_PHONE_KEY_SHORT_WAKEUP_IDLE
	case MSG_BT_PHONE_KEY:
              put_msg_lifo(MSG_NEXT_WORKMODE);
		break;
#endif
#ifdef USE_MODE_SHORT_WAKEUP_IDLE
	case MSG_NEXT_WORKMODE:
              put_msg_lifo(MSG_NEXT_WORKMODE);
		break;
#endif		
        case MSG_POWER_DOWN:
        case MSG_MUSIC_NEW_DEVICE_IN:
	     func_msg_hdlr(S_FUNC,SYS_USB_MODE);
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_HALF_SECOND:     
	     LED_FADE_OFF();
            UI_menu(MENU_MAIN);
            break;   
        default:
            ap_handle_hotkey(msg);		
            break;
        }
    }

}
/*----------------------------------------------------------------------------*/
/** @brief: 系统主循环
    @param: void
    @return:void
    @author:Juntham
    @note:  void main(void)
*/
/*----------------------------------------------------------------------------*/
void main(void) AT(CSTART)
{
	work_mode = SYS_IDLE_MODE;
	
	ext_pa_mute(PA_MUTE);
#ifndef NDEBUG
    	set_debug_mode(1);          //进入2线调试模式
#else
    	set_debug_mode(0);
#endif

#ifdef WDT_EN
    	config_wdt(0x5D);           //enable WDT 8S,如果改成4S,有些慢U盘会导致看门狗复位
#endif

    	uart_setup();

	sys_init();
    	clear_all_event();

    while (1)
    {
        flush_all_msg();
	 func_msg_hdlr(S_FUNC,work_mode);
   	 //deg(" --->main :work_mode %x \r\n",(u16)work_mode);
		
        switch (work_mode)
        {
        case SYS_USB_MODE:
        case SYS_SD_MODE:
#ifdef MAIN_UART_DEBUG		
            my_puts("main loop----> Music Mode\n");
#endif
            music_app();
            break;

#ifdef USB_DEVICE_EN
        case SYS_USB_DEVICE_MODE:
#ifdef MAIN_UART_DEBUG		
            my_puts("main loop----> PC Mode\n");
#endif
            USB_device_mode();
            break;
#endif

#ifdef RADIO_MODE_ENABLE
        case SYS_RADIO_MODE:
#ifdef MAIN_UART_DEBUG		
            my_puts("main loop----> FM Mode\n");
#endif
            fm_mode();
            break;
#endif

#ifndef NOT_USE_LINE_IN_FUNC
        case SYS_AUX_MODE:
 #ifdef MAIN_UART_DEBUG		
           my_puts("main loop----> AUX Mode\n");
#endif
            Line_in_mode();
            break;
#endif

#ifdef RTC_EN
        case SYS_RTC_MODE:
#ifdef MAIN_UART_DEBUG		
           my_puts("main loop----> RTC Mode\n");
#endif
	     RTC_mode();
            break;
#endif

#ifdef BLUE_TOOTH_MODE_ENABLE
    	 case SYS_BLUETOOTH_MODE:
#ifdef MAIN_UART_DEBUG		
           my_puts("main loop----> BT  Mode\n");
#endif	 	
	    bluetooth_main(); 	
	    break;
#endif    

#ifdef IPOD_MODE_ENABLE 
    	 case SYS_IPOD_MODE:
#ifdef MAIN_UART_DEBUG		
           my_puts("main loop----> IPOD  Mode\n");
#endif	 	
	    ipod_main(); 	
	    break;
#endif    

	case SYS_IDLE_MODE:
#ifdef MAIN_UART_DEBUG		
           my_puts("main loop----> IDLE  Mode\n");
#endif	 	
	    sys_idle_hdlr();
	    break;
		
	case SYS_PWR_OFF_MODE:
#ifdef MAIN_UART_DEBUG		
            my_puts("main loop----> power off Mode\n");
#endif
#ifdef USE_POWER_KEY
	     power_key_hdlr(SYS_PWR_OFF);
#elif defined(USE_POWER_IDLE_MODE)
	     power_key_hdlr(SYS_PWR_IDLE);
#endif
	     break;
        default:
	     func_msg_hdlr(S_FUNC,SYS_USB_MODE);
            break;
        }
        set_memory(MEM_SYSMODE, work_mode);
    }
}
