/*--------------------------------------------------------------------------*/
/**@file    hot_msg.c
   @brief   ϵͳ������Ϣ������
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "hot_msg.h"
#include "msg.h"
#include "device.h"
#include "get_music_file.h"
#include "main.h"
#include "key.h"
#include "iic.h"
#include "DAC.h"
#include "music_play.h"
#include "UI_API.h"
#include "RTC_API.h"
#include "play_file.h"
#include "break_point.h"
#include "dac.h"
#include "IRTC.h"
#include "misc_hdlr_if.h"

#include "FM_API.h"

extern ENUM_WORK_MODE _data work_mode;
extern u8 _data main_vol_L, main_vol_R;

#ifdef EVENT_50MS_HANDLER_ENABLE
extern _no_init bool _bit event_50ms_handle;
#endif

_no_init u16 _data input_number;	    ///<��������ֵ�ʵ��ֵ


/*----------------------------------------------------------------------------*/
/** @brief:
    @param:
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
static void new_device_in(u8 dev) AT(CSTART)
{
    func_msg_hdlr(I_FUNC,dev);
    LED_FADE_ON();
    dev -= MSG_USB_DISK_IN;
    music_device_info[dev].wBreak_point_filenum = 0;
    music_device_info[dev].wfileTotal = 0;
    playfile.given_file_method = PLAY_BREAK_POINT;
    playfile.given_device = (ENUM_DEVICE_SELECT_MODE)dev;
    put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
}
/*----------------------------------------------------------------------------*/
/**@brief   ������Ϣ���д�����
   @param   key�� ��Ҫ�������Ϣ
   @return  void
   @author: Juntham
   @note    void ap_handle_hotkey(u8 key)
*/
/*----------------------------------------------------------------------------*/
void ap_handle_hotkey(u8 key) AT(CSTART)
{
    u8 mode_idx_reg;
	
#ifdef EVENT_50MS_HANDLER_ENABLE
	if(event_50ms_handle){
		event_50ms_handle =0;
		event_50ms_hdlr();
	}
#endif

    switch (key)
    {
#ifdef RTC_EN
    case MSG_ALM_ON:
#ifdef STANDBY_EN
        read_RTC((RTC_TIME *)(&curr_time));

        if((curr_time.bHour == curr_alarm.bHour)
            &&(curr_time.bMin == curr_alarm.bMin)
              &&(curr_alarm.bSw))
#endif
        {
#ifdef STANDBY_EN
            alm_on_flag = 1;
#endif
            UI_menu(MENU_ALM_UP);
            RTC_setting_var.bAlarmOn = 1;
            write_next_ALM();
            RTC_setting_var.bLastWorkMode = work_mode;
            if (work_mode != SYS_RTC_MODE)
            {
		  func_msg_hdlr(S_FUNC,SYS_RTC_MODE);      
                put_msg_lifo(MSG_CHANGE_WORK_MODE);     //����ʹ�ø����ȼ���Ϣ����������������Ϣ��ͻ
            }
        }

        break;
#endif

    case MSG_POWER_DOWN:
		
#ifdef USE_POWER_KEY
	func_msg_hdlr(S_FUNC,SYS_PWR_OFF_MODE);
#elif defined(USE_POWER_IDLE_MODE)
	func_msg_hdlr(S_FUNC,SYS_PWR_OFF_MODE);
#else		
	func_msg_hdlr(S_FUNC,SYS_IDLE_MODE);
#endif
	put_msg_lifo(MSG_CHANGE_WORK_MODE);
	break;

    case MSG_MUTE:												//����
        if (!Sys_Volume)
            break;
        dac_mute_toggle();
        break;

    case MSG_USB_DISK_OUT:
    case MSG_SDMMCA_OUT:
#ifdef SDMMCB_EN
    case MSG_SDMMCB_OUT:
#endif
        LED_FADE_ON();
	 func_msg_hdlr(O_FUNC,key);
        /*��ǰ��豸������*/
        if ((device_check() == 0x0)&&((work_mode == SYS_USB_MODE)||(work_mode == SYS_SD_MODE)))
        {
            playfile.given_file_method = PLAY_BREAK_POINT;
            playfile.given_device = DEVICE_AUTO_NEXT;
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
            /*����ϵ���Ϣ*/
//#if defined BREAK_POINT_PLAY_EN && defined USE_EEPROM_MEMORY
#if defined BREAK_POINT_PLAY_EN && !defined USE_IRTC_MEMORY
            save_music_break_point(device_active);
#endif
        }
        break;

#ifdef USB_DEVICE_EN
    case MSG_USB_PC_IN:
#ifdef SDMMCA_EN
        music_device_info[DEVICE_SDMMCA].wBreak_point_filenum = 0;
        music_device_info[DEVICE_SDMMCA].wfileTotal = 0;
#endif
#ifdef SDMMCB_EN
        music_device_info[DEVICE_SDMMCB].wBreak_point_filenum = 0;
        music_device_info[DEVICE_SDMMCB].wfileTotal = 0;
#endif
        LED_FADE_ON();

	 func_msg_hdlr(S_FUNC,SYS_USB_DEVICE_MODE);
        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        break;

#endif
#ifndef NOT_USE_LINE_IN_FUNC
#if defined(USE_ADKEY_DETECT_AUX)||defined(AUX_DETECTION_THREAD_ENABLE)
    case MSG_AUX_IN :
        LED_FADE_ON();
	 func_msg_hdlr(I_FUNC,MSG_AUX_IN);		
#ifdef USB_DEVICE_EN
        if (work_mode != SYS_USB_DEVICE_MODE)
#endif
        {
#ifdef FM_AUX_SHARE_SAME_PATH
	    func_msg_hdlr(O_FUNC,SYS_RADIO_MODE);
#endif
	    func_msg_hdlr(S_FUNC,SYS_AUX_MODE);
           put_msg_lifo(MSG_CHANGE_WORK_MODE);
        }
        break;

    case MSG_AUX_OUT :
        LED_FADE_ON();
	 func_msg_hdlr(O_FUNC,MSG_AUX_OUT);				
#ifdef FM_AUX_SHARE_SAME_PATH		
#ifndef NO_FM_CHIP_ON_BOARD
       if(chk_fm_dev_online()){	//NO FM
	    func_msg_hdlr(I_FUNC,SYS_RADIO_MODE); 
	}
#endif
#endif
	 
        break;
#endif
#endif

#ifdef SDMMCA_EN
    case MSG_SDMMCA_IN :
#endif

#ifdef SDMMCB_EN
    case MSG_SDMMCB_IN :
#endif

#ifdef USB_DISK_EN
    case MSG_USB_DISK_IN  :
#endif
        new_device_in(key);
        break;

    case MSG_NEXT_WORKMODE:

#if 1
	mode_idx_reg = func_msg_hdlr(F_FUNC,F_FUNC);

       //my_printf("MSG_NEXT_WORKMODE : %x ,  %x  \r\n", work_mode,mode_idx_reg);

	if(work_mode == mode_idx_reg){
		break;
	}
	else{

		work_mode = (ENUM_WORK_MODE)mode_idx_reg;
		
		flush_all_msg();
		
		if(work_mode==SYS_USB_MODE){
			
		        new_device_in(MSG_USB_DISK_IN);
			 break;			
		}
		else if(work_mode==SYS_SD_MODE){

		        new_device_in(MSG_SDMMCA_IN);
			 break;
		}
		else if(work_mode==SYS_RADIO_MODE){


		}
#ifndef NOT_USE_LINE_IN_FUNC
		else if(work_mode==SYS_AUX_MODE){

		}		
#endif
	        put_msg_lifo(MSG_CHANGE_WORK_MODE);
		
	}
#else
        work_mode++;
        put_msg_lifo(MSG_CHANGE_WORK_MODE);
#endif		
        break;

    case MSG_VOL_UP:
        flush_all_msg();
        if (!Sys_Volume)
            break;
        main_vol_L++;
        main_vol_L++;
    case MSG_VOL_DOWN:
        flush_all_msg();
        if (!Sys_Volume)
            break;
        main_vol_L--;
        if (main_vol_L == 255)
            main_vol_L = 0;
        else if (main_vol_L > MAX_MAIN_VOL_L)
            main_vol_L = MAX_MAIN_VOL_L;

        main_vol_R = main_vol_L;
        set_main_vol(main_vol_L, main_vol_R);
        //deg("Vol-L %u/R %u\n", main_vol_L, main_vol_R);
        set_memory(MEM_VOL_L, main_vol_L);
        set_memory(MEM_VOL_R, main_vol_R);
        UI_menu(MENU_MAIN_VOL);
        break;

    case MSG_0:
    case MSG_1:
    case MSG_2:
    case MSG_3:
    case MSG_4:
    case MSG_5:
    case MSG_6:
    case MSG_7:
    case MSG_8:
    case MSG_9:
        if (!Sys_IRInput)
            break;

        if (input_number > 999)
            input_number = 0;

        input_number = input_number * 10 + key;
        UI_menu(MENU_INPUT_NUMBER);
        break;
    }
}

