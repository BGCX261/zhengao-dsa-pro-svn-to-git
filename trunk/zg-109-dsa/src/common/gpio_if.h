/*************************************************************/
/** @file:gpio_if.h
    @brief:
    @details:
    @author: R  A
    @date: 2012-06-13,8:43
    @note:
*/
/*************************************************************/

//1 GPIO :P36 DP;   P37 DM


#include "custom_config.h"
#ifndef _GPIO_IF_
#define _GPIO_IF_

#include "config.h"
#include "misc_hdlr_if.h"

#ifdef MUTE_CTRL_LEVEL_LOW_MUTE
#define MUTE_LEVEL		0
#define UNMUTE_LEVEL	1
#else
#define MUTE_LEVEL		1
#define UNMUTE_LEVEL	0
#endif

#ifdef LED_CTRL_LEVEL_LOW_ON
#define ON_LEVEL		0
#define OFF_LEVEL		1
#else
#define ON_LEVEL		1
#define OFF_LEVEL		0
#endif

#ifdef POWER_CTRL_LEVEL_LOW_POWER_ON
#define POWER_ON_LEVEL		0
#define POWER_OFF_LEVEL		1
#else
#define POWER_ON_LEVEL		1
#define POWER_OFF_LEVEL		0
#endif

#ifdef __SMART_CPU__

#if defined(PLAY_STATUS_LED_P25)
#define LED_PORT_BIT		5
#define led_port_init()		P2DIE &=~ (BIT(LED_PORT_BIT)); P2DIR &=~(BIT(LED_PORT_BIT));P2PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P2DIE &=~ (BIT(LED_PORT_BIT)); P25=ON_LEVEL
#define led_set_port_off()		P2DIE &=~(BIT(LED_PORT_BIT)); P25=OFF_LEVEL
#elif defined(PLAY_STATUS_LED_P17)
#define LED_PORT_BIT		7
#define led_port_init()		P1DIR &=~(BIT(LED_PORT_BIT));P1PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P17=ON_LEVEL
#define led_set_port_off()		P17=OFF_LEVEL
#elif defined(PLAY_STATUS_LED_P26)
#define LED_PORT_BIT		6
#define led_port_init()		P2DIR &=~(BIT(LED_PORT_BIT));P2PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P26=ON_LEVEL
#define led_set_port_off()		P26=OFF_LEVEL
#elif defined(PLAY_STATUS_LED_P27)
#define LED_PORT_BIT		7
#define led_port_init()		P2DIR &=~(BIT(LED_PORT_BIT));P2PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P27=ON_LEVEL
#define led_set_port_off()		P27=OFF_LEVEL
#elif defined(PLAY_STATUS_LED_P30)
#define LED_PORT_BIT		0
#define led_port_init()		P3DIR &=~(BIT(LED_PORT_BIT));P3PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P30=ON_LEVEL
#define led_set_port_off()		P30=OFF_LEVEL
#elif defined(PLAY_STATUS_LED_P04)
#define LED_PORT_BIT		4
#define led_port_init()		P0DIR &=~(BIT(LED_PORT_BIT));P0PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P04=ON_LEVEL
#define led_set_port_off()		P04=OFF_LEVEL
#elif defined(PLAY_STATUS_LED_P46)
#define LED_PORT_BIT		6
#define led_port_init()		P4DIR &=~(BIT(LED_PORT_BIT));P4PU |= BIT(LED_PORT_BIT);
#if ON_LEVEL
#define led_set_port_on()		P4DIR &=~(BIT(LED_PORT_BIT));P4PU |= BIT(LED_PORT_BIT);P4|=(BIT(LED_PORT_BIT))
#define led_set_port_off()		P4DIR &=~(BIT(LED_PORT_BIT));P4PU |= BIT(LED_PORT_BIT);P4&=~(BIT(LED_PORT_BIT))
#else
#define led_set_port_on()		P4DIR &=~(BIT(LED_PORT_BIT));P4PU |= BIT(LED_PORT_BIT);P4&=~(BIT(LED_PORT_BIT))
#define led_set_port_off()		P4DIR &=~(BIT(LED_PORT_BIT));P4PU |= BIT(LED_PORT_BIT);P4|=(BIT(LED_PORT_BIT))
#endif
#elif defined(PLAY_STATUS_LED_P01)
#define LED_PORT_BIT		1
#define led_port_init()		P0DIR &=~(BIT(LED_PORT_BIT));P0PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P01=ON_LEVEL
#define led_set_port_off()		P01=OFF_LEVEL
#elif defined(PLAY_STATUS_LED_P02)
#define LED_PORT_BIT		2
#define led_port_init()		P0DIR &=~(BIT(LED_PORT_BIT));P0PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P02=ON_LEVEL
#define led_set_port_off()		P02=OFF_LEVEL
#elif defined(PLAY_STATUS_LED_P07)
#define LED_PORT_BIT		7
#define led_port_init()		P0DIR &=~(BIT(LED_PORT_BIT));P0PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P07=ON_LEVEL
#define led_set_port_off()		P07=OFF_LEVEL
#elif defined(PLAY_STATUS_LED_VPP)
#define LED_PORT_BIT		1
#define led_port_init()		P0DIR &=~(BIT(LED_PORT_BIT));P0PU |= BIT(LED_PORT_BIT);
#define led_set_port_on()		P01=ON_LEVEL
#define led_set_port_off()		P01=OFF_LEVEL
#endif

