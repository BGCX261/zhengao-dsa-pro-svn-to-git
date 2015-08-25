/*--------------------------------------------------------------------------*/
/**@file    ipod_mode.c
   @brief   ipod_mode- 模式主循环
   @details
   @author   R A
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"
#include "config.h"
#include "ipod_mode.h"
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

#ifdef IPOD_MODE_ENABLE 
/*----------------------------------------------------------------------------*/
/**@brief   Line-In 模式信息初始化
   @param   void
   @return  void
   @author  Change.tsai
   @note    void Line_in_info_init(void)
*/
/*----------------------------------------------------------------------------*/
void ipod_info_init(void) AT(LINE_IN_CODE)
{
    /*------------System configuration-----------*/
    Sys_IRInput = 0;
    Sys_Volume = 1;
  
    /*---------AUX MAIN UI--------------*/
    SET_UI_MAIN(MENU_IPOD_MAIN);
    UI_menu(MENU_IPOD_MAIN);
    key_table_sel(0);
}


/*----------------------------------------------------------------------------*/
/**@brief   Line-In 模式主循环
   @param   void
   @return  void
   @author  Change.tsai
   @note    void Line_in_loop(void)
*/
/*----------------------------------------------------------------------------*/
void ipod_hdlr(void) AT(LINE_IN_CODE)
{
    u8 msg;

    activate_pop_noise_hdlr(MS_1500);

    while (1)
    {
        msg = app_get_msg();

	 event_halfsecond_hdlr(msg);

        switch (msg)
        {
        case MSG_MUSIC_NEW_DEVICE_IN:
		func_msg_hdlr(S_FUNC,SYS_USB_MODE);
        case MSG_CHANGE_WORK_MODE:
            return;

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
void ipod_main(void) AT(LINE_IN_CODE)
{
    ext_pa_mute(PA_MUTE);   
    ipod_info_init();
    dac_channel_sel(DAC_IPOD_PATH);
    system_clk_div(CLK_1M);
    ipod_hdlr();
    ext_pa_mute(PA_MUTE);   
}
#endif
