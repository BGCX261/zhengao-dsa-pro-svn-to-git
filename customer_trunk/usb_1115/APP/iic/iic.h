/*--------------------------------------------------------------------------*/
/**@file     iic.h
   @brief    IIC头文件
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _IIC_H_
#define _IIC_H_

#include "config.h"

#define USE_RTC_RAM       0///< 1:使用RTC内部的64个字节的RAM做记忆，掉电不能记忆；0:使用EEROM做记忆

#ifdef __C51__

#include "gpio_if.h"

#define iic_delay()      delay(200)

extern u8 read_info(u8 addr);
extern void write_info(u8 addr,u8 dat);
extern u8 read_rtc_ram(u8 addr);
extern void write_rtc_ram(u8 addr,u8 dat);

void iic_init_io(void);
void iic_start(void);
void iic_stop(void);
bool r_ack(void);
void s_ack(u8 flag);
u8 iic_revbyte_io( void );
u8 iic_revbyte( u8 para );
void iic_sendbyte_io(u8 byteI2C);
bool iic_sendbyte(u8 byte);

void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n);
void iic_readn(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n);


u8 read_eerom(u8 iic_addr);
void write_eerom(u8 addr,u8 dat);
void  eeprom_page_write_start(void);
void  eeprom_page_write_stop(void);
#endif





#define MEM_FRE            0
#define MEM_CHAN		   1
#define MEM_CHANNL         2
#define MEM_FM_LEN         26//28

#define MEM_ACTIVE_DEV     29


#define MEM_USB_PLAYPOINT_ID0   46//30
#define MEM_USB_PLAYPOINT_ID1	48//32
#define MEM_USB_PLAYPOINT_ID2   52//36


#define MEM_EQ_MODE        40
#define MEM_PLAY_MODE      41
#define MEM_VOL            42
#define MEM_SYSMODE        43

#define MEM_SD_PLAYPOINT_ID0   30// 46
#define MEM_SD_PLAYPOINT_ID1   32//	48
#define MEM_SD_PLAYPOINT_ID2   36// 52


#define MEM_ALARM_0_HOUR  	60
#define MEM_ALARM_0_MIN	  	61
//#define MEM_ALARM_0_DAYS	62
//#define MEM_ALARM_1_HOUR  62
//#define MEM_ALARM_1_MIN	  63
//#define MEM_ALARM_2_HOUR  64
//#define MEM_ALARM_2_MIN	  65
//#define MEM_ALARM_3_HOUR  66
//#define MEM_ALARM_3_MIN	  67
//#define MEM_ALARM_4_HOUR  68
//#define MEM_ALARM_4_MIN	  69
//#define MEM_ALARM_ALL_SW  70	///<按位存储闹钟开关状态
#define EEPROM_SIGN			127		 ///<用作EEPROM识别位
///<PC校准HPRC时，用来校验是否第一次应用RAM或者EEPROM
///<非PC校准HPRC时，没用到以下存储
#define MEM_0X55_DAT  			44		
#define MEM_0XAA_DAT  			45		

///<PC校准HPRC时，以下4个连续BYTE存放PC校准HPRC时钟数据
///<非PC校准HPRC时，以下存储空间可为其他所有
#define MEM_PLLCON0     		60		///<60	   
#define MEM_PLLCON1  MEM_PLLCON0+1	 	///<61	   
#define MEM_NULL0    MEM_PLLCON0+2	 	///<62
#define MEM_NULL1    MEM_PLLCON0+3	 	///<63

#define MEM_BASE	66
#define MEM_TREB 	67
#define MEM_BAL 	68
#define MEM_FADE 	69

#endif
