/*--------------------------------------------------------------------------*/
/**@file   music.h
   @brief  music头文件
   @details
   @author
   @date   2011-5-18
   @note
*/
/*----------------------------------------------------------------------------*/
#include "music.h"
#include "msgfor_hot.h"
#include "device.h"
#include "dsp.h"
#include "id3.h"
#include "eq.h"
#include "get_music_file.h"
#include "main.h"
#include "dac.h"
#include "rtc_api.h"
#include "led_ind_drv.h"

extern bool input_number_en;
extern u8  main_menu, cur_menu, main_menu_conter;
extern u16 input_number;
extern u8 device_active;

extern _xdata SYS_WORK_MODE   work_mode;
extern u8 bright_counter;
extern bool vol_change_en;
extern bool key_voice_en;
extern u8 _idata last_work_mode;
u8 play_mode;							 ///<循环模式
u8 given_device;						 ///<需要查找的设备
u16 given_file_number;					 ///<需要查找的文件号
u16 break_point_filenum;				 ///<断点信息对应的文件号
u8 play_status;							///<播放状态
u8 play_delay_time;
extern xd_u8 DSA_SEL_DEV;

xd_u8 dev_remov_timer=0;
xd_u8 disk_toc_ok=0,dev_invalid=0,dev_init_read=0;
bool send_init_device_cmd_delay=0;
u8 eq_mode;				  ///<EQ模式
u8 music_type;			  ///<音乐文件的格式
u8 given_file_method;	  ///<获取文件的方式
u8 _pdata music_spec[9] _at_ 0x02;	 ///<频谱BUFF

u8 _xdata decode_buffer[1024*2] _at_ 0x2880;	 ///<解码BUFF
u8 _xdata win_buffer[512] _at_ 0x4C0;            ///<文件系统缓存BUFF
FSAPIMSG _pdata fs_msg _at_ 0x40;				 ///<文件系统相关消息
FSINFO _xdata fs_info _at_ 0x25e;
DECODER_MSG _xdata *dec_msg;					 ///<解码相关的消息
FIL xdata fat_ptr1;								 ///<文件在文件系统中的相关消息
bool find_break_point_file_flag;			///<是否找到可以断点续播的文件

DISK_MUSIC_POINT _idata	disk_mus_point[2];	   ///<音乐文件断点记忆的变量

extern u8 ldoin_voltage(void);
extern u8 _xdata adc_vdd12;
extern u8 _xdata adc_vddio;

extern u16 _idata adkey_value1;
extern u16 _idata user_code;
extern u8 _pdata music_spec[9];
extern u8 _bdata device_online;

#ifdef AC_SLAVE_ENABLE
extern void DSA_init(void);
extern void DSA_clr_ID3_info();
#endif

/*----------------------------------------------------------------------------*/
/**@brief MUSIC解码初始化
   @param 无
   @return  无
   @note void decode_init(void)
*/
/*----------------------------------------------------------------------------*/
static void decode_init(void)
{
    file_io_init();
    dec_msg->buffer = decode_buffer;
    dec_msg->buffer_len = 2048;
}
/*----------------------------------------------------------------------------*/
/**@brief MUSIC模式信息初始化
   @param 无
   @return  无
   @note void music_info_init(void)
*/
/*----------------------------------------------------------------------------*/
void music_info_init(void)
{
#ifdef NO_REM_LAST_DEV
	given_device = NO_DEVICE;
#else
     given_device = read_info(MEM_ACTIVE_DEV);
#endif

    if (given_device == DEVICE_SDMMC0)
    {
	 Set_Curr_Func(SYS_MP3DECODE_SD);
        given_file_method = PLAY_BREAK_POINT;
        given_device = DEVICE_SDMMC0;
        //put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
    }
    else if (given_device == DEVICE_UDISK)
    {
    	 Set_Curr_Func(SYS_MP3DECODE_USB);
        given_file_method = PLAY_BREAK_POINT;
        given_device = DEVICE_UDISK;
        //put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
    }
    else
    {
    	 Set_Curr_Func(SYS_MP3DECODE_USB);
        given_file_method = PLAY_BREAK_POINT;
        given_device = DEVICE_UDISK;
        //put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
    }

    send_init_device_cmd_delay=1;
}

