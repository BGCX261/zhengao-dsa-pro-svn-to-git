/*******************************************************************************************
File Name:  IRFF00.h

Version:    1.00

Discription: 红外按键表 0xFF00

Author:     Caibingquan

Email:      change.tsai@gmail.com

Date:       2012.06.04

Copyright:(c) 2012 , All Rights Reserved.
*******************************************************************************************/
#ifndef	_IRFF00_H_
#define _IRFF00_H_

#include "my_irkey_tab.h"


#define IRFF00_MUSIC_SHORT		\
                                                        /*00*/    MUSIC_IRKEY_SHORT_00,\
							       /*01*/    MUSIC_IRKEY_SHORT_01,\
								/*02*/    MUSIC_IRKEY_SHORT_02,\
								/*03*/    MUSIC_IRKEY_SHORT_03,\
								/*04*/    MUSIC_IRKEY_SHORT_04,\
								/*05*/    MUSIC_IRKEY_SHORT_05,\
								/*06*/    MUSIC_IRKEY_SHORT_06,\
								/*07*/    MUSIC_IRKEY_SHORT_07,\
								/*08*/    MUSIC_IRKEY_SHORT_08,\
								/*09*/    MUSIC_IRKEY_SHORT_09,\
                                                        /*10*/    MUSIC_IRKEY_SHORT_10,\
								/*11*/    MUSIC_IRKEY_SHORT_11,\
								/*12*/    MUSIC_IRKEY_SHORT_12,\
								/*13*/    MUSIC_IRKEY_SHORT_13,\
								/*14*/    MUSIC_IRKEY_SHORT_14,\
								/*15*/    MUSIC_IRKEY_SHORT_15,\
								/*16*/    MUSIC_IRKEY_SHORT_16,\
								/*17*/    MUSIC_IRKEY_SHORT_17,\
								/*18*/    MUSIC_IRKEY_SHORT_18,\
								/*19*/    MUSIC_IRKEY_SHORT_19,\
								/*20*/    MUSIC_IRKEY_SHORT_20

#define IRFF00_MUSIC_LONG		\
                                                        /*00*/    MUSIC_IRKEY_LONG_00,\
                                                        /*01*/    MUSIC_IRKEY_LONG_01,\
								/*02*/    MUSIC_IRKEY_LONG_02,\
								/*03*/    MUSIC_IRKEY_LONG_03,\
								/*04*/    MUSIC_IRKEY_LONG_04,\
								/*05*/    MUSIC_IRKEY_LONG_05,\
								/*06*/    MUSIC_IRKEY_LONG_06,\
								/*07*/    MUSIC_IRKEY_LONG_07,\
								/*08*/    MUSIC_IRKEY_LONG_08,\
								/*09*/    MUSIC_IRKEY_LONG_09,\
                                                       /*10*/     MUSIC_IRKEY_LONG_10,\
								/*11*/    MUSIC_IRKEY_LONG_11,\
								/*12*/    MUSIC_IRKEY_LONG_12,\
								/*13*/    MUSIC_IRKEY_LONG_13,\
								/*14*/    MUSIC_IRKEY_LONG_14,\
								/*15*/    MUSIC_IRKEY_LONG_15,\
								/*16*/    MUSIC_IRKEY_LONG_16,\
								/*17*/    MUSIC_IRKEY_LONG_17,\
								/*18*/    MUSIC_IRKEY_LONG_18,\
								/*19*/    MUSIC_IRKEY_LONG_19,\
								/*20*/    MUSIC_IRKEY_LONG_20

#define IRFF00_MUSIC_HOLD		\
                                                         /*00*/    MUSIC_IRKEY_HOLD_00,\
                                                         /*01*/    MUSIC_IRKEY_HOLD_01,\
								/*02*/    MUSIC_IRKEY_HOLD_02,\
								/*03*/    MUSIC_IRKEY_HOLD_03,\
								/*04*/    MUSIC_IRKEY_HOLD_04,\
								/*05*/    MUSIC_IRKEY_HOLD_05,\
								/*06*/    MUSIC_IRKEY_HOLD_06,\
								/*07*/    MUSIC_IRKEY_HOLD_07,\
								/*08*/    MUSIC_IRKEY_HOLD_08,\
								/*09*/    MUSIC_IRKEY_HOLD_09,\
                                                       /*10*/     MUSIC_IRKEY_HOLD_10,\
								/*11*/    MUSIC_IRKEY_HOLD_11,\
								/*12*/    MUSIC_IRKEY_HOLD_12,\
								/*13*/    MUSIC_IRKEY_HOLD_13,\
								/*14*/    MUSIC_IRKEY_HOLD_14,\
								/*15*/    MUSIC_IRKEY_HOLD_15,\
								/*16*/    MUSIC_IRKEY_HOLD_16,\
								/*17*/    MUSIC_IRKEY_HOLD_17,\
								/*18*/    MUSIC_IRKEY_HOLD_18,\
								/*19*/    MUSIC_IRKEY_HOLD_19,\
								/*20*/    MUSIC_IRKEY_HOLD_20


