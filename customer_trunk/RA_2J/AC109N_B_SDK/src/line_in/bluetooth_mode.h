#ifndef _BLUETOOTH_MODE_H_
#define _BLUETOOTH_MODE_H_

#include "config.h"

enum {
	
	BT_STA_STOP,
	BT_STA_PAUSE,
	BT_STA_PLAY,	
	BT_STA_MASK=0x80,	
};


typedef enum {
	
	BT_POWER_ON,
	BT_PAIR_MODE,
	BT_PAIRED,
	BT_CONECTED_A2DP,
	BT_CONECTED_AVRCP,
	BT_CONECTED_HF,
	BT_INCOMING_CALL,
	BT_OUTGOING_CALL,
	BT_CALL_DROP,
	BT_CALL_ACTIVE,
	BT_DISCONECT_A2DP,	
	BT_DISCONECT_AVRCP,		
	BT_ACK,
	BT_DEV_ISSUE_PLAY,
	BT_STATUS_MAX,
}AT_REV_CMD;

typedef enum {
	
	BT_PLAY,
	BT_NEXT,
	BT_PREV,
	BT_VOL_P,
	BT_VOL_M,	
	BT_FAST_FARWORD,
	BT_REWIND,
	BT_STOP,
	BT_DISPAIR,
	BT_ENTER_PAIRING_MODE,
	BT_FAST_PAIRING_MODE,
	BT_ANSWER_CALL,
	BT_END_CALL,

	BT_CMD_SET_MAX,
}AT_PROMPT_CMD;

enum {

	CALL_IDLE,
	INCOMING_CALL,
	OUTGOING_CALL,
	CALL_ACTIVE,
};

enum{

	BT_STA_LED_IDLE,
	BT_STA_LED_SDBY,
	BT_STA_LED_PAIR,
	BT_STA_LED_INCOMING,
	BT_STA_LED_CALL,
	BT_STA_LED_PLAY,
	BT_STA_LED_PAUSE,
	BT_STA_LED_ON = 0x86,

};

typedef struct{

	u8 bt_cmd;
	u8 sys_msg;
}BT_MSG;

#ifdef __IAR_SYSTEMS_ICC__

void bluetooth_main(void);
void bluetooth_gpio_preinit(void);

u8 get_blue_tooth_connect_status(void);
#endif  /*  __IAR_SYSTEMS_ICC__ */


#endif  /*  _LINE_IN_MODE_H_   */
