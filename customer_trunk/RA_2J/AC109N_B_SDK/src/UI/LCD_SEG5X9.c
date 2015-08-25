/*--------------------------------------------------------------------------*/
/**@file    LCD_SEG4X8.c
   @brief   LCD 段码屏模块驱动接口函数
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/

#include "UI_API.h"

#if defined LCD_SEG_5X9
#include "LCD_SEG5X9.h"
#include "IRTC.h"
#include "device.h"
#include "get_music_file.h"
#include "main.h"
#include "fm_radio.h"
#include "hot_msg.h"
#include "music_play.h"
#include "play_file.h"
#include "RTC_API.h"
#include "gpio_if.h"

LCD_SEG5X9_VAR _idata LCD_SEG5X9_var;
LCDC5X9_P1BUF _idata LCDC5X9_P1buf;
LCDC5X9_P0BUF _idata LCDC5X9_P0buf;

extern xd_u8 ffr_func_flag;
extern bool music_disp_file_dir,radio_play_pause;
xd_u8 backlight_fadeout=0;
extern u8 version_timer;
const u8 LCD_SEG_NUMBER[] =
{
    /*0*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGE | SEGF),
    /*1*/
    (u8)(SEGB | SEGC),
    /*2*/
    (u8)(SEGA | SEGB | SEGD | SEGE | SEGG),
    /*3*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGG),
    /*4*/
    (u8)(SEGB | SEGC | SEGF | SEGG),
    /*5*/
    (u8)(SEGA | SEGC | SEGD | SEGF | SEGG),
    /*6*/
    (u8)(SEGA | SEGC | SEGD | SEGE | SEGF | SEGG),
    /*7*/
    (u8)(SEGA | SEGB | SEGC),
    /*8*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG),
    /*9*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
};

const u8 LCD_SEG_SMALL_NUMBER[] =
{
    /*a*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGE | SEGG),
    /*b*/
    (u8)(SEGC | SEGD | SEGE | SEGF | SEGG),
    /*c*/
    (u8)(SEGA | SEGD | SEGE | SEGF),
    /*d*/
    (u8)(SEGB | SEGC | SEGD | SEGE | SEGG),
    /*e*/
    (u8)(SEGB | SEGC | SEGD | SEGE | SEGG),
    /*f*/
    (u8)(SEGA | SEGC | SEGD | SEGF | SEGG),
    /*g*/
    (u8)(SEGA | SEGC | SEGD | SEGE | SEGF | SEGG),
    /*h*/
    (u8)(SEGA | SEGB | SEGC),
    /*i*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG),
    /*j*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*k*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*l*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*m*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*n*/
    (u8)(SEGC | SEGE | SEGG),
    /*o*/
    (u8)(SEGC | SEGD | SEGE | SEGG),
    /*p*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*q*/
    (u8)(SEGA | SEGB | SEGC | SEGF | SEGG),
    /*r*/
    (u8)(SEGE | SEGG),
    /*s*/
    (u8)(SEGA | SEGC | SEGD | SEGF | SEGG),
    /*t*/
    (u8)(SEGD | SEGE | SEGF  | SEGG),
    /*u*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*v*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*w*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*x*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*y*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*z*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
};

const u8 LCD_SEG_LARGE_NUMBER[] =
{
    /*A*/
    (u8)(SEGA | SEGB | SEGC | SEGE | SEGF | SEGG),
    /*B*/
    (u8)(SEGB | SEGC),
    /*C*/
    (u8)(SEGA | SEGD | SEGE | SEGF),
    /*D*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGG),
    /*E*/
    (u8)(SEGA | SEGD | SEGE | SEGF | SEGG),
    /*F*/
    (u8)(SEGA | SEGE | SEGF | SEGG),
    /*G*/
    (u8)(SEGA | SEGC | SEGD | SEGE | SEGF | SEGG),
    /*H*/
    (u8)(SEGB | SEGC | SEGG| SEGE | SEGF),
    /*I*/
    (u8)(SEGB | SEGC),
    /*J*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*K*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*L*/
    (u8)(SEGD | SEGE | SEGF),
    /*M*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*N*/
    (u8)(SEGA | SEGB | SEGC | SEGE | SEGF),
    /*O*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGE | SEGF),
    /*P*/
    (u8)(SEGA | SEGB | SEGE | SEGF | SEGG),
    /*Q*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*R*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*S*/
    (u8)(SEGA | SEGC | SEGD | SEGF | SEGG),
    /*T*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*U*/
    (u8)(SEGB | SEGC | SEGD | SEGE | SEGF),
    /*V*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*W*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*X*/
    (u8)(SEGB | SEGC | SEGG| SEGE | SEGF),
    /*Y*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
    /*Z*/
    (u8)(SEGA | SEGB | SEGC | SEGD | SEGF | SEGG),
};