#define IRFF00_MUSIC_LONG_UP	\
                                                        /*00*/    MUSIC_IRKEY_L_UP_00,\
                                                        /*01*/    MUSIC_IRKEY_L_UP_01,\
								/*02*/    MUSIC_IRKEY_L_UP_02,\
								/*03*/    MUSIC_IRKEY_L_UP_03,\
								/*04*/    MUSIC_IRKEY_L_UP_04,\
								/*05*/    MUSIC_IRKEY_L_UP_05,\
								/*06*/    MUSIC_IRKEY_L_UP_06,\
								/*07*/    MUSIC_IRKEY_L_UP_07,\
								/*08*/    MUSIC_IRKEY_L_UP_08,\
								/*09*/    MUSIC_IRKEY_L_UP_09,\
								/*10*/    MUSIC_IRKEY_L_UP_10,\
								/*11*/    MUSIC_IRKEY_L_UP_11,\
								/*12*/    MUSIC_IRKEY_L_UP_12,\
								/*13*/    MUSIC_IRKEY_L_UP_13,\
                                                        /*14*/    MUSIC_IRKEY_L_UP_14,\
								/*15*/    MUSIC_IRKEY_L_UP_15,\
								/*16*/    MUSIC_IRKEY_L_UP_16,\
								/*17*/    MUSIC_IRKEY_L_UP_17,\
								/*18*/    MUSIC_IRKEY_L_UP_18,\
								/*19*/    MUSIC_IRKEY_L_UP_19,\
								/*20*/    MUSIC_IRKEY_L_UP_20

const u8 irff00_msg_music_table[3][21] AT (TABLE_CODE)=				//Music模式下的遥控转换表
{
    /*短按*/	    {IRFF00_MUSIC_SHORT},
    /*长按*/		{IRFF00_MUSIC_LONG},
    /*连按*/		{IRFF00_MUSIC_HOLD},
    ///*长按抬起*/	{IRFF00_MUSIC_LONG_UP},
};

//
#define IRFF00_FM_SHORT			\
								/*00*/    FM_IRKEY_SHORT_00,\
							       /*01*/    FM_IRKEY_SHORT_01,\
								/*02*/    FM_IRKEY_SHORT_02,\
								/*03*/    FM_IRKEY_SHORT_03,\
								/*04*/    FM_IRKEY_SHORT_04,\
								/*05*/    FM_IRKEY_SHORT_05,\
								/*06*/    FM_IRKEY_SHORT_06,\
								/*07*/    FM_IRKEY_SHORT_07,\
								/*08*/    FM_IRKEY_SHORT_08,\
								/*09*/    FM_IRKEY_SHORT_09,\
                                				/*10*/    FM_IRKEY_SHORT_10,\
								/*11*/    FM_IRKEY_SHORT_11,\
								/*12*/    FM_IRKEY_SHORT_12,\
								/*13*/    FM_IRKEY_SHORT_13,\
								/*14*/    FM_IRKEY_SHORT_14,\
								/*15*/    FM_IRKEY_SHORT_15,\
								/*16*/    FM_IRKEY_SHORT_16,\
								/*17*/    FM_IRKEY_SHORT_17,\
								/*18*/    FM_IRKEY_SHORT_18,\
								/*19*/    FM_IRKEY_SHORT_19,\
								/*20*/    FM_IRKEY_SHORT_20