#ifdef TWO_PLAY_STATUS_LED

#if defined(PLAY_STATUS_ID2_LED_P25)
#define LED_ID2_PORT_BIT		5
#define led_id2_port_init()		P2DIE &=~ (BIT(LED_ID2_PORT_BIT)); P2DIR &=~(BIT(LED_ID2_PORT_BIT));P2PU |= BIT(LED_ID2_PORT_BIT);
#define led_id2_set_port_on()		P2DIE &=~ (BIT(LED_ID2_PORT_BIT)); P25=ON_LEVEL
#define led_id2_set_port_off()		P2DIE &=~(BIT(LED_ID2_PORT_BIT)); P25=OFF_LEVEL
#elif defined(PLAY_STATUS_ID2_LED_P17)
#define LED_ID2_PORT_BIT		7
#define led_id2_port_init()		P1DIR &=~(BIT(LED_ID2_PORT_BIT));P1PU |= BIT(LED_ID2_PORT_BIT);
#define led_id2_set_port_on()		P17=ON_LEVEL
#define led_id2_set_port_off()		P17=OFF_LEVEL
#elif defined(PLAY_STATUS_ID2_LED_P27)
#define LED_ID2_PORT_BIT		7
#define led_id2_port_init()		P2DIR &=~(BIT(LED_ID2_PORT_BIT));P2PU |= BIT(LED_ID2_PORT_BIT);
#define led_id2_set_port_on()		P27=ON_LEVEL
#define led_id2_set_port_off()		P27=OFF_LEVEL
#elif defined(PLAY_STATUS_ID2_LED_P30)
#define LED_PORT_BIT		0
#define led_id2_port_init()		P3DIR &=~(BIT(LED_ID2_PORT_BIT));P3PU |= BIT(LED_ID2_PORT_BIT);
#define led_id2_set_port_on()		P30=ON_LEVEL
#define led_id2_set_port_off()		P30=OFF_LEVEL
#elif defined(PLAY_STATUS_ID2_LED_P04)
#define LED_ID2_PORT_BIT		4
#define led_id2_port_init()		P0DIR &=~(BIT(LED_ID2_PORT_BIT));P0PU |= BIT(LED_ID2_PORT_BIT);
#define led_id2_set_port_on()		P04=ON_LEVEL
#define led_id2_set_port_off()		P04=OFF_LEVEL
#elif defined(PLAY_STATUS_ID2_LED_P46)
#define LED_ID2_PORT_BIT		6
#define led_id2_port_init()		P4DIR &=~(BIT(LED_ID2_PORT_BIT));P4PU |= BIT(LED_ID2_PORT_BIT);
#if ON_LEVEL
#define led_id2_set_port_on()		P4DIR &=~(BIT(LED_ID2_PORT_BIT));P4PU |= BIT(LED_ID2_PORT_BIT);P4|=(BIT(LED_ID2_PORT_BIT))
#define led_id2_set_port_off()		P4DIR &=~(BIT(LED_ID2_PORT_BIT));P4PU |= BIT(LED_ID2_PORT_BIT);P4&=~(BIT(LED_ID2_PORT_BIT))
#else
#define led_id2_set_port_on()		P4DIR &=~(BIT(LED_ID2_PORT_BIT));P4PU |= BIT(LED_ID2_PORT_BIT);P4&=~(BIT(LED_ID2_PORT_BIT))
#define led_id2_set_port_off()		P4DIR &=~(BIT(LED_ID2_PORT_BIT));P4PU |= BIT(LED_ID2_PORT_BIT);P4|=(BIT(LED_ID2_PORT_BIT))
#endif
#elif defined(PLAY_STATUS_ID2_LED_P01)
#define LED_ID2_PORT_BIT		1
#define led_id2_port_init()		P0DIR &=~(BIT(LED_ID2_PORT_BIT));P0PU |= BIT(LED_ID2_PORT_BIT);
#define led_id2_set_port_on()		P01=ON_LEVEL
#define led_id2_set_port_off()		P01=OFF_LEVEL
#elif defined(PLAY_STATUS_ID2_LED_P02)
#define LED_ID2_PORT_BIT		2
#define led_id2_port_init()		P0DIR &=~(BIT(LED_ID2_PORT_BIT));P0PU |= BIT(LED_ID2_PORT_BIT);
#define led_id2_set_port_on()		P02=ON_LEVEL
#define led_id2_set_port_off()		P02=OFF_LEVEL
#elif defined(PLAY_STATUS_ID2_LED_VPP)
#define LED_PORT_BIT		1
#define led_id2_port_init()		P0DIR &=~(BIT(LED_ID2_PORT_BIT));P0PU |= BIT(LED_ID2_PORT_BIT);
#define led_id2_set_port_on()		P01=ON_LEVEL
#define led_id2_set_port_off()		P01=OFF_LEVEL
#endif


