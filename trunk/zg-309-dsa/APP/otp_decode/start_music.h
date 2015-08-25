/*--------------------------------------------------------------------------*/
/**@file      start_music.h
   @brief     “Ù¿÷ø‚Õ∑Œƒº˛
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _START_MUSIC_H_
#define _START_MUSIC_H_
#include "config.h"
#include "uart.h"
#include "eq.h"
#include "id3.h"
#include "dac.h"


void music_play_otp(void);
u16 read_file_otp1(u8 _xdata *buffer, u16 len);
u8 seek_file_otp1(u8 type, u16 offsize_L, u16 offsize_H);
u8 file_status_otp1(void);


u16 read_file_otp(u8 _xdata *buffer, u16 len);
u8 seek_file_otp(u8 type, u16 offsize_L, u16 offsize_H);
u8 file_status_otp(void);

#endif