#define IRFF00_FM_LONG			\
								/*00*/    FM_IRKEY_LONG_00,\
                                				/*01*/    FM_IRKEY_LONG_01,\
								/*02*/    FM_IRKEY_LONG_02,\
								/*03*/    FM_IRKEY_LONG_03,\
								/*04*/    FM_IRKEY_LONG_04,\
								/*05*/    FM_IRKEY_LONG_05,\
								/*06*/    FM_IRKEY_LONG_06,\
								/*07*/    FM_IRKEY_LONG_07,\
								/*08*/    FM_IRKEY_LONG_08,\
								/*09*/    FM_IRKEY_LONG_09,\
                                				/*10*/    FM_IRKEY_LONG_10,\
								/*11*/    FM_IRKEY_LONG_11,\
								/*12*/    FM_IRKEY_LONG_12,\
								/*13*/    FM_IRKEY_LONG_13,\
								/*14*/    FM_IRKEY_LONG_14,\
								/*15*/    FM_IRKEY_LONG_15,\
								/*16*/    FM_IRKEY_LONG_16,\
								/*17*/    FM_IRKEY_LONG_17,\
								/*18*/    FM_IRKEY_LONG_18,\
								/*19*/    FM_IRKEY_LONG_19,\
								/*20*/    FM_IRKEY_LONG_20//MUSIC_IRKEY_LONG_20

#define IRFF00_FM_HOLD			\
								/*00*/    FM_IRKEY_HOLD_00,\
                                				/*01*/    FM_IRKEY_HOLD_01,\
								/*02*/    FM_IRKEY_HOLD_02,\
								/*03*/    FM_IRKEY_HOLD_03,\
								/*04*/    FM_IRKEY_HOLD_04,\
								/*05*/    FM_IRKEY_HOLD_05,\
								/*06*/    FM_IRKEY_HOLD_06,\
								/*07*/    FM_IRKEY_HOLD_07,\
								/*08*/    FM_IRKEY_HOLD_08,\
								/*09*/    FM_IRKEY_HOLD_09,\
                               	 			/*10*/    FM_IRKEY_HOLD_10,\
								/*11*/    FM_IRKEY_HOLD_11,\
								/*12*/    FM_IRKEY_HOLD_12,\
								/*13*/    FM_IRKEY_HOLD_13,\
								/*14*/    FM_IRKEY_HOLD_14,\
								/*15*/    FM_IRKEY_HOLD_15,\
								/*16*/    FM_IRKEY_HOLD_16,\
								/*17*/    FM_IRKEY_HOLD_17,\
								/*18*/    FM_IRKEY_HOLD_18,\
								/*19*/    FM_IRKEY_HOLD_19,\
								/*20*/    FM_IRKEY_HOLD_20


#define IRFF00_FM_LONG_UP		\
								/*00*/    FM_IRKEY_L_UP_00,\
                                				/*01*/    FM_IRKEY_L_UP_01,\
								/*02*/    FM_IRKEY_L_UP_02,\
								/*03*/    FM_IRKEY_L_UP_03,\
								/*04*/    FM_IRKEY_L_UP_04,\
								/*05*/    FM_IRKEY_L_UP_05,\
								/*06*/    FM_IRKEY_L_UP_06,\
								/*07*/    FM_IRKEY_L_UP_07,\
								/*08*/    FM_IRKEY_L_UP_08,\
								/*09*/    FM_IRKEY_L_UP_09,\
								/*10*/    FM_IRKEY_L_UP_10,\
								/*11*/    FM_IRKEY_L_UP_11,\
								/*12*/    FM_IRKEY_L_UP_12,\
								/*13*/    FM_IRKEY_L_UP_13,\
                               	 			/*14*/    FM_IRKEY_L_UP_14,\
								/*15*/    FM_IRKEY_L_UP_15,\
								/*16*/    FM_IRKEY_L_UP_16,\
								/*17*/    FM_IRKEY_L_UP_17,\
								/*18*/    FM_IRKEY_L_UP_18,\
								/*19*/    FM_IRKEY_L_UP_19,\
								/*20*/    FM_IRKEY_L_UP_20

const u8 irff00_msg_fm_table[3][21] AT (TABLE_CODE)=				//Music模式下的遥控转换表
{
    /*短按*/	    {IRFF00_FM_SHORT},
    /*长按*/		{IRFF00_FM_LONG},
    /*连按*/		{IRFF00_FM_HOLD},
    ///*长按抬起*/	{IRFF00_FM_LONG_UP},
};

