/*--------------------------------------------------------------------------*/
/**@file    FM_radio.c
   @brief   FM 模式主循环
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"
#include "fm_radio.h"
#include "FM_API.h"
#include "hot_msg.h"
#include "msg.h"
#include "key.h"
#include "main.h"
#include "iic.h"
#include "UI_API.h"
#include "music_play.h"
#include "tff.h"
#include "dac.h"
#include "clock.h"
#include "sdmmc_api.h"
#include "misc_hdlr_if.h"

extern ENUM_WORK_MODE _data work_mode;
_no_init FM_MODE_VAR _data fm_mode_var;
_no_init u8 _data scan_mode;

/*----------------------------------------------------------------------------*/
/**@brief    FM 模式主循环
   @param    无
   @return   无
   @note     void fm_play(void)
*/
/*----------------------------------------------------------------------------*/
void fm_play(void) AT(FM_CODE)
{
    u8 scan_counter =0;
    u8 key= 0;
	
    activate_pop_noise_hdlr();
	
    while (1)
    {
        key = app_get_msg();

	 event_halfsecond_hdlr(key);

        switch (key)
        {
        case MSG_MUSIC_NEW_DEVICE_IN:
	 	func_msg_hdlr(S_FUNC,SYS_USB_MODE);
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_STOP_SCAN:
  	     set_play_status_led(LED_SPARK_ON);					
            scan_counter = 1;                   //再搜索一个频点就停止
            break;
			
        case MSG_FM_SCAN_ALL_INIT:
            if (scan_mode == FM_SCAN_STOP)
            {
                set_memory(MEM_CHAN, 0);
        		set_memory(MEM_FRE, 0);
                clear_all_fm_point();
                fm_mode_var.bTotalChannel = 0;
                fm_mode_var.bFreChannel = 0;
                fm_mode_var.wFreq = MIN_FRE - 1;					//自动搜索从最低的频点开始
                scan_counter = MAX_CHANNL;
                scan_mode = FM_SCAN_ALL;
            	  flush_all_msg();	
            }
            else
            {
                scan_counter = 1;                   //再搜索一个频点就停止
            }

        case MSG_FM_SCAN_ALL:
            if (fm_scan(scan_mode))
            {
                if (scan_mode == FM_SCAN_ALL)
                    delay_n10ms(100);                               //播放1S
                else
                {
		      set_play_status_led(LED_SPARK_ON);				
                    scan_mode = FM_SCAN_STOP;
                    break;
                }
            }

            scan_counter--;
            if (scan_counter == 0)
            {
            	  flush_all_msg();	
                if (scan_mode == FM_SCAN_ALL)                 //全频点搜索结束，播放第一个台
                {
                    put_msg_lifo(MSG_FM_NEXT_STATION);
  		      set_play_status_led(LED_SPARK_ON);				
                    scan_mode = FM_SCAN_STOP;
                }
                else                            //半自动搜索，播放当前频点
                {
		      set_play_status_led(LED_SPARK_ON);				
                    scan_mode = FM_SCAN_STOP;
                    fm_module_mute(0);
                    break;
                }
            }
            else                                                    //搜索过程中只响应事件
            {
	         set_play_status_led(LED_SPARK_FAST);				            	  
                put_msg_fifo(MSG_FM_SCAN_ALL);
            	  //delay_n10ms(20);       				
            }
			break;

        case MSG_FM_SCAN_ALL_DOWN:
            scan_mode = FM_SCAN_PREV;		
            put_msg_lifo(MSG_FM_SCAN_ALL);
            break;

        case MSG_FM_SCAN_ALL_UP:
            scan_mode = FM_SCAN_NEXT;
            put_msg_lifo(MSG_FM_SCAN_ALL);
			break;

        case MSG_FM_PREV_STEP:
            flush_all_msg();
#ifdef RADIO_NEXT_PREV_STOP_SCAN
	     if(scan_mode != FM_SCAN_STOP){
            		put_msg_lifo(MSG_STOP_SCAN);
			break;
	     }
#endif
            set_fre(FM_FRE_DEC);
            fm_mode_var.bFreChannel = get_channel_via_fre(fm_mode_var.wFreq - MIN_FRE);						//查找该频点是否有记忆过
            set_memory(MEM_FRE, fm_mode_var.wFreq - MIN_FRE);
			set_memory(MEM_CHAN, fm_mode_var.bFreChannel);
			fm_module_mute(0);
			UI_menu(MENU_FM_MAIN);
            break;

        case MSG_FM_NEXT_STEP:
            flush_all_msg();
#ifdef RADIO_NEXT_PREV_STOP_SCAN
	     if(scan_mode != FM_SCAN_STOP){
            		put_msg_lifo(MSG_STOP_SCAN);
			break;
	     }
#endif			
            set_fre(FM_FRE_INC);
            fm_mode_var.bFreChannel = get_channel_via_fre(fm_mode_var.wFreq - MIN_FRE);						//查找该频点是否有记忆过
            set_memory(MEM_FRE, fm_mode_var.wFreq - MIN_FRE);
			set_memory(MEM_CHAN, fm_mode_var.bFreChannel);
			fm_module_mute(0);
			UI_menu(MENU_FM_MAIN);
            break;

        case MSG_FM_PREV_STATION:
            flush_all_msg();
            if (fm_mode_var.bTotalChannel == 0)
                break;
            fm_mode_var.bFreChannel -= 2;
        case MSG_FM_NEXT_STATION:
            if (fm_mode_var.bTotalChannel == 0)
                break;
            fm_mode_var.bFreChannel++;

            if ((fm_mode_var.bFreChannel == 0) || (fm_mode_var.bFreChannel == 0xff))
            {
                fm_mode_var.bFreChannel = fm_mode_var.bTotalChannel;
            }
            else if (fm_mode_var.bFreChannel > fm_mode_var.bTotalChannel)
            {
                fm_mode_var.bFreChannel = 1;
            }
            fm_mode_var.wFreq = get_fre_via_channle(fm_mode_var.bFreChannel) + MIN_FRE;				//根据台号找频点
            set_fre(FM_CUR_FRE);
            set_memory(MEM_FRE, fm_mode_var.wFreq - MIN_FRE);
			set_memory(MEM_CHAN, fm_mode_var.bFreChannel);
			fm_module_mute(0);
			UI_menu(MENU_FM_CHANNEL);
            break;

        case MSG_CH_SAVE:
            ch_save();
            break;

        case MSG_HALF_SECOND:

	     pop_noise_handler();			

            LED_FADE_OFF();
            UI_menu(MENU_MAIN);
            break;

        case MSG_MUSIC_PP:

#ifdef RADIO_PLAY_KEY_MUTE_VOL
	     if(scan_mode != FM_SCAN_STOP){
	    	     	put_msg_lifo(MSG_STOP_SCAN);
			break;
	     }
#endif
#ifdef RADIO_PLAY_KEY_MUTE_VOL
            	put_msg_lifo(MSG_MUTE);
		break;
#endif
			
#ifdef UI_ENABLE
            if (UI_var.bCurMenu == MENU_INPUT_NUMBER)   //暂停和播放
            {
                put_msg_lifo(MSG_INPUT_TIMEOUT);
                break;
            }
#else
            break;
#endif

        case MSG_INPUT_TIMEOUT:
            /*由红外界面返回*/
            if (input_number <= MAX_CHANNL)							//输入的是台号
            {
                key = get_fre_via_channle(input_number);
                if (key != 0xff)
                {
                    fm_mode_var.wFreq = key + MIN_FRE;
                    fm_mode_var.bFreChannel = input_number;
                    set_fre(FM_CUR_FRE);
                    fm_module_mute(0);
                    UI_menu(MENU_FM_DISP_FRE);
                }
            }
            else if ((input_number >= MIN_FRE) && (input_number <= MAX_FRE)) //输入的是频点
            {
                fm_mode_var.wFreq = input_number;
                fm_mode_var.bFreChannel = get_channel_via_fre(fm_mode_var.wFreq - MIN_FRE);
                set_fre(FM_CUR_FRE);
                fm_module_mute(0);
            }
            input_number = 0;
            set_memory(MEM_FRE, fm_mode_var.wFreq - MIN_FRE);
			set_memory(MEM_CHAN, fm_mode_var.bFreChannel);
            UI_menu(MENU_FM_DISP_FRE);
            break;

        default:
            ap_handle_hotkey(key);
            break;
        }

    }
}

