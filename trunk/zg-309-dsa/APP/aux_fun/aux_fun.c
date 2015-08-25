/*--------------------------------------------------------------------------*/
/**@file    fm_receive.c
   @brief   FM接收任务模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/

#include "aux_fun.h"
#include "dac.h"
#include "clock.h"
#include "rtc_api.h"
#include "eq.h"

extern bool input_number_en;
extern u8  main_menu, cur_menu, main_menu_conter ;
extern u16 input_number;
extern _xdata SYS_WORK_MODE  work_mode;
extern u8 _idata last_work_mode;
extern u8 _xdata decode_buffer[];
extern u8 eq_mode;
extern bool vol_change_en;
extern u8 play_status;							///<播放状态

/*----------------------------------------------------------------------------*/
/**@brief   Line IN模式主循环
   @param   无
   @return  无
   @note    void aux_main(void)
*/
/*----------------------------------------------------------------------------*/
void aux_main(void)
{
    u8 key;

    while (1)
    {
#ifdef EXCHANGE_LINE_IN_CHANNEL
        dac_out_select(DAC_AMUX0, 0);
#else
        dac_out_select(DAC_AMUX1, 0);
#endif

        key = app_get_msg();

        switch (key)
        {
#if defined(LINE_IN_PLAY_KEY_PAUSE)
        case MSG_MUSIC_PP:											//暂停和播放
            if (play_status == MAD_PLAY)
            {
            	  ext_amp_mute(1);
		  dac_mute_control(1,1);					
                play_status = MAD_PAUSE;
            }
            else if (play_status == MAD_PAUSE)
            {
	         dac_mute_control(0,1);	
            	  ext_amp_mute(0);
                play_status = MAD_PLAY;
            }
		break;
#endif
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
	     Set_Curr_Func(SYS_MP3DECODE_USB);
            return;

        case MSG_HALF_SECOND:
////////////////////////////////////////////////////////////
//显示界面的切换
            set_brightness_fade_out();
            if (main_menu_conter < SUB_MENU_TIME)
            {
                main_menu_conter++;
            }
            else if (cur_menu != main_menu)
            {
                cur_menu = main_menu;
                disp_port(cur_menu);
            }
            break;

#if (AMUX_SPECTRUM_EN == 1)
        case MSG_100MS:
            if (cur_menu == MENU_AUX)
            {
                music_spec_cul(1);
                disp_port(MENU_100MS_REFRESH);
            }
            break;
#endif
#if RTC_ENABLE
        case MSG_ALM_ON:
            write_next_alm_sec();
	     Set_Curr_Func(SYS_RTC);
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
#endif
        default:
            ap_handle_hotkey(key);
            break;
        }
    }

}
/*----------------------------------------------------------------------------*/
/**@brief   Line IN模式入口
   @param   无
   @return  无
   @note    void aux_fun(void)
*/
/*----------------------------------------------------------------------------*/
void aux_fun(void)
{
//    printf("enter aux\n");
//	amp_abd(1);
    play_status = MAD_PLAY;
    input_number_en = 0;
    vol_change_en=1;
    main_menu = MENU_AUX;
    disp_port(MENU_AUX);
    amux_dsp_eq();
#if AMUX_SPECTRUM_EN
    SYSTEM_CLK_DIV1();
#else
    SYSTEM_CLK_DIV4();
#endif

    key_table_sel(0);
    flush_all_msg();

#if AMUX_SPECTRUM_EN
    recording_start(0, decode_buffer);
#endif
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
    aux_main();
    main_vol_set(0, CHANGE_VOL_NO_MEM);
#if AMUX_SPECTRUM_EN
    recording_end();
#endif
}