#endif

//2MUTE_GPIO_CONFIG START

#if defined(MUTE_PORT_USE_DUMP)
#define mute_gpio_init() 			
#define mute_port_mute()			
#define mute_port_unmute()

#elif defined(MUTE_GPIO_USE_P27)
#define mute_gpio_init() 			P2DIR &= ~(BIT(7));P2PU |= (BIT(7))		
#define mute_port_mute()			P27  =MUTE_LEVEL		
#define mute_port_unmute()		P27  =UNMUTE_LEVEL
#elif defined(MUTE_GPIO_USE_P25)
#define MUTE_PORT_BIT		5
#define mute_gpio_init() 			P2DIR &= ~(BIT(MUTE_PORT_BIT));P2PU |= (BIT(MUTE_PORT_BIT))		
#define mute_port_mute()			P25  =MUTE_LEVEL		
#define mute_port_unmute()		P25  =UNMUTE_LEVEL
#elif defined(MUTE_GPIO_USE_P36)
#define MUTE_PORT_BIT		6
#define mute_gpio_init() 			P3DIR &= ~(BIT(MUTE_PORT_BIT));P3PU |= (BIT(MUTE_PORT_BIT))		
#define mute_port_mute()			P36  =MUTE_LEVEL		
#define mute_port_unmute()		P36  =UNMUTE_LEVEL
#elif defined(MUTE_GPIO_USE_P30)
#define MUTE_PORT_BIT		0
#define mute_gpio_init() 			P3DIR &= ~(BIT(MUTE_PORT_BIT));P3PU |= (BIT(MUTE_PORT_BIT))		
#define mute_port_mute()			P30  =MUTE_LEVEL		
#define mute_port_unmute()		P30  =UNMUTE_LEVEL
#elif defined(MUTE_GPIO_USE_P05)
#define mute_gpio_init() 			P0DIR &= ~(BIT(5));P0PU |= (BIT(5))		
#define mute_port_mute()			P05  =MUTE_LEVEL		
#define mute_port_unmute()		P05  =UNMUTE_LEVEL
#elif defined(MUTE_GPIO_USE_P03)
#define mute_gpio_init() 			P0DIR &= ~(BIT(3));P0PU |= (BIT(3))		
#define mute_port_mute()			P03  =MUTE_LEVEL		
#define mute_port_unmute()		P03  =UNMUTE_LEVEL
#elif defined(MUTE_GPIO_USE_P02)
#define MUTE_PORT_BIT		2
#define mute_gpio_init() 			P0DIR &= ~(BIT(MUTE_PORT_BIT));P0PU |= (BIT(MUTE_PORT_BIT))		
#define mute_port_mute()			P02  =MUTE_LEVEL		
#define mute_port_unmute()		P02  =UNMUTE_LEVEL
#elif defined(MUTE_GPIO_USE_P01)
#define mute_gpio_init() 			P0DIR &= ~(BIT(1));P0PU |= (BIT(1))		
#define mute_port_mute()			P01  =MUTE_LEVEL			
#define mute_port_unmute()		P01  =UNMUTE_LEVEL
#else
#define mute_gpio_init() 			
#define mute_port_mute()			
#define mute_port_unmute()
#endif

//2 MUTE_GPIO_CONFIG END


//2 KEY_GPIO_CONFIG START
#ifdef ADKEY_GPIO_USE_P07
#define ADC_CH_FOR_KEY		0xF7
#elif defined(ADKEY_GPIO_USE_P06)
#define ADC_CH_FOR_KEY		0xF6
#elif defined(ADKEY_GPIO_USE_P02)
#define ADC_CH_FOR_KEY		0xF2
#else
"ERROR : NO ADC KEY PORT DEFINE "
#endif
//2 KEY_GPIO_CONFIG END


