/*--------------------------------------------------------------------------*/
/**@file       get_music_file.c
   @brief      �ļ�����
   @details
   @author
   @date   2010-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#include "get_music_file.h"
#include "device.h"
#include "uart.h"


extern u16 given_file_number;
extern u16 break_point_filenum;
extern u8 given_device;
extern u8 play_mode;
extern FSAPIMSG _pdata fs_msg;
extern FIL xdata fat_ptr1;
extern u8 device_active;
extern bool find_break_point_file_flag;

extern void stop_decode(void);

/*----------------------------------------------------------------------------*/
/**@brief   ��ȡһ�������
   @param   ��
   @return  ��ȡ���������
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
/**@brief   ��ȡ�ļ���
   @param   playmode   ѭ������ģʽ
   @param   searchMode  0����һ���ļ���1����һ���ļ���2����ǿ��REPEAT_ONEģʽ�r��REPEAT_ALLģʽ�²����ļ�
   @return  0:fail 1:success
   @note     u8 fs_get_filenum(PLAY_MODE playmode, u8 searchMode)
*/
/*----------------------------------------------------------------------------*/

u8 fs_get_filenum(u8 playmode, u8 searchMode)
{
    //u16 fileTotal;
    
    find_break_point_file_flag = 0;
//    if(RECODE_PLAY == encode_status)
//    {
//        playmode = REPEAT_REC;
//    }
//    else 
    if (searchMode == PLAY_FIRST_FILE)				//���ŵ�һ���ļ�
    {
        given_file_number = 1;
        return GET_FILE_OK;
    }
    else if (searchMode == PLAY_LAST_FILE)				//�������һ���ļ�
    {
        given_file_number = logic_fileTotal;//fs_msg.fileTotal;
        return GET_FILE_OK;
    }
    else if (searchMode == PLAY_BREAK_POINT)				//���ż�����ļ���źͶϵ�
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
    else if (PLAY_SEL_FILE == searchMode)		 //����ɾ���ļ�����ļ�
    {
        if((!given_file_number) || (given_file_number > logic_fileTotal))
        {
            given_file_number = 1;
        }
        return GET_FILE_OK;   
    }

    given_file_number = filenum_phy_logic(fs_msg.fileNumber);  //�����ļ���ת�����߼��ļ���

    if ((playmode == REPEAT_ONE) && (searchMode != PLAY_AUTO_NEXT))
    {
        playmode = REPEAT_ALL;					//�ڵ���ѭ��ģʽ�£�ת����ȫѭ��ģʽ
    }


    switch (playmode)
    {
    case REPEAT_RANDOM:
        given_file_number = ReadLFSR();
        given_file_number = given_file_number % logic_fileTotal + 1;
        break;

    case REPEAT_BACK:					  //��������
        if (searchMode == PLAY_PREV_FILE)		 //next file		
        {
			given_file_number++;
            if (given_file_number > logic_fileTotal)
            {
                given_file_number = 1;
                return GET_DEVICE_END;
            }
            //goto _next_file_rpt;
        }
        else					               	  	//prev file
        {
			given_file_number--;
            if (given_file_number == 0)
            {
                return GET_DEVICE_HEAD;
            }
            //goto _prve_file_rpt;
        }
        break;
    case REPEAT_OFF:
    case REPEAT_ALL:
        if (searchMode == PLAY_PREV_FILE)					//prev file
        {
//_prve_file_rpt:
            given_file_number--;
            if (given_file_number == 0)
            {
            	   given_file_number =logic_fileTotal;
                //return GET_DEVICE_HEAD;
            }
        }
        else					                //next file
        {
//_next_file_rpt:
            given_file_number++;
            if (given_file_number > logic_fileTotal)
            {
                given_file_number = 1;
				
		  if(playmode ==REPEAT_OFF){
                	return GET_DEVICE_END;
		  }
            }
        }
        break;

    case REPEAT_FOLDER:
        if (searchMode == PLAY_PREV_FILE)
        {
            given_file_number = filenum_logic_phy(given_file_number);  //�߼��ļ���ת���������ļ���
            given_file_number--;
            if (given_file_number == fs_msg.fileTotalOutDir)
                given_file_number = fs_msg.fileTotalOutDir + fs_msg.fileTotalInDir;
            given_file_number = filenum_phy_logic(given_file_number);	//�����ļ���ת�����߼��ļ���
        }
        else					//next file
        {
            given_file_number = filenum_logic_phy(given_file_number);
            given_file_number++;
            if (given_file_number > (fs_msg.fileTotalOutDir + fs_msg.fileTotalInDir))
                given_file_number = fs_msg.fileTotalOutDir + 1;
            given_file_number = filenum_phy_logic(given_file_number);
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
}

#endif
#ifdef USE_FOLDER_SELECT_FUNC
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
	printf(" ---> 00  dirNum %x \r\n",(u16)(fs_msg.dir_index));
#endif	

}
#endif



