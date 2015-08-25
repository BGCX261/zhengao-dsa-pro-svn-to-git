/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    一些基本参数的配置
   @author
   @date   2010-12-13
   @note   AC309N
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"

#ifndef _CONFIG_
#define _CONFIG_

#include "AC309N.h"
#include "typedef.h"
#include "entry.h"
#include "clock.h"


#define USB_DEVICE_ENABLE		1		///<根据客户选用的bsp库，对应地选择是否打开，选用PC校准HPRC时钟时，须置1
#define ENABLE_MUSIC_OTP        0      ///<otp音乐使能
#ifdef __C51__
#include "intrins.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

extern u8 _xdata P0_IE;
void port_pnie_init(void);
void port_pnie(void);

typedef enum
{
    DIS_SD_CMD_CHK = 0,	///<在命令检测SD卡在线状态的情况下，暂停SD在线检测
    EN_SD_CMD_CHK,		///<在命令检测SD卡在线状态的情况下，恢复SD在线检测
    SET_SD_H_CHK,		///<在命令检测SD卡在线状态的情况下，SD不在线时检测100MS一次
    SET_SD_L_CHK,		///<在命令检测SD卡在线状态的情况下，SD不在线时检测1S一次
}Sd_api_cmd;


typedef enum {
	LED_FLASH_ON,
	LED_FLASH_VERY_FAST,
	LED_FLASH_FAST,
	LED_FLASH_NOR,
	LED_FLASH_SLOW,
	LED_FLASH_STOP,
	
}LED_FLASH_TYPE;

#if 0
enum
{
    MUSIC_MODE = 0,
#if USB_DEVICE_ENABLE
    USB_DEVICE_MODE,
#endif
    FM_RADIO_MODE,
    AUX_MODE,
    RTC_MODE,
	OTP_DECODE_MODE,
    IDLE_MODE,
};
#endif
enum
{
    SD_CLK_P20 =0,                
    SD_CLK_P30 ,
};

typedef enum
{
    SYS_MP3DECODE_USB,
    SYS_MP3DECODE_SD,
    
#if defined(EXCHANGE_FM_AUX_PRIO)    
    SYS_AUX,
    SYS_FMREV,
#ifdef RADIO_AM_WM_ENABLE
    SYS_AMREV,
#endif      

#else

    SYS_FMREV,
#ifdef RADIO_AM_WM_ENABLE
    SYS_AMREV,
#endif    
    SYS_AUX,
    
#endif

#if defined(IPONE_INDEPENDENT_MODE)	
    SYS_IPH,
#endif    

    SYS_RTC,
    SYS_IDLE,
    SYS_USB_DEVICE,
}SYS_WORK_MODE;
#endif


//显示屏选择
#define DISP_LCD_12832        0
#define DISP_LCD_9632         1
#define DISP_LCD_12864_SER    2
#define DISP_LCD_12864_PAR    3
#define DISP_LED5X7           4
#define DISP_LCD_5X7          5
#define DISP_NONE		          0xFF

#if defined(NO_LED_DISPLAY)
#define monitor              DISP_NONE //DISP_LED5X7
#else
#define monitor              DISP_LED5X7 //DISP_LED5X7
#endif

#if ((monitor == DISP_LCD_12832) || (monitor == DISP_LCD_9632) || (monitor == DISP_LCD_12864_SER)|| (monitor == DISP_LCD_12864_PAR))			//是否为段码LCD屏
#define DISP_DOT_LCD			1
#else
#define DISP_DOT_LCD			0
#endif

#if (monitor == DISP_LED5X7)			//是否为数码管LED屏
#define DISP_SEG_LED            1
#else
#define DISP_SEG_LED			0
#endif


///<输入时钟选择，具体请见clock.h
/*(PLL_IN_OSC0_32K | PLL_IN_OSC0_4M | PLL_IN_OSC0_12M | PLL_IN_OSC1_4M | PLL_IN_OSC1_12M | PLL_IN_HPRC)*/
/*------------------------------------------------------------------------------------*/
/*
当晶振源为PLL_IN_HPRC，USE_SOF_PLL:0：选用P00/P01外挂12M晶振开机时矫正，不挂12M不校准;
								   1：选用PC矫正方法,此功能需有PC功能;	 
当晶振源为PLL_IN_HPRC，USE_SOF_PLL为1时，请确认已在app.lin里添加overlay(* ! (sof_isr))								   			
*/
/*------------------------------------------------------------------------------------*/
#define INPUT_OSC_SELECT        	PLL_IN_OSC0_32K//PLL_IN_HPRC////PLL_IN_OSC1_12M//
#define USE_SOF_PLL    	 			0 
#define SHARE_32768_PERIPHERALS    0					///<是否与外设共用32768晶体，0：不共用，1：共用晶体（如收音等）
#ifdef  USE_RTC_FUNC
#define RTC_ENABLE              1           			///<RTC使能，如果不需要使用RTC功能，此处填0
#else
#define RTC_ENABLE              0           			///<RTC使能，如果不需要使用RTC功能，此处填0
#endif
#define DEBUG_SOF_PLL	 0		 ///<调试所用

///////work mode
#if RTC_ENABLE
#define MAX_WORK_MODE	 SYS_IDLE
#else
#define MAX_WORK_MODE	 SYS_IDLE
#endif

#define IDLE_WORK_MODE   SYS_IDLE

//音乐播放功能选择

#define    BREAK_POINT_PLAY_EN				1			//是否允许断点播放功能
#define    LAST_MEM_FILE_PLAY_EN            0			//是否允许记忆文件序号播放功能
#define    ID3_TAG_EN						1
#define    FF_FR_EN                         1			//是否允许快进快退功能
#define    FF_FR_MUSIC                      1			//在快进快退时，是否需要听到声音
#define    MUSIC_SPECTRUM_EN                0			//是否允许计算MUSIC频谱
#define    AMUX_SPECTRUM_EN	                0			//是否允许计算AMUX频谱
#define    BURST_OUT_POINT_SAVE_ENABLE      0			//突然断电使能位,1有效,3.3V需要电容支持至少100μF
#define    MUSIC_FADE_OUT_EN				1			//切换歌曲的淡出使能， 1有效




//sd检测模式
#define SDMMC_CMD_MODE   1	  ///<使用SD card 命令查询模式
#define SDMMC_CLK_MODE   0	  ///<使用SD clk 查询模式
#define SDMMC_GPIO_MODE  0	  ///<使用独立的GPIO做SD在线查询模式


#endif
