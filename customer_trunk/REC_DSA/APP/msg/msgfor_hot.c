/*--------------------------------------------------------------------------*/
/**@file    msgfor_hot.c
   @brief   HOT 消息处理模块
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
extern void disk_remove_deal_for_music(void);

extern u8 work_mode;
extern u8 _idata last_work_mode;
extern bool input_number_en;
extern bool eq_change_en;
extern bool play_mode_change_en;
extern bool fisrt_init_dev;

extern u8 given_device;
extern u16 given_file_number;
extern u8 given_file_method;
extern u8 eq_mode;
extern u8 play_mode;
extern u8  main_menu, cur_menu, main_menu_conter;
extern u8 device_active;
u16 input_number;	 ///<输入的数字的实际值
bool vol_change_en;	 ///<音量修改允许位
extern u8 device_online;
extern u8 music_type;
bool rec_device_out;
bool rec_device_full=0;
u8 rec_source=0;
extern void stop_decode(void);

#ifdef AC_SLAVE_ENABLE
extern void DSA_init(void);
extern void DSA_if_hdlr(void);
extern bool DSA_GETHERING_DATA_ENABLE_BIT;
extern xd_u8 DSA_SEL_DEV;
extern bool disk_toc_ok;
#endif


/*----------------------------------------------------------------------------*/
/**@brief   几个任务都会用到的消息集中处理的函数
   @param   key： 需要处理的消息
   @return  0：需要切换工作模式;
   @note    unsigned char I2C_sendbyte(unsigned char I2Cdata)
*/
/*----------------------------------------------------------------------------*/
void ap_handle_hotkey(u8 key)
{
    u8 res;
	
#ifdef AC_SLAVE_ENABLE
	if(DSA_GETHERING_DATA_ENABLE_BIT){
		DSA_GETHERING_DATA_ENABLE_BIT =0;
		DSA_if_hdlr();
	}
#endif

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

    case MSG_USB_DISK_OUT:
    case MSG_SDMMC_OUT:
        //deg_str("device out \n");        
	 device_check();
	 sys_printf(" DEVICE  UNPLUGGED ");

        if( (!device_check() ) && (encode_status >= RECODE_INIT )) //在录音时，活动设备拔出
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

    case MSG_SDMMC_IN_SEL:
        fisrt_init_dev=1;
	 disk_toc_ok=0;		
	 DSA_SEL_DEV=DEVICE_SDMMC0;	
    case MSG_SDMMC_IN :
	 device_check();
	 if(DSA_SEL_DEV==DEVICE_SDMMC0)
	 {
		 sys_printf(" SELCET DEVICE_SDMMC0 ");
		 usb_suspend();
	        stop_decode();
	        break_encode();
#ifdef AC_SLAVE_ENABLE
		 DSA_init();
#endif	
		 given_device = DEVICE_SDMMC0;
	        given_file_method = PLAY_FIRST_FILE;
	        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
	 }
        break;
    case MSG_USB_DISK_IN_SEL:
        fisrt_init_dev=1;
	 disk_toc_ok=0;				
	 DSA_SEL_DEV=DEVICE_UDISK;	
    case MSG_USB_DISK_IN  :
	 device_check();
	 if(DSA_SEL_DEV==DEVICE_UDISK)
	 {
	     	sys_printf(" SELCET DEVICE_UDISK ");

        	break_encode();
       	stop_decode();
#ifdef AC_SLAVE_ENABLE
		 DSA_init();
#endif	
	    	given_device = DEVICE_UDISK;
	       given_file_method = PLAY_FIRST_FILE;      
	       put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
	 }
        break;

    case MSG_NEXT_WORKMODE:
        break_encode();
        work_mode++;
        if (work_mode > MAX_WORK_MODE)
            work_mode = MUSIC_MODE;
        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        break;

    case MSG_VOL_UP:
        if (vol_change_en==0)
            break;
        dac_mute_control(0,1);					//调节音量时，自动UNMUTE
        write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_INC));
        disp_port(MENU_MAIN_VOL);
        break;

    case MSG_VOL_DOWN:
        if (vol_change_en==0)
            break;
        dac_mute_control(0,1);					//调节音量时，自动UNMUTE
        write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_DEC));
        disp_port(MENU_MAIN_VOL);
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

        if (input_number > 999)
            input_number = 0;

        input_number = input_number * 10 + key;
        disp_port(MENU_INPUT_NUMBER);
        break;
