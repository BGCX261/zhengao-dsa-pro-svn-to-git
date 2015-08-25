/*******************************************************************************************
File Name:  IRFF00.h

Version:    1.00

Discription: 红外按键表 0xFF00

Author:     Caibingquan

Email:      change.tsai@gmail.com

Date:       2012.06.04

Copyright:(c) 2012 , All Rights Reserved.
*******************************************************************************************/
#include "custom_config.h"
#ifndef	_AD_KEY_H_
#define _AD_KEY_H_
#include "my_adkey.h"

/*-----------FPGA use-------------------*/
#define AD_VDD      (u16)0xff80
#define AD_VOL1     (u16)0xc8c0
#define AD_VOL2     (u16)0x9680
#define AD_VOL3     (u16)0x6440
#define AD_VOL4     (u16)0x3200
#define AD_GND      (u16)0x0000

//#define AD_NOKEY    ((((u16)AD_VDD - AD_VOL1)>>1) + AD_VOL1)
#define AD_KEY1     ((((u16)AD_VOL1 - AD_VOL2)>>1) + AD_VOL2)
#define AD_KEY2     ((((u16)AD_VOL2 - AD_VOL3)>>1) + AD_VOL3)
#define AD_KEY3     ((((u16)AD_VOL3 - AD_VOL4)>>1) + AD_VOL4)
#define AD_KEY4     ((((u16)AD_VOL4 - AD_GND)>>1) + AD_GND)


/*-------------ADKEY GROUP 1----------------*/
#if defined( CUSTOMER_DEFINED_ADKEY_RESISTOR)

#if defined(NEW_RES_VALUE_CACULATING)

#if defined( K000_TC_901_V001)
#define RES_PULL_UP			3300		/// 3.3K
#define RES_1				0
#define RES_2				2000
#define RES_3				3900	
#define RES_4				6800
#define RES_5				12000
#define RES_6				20000
#define RES_7				30000
#define RES_8				100000
#define RES_9				100000
#define RES_10				100000
#else
#define RES_PULL_UP			3300		/// 3.3K
#define RES_1				0
#define RES_2				470
#define RES_3				1000	
#define RES_4				2000
#define RES_5				3300
#define RES_6				5600
#define RES_7				10000
#define RES_8				33000
#define RES_9				33000
#define RES_10				33000
#endif

#define ADKEY1_8			(((255*RES_2)/(RES_2+RES_PULL_UP)+(255*RES_1)/(RES_1+RES_PULL_UP))/2)
#define ADKEY1_7			(((255*RES_3)/(RES_3+RES_PULL_UP)+(255*RES_2)/(RES_2+RES_PULL_UP))/2)	
#define ADKEY1_6			(((255*RES_4)/(RES_4+RES_PULL_UP)+(255*RES_3)/(RES_3+RES_PULL_UP))/2)	
#define ADKEY1_5			(((255*RES_5)/(RES_5+RES_PULL_UP)+(255*RES_4)/(RES_4+RES_PULL_UP))/2)
#define ADKEY1_4			(((255*RES_6)/(RES_6+RES_PULL_UP)+(255*RES_5)/(RES_5+RES_PULL_UP))/2)
#define ADKEY1_3			(((255*RES_7)/(RES_7+RES_PULL_UP)+(255*RES_6)/(RES_6+RES_PULL_UP))/2)
#define ADKEY1_2			(((255*RES_8)/(RES_8+RES_PULL_UP)+(255*RES_7)/(RES_7+RES_PULL_UP))/2)
#define ADKEY1_1			(((255*RES_9)/(RES_9+RES_PULL_UP)+(255*RES_8)/(RES_8+RES_PULL_UP))/2)
#define ADKEY1_0			(((255*RES_10)/(RES_10+RES_PULL_UP)+(255*RES_9)/(RES_9+RES_PULL_UP))/2)
#define AD_NOKEY			(0xFA)

#endif

#else

#define AD_NOKEY		(0xff40-0xe840)/2+0xe840
#define ADKEY1_0		(0xe800-0xd1c0)/2+0xd1c0
#define ADKEY1_1		(0xd140-0xb2c0)/2+0xb2c0
#define ADKEY1_2		(0xb2c0-0x99c0)/2+0x99c0
#define ADKEY1_3		(0x9980-0x85c0)/2+0x85c0
#define ADKEY1_4		(0x8540-0x67c0)/2+0x67c0
#define ADKEY1_5		(0x66c0-0x4ac0)/2+0x4ac0
#define ADKEY1_6		(0x49c0-0x3740)/2+0x3740
#define ADKEY1_7		(0x3700-0x1e80)/2+0x1e80
#define ADKEY1_8		(0x1e40-0x0)/2+0x0

#endif

const u16 ad_key_table[] AT (TABLE_CODE)=
{
    ADKEY1_0,ADKEY1_1,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8
};


#define ADKEY1_MUSIC_SHORT		\
                                				/*00*/    MUSIC_ADKEY_SHORT_00,\
							    	/*01*/    MUSIC_ADKEY_SHORT_01,\
								/*02*/    MUSIC_ADKEY_SHORT_02,\
								/*03*/    MUSIC_ADKEY_SHORT_03,\
								/*04*/    MUSIC_ADKEY_SHORT_04,\
								/*05*/    MUSIC_ADKEY_SHORT_05,\
								/*06*/    MUSIC_ADKEY_SHORT_06,\
								/*07*/    MUSIC_ADKEY_SHORT_07,\
								/*08*/    MUSIC_ADKEY_SHORT_08,\
								/*09*/    MUSIC_ADKEY_SHORT_09,

