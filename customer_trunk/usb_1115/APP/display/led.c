/*--------------------------------------------------------------------------*/
/**@file    led.c
   @brief   4位LED驱动
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "led.h"

#if (DISP_SEG_LED == 1)

_idata u8 LED_BUFF[5];   ///<LED显存
u8 _code led_icon[] =    ///<LED标志位
{
    LED0_FM,
    LED0_AUX,
    LED0_USB,
    LED0_SD,
    LED0_WMA,
    LED0_MP3,
    LED0_WAV,
    LED0_1POINT,
    LED0_2POINT,
};

u8 led_counter;			  ///<LED显示坐标
u8 led_flash_char;		  ///<LED闪烁数字位
u8 led_flash_icon;		  ///<LED闪烁状态位
bool all_flash_flag;	  ///<LED全闪烁标志位

#define LED0_STATUS   LED_BUFF[4]

#define LED_MINUS     0x40

u8 _code LED_NUMBER[10] =
{
    0x3f,0x06,0x5b,0x4f,0x66,  ///<0~4
    0x6d,0x7d,0x07,0x7f,0x6f   ///<5~9
};

u8 _code LED_LARGE_LETTER[26] =
{
    0x77,0x40,0x40,0x3f,0x79,///<ABCDE
    0x71,0x40,0x76,0x06,0x40,///<FGHIJ
    0x40,0x38,0x40,0x37,0x3f,///<KLMNO
    0x73,0x40,0x50,0x6d,0x40,///<PQRST
    0x3e,0x3e,0x40,0x76,0x40,///<UVWXY
    0x40///<Z
};

u8 _code LED_SMALL_LETTER[26] =
{
    0x77,0x7c,0x40,0x5e,0x79,///<abcde
    0x71,0x40,0x40,0x40,0x40,///<fghij
    0x40,0x38,0x40,0x54,0x5c,///<klmno
    0x73,0x67,0x50,0x40,0x40,///<pqrst
    0x3e,0x3e,0x40,0x40,0x40,///<uvwxy
    0x40///<z
};
/*----------------------------------------------------------------------------*/
/**@brief    清空LED BUFF函数，LED显示位置设为1
   @param	 无
   @return	 无
   @note     void clear_led(void)
*/
/*----------------------------------------------------------------------------*/
void clear_led(void)
{
    LED_BUFF[0] = 0;	  /* 千位 */
    LED_BUFF[1] = 0;	  /* 百位 */
    LED_BUFF[2] = 0;	  /* 十位 */
    LED_BUFF[3] = 0;	  /* 个位 */
    LED_BUFF[4] = 0;	  /* 状态位 */
    led_counter = 0;
}
/*----------------------------------------------------------------------------*/
/**@brief    LED 显示坐标设置
   @param	 x:显示坐标
   @return	 无
   @note     void led_setx(u8 x)
*/
/*----------------------------------------------------------------------------*/
void led_setx(u8 x)
{
    led_counter = x + 0;
}
/*----------------------------------------------------------------------------*/
/**@brief    LED 显示初始化
   @param	 无
   @return	 无
   @note     void init_led_disp(void)
*/
/*----------------------------------------------------------------------------*/
void init_led_disp(void)
{
    led_flash_char = 0;
    led_flash_icon = 0;
    all_flash_flag = 0;
    clear_led();
    led_com_out();
    led_seg_out();
}
/*----------------------------------------------------------------------------*/
/**@brief    LED 显示命令处理
   @param	 key:显示命令
   @return	 无
   @note     void led_cmd(u8 key)
*/
/*----------------------------------------------------------------------------*/
void led_cmd(u8 key)
{
    if (key == 'c')
        clear_led();
}
/*----------------------------------------------------------------------------*/
/**@brief    LED 亮度设置
   @param	 br:亮度数值
   @return	 无
   @note     void led_set_brightness(u8 br)
*/
/*----------------------------------------------------------------------------*/
void led_set_brightness(u8 br)
{
    if (br > 16)
        return;
    if (br == 16)
        PWM4CON = 0;
    else
        PWM4CON = br | 0xd0;
}
/*----------------------------------------------------------------------------*/
/**@brief    LED 闪烁设置
   @param	 chardata：显示数据
   @return	 无
   @note     void led_set_brightness(u8 br)
*/
/*----------------------------------------------------------------------------*/
void led_flash_set(u8 chardata)
{
    if (chardata == 0xff)				//all flash
    {
        led_flash_icon = 0xff;
        led_flash_char = 0xff;
        all_flash_flag = 1;
    }
    else if (chardata == 0xfe)				//all no flash
    {
        led_flash_icon = 0;
        led_flash_char = 0;
        all_flash_flag = 0;
    }
    else if (!all_flash_flag)
    {
        if (chardata < 0x40)			   //Mask version 	//chardata为小于 0x40 b0100 0000
            led_flash_icon &= ~led_icon[chardata & 0x3f];	//chardata & 0x3f 0x0~0x0C
        else if (chardata < 0x80)							//chardata为大于 0x40 b0100 0000
            led_flash_char &= ~BIT(chardata & 0x7f);		//chardata & 0x7f 0x40~0x47
        else if (chardata < 0xc0)		   //Normal version	//chardata为大于 0x80 b1000 0000
        {
            led_flash_icon |= led_icon[chardata & 0x3f];	//chardata & 0x3f 0x0~0x0C
        }
        else											  	//chardata为大于 0xC0 b1100 0000
            led_flash_char |= BIT(chardata & 0x7f);		  	//chardata & 0x7f 0x80~8C 数字闪烁的位设置，？使用时验证0x7f的正确性，错误则使用0x3f
    }
}
/*----------------------------------------------------------------------------*/
/**@brief    LED 状态图标显示
   @param	 chardata：状态位数据
   @return	 无
   @note     void led_disp_icon(u8 chardata)
*/
/*----------------------------------------------------------------------------*/
void led_disp_icon(u8 chardata)
{
    if (chardata < 0x40)					//Mask version
        LED0_STATUS &= ~led_icon[chardata];
    else if (chardata < 0xC0)				//Normal version
        LED0_STATUS |= led_icon[chardata & 0x3f];
}