//3  BAT_ ADC_CONFIG START

#ifdef USE_BAT_MANAGEMENT

#ifdef BAT_MEASURE_USE_ADC_PORT

#ifdef BAT_AD_GPIO_USE_P07
#define AD_CH_BAT_PORT		0xF7
#elif defined(BAT_AD_GPIO_USE_P06)
#define AD_CH_BAT_PORT		0xF6
#elif defined(BAT_AD_GPIO_USE_P05)
#define AD_CH_BAT_PORT		0xF5
#elif defined(BAT_AD_GPIO_USE_P02)
#define AD_CH_BAT_PORT		0xF2
#else
"ERROR : NO ADC  PORT DEFINE "
#endif

#endif



#endif
//2 BAT  ADC__CONFIG END


//2 AUX DETECTION_GPIO_CONFIG START
#ifdef AUX_DETECTION_THREAD_ENABLE

#define  AUX_INVALID_LEVEL				0

#ifdef AUX_DETECT_USE_P01
#define  aux_detect_gpio_init()      			P0DIR &=~(BIT(1));P01=1; P0DIR |= BIT(1);P0PU |= BIT(1);P0PD &=~(BIT(1))
#define  aux_detect_gpio_pin 		 			P01
#define  aux_detect_gpio_release()      		P0DIR &= ~(BIT(1)); //linein check port
#elif defined(AUX_DETECT_USE_P07)
#define  aux_detect_gpio_init()      			P0DIR &=~(BIT(7));P07=1; P0DIR |= BIT(7);P0PU |= BIT(7);
#define  aux_detect_gpio_pin 		 			P07
#define  aux_detect_gpio_release()      		P0DIR &= ~(BIT(7)); //linein check port
#elif defined(AUX_DETECT_USE_P04)
#define AUX_PORT_BIT		4
#define  aux_detect_gpio_init()      			P0DIR &=~(BIT(AUX_PORT_BIT));P04=1; P0DIR |= BIT(AUX_PORT_BIT);P0PU |= BIT(AUX_PORT_BIT);
#define  aux_detect_gpio_pin 		 			P04
#define  aux_detect_gpio_release()      		P0DIR &= ~(BIT(AUX_PORT_BIT)); //linein check port
#elif defined(AUX_DETECT_USE_P46)
#define  aux_detect_gpio_init()      			P4DIR &=~(BIT(6));P4|=(BIT(6)); P4DIR |= BIT(6);P4PU |= BIT(6);
#define  aux_detect_gpio_pin 		 			(P4&BIT(6))
#define  aux_detect_gpio_release()      		P4DIR &= ~(BIT(6)); //linein check port
#else
"ERROR : NO   PORT DEFINE "
#endif
#endif

//2 AUX DETECTION_CONFIG END


//3 PHONE DETECTION_GPIO_CONFIG START
#ifdef PHONE_DETECTION_THREAD_ENABLE

#define  PHONE_INVALID_LEVEL				0

#ifdef PHONE_DETECT_USE_P01
#define  phone_detect_gpio_init()      			P0DIR &=~(BIT(1));P01=1; P0DIR |= BIT(1);P0PU |= BIT(1);
#define  phone_detect_gpio_pin 		 		P01
#define  phone_detect_gpio_release()      		P0DIR &= ~(BIT(1)); //linein check port
#elif defined(PHONE_DETECT_USE_P04)
#define  phone_detect_gpio_init()      			P0DIR &=~(BIT(4));P04=1; P0DIR |= BIT(4);P0PU |= BIT(4);
#define  phone_detect_gpio_pin 		 		P04
#define  phone_detect_gpio_release()      		P0DIR &= ~(BIT(4)); //linein check port
#else
"ERROR : NO   PORT DEFINE "
#endif


#endif

//2 PHONE DETECTION_CONFIG END



//3 CHARGER DETECTION_GPIO_CONFIG START
#ifdef CHARGER_DETECTION_THREAD_ENABLE

#define  CHARGER_INVALID_LEVEL				1

