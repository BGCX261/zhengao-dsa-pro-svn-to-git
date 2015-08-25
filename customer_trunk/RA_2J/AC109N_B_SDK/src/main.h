/*************************************************************/
/** @file:main.h
    @brief:
    @details:
    @author:Juntham
    @date: 2012-06-13,8:43
    @note:
*/
/*************************************************************/
#ifndef _MAIN_
#define _MAIN_

#include "config.h"

#ifdef __SMART_CPU__


typedef enum
{

#ifdef CUSTOMER_DEFINED_MODE_CYCLE
    ///MUSIC_MODE = 0,
    SYS_USB_MODE,
    
    SYS_SD_MODE,

    SYS_BLUETOOTH_MODE,

    SYS_AUX_MODE,

    SYS_RADIO_MODE,

#ifdef RTC_EN
    SYS_RTC_MODE,
#endif

#ifdef IPOD_MODE_ENABLE 
    SYS_IPOD_MODE,
#endif
    SYS_IDLE_MODE,

#ifdef USB_DEVICE_EN
    SYS_USB_DEVICE_MODE,
#endif

    SYS_PWR_OFF_MODE,

    MAX_WORK_MODE = SYS_IDLE_MODE,
    
#else
    ///MUSIC_MODE = 0,
    SYS_USB_MODE,
    
    SYS_SD_MODE,

    SYS_RADIO_MODE,

    SYS_AUX_MODE,
#ifdef RTC_EN
    SYS_RTC_MODE,
#endif
    SYS_BLUETOOTH_MODE,
#ifdef IPOD_MODE_ENABLE 
    SYS_IPOD_MODE,
#endif
    SYS_IDLE_MODE,

#ifdef USB_DEVICE_EN
    SYS_USB_DEVICE_MODE,
#endif

    SYS_PWR_OFF_MODE,

    MAX_WORK_MODE = SYS_IDLE_MODE,
#endif
}ENUM_WORK_MODE;


extern _no_init bool _bit Sys_Volume;
extern _no_init bool _bit Sys_IRInput;
extern _no_init bool _bit Sys_HalfSec;
extern _no_init bool _bit alm_on_flag;
extern _no_init bool _bit set_sd_clk;


extern ENUM_WORK_MODE _data work_mode;
extern u8 _data main_vol_L, main_vol_R;
extern void (_near_func * _pdata int_enter_pro[16])(void);

#endif

#endif