/*----------------------------------------------------------------------------*/
/**@brief    LED 字符显示
   @param	 chardata：字符数据
   @return	 无
   @note     void led_putchar(u8 chardata)
*/
/*----------------------------------------------------------------------------*/
void led_putchar(u8 chardata)
{

    if ((chardata < ' ') || (chardata > '~') || (led_counter > 4))
    {
        return;
    }
    if ((chardata >= '0') && (chardata <= '9'))
    {
        LED_BUFF[led_counter++] = LED_NUMBER[chardata - '0'];
    }
    else if ((chardata >= 'a') && (chardata <= 'z'))
    {
        LED_BUFF[led_counter++] = LED_SMALL_LETTER[chardata - 'a'];
    }
    else if ((chardata >= 'A') && (chardata <= 'Z'))
    {
        LED_BUFF[led_counter++] = LED_LARGE_LETTER[chardata - 'A'];
    }
    else if (chardata == ':')
    {
        LED0_STATUS |= LED0_2POINT;
    }
    else if (chardata == ' ')
    {
        led_counter++;
    }
    else if (chardata == '-')
    {
        LED_BUFF[led_counter++] = LED_MINUS;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    LED扫描函数
   @param
   @return
   @note     void disp_scan(void)
*/
/*----------------------------------------------------------------------------*/
void disp_scan(void)
{
    static u8 cnt;
    static u8 counter;
    static bool flash;

    u8 com, seg;

    seg = LED_BUFF[cnt];
    com = BIT(cnt);

    counter++;
    if (counter == 250)
    {
        counter = 0;
        flash = !flash;
    }

    if (flash)
    {
        if ((led_flash_icon) && (cnt == 4))
        {
            seg &= ~led_flash_icon;
        }

        if (((led_flash_char & BIT(0)) && (cnt == 1)) ||
                ((led_flash_char & BIT(1)) && (cnt == 2))||
                ((led_flash_char & BIT(2)) && (cnt == 3)) ||
                ((led_flash_char & BIT(3)) && (cnt == 4)))
        {
            seg = 0x0;
        }
    }

    LED_COM &= ~0x1f;
    LED_COM_MASK &= ~0x1f;
    LED_SEG |= 0x7f;			 //清LED COM SEG

    LED_SEG &= ~seg;
    LED_COM |= com;
    LED_COM_MASK |= com;
    cnt = (cnt >= 4)?( 0 ): (cnt+1);
}
#else
void disp_scan(void)
{
}
#endif