#ifdef CHARGER_DETECT_USE_P01
#define  CHGR_PORT_BIT		1
#define  charger_detect_gpio_init()      			P0DIR &=~(BIT(CHGR_PORT_BIT));P01=~(CHARGER_INVALID_LEVEL); P0DIR |= BIT(CHGR_PORT_BIT);P0PU &=~(BIT(CHGR_PORT_BIT));P0PD |=(BIT(CHGR_PORT_BIT))
#define  charger_detect_gpio_pin 		 		P01
#define  charger_detect_gpio_release()      		P0DIR &= ~(BIT(CHGR_PORT_BIT)); //linein check port
#elif defined(CHARGER_DETECT_USE_P04)
#define  CHGR_PORT_BIT		4
#define  charger_detect_gpio_init()      			P0DIR &=~(BIT(1));P01=~(CHARGER_INVALID_LEVEL); P0DIR |= BIT(CHGR_PORT_BIT);P0PU &=~(BIT(CHGR_PORT_BIT));P0PD |=(BIT(CHGR_PORT_BIT))
#define  charger_detect_gpio_pin 		 		P04
#define  charger_detect_gpio_release()      		P0DIR &= ~(BIT(CHGR_PORT_BIT)); //linein check port
#elif defined(CHARGER_DETECT_USE_P17)
#define  CHGR_PORT_BIT		7
#define  charger_detect_gpio_init()      			P1DIR &=~(BIT(1));P17=~(CHARGER_INVALID_LEVEL); P1DIR |= BIT(CHGR_PORT_BIT);P1PU &=~(BIT(CHGR_PORT_BIT));P1PD |=(BIT(CHGR_PORT_BIT))
#define  charger_detect_gpio_pin 		 		P17
#define  charger_detect_gpio_release()      		P1DIR &= ~(BIT(CHGR_PORT_BIT)); //linein check port
#else
"ERROR : NO   PORT DEFINE "
#endif





#ifdef BAT_CHARGE_LED_IND_AT_P26
#define charger_led_ind_gpio_init() 			P2DIR &= ~(BIT(6));P2PU |= (BIT(6))		
#define charger_led_ind_gpio_on()		P26  =1		
#define charger_led_ind_gpio_off()		P26  =0
#elif defined(BAT_CHARGE_LED_IND_AT_P27)
#define charger_led_ind_gpio_init() 			P2DIR &= ~(BIT(7));P2PU |= (BIT(7))		
#define charger_led_ind_gpio_on()		P27  =1		
#define charger_led_ind_gpio_off()		P27  =0
#endif

#endif

//2 CHARGER DETECTION_CONFIG END





//2 IIC_GPIO_CONFIG START

#ifdef IIC_GPIO_CLK_DATA_USE_P00_P01

#define IIC_CLK_PIN			P00
#define IIC_DATA_PIN		P01
#define SET_IIC_CLK_OUT()	P0DIR &= ~(BIT(0));	
#define SET_IIC_DATA_OUT()	P0DIR &= ~(BIT(1));	
#define SET_IIC_DATA_IN()	P0DIR |=(BIT(1));	P0PU |= (BIT(1));
#elif defined(IIC_GPIO_CLK_DATA_USE_P01_P00)

#define IIC_CLK_PIN			P01
#define IIC_DATA_PIN		P00
#define SET_IIC_CLK_OUT()	P0DIR &= ~(BIT(1));	
#define SET_IIC_DATA_OUT()	P0DIR &= ~(BIT(0));	
#define SET_IIC_DATA_IN()	P0DIR |=(BIT(0));	P0PU |= (BIT(0));

#elif defined(IIC_GPIO_CLK_DATA_USE_P03_P02)
#define IIC_CLK_PIN			P03
#define IIC_DATA_PIN		P02
#define SET_IIC_CLK_OUT()	P0DIR &= ~(BIT(3));	
#define SET_IIC_DATA_OUT()	P0DIR &= ~(BIT(2));	
#define SET_IIC_DATA_IN()	P0DIR |=(BIT(2));	P0PU |= (BIT(2));
#elif defined(IIC_GPIO_CLK_DATA_USE_P02_P03)
#define IIC_CLK_PIN			P02
#define IIC_DATA_PIN		P03
#define SET_IIC_CLK_OUT()	P0DIR &= ~(BIT(2));	
#define SET_IIC_DATA_OUT()	P0DIR &= ~(BIT(3));	
#define SET_IIC_DATA_IN()	P0DIR |=(BIT(3));	P0PU |= (BIT(3));
#elif defined(IIC_GPIO_CLK_DATA_USE_P01_P26)

#define IIC_CLK_PIN			P01
#define IIC_DATA_PIN		P26
#define SET_IIC_CLK_OUT()	P0DIR &= ~(BIT(1));	
#define SET_IIC_DATA_OUT()	P2DIR &= ~(BIT(6));	
#define SET_IIC_DATA_IN()	P2DIR |=(BIT(6));	P2PU |= (BIT(6));
#elif defined(IIC_GPIO_CLK_DATA_DUMMY)
#define IIC_CLK_PIN			P00
#define IIC_DATA_PIN		P00
#define SET_IIC_CLK_OUT()	
#define SET_IIC_DATA_OUT()		
#define SET_IIC_DATA_IN()	
#else
"ERROR : NO IIC  PORT DEFINE "
#endif
//2 IIC_GPIO_CONFIG END


