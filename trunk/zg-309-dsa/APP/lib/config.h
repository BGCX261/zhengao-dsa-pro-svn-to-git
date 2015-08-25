/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    һЩ��������������
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


#define USB_DEVICE_ENABLE		1		///<���ݿͻ�ѡ�õ�bsp�⣬��Ӧ��ѡ���Ƿ�򿪣�ѡ��PCУ׼HPRCʱ��ʱ������1
#define ENABLE_MUSIC_OTP        0      ///<otp����ʹ��
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
    DIS_SD_CMD_CHK = 0,	///<��������SD������״̬������£���ͣSD���߼��
    EN_SD_CMD_CHK,		///<��������SD������״̬������£��ָ�SD���߼��
    SET_SD_H_CHK,		///<��������SD������״̬������£�SD������ʱ���100MSһ��
    SET_SD_L_CHK,		///<��������SD������״̬������£�SD������ʱ���1Sһ��
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


//��ʾ��ѡ��
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

#if ((monitor == DISP_LCD_12832) || (monitor == DISP_LCD_9632) || (monitor == DISP_LCD_12864_SER)|| (monitor == DISP_LCD_12864_PAR))			//�Ƿ�Ϊ����LCD��
#define DISP_DOT_LCD			1
#else
#define DISP_DOT_LCD			0
#endif

#if (monitor == DISP_LED5X7)			//�Ƿ�Ϊ�����LED��
#define DISP_SEG_LED            1
#else
#define DISP_SEG_LED			0
#endif


///<����ʱ��ѡ�񣬾������clock.h
/*(PLL_IN_OSC0_32K | PLL_IN_OSC0_4M | PLL_IN_OSC0_12M | PLL_IN_OSC1_4M | PLL_IN_OSC1_12M | PLL_IN_HPRC)*/
/*------------------------------------------------------------------------------------*/
/*
������ԴΪPLL_IN_HPRC��USE_SOF_PLL:0��ѡ��P00/P01���12M���񿪻�ʱ����������12M��У׼;
								   1��ѡ��PC��������,�˹�������PC����;	 
������ԴΪPLL_IN_HPRC��USE_SOF_PLLΪ1ʱ����ȷ������app.lin�����overlay(* ! (sof_isr))								   			
*/
/*------------------------------------------------------------------------------------*/
#define INPUT_OSC_SELECT        	PLL_IN_OSC0_32K//PLL_IN_HPRC////PLL_IN_OSC1_12M//
#define USE_SOF_PLL    	 			0 
#define SHARE_32768_PERIPHERALS    0					///<�Ƿ������蹲��32768���壬0�������ã�1�����þ��壨�������ȣ�
#ifdef  USE_RTC_FUNC
#define RTC_ENABLE              1           			///<RTCʹ�ܣ��������Ҫʹ��RTC���ܣ��˴���0
#else
#define RTC_ENABLE              0           			///<RTCʹ�ܣ��������Ҫʹ��RTC���ܣ��˴���0
#endif
#define DEBUG_SOF_PLL	 0		 ///<��������

///////work mode
#if RTC_ENABLE
#define MAX_WORK_MODE	 SYS_IDLE
#else
#define MAX_WORK_MODE	 SYS_IDLE
#endif

#define IDLE_WORK_MODE   SYS_IDLE

//���ֲ��Ź���ѡ��

#define    BREAK_POINT_PLAY_EN				1			//�Ƿ�����ϵ㲥�Ź���
#define    LAST_MEM_FILE_PLAY_EN            0			//�Ƿ���������ļ���Ų��Ź���
#define    ID3_TAG_EN						1
#define    FF_FR_EN                         1			//�Ƿ����������˹���
#define    FF_FR_MUSIC                      1			//�ڿ������ʱ���Ƿ���Ҫ��������
#define    MUSIC_SPECTRUM_EN                0			//�Ƿ��������MUSICƵ��
#define    AMUX_SPECTRUM_EN	                0			//�Ƿ��������AMUXƵ��
#define    BURST_OUT_POINT_SAVE_ENABLE      0			//ͻȻ�ϵ�ʹ��λ,1��Ч,3.3V��Ҫ����֧������100��F
#define    MUSIC_FADE_OUT_EN				1			//�л������ĵ���ʹ�ܣ� 1��Ч




//sd���ģʽ
#define SDMMC_CMD_MODE   1	  ///<ʹ��SD card �����ѯģʽ
#define SDMMC_CLK_MODE   0	  ///<ʹ��SD clk ��ѯģʽ
#define SDMMC_GPIO_MODE  0	  ///<ʹ�ö�����GPIO��SD���߲�ѯģʽ


#endif
