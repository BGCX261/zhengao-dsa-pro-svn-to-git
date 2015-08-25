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
#ifdef EVENT_50MS_HANDLER_ENABLE
extern _no_init bool _bit event_50ms_handle;
#endif
extern struct Str_Band Current_Band;
extern xd_u8 MEM_FREQ,MEM_CH,MEM_ALL_CH;
_no_init FM_MODE_VAR _data fm_mode_var;
_no_init u8 _data scan_mode;
bool radio_play_pause=0;
extern xd_u8 radio_band_mode;

/*----------------------------------------------------------------------------*/
/**@brief    FM 模式主循环
   @param    无
   @return   无
   @note     void fm_play(void)
*/
/*----------------------------------------------------------------------------*/
void radio_preset_handler()
{
	reset_radio_mem(FM_MODE);
	reset_radio_mem(MW_MODE);
}
void fm_play(void) AT(FM_CODE)
{
    u8 scan_counter =0;
    u8 key= 0;
	
    activate_pop_noise_hdlr(MS_1500);

#ifdef AMP_GPIO_POWER_CTRL
    AMP_TURN_ON_POWER();
#endif
   put_msg_lifo(MSG_RADIO_CHIP_INIT);
    while (1)
    {
        key = app_get_msg();

	 event_halfsecond_hdlr(key);

#ifdef EVENT_50MS_HANDLER_ENABLE
	if(event_50ms_handle){
		event_50ms_handle =0;
		event_50ms_hdlr();
	}
#endif


        switch (key)
        {

        case MSG_RADIO_CHIP_INIT:
		//adc_mode_switcher_protect(AD_MODE_PROTECT);			
		init_fm_rev();	
		radio_band_switcher();	
		activate_pop_noise_hdlr(MS_500);
		//adc_mode_switcher_protect(AD_MODE_UNPROTECT);
		break;
        case MSG_RADIO_BAND_SWITCH:
	       flush_all_msg();	
              scan_mode = FM_SCAN_STOP;
		activate_pop_noise_hdlr(MS_500);
		radio_band_switcher();	
		break;
        case MSG_MUSIC_NEW_DEVICE_IN:
		break;
	 	//func_msg_hdlr(S_FUNC,SYS_USB_MODE);
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_STOP_SCAN:
	     if(scan_mode != FM_SCAN_STOP){		 	
            		scan_counter = 1;                   //再搜索一个频点就停止
            		put_msg_lifo(MSG_FM_SCAN_ALL_INIT);
		}
		 break;
			
        case MSG_FM_SCAN_ALL_INIT:
            if (scan_mode == FM_SCAN_STOP)
            {
                fm_mode_var.bTotalChannel = 10;
                fm_mode_var.bFreChannel = 0;
                fm_mode_var.wFreq = Current_Band.Band_Bottom - Current_Band.Seek_Step;					//自动搜索从最低的频点开始
                scan_counter = (Current_Band.Max_channel+1);
                scan_mode = FM_SCAN_ALL;
            	  flush_all_msg();	
				
    		  ext_pa_mute(PA_MUTE);
            }
            else
            {
                scan_counter = 1;                   //再搜索一个频点就停止
            }

        case MSG_FM_SCAN_ALL:

            if((scan_mode == FM_SCAN_PREV)||(scan_mode == FM_SCAN_NEXT)){
			ext_pa_mute(PA_MUTE);
            }
            if (fm_scan(scan_mode))
            {
                if (scan_mode == FM_SCAN_ALL){
                    	delay_n10ms(100);
               }
		else if(scan_mode == FM_SCAN_END){
                     put_msg_lifo(MSG_FM_NEXT_STATION);
                    	delay_n10ms(100);                         				 
                     scan_mode = FM_SCAN_STOP;
			break;
		}
		else
                {
                    scan_mode = FM_SCAN_STOP;
    		      ext_pa_mute(PA_UNMUTE);
	             flush_all_msg();	
                    break;
                }
            }

            scan_counter--;
				
            if (scan_counter == 0)
            {
            	  flush_all_msg();	
                //fm_module_mute(0);

		  activate_pop_noise_hdlr(MS_500);
                if (scan_mode == FM_SCAN_ALL)                 //全频点搜索结束，播放第一个台
                {

                	fm_mode_var.bFreChannel = 1;
	    		restore_station_from_ch();
	    		UI_menu(MENU_FM_CHANNEL);
                }
                scan_mode = FM_SCAN_STOP;					

            }
            else                                                    //搜索过程中只响应事件
            {
                put_msg_fifo(MSG_FM_SCAN_ALL);
            	  //delay_n10ms(20);       				
            }
			break;

        case MSG_FM_SCAN_ALL_DOWN:
            scan_mode = FM_SCAN_PREV;
            scan_counter = Current_Band.Max_channel+1;
            put_msg_lifo(MSG_FM_SCAN_ALL);
            break;

        case MSG_FM_SCAN_ALL_UP:
            scan_mode = FM_SCAN_NEXT;
            scan_counter = Current_Band.Max_channel+1;			
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

	     //fm_module_mute(0);
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
	     //fm_module_mute(0);
	     UI_menu(MENU_FM_MAIN);
            break;

        case MSG_FM_PREV_STATION:
            flush_all_msg();
#ifdef RADIO_NEXT_PREV_STOP_SCAN
	     if(scan_mode != FM_SCAN_STOP){
            		put_msg_lifo(MSG_STOP_SCAN);
			break;
	     }
#endif						
            if (fm_mode_var.bTotalChannel == 0)
                break;
            fm_mode_var.bFreChannel -= 2;
        case MSG_FM_NEXT_STATION:
			
#ifdef RADIO_NEXT_PREV_STOP_SCAN
	     if(scan_mode != FM_SCAN_STOP){
            		put_msg_lifo(MSG_STOP_SCAN);
			break;
	     }
#endif			
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
	    activate_pop_noise_hdlr(MS_500);

	    restore_station_from_ch();
           set_fre(FM_CUR_FRE);

	    //fm_module_mute(0);
	    UI_menu(MENU_FM_CHANNEL);
            break;
#if 0
        case MSG_CH_SAVE:
            ch_save();
            break;
#endif
        case MSG_HALF_SECOND:

	     pop_noise_handler();			

            LED_FADE_OFF();
            UI_menu(MENU_MAIN);
            break;
			
#ifdef RADIO_PP_KEY_FM_MW_SEL

        case MSG_MUSIC_PP:
		if(radio_band_mode==FM_MODE){
			radio_band_set(MW_MODE);
		}
		else{
			radio_band_set(FM_MODE);
		}
	       put_msg_lifo(MSG_RADIO_BAND_SWITCH);				
		break;

#else

        case MSG_MUSIC_PP:

#ifdef RADIO_NEXT_PREV_STOP_SCAN
	     if(scan_mode != FM_SCAN_STOP){
            		put_msg_lifo(MSG_STOP_SCAN);
			break;
	     }
#endif	

#if 1
	     radio_play_pause=1-radio_play_pause;
	     if(radio_play_pause){		
    		  ext_pa_mute(PA_MUTE);
	    }
	    else{
    		  ext_pa_mute(PA_UNMUTE);
	   }
          UI_menu(MENU_FM_DISP_FRE);
#endif
		
#if 0//def UI_ENABLE
            if (UI_var.bCurMenu == MENU_INPUT_NUMBER)   //暂停和播放
            {
                put_msg_lifo(MSG_INPUT_TIMEOUT);
                break;
            }
#else
            break;
#endif

#endif

#ifndef RADIO_NO_NUM_INPUT
        case MSG_INPUT_TIMEOUT:
            /*由红外界面返回*/
            if (input_number <= Current_Band.Max_channel)							//输入的是台号
            {
                key = get_fre_via_channle(input_number);
                if (key != 0xff)
                {
                    fm_mode_var.wFreq = key + Current_Band.Band_Bottom;
                    fm_mode_var.bFreChannel = input_number;
                    set_fre(FM_CUR_FRE);
                    //fm_module_mute(0);
                    UI_menu(MENU_FM_DISP_FRE);
                }
            }
            else if ((input_number >= Current_Band.Band_Bottom) && (input_number <= Current_Band.Band_Top)) //输入的是频点
            {
                fm_mode_var.wFreq = input_number;
                fm_mode_var.bFreChannel = get_channel_via_fre(fm_mode_var.wFreq - Current_Band.Band_Bottom);
                set_fre(FM_CUR_FRE);
                //fm_module_mute(0);
            }
            input_number = 0;
            set_memory(MEM_FREQ,((fm_mode_var.wFreq - Current_Band.Band_Bottom)/Current_Band.Seek_Step));
	     set_memory(MEM_CH, fm_mode_var.bFreChannel);
            UI_menu(MENU_FM_DISP_FRE);
            break;
#endif
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
	//adc_mode_switcher_protect(AD_MODE_PROTECT);
#ifdef AMP_GPIO_SEL_AB_D_MODE
	AMP_GPIO_SEL_AB_MODE();
#endif		
#ifndef DISABLE_P05_OSC_OUTPUT
    	P05_config(P05_OSC_CLK);
#endif

	chk_fm_dev_online();

    	//init_fm_rev();
        P2HD &= ~0x7;
        sd_chk_ctl(SET_SD_CHK_STEP, 255);
       //fm_info_init();
      	radio_band_switcher();	

       dac_channel_sel(DAC_RADIO_PATH);
        system_clk_div(CLK_24M);
       fm_play();
		
    	ext_pa_mute(PA_MUTE);
       dac_channel_sel(DAC_DECODER);
       fm_rev_powerdown();
       sd_chk_ctl(SET_SD_CHK_STEP, 20);
       P2HD |= 0x7;

	//dac_mute(0); 					
	radio_play_pause =0;
	
#ifdef AMP_GPIO_SEL_AB_D_MODE
	AMP_GPIO_SEL_D_MODE();
#endif		

#ifndef DISABLE_P05_OSC_OUTPUT
    	P05_config(P05_NORMAL_IO);
#endif
}
