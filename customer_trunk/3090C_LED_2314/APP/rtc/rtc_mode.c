/*--------------------------------------------------------------------------*/
/**@file    rtc_mode.c
   @brief   RTC任务模块
   @details
   @author
   @date   2011-7-4
   @note
*/
/*----------------------------------------------------------------------------*/
#include "rtc_mode.h"
#include "eq.h"
#include "PT2313.h"
#include "uart.h"

#if RTC_ENABLE
extern u8 _xdata all_alm_sw;

extern bool input_number_en;
extern  u8 main_menu, cur_menu, main_menu_conter;
extern u16 input_number;
extern u8 work_mode;
extern u8 _idata last_work_mode;
extern u8 _xdata alm_cnt;

extern RTC_TIME _xdata curr_time;
extern ALM_TIME _xdata alarm;
extern bool vol_change_en;
extern bool key_voice_en;

//extern DECODER_MSG _xdata *dec_msg;
extern u8 sys_main_vol;

u8 _xdata rtc_mode_setting;				 ///<RTC 时间/闹钟 设置模式标记
u8 _xdata rtc_coordinate;				 ///<RTC 时间界面反色坐标
u8 _xdata alm_coordinate;				 ///<RTC 闹钟界面反色坐标
bool alm_on_flag;		    			 ///<RTC 闹钟标记位
#if 1//defined(USE_SNOOZE_FUNC)        
u16 snooze_cnt=0;
bool snooze_en=0;
#define SNOOZE_TIME		5*2
void snooze_init()
{
	snooze_en =0;
	snooze_cnt =0;
}
void set_snooze_func(void)
{
	if(alm_on_flag){
		alm_on_flag =0;
		
		snooze_en =~snooze_en;	
	 	work_mode= RTC_MODE;
	       put_msg_lifo(MSG_CHANGE_WORK_MODE);
	}
	else{
		if(snooze_en){
			snooze_init();
		}
	}
}
void snooze_hdlr()
{
	if(snooze_en){
		if(snooze_cnt++>(SNOOZE_TIME*60)){
		//if(snooze_cnt++>(SNOOZE_TIME)){
			snooze_init();
        		put_msg_lifo(MSG_ALM_ON);
		}
	}
}
void clr_alarm_func(void)
{
	if(alm_on_flag){

	}
	else{
		alm_on_flag =0;
		snooze_en =0;	
	 	work_mode= RTC_MODE;
	       put_msg_lifo(MSG_CHANGE_WORK_MODE);
	}
}
#endif
bool alm_recover_vol_enable=0;
u8 alrm_vol_bakup=0;
u8 alarm_vol_adj=0;
void alarm_setting_vol_hdlr(void)
{	
	if(alm_on_flag){

		if(alm_recover_vol_enable){

			alarm_vol_adj++;
			
			if(sys_main_vol>20){
				alm_recover_vol_enable =0;
			}
			
			if(sys_main_vol<=20){
				//main_vol_set(sys_main_vol,SET_USE_CURRENT_VOL);
				PT2313_Config(sys_main_vol,VOL_ADJ);

				if(alarm_vol_adj==4){
					alarm_vol_adj=0;
					sys_main_vol++;
				}
				
			}
			else{

				if(sys_main_vol != alrm_vol_bakup)
					sys_main_vol = alrm_vol_bakup;
			}
		}
	}
}
/*----------------------------------------------------------------------------*/
/**@brief RTC模式主循环
   @param 	void
   @return  void
   @note  void deal_rtc(void)
*/
/*----------------------------------------------------------------------------*/
void deal_rtc(void)
{
    u8 key;
    u8 rtc_set_cnt;

    close_alarm();

    while (1)
    {
        key = app_get_msg();
#if 0
        if (alm_on_flag)
        {
            key = alm_msg_convert(key);
        }
#endif		
        switch (key)
        {
        case MSG_NEXT_WORKMODE:
        case MSG_REC_KEY:
        case MSG_REC_PLAY:
		break;
        case MSG_CHANGE_WORK_MODE:
            return;
			
        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
            break;

        case MSG_ALM_SOURCE:
			
              //if(rtc_mode_setting == ALARM_SETTING)
		{
#if 1
			if(alarm.sw==0)break;
			
			if(rtc_mode_setting != ALARM_SETTING){

				alarm.bSource =0;
				alm_coordinate=3;				
               		rtc_mode_setting = ALARM_SETTING;
	               	disp_port(MENU_ALM_SET);
					
			}
			else{
                		rtc_mode_setting = RTC_DISPLAY;
               		disp_port(MENU_RTC);
				break;

			}
#if 0			
			if(alm_coordinate==3){
                		rtc_mode_setting = RTC_DISPLAY;
               		disp_port(MENU_RTC);
				break;						
			}
			else{
				
				alarm.bSource =0;
				alm_coordinate=3;;
			}
#endif			

#else
			 alarm.bSource++;	
			if(alarm.bSource>3){
				alarm.bSource =0;
			}
#endif			
		}
                rtc_set_cnt=0;
			  
		break;
        case MSG_ALM_SETUP:
			
              if(rtc_mode_setting == ALARM_SETTING){
			alm_coordinate++;
			if(alm_coordinate>2){
                		rtc_mode_setting = RTC_DISPLAY;
			}
		}
		else{

			snooze_init();			
             		alm_coordinate = 1;
			alarm.sw=1;
			alarm.bSource =0;
               	rtc_mode_setting = ALARM_SETTING;
                	write_next_alm_sec();
			save_alarm_info();	
		}
                rtc_set_cnt=0;
		
              disp_port(MENU_RTC);
		break;
		
        case MSG_RTC_SETTING:
            if (rtc_mode_setting == RTC_SETTING)
            {
                	rtc_mode_setting = RTC_DISPLAY;
            }
	     else{
            		rtc_coordinate = 3;
                	rtc_mode_setting = RTC_SETTING;
	     }
                rtc_set_cnt=0;
		 
            disp_port(MENU_RTC);
            break;

        case MSG_RTC_NEXT:
			
            if (rtc_mode_setting == RTC_SETTING)
            {
                rtc_coordinate++;
                if (rtc_coordinate > 4)
                {
                	rtc_mode_setting = RTC_DISPLAY;
                }
                rtc_set_cnt=0;
                disp_port(MENU_RTC);
            }            
            break;
#if 0			
        case MSG_RTC_PREV:
            if (rtc_mode_setting == RTC_SETTING)
            {
                rtc_coordinate--;
                if (rtc_coordinate == 255)
                {
                    rtc_coordinate = 5;
                }
                rtc_set_cnt=0;
                disp_port(MENU_RTC);
            }
            if (rtc_mode_setting == ALARM_SETTING)
            {
                alm_coordinate--;
                if (alm_coordinate == 255)
                {
                    //if(alarm[0].sw)
                    //{
                    //	alm_coordinate = 9;
                    //}
                    //else
                    //{
                    alm_coordinate = 2;
                    //}
                }
                disp_port(MENU_ALM_SET);
            }
            break;
#endif			
        case MSG_RTC_PLUS:
        case MSG_RTC_PLUS_HOLD:
            if (rtc_mode_setting == RTC_SETTING)
            {
                rtc_set_cnt=0;
                curr_time_plus();
                write_rtc(&curr_time);
                write_next_alm_sec();
                disp_port(MENU_RTC);
            }
            if (rtc_mode_setting == ALARM_SETTING)
            {
                rtc_set_cnt=0;
                alm_time_plus();
                save_alarm_info();
                write_next_alm_sec();
		  if(alm_coordinate==3){
                	disp_port(MENU_ALM_SET);
		  }
		  else{
                	disp_port(MENU_RTC);
		  }
            }
            break;
        case MSG_RTC_MINUS:
        case MSG_RTC_MINUS_HOLD:
            if (rtc_mode_setting == RTC_SETTING)
            {
                rtc_set_cnt=0;
                curr_time_minus();
                write_rtc(&curr_time);
                write_next_alm_sec();
                disp_port(MENU_RTC);
            }
            if (rtc_mode_setting == ALARM_SETTING)
            {
                rtc_set_cnt=0;
                alm_time_minus();
                save_alarm_info();
                write_next_alm_sec();
		  if(alm_coordinate==3){
                	disp_port(MENU_ALM_SET);
		  }
		  else{				
                	disp_port(MENU_RTC);
		  }
            }
            break;

        case MSG_HALF_SECOND:

	     snooze_hdlr();
            if (main_menu_conter < SUB_MENU_TIME*4)
            {
                main_menu_conter++;
            }
            else if (cur_menu != main_menu)
            {
                rtc_mode_setting = RTC_DISPLAY;
                read_rtc(&curr_time);
                chk_date_err();
                disp_port(MENU_RTC);
            }

            if ((rtc_mode_setting == RTC_SETTING)||(rtc_mode_setting == ALARM_SETTING))
                rtc_set_cnt++;

            if ((rtc_set_cnt==8)&&((rtc_mode_setting == RTC_SETTING)||(rtc_mode_setting == ALARM_SETTING)))
            {
                rtc_set_cnt=0;
                rtc_mode_setting = RTC_DISPLAY;
                read_rtc(&curr_time);
                chk_date_err();
                disp_port(MENU_RTC);
            }

            if (cur_menu == MENU_RTC)
            {
                read_rtc(&curr_time);
                chk_date_err();
                disp_port(MENU_RTC);
            }
            break;

        case MSG_ALM_ON:
            write_next_alm_sec();
            alm_on_flag = 1;
	    alrm_vol_bakup=sys_main_vol;
	    sys_main_vol = 10;
	    alm_recover_vol_enable=1;		
	     if(alarm.bSource== 0){
			work_mode = MUSIC_MODE;
	     }
	     else if(alarm.bSource== 1){
			work_mode = MUSIC_MODE;
	     }		 
	     else if(alarm.bSource== 2){
			work_mode = FM_RADIO_MODE;
	     }		
	     else{
			work_mode = AUX_MODE;
	     }		
	     disp_port(MENU_RTC);
	    return;
	   break;

        default:
            ap_handle_hotkey(key);
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief RTC模式入口
   @param 	void
   @return  void
   @note  void rtc_fun(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_fun(void)
{
    MAIN_POWER_PORT_INIT();	
    MAIN_POWER_PORT_DISABLE();	
    iic_gpio_set_low();
    amp_mute(1);

    if(alm_on_flag){
		if(sys_main_vol != alrm_vol_bakup)
		sys_main_vol = alrm_vol_bakup;
    		alm_on_flag = 0;
    }
    input_number_en = 0;
    vol_change_en=0;
    key_voice_en=0;
    main_menu = MENU_RTC;
    close_alarm();
    dsp_set_eq_mode(0);			  //系统时钟div前需关闭eq
    SYSTEM_CLK_DIV4();
    key_table_sel(0);
    flush_all_msg();
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
    dac_out_select(DAC_MUSIC, 0);
	
    rtc_mode_setting = RTC_DISPLAY;
    rtc_coordinate = 0;
    alm_coordinate = 0;
    if (alm_cnt)
    {
        put_msg_lifo(MSG_ALM_ON);
    }
    else
    {
        read_rtc(&curr_time);
        chk_date_err();
        disp_port(MENU_RTC);
    }

    MAIN_POWER_PORT_INIT();	
    MAIN_POWER_PORT_DISABLE();	
	
    deal_rtc();

    amp_mute(1);
    MAIN_POWER_PORT_ENABLE();	

    delay_10ms(3);
    key_voice_en=0;
    main_vol_set(0, CHANGE_VOL_NO_MEM);
    MAIN_POWER_PORT_ENABLE();	
    amp_mute(1);
    delay_10ms(80);
  
    snooze_en =0;
	
    PT2313_Init();
    delay_10ms(10);
    PT2313_Init();
	
}
#endif