/*----------------------------------------------------------------------------*/
/**@brief MUSIC断点信息写入rtcram中
   @param 无
   @return  无
   @note void backup_mp_by_rtcram(void)
*/
/*----------------------------------------------------------------------------*/
void backup_music_point_to_rtcram(void)
{
    u8 i;
    if (DEVICE_SDMMC0 == device_active)
    {
        for (i = 2;i<10;i++)
        {
            write_rtc_ram(MEM_SD_PLAYPOINT_ID0+i,((u8 *)(&(disk_mus_point[0].id0)))[i]);
        }
    }
    if (DEVICE_UDISK == device_active)
    {
        for (i = 2;i<10;i++)
        {
            write_rtc_ram(MEM_USB_PLAYPOINT_ID0+i,((u8 *)(&(disk_mus_point[1].id0)))[i]);
        }
    }


}
/*----------------------------------------------------------------------------*/
/**@brief MUSIC断点信息写入EEPR0M中
   @param 无
   @return  无
   @note void backup_mp_by_eeprom(void)
*/
/*----------------------------------------------------------------------------*/
void backup_music_point_to_eeprom(void)
{
    u8 cnt,i;
    eeprom_page_write_start();
    if (device_active == DEVICE_SDMMC0)
    {
        cnt = 0;
        iic_sendbyte(MEM_SD_PLAYPOINT_ID1);
    }
    else if (device_active == DEVICE_UDISK)
    {
        cnt = 1;
        iic_sendbyte(MEM_USB_PLAYPOINT_ID1);
    }
    for ( i = 0;i<8;i++)
    {
        iic_sendbyte(((u8 *)(&(disk_mus_point[cnt].id1)))[i]);
    }
    eeprom_page_write_stop();
}
/*----------------------------------------------------------------------------*/
/**@brief MUSIC断点信息写入EEPROM中
   @param 无
   @return  无
   @note void backup_music_point(void)
*/
/*----------------------------------------------------------------------------*/

