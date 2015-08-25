/*--------------------------------------------------------------------------*/
/**@file    get_music_file.c
   @brief   �ļ����ҽӿں���
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "config.h"
#include "music_play.h"
#include "get_music_file.h"
#include "device.h"
#include "iic.h"
#include "play_file.h"
#include "key.h"

_no_init SELECT_PLAY_FILE _data playfile;
_no_init FF_APIS _xdata ff_api;
_no_init FF_APIS ff_api_tmp AT(FF_API_TEMP);                ///<��û�н���ʱʹ��

/*Path search example*/
const u8 Specific_path[] = 
{
    "/1       /B???????MP3",
};

const u8 Specific_path1[] = 
{
    "/1       /B*MP3",
};
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡһ�������
   @param   ��
   @return  ��ȡ���������
   @author: Juntham 
   @note    u16 get_u16_random()
*/
/*----------------------------------------------------------------------------*/
u16 get_u16_random(void) AT(GET_MUSIC_FILE)
{
    u16 *ptr;
    u16 res;
    
    ptr = (u16 *)0x200;
    res = *ptr++;
    res = *ptr + TMR2_CNTL;
    
    return res;
}

/*----------------------------------------------------------------------------*/
/** @brief: ��ȡ�ļ������ļ���������������û�н���ʱʹ�ã�
    @param: void
    @return:void
    @author:Juntham
    @note:  void get_dir_file_total(void) 
*/
/*----------------------------------------------------------------------------*/
#ifdef FOLDER_PLAY_EN
static void get_dir_file_total(void) AT(GET_MUSIC_FILE)
{
    if (ff_api.fs_msg.fileTotalInDir == 0)
    {
        stop_decode();
        my_memcpy((u8 *)&ff_api_tmp, (u8 *)&ff_api, sizeof(FF_APIS));
        ff_api.fs_msg.fileTotalInDir = fs_getfile_totalindir(&ff_api_tmp);
    }
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief   ��ȡ�ļ���
   @param   playmode   ѭ������ģʽ
   @param   searchMode  0����һ���ļ���1����һ���ļ���2����ǿ��REPEAT_ONEģʽ�r��REPEAT_ALLģʽ�²����ļ�
   @return  0:fail 1:success
   @author:Juntham
   @note    u8 fs_get_filenum(ENUM_PLAY_MODE playmode, ENUM_FILE_SELECT_MODE searchMode)
*/
/*----------------------------------------------------------------------------*/
u8 fs_get_filenum(ENUM_PLAY_MODE playmode, ENUM_FILE_SELECT_MODE searchMode) AT(GET_MUSIC_FILE)
{
    u16 fileTotal = music_device_info[device_active].wfileTotal;
     
    if (searchMode == PLAY_FIRST_FILE)				//���ŵ�һ���ļ�
    {
        playfile.given_file_number = 1;
        return GET_FILE_OK;
    }
    else if (searchMode == PLAY_LAST_FILE)				//�������һ���ļ�
    {
        playfile.given_file_number = fileTotal;
        return GET_FILE_OK;
    }
    else if (searchMode == PLAY_BREAK_POINT)				//���ż�����ļ���źͶϵ�
    {
#ifdef LAST_MEM_FILE_PLAY_EN
        if (find_break_point_file_flag)                 /*�����ļ���Ч*/
        {
            find_break_point_file_flag = 0;
            playfile.given_file_number = 0;
        }
        else
        {
            playfile.given_file_number = music_device_info[device_active].wBreak_point_filenum;
            if (playfile.given_file_number == 0)
                playfile.given_file_number = 1;
        }
#else
        playfile.given_file_number = 1;
#endif
        return GET_FILE_OK;
    }

    if ((playmode == REPEAT_ONE) && (searchMode != PLAY_AUTO_NEXT))
    {
        playmode = REPEAT_ALL;					//�ڵ���ѭ��ģʽ�£�ת����ȫѭ��ģʽ
    }
    switch (playmode)
    {
#ifdef RANDOM_PLAY_EN        
    case REPEAT_RANDOM:
        playfile.given_file_number = get_u16_random();
        playfile.given_file_number = (playfile.given_file_number % fileTotal) + 1;
        break;
#endif

    case REPEAT_ALL:
        if (searchMode == PLAY_PREV_FILE)					//prev file
        {
            playfile.given_file_number--;
            if (playfile.given_file_number == 0)
            {
                playfile.given_file_number=fileTotal;
            }
        }
        else					                //next file
        {
            playfile.given_file_number++;
            if (playfile.given_file_number > fileTotal)
            {
                playfile.given_file_number = 1;
               // return GET_DEVICE_END;
            }
        }
        break;
#ifdef FOLDER_PLAY_EN
    case REPEAT_FOLDER:
        {
            get_dir_file_total();   
            //deg("X-playfile.given_file_number : %04x\n", playfile.given_file_number);
            if (searchMode == PLAY_PREV_FILE)
            {
                playfile.given_file_number--;
                if (playfile.given_file_number == ff_api.fs_msg.fileTotalOutDir)
                    playfile.given_file_number = ff_api.fs_msg.fileTotalOutDir + ff_api.fs_msg.fileTotalInDir;
                //deg("2-playfile.given_file_number : %04x\n", playfile.given_file_number);   
            }
            else
            {
                playfile.given_file_number++;
                if (playfile.given_file_number > (ff_api.fs_msg.fileTotalOutDir + ff_api.fs_msg.fileTotalInDir))
                    playfile.given_file_number = ff_api.fs_msg.fileTotalOutDir + 1;
                //deg("3-playfile.given_file_number : %04x\n", playfile.given_file_number);   
            }            
        }
        break;
#endif        
    }

    return GET_FILE_OK;
}
extern bool music_disp_file_dir;
void next_prev_folder(u8 key_cmd)
{
 	music_disp_file_dir=1;

	get_dir_file_total();
       if (key_cmd == PLAY_NEXT_FILE)
       {
       	//playfile.given_file_number--;
              //if (playfile.given_file_number == ff_api.fs_msg.fileTotalOutDir)
              playfile.given_file_number = ff_api.fs_msg.fileTotalOutDir + ff_api.fs_msg.fileTotalInDir+1;
	    	if(playfile.given_file_number > music_device_info[device_active].wfileTotal)
		{
			playfile.given_file_number = 1;	
		}		
       }
       else
       {
              //playfile.given_file_number++;
              //if (playfile.given_file_number > (ff_api.fs_msg.fileTotalOutDir + ff_api.fs_msg.fileTotalInDir))
              playfile.given_file_number = ff_api.fs_msg.fileTotalOutDir;
		if (playfile.given_file_number == 0)
		{
			playfile.given_file_number =  music_device_info[device_active].wfileTotal;
		}	
		else{
			get_dir_file_total();	
			playfile.given_file_number -= (ff_api.fs_msg.fileTotalInDir - 1); 		
		}
       }
	   
#ifdef BAT_UART_DEBUG
   	my_printf(" ---> :playfile.given_file_number  	%d \r\n",(u16)playfile.given_file_number);
   	my_printf(" ---> :playfile.dirCounter	 		 %d \r\n",(u16)ff_api.fs_msg.dirCounter);
   	my_printf(" ---> :playfile.musicDirCounter	 	%d \r\n",(u16)ff_api.fs_msg.musicDirCounter);
#endif
	   
       put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);  
}

