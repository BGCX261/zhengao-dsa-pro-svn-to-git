/*--------------------------------------------------------------------------*/
/**@file    bluetooth_mode.c
   @brief   Line-In 模式主循环
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"
#include "config.h"
#include "bluetooth_mode.h"
#include "msg.h"
#include "hot_msg.h"
#include "key.h"
#include "main.h"
#include "device.h"
#include "iic.h"
#include "UI_API.h"
#include "LCD.h"
#include "dac.h"
#include "clock.h"
#include "misc_hdlr_if.h"

#ifdef BLUE_TOOTH_MODE_ENABLE 


#ifdef BLUE_TOOTH_STATUS_LED_PARTTERN
extern void blue_tooth_status_led_init(void);
extern void blue_tooth_status_led_hdlr(void);
#endif

extern void set_led_status(u8 statu_cmd);

#ifdef BLUE_TOOTH_CELLPHONE_FUNC        
xd_u8 bt_call_status = 0;
#endif

#ifdef BLUE_TOOTH_UART_FUNC 
extern void blue_tooth_uart_init(void);
extern void bluetooth_rev_msg_hdlr(void);
extern void bluetooth_promt_msg_hdlr(u8 key_msg);
extern void blue_tooth_uart_release(void);

#ifdef BLUE_TOOTH_CONFIG_DEV_NAME
extern void config_dev_name(void);
#endif
bool bt_play_status = 0;
xd_u8 bt_connect_status = 0;
u8 get_blue_tooth_connect_status(void)
{
	return bt_connect_status;
}	
#endif

/*----------------------------------------------------------------------------*/
/**@brief   Line-In 模式信息初始化
   @param   void
   @return  void
   @author  Change.tsai
   @note    void Line_in_info_init(void)
*/
/*----------------------------------------------------------------------------*/
void bluetooth_info_init(void) AT(LINE_IN_CODE)
{
#ifdef BLUE_TOOTH_STATUS_LED_PARTTERN
    blue_tooth_status_led_init();
#endif	
    BLUE_TOOTH_PWR_ON();
#ifdef BLUE_TOOTH_AUX_FUNC_ENABLE	
    BLUE_TOOTH_AUX_MODE_RELEASE();
#endif

    /*------------System configuration-----------*/
    Sys_IRInput = 0;
    Sys_Volume = 1;
  
    /*---------AUX MAIN UI--------------*/
    SET_UI_MAIN(MENU_BLUETOOTH_MAIN);
    UI_menu(MENU_BLUETOOTH_MAIN);
    key_table_sel(0);

#ifdef BLUE_TOOTH_CELLPHONE_FUNC        
    bt_call_status = CALL_IDLE;	
#endif	
    bt_connect_status = 0;
    bt_play_status = 0;
}
void bluetooth_end_hdlr(void) AT(LINE_IN_CODE)
{

    ext_pa_mute(PA_MUTE);  
	
#ifdef BLUE_TOOTH_UART_FUNC 
    blue_tooth_uart_release();	
#endif

#ifdef BLUE_TOOTH_STATUS_LED_PARTTERN
    set_led_status(BT_STA_LED_IDLE);
    blue_tooth_status_led_hdlr();
#endif			

    BLUE_TOOTH_PWR_OFF();

#ifdef BLUE_TOOTH_CELLPHONE_FUNC        
    bt_call_status = CALL_IDLE;	
#endif	
    bt_connect_status = 0;
    bt_play_status = 0;
}


