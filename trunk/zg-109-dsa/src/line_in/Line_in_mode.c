/*--------------------------------------------------------------------------*/
/**@file    Line_in_mode.c
   @brief   Line-In 模式主循环
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"
#include "config.h"
#include "Line_in_mode.h"
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
#include "FM_API.h"

#ifndef NOT_USE_LINE_IN_FUNC
/*----------------------------------------------------------------------------*/
/**@brief   Line-In 模式信息初始化
   @param   void
   @return  void
   @author  Change.tsai
   @note    void Line_in_info_init(void)
*/
/*----------------------------------------------------------------------------*/
void Line_in_info_init(void) AT(LINE_IN_CODE)
{
    set_play_status_led(LED_SPARK_ON);
    ext_pa_mute(PA_MUTE);   
	
    /*------------System configuration-----------*/
    Sys_IRInput = 0;
    Sys_Volume = 1;
  
    /*---------AUX MAIN UI--------------*/
    SET_UI_MAIN(MENU_AUX_MAIN);
    UI_menu(MENU_AUX_MAIN);
    key_table_sel(0);
#ifdef BLUE_TOOTH_AUX_FUNC_ENABLE	
    BLUE_TOOTH_PWR_ON();
    BLUE_TOOTH_AUX_MODE();
#endif
}

void Line_in_end_hdlr(void) AT(LINE_IN_CODE)
{
    ext_pa_mute(PA_MUTE);   
	
#ifdef RADIO_PLAY_KEY_MUTE_VOL
	dac_mute(0);
#endif

#ifdef BLUE_TOOTH_AUX_FUNC_ENABLE	
    BLUE_TOOTH_PWR_OFF();
    BLUE_TOOTH_AUX_MODE_RELEASE();
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief   Line-In 模式主循环
   @param   void
   @return  void
   @author  Change.tsai
   @note    void Line_in_loop(void)
*/
/*----------------------------------------------------------------------------*/
void Line_in_mode_loop(void) AT(LINE_IN_CODE)
{
    u8 msg;

    activate_pop_noise_hdlr();

    while (1)
    {
        msg = app_get_msg();
		
	 event_halfsecond_hdlr(msg);

        switch (msg)
        {
#ifdef AUX_PLAY_KEY_MUTE_VOL
        case MSG_MUSIC_PP:
            	put_msg_lifo(MSG_MUTE);
		break;
#endif
        
        case MSG_AUX_IN:
            break;
        case MSG_AUX_OUT :
	 func_msg_hdlr(O_FUNC,MSG_AUX_OUT);			
#ifdef FM_AUX_SHARE_SAME_PATH		
#ifndef NO_FM_CHIP_ON_BOARD
       if(chk_fm_dev_online()){	//NO FM
	       func_msg_hdlr(I_FUNC,SYS_RADIO_MODE);
	    	func_msg_hdlr(S_FUNC,SYS_RADIO_MODE);	
		break;
	}
#endif
#endif
 	     put_msg_lifo(MSG_NEXT_WORKMODE); 
            break;
        case MSG_MUSIC_NEW_DEVICE_IN:
		func_msg_hdlr(S_FUNC,SYS_USB_MODE);
        case MSG_CHANGE_WORK_MODE:
            return;
#ifdef AUX_NEXT_PREV_ADJ_VOL
	case MSG_MUSIC_NEXT_FILE:
 	     put_msg_lifo(MSG_VOL_UP); 
	     break;
	case MSG_MUSIC_PREV_FILE:
 	     put_msg_lifo(MSG_VOL_DOWN); 	
	     break;
#endif

        case MSG_HALF_SECOND:     

	     pop_noise_handler();		
		 
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
/**@brief   Line-In 模式
   @param   void
   @return  void
   @author  Change.tsai
   @note    void Line_in_mode(void)
*/
/*----------------------------------------------------------------------------*/
void Line_in_mode(void) AT(LINE_IN_CODE)
{
    Line_in_info_init();
    dac_channel_sel(DAC_AUX_PATH);
    system_clk_div(CLK_1M);
    Line_in_mode_loop();
    Line_in_end_hdlr();   
}
#endif
