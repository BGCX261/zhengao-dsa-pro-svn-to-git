/*******************************************************************************************
File Name:  LCD_char.c

Version:    1.00

Discription: LCD 模块

Author:     Caibingquan

Email:      change.tsai@gmail.com

Date:       2012.06.06

Copyright:(c) 2012 , All Rights Reserved.
*******************************************************************************************/
#include "config.h"


const unsigned char gImage_sd[30] =
{
    0XFC,0XFE,0XE3,0XFF,0XF1,0XFF,0XF1,0XFF,0XF1,0XFF,0XF1,0XFF,0XFF,0X00,0X00,
    0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X00,0x00,
};  ///<sd小图标
const unsigned char gImage_point2[8] =   /* 0X22,0X01,0X04,0X00,0X10,0X00, */
{
    0X00,0X18,0X18,0X00,0X00,0X06,0X06,0X00,
};  ///<时间显示用的点的小图标

const unsigned char gImage_udisk[30] =   /* 0X22,0X01,0X10,0X00,0X10,0X00, */
{
    0X80,0XC0,0XE0,0X80,0X98,0XBC,0XBC,0X98,0XB0,0XC0,0X80,0X80,0XC0,0XC0,0X80,
    0X00,0X01,0X03,0X00,0X00,0X0C,0X1E,0X1E,0X0C,0X06,0X03,0X00,0X01,0X01,0x00,
};   ///<USB MASS STORAGE小图标

const unsigned char gImage_eqcls[34] =   /* 0X22,0X01,0X11,0X00,0X10,0X00, */
{
    0X00,0X38,0X44,0X44,0X44,0X00,0X00,0X3C,0X40,0X40,0X00,0X00,0X48,0X54,0X54,0X24,
    0X00,0X00,0X7F,0X47,0X7F,0X41,0X7F,0X41,0X7F,0X43,0X7F,0X47,0X7F,0X47,0X7F,0X43,
    0X7F,0X00,
};  ///<class 音效的小图标

const unsigned char gImage_eqjaz[34] =   /* 0X22,0X01,0X11,0X00,0X10,0X00, */
{
    0X00,0X60,0X40,0X7C,0X00,0X78,0X14,0X78,0X00,0X64,0X54,0X4C,0X00,0X64,0X54,0X4C,
    0X00,0X00,0X7F,0X47,0X7F,0X47,0X7F,0X43,0X7F,0X43,0X7F,0X47,0X7F,0X43,0X7F,0X41,
    0X7F,0X00,
};  ///<    音效的小图标

const unsigned char gImage_eqnor[34] =   /* 0X22,0X01,0X11,0X00,0X10,0X00, */
{
    0X00,0X7C,0X08,0X30,0X7C,0X00,0X38,0X44,0X44,0X38,0X00,0X7C,0X14,0X34,0X54,0X48,
    0X00,0X00,0X7F,0X47,0X7F,0X47,0X7F,0X47,0X7F,0X47,0X7F,0X47,0X7F,0X47,0X7F,0X47,
    0X7F,0X00,
};  ///<    音效的小图标

const unsigned char gImage_eqpop[34] =   /* 0X22,0X01,0X11,0X00,0X10,0X00, */
{
    0X00,0X7C,0X14,0X14,0X08,0X00,0X38,0X44,0X44,0X44,0X38,0X00,0X7C,0X14,0X14,0X08,
    0X00,0X00,0X7F,0X41,0X7F,0X43,0X7F,0X47,0X7F,0X4F,0X7F,0X47,0X7F,0X43,0X7F,0X41,
    0X7F,0X00,
};   ///<    音效的小图标

const unsigned char gImage_eqrck[34] =   /* 0X22,0X01,0X11,0X00,0X10,0X00, */
{
    0X00,0X7C,0X14,0X68,0X00,0X38,0X44,0X38,0X00,0X38,0X44,0X44,0X00,0X7C,0X10,0X6C,
    0X00,0X00,0X7F,0X47,0X7F,0X43,0X7F,0X41,0X7F,0X47,0X7F,0X47,0X7F,0X43,0X7F,0X41,
    0X7F,0X00,
};    ///<    音效的小图标

