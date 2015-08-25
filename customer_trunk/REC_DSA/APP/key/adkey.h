/*--------------------------------------------------------------------------*/
/**@file   adkey.h
   @brief  AD按键定义
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef	_ADKEY_H_
#define _ADKEY_H_

/************ADKEY GROUP 1****************/

#define ADKEY1			(0xff40-0xe840)/2+0xe840
#define ADKEY1_0		(0xe800-0xd1c0)/2+0xd1c0
#define ADKEY1_1		(0xd140-0xb2c0)/2+0xb2c0
#define ADKEY1_2		(0xb2c0-0x99c0)/2+0x99c0
#define ADKEY1_3		(0x9980-0x85c0)/2+0x85c0
#define ADKEY1_4		(0x8540-0x67c0)/2+0x67c0
#define ADKEY1_5		(0x66c0-0x4ac0)/2+0x4ac0
#define ADKEY1_6		(0x49c0-0x3740)/2+0x3740
#define ADKEY1_7		(0x3700-0x1e80)/2+0x1e80
#define ADKEY1_8		(0x1e40-0x0)/2+0x0

u16 _code adkey1_check_table[] = {ADKEY1_0, ADKEY1_1, ADKEY1_2, ADKEY1_3, ADKEY1_4, ADKEY1_5, ADKEY1_6, ADKEY1_7, ADKEY1_8,};
	//case MSG_REV_STRONG_UP:          MSG_DEVICE_MODE
	//case MSG_REV_STRONG_DOWN:        MSG_DEL_CURR_FILE
    //case MSG_REV_DEEP_UP:
    //case MSG_REV_DEEP_DOWN:
//
#define ADKEY1_MUSIC_SHORT		\
                                /*00*/    NO_MSG,\
							    /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    MSG_PREV_FOLDER,\
								/*04*/    MSG_NEXT_FOLDER,\
								/*05*/    MSG_MUSIC_NEXT_FILE,\
								/*06*/    MSG_MUSIC_PREV_FILE,\
								/*07*/    MSG_SDMMC_IN_SEL,\
								/*08*/    MSG_USB_DISK_IN_SEL,\
								/*09*/    MSG_MUSIC_PP,

#define ADKEY1_MUSIC_LONG		\
                                /*00*/    MSG_REC_MIC,\
                                /*01*/    MSG_REC_AUX1,\
								/*02*/    MSG_REC_AUX2,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    MSG_MUSIC_FF,\
								/*06*/    MSG_MUSIC_FR,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    MSG_REC_STOP,


#define ADKEY1_MUSIC_HOLD		\
                                /*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    MSG_MUSIC_FF,\
								/*06*/    MSG_MUSIC_FR,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,

#define ADKEY1_MUSIC_LONG_UP	\
                                /*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    MSG_MUSIC_FFR_DONE,\
								/*06*/    MSG_MUSIC_FFR_DONE,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,

const u8 _code adkey1_msg_music_table[4][10] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY1_MUSIC_SHORT},
    /*长按*/		{ADKEY1_MUSIC_LONG},
    /*连按*/		{ADKEY1_MUSIC_HOLD},
    /*长按抬起*/	{ADKEY1_MUSIC_LONG_UP},
};

//
#define ADKEY1_FM_SHORT			\
								/*00*/    MSG_FM_NEXT_STEP,\	
							    /*01*/    MSG_FM_PREV_STEP,\  
								/*02*/    MSG_FM_SCAN_ALL,\
								/*03*/    MSG_REC_PP,\
								/*04*/    MSG_REC_KEY,\
								/*05*/    MSG_FM_NEXT_STATION,\
								/*06*/    MSG_FM_PREV_STATION,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,

#define ADKEY1_FM_LONG			\
								/*00*/    MSG_FM_NEXT_STEP,\
                                /*01*/    MSG_FM_PREV_STEP,\
								/*02*/    MSG_NEXT_WORKMODE,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    MSG_FM_SCAN_ALL_DOWN,\
								/*06*/    MSG_FM_SCAN_ALL_UP,\
								/*07*/    MSG_VOL_UP,\
								/*08*/    MSG_VOL_DOWN,\
								/*09*/    MSG_KALAOK,

#define ADKEY1_FM_HOLD			\
								/*00*/    MSG_FM_NEXT_STEP,\
                                /*01*/    MSG_FM_PREV_STEP,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    MSG_VOL_UP,\
								/*08*/    MSG_VOL_DOWN,\
								/*09*/    NO_MSG,


#define ADKEY1_FM_LONG_UP		\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,

const u8 _code adkey1_msg_fm_table[4][10] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY1_FM_SHORT},
    /*长按*/		{ADKEY1_FM_LONG},
    /*连按*/		{ADKEY1_FM_HOLD},
    /*长按抬起*/	{ADKEY1_FM_LONG_UP},
};
#endif


