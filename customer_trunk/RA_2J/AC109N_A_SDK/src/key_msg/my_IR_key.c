/*--------------------------------------------------------------------------*/
/**@file   my_IR_key.c
   @brief  红外按键码值映射表
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "my_IR_key.h"

#if 1//def _MY_IR_KEY_

u8 const _code My_IRTab[]=       /*user code is 0xFF*/
{
	IR_KEY_CODE_0,
	IR_KEY_CODE_1,
	IR_KEY_CODE_2,
	IR_KEY_CODE_3,
	IR_KEY_CODE_4,
	IR_KEY_CODE_5,
	IR_KEY_CODE_6,
	IR_KEY_CODE_7,
	IR_KEY_CODE_8,
	IR_KEY_CODE_9,
	IR_KEY_CODE_100,
	IR_KEY_CODE_MODE,
	IR_KEY_CODE_PLAY,
	IR_KEY_CODE_PLAY_M,
	IR_KEY_CODE_VOL_UP,
	IR_KEY_CODE_VOL_DN,
	IR_KEY_CODE_PREV,
	IR_KEY_CODE_NEXT,
	IR_KEY_CODE_EQ_UP,
	IR_KEY_CODE_CHN_UP,
	IR_KEY_CODE_CHN_DN,
};

#endif


