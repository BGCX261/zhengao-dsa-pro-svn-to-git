/*--------------------------------------------------------------------------*/
/**@file     uart.h
   @brief    ´®¿Ú´òÓ¡Çý¶¯
   @details
   @author
   @date   2011-4-26
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _UART_
#define _UART_

#include "config.h"

#ifdef __C51__
void uart_init(void);
void putbyte (char c);
void sys_printf(char *str);
void printf_buf(u8 _xdata *buf, u16 len);
void printf_u8(u8 dat);
void deg_string(u8 *p);
#endif

#endif