/*----------------------------------------------------------------------------*/
/**@brief   Line-In 模式主循环
   @param   void
   @return  void
   @author  Change.tsai
   @note    void Line_in_loop(void)
*/
/*----------------------------------------------------------------------------*/
void bluetooth_hdlr(void) AT(LINE_IN_CODE)
{
    u8 msg;
#ifdef BLUE_TOOTH_UART_FUNC 
	blue_tooth_uart_init();
#endif

    activate_pop_noise_hdlr();
#ifdef BLUE_TOOTH_CONFIG_DEV_NAME
    config_dev_name();
#endif
    while (1)
    {
        msg = app_get_msg();

	 event_halfsecond_hdlr(msg);
		
#ifdef BLUE_TOOTH_UART_FUNC 
	bluetooth_rev_msg_hdlr();
	bluetooth_promt_msg_hdlr(msg);
#endif	 
        switch (msg)
        {
#ifdef BLUE_TOOTH_CELLPHONE_FUNC      
#ifdef USE_PP_ANSWER_PHONE
	case MSG_MUSIC_PP:
#elif defined(USE_MODE_ANSWER_PHONE)	
	case MSG_NEXT_WORKMODE:
#endif
	case MSG_BT_PHONE_KEY:
		if(bt_call_status ==INCOMING_CALL){
			put_msg_fifo(MSG_BT_ANSWER_CALL);
			bt_call_status = CALL_ACTIVE;	
			set_led_status(BT_STA_LED_INCOMING);
			
		}
		else if((bt_call_status == CALL_ACTIVE)||(bt_call_status == OUTGOING_CALL)){
			put_msg_fifo(MSG_BT_END_CALL);
			bt_call_status = CALL_IDLE;	
			set_led_status(BT_STA_LED_SDBY);
		}
		else{
#if defined(USE_MODE_ANSWER_PHONE)	
			goto __HOT_MSG;
#endif
		}
		break;	
        case MSG_MUSIC_PP:
		bt_play_status =1-bt_play_status;
		if(bt_play_status)
			set_led_status(BT_STA_LED_PLAY);
		else
			set_led_status(BT_STA_LED_SDBY);			
		break;		
	case MSG_BT_REPAIRING:		
        case MSG_BT_PAIRING:
		set_led_status(BT_STA_LED_PAIR);
		bt_connect_status=0;				
		break;
	case MSG_BT_INCOMING_CALL:
#ifdef BLUETOOTH_UART_DEBUG		
		my_puts(" ----> MSG_BT_INCOMING_CALL \n");
#endif		
		set_led_status(BT_STA_LED_INCOMING);
		bt_call_status = INCOMING_CALL;
		break;
	case MSG_BT_OUTGOING_CALL:
#ifdef BLUETOOTH_UART_DEBUG				
		my_puts(" ----> MSG_BT_OUTGOING_CALL \n");
#endif	
		set_led_status(BT_STA_LED_INCOMING);
		bt_call_status = OUTGOING_CALL;
		break;		
	case MSG_BT_DROP_CALL:
#ifdef BLUETOOTH_UART_DEBUG						
		my_puts(" ----> MSG_BT_DROP_CALL \n");
#endif	
		set_led_status(BT_STA_LED_SDBY);
		bt_call_status = CALL_IDLE;		
		break;
	case MSG_BT_ACTIVE_CALL:
#ifdef BLUETOOTH_UART_DEBUG						
		my_puts(" ----> MSG_BT_ACTIVE_CALL \n");
#endif	
		//set_led_status(BT_STA_LED_CALL);
		bt_call_status = CALL_ACTIVE;				
		break;
#endif		
	case MSG_BT_CONNECTED:
#ifdef BLUE_TOOTH_STATUS_LED_PARTTERN		
		set_led_status(BT_STA_LED_SDBY);
#endif
		bt_connect_status=1;		
		break;		
        case MSG_MUSIC_NEW_DEVICE_IN:
		func_msg_hdlr(S_FUNC,SYS_USB_MODE);
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_HALF_SECOND:
			
#ifdef BLUE_TOOTH_STATUS_LED_PARTTERN
	    blue_tooth_status_led_hdlr();
#endif			
	     pop_noise_handler();					
            LED_FADE_OFF();
            UI_menu(MENU_MAIN);
            break;   
          
        default:
__HOT_MSG:			
            ap_handle_hotkey(msg);
            break;
        }
    }

}

/*----------------------------------------------------------------------------*/
/**@brief   Line-In 模式
   @param   void
   @return  void
   @author  Change.tsai
   @note    void Line_in_mode(void)
*/
/*----------------------------------------------------------------------------*/
void bluetooth_main(void) AT(LINE_IN_CODE)
{
    set_play_status_led(LED_SPARK_ON);
    ext_pa_mute(PA_MUTE);   
    bluetooth_info_init();
    dac_channel_sel(DAC_BT_PATH);
    system_clk_div(CLK_1M);
    bluetooth_hdlr();
    bluetooth_end_hdlr();
}
#endif
