/*--------------------------------------------------------------------------*/
/**@file    led_ind_drv.c
   @brief   led_ind_drv
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "led_ind_drv.h"
#include "main.h"
#include "device.h"

#if defined(NEW_CUSTOMIZED_LED_METHOD)

#ifndef NO_PLAY_STATUS_LED
extern _xdata SYS_WORK_MODE  work_mode;

static u8 LED_Flash_mode =0xFF;
static xd_u16 LED_cnt=0;
static u8 last_led_work_mode=0x0F;

#if defined(K202_WEISI_KL202_V001)
#define LED_MAX_NUM	3

mode_led _code mode_led_tab[LED_MAX_NUM]=
{
	SYS_MP3DECODE_USB,		BIT(7),PORT_P2,
	SYS_MP3DECODE_SD,		BIT(4),PORT_P2,
	SYS_FMREV,				BIT(5),PORT_P2,
};

#elif defined(K000_JLH_2402_V001)

#define LED_MAX_NUM	3
mode_led _code mode_led_tab[LED_MAX_NUM]=
{
	SYS_MP3DECODE_USB,		BIT(4),PORT_P2,
	SYS_MP3DECODE_SD,		BIT(5),PORT_P2,
	SYS_FMREV,				BIT(6),PORT_P2,
};
#else
#define LED_MAX_NUM	4
mode_led _code mode_led_tab[LED_MAX_NUM]=
{
	SYS_MP3DECODE_USB,		BIT(7),PORT_P0,
	SYS_MP3DECODE_SD,		BIT(7),PORT_P0,
	SYS_FMREV,				BIT(7),PORT_P0,
	SYS_AUX,				BIT(7),PORT_P0,	

};
#endif

void new_led_gpio_init()
{
	u8 led_port=0,i=0;
	for(i=0;i<LED_MAX_NUM;i++){
		
		if(mode_led_tab[i].led_port ==PORT_P0){

			P0DIR &=~(mode_led_tab[i].led_port_bit);
			P0PU |=(mode_led_tab[i].led_port_bit);
	#if defined(LED_CTRL_LEVEL_NORMAL)
				P0 &=~(mode_led_tab[i].led_port_bit);				
	#else
				P0 |=(mode_led_tab[i].led_port_bit);							
	#endif			
		}
		else if(mode_led_tab[i].led_port ==PORT_P1){
			
			P1DIR &=~(mode_led_tab[i].led_port_bit);
			P1PU |=(mode_led_tab[i].led_port_bit);
	#if defined(LED_CTRL_LEVEL_NORMAL)
				P1 &=~(mode_led_tab[i].led_port_bit);				
	#else
				P1 |=(mode_led_tab[i].led_port_bit);							
	#endif			
		}
		else if(mode_led_tab[i].led_port ==PORT_P2){


			if((mode_led_tab[i].led_port_bit)>=BIT(6)){
				DACCON0|=0x80;
			}
			else if((mode_led_tab[i].led_port_bit)>=BIT(4)){
				DACCON0|=0x40;
			}

			P2DIR &=~(mode_led_tab[i].led_port_bit);	
			P2PU |=(mode_led_tab[i].led_port_bit);
	#if defined(LED_CTRL_LEVEL_NORMAL)
				P2 &=~(mode_led_tab[i].led_port_bit);				
	#else
				P2 |=(mode_led_tab[i].led_port_bit);							
	#endif			
		}
		else if(mode_led_tab[i].led_port ==PORT_P3){

			P3DIR &=~(mode_led_tab[i].led_port_bit);	
			P3PU |=(mode_led_tab[i].led_port_bit);	
	#if defined(LED_CTRL_LEVEL_NORMAL)
				P3 &=~(mode_led_tab[i].led_port_bit);				
	#else
				P3 |=(mode_led_tab[i].led_port_bit);							
	#endif
		}
	}

//et_play_flash(LED_FLASH_ON);

}
void turn_off_last_working_led()
{
	if(last_led_work_mode>SYS_IDLE)return;
	
		if(mode_led_tab[last_led_work_mode].led_port ==0x80){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P0 &=~(mode_led_tab[last_led_work_mode].led_port_bit);				
#else
			P0 |=(mode_led_tab[last_led_work_mode].led_port_bit);							
#endif			
		}
		else if(mode_led_tab[last_led_work_mode].led_port ==0x90){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P1 &=~(mode_led_tab[last_led_work_mode].led_port_bit);				
#else
			P1 |=(mode_led_tab[last_led_work_mode].led_port_bit);							
#endif			
		}
		else if(mode_led_tab[last_led_work_mode].led_port ==0xa0){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P2 &=~(mode_led_tab[last_led_work_mode].led_port_bit);				
#else
			P2 |=(mode_led_tab[last_led_work_mode].led_port_bit);							
#endif			
		}
		else if(mode_led_tab[last_led_work_mode].led_port ==0xb0){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P3 &=~(mode_led_tab[last_led_work_mode].led_port_bit);				
#else
			P3 |=(mode_led_tab[last_led_work_mode].led_port_bit);							
#endif
		}		
}
 void led_set_new_method(u8 led_cmd)
{	
	switch(mode_led_tab[work_mode].led_port){

		case 0x80:

			if(led_cmd)
				P0 |=(mode_led_tab[work_mode].led_port_bit);			
			else 
				P0 &=~(mode_led_tab[work_mode].led_port_bit);	
			break;
		case 0x90:

			if(led_cmd)
				P1 |=(mode_led_tab[work_mode].led_port_bit);			
			else 
				P1 &=~(mode_led_tab[work_mode].led_port_bit);			
			break;
		case 0xA0:

			if(led_cmd)
				P2 |=(mode_led_tab[work_mode].led_port_bit);			
			else 
				P2 &=~(mode_led_tab[work_mode].led_port_bit);			
			break;
		case 0xB0:
		
			if(led_cmd)
				P3 |=(mode_led_tab[work_mode].led_port_bit);			
			else 
				P3 &=~(mode_led_tab[work_mode].led_port_bit);			
			break;
	}
}
void set_play_flash(LED_FLASH_TYPE led_status)
{
	EA = 0;
#if(LED_MAX_NUM>1)    
	if(last_led_work_mode!=work_mode)
	{
		turn_off_last_working_led();
		last_led_work_mode = work_mode;
	}
#endif

	if(led_status ==LED_FLASH_ON){
		LED_Flash_mode = 0xF6;
	}
	else if(led_status ==LED_FLASH_VERY_FAST){
		LED_Flash_mode = 36;
	}
	else if(led_status ==LED_FLASH_FAST){
		LED_Flash_mode = 50;
	}
	else if(led_status ==LED_FLASH_NOR){
		LED_Flash_mode = 250;
	}
	else if(led_status ==LED_FLASH_STOP){
		LED_Flash_mode = 0xFF;
	}
	EA =1;
}
#endif
void play_led_flash()
{
#ifndef NO_PLAY_STATUS_LED

	static bool led_bit=0;

#if defined(PLAY_STATUS_LED_SHARE_WITH_IIC_SCL)
	if(iic_busy)return;
#endif

	LED_cnt++;
	
	if(LED_Flash_mode ==0xFF){	//LED_FLASH_STOP

		led_set_new_method(OFF_LEVEL);
	}
	else if(LED_Flash_mode == 0xF6){	//LED_FLASH_ON

		led_set_new_method(ON_LEVEL);
	}
	else  if((LED_cnt % LED_Flash_mode)==0){

		led_bit =~led_bit;
		led_set_new_method(led_bit);
	}
	
#endif	
}
#endif
