/*--------------------------------------------------------------------------*/
/**@file    gpio_if.c
   @brief   gpio_if  ½Ó¿Úº¯Êý
   @details
   @author  R A 
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"
#include "gpio_if.h"

extern bool iic_busy;

#ifdef AUX_DETECTION_THREAD_ENABLE
void aux_detect_init(void)
{
	aux_detect_gpio_init();
}
bool aux_detect_level(void)
{
	return (aux_detect_gpio_pin);
}
void aux_detect_release(void)
{
	aux_detect_gpio_release();
}
bool aux_gpio_protect(void)
{
#ifdef AUX_DETECTION_GPIO_SHARE_WITH_IIC_CLK
	return iic_busy;
#else
	return 0;
#endif

}
#endif

#ifdef PHONE_DETECTION_THREAD_ENABLE
void phone_detect_init(void)
{
	phone_detect_gpio_init();
}
bool phone_detect_level(void)
{
	return (phone_detect_gpio_pin);
}
void phone_detect_release(void)
{
	phone_detect_gpio_release();
}
bool phone_gpio_protect(void)
{
#ifdef PHONE_DETECTION_GPIO_SHARE_WITH_IIC_CLK
	return iic_busy;
#else
	return 0;
#endif

}
#endif

#if 1//def CHARGER_DETECTION_THREAD_ENABLE
void charger_detect_init(void)
{
	charger_detect_gpio_init();
}
bool charger_detect_level(void)
{
	return (charger_detect_gpio_pin);
}
void charger_detect_release(void)
{
	charger_detect_gpio_release();
}
bool charger_gpio_protect(void)
{

#ifdef CHARGER_DETECTION_GPIO_SHARE_WITH_IIC_CLK
	return iic_busy;
#else
	return 0;
#endif

}
#endif

#ifdef USE_POWER_KEY
void sys_gpio_ctrl_pwr(SYS_PWR_HDLR ctrl_level)
{
	power_gpio_init();
	
	if(ctrl_level == SYS_PWR_ON){
		power_port_on();
	}
	else{
		power_port_off();
	}

}
#endif



