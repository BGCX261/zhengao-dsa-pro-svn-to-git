/*--------------------------------------------------------------------------*/
/**@file   led_ind_drv.h
   @brief  LED驱动头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"

#ifndef _LED_IND_DRV_H_
#define	_LED_IND_DRV_H_
#include "config.h"

#define PORT_P0		0X80
#define PORT_P1		0X90
#define PORT_P2		0XA0
#define PORT_P3		0XB0


typedef struct {

	SYS_WORK_MODE led_mode;
	u8 led_port_bit;
	u8 led_port;
}mode_led;


#ifdef LED_CTRL_LEVEL_NORMAL
#define ON_LEVEL		1
#define OFF_LEVEL		0
#else
#define ON_LEVEL		0
#define OFF_LEVEL		1
#endif


#ifdef __C51__
void new_led_gpio_init();
void set_play_flash(LED_FLASH_TYPE led_status);
void play_led_flash();
#endif

#endif
