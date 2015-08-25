/*--------------------------------------------------------------------------*/
/**@file     gpio_if.h
   @brief    gpio if
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _GPIO_IF_H_
#define _GPIO_IF_H_

#include "Custom_config.h"

// msgfor_hot.c
#ifdef MUTE_CTRL_LEVEL_NORMAL
#define MUTE_LEVEL		1
#define UNMUTE_LEVEL	0
#else
#define MUTE_LEVEL		0
#define UNMUTE_LEVEL	1
#endif

#if defined(MUTE_PORT_USE_DUMP)
#define INIT_MUTE_PORT()		
#define AMP_MUTE_ENABLE()			
#define AMP_MUTE_DISABLE()	
#elif defined(MUTE_PORT_USE_P01)
#define INIT_MUTE_PORT()			P0DIR &= ~(BIT(1));P0PU |= BIT(1)
#define AMP_MUTE_ENABLE()			P01  =MUTE_LEVEL
#define AMP_MUTE_DISABLE()			P01  =UNMUTE_LEVEL
#elif defined(MUTE_PORT_USE_WKUP)
//dummy
#elif defined(MUTE_PORT_USE_P00)
#define INIT_MUTE_PORT()			P0DIR &= ~(BIT(0));P0PU |= (BIT(0))
#define AMP_MUTE_ENABLE()			P00  =MUTE_LEVEL
#define AMP_MUTE_DISABLE()			P00  =UNMUTE_LEVEL
#elif defined(MUTE_PORT_USE_P03)
#define INIT_MUTE_PORT()			P0DIR &= ~(BIT(3));P0PU |= (BIT(3))
#define AMP_MUTE_ENABLE()			P03  =MUTE_LEVEL
#define AMP_MUTE_DISABLE()			P03  =UNMUTE_LEVEL
#elif defined(MUTE_PORT_USE_P04)
#define INIT_MUTE_PORT()			P0DIR &= ~(BIT(4));P0PU |= (BIT(4))
#define AMP_MUTE_ENABLE()			P04  =MUTE_LEVEL
#define AMP_MUTE_DISABLE()			P04  =UNMUTE_LEVEL
#elif defined(MUTE_PORT_USE_P17)
#define INIT_MUTE_PORT()			P1DIR &= ~(BIT(7));P1PU |= (BIT(7))
#define AMP_MUTE_ENABLE()			P17  =MUTE_LEVEL
#define AMP_MUTE_DISABLE()			P17  =UNMUTE_LEVEL
#endif


//4 ----- IIC ¡£H
#if defined(IIC_GPIO_USE_P02_P03)
#define iic_data_out()    P0DIR &= ~(1<<2);P0PU |= (1<<2)
#define iic_data_in()     P0DIR |= (1<<2);P0PU |= (1<<2)
#define iic_data_r()      P02
#define iic_data_h()      P02 = 1
#define iic_data_l()      P02 = 0

#define iic_clk_out()    P0DIR &= ~(1<<3);P0PU |= (1<<3)
#define iic_clk_h()      P03 = 1
#define iic_clk_l()      P03 = 0
#elif defined(IIC_GPIO_USE_P00_P01)
#define iic_data_out()    P0DIR &= ~(BIT(1));P0PU |= BIT(1) 	
#define iic_data_in()     P0DIR |= (BIT(1));P0PU |= BIT(1)	
#define iic_data_r()      P01
#define iic_data_h()      P01 = 1
#define iic_data_l()      P01 = 0

#define iic_clk_out()    P0DIR &= ~(BIT(0));P0PU |= (BIT(0))
#define iic_clk_h()      P00 = 1
#define iic_clk_l()      P00 = 0
#endif

#if defined(AUX_DETECT_USE_P02)
#define  aux_detect_in()      P0DIR &= ~(BIT(2)); P02=1; P0DIR |= BIT(2);P0PU |= BIT(2);//linein check port
#define  AUX_DETECT_GPIO  P02
#define  aux_detect_in_off()        P0DIR &= ~(BIT(2));P02=1;  //linein check port
#elif defined(AUX_DETECT_USE_P04)
#define  aux_detect_in()      P0DIR &= ~(BIT(4)); P04=1; P0DIR |= BIT(4);P0PU |= BIT(4);//linein check port
#define  AUX_DETECT_GPIO  P04
#define  aux_detect_in_off()        P0DIR &= ~(BIT(4));P04=1;  //linein check port
#elif defined(AUX_DETECT_USE_P03)
#define  aux_detect_in()      P0DIR &= ~(BIT(3)); P03=1; P0DIR |= BIT(3);P0PU |= BIT(3);//linein check port
#define  AUX_DETECT_GPIO  P03
#define  aux_detect_in_off()        P0DIR &= ~(BIT(3));P03=1;  //linein check port
#elif defined(AUX_DETECT_USE_P07)
#define  aux_detect_in()      P0DIR |= BIT(7);P0PU |= BIT(7);//linein check port
#define  AUX_DETECT_GPIO  P07
#define  aux_detect_in_off()        P0DIR &= ~(BIT(7)); //linein check port
#elif defined(AUX_DETECT_USE_P06)
#define  aux_detect_in()      		P0DIR |= BIT(6);P0PU |= BIT(6);//linein check port
#define  AUX_DETECT_GPIO  		P06
#define  aux_detect_in_off()        	P0DIR &= ~(BIT(6)); //linein check port
#elif defined(AUX_DETECT_USE_P01)
#define  aux_detect_in()      		P0DIR |= BIT(1);P0PU |= BIT(1);//linein check port
#define  AUX_DETECT_GPIO  		P01
#define  aux_detect_in_off()        P0DIR &= ~(BIT(1)); //linein check port
#else
#define  aux_detect_in()					
#define  AUX_DETECT_GPIO
#define  aux_detect_in_off()
#endif


//4 ----- LCD ¡£H

#define LCD_BL_INIT()	P1DIR &= ~(BIT(0));P1PU |=BIT(0); P1|=(BIT(0))
#define LCD_BL_GPIO_H()	P1|=(BIT(0))
#define LCD_BL_GPIO_L()	P1&=~(BIT(0))

#define LCDPORT_OUT()  LCD_DATA_OUT;LCD_CLK_OUT;LCD_A0_OUT;LCD_RES_OUT;LCD_CS_OUT;//P1DIR &= ~( BIT(7)|BIT(6) );P3DIR &= ~( BIT(0) | BIT(1) | BIT(2) ) 
#define LCDPORT_H()    P1 |= ( BIT(7)|BIT(6) );LCD_A0_H;  LCD_RES_H;	LCD_CS_H;

#define LCD_DATA_OUT P1DIR &= ~(BIT(7));P1PU |= BIT(7)//7 
#define	LCD_CLK_OUT	 P1DIR &= ~(BIT(6));P1PU |= BIT(6)//6

#define	LCD_A0_OUT	  P1DIR &= ~(BIT(3));P1PU |= BIT(3)
#define	LCD_A0_L	  P13 = 0      //P0 &= ~BIT(5)
#define	LCD_A0_H	  P13 = 1      //P0 |= BIT(5)

#define LCD_RES_OUT	  P1DIR &= ~(BIT(2));
#define LCD_RES_L	  P12 = 0      //P3 &= ~BIT(2)
#define LCD_RES_H	  P12 = 1      //P3 |= BIT(2)

#define LCD_CS_OUT	  P1DIR &= ~(BIT(1));P1PU |= BIT(1)
#define LCD_CS_L	  P11 = 0      //P0 &= ~BIT(4)
#define LCD_CS_H	  P11 = 1      //P0 |= BIT(4)


#define SPIDMAISRDIS()  IE1 &= ~(BIT(3))
#define SPIDMAISREN()	IP1 |= BIT(3), IE1 |= BIT(3)

//4 ----- KEY ¡£H

#define ADC_KEY_IO6    0xfe
#define ADC_KEY_IO7    0xff
#define ADC_KEY_IO5    0xfd
#define ADC_KEY_IO2    0xfa
#define ADC_VDD_12     0xf8
#define ADC_LDOIN      0xf9
#define ADC_MAX_USED   0x03


#define OC_SRC_GPIO_INIT()		P0DIR &= ~(BIT(4));P0PU |=BIT(4);
#define SRC_OPT_EN()		P0|=(BIT(4))
#define SRC_COA_EN()		P0&=~(BIT(4))

#define HDMI_SRC_GPIO_INIT()		P3DIR &= ~(BIT(4));P3PU |=BIT(4); 
#define SRC_HDMI_1_EN()		P3|=(BIT(4))
#define SRC_HDMI_2_EN()		P3&=~(BIT(4))

#endif
