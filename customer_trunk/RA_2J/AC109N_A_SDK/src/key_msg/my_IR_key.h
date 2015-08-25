/*--------------------------------------------------------------------------*/
/**@file   my_IR_key.h
   @brief  按键消息扫描头文件
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"

#ifndef	_MY_IR_KEY_H_
#define _MY_IR_KEY_H_
#include "config.h"

#define USER_CODE_ID		0xFF00


/* FILL BELOW TO ASSIGN CODE TABLE*/
#ifdef IR_USER_CODE_0XCF30
#define  IR_KEY_CODE_0				0x00
#define  IR_KEY_CODE_1				0x01
#define  IR_KEY_CODE_2				0x02
#define  IR_KEY_CODE_3				0xFF
#define  IR_KEY_CODE_4				0xFF
#define  IR_KEY_CODE_5				0xFF
#define  IR_KEY_CODE_6				0xFF
#define  IR_KEY_CODE_7				0xFF
#define  IR_KEY_CODE_8				0xFF
#define  IR_KEY_CODE_9				0xFF
#define  IR_KEY_CODE_100			0xFF

#define  IR_KEY_CODE_MODE			0xFF
#define  IR_KEY_CODE_PLAY			0x0E
#define  IR_KEY_CODE_PLAY_M		0xFF
#define  IR_KEY_CODE_VOL_UP		0xFF
#define  IR_KEY_CODE_VOL_DN		0xFF	
#define  IR_KEY_CODE_PREV			0x1C
#define  IR_KEY_CODE_NEXT			0x15
#define  IR_KEY_CODE_EQ_UP			0xFF
#define  IR_KEY_CODE_EQ_DN			0xFF
#define  IR_KEY_CODE_CHN_UP		0xFF
#define  IR_KEY_CODE_CHN_DN		0xFF
#else
#define  IR_KEY_CODE_0				0x16
#define  IR_KEY_CODE_1				0x0C
#define  IR_KEY_CODE_2				0x18
#define  IR_KEY_CODE_3				0x5E
#define  IR_KEY_CODE_4				0x08
#define  IR_KEY_CODE_5				0x1C
#define  IR_KEY_CODE_6				0x5A
#define  IR_KEY_CODE_7				0x42
#define  IR_KEY_CODE_8				0x52
#define  IR_KEY_CODE_9				0x4A
#define  IR_KEY_CODE_100			0x19

#define  IR_KEY_CODE_MODE			0x46
#define  IR_KEY_CODE_PLAY			0x43
#define  IR_KEY_CODE_PLAY_M		0x0D
#define  IR_KEY_CODE_VOL_UP		0x15
#define  IR_KEY_CODE_VOL_DN		0x07	
#define  IR_KEY_CODE_PREV			0x44
#define  IR_KEY_CODE_NEXT			0x40
#define  IR_KEY_CODE_EQ_UP			0x09
#define  IR_KEY_CODE_EQ_DN			0xFF
#define  IR_KEY_CODE_CHN_UP		0x47
#define  IR_KEY_CODE_CHN_DN		0x45
#endif


#define IR_KEY_CODE_RETURN			0xFF
#define IR_KEY_CODE_NONE 			0xFF



#endif/*_MY_IR_KEY_H_*/