void backup_music_point(void)
{
    if ((play_status != MAD_PLAY) && (play_status != MAD_PAUSE))				//当前没有处于播放或暂停状态,不保存断点
    {
        return;
    }
    if (device_active == DEVICE_SDMMC0)
    {
        disk_mus_point[0].id1 = dec_msg->id1;
        disk_mus_point[0].id2 = dec_msg->id2;
    }
    else if (device_active == DEVICE_UDISK)
    {
        disk_mus_point[1].id1 = dec_msg->id1;
        disk_mus_point[1].id2 = dec_msg->id2;
    }
#if USE_RTC_RAM
    backup_music_point_to_rtcram();
#else
    backup_music_point_to_eeprom();
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief 保存MUSIC断点信息
   @param 无
   @return  无
   @note void save_music_point(void)
*/
/*----------------------------------------------------------------------------
void save_music_point(void)
{
    if ((play_status != MAD_PLAY) && (play_status != MAD_PAUSE))				//当前没有处于播放或暂停状态,不保存断点
    {
        return;
    }

}*/
/*----------------------------------------------------------------------------*/
/**@brief 加载MUSIC断点信息
   @param 无
   @return  0：不存在有效地断点；1：存在有效地断点
   @note static bool load_music_point(void)
*/
/*----------------------------------------------------------------------------*/
static bool load_music_point(void)
{
    if (device_active == DEVICE_SDMMC0)
    {

        if (!disk_mus_point[0].id1)
        {
            return 0;
        }
        dec_msg->id1 = disk_mus_point[0].id1;
        dec_msg->id2 = disk_mus_point[0].id2;
    }
    else if (device_active == DEVICE_UDISK)
    {

        if (!disk_mus_point[1].id1)
        {
            return 0;
        }
        dec_msg->id1 = disk_mus_point[1].id1;
        dec_msg->id2 = disk_mus_point[1].id2;
    }
    return 1;
}
/*----------------------------------------------------------------------------*/
/**@brief 从EEPROM中读出断点信息，并初始化解码变量
   @param 无
   @return  无
   @note void music_info_init(void)
*/
/*----------------------------------------------------------------------------*/
void restore_music_point(void)
{
    u8 i;
    for (i = 0;i<10;i++)
    {
        ((u8 *)(&(disk_mus_point[0].id0)))[i] = read_info(MEM_SD_PLAYPOINT_ID0+i);
    }
    for (i = 0;i<10;i++)
    {
        ((u8 *)(&(disk_mus_point[1].id0)))[i] = read_info(MEM_USB_PLAYPOINT_ID0+i);
    }

}

/*----------------------------------------------------------------------------*/
/**@brief   停止解码
   @param   无
   @return  无
   @note   stop_decode
*/
/*----------------------------------------------------------------------------*/
void stop_decode(void)
{

    play_status = MAD_STOP;

//set_play_flash(LED_FLASH_ON);

#if (1 == MUSIC_FADE_OUT_EN)
    main_vol_set(0, CHANGE_VOL_NO_MEM | CHANGE_VOL_PEND);
#endif
    mad_control(MAD_STOP, 0);
    decode_init();									//解码初始化，会将解码的变量及状态清零
}

void cipher_judge(void)
{
    if((fs_msg.fname[8]== 'S') &&(fs_msg.fname[9]== 'M') && (fs_msg.fname[10]== 'P'))
    {
        cipher_ctl(1);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  开始解码
   @param  无
   @return 无
   @note   start_decode
*/
/*----------------------------------------------------------------------------*/
static u8 start_decode(void)
{
    cipher_judge();

    mad_control(MAD_STOP, 0);
    decode_init();									//解码初始化，会将解码的变量及状态清零
    music_type = music_format_check(decode_buffer);	//检查文件格式

    if (music_type == NOT_SUPPORT)					//不支持的格式
    {
        return 1;
    }
    else if (music_type == IS_MP3)					//MP3
    {

        get_music_tag();
        if (!get_mp3_total_time())
            return 1;
    }
    else
        get_music_tag();

    if (dec_msg->total_time == 0)					//总播放时间为0，则不进行播放，如果遇到因为添加了此判断而不能播放的文件，则可去掉此条件
    {
        return 1;
    }
	
#ifdef WMA_FORMAT_NOT_SUPPORT
    if (music_type == IS_WMA){
        return 1;
    }
#endif

    set_eq(eq_mode);

#if (BREAK_POINT_PLAY_EN == 1)
    if (find_break_point_file_flag) 								//取保存过的断点信息
    {
        find_break_point_file_flag = load_music_point();
    }
#endif
	dsp_set_dcc_flt(14);
    dsp_set_ch_mode(0);
    dsp_set_rinv_mode(0);
    mad_control(MAD_INIT, 0);
    mad_control(MAD_PLAY, 0);
    play_status = MAD_PLAY;
	
    if (device_active == DEVICE_SDMMC0)
    {
	 Set_Curr_Func(SYS_MP3DECODE_SD);
    }
    else if (device_active == DEVICE_UDISK)
    {

	 Set_Curr_Func(SYS_MP3DECODE_USB);
    }	

	dev_init_read=0;
	disk_toc_ok=1;
	DSA_clr_ID3_info();
 // set_play_flash(LED_FLASH_NOR);
    return 0;
}
/*----------------------------------------------------------------------------*/
/**@brief  设备拔出时MUSIC任务的处理
   @param  无
   @return 无
   @note   void disk_remove_deal_for_music(void)
*/
/*----------------------------------------------------------------------------*/
void disk_remove_deal_for_music(void)
{

   // if ((device_check() == 0))//当前播放设备已经不在线,则自动选取下一个设备
    {

#if 1
    	 //Set_Curr_Func(SYS_IDLE);
       // put_msg_lifo(MSG_CHANGE_WORK_MODE);      
#else	            
        given_device = DEVICE_AUTO_NEXT;

        given_file_method = PLAY_BREAK_POINT;
        put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
#endif		

	   sys_printf(" ------------------------------------->  disk_remove_deal_for_music ");

        if ( (play_status == MAD_PAUSE) || (play_status == MAD_PLAY) )
            backup_music_point();								//记录断点信息
    }

}

/*----------------------------------------------------------------------------*/
/**@brief  MUSIC模式主循环
   @param  无
   @return 无
   @note   void music_play(void)
*/
/*----------------------------------------------------------------------------*/
void music_play(void)
{
    u8 key;
    u8 res;
	
    while (1)
    {
#if (FF_FR_MUSIC == 0)
        if (play_status == MAD_PLAY)
        {
            dac_out_select(DAC_MUSIC, 0);
        }
#else
        if ((play_status == MAD_PLAY) || (play_status == MAD_FF) || (play_status == MAD_FR))
        {
            dac_out_select(DAC_MUSIC, 0);
        }
#endif
        //suspend_sdmmc();						//可减少SDMMC功耗，但会增加电源波动
        key = app_get_msg();

        switch (key)
        {
        case MSG_CHANGE_WORK_MODE:
            //backup_music_point();
           break;
           // return;

        case MSG_DEVICE_REMOVED:
        	device_check();
        	disk_remove_deal_for_music();
		stop_decode();
	 	dev_remov_timer=8;
		
            break;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
     	     dev_init_read=1;	
	     send_init_device_cmd_delay=1;
	     backup_music_point();
	     break;
        case MSG_MUSIC_SELECT_NEW_DEVICE:					        //重新选择设备
            res = find_device(given_device);

            if ((res == DEV_INIT_ERR) ||
                    (res == NO_DEFINE_DEV))                    //指定的设备不在线，或初始化失败
            {
			disk_toc_ok=0;
			dev_invalid=1;
			dev_init_read=0;	
		    //Set_Curr_Func(SYS_IDLE);
       	    //put_msg_lifo(MSG_CHANGE_WORK_MODE);      
	            break;
				
                //given_device = DEVICE_AUTO_NEXT;			   //自动选择下一个设备
                //put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
                //break;
            }
            else if ((res == NO_EFFECTIVE_DEV) ||
                     (res == NO_DEV_ONLINE))                    //无可播放的设备
            {
#if defined(NO_DEV_DEFAULT_GO_TO_AUX)
		 //Set_Curr_Func(SYS_AUX);
#elif defined(NO_DEV_DEFAULT_GO_TO_IDLE)
		// Set_Curr_Func(SYS_IDLE);
        	 //put_msg_fifo(MSG_NO_DEVICE);	 
#else
		 //Set_Curr_Func(SYS_FMREV);
#endif

			disk_toc_ok=0;
			dev_invalid=1;
			dev_init_read=0;	

		 //Set_Curr_Func(SYS_IDLE);
       	 //put_msg_lifo(MSG_CHANGE_WORK_MODE);      
	        break;

            }
            else
                put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);		//找到可用设备

            break;

        case MSG_MUSIC_SELECT_NEW_FILE:


            if (device_check() == 0)                                //当前播放设备已经不在线,则自动选取下一个设备
            {
#if 1
			disk_toc_ok=0;
	    	 //Set_Curr_Func(SYS_IDLE);
	        //put_msg_lifo(MSG_CHANGE_WORK_MODE);      
#else            
                given_device = DEVICE_AUTO_NEXT;
                put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
#endif				
                break;
            }

            res = fs_get_filenum(play_mode, given_file_method);

#if 0
            if (res == GET_DEVICE_END)								//下一曲到设备的结束，查找下一个设备的第一首
            {
                given_file_method = PLAY_FIRST_FILE;
                given_device = DEVICE_AUTO_NEXT;
                put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
                break;
            }
            else if (res == GET_DEVICE_HEAD)								//上一曲到设备的结束，查找下一个设备的最后一首
            {
                given_file_method = PLAY_LAST_FILE;
                given_device = DEVICE_AUTO_PREV;
                put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
                break;
            }
#endif
            put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
            break;

        case MSG_MUSIC_PLAY_NEW_FILE:									//按文件序号选择文件进行播放

            flush_all_msg();
            stop_decode();
            cipher_ctl(0);
            res = fs_getfile_bynumber(0, &fat_ptr1, given_file_number);
            disp_port(MENU_FILENUM);

            if (res == 0)
            {
                if (given_file_method == PLAY_BREAK_POINT)
                    res = start_decode();
                else
                    res = start_decode();
            }

            if (res != 0)                                       //播放不成功
            {
                play_status = MAD_STOP_WAIT;
                play_delay_time = 0;
                if (given_file_method <= PLAY_BREAK_POINT) 		//重新找下一首
                {
                    given_file_method = PLAY_NEXT_FILE;
                    break;
                }
                else											//重新找上一首
                {
                    given_file_method = PLAY_PREV_FILE;
                    break;
                }
            }
            main_menu = MENU_MUSIC_MAIN;
            write_file_info();

            break;

        case MSG_DECODE_FILE_END:


            if ((dec_msg->play_time >= 5) || (play_status == MAD_FF) || (play_status == MAD_FR))     //当前歌曲的播放时间大于5S时，直接播放下一首
            {         
                given_file_method = PLAY_AUTO_NEXT;
                put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
            }
            else													//当前歌曲播放时间小于5S，有可能是不坏歌曲，等待一段时间
            {
                play_delay_time = 0;
                given_file_method = PLAY_AUTO_NEXT;
                play_status = MAD_STOP_WAIT;
            }
           if (play_mode == REPEAT_OFF){
           
		    if(given_file_number ==  fs_msg.fileTotal){
	            	flush_all_msg();			
			stop_decode();			
	    	    }   
    	    }   
            break;

        case MSG_MUSIC_PREV_FILE:												//选择上一个文件进行播放

            given_file_method = PLAY_PREV_FILE;
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
            break;

        case MSG_MUSIC_NEXT_FILE:												//选择下一个文件进行播放

            //delay_10ms(30);
            given_file_method = PLAY_NEXT_FILE;
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
            break;
#if defined(DECODE_STOP_MODE_ENABLE	)
	case MSG_MUSIC_STOP:

		if(play_status !=MAD_STOP){
            		flush_all_msg();
			stop_decode();
		}
		break;
#endif		
        case MSG_MUSIC_PP:											//暂停和播放
            if (cur_menu == MENU_INPUT_NUMBER)			            //数字输入模式
            {
                put_msg_lifo(MSG_PICH_SONG);
                break;
            }
			
#if defined(DECODE_STOP_MODE_ENABLE	)			
	    if(play_status ==MAD_STOP){
#if 1
           		given_file_method = PLAY_FIRST_FILE;
            		put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
			break;
#else
                    res = start_decode();
	//   	      set_play_flash(LED_FLASH_NOR);					
			play_status = MAD_PLAY;
			break;
#endif			
	    }
#endif
            if (play_status == MAD_PLAY)
            {
                disp_port(MENU_PAUSE);
                main_menu = MENU_PAUSE;
                mad_control(MAD_PAUSE, 0);
                play_status = MAD_PAUSE;
 // 		  set_play_flash(LED_FLASH_ON);

            }
            else if (play_status == MAD_PAUSE)
            {
                main_menu = MENU_MUSIC_MAIN;
                disp_port(MENU_MUSIC_MAIN);
                mad_control(MAD_PLAY, 0);
                play_status = MAD_PLAY;
 // 		  set_play_flash(LED_FLASH_NOR);				
            }

            flush_all_msg();
            break;

        case MSG_MUSIC_NEXT_EQ:
            if (play_status == MAD_PAUSE)
                break;
            eq_mode++;
            if (eq_mode > CLASSIC)
            {
                eq_mode = NORMAL;
            }
            set_eq(eq_mode);
            disp_port(MENU_SET_EQ);
            break;
			
        case MSG_MUSIC_REP_OFF:
            if (play_status == MAD_PAUSE)
                break;
             play_mode = REPEAT_OFF;
			
            break;

        case MSG_MUSIC_REP_ONE:
            if (play_status == MAD_PAUSE)
                break;

             play_mode = REPEAT_ONE;
			
            break;

        case MSG_MUSIC_REP_ALL:
            if (play_status == MAD_PAUSE)
                break;

             play_mode = REPEAT_ALL;
			
            break;
			
        case MSG_NEXT_PLAYMODE:
            if (play_status == MAD_PAUSE)
                break;
			
            play_mode++;
            if (play_mode > REPEAT_OFF)
            {
                play_mode = REPEAT_ALL;
            }
            disp_port(MENU_SET_PLAY_MODE);
            break;

        //case MSG_MUTE:												//静音
        //    break;

#if (FF_FR_EN == 1)
        case MSG_MUSIC_FR:											//启动快退
            if (find_break_point_file_flag)							//如果是记忆播放的歌曲，不能快退
            {

                break;
            }
            if (play_status == MAD_PLAY)
            {
                play_status = MAD_FR;
            }

            break;

        case MSG_MUSIC_FF:											//启动快进
            if (play_status == MAD_PLAY)
            {
                play_status = MAD_FF;
            }
            break;

		case MSG_KEY_CHANGE:
        case MSG_MUSIC_FFR_DONE:									//快进快退结束，恢复播放
            if (play_status == MAD_FR)
            {
                set_eq(eq_mode);
                flush_all_msg();
#if (FF_FR_MUSIC == 0)

                dac_mute_control(0);
#endif
                play_status = MAD_PLAY;
            }
            else if (play_status == MAD_FF)
            {
                set_eq(eq_mode);
                flush_all_msg();
#if (FF_FR_MUSIC == 0)

                dac_mute_control(0);
#endif
                play_status = MAD_PLAY;
            }

            break;
#endif
        case MSG_PICH_SONG:
            if (cur_menu == MENU_INPUT_NUMBER)			           //数字输入模式
            {
                if ((input_number <= fs_msg.fileTotal) && (input_number != 0))			   //输入数字是否有效
                {
                    given_file_number = input_number;
                    given_file_method = PLAY_FIRST_FILE;
                    given_device = DEVICE_AUTO_NEXT;
                    put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
                }
                else
                    disp_port(main_menu);
            }

            break;

#if (MUSIC_SPECTRUM_EN == 1)
        case MSG_100MS:
            if (cur_menu == MENU_MUSIC_MAIN)
            {
                music_spec_cul(1);
                disp_port(MENU_100MS_REFRESH);
            }
            break;
#endif

        case MSG_200MS:
////////////////////////////////////////////////////////////
//快进快退实际的操作在这里完成
#if (FF_FR_EN == 1)
            if (play_status == MAD_FF)
            {
#if (FF_FR_MUSIC == 0)							//如果需要在快进快退过程中听到声音，可以不加此行
                dac_mute_control(1);
#endif
                mad_control(MAD_FF, FF_FR_STEP);
                mad_control(MAD_FAST_FORWARD, 0);
#if (FF_FR_MUSIC == 1)

                dac_mute_control(0,1);
#endif
                mad_control(MAD_PLAY, 0);
            }
            else if (play_status == MAD_FR)
            {
#if (FF_FR_MUSIC == 0)
                dac_mute_control(1);							//如果需要在快进快退过程中听到声音，可以不加此行
#endif
                mad_control(MAD_FR, FF_FR_STEP);
                mad_control(MAD_FAST_REVERASE, 0);
#if (FF_FR_MUSIC == 1)
                dac_mute_control(0,1);
#endif
                mad_control(MAD_PLAY, 0);
            }
            disp_port(MENU_HALF_SEC_REFRESH);
#endif
#if (DISP_DOT_LCD == 1)
            disp_port(MENU_200MS_REFRESH);								//播放时的滚动显示
#endif
            break;

        case MSG_HALF_SECOND:
		if(send_init_device_cmd_delay){
	        	put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
			send_init_device_cmd_delay=0;
		}
/////////////////////////////////////////////////////////////
//短歌曲或损坏的歌曲在这里跳到下一首
            if (play_status == MAD_STOP_WAIT)				//等待一段时间再自动选择下一首
            {
                if (play_delay_time < 4)
                    play_delay_time++;
                else
                {
                    put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);
                }
            }

		//printf(" --->MSG_HALF_SECOND play time  %u : %u   \r\n",(u16)(dec_msg->play_time/60),(u16)(dec_msg->play_time%60));

		if(dev_remov_timer>0){

			dev_remov_timer--;
			if(dev_remov_timer==0){
			    	 Set_Curr_Func(SYS_IDLE);
			        put_msg_lifo(MSG_CHANGE_WORK_MODE);      
			}
		}
////////////////////////////////////////////////////////////
//显示界面的切换
            if (main_menu_conter < SUB_MENU_TIME)
            {
                main_menu_conter++;
            }
            else if (cur_menu != main_menu)
            {
                if (cur_menu == MENU_INPUT_NUMBER)			//数字输入模式
                {
                    put_msg_lifo(MSG_PICH_SONG);
                    break;
                }
                else
                {
                    cur_menu = main_menu;
                }
                disp_port(cur_menu);
            }
/////////////////////////////////////////////////////////////
//调整显示亮度
            set_brightness_fade_out();
/////////////////////////////////////////////////////////////
//更新实时界面
            disp_port(MENU_HALF_SEC_REFRESH);
            break;
        case MSG_NEXT_FOLDER:
	     select_folder_file(FIND_NEXT_DIR);		
            break;
        case MSG_PREV_FOLDER:
	     select_folder_file(FIND_PREV_DIR);		
            break;
#if 0//RTC_ENABLE
        case MSG_ALM_ON:
            write_next_alm_sec();
            Set_Curr_Func(SYS_RTC);
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
#endif
        default :
            ap_handle_hotkey(key);
            break;
        }
    }
}


/*----------------------------------------------------------------------------*/
/**@brief   播放解码模式入口
   @param   无
   @return  无
   @note    void music_decode(void)
*/
/*----------------------------------------------------------------------------*/
void music_decode(void)
{

   sys_printf(" ------------------------------------>music_decode ");

#ifdef AC_SLAVE_ENABLE
	DSA_init();
#endif	

     dev_remov_timer=0;
     play_mode = REPEAT_OFF;
     disk_toc_ok=0;
     dev_invalid=0;
	 
     if(get_device_online_status()>0){
     		dev_init_read=1;	
     }
     else{
     		dev_init_read=0;	
    }	
    input_number_en = 1;									//允许数字输入功能
    vol_change_en=1;
    key_voice_en=1;
    main_menu = MENU_MUSIC_MAIN;
    dec_msg = get_dec_msg_ptr();
    fat_ptr1.buf = win_buffer;
    SYSTEM_CLK_DIV1();
    //sd_speed_init(0, 100);
    key_table_sel(0);
    flush_all_msg();
    music_info_init();
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
    
    if(DSA_SEL_DEV==DEVICE_SDMMC0){
		
        given_device = DEVICE_SDMMC0;

    }
    else if(DSA_SEL_DEV==DEVICE_UDISK){
        given_device = DEVICE_UDISK;
   }
    //put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
    
    music_play();
    //delay_10ms(3);
    stop_decode();
    usb_suspend();				//Entered Suspend Mode
    key_voice_en=0;
    main_vol_set(0, CHANGE_VOL_NO_MEM);
    given_device = NO_DEVICE;
}