#if 0
const u8 IRTabFF00[] AT (TABLE_CODE)= 	   /*user code is 0xFF00*/
{
    NKEY_00, NKEY_01, NKEY_02, NKEY_03, NKEY_04, NKEY_05, NKEY_06, IR_06, IR_15, IR_08, NKEY_0A, NKEY_0B, IR_12, IR_11, NKEY_0E, NKEY_0F,
    NKEY_10, NKEY_11, NKEY_12, NKEY_13, NKEY_14, IR_07, IR_09, NKEY_17, IR_13, IR_10, NKEY_1A, NKEY_1B, IR_16, NKEY_1D, NKEY_1E, NKEY_1F,
    NKEY_20, NKEY_21, NKEY_22, NKEY_23, NKEY_24, NKEY_25, NKEY_26, NKEY_27, NKEY_28, NKEY_29, NKEY_2A, NKEY_2B, NKEY_2C, NKEY_2D, NKEY_2E, NKEY_2F,
    NKEY_30, NKEY_31, NKEY_32, NKEY_33, NKEY_34, NKEY_35, NKEY_36, NKEY_37, NKEY_38, NKEY_39, NKEY_3A, NKEY_3B, NKEY_3C, NKEY_3D, NKEY_3E, NKEY_3F,
    IR_04, NKEY_41, IR_18, IR_05, IR_03, IR_00, IR_01, IR_02, NKEY_48, NKEY_49, IR_20, NKEY_4B, NKEY_4C, NKEY_4D, NKEY_4E, NKEY_4F,
    NKEY_50, NKEY_51, IR_19, NKEY_53, NKEY_54, NKEY_55, NKEY_56, NKEY_57, NKEY_58, NKEY_59, IR_17, NKEY_5B, NKEY_5C, NKEY_5D, IR_14, NKEY_5F,
};
#endif

/*
{
	NKEY_00, NKEY_01, NKEY_02, NKEY_03, NKEY_04, NKEY_05, NKEY_06, NKEY_07, NKEY_08, NKEY_09, NKEY_0A, NKEY_0B, NKEY_0C, NKEY_0D, NKEY_0E, NKEY_0F,
	NKEY_10, NKEY_11, NKEY_12, NKEY_13, NKEY_14, NKEY_15, NKEY_16, NKEY_17, NKEY_18, NKEY_19, NKEY_1A, NKEY_1B, NKEY_1C, NKEY_1D, NKEY_1E, NKEY_1F,
	NKEY_20, NKEY_21, NKEY_22, NKEY_23, NKEY_24, NKEY_25, NKEY_26, NKEY_27, NKEY_28, NKEY_29, NKEY_2A, NKEY_2B, NKEY_2C, NKEY_2D, NKEY_2E, NKEY_2F,
	NKEY_30, NKEY_31, NKEY_32, NKEY_33, NKEY_34, NKEY_35, NKEY_36, NKEY_37, NKEY_38, NKEY_39, NKEY_3A, NKEY_3B, NKEY_3C, NKEY_3D, NKEY_3E, NKEY_3F,
	NKEY_40, NKEY_41, NKEY_42, NKEY_43, NKEY_44, NKEY_45, NKEY_46, NKEY_47, NKEY_48, NKEY_49, NKEY_4A, NKEY_4B, NKEY_4C, NKEY_4D, NKEY_4E, NKEY_4F,
	NKEY_50, NKEY_51, NKEY_52, NKEY_53, NKEY_54, NKEY_55, NKEY_56, NKEY_57, NKEY_58, NKEY_59, NKEY_5A, NKEY_5B, NKEY_5C, NKEY_5D, NKEY_5E, NKEY_5F,
	NKEY_60, NKEY_61, NKEY_62, NKEY_63, NKEY_64, NKEY_65, NKEY_66, NKEY_67, NKEY_68, NKEY_69, NKEY_6A, NKEY_6B, NKEY_6C, NKEY_6D, NKEY_6E, NKEY_6F,
	NKEY_70, NKEY_71, NKEY_72, NKEY_73, NKEY_74, NKEY_75, NKEY_76, NKEY_77, NKEY_78, NKEY_79, NKEY_7A, NKEY_7B, NKEY_7C, NKEY_7D, NKEY_7E, NKEY_7F,
	NKEY_80, NKEY_81, NKEY_82, NKEY_83, NKEY_84, NKEY_85, NKEY_86, NKEY_87, NKEY_88, NKEY_89, NKEY_8A, NKEY_8B, NKEY_8C, NKEY_8D, NKEY_8E, NKEY_8F,
}
*/
#endif