/*----------------------------------------------------------------------------*/
/**@brief    FM 模式
   @param    无
   @return   无
   @note     void fm_mode(void)
*/
/*----------------------------------------------------------------------------*/
void fm_mode(void) AT(FM_CODE)
{

    	ext_pa_mute(PA_MUTE);

#ifdef AMP_GPIO_SEL_AB_D_MODE
	AMP_GPIO_SEL_AB_MODE();
#endif		
#ifndef DISABLE_P05_OSC_OUTPUT
    	P05_config(P05_OSC_CLK);
#endif

    	init_fm_rev();
        P2HD &= ~0x7;
        sd_chk_ctl(SET_SD_CHK_STEP, 255);
       fm_info_init();
       dac_channel_sel(DAC_RADIO_PATH);
        system_clk_div(CLK_1M);
       fm_play();

      	set_play_status_led(LED_SPARK_ON);
		
    	ext_pa_mute(PA_MUTE);   
       dac_channel_sel(DAC_DECODER);
       fm_rev_powerdown();
        sd_chk_ctl(SET_SD_CHK_STEP, 20);
        P2HD |= 0x7;

#ifdef AMP_GPIO_SEL_AB_D_MODE
	AMP_GPIO_SEL_D_MODE();
#endif		
#ifdef RADIO_PLAY_KEY_MUTE_VOL
	dac_mute(0);
#endif
#ifndef DISABLE_P05_OSC_OUTPUT
    	P05_config(P05_NORMAL_IO);
#endif
}