//2 POWER KEY_GPIO_CONFIG START
#ifdef USE_POWER_KEY
#if defined(POWER_CTRL_GPIO_USE_P02)
#define power_gpio_init() 			P0DIR &= ~(BIT(2));P0PU |= (BIT(2))		
#define power_port_on()			P02  =POWER_ON_LEVEL		
#define power_port_off()			P02  =POWER_OFF_LEVEL
#elif defined(POWER_CTRL_GPIO_USE_P01)
#define power_gpio_init() 			P0DIR &= ~(BIT(1));P0PU |= (BIT(1))		
#define power_port_on()			P01  =POWER_ON_LEVEL			
#define power_port_off()			P01  =POWER_OFF_LEVEL
#elif defined(POWER_CTRL_GPIO_USE_P05)
#define power_gpio_init() 			P0DIR &= ~(BIT(5));P0PU |= (BIT(5))		
#define power_port_on()			P05 =POWER_ON_LEVEL			
#define power_port_off()			P05  =POWER_OFF_LEVEL
#elif defined(POWER_CTRL_GPIO_USE_P01)
#define power_gpio_init() 			P0DIR &= ~(BIT(1));P0PU |= (BIT(1))		
#define power_port_on()			P01  =POWER_ON_LEVEL			
#define power_port_off()			P01  =POWER_OFF_LEVEL
#elif defined(POWER_CTRL_GPIO_USE_WAKEUP)
#define WKUP_PIN_USE_ENABLE
extern void wkup_pin_ctrl(bool dir);
#define power_gpio_init() 			
#define power_port_on()			wkup_pin_ctrl(POWER_ON_LEVEL)
#define power_port_off()			wkup_pin_ctrl(POWER_OFF_LEVEL)
#else
"ERROR : NO POWER CTRL GPIO DEFINE "
#endif
#endif
//2 POWER KEY_GPIO_CONFIG END


//2  LCD GPIO	START
#if 1
//´®¿Ú
#define LCD_DATA_OUT    P1DIR &= ~BIT(7); P1PU |= BIT(7)//7
#define	LCD_CLK_OUT	    P1DIR &= ~BIT(6); P1PU |= BIT(6)//6

//²¢¿Ú
#define LCD_DATA_OUT_PAR  P1DIR = 0x00;P1PU = 0xff;P1= 0XFF
#define LCD_CMD_OUT_PAR	  P3DIR &= ~0X1E;P3PU |= 0x1E;P3 |= 0X1E


#define LCDPORT_OUT()     LCD_DATA_OUT;LCD_CLK_OUT;LCD_A0_OUT;LCD_RES_OUT;LCD_CS_OUT
#define LCDPORT_H()       P1 |= ( BIT(7)|BIT(6) );LCD_A0_H; LCD_RES_H;/**/	LCD_CS_H

#define LCDPORT_OUT_PAR()   LCD_WR_OUT;LCD_DATA_OUT_PAR;LCD_CMD_OUT_PAR
#define LCDPORT_H_PAR()     P1 = 0xff; LCD_A0_H; /*LCD_RES_H;*/LCD_CS_H;LCD_WR_H

#define LCD_WR_OUT	  P3DIR &= ~BIT(3);P3PU |= BIT(3)
#define LCD_WR_L	  P33 = 0
#define LCD_WR_H	  P33 = 1


#define	LCD_A0_OUT	  P3DIR &= ~BIT(2);P3PU |= BIT(2)
#define	LCD_A0_L	  P32 = 0
#define	LCD_A0_H	  P32 = 1

#define LCD_RES_OUT	  P3DIR &= ~BIT(4);P3PU |= BIT(4)
#define LCD_RES_L	  P34=  0
#define LCD_RES_H	  P34 = 1

#define LCD_CS_OUT	  P3DIR &= ~BIT(1);P3PU |= BIT(1)
#define LCD_CS_L	  P31 = 0
#define LCD_CS_H	  P31 = 1
#endif
//2  LCD GPIO END