////////////////录音
    case MSG_REC_MIC:
	rec_source=REC_SOUR_MIC;
       break_encode();
       stop_decode();	
       put_msg_lifo(MSG_REC_FIND);	   
	break;
    case MSG_REC_AUX1:
	rec_source=REC_SOUR_AUX1;
       break_encode();
       stop_decode();		
       put_msg_lifo(MSG_REC_FIND);	   
	break;	
    case MSG_REC_AUX2:
	rec_source=REC_SOUR_AUX2;
       break_encode();
       stop_decode();		
       put_msg_lifo(MSG_REC_FIND);	   
	break;

    case MSG_REC_KEY:	  //录音开始和结束
        if(RECODE_PLAY >= encode_status)
        {
            put_msg_lifo(MSG_REC_FIND);
        }
        else
        {
            put_msg_lifo(MSG_REC_STOP);
        }
        break;

	case MSG_REC_PP:      //录音暂停和继续录音

        if(RECODE_WORKING == encode_status)
        {
            put_msg_lifo(MSG_REC_PAUSE);
        }
        else if(RECODE_PAUSE == encode_status)
        {

            put_msg_lifo(MSG_REC_CONTINUE);
        }
        break;

    case MSG_ENCODE_END:   //设备写err  或 设备满

	if(rec_device_out)		//录音时活动设备拔出,在设备拔出那里处理，在此不做处理
	{
		rec_device_out =0;
		break;
	}

       api_stop_encode();		//停止录音
	put_msg_lifo(MSG_REC_PLAY);
	break;

	 case MSG_ENCODE_FAT_FULL:  //建文件时

	 rec_device_full=1;	 
        api_stop_encode();		//停止录音
	 if(REC_MIC_MODE == work_mode)		//录音时写设备出现问题、设备满
        {
             put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
             break;   
        }
	 
        break;
////////////////录音涉及的各种状态
    case MSG_REC_FIND:

        encode_status = RECODE_INIT;

 	rec_device_full=0;	 

        if(rec_source==REC_SOUR_MIC)
        {
            if(work_mode!= REC_MIC_MODE){
	            work_mode = REC_MIC_MODE;
	            put_msg_lifo(MSG_CHANGE_WORK_MODE);
	            break;
            	}
        }
        else if(rec_source==REC_SOUR_AUX1)
        {
            if(work_mode!= AUX_MODE){
	            work_mode = AUX_MODE;
       	     put_msg_lifo(MSG_CHANGE_WORK_MODE);
            	     break;
            }
        }
        else if(rec_source==REC_SOUR_AUX2)
        {
            if(work_mode!= FM_RADIO_MODE){
	            work_mode = FM_RADIO_MODE;
       	     put_msg_lifo(MSG_CHANGE_WORK_MODE);
            	     break;
            	}
        }
		
	 if(DSA_SEL_DEV == DEVICE_SDMMC0)
        {
            	given_device = DEVICE_SDMMC0;
        }
	 else{
            	given_device = DEVICE_UDISK;
	 }
	 
        sys_clk_div(2);
        put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
        break;
    case MSG_REC_START:		//开始录音

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
        encode_device = device_active;	 //设置录音存储设备

        write_file_info(0);

        set_rec_channel(encode_channel); //设置录音通道  

        set_rec_vol(encode_vol);		 //设置录音音量


	if(REC_MIC_MODE == work_mode)
	{	
		kala_dac_off();
//		dac_mute_control(1,1);
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

//混响强度 0x400c 取值范围 0-255
//混响深度 0x4015 0x4014   取值范围 0-2048

#if ECHO_ENABLE      
        if(1 != start_encode_echo(IS_MP3))			 //开始录音
#else
        if(1 != start_encode(IS_MP3))			 //开始录音
#endif
        {
		put_msg_lifo(MSG_ENCODE_FAT_FULL);
		break;
	}
#if ECHO_ENABLE  ///<减弱冲击声，打开混响深度和强度
        delay_10ms(20);
        if( REC_MIC == ( encode_channel & 0xf ) ) ///<MIC 下有混响
        {
            set_echo(app_echo.strong, app_echo.deep);
        }
//        app_echo.strong = REC_ECHO_STRONG;
        echo_vol_set(REC_MIC_VOL);

#endif

         rec_device_full=0;	 

        encode_status = RECODE_WORKING;
        break;

    case MSG_REC_STOP:      //停止录音
        api_stop_encode();		//停止录音
        put_msg_lifo(MSG_REC_PLAY);
        break;
    case MSG_REC_PAUSE:     //暂停录音
	encode_status = RECODE_PAUSE;		 		
        pause_encode();
        break;
    case MSG_REC_CONTINUE:  //暂停录音之后继续录音
	 encode_status = RECODE_WORKING;			
        continue_encode();
        break;
    case MSG_REC_PLAY:     //播放最后的录音文件

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

    case MSG_MUSIC_SELECT_NEW_DEVICE:					        //重新选择设备

        res = find_device(given_device);

        if ((res == DEV_INIT_ERR) ||
                (res == NO_DEFINE_DEV))                    //指定的设备不在线，或初始化失败
        {
		
            //given_device = DEVICE_AUTO_NEXT;			   //自动选择下一个设备
            //put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
            break;
        }
        else if ((res == NO_EFFECTIVE_DEV) ||
                 (res == NO_DEV_ONLINE))                    //无可播放的设备
        {		
            if(RECODE_STOP != encode_status)
            {
                encode_status = RECODE_STOP;
		  if(REC_MIC_MODE == work_mode)
		  {
		  	work_mode =IDLE_MODE;
			put_msg_lifo(MSG_CHANGE_WORK_MODE);
		  }
                break;
            }
            else
            {	
		  	work_mode =IDLE_MODE;
			put_msg_lifo(MSG_CHANGE_WORK_MODE);
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
                if(RECODE_PLAY == encode_status)  //去播刚录好的文件
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
                    put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);		//找到可用设备
                }
            }
            
        }
        break;



    }
}