const unsigned char gImage_small_dot[3] =   /* 0X22,0X01,0X03,0X00,0X08,0X00, */
{
    0X00,0X28,0X00,
};    ///<    3*8的':'小图标
/*
_code unsigned char gImage_pause[] =
{

};       ///< 暂停图标
*/


const unsigned char gImage_number[60] =
{
    0X38,0X64,0X54,0X4C,0X38,0X0,/*0*/
    0X00,0X48,0X7C,0X40,0X00,0X0,
    0X64,0X54,0X54,0X54,0X48,0X0,
    0X44,0X54,0X54,0X54,0X28,0X0,
    0X20,0X30,0X28,0X7C,0X20,0X0,/*4*/
    0X5C,0X54,0X54,0X54,0X20,0X0,
    0X38,0X54,0X54,0X54,0X20,0X0,
    0X04,0X04,0X74,0X0C,0X04,0X0,
    0X28,0X54,0X54,0X54,0X28,0X0,
    0X08,0X54,0X54,0X54,0X38,0X0,/*9*/
};   ///<6*8的数字图标
const unsigned char gImage_vol[124] =   /* 0X22,0X01,0X1F,0X00,0X20,0X00, */
{
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X00,0X00,
    0X00,0X00,0X00,0X00,0X40,0XE0,0XE0,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0XF0,0XF0,0XF0,0XF0,0XF0,0XF8,0XFC,0XFC,0XFE,0XFF,0XFF,0X00,0X00,0X00,
    0X02,0X0F,0X3E,0XF8,0XE0,0X01,0X07,0XFF,0XFC,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X0F,0X0F,0X0F,0X0F,0X0F,0X1F,0X3F,0X7F,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,
    0XE0,0XF8,0X3F,0X0F,0X80,0XE0,0XFF,0X3F,0X03,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X0E,0X07,0X03,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};  ///<音量界面的喇叭图标

const unsigned char gImage_play_all[22] =   /* 0X22,0X01,0X0B,0X00,0X10,0X00, */
{
    0X58,0X64,0X74,0X04,0X44,0X44,0X44,0X40,0X5C,0X4C,0X34,0X3E,0X7F,0X7F,0X47,0X6B,
    0X6D,0X6B,0X47,0X7F,0X7F,0X3E,
};             ///< play all 小图标

const unsigned char gImage_play_folder[22] =   /* 0X22,0X01,0X0B,0X00,0X10,0X00, */
{
    0X58,0X64,0X74,0X04,0X44,0X44,0X44,0X40,0X5C,0X4C,0X34,0X3E,0X7F,0X7F,0X41,0X5D,
    0X5D,0X5D,0X63,0X7F,0X7F,0X3E,
};

const unsigned char gImage_play_one[22] =   /* 0X22,0X01,0X0B,0X00,0X10,0X00, */
{
    0X58,0X64,0X74,0X04,0X44,0X44,0X44,0X40,0X5C,0X4C,0X34,0X3E,0X7F,0X7F,0X7F,0X5B,
    0X41,0X5F,0X7F,0X7F,0X7F,0X3E,
};

const unsigned char gImage_play_random[22] =   /* 0X22,0X01,0X0B,0X00,0X10,0X00, */
{
    0X58,0X64,0X74,0X04,0X04,0X04,0X04,0X04,0X44,0X44,0X38,0X3E,0X7F,0X7F,0X41,0X75,
    0X75,0X65,0X5B,0X7F,0X7F,0X3E,
};


const unsigned char gImage_wma[46] =   /* 0X22,0X01,0X17,0X00,0X10,0X00, */
{
    0X00,0XFE,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,
    0X01,0X01,0X01,0X01,0X01,0XFE,0X00,0X00,0X3F,0X7F,0X41,0X6F,0X77,0X6F,0X41,0X7F,
    0X41,0X7B,0X77,0X7B,0X41,0X7F,0X47,0X6B,0X6D,0X6B,0X47,0X7F,0X3F,0X00,
};
const unsigned char gImage_mp3[44] =   /* 0X22,0X01,0X16,0X00,0X10,0X00, */
{
    0X00,0XFE,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,
    0X01,0X01,0X01,0X01,0X01,0XFE,0X00,0X3F,0X7F,0X41,0X7B,0X77,0X7B,0X41,0X7F,0X41,
    0X75,0X75,0X75,0X71,0X7F,0X5D,0X55,0X55,0X55,0X6B,0X7F,0X3F,
};

