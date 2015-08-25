#ifndef _FM_API_H_
#define _FM_API_H_

#include "config.h"

#ifdef __IAR_SYSTEMS_ICC__

bool chk_fm_dev_online(void);
void init_fm_rev(void);
bool set_fre(u8);
void fm_rev_powerdown(void);
void save_fre(u16 fre);
void fm_module_mute(u8 flag);
void fm_set_ch(u8 db);

void save_curr_freq(u16 wFreq);
u16 read_curr_freq(void);

void save_curr_channel(u8 c_channel);
u8 read_curr_channel(void);
void save_tatol_channel(u8 a_channel);
u8 read_tatol_channel(void);
void restore_station_from_ch(void);

void fm_info_init(void);
u8 fm_scan_msg(void);
bool fm_scan(u8 mode);
void radio_band_set(u8 band_mod);
void radio_band_switcher(void);
void reset_radio_mem(u8 preset_band);

#endif  /*  __IAR_SYSTEMS_ICC__ */

#define FM_CUR_FRE          0
#define FM_FRE_DEC          1
#define FM_FRE_INC			2

#define FM_SCAN_STOP        0
#define FM_SCAN_PREV        1
#define FM_SCAN_NEXT		2
#define FM_SCAN_ALL         3
#define FM_SCAN_END         4

#define MAX_FRE    1080
#define MIN_FRE	   875
#define MAX_CHANNL (MAX_FRE - MIN_FRE + 1)


#define MAX_MW_FRE    		1692
#define MIN_MW_FRE	   		531
#define MAX_MW_CHANNL 	(((MAX_MW_FRE - MIN_MW_FRE)/AM_9KHz_STEP)+ 1)

enum Band_Mode	
{
	FM_MODE,
	MW_MODE,
};


struct Str_Band
{
	//enum Band_Mode	Band;						// 频段
	u16			Band_Top;					//	tune台频段上门限
	u16			Band_Bottom;				//	tune台频段下门限
	//u16			Seek_Up_Limit;				//	seek频段上门限
	//u16			Seek_Down_Limit;			//	seek频段下门限
	//u8			Min_Step;					//
	u8			Max_channel;					//
	u8			Seek_Step;					// SeekFromCurrentCh 函数用的频率步进
	u8			ValidStation_Step;			// ValidStation 函数用的频率步进
	u8			AFCTH_Prev;					//
	u8			AFCTH;						//
	u8			AFCTH_Next;					// 
};
  
#endif  /*  _FM_API_H_   */
