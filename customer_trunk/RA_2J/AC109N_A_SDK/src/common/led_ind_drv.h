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
#include "main.h"

#define PORT_P0		0X80
#define PORT_P1		0X90
#define PORT_P2		0XA0
#define PORT_P3		0XB0
#define PORT_P4		0xB1

#define PORT_VPP	0XF0
#define PORT_N		0XFF


typedef struct {

	ENUM_WORK_MODE led_mode;
	u8 led_port_bit;
	u8 led_port;
#ifdef EXTENDED_WORK_MODE_USE_TWO_GPIO_CTRL
	u8 led_port_bit_2;
	u8 led_port_2;
#endif	
}mode_led;

#endif
