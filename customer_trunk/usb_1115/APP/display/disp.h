/*--------------------------------------------------------------------------*/
/**@file   disp.h
   @brief    显示模块头文件
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef   _DISP_H_
#define  _DISP_H_

#include "config.h"
#include "my_printf.h"

#ifdef __C51__

enum
{
    MENU_NULL = 0,
    MENU_PLAY,
    MENU_PAUSE,
    MENU_MAIN_VOL,
    MENU_EQ,
    MENU_POWER_UP,
    MENU_POWER_OFF,
    MENU_PLAYMODE,
    MENU_NOFILE,
    MENU_NODEVICE,
    MENU_PLAY_TIME,
    MENU_FILENUM,
    MENU_INPUT_NUMBER,
    MENU_WAIT,
    MENU_USBDEV_MAIN,
    MENU_MUSIC_MAIN,
    MENU_FM_MAIN,
    MENU_FM_DISP_FRE,
    MENU_FM_FIND_STATION,
    MENU_FM_CHANNEL,
    MENU_USBREMOVE,
    MENU_SDREMOVE,
    MENU_SCAN_DISK,
    MENU_AUX,
    MENU_RTC,
    MENU_RTC_PWD,
    MENU_ALM_UP,
    MENU_ALM_SET,
    MENU_ALM_REQUEST,


    MENU_200MS_REFRESH = 0x80,
    MENU_100MS_REFRESH,
    MENU_SET_EQ,
    MENU_SET_PLAY_MODE,
    MENU_HALF_SEC_REFRESH,
    MENU_POWER_DOWN,
};

void disp_power_on(void);
void disp_fm_freq(void);
void disp_input_number(u16 num);
void disp_main_vol(u8 vol);
void disp_port(u8 menu);
void disp_music_play_time(void);
void disp_music_format(void);
void disp_roll_ctrl(u8 mode);
void disp_main_menu_refresh(void);
void disp_eq(void);
void disp_play_mode(void);
void init_display(void);
void set_pos_x(u8 x);
void set_pos_y(u8 y);
void disp_bmp(u8 id);
void clear_display(void);
void disp_flash_icon(u8 id);
void disp_cmd(u8 key);
void set_brightness(u8 br);
void set_brightness_fade_out(void);
void set_brightness_all_on(void);

#endif

#define SUB_MENU_TIME         (1*2)

#endif