/*--------------------------------------------------------------------------*/
/**@file    led_ind_drv.c
   @brief   led_ind_drv
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"
#include "led_ind_drv.h"
#include "main.h"
#include "device.h"

#if 0
#if defined(PLAY_STATUS_LED_P02)
#define LED_MAX_NUM	2
mode_led const _code  mode_led_tab[LED_MAX_NUM]=
{
	SYS_USB_MODE,			BIT(2),PORT_P0,
	SYS_SD_MODE,			BIT(2),PORT_P0,
};
#elif defined(PLAY_STATUS_LED_P25)
#define LED_MAX_NUM	4
mode_led const _code  mode_led_tab[LED_MAX_NUM]=
{
	SYS_USB_MODE,			BIT(5),PORT_P2,
	SYS_SD_MODE,			BIT(5),PORT_P2,
	SYS_AUX_MODE,			BIT(5),PORT_P2,
	SYS_IDLE_MODE,			BIT(5),PORT_P2,
};
#elif defined(PLAY_STATUS_LED_P01)
#define LED_MAX_NUM	4
mode_led const _code  mode_led_tab[LED_MAX_NUM]=
{
	SYS_USB_MODE,				BIT(1),PORT_P0,
	SYS_SD_MODE,				BIT(1),PORT_P0,
	SYS_BLUETOOTH_MODE,		BIT(1),PORT_P0,
	SYS_IDLE_MODE,				BIT(1),PORT_P0,
};
#elif defined(PLAY_STATUS_LED_P17)
#define LED_MAX_NUM	4
mode_led const _code  mode_led_tab[LED_MAX_NUM]=
{
	SYS_USB_MODE,				BIT(7),PORT_P1,
	SYS_SD_MODE,				BIT(7),PORT_P1,
	SYS_RADIO_MODE,			BIT(7),PORT_P1,
	SYS_AUX_MODE,				BIT(7),PORT_P1,	
};
#elif defined(PLAY_STATUS_LED_P46)
#define LED_MAX_NUM	3
mode_led const _code  mode_led_tab[LED_MAX_NUM]=
{
	SYS_USB_MODE,			BIT(6),PORT_P4,
	SYS_SD_MODE,			BIT(6),PORT_P4,
	SYS_AUX_MODE,			BIT(6),PORT_P4,
};
#else
#define LED_MAX_NUM	4
mode_led const _code  mode_led_tab[LED_MAX_NUM]=
{
	SYS_USB_MODE,				BIT(7),PORT_P0,
	SYS_SD_MODE,				BIT(7),PORT_P0,
	SYS_RADIO_MODE,			BIT(7),PORT_P0,
	SYS_AUX_MODE,				BIT(7),PORT_P0,	
};
#endif
#endif

