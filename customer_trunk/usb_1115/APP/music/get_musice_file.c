/*--------------------------------------------------------------------------*/
/**@file       get_music_file.c
   @brief      文件查找
   @details
   @author
   @date   2010-9-8
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"

#include "get_music_file.h"
#include "device.h"


extern u16 given_file_number;
extern u16 break_point_filenum;
extern u8 given_device;
extern u8 play_mode;
extern FSAPIMSG _pdata fs_msg;
extern u8 device_active;
extern bool find_break_point_file_flag;

extern FIL xdata fat_ptr1;
extern void stop_decode(void);

/*----------------------------------------------------------------------------*/
/**@brief   获取一个随机数
   @param   无
   @return  获取到的随机数
   @note    u8 ReadLFSR()
*/
/*----------------------------------------------------------------------------*/

u16 ReadLFSR()
{
    u16 tmp ;
    CRCFIFO = T3CNTH;
    CRCFIFO = T3CNTL;
    ((u8 *)(&tmp))[0] = CRCREGH ;
    ((u8 *)(&tmp))[1] = CRCREGL ;
    return tmp;
}



/*----------------------------------------------------------------------------*/
/**@brief   获取文件号
   @param   playmode   循环播放模式
   @param   searchMode  0：上一个文件；1：下一个文件；2：在强行REPEAT_ONE模式時在REPEAT_ALL模式下查找文件
   @return  0:fail 1:success
   @note     u8 fs_get_filenum(PLAY_MODE playmode, u8 searchMode)
*/
/*----------------------------------------------------------------------------*/

u8 fs_get_filenum(u8 playmode, u8 searchMode)
{
    u16 fileTotal;

    find_break_point_file_flag = 0;

    if (searchMode == PLAY_FIRST_FILE)				//播放第一个文件
    {
        given_file_number = 1;
        return GET_FILE_OK;
    }
    else if (searchMode == PLAY_LAST_FILE)				//播放最后一个文件
    {
        given_file_number = fs_msg.fileTotal;
        return GET_FILE_OK;
    }
    else if (searchMode == PLAY_BREAK_POINT)				//播放记忆的文件序号和断点
    {
#if ((LAST_MEM_FILE_PLAY_EN == 1) || (BREAK_POINT_PLAY_EN == 1))

        if (break_point_filenum)
        {
            given_file_number = break_point_filenum;
            find_break_point_file_flag = 1;
        }
        else
#endif

            given_file_number = 1;


        break_point_filenum = 0;

        return GET_FILE_OK;
    }

    fileTotal = fs_msg.fileTotal;

    given_file_number = fs_msg.fileNumber;

    if ((playmode == REPEAT_ONE) && (searchMode != PLAY_AUTO_NEXT))
    {
        playmode = REPEAT_ALL;					//在单曲循环模式下，转换成全循环模式
    }
    switch (playmode)
    {
    case REPEAT_RANDOM:
        given_file_number = ReadLFSR();
        given_file_number = given_file_number % fs_msg.fileTotal + 1;
        break;

    case REPEAT_OFF:
    case REPEAT_ALL:
        if (searchMode == PLAY_PREV_FILE)					//prev file
        {
            given_file_number--;
            if (given_file_number == 0)
            {
            	  given_file_number =  fs_msg.fileTotal;
                //return GET_DEVICE_HEAD;
            }
        }
        else					                //next file
        {
            given_file_number++;
            if (given_file_number > fileTotal)
            {
                given_file_number = 1;

		  if((playmode == REPEAT_OFF)&&(searchMode ==PLAY_AUTO_NEXT)){
                	return GET_DEVICE_END;
		  }
	     }
        }
        break;

    case REPEAT_FOLDER:
        if (searchMode == PLAY_PREV_FILE)
        {
            given_file_number--;
            if (given_file_number == fs_msg.fileTotalOutDir)
                given_file_number = fs_msg.fileTotalOutDir + fs_msg.fileTotalInDir;
        }
        else					//next file
        {
            given_file_number++;
            if (given_file_number > (fs_msg.fileTotalOutDir + fs_msg.fileTotalInDir))
                given_file_number = fs_msg.fileTotalOutDir + 1;
        }
        break;
    }

    return GET_FILE_OK;
}
#ifdef NEXT_PREV_10_FUNC
void next_prev_10_file(u8 cmd)
{
	if (cmd == FIND_NEXT_10)
	{
	    	if(given_file_number < (fs_msg.fileTotal-10))
		{
			given_file_number = given_file_number+10;	
		}
	}
	else
	{
	    	if(given_file_number > (10))
		{
			given_file_number = given_file_number-10;	
		}
	}

	put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
	
}

#endif
#if defined(USE_FOLDER_SELECT_FUNC)
u16 get_dir_file(u8 cmd)
{
	u8 fileNumber;

	if (cmd == FIND_NEXT_DIR)
	{
		fileNumber = fs_msg.fileTotalInDir + fs_msg.fileTotalOutDir + 1;

	    if (fileNumber > fs_msg.fileTotal)
		{
			fileNumber = 1;	
		}
	}
	else if(cmd == FIND_PREV_DIR)
	{
		fileNumber = fs_msg.fileTotalOutDir;
		if (fileNumber == 0)
		{
			fileNumber = fs_msg.fileTotal;
			return fileNumber;
		}
		stop_decode();
		fs_getfile_bynumber(0, &fat_ptr1, fileNumber);
		fileNumber -= (fs_msg.fileTotalInDir - 1); 		
	}
	return fileNumber;		
}
void select_folder_file(u8 cmd)
{
 	given_file_number= get_dir_file(cmd); 
       put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);

#if 0
	printf(" ---> 00  fileTotal %x \r\n",(u16)fs_msg.fileTotal);
	printf(" ---> 00  given_file_number %x \r\n",(u16)given_file_number);
	printf(" ---> 00  dirNum %x \r\n",(u16)(fs_msg.dirNum));
#endif	
}
#endif