#ifdef BLUE_TOOTH_STATUS_LED_AT_P16
#define BT_S_PORT_BIT		6
#define BLUE_TOOTH_STATUS_LED_INIT()		P1DIR &= ~BIT(BT_S_PORT_BIT);P1PU |= BIT(BT_S_PORT_BIT);P16 = 0
#define BLUE_TOOTH_STATUS_LED_ON()		P16 = 0
#define BLUE_TOOTH_STATUS_LED_OFF()		P16 = 1
#elif defined( BLUE_TOOTH_STATUS_LED_AT_P17)
#define BT_S_PORT_BIT		7
#define BLUE_TOOTH_STATUS_LED_INIT()		P1DIR &= ~BIT(BT_S_PORT_BIT);P1PU |= BIT(BT_S_PORT_BIT);P17 = 0
#define BLUE_TOOTH_STATUS_LED_ON()		P17	= 0
#define BLUE_TOOTH_STATUS_LED_OFF()		P17  = 1
#elif defined(BLUE_TOOTH_STATUS_LED_AT_P00)
#define BT_S_PORT_BIT		0
#define BLUE_TOOTH_STATUS_LED_INIT()		P0DIR &= ~BIT(BT_S_PORT_BIT);P0PU |= BIT(BT_S_PORT_BIT);P00 = 0
#define BLUE_TOOTH_STATUS_LED_ON()		P00= 0
#define BLUE_TOOTH_STATUS_LED_OFF()		P00 = 1
#elif defined(BLUE_TOOTH_STATUS_LED_AT_P04)
#define BT_S_PORT_BIT		4
#define BLUE_TOOTH_STATUS_LED_INIT()		P0DIR &= ~BIT(BT_S_PORT_BIT);P0PU |= BIT(BT_S_PORT_BIT);P04 = 0
#define BLUE_TOOTH_STATUS_LED_ON()		P04= 0
#define BLUE_TOOTH_STATUS_LED_OFF()		P04 = 1
#elif defined(BLUE_TOOTH_STATUS_LED_AT_P05)
#define BT_S_PORT_BIT		5
#define BLUE_TOOTH_STATUS_LED_INIT()		P0DIR &= ~BIT(BT_S_PORT_BIT);P0PU |= BIT(BT_S_PORT_BIT);P05 = 1
#define BLUE_TOOTH_STATUS_LED_ON()		P05= 0
#define BLUE_TOOTH_STATUS_LED_OFF()		P05 = 1
#elif defined(BLUE_TOOTH_STATUS_LED_AT_P46)
#define BT_S_PORT_BIT		4
#define BLUE_TOOTH_STATUS_LED_INIT()		P0DIR &= ~BIT(BT_S_PORT_BIT);P0PU |= BIT(BT_S_PORT_BIT);P4 &=~(BIT(BT_S_PORT_BIT));
#define BLUE_TOOTH_STATUS_LED_ON()		P4 &=~(BIT(BT_S_PORT_BIT));
#define BLUE_TOOTH_STATUS_LED_OFF()		P4 |=(BIT(BT_S_PORT_BIT));
#else
#define BLUE_TOOTH_STATUS_LED_INIT()	
#define BLUE_TOOTH_STATUS_LED_ON()	
#define BLUE_TOOTH_STATUS_LED_OFF()	
#endif

#ifdef BLUE_TOOTH_CALL_STATUS_AT_P16
#define BT_CS_PORT_BIT		6
#define BLUE_TOOTH_CALL_STATUS_ON()		P1DIR &= ~BIT(BT_CS_PORT_BIT);P1PU |= BIT(BT_CS_PORT_BIT);P16 = 0
#define BLUE_TOOTH_CALL_STATUS_OFF()		P1DIR &= ~BIT(BT_CS_PORT_BIT);P1PU |= BIT(BT_CS_PORT_BIT);P16 = 1
#else
#define BLUE_TOOTH_CALL_STATUS_ON()	
#define BLUE_TOOTH_CALL_STATUS_OFF()	
#endif


#ifdef BLUE_TOOTH_GPIO_PWR_AT_P16
#define BLUE_TOOTH_PWR_ON()		P1DIR &= ~BIT(6);P1PU |= BIT(6);P16 = 1
#define BLUE_TOOTH_PWR_OFF()		P1DIR &= ~BIT(6);P1PU |= BIT(6);P16 = 0
#elif defined(BLUE_TOOTH_GPIO_PWR_AT_P36)
#define BLUE_TOOTH_PWR_ON()		P3DIR &= ~BIT(6);P3PU |= BIT(6);P36 = 1
#define BLUE_TOOTH_PWR_OFF()		P3DIR &= ~BIT(6);P3PU |= BIT(6);P36 = 0
#elif defined(BLUE_TOOTH_GPIO_PWR_AT_P01)
#define BLUE_TOOTH_PWR_ON()		P0DIR &= ~BIT(1);P0PU |= BIT(1);P01 = 1
#define BLUE_TOOTH_PWR_OFF()		P0DIR &= ~BIT(1);P0PU |= BIT(1);P01 = 0
#else
#define BLUE_TOOTH_PWR_ON()	
#define BLUE_TOOTH_PWR_OFF()	
#endif