const u8 playmodestr[4][5] AT(LCD_SEG_TABLE_CODE)=
{
    "rPtA",

#ifdef FOLDER_PLAY_EN
    "rPtd",
#endif

    "rPt1",

#ifdef RANDOM_PLAY_EN
    "rdN",
#endif
};

const u8 menu_string[][5] AT(LCD_SEG_TABLE_CODE)=
{
    " ON ",
    "  Sd",
#ifdef USB_DEVICE_EN
    " USb",
    //" UP ",
    //" dN ",
#endif
    "AUX",
#ifdef RTC_ALARM_EN
    "-AL-"
#endif
    "NOSd",
    "rESt",
};

/*----------------------------------------------------------------------------*/
/**@brief   5X8段码屏初始化函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG5X9_init(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void LCD_SEG5X9_init(void) AT(LCD_SEG_CODE)
{

    CLK_CON2 |= BIT(4);                 //[4]LCD Clk
    //CLK_GAT |= BIT(5);
    LCD_CON0 = BIT(6)|BIT(4);	//[6:4]:VLCDS 3.3V
    LCD_CON1 = BIT(0)|BIT(1)|BIT(4)|BIT(5)|BIT(6);           //[7:6]:4 COM
    LCD_CON0 |= (BIT(7)|BIT(3))/**/;      	//[7]: Frame Frequency [3:2]:1/2 Bias
    //LCD_CON0 |= BIT(1);	            //[1]:DOTEN COM0-SEG0
    //SEG_EN0 = 0xFF;
    SEG_EN1 = 0xFF;
    SEG_EN0 =  (BIT(7)|BIT(1)|BIT(0));
    LCD_CON0 |= BIT(0);	                //[0]:LCDEN
}

/*----------------------------------------------------------------------------*/
/**@brief   LCD_SEG 显示坐标设置
   @param   x：显示横坐标
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_setX(u8 X)
*/
/*----------------------------------------------------------------------------*/
_near_func void LCD_SEG5X9_setX(u8 X) AT(LCD_SEG_CODE)
{
    LCD_SEG5X9_var.bCoordinateX = X;
}