#define ADKEY1_MUSIC_LONG		\
                                				/*00*/    MUSIC_ADKEY_LONG_00,\
                                				/*01*/    MUSIC_ADKEY_LONG_01,\
								/*02*/    MUSIC_ADKEY_LONG_02,\
								/*03*/    MUSIC_ADKEY_LONG_03,\
								/*04*/    MUSIC_ADKEY_LONG_04,\
								/*05*/    MUSIC_ADKEY_LONG_05,\
								/*06*/    MUSIC_ADKEY_LONG_06,\
								/*07*/    MUSIC_ADKEY_LONG_07,\
								/*08*/    MUSIC_ADKEY_LONG_08,\
								/*09*/    MUSIC_ADKEY_LONG_09,


#define ADKEY1_MUSIC_HOLD		\
                                				/*00*/    MUSIC_ADKEY_HOLD_00,\
                                				/*01*/    MUSIC_ADKEY_HOLD_01,\
								/*02*/    MUSIC_ADKEY_HOLD_02,\
								/*03*/    MUSIC_ADKEY_HOLD_03,\
								/*04*/    MUSIC_ADKEY_HOLD_04,\
								/*05*/    MUSIC_ADKEY_HOLD_05,\
								/*06*/    MUSIC_ADKEY_HOLD_06,\
								/*07*/    MUSIC_ADKEY_HOLD_07,\
								/*08*/    MUSIC_ADKEY_HOLD_08,\
								/*09*/    MUSIC_ADKEY_HOLD_09,

#define ADKEY1_MUSIC_LONG_UP	\
                                				/*00*/    MUSIC_ADKEY_L_UP_00,\
                                				/*01*/    MUSIC_ADKEY_L_UP_01,\
								/*02*/    MUSIC_ADKEY_L_UP_02,\
								/*03*/    MUSIC_ADKEY_L_UP_03,\
								/*04*/    MUSIC_ADKEY_L_UP_04,\
								/*05*/    MUSIC_ADKEY_L_UP_05,\
								/*06*/    MUSIC_ADKEY_L_UP_06,\
								/*07*/    MUSIC_ADKEY_L_UP_07,\
								/*08*/    MUSIC_ADKEY_L_UP_08,\
								/*09*/    MUSIC_ADKEY_L_UP_09,

const u8 adkey_msg_music_table[3][10] AT (TABLE_CODE)=				//Music模式下的遥控转换表
{
    /*短按*/	    	{ADKEY1_MUSIC_SHORT},
    /*长按*/		{ADKEY1_MUSIC_LONG},
    /*连按*/		{ADKEY1_MUSIC_HOLD},
    ///*长按抬起*/	{ADKEY1_MUSIC_LONG_UP},
};

#define ADKEY1_FM_SHORT			\
								/*00*/    FM_ADKEY_SHORT_00,\
							    	/*01*/    FM_ADKEY_SHORT_01,\
								/*02*/    FM_ADKEY_SHORT_02,\
								/*03*/    FM_ADKEY_SHORT_03,\
								/*04*/    FM_ADKEY_SHORT_04,\
								/*05*/    FM_ADKEY_SHORT_05,\
								/*06*/    FM_ADKEY_SHORT_06,\
								/*07*/    FM_ADKEY_SHORT_07,\
								/*08*/    FM_ADKEY_SHORT_08,\
								/*09*/    FM_ADKEY_SHORT_09,

#define ADKEY1_FM_LONG			\
								/*00*/    FM_ADKEY_LONG_00,\
                               	 			/*01*/    FM_ADKEY_LONG_01,\
								/*02*/    FM_ADKEY_LONG_02,\
								/*03*/    FM_ADKEY_LONG_03,\
								/*04*/    FM_ADKEY_LONG_04,\
								/*05*/    FM_ADKEY_LONG_05,\
								/*06*/    FM_ADKEY_LONG_06,\
								/*07*/    FM_ADKEY_LONG_07,\
								/*08*/    FM_ADKEY_LONG_08,\
								/*09*/    FM_ADKEY_LONG_09,

#define ADKEY1_FM_HOLD			\
								/*00*/    FM_ADKEY_HOLD_00,\
                                				/*01*/    FM_ADKEY_HOLD_01,\
								/*02*/    FM_ADKEY_HOLD_02,\
								/*03*/    FM_ADKEY_HOLD_03,\
								/*04*/    FM_ADKEY_HOLD_04,\
								/*05*/    FM_ADKEY_HOLD_05,\
								/*06*/    FM_ADKEY_HOLD_06,\
								/*07*/    FM_ADKEY_HOLD_07,\
								/*08*/    FM_ADKEY_HOLD_08,\
								/*09*/    FM_ADKEY_HOLD_09,


#define ADKEY1_FM_LONG_UP		\
								/*00*/    FM_ADKEY_L_UP_00,\
                                				/*01*/    FM_ADKEY_L_UP_01,\
								/*02*/    FM_ADKEY_L_UP_02,\
								/*03*/    FM_ADKEY_L_UP_03,\
								/*04*/    FM_ADKEY_L_UP_04,\
								/*05*/    FM_ADKEY_L_UP_05,\
								/*06*/    FM_ADKEY_L_UP_06,\
								/*07*/    FM_ADKEY_L_UP_07,\
								/*08*/    FM_ADKEY_L_UP_08,\
								/*09*/    FM_ADKEY_L_UP_09,

const u8 adkey_msg_fm_table[3][10] AT (TABLE_CODE)=				//Music模式下的遥控转换表
{
    /*短按*/	    	{ADKEY1_FM_SHORT},
    /*长按*/		{ADKEY1_FM_LONG},
    /*连按*/		{ADKEY1_FM_HOLD},
    ///*长按抬起*/	{ADKEY1_FM_LONG_UP},
};


#endif /*   _AD_KEY_H_  */
