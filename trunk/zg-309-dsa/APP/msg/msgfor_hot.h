/*--------------------------------------------------------------------------*/
/**@file    msgfor_hot.h
   @brief   HOT 消息处理
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _MSGFOR_HOT_
#define	_MSGFOR_HOT_

#include "config.h"
#include "key.h"


#ifdef __C51__
void ap_handle_hotkey(u8 msg);
#endif

typedef enum{

	USB_DEV,
	SD_DEV,
#if defined(EXCHANGE_FM_AUX_PRIO)    
	AUX_DEV,
	FM_DEV,
#ifdef RADIO_AM_WM_ENABLE
    	AM_DEV,
#endif    		
#else	
	FM_DEV,
#ifdef RADIO_AM_WM_ENABLE
    	AM_DEV,
#endif    	
	AUX_DEV,
#endif	
#if defined(IPONE_INDEPENDENT_MODE)	
	IPH_DEV,
#endif	

#if (RTC_ENABLE)
	RTC_DEV,
#endif	
	IDLE,
}DEV_ON_LIST;

void Init_Func_List();
void Set_Curr_Func(u8 curr_mod);
void Remov_Func_From_List(DEV_ON_LIST Dev);
#endif