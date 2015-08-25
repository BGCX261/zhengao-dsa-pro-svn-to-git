/*--------------------------------------------------------------------------*/
/**@file    msgfor_hot.c
   @brief   HOT ��Ϣ����ģ��
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/

#include "msgfor_hot.h"
#include "disp.h"
#include "main.h"
#include "device.h"
#include "eq.h"
#include "dac.h"
#include "rtc_api.h"
#include "echo.h"
#include "PT2313.h"
#include "rtc_mode.h"

extern void disk_remove_deal_for_music(void);

extern u8 work_mode;
extern u8 _idata last_work_mode;
extern bool input_number_en;
extern bool eq_change_en;
extern bool play_mode_change_en;

extern u8 given_device;
extern u16 given_file_number;
extern u8 given_file_method;
extern u8 eq_mode;
extern u8 play_mode;
extern u8  main_menu, cur_menu, main_menu_conter;
extern u8 device_active;
u16 input_number;	 ///<��������ֵ�ʵ��ֵ
bool vol_change_en;	 ///<�����޸�����λ
extern u8 device_online;
extern u8 music_type;
extern bool alm_on_flag;

bool rec_device_out;
u8 key_100_flag=0;
u8 sys_main_vol=0;
bool sys_mute_flag=0;

u8 rec_device_sel=0;

/*----------------------------------------------------------------------------*/
/**@brief   �������񶼻��õ�����Ϣ���д����ĺ���
   @param   key�� ��Ҫ��������Ϣ
   @return  0����Ҫ�л�����ģʽ;
   @note    unsigned char I2C_sendbyte(unsigned char I2Cdata)
*/
/*----------------------------------------------------------------------------*/
 bool ir_remote_set_snooze()
{
	if(alm_on_flag){
	       put_msg_lifo(MSG_SNOOZE_SETUP);
		return 1;
	}	
		return 0;
}
#if 1//defined(USE_TIMER_POWER_OFF_FUNC)
u8 timer_pwr_idx=0,timer_disp=0;
u16 timer_pwr_cnt=0;
u8 _code timer_tab[]={0,15,30,45,60,90};
void timer_pwr_setting()
{
	timer_pwr_idx++;
	if(timer_pwr_idx>(sizeof(timer_tab)-1)){

		timer_pwr_idx=0;
	}
	
	timer_pwr_cnt =0;
	timer_disp=timer_tab[timer_pwr_idx];
	
	disp_port(DISP_PWR_TIMER);
}
void timer_pwr_off_hdlr()
{
	if(timer_pwr_idx>0){
		timer_pwr_cnt++;

		//if(timer_pwr_cnt>=(timer_tab[timer_pwr_idx]/*2*60*/)){
		if(timer_pwr_cnt>=(timer_tab[timer_pwr_idx]*2*60)){
			
			timer_pwr_idx =0;
			timer_pwr_cnt =0;
       		set_brightness_all_on();
			work_mode = IDLE_MODE;
			put_msg_fifo(MSG_SYS_POWERON);		
		}	
	}
}
#endif