/*----------------------------------------------------------------------------*/
/**@brief   LCD_SEG 屏幕清除函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_clear(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void LCD_SEG5X9_clear(void) AT(LCD_SEG_CODE)
{
    my_memset((u8 _xdata *)&LCD_SEG5X9_var, 0x0, sizeof(LCD_SEG5X9_VAR));
}
_near_func void LCD_clear_icon(u8 icon) AT(LCD_SEG_CODE)
{
#if 1
	switch(icon)
	{
	    case LCD_PLAY_ICON:
		    	LCD_SEG5X9_var.seg0_state[3] &= ~PLAY_ICON;					
			break;
	    case LCD_PAUSE_ICON:
    	 		LCD_SEG5X9_var.seg0_state[2] &= ~PAUS_ICON;
			break;
	    case LCD_COL_ICON:
		      LCD_SEG5X9_var.seg1_state[0] &= ~COL_ICON;			
			break;
	    case LCD_FM_ICON:
			LCD_SEG5X9_var.seg0_state[2] &= ~FM_ICON;			
			LCD_SEG5X9_var.seg1_state[0] &= ~MHZ_ICON;			
			break;
	    case LCD_MHZ_ICON:
			break;
	    case LCD_MW_ICON:
			LCD_SEG5X9_var.seg0_state[3] &= ~AM_ICON;			
			break;
	    case LCD_KHZ_ICON:
			LCD_SEG5X9_var.seg1_state[0] &= ~KHZ_ICON;						
			break;
	    case LCD_BAT_SHELL_ICON:
			LCD_SEG5X9_var.seg0_state[1] &= ~BAT_SHELL_ICON;									
			break;
	    case LCD_BAT_L1_ICON:
			LCD_SEG5X9_var.seg0_state[0] &= ~BAT_LVL1_ICON;						
			break;
	    case LCD_BAT_L2_ICON:
			LCD_SEG5X9_var.seg0_state[3] &= ~BAT_LVL2_ICON;						
			break;
	    case LCD_USBPC_ICON:
			LCD_SEG5X9_var.seg0_state[0] &= ~PC_ICON;						
			break;			
	}
#endif	
}
_near_func void LCD_show_icon(u8 icon) AT(LCD_SEG_CODE)
{
#if 1
	switch(icon)
	{
	    case LCD_PLAY_ICON:
		    	LCD_SEG5X9_var.seg0_state[3] |= PLAY_ICON;			
			break;
	    case LCD_PAUSE_ICON:
    	 		LCD_SEG5X9_var.seg0_state[2] |= PAUS_ICON;
			break;
	    case LCD_COL_ICON:
     			LCD_SEG5X9_var.seg1_state[0] |= COL_ICON;			
			break;
	    case LCD_FM_ICON:
			LCD_SEG5X9_var.seg0_state[2] |= FM_ICON;			
			LCD_SEG5X9_var.seg1_state[0] |= MHZ_ICON;			
			break;
	    case LCD_MHZ_ICON:
			break;
	    case LCD_MW_ICON:
			LCD_SEG5X9_var.seg0_state[3] |=AM_ICON;
			break;
	    case LCD_KHZ_ICON:
			LCD_SEG5X9_var.seg1_state[0] |=KHZ_ICON;			
			break;
	    case LCD_BAT_SHELL_ICON:
			LCD_SEG5X9_var.seg0_state[1] |=BAT_SHELL_ICON;			
			break;
	    case LCD_BAT_L1_ICON:
			LCD_SEG5X9_var.seg0_state[0] |=BAT_LVL1_ICON;			
			break;
	    case LCD_BAT_L2_ICON:
			LCD_SEG5X9_var.seg0_state[3] |=BAT_LVL2_ICON;			
			break;
	    case LCD_USBPC_ICON:
			LCD_SEG5X9_var.seg0_state[0] |=PC_ICON;			
			break;			
	}
#endif	
}
_near_func void LCD_backlight_turn_on(void) AT(LCD_SEG_CODE)
{
	backlight_fadeout=20;
	GPIO_BACKLIGHT_TURN_ON();
}
_near_func void LCD_backlight_turn_off(void) AT(LCD_SEG_CODE)
{
	if(backlight_fadeout>0){
		backlight_fadeout--;
		if(backlight_fadeout==0){
			GPIO_BACKLIGHT_TURN_OFF();
		}
	}
}
/*----------------------------------------------------------------------------*/
/**@brief   LCD_SEG 单个字符显示函数
   @param   chardata：显示字符
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_char(u8 chardata)
*/
/*----------------------------------------------------------------------------*/
_near_func void LCD_SEG5X9_show_char(u8 chardata) AT(LCD_SEG_CODE)
{
    if ((chardata < ' ') || (chardata > '~') || (LCD_SEG5X9_var.bCoordinateX > 4))
    {
        return;
    }
    if ((chardata >= '0') && (chardata <= '9'))
    {
        LCD_SEG5X9_var.bShowBuff[LCD_SEG5X9_var.bCoordinateX++] = LCD_SEG_NUMBER[chardata - '0'];
    }
    else if ((chardata >= 'a') && (chardata <= 'z'))
    {
        LCD_SEG5X9_var.bShowBuff[LCD_SEG5X9_var.bCoordinateX++] = LCD_SEG_SMALL_NUMBER[chardata - 'a'];
    }
    else if ((chardata >= 'A') && (chardata <= 'Z'))
    {
        LCD_SEG5X9_var.bShowBuff[LCD_SEG5X9_var.bCoordinateX++] = LCD_SEG_LARGE_NUMBER[chardata - 'A'];
    }
    else if (chardata == ':')
    {
        //LED_STATUS |= LED_2POINT;
    }
    else if (chardata == ' ')
    {
        LCD_SEG5X9_var.bCoordinateX++;
    }
    else if (chardata == '-')
    {
        //LCD_SEG5X9_var.bShowBuff[LCD_SEG5X9_var.bCoordinateX++] = BIT(3);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   LCD_SEG 单个字符显示函数
   @param   chardata：显示字符
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_number(u8 number)
*/
/*----------------------------------------------------------------------------*/
_near_func void LCD_SEG5X9_show_number(u8 number) AT(LCD_SEG_CODE)
{
    LCD_SEG5X9_show_char(number + '0');
}

/*----------------------------------------------------------------------------*/
/**@brief   LCD_SEG 字符串显示函数
   @param   *str：字符串的指针   offset：显示偏移量
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_string(u8 *str)
*/
/*----------------------------------------------------------------------------*/
_near_func void LCD_SEG5X9_show_string(u8 *str) AT(LCD_SEG_CODE)
{
    while (0 != *str)
    {
        LCD_SEG5X9_show_char(*str++);
    }
}


/*----------------------------------------------------------------------------*/
/** @brief:
    @param:
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
void LCD_SEG5X9_show_string_menu(u8 menu)
{
    	LCD_SEG5X9_show_string((u8 *)menu_string[menu]);

	if(MENU_PC_MAIN==menu){
		LCD_show_icon(LCD_USBPC_ICON);
	}
	else if(MENU_POWER_UP==menu){
		LCD_backlight_turn_on();
	}
	else if(MENU_IDLE_MAIN==menu){

		if(version_timer>0){
		    LCD_SEG5X9_clear();			
		    LCD_SEG5X9_show_char('U');
		    LCD_SEG5X9_setX(2);
		    itoa2(VERSION_NO);
		    LCD_SEG5X9_show_string((u8 *)bcd_number);
		}
	}
}

/*----------------------------------------------------------------------------*/
/**@brief   Music模式 设备显示
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG5X9_show_dev(void)
*/
/*----------------------------------------------------------------------------*/
_near_func static void LCD_SEG5X9_show_dev(void) AT(LCD_SEG_CODE)
{
    /*Music Device type*/
#if 0
    if (device_active == DEVICE_SDMMCA)
      LCD_SEG5X9_var.state[1] |= SD_ICON;
    else if (device_active == DEVICE_UDISK)
     LCD_SEG5X9_var.state[0] |= USB_ICON;
#endif

	//LCD_show_icon(LCD_COL_ICON);
     //LCD_SEG5X9_var.seg1_state[0] |= COL_ICON;
}

/*----------------------------------------------------------------------------*/
/**@brief   Music模式 显示界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_music_main(void)
*/
/*----------------------------------------------------------------------------*/
void LCD_SEG5X9_show_music_main(void)
{
    u16 play_time;
    static bool scr_blink=0,scr_snr=0;
    static u8 play_slider_scr=0,sec_reg;
    /*Music Play time info*/
    play_time = get_music_play_time();

    //LCD_SEG5X9_show_dev();

    if (Music_Play_var.bPlayStatus  == MAD_PLAY){



		 if(((play_time%60)%10)==0){
		 	
		 	if(sec_reg !=(play_time%60)){
				
				sec_reg =(play_time%60);
				
				scr_snr=1;
				play_slider_scr++;	
				
				if(play_slider_scr>3)
					play_slider_scr =0;
		 	}
		 }
		else{
			scr_snr=0;

		}
		LCD_show_icon(LCD_PLAY_ICON);
		LCD_show_icon(LCD_COL_ICON);

		if(ffr_func_flag>0){
			scr_snr=0;
		}
		if(scr_snr){
			
			LCD_clear_icon(LCD_COL_ICON);		 	
			LCD_SEG5X9_setX(0);		
				
#if 0//def FM_UART_DEBUG
			my_printf(" --->LCD_SEG5X9_show_music_main :.  %4u \r\n",(u16)play_slider_scr);
#endif
			if(play_slider_scr==3){
			       LCD_SEG5X9_show_char('F');	
			    	itoa3(ff_api.fs_msg.dirCounter+1);
			    	LCD_SEG5X9_show_string((u8 *)bcd_number);
			}
			else{
    				itoa4(playfile.given_file_number);
    				if(playfile.given_file_number <= 999)
        			bcd_number[0] = ' ';		
				LCD_SEG5X9_show_string((u8 *)bcd_number);
			}
		}
	 	else{

		    itoa2(play_time/60);
		    LCD_SEG5X9_show_string((u8 *)bcd_number);

		    itoa2(play_time%60);
		    LCD_SEG5X9_show_string((u8 *)bcd_number);
	 	}
    }
    else if (Music_Play_var.bPlayStatus == MAD_PAUSE){

    	itoa2(play_time/60);
    	LCD_SEG5X9_show_string((u8 *)bcd_number);

    	itoa2(play_time%60);
    	LCD_SEG5X9_show_string((u8 *)bcd_number);
	
	LCD_show_icon(LCD_PAUSE_ICON);
	LCD_show_icon(LCD_COL_ICON);

	scr_blink=1-scr_blink;
	if(scr_blink){

		LCD_SEG5X9_clear();
		LCD_show_icon(LCD_PAUSE_ICON);
	        bcd_number[0] = ' ';
	        bcd_number[1] = ' ';
	        bcd_number[2] = ' ';
	        bcd_number[3] = ' ';
	    	LCD_SEG5X9_setX(0);		
	    	LCD_SEG5X9_show_string((u8 *)bcd_number);
	}

   }
    else if (Music_Play_var.bPlayStatus == MAD_STOP){

	play_slider_scr=0;
   	itoa4(music_device_info[device_active].wfileTotal);
    	if (music_device_info[device_active].wfileTotal <= 999)
        bcd_number[0] = ' ';
    	LCD_SEG5X9_setX(0);		
    	LCD_SEG5X9_show_string((u8 *)bcd_number);

   }	
}


/*----------------------------------------------------------------------------*/
/**@brief   Music 播放文件号显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_filenumber(void)
*/
/*----------------------------------------------------------------------------*/
void LCD_SEG5X9_show_filenumber(void)
{
    if(music_disp_file_dir){
       LCD_SEG5X9_show_char('F');	
    	itoa3(ff_api.fs_msg.dirCounter+1);
    	LCD_SEG5X9_show_string((u8 *)bcd_number);
    }
    else{		
    	itoa4(playfile.given_file_number);
    	if (playfile.given_file_number <= 999)
        bcd_number[0] = ' ';		
    	LCD_SEG5X9_show_string((u8 *)bcd_number);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   音量显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_volume(void)
*/
/*----------------------------------------------------------------------------*/
void LCD_SEG5X9_show_volume(void)
{
    LCD_SEG5X9_show_char('U');
    LCD_SEG5X9_setX(2);
    itoa2(main_vol_L);
    LCD_SEG5X9_show_string((u8 *)bcd_number);
}


/*----------------------------------------------------------------------------*/
/**@brief   红外输入文件号显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_IR_number(void)
*/
/*----------------------------------------------------------------------------*/
#ifndef NO_NUM_KEY_FUNC
void LCD_SEG5X9_show_IR_number(void)
{
    /*IR File Number info*/
    itoa4(input_number);
    LCD_SEG5X9_show_string((u8 *)bcd_number);
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief   EQ显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_eq(void)
*/
/*----------------------------------------------------------------------------*/
#if 0
void LCD_SEG5X9_show_eq(void)
{
    LCD_SEG5X9_show_char('E');
    LCD_SEG5X9_show_char('q');
    LCD_SEG5X9_setX(3);
    LCD_SEG5X9_show_number(Music_Play_var.bEQ%10);
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   循环模式显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_playmode(void)
*/
/*----------------------------------------------------------------------------*/
void LCD_SEG5X9_show_playmode(void)
{
    LCD_SEG5X9_show_string((u8 *)&playmodestr[playfile.play_mode][0]);
    //LCD_SEG5X9_var.state[0] |= REP_ICON;
}
#if 0
/*----------------------------------------------------------------------------*/
/**@brief   RTC 显示界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_RTC_main(void)
*/
/*----------------------------------------------------------------------------*/
void LCD_SEG5X9_show_RTC_main(void)
{
    itoa2(curr_time.bHour);
    LCD_SEG5X9_show_string((u8 *)bcd_number);
    itoa2(curr_time.bMin);
    LCD_SEG5X9_show_string((u8 *)bcd_number);

    if (UI_var.bCurMenu == MENU_RTC_SET)
    {
        if (RTC_setting_var.bCoordinate == 0)
            LCD_SEG5X9_var.bFlashIcon = BIT(0)|BIT(1);
        else if (RTC_setting_var.bCoordinate == 1)
            LCD_SEG5X9_var.bFlashIcon = BIT(2)|BIT(3);
    }
    else
        LCD_SEG5X9_var.bFlashIcon = 0;

    LCD_CON0 |= BIT(1);	            //[1]:DOTEN COM0-SEG0

    if (curr_alarm.bSw)
    {
        LCD_SEG5X9_var.seg0_state[0] |= ALARM_ICON;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   Alarm 显示界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LED5X7_show_alarm(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void LCD_SEG5X9_show_alarm(void)
{
    itoa2(curr_alarm.bHour);
    LCD_SEG5X9_show_string((u8 *)bcd_number);
    itoa2(curr_alarm.bMin);
    LCD_SEG5X9_show_string((u8 *)bcd_number);

    LCD_CON0 |= BIT(1);	            //[1]:DOTEN COM0-SEG0

    if (RTC_setting_var.bCoordinate == 0)
        LCD_SEG5X9_var.bFlashIcon = BIT(0)|BIT(1);
    else if (RTC_setting_var.bCoordinate == 1)
        LCD_SEG5X9_var.bFlashIcon = BIT(2)|BIT(3);
    else if (RTC_setting_var.bCoordinate == 2)
        LCD_SEG5X9_var.bFlashIcon |= 0xF;

    /*Alarm info - Switch On/Off*/
    if (curr_alarm.bSw)
    {
        LCD_SEG5X9_var.seg0_state[0] |= ALARM_ICON;
    }
}
#endif	

/*----------------------------------------------------------------------------*/
/**@brief   FM 模式主界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_fm_main(void)
*/
/*----------------------------------------------------------------------------*/
extern bool kt_band_mode;
void LCD_SEG5X9_show_fm_main(void)
{
    /*FM - Frequency*/
    itoa4(fm_mode_var.wFreq);
    if (fm_mode_var.wFreq <= 999)
        bcd_number[0] = ' ';

    LCD_SEG5X9_show_string((u8 *)bcd_number);

#if 1
    if(kt_band_mode){
	   LCD_show_icon(LCD_MW_ICON);		
	   LCD_show_icon(LCD_KHZ_ICON);		
	    //LCD_SEG5X9_var.seg0_state[3] |=AM_ICON;
	   // LCD_SEG5X9_var.seg1_state[0] |=KHZ_ICON;
    }
    else{		
	   LCD_show_icon(LCD_FM_ICON);			
	   //LCD_SEG5X9_var.seg1_state[0] |= FM_ICON;
    }
#endif
    if(radio_play_pause)
	   LCD_show_icon(LCD_PAUSE_ICON);			
		
}

/*----------------------------------------------------------------------------*/
/**@brief   FM 模式主界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_SEG4X8_show_fm_station(void)
*/
/*----------------------------------------------------------------------------*/
void LCD_SEG5X9_show_fm_station(void)
{
    /*FM - Station*/
    LCD_SEG5X9_show_char('C');
    LCD_SEG5X9_show_char('H');
    LCD_SEG5X9_setX(2);
    itoa2(fm_mode_var.bFreChannel);
    LCD_SEG5X9_show_string((u8 *)bcd_number);
#if 0	
    if(kt_band_mode){
	   LCD_show_icon(LCD_MW_ICON);		
    }
    else{		
	   LCD_show_icon(LCD_FM_ICON);			
    }	
#endif	
}

/*----------------------------------------------------------------------------*/
/**@brief   LCD 段码屏4X8 1/2bias 扫描驱动
   @param   void
   @return  void
   @author  Change.tsai
   @note    void LCD_drive4X8_12(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void LCD_drive5X9_12(void) AT(LCD_SEG_CODE)
{
    u8 cnt;

    if (Sys_HalfSec)
    {
       for(cnt=0;cnt<4;cnt++)
       {
            if (LCD_SEG5X9_var.bFlashIcon & BIT(cnt)) //数字位闪烁
            {
                LCD_SEG5X9_var.bShowBuff[cnt] = 0x0;
            }
       }
    }

    //LCD_show_icon(LCD_BAT_SHELL_ICON);
    ///////////数字赋值////////////
    LCDC5X9_P1buf.bCom3Seg1 = ((LCD_SEG5X9_var.bShowBuff[3] & (SEGA|SEGF))) | ((LCD_SEG5X9_var.bShowBuff[2] & (SEGA|SEGF))<<2) | ((LCD_SEG5X9_var.bShowBuff[1] & (SEGA|SEGF))<<4)| ((LCD_SEG5X9_var.bShowBuff[0] & (SEGA|SEGF))<<6);
    LCDC5X9_P1buf.bCom2Seg1 = ((LCD_SEG5X9_var.bShowBuff[3] & (SEGB|SEGG))>>2) | ((LCD_SEG5X9_var.bShowBuff[2] & (SEGB|SEGG))) | ((LCD_SEG5X9_var.bShowBuff[1] & (SEGB|SEGG))<<2)| ((LCD_SEG5X9_var.bShowBuff[0] & (SEGB|SEGG))<<4);
    LCDC5X9_P1buf.bCom1Seg1 = ((LCD_SEG5X9_var.bShowBuff[3] & (SEGC|SEGE))>>4) | ((LCD_SEG5X9_var.bShowBuff[2] & (SEGC|SEGE))>>2) | ((LCD_SEG5X9_var.bShowBuff[1] & (SEGC|SEGE)))| ((LCD_SEG5X9_var.bShowBuff[0] & (SEGC|SEGE))<<2);
    LCDC5X9_P1buf.bCom0Seg1 = ((LCD_SEG5X9_var.bShowBuff[3] & (SEGD))>>6) | ((LCD_SEG5X9_var.bShowBuff[2] & (SEGD))>>4) | ((LCD_SEG5X9_var.bShowBuff[1] & (SEGD))>>2)| ((LCD_SEG5X9_var.bShowBuff[0] & (SEGD)));

    LCDC5X9_P1buf.bCom0Seg1 |= (LCD_SEG5X9_var.seg1_state[0]);
	
    LCDC5X9_P0buf.bCom0Seg0 = (LCD_SEG5X9_var.seg0_state[0]);
    LCDC5X9_P0buf.bCom1Seg0 = (LCD_SEG5X9_var.seg0_state[1]);
    LCDC5X9_P0buf.bCom2Seg0 = (LCD_SEG5X9_var.seg0_state[2]);
    LCDC5X9_P0buf.bCom3Seg0 = (LCD_SEG5X9_var.seg0_state[3]);

    ///////////状态赋值////////////



    COM0_SEG01(LCDC5X9_P1buf.bCom0Seg1);
    COM1_SEG01(LCDC5X9_P1buf.bCom1Seg1);
    COM2_SEG01(LCDC5X9_P1buf.bCom2Seg1);
    COM3_SEG01(LCDC5X9_P1buf.bCom3Seg1);
    COM4_SEG01(LCDC5X9_P1buf.bCom4Seg1);

    COM0_SEG00(LCDC5X9_P0buf.bCom0Seg0);
    COM1_SEG00(LCDC5X9_P0buf.bCom1Seg0);
    COM2_SEG00(LCDC5X9_P0buf.bCom2Seg0);
    COM3_SEG00(LCDC5X9_P0buf.bCom3Seg0);
}
#endif
