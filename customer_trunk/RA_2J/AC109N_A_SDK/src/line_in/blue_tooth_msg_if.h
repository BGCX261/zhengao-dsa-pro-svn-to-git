#include "custom_config.h"

#ifndef _BLUE_TOOTH_MSG_IF_H_
#define _BLUE_TOOTH_MSG_IF_H_

#ifdef BLUE_TOOTH_UART_FUNC
#include "bluetooth_mode.h"
#include "uart.h"
#include "main.h"
#include "config.h"
#include "clock.h"
#include "msg.h"

BT_MSG const _code bt_rev_msg[]=
{
	//BT_PAIR_MODE,			MSG_BT_PAIRING,
	BT_CONECTED_A2DP, 		MSG_BT_CONNECTED,
	BT_CONECTED_AVRCP, 	MSG_BT_CONNECTED,
	BT_DISCONECT_A2DP,		MSG_BT_REPAIRING,			
	BT_DISCONECT_AVRCP,	MSG_BT_REPAIRING,			
	BT_INCOMING_CALL,		MSG_BT_INCOMING_CALL,			
	BT_OUTGOING_CALL,		MSG_BT_OUTGOING_CALL,			
	BT_CALL_DROP,			MSG_BT_DROP_CALL,			
	BT_CALL_ACTIVE,			MSG_BT_ACTIVE_CALL,			
};
BT_MSG const _code bt_promt_msg[]=
{
	BT_PLAY,						MSG_MUSIC_PP,
	BT_NEXT,					MSG_MUSIC_NEXT_FILE,
	BT_PREV,					MSG_MUSIC_PREV_FILE,
#ifdef BLUE_TOOTH_UART_CTRL_VOL
	BT_VOL_P,					MSG_VOL_UP,
	BT_VOL_M,					MSG_VOL_DOWN,
#endif	
	//BT_FAST_FARWORD,			MSG_MUSIC_FF,
	//BT_REWIND,					MSG_MUSIC_FR,
	BT_STOP,					MSG_MUSIC_STOP,
	BT_DISPAIR,					MSG_BT_PAIRING,
	BT_FAST_PAIRING_MODE,		MSG_BT_REPAIRING,	
	BT_ANSWER_CALL,			MSG_BT_ANSWER_CALL,
	BT_END_CALL,				MSG_BT_END_CALL,
};



#endif


#endif

