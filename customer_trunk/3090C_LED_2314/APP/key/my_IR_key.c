/*--------------------------------------------------------------------------*/
/**@file   my_IR_key.c
   @brief  红外按键码值映射表
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"

#include "key.h"
#include "my_IR_key.h"

#if 1//def _MY_IR_KEY_


_code u8 My_IRTab[]=       /*user code is 0xFF*/
{
	My_IR_KEY_0,
	My_IR_KEY_1,
	My_IR_KEY_2,
	My_IR_KEY_3,
	My_IR_KEY_4,
	My_IR_KEY_5,
	My_IR_KEY_6,
	My_IR_KEY_7,
	My_IR_KEY_8,
	My_IR_KEY_9,
	My_IR_KEY_100,
	My_IR_KEY_MODE,
	My_IR_KEY_PLAY,	
	My_IR_KEY_PLAY_M,
	My_IR_KEY_VOL_UP,
	My_IR_KEY_VOL_DN,
	My_IR_KEY_PREV,
	My_IR_KEY_NEXT,
	My_IR_KEY_EQ_UP,
	My_IR_KEY_CHN_UP,
	My_IR_KEY_CHN_DN,
	My_IR_KEY_F_NEXT,
	My_IR_KEY_F_PREV,
	My_IR_KEY_STOP,
	My_IR_KEY_REC,
	My_IR_KEY_DEL,
	My_IR_KEY_POWER,
	My_IR_KEY_SLEEP,
	My_IR_KEY_ALARM,
	My_IR_KEY_MUTE,
};

u8 get_my_IR_key_MAX()
{
	return (u8)((sizeof(My_IRTab)));
}
#endif