void ap_handle_hotkey(u8 key)
{
    u8 res;

    switch (key)
    {

#if ECHO_ENABLE
    case MSG_REV_SW:
        echo_sw();		
        break;
    
	case MSG_REV_STRONG_UP:
	case MSG_REV_STRONG_DOWN:
        if(echo_strong(key))
        {
            disp_port(MENU_REV_STRONG);   
        }
        break;
	
     case MSG_REV_DEEP_UP:
     case MSG_REV_DEEP_DOWN:
        if(echo_deep(key))
        {
            disp_port(MENU_REV_DEEP);
        }
        break;
#endif

     case MSG_ALM_SETUP:
	 	//clr_alarm_func();
	 	break;
     case MSG_SNOOZE_SETUP:
	 	set_snooze_func();
	 	break;
     case MSG_MUTE_UNMUTE:
	 	sys_mute_flag =~sys_mute_flag;
		if(sys_mute_flag){
    			amp_mute(1);
			PT2313_Config(0,VOL_ADJ);
		}
		else{
			PT2313_Config(sys_main_vol,VOL_ADJ);
    			amp_mute(0);
		}
	 	break;
     case MSG_SLEEP_SETUP:
	 	if(work_mode != RTC_MODE){
			timer_pwr_setting();
		}
		break;
     case MSG_SYS_POWERON:
	 	
	 	if(work_mode==RTC_MODE){
			
	 		work_mode= MUSIC_MODE;
		}
		else{
	 		work_mode= RTC_MODE;
		}

		timer_pwr_idx=0;
		
	       put_msg_lifo(MSG_CHANGE_WORK_MODE);
	 	break;

		
    case MSG_USB_DISK_OUT:
    case MSG_SDMMC_OUT:
		
        set_brightness_all_on();
        if( (!device_check() ) && (encode_status >= RECODE_INIT )) //��¼��ʱ����豸�γ�
        {	
            rec_device_out = 1;
            api_stop_encode();
            if(AUX_MODE == work_mode)
	        {
	            main_menu = MENU_AUX;
				disp_port(MENU_AUX);
	        }
#if FM_MODULE 
			else if(FM_RADIO_MODE == work_mode)
	        {
	            main_menu = MENU_FM_MAIN;
                disp_port(MENU_FM_MAIN);
	        }
#endif
            else
            {
                 put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
                 //break;  
            }
		}
        /*
        if((!device_check()) && (REC_MIC_MODE == work_mode))
        {
             put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
             break;   
        }
        */
	    if(MUSIC_MODE != work_mode)
			break;
        put_msg_lifo(MSG_DEVICE_REMOVED);
        disk_remove_deal_for_music();
        break;

#if USB_DEVICE_ENABLE
    case MSG_USB_PC_IN:

    #if ECHO_ENABLE
        if(BUSY == echo_ptr->status)
        {
            close_echo();
        }
    #endif
        break_encode();
        set_brightness_all_on();
        device_check();
        work_mode = USB_DEVICE_MODE;
        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        break;

    case MSG_USB_PC_OUT:
        set_brightness_all_on();
        break;
#endif

    case MSG_AUX_IN :
        break_encode();
        set_brightness_all_on();
#if USB_DEVICE_ENABLE
        if ((AUX_MODE != work_mode) && (work_mode != USB_DEVICE_MODE))
#else
        if (AUX_MODE != work_mode)
#endif
        {
            work_mode = AUX_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
        }
        break;

    case MSG_AUX_OUT :
        set_brightness_all_on();

	 if(work_mode != AUX_MODE)break;
	 
        if((RECODE_WORKING == encode_status)||(RECODE_PAUSE == encode_status))
        {	
            break;
        } 

        break_encode();

	 given_device = DEVICE_UDISK;
        given_file_method = PLAY_BREAK_POINT;      
	 put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
		
        break;

    case MSG_SDMMC_IN :
        set_brightness_all_on();
	 device_check();
        if((RECODE_WORKING == encode_status)||(RECODE_PAUSE == encode_status))
        {	
            break;
        } 
        
        break_encode();

#if USB_DEVICE_ENABLE
        if (work_mode == USB_DEVICE_MODE)
            break;
#endif

		given_device = read_info(MEM_ACTIVE_DEV);

		if(given_device == DEVICE_SDMMC0_REC)
			given_device = DEVICE_SDMMC0_REC;
		else
			given_device = DEVICE_SDMMC0;

        given_file_method = PLAY_BREAK_POINT;
        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        break;

    case MSG_USB_DISK_IN  :
        set_brightness_all_on();
		device_check();
        if((RECODE_WORKING == encode_status)||(RECODE_PAUSE == encode_status))
        {
            break;
        }
        break_encode();
       
		given_device = read_info(MEM_ACTIVE_DEV);

		if(given_device == DEVICE_UDISK_REC)
			given_device = DEVICE_UDISK_REC;
		else
	    	given_device = DEVICE_UDISK;

        given_file_method = PLAY_BREAK_POINT;      
        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        break;

    case MSG_NEXT_WORKMODE:
        break_encode();


	 if(work_mode == MUSIC_MODE){

		device_check();		
	    	if(((device_active &(~VIRTUAL_DEVICE))== DEVICE_UDISK)&&(device_online&DEVICE_SDMMC0)>0){

		    	given_device = DEVICE_SDMMC0;
		       given_file_method = PLAY_BREAK_POINT;      
		        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
			break;
		}
	 }
	
        work_mode++;
		

	if(work_mode > MAX_WORK_MODE){
		
            work_mode = MUSIC_MODE;

		if(get_device_online_status()&DEVICE_UDISK){
			
	    		given_device = DEVICE_UDISK;
		        given_file_method = PLAY_BREAK_POINT;      
		        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
		}
		else if(get_device_online_status()&DEVICE_SDMMC0){
			
	    		given_device = DEVICE_SDMMC0;
		        given_file_method = PLAY_BREAK_POINT;      
		        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
		}
		else{
        		work_mode++;
		}
	}


        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        break;

    case MSG_VOL_UP:
        if (vol_change_en==0)
            break;

	sys_main_vol++;
	sys_main_vol++;
    case MSG_VOL_DOWN:
        if (vol_change_en==0)
            break;
		
	if(sys_main_vol>0)
		sys_main_vol--;

	if(sys_main_vol>MAX_MAIN_VOL){
		sys_main_vol =MAX_MAIN_VOL;
	}
	
	sys_mute_flag =0;
	
	PT2313_Config(sys_main_vol,VOL_ADJ);
	
	 if(sys_main_vol==0){
    		amp_mute(1);
	 }
	 else{
    		amp_mute(0);
	 }		
        dac_mute_control(0,1);					//��������ʱ���Զ�UNMUTE
        write_info(MEM_VOL, sys_main_vol);
        disp_port(MENU_MAIN_VOL);
        break;
		
     case MSG_MUSIC_NEXT_EQ:
	 if(work_mode == RTC_MODE)
	 	break;

            eq_mode++;
            if (eq_mode > CLASSIC)
            {
                eq_mode = NORMAL;
            }

	    PT2313_Config(eq_mode,EQ_ADJ);
			
            set_eq(NORMAL);
            disp_port(MENU_SET_EQ);
            break;
			
    case MSG_100:
		
        if (!input_number_en)
            break;

	if (input_number > 999)
            input_number = 0;

	      key_100_flag = 0xFF;
#ifdef USE_10_PLUS_FUNC				  
	     input_number = input_number+10;
#else
	     input_number = input_number+100;
#endif
        disp_port(MENU_INPUT_NUMBER);
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
		
        if (!input_number_en)
            break;		
		
	     if(key_100_flag ==0xFF){
			input_number += key;
			key_100_flag = 0xFE;
	     }
	     else if(key_100_flag ==0xFE){
		 	
			input_number += (input_number%10)*10-(input_number%10)+key;
			key_100_flag = 0x00;
	     }
	     else 
	     {
	     	     	if((input_number)>6553){
				input_number = 0x0000;			
			}
        		input_number = input_number * 10 + key;
			key_100_flag = 0x00;			
	     }
#if 1
	     if (input_number > 9999)
	     {
		       input_number = 0;			
			input_number = input_number *10 + key;
	    }
#endif
        disp_port(MENU_INPUT_NUMBER);
        break;
////////////////¼��
    case MSG_REC_KEY_AT_USB:

       if(RTC_MODE == work_mode){
		break;
	}
	   
	if(RECODE_PLAY >= encode_status)
       {		
		rec_device_sel=DEVICE_UDISK;
		api_stop_encode();			
            	put_msg_lifo(MSG_REC_FIND);
	}
        else
        {
            put_msg_lifo(MSG_REC_STOP);
        }		
	break;
	
    case MSG_REC_KEY_AT_SD:

	if(RTC_MODE == work_mode){
		break;
	}
	if(RECODE_PLAY >= encode_status)
       {		
		rec_device_sel=DEVICE_SDMMC0;
       	api_stop_encode();			
            	put_msg_lifo(MSG_REC_FIND);
	}
        else
        {
            put_msg_lifo(MSG_REC_STOP);
        }	
	break;
#if 0	
    case MSG_REC_KEY:	  //¼����ʼ�ͽ���
	if(RECODE_PLAY >= encode_status)
        {
            put_msg_lifo(MSG_REC_FIND);

        }
        else
        {
            put_msg_lifo(MSG_REC_STOP);
        }
        break;
#endif
	case MSG_REC_PP:      //¼����ͣ�ͼ���¼��

        if(RECODE_WORKING == encode_status)
        {
            put_msg_lifo(MSG_REC_PAUSE);
        }
        else if(RECODE_PAUSE == encode_status)
        {

            put_msg_lifo(MSG_REC_CONTINUE);
        }
        break;

    case MSG_ENCODE_END:   //�豸дerr  �� �豸��
	//	deg_str("MSG_ENCODE_END \n");
		if(rec_device_out)		//¼��ʱ��豸�γ�,���豸�γ����ﴦ�����ڴ˲�������
		{
			rec_device_out =0;
			break;
		}

        api_stop_encode();		//ֹͣ¼��
		put_msg_lifo(MSG_REC_PLAY);
		break;

	 case MSG_ENCODE_FAT_FULL:  //���ļ�ʱ
	 //	deg_str("MSG_ENCODE_FAT_FULL \n");
		api_stop_encode();		//ֹͣ¼��
		if(REC_MIC_MODE == work_mode)		//¼��ʱд�豸�������⡢�豸��
        {
             put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
             break;   
        }
       // break_encode();
        if(AUX_MODE == work_mode)
        {
            main_menu = MENU_AUX;
        }
#if FM_MODULE 
		else if(FM_RADIO_MODE == work_mode)
        {
            main_menu = MENU_FM_MAIN;
        }
#endif
        disp_port(main_menu);
        break;
////////////////¼���漰�ĸ���״̬
    case MSG_REC_FIND:
//        if(RECODE_PLAY >= encode_status)
//        {
//            break;
//        }
#if USB_DEVICE_ENABLE
        if(USB_DEVICE_MODE == work_mode)
        {
            break;
        }
#endif
        encode_status = RECODE_INIT;
 
        if(REC_MIC_MODE != work_mode)
        {
            work_mode = REC_MIC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            given_device = rec_device_sel;//read_info(MEM_ACTIVE_DEV);
            break;
        }
#if 0		
        else //if((MUSIC_MODE != work_mode))
        {
            if (given_device == NO_DEVICE)
            {
                
                given_device = read_info(MEM_ACTIVE_DEV);

            }
        }      
        if( (( given_device & (~VIRTUAL_DEVICE ))  != DEVICE_SDMMC0) 
            && ((given_device & (~VIRTUAL_DEVICE)) != DEVICE_UDISK)
          )
        {
            given_device = DEVICE_SDMMC0;
        }
#endif	
        given_device = rec_device_sel;//read_info(MEM_ACTIVE_DEV);

        sys_clk_div(2);//SYSTEM_CLK_DIV2();

        put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
        break;
    case MSG_REC_START:		//��ʼ¼��

	rec_device_out = 0;
#if 0
		 rec_sys_set(0);  //0:24M   1:48M
		 sys_clk_div(2);//SYSTEM_CLK_DIV2();  //24 M
#else
	rec_sys_set(1);
	sys_clk_div(1);//SYSTEM_CLK_DIV1();	  //48 M
#endif
        //init_rec_name();

               
        device_active |= VIRTUAL_DEVICE;
        encode_device = device_active;	 //����¼���洢�豸

        write_file_info(0);

        set_rec_channel(encode_channel); //����¼��ͨ��  

        set_rec_vol(encode_vol);		 //����¼������

		

	if(REC_MIC_MODE == work_mode)
	{	
			kala_dac_off();
//			dac_mute_control(1,1);
#if KALAOK_FUNCTION
			dsp_set_adc_con(0);
			P3HD &=~(1<<6);
#endif
	}

        if(REC_MIC == encode_channel)
        {
            set_rec_track(TRACK_LEFT);
        }
        else
        {
            set_rec_track(TRACK_ALL);
        }
        /**/
        
        CLKGAT |= MP3CLK;// | SPIURCLK;

		
 //     CLKCON0 |= DACCLK;
 //		P3HD &=~(1<<6);
	   
        if(DEVICE_SDMMC0 == (device_active & (~VIRTUAL_DEVICE)))
        {
            CLKGAT |= USBCLK;
        }
        else if(DEVICE_UDISK == (device_active & (~VIRTUAL_DEVICE)))
        {
            CLKGAT |= SDCLK;
        }
#if ECHO_ENABLE
        if(BUSY == echo_ptr->status)
        {
            close_echo();
        }
#endif
        ///0x
        //my_memset(0x4000,0,0x787f-0x4000);
        //my_memset(0x8000,0,0x9c3f-0x8000);

//����ǿ�� 0x400c ȡֵ��Χ 0-255
//������� 0x4015 0x4014   ȡֵ��Χ 0-2048

#if ECHO_ENABLE      
        if(1 != start_encode_echo(IS_MP3))			 //��ʼ¼��
#else
        if(1 != start_encode(IS_MP3))			 //��ʼ¼��
#endif
        {
		put_msg_lifo(MSG_ENCODE_FAT_FULL);
		break;
	}
#if ECHO_ENABLE  ///<������������򿪻�����Ⱥ�ǿ��
        delay_10ms(20);
        if( REC_MIC == ( encode_channel & 0xf ) ) ///<MIC ���л���
        {
            set_echo(app_echo.strong, app_echo.deep);
        }
//        app_echo.strong = REC_ECHO_STRONG;
        echo_vol_set(REC_MIC_VOL);

#endif

        /*
        if(REC_MIC_MODE == work_mode)
        {
    		while(!((cmd_ctl_rec(REC_NO_OPT,0)) &  FRIST_ADC_PACKET)) //������ǰ�Ĵ���
    		{
    
    		}
            delay_10ms(50);//�������������
        }
		cmd_ctl_rec(ENABLE_REC_DATA,ENABLE_REC_BIT);
        */
        encode_status = RECODE_WORKING;
#if 0//FM_MODULE 
		if(FM_RADIO_MODE != work_mode)
#endif
		{
		 	main_menu = MENU_RECWORKING;//
		}
		disp_port(main_menu);
        //disp_port(MENU_REC);
        break;
    case MSG_REC_STOP:      //ֹͣ¼��
        api_stop_encode();		//ֹͣ¼��
        put_msg_lifo(MSG_REC_PLAY);
        break;
    case MSG_REC_PAUSE:     //��ͣ¼��
		encode_status = RECODE_PAUSE;
	
#if  0//FM_MODULE 
		if(FM_RADIO_MODE == work_mode)
			disp_port(MENU_FM_MAIN);
		else
#endif
		{
			main_menu = MENU_REC_PAUSE;	
		  	disp_port(MENU_REC_PAUSE);
		}
		 		
        pause_encode();
        break;
    case MSG_REC_CONTINUE:  //��ͣ¼��֮�����¼��
		encode_status = RECODE_WORKING;
	
#if FM_MODULE 
		if(FM_RADIO_MODE == work_mode)
			disp_port(MENU_FM_MAIN);
		else
#endif
		{
		 	main_menu = MENU_RECWORKING;//
		    disp_port(MENU_RECWORKING);
		}
			
        continue_encode();
        break;
    case MSG_REC_PLAY:     //��������¼���ļ�

        encode_status = RECODE_PLAY;
        given_device = encode_device & (~VIRTUAL_DEVICE);

        if( (given_device != DEVICE_SDMMC0) && (given_device != DEVICE_UDISK))
        {
            given_device = DEVICE_SDMMC0;
        }
        given_device |= VIRTUAL_DEVICE;
        if((MUSIC_MODE != work_mode))
        {
            put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        }
        else
        {
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
        }
        break;

    case MSG_MUSIC_SELECT_NEW_DEVICE:					        //����ѡ���豸

        res = find_device(given_device);

        if ((res == DEV_INIT_ERR) ||
                (res == NO_DEFINE_DEV))                    //ָ�����豸�����ߣ����ʼ��ʧ��
        {
		
            given_device = DEVICE_AUTO_NEXT;			   //�Զ�ѡ����һ���豸
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
            break;
        }
        else if ((res == NO_EFFECTIVE_DEV) ||
                 (res == NO_DEV_ONLINE))                    //�޿ɲ��ŵ��豸
        {		
            if(RECODE_STOP != encode_status)
            {
                encode_status = RECODE_STOP;
		  if(REC_MIC_MODE == work_mode)
	         {
					put_msg_lifo(MSG_NEXT_WORKMODE);
		  }
                break;
            }
            else
            {	
                put_msg_lifo(MSG_NEXT_WORKMODE);
            }
            break;
        }
        else
        {		
            if(RECODE_PLAY < encode_status)
            {
                put_msg_lifo(MSG_REC_START);
            }
            else
            {
                if(RECODE_PLAY == encode_status)  //ȥ����¼�õ��ļ�
                {
                    encode_status = RECODE_STOP;
#if VIRTUAL_ENABLE
                    given_file_number = encode_filenum;
#else
                    given_file_number = encode_filenum + encode_fristfile - 1;
#endif
                    put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
                }
                else
                {
                    put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);		//�ҵ������豸
                }
            }
            
        }
        break;



    }
}