#ifdef BLUE_TOOTH_AUX_FUNC_ENABLE
#ifdef BLUE_TOOTH_AUX_FUNC_GPIO_AT_P37
#define BT_AUX_PORT_BIT		7
#define BLUE_TOOTH_AUX_MODE()				P3DIR &= ~BIT(BT_AUX_PORT_BIT);P3PU |= BIT(BT_AUX_PORT_BIT);P37 = 0
#define BLUE_TOOTH_AUX_MODE_RELEASE()	P3DIR &= ~BIT(BT_AUX_PORT_BIT);P3PU |= BIT(BT_AUX_PORT_BIT);P37 = 1
#endif
#endif


#ifdef AMP_GPIO_SEL_AB_D_MODE

#define AMP_AB_MODE_LOGIC		1
#define AMP_D_MODE_LOGIC		0

#ifdef AMP_GPIO_SEL_AB_D_MODE_AT_P37
#define AMP_PORT_BIT		7

#define AMP_GPIO_SEL_AB_MODE()		P3DIR &= ~BIT(AMP_PORT_BIT);P3PU |= BIT(AMP_PORT_BIT);P37 = AMP_AB_MODE_LOGIC
#define AMP_GPIO_SEL_D_MODE()			P3DIR &= ~BIT(AMP_PORT_BIT);P3PU |= BIT(AMP_PORT_BIT);P37 = AMP_D_MODE_LOGIC
#elif defined(AMP_GPIO_SEL_AB_D_MODE_AT_P36)

#define AMP_PORT_BIT		6

#define AMP_GPIO_SEL_AB_MODE()		P3DIR &= ~BIT(AMP_PORT_BIT);P3PU |= BIT(AMP_PORT_BIT);P36 = AMP_AB_MODE_LOGIC
#define AMP_GPIO_SEL_D_MODE()			P3DIR &= ~BIT(AMP_PORT_BIT);P3PU |= BIT(AMP_PORT_BIT);P36 = AMP_D_MODE_LOGIC

#elif defined(AMP_GPIO_SEL_AB_D_MODE_AT_P46)

#define AMP_PORT_BIT		6

#if AMP_AB_MODE_LOGIC
#define AMP_GPIO_SEL_AB_MODE()		P4DIR &=~(BIT(AMP_PORT_BIT));P4PU |= BIT(AMP_PORT_BIT);P4|=(BIT(AMP_PORT_BIT))
#define AMP_GPIO_SEL_D_MODE()			P4DIR &=~(BIT(AMP_PORT_BIT));P4PU |= BIT(AMP_PORT_BIT);P4&=~(BIT(AMP_PORT_BIT))
#else
#define AMP_GPIO_SEL_AB_MODE()		P4DIR &=~(BIT(AMP_PORT_BIT));P4PU |= BIT(AMP_PORT_BIT);P4&=~(BIT(AMP_PORT_BIT))
#define AMP_GPIO_SEL_D_MODE()			P4DIR &=~(BIT(AMP_PORT_BIT));P4PU |= BIT(AMP_PORT_BIT);P4|=(BIT(AMP_PORT_BIT))
#endif

#elif defined(AMP_GPIO_SEL_AB_D_MODE_AT_P01)

#define AMP_PORT_BIT		1

#define AMP_GPIO_SEL_AB_MODE()		P0DIR &= ~BIT(AMP_PORT_BIT);P0PU |= BIT(AMP_PORT_BIT);P01 = AMP_AB_MODE_LOGIC
#define AMP_GPIO_SEL_D_MODE()		P0DIR &= ~BIT(AMP_PORT_BIT);P0PU |= BIT(AMP_PORT_BIT);P01 = AMP_D_MODE_LOGIC
#else
"#ERROR   NO AMP_PORT   DEFINE "
#endif

#endif


















//1 FUNCTION PREDEFINE

#ifdef AUX_DETECTION_THREAD_ENABLE
void aux_detect_init(void);
bool aux_detect_level(void);
void aux_detect_release(void);
bool aux_gpio_protect(void);
#endif


#ifdef PHONE_DETECTION_THREAD_ENABLE
void phone_detect_init(void);
bool phone_detect_level(void);
void phone_detect_release(void);
bool phone_gpio_protect(void);

#define EVENT_50MS_HANDLER_ENABLE

#endif


#ifdef CHARGER_DETECTION_THREAD_ENABLE
void charger_detect_init(void);
bool charger_detect_level(void);
void charger_detect_release(void);
bool charger_gpio_protect(void);
#endif


#ifdef USE_POWER_KEY
void sys_gpio_ctrl_pwr(SYS_PWR_HDLR ctrl_level);
#endif
#endif

#endif