const unsigned char gImage_wav[44] =   /* 0X22,0X01,0X16,0X00,0X10,0X00, */
{
    0X00,0XFE,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,0X01,
    0X01,0X01,0X01,0X01,0X01,0XFE,0X00,0X3F,0X7F,0X41,0X6F,0X77,0X6F,0X41,0X7F,0X47,
    0X6B,0X6D,0X6B,0X47,0X7F,0X71,0X6F,0X5F,0X6F,0X71,0X7F,0X3F,
};

const unsigned char CharsTable[]=   //[96][16] = //8 * 16
{
    /*--  文字:     --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    /*--  文字:  !  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x00,0x00,0x00,

    /*--  文字:  "  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x3C,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    /*--  文字:  #  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x20,0xE0,0x3C,0x20,0xE0,0x3C,0x20,0x04,0x3C,0x07,0x04,0x3C,0x07,0x04,0x00,

    /*--  文字:  $  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x30,0x48,0x84,0xFF,0x04,0x08,0x10,0x00,0x08,0x10,0x20,0x7F,0x21,0x12,0x0C,

    /*--  文字:  %  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x38,0x44,0x44,0xB8,0x60,0x18,0x04,0x00,0x20,0x18,0x06,0x1D,0x22,0x22,0x1C,

    /*--  文字:  &  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x38,0xC4,0xC4,0x38,0x00,0x80,0x00,0x1E,0x21,0x20,0x20,0x13,0x0C,0x33,

    /*--  文字:  '  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    /*--  文字:  (  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,

    /*--  文字:  )  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,

    /*--  文字:  *  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x40,0x80,0xE0,0x80,0x40,0x00,0x00,0x00,0x02,0x01,0x00,0x01,0x02,0x00,0x00,

    /*--  文字:  +  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x80,0x80,0x80,0xF0,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,

    /*--  文字:  ,  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x30,0x00,0x00,0x00,

    /*--  文字:  -  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    /*--  文字:  .  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,

    /*--  文字:  /  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x80,0x60,0x18,0x06,0x00,0x00,0x18,0x06,0x01,0x00,0x00,0x00,0x00,

    /*--  文字:  0  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xF0,0x08,0x04,0x04,0x04,0x08,0xF0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,

    /*--  文字:  1  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x08,0x08,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,

    /*--  文字:  2  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x18,0x04,0x04,0x04,0x84,0x78,0x00,0x00,0x38,0x24,0x22,0x21,0x20,0x20,0x00,

    /*--  文字:  3  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x18,0x84,0x84,0x84,0x84,0x78,0x00,0x00,0x18,0x20,0x20,0x20,0x20,0x1F,0x00,

    /*--  文字:  4  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0xC0,0x30,0x0C,0xFC,0x00,0x00,0x04,0x07,0x04,0x04,0x04,0x3F,0x04,

    /*--  文字:  5  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x44,0x44,0x44,0x44,0x84,0x00,0x00,0x18,0x20,0x20,0x20,0x20,0x1F,0x00,

    /*--  文字:  6  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xF8,0x84,0x84,0x84,0x84,0x18,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,

    /*--  文字:  7  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x04,0x04,0x04,0xC4,0x34,0x0C,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00,

    /*--  文字:  8  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x78,0x84,0x84,0x84,0x84,0x78,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,

    /*--  文字:  9  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xF8,0x04,0x04,0x04,0x04,0xF8,0x00,0x00,0x18,0x21,0x21,0x21,0x21,0x1F,0x00,

    /*--  文字:  :  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,

    /*--  文字:  ;  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x1C,0x00,0x00,0x00,

    /*--  文字:  <  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x80,0x40,0x40,0x20,0x20,0x10,0x10,0x00,0x00,0x01,0x01,0x02,0x02,0x04,0x04,

    /*--  文字:  =  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,

    /*--  文字:  >  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x10,0x10,0x20,0x20,0x40,0x40,0x80,0x00,0x04,0x04,0x02,0x02,0x01,0x01,0x00,

    /*--  文字:  ?  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x30,0x08,0x04,0x04,0x84,0x48,0x30,0x00,0x00,0x00,0x00,0x37,0x00,0x00,0x00,

    /*--  文字:  @  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xF0,0x08,0xC4,0x24,0xE4,0x08,0xF0,0x00,0x0F,0x10,0x23,0x24,0x23,0x14,0x07,

    /*--  文字:  A  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0xE0,0x1C,0xE0,0x00,0x00,0x00,0x38,0x07,0x04,0x04,0x04,0x07,0x38,

    /*--  文字:  B  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x84,0x84,0x84,0x84,0x48,0x30,0x00,0x3F,0x20,0x20,0x20,0x20,0x11,0x0E,

    /*--  文字:  C  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xF0,0x08,0x04,0x04,0x04,0x08,0x30,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0C,

    /*--  文字:  D  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x04,0x04,0x04,0x04,0x18,0xE0,0x00,0x3F,0x20,0x20,0x20,0x20,0x18,0x07,

    /*--  文字:  E  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x84,0x84,0x84,0x84,0x84,0x04,0x00,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,

    /*--  文字:  F  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x84,0x84,0x84,0x84,0x84,0x04,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,

    /*--  文字:  G  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xF0,0x08,0x04,0x04,0x04,0x08,0x10,0x00,0x0F,0x10,0x20,0x20,0x21,0x11,0x3F,

    /*--  文字:  H  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x80,0x80,0x80,0x80,0x80,0xFC,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x3F,

    /*--  文字:  I  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,

    /*--  文字:  J  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x18,0x20,0x20,0x20,0x1F,0x00,0x00,

    /*--  文字:  K  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x80,0x40,0x20,0x10,0x08,0x04,0x00,0x3F,0x01,0x02,0x04,0x08,0x10,0x20,

    /*--  文字:  L  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x20,0x20,0x20,0x20,0x20,0x00,

    /*--  文字:  M  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x30,0xC0,0x00,0xC0,0x30,0xFC,0x00,0x3F,0x00,0x00,0x07,0x00,0x00,0x3F,

    /*--  文字:  N  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x18,0x60,0x80,0x00,0x00,0xFC,0x00,0x3F,0x00,0x00,0x01,0x06,0x18,0x3F,

    /*--  文字:  O  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xF0,0x08,0x04,0x04,0x04,0x08,0xF0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,

    /*--  文字:  P  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x04,0x04,0x04,0x04,0x88,0x70,0x00,0x3F,0x01,0x01,0x01,0x01,0x00,0x00,

    /*--  文字:  Q  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xF0,0x08,0x04,0x04,0x04,0x08,0xF0,0x00,0x0F,0x10,0x20,0x24,0x28,0x30,0x4F,

    /*--  文字:  R  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x04,0x04,0x04,0x04,0x88,0x70,0x00,0x3F,0x01,0x01,0x01,0x01,0x02,0x3C,

    /*--  文字:  S  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x30,0x48,0x44,0x84,0x84,0x08,0x10,0x00,0x08,0x10,0x20,0x20,0x20,0x11,0x0E,

    /*--  文字:  T  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,

    /*--  文字:  U  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x1F,0x20,0x20,0x20,0x20,0x20,0x1F,

    /*--  文字:  V  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x1C,0xE0,0x00,0x00,0x00,0xE0,0x1C,0x00,0x00,0x00,0x07,0x38,0x07,0x00,0x00,

    /*--  文字:  W  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x00,0xC0,0x3C,0xC0,0x00,0xFC,0x00,0x03,0x3C,0x03,0x00,0x03,0x3C,0x03,

    /*--  文字:  X  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x0C,0x30,0x40,0x80,0x40,0x30,0x0C,0x00,0x30,0x0C,0x03,0x00,0x03,0x0C,0x30,

    /*--  文字:  Y  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x0C,0x30,0xC0,0x00,0xC0,0x30,0x0C,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,

    /*--  文字:  Z  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x04,0x04,0x04,0xC4,0x34,0x0C,0x00,0x00,0x30,0x2C,0x23,0x20,0x20,0x20,0x00,

    /*--  文字:  [  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,

    /*--  文字:  \  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x20,0xFC,0x20,0xE0,0x3C,0xE0,0x20,0xFC,0x00,0x03,0x3C,0x03,0x00,0x03,0x3C,0x03,

    /*--  文字:  ]  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,

    /*--  文字:  ^  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x08,0x04,0x02,0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    /*--  文字:  _  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,

    /*--  文字:  `  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x02,0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    /*--  文字:  a  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x80,0x40,0x40,0x40,0x40,0x80,0x00,0x00,0x1C,0x22,0x22,0x22,0x22,0x1F,0x20,

    /*--  文字:  b  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x3F,0x10,0x20,0x20,0x20,0x10,0x0F,

    /*--  文字:  c  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x80,0x40,0x40,0x40,0x40,0x80,0x00,0x0F,0x10,0x20,0x20,0x20,0x20,0x10,

    /*--  文字:  d  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x80,0x40,0x40,0x40,0x80,0xFC,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x3F,

    /*--  文字:  e  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x0F,0x12,0x22,0x22,0x22,0x22,0x13,

    /*--  文字:  f  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x40,0x40,0xF8,0x44,0x44,0x44,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,

    /*--  文字:  g  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x80,0x40,0x40,0x40,0x40,0xC0,0x00,0x00,0x27,0x48,0x48,0x48,0x48,0x3F,0x00,

    /*--  文字:  h  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x3F,0x00,

    /*--  文字:  i  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0xCC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,

    /*--  文字:  j  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0xCC,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,

    /*--  文字:  k  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xFC,0x00,0x00,0x80,0x40,0x20,0x00,0x00,0x3F,0x02,0x05,0x08,0x10,0x20,0x00,

    /*--  文字:  l  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,

    /*--  文字:  m  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xC0,0x40,0x40,0x80,0x40,0x40,0x80,0x00,0x3F,0x00,0x00,0x3F,0x00,0x00,0x3F,

    /*--  文字:  n  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xC0,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x3F,0x00,

    /*--  文字:  o  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,

    /*--  文字:  p  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xC0,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x7F,0x08,0x10,0x10,0x10,0x08,0x07,

    /*--  文字:  q  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x80,0x40,0x40,0x40,0x80,0xC0,0x00,0x07,0x08,0x10,0x10,0x10,0x08,0x7F,

    /*--  文字:  r  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0xC0,0x80,0x40,0x40,0x40,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,

    /*--  文字:  s  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x80,0x40,0x40,0x40,0x40,0x80,0x00,0x00,0x11,0x22,0x22,0x24,0x24,0x18,0x00,

    /*--  文字:  t  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x40,0x40,0xFC,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x00,

    /*--  文字:  u  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xC0,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x3F,0x00,

    /*--  文字:  v  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x03,0x0C,0x30,0x0C,0x03,0x00,

    /*--  文字:  w  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xC0,0x00,0x00,0x80,0x00,0x00,0xC0,0x00,0x07,0x38,0x0C,0x03,0x0C,0x38,0x07,

    /*--  文字:  x  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x40,0x80,0x00,0x00,0x00,0x80,0x40,0x00,0x20,0x10,0x09,0x06,0x09,0x10,0x20,

    /*--  文字:  y  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x40,0x43,0x4C,0x30,0x0C,0x03,0x00,

    /*--  文字:  z  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x40,0x40,0x40,0x40,0x40,0xC0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x20,0x00,

    /*--  文字:  {  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x80,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,0x00,

    /*--  文字:  |  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,

    /*--  文字:  }  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x02,0x02,0x7C,0x80,0x80,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,

    /*--  文字:  ~  --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0x80,0x40,0x40,0x80,0x80,0x80,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    /*--  文字:    --*/
    /*--  @DotumChe12;  此字体下对应的点阵为：宽x高=8x16   --*/
    0x00,0xF8,0x08,0x08,0x08,0x08,0xF8,0x00,0x00,0x3F,0x20,0x20,0x20,0x20,0x3F,0x00,
} ;



