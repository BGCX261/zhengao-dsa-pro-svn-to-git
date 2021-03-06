/*--------------------------------------------------------------------------*/
/**@file     uart.c
   @brief    ���ڴ�ӡ����
   @details
   @author
   @date   2011-4-26
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"
#include "uart.h"
#include "resource.h"
#include "rtc_api.h"

extern RTC_TIME _xdata curr_time;

void uart_init(void)
{
#if defined (_USE_UART_P0_)
    UTBAUD = (48000000/(8 * 115200)) - 1;	//25;//0x37;					/* 25: cpu 24M, 115200bps*/	/*77 for 384*/ /*0x137 for 9600*/
    UTCON = 0x01;
	
    P0DIR &= ~(1<<6);
    P0DIR |= (1<<7);
    UTCON = 0x41;							/* enable uart */
#elif defined(_USE_UART_P2_)
    UTBAUD = (48000000/(8 * 115200)) - 1;	//25;//0x37;					/* 25: cpu 24M, 115200bps*/	/*77 for 384*/ /*0x137 for 9600*/
    UTCON = 0x01;
	
    P2DIR &= 0xef;							/* P06 for transmit */
    P2DIR |= 0x20;							/* P07 for receive */
    UTCON = 0x41;							/* enable uart */
#else
    UTCON = 0x00;							/* disable uart */
#endif
}

#pragma disable
void putbyte(char c)
{
    UTBUF = c;
    while (!(UTSTA & 0x80))
    {
    }
}

char putchar (char c)
{
    if (c == '\n')
    {
        putbyte(0x0d);
        putbyte(0x0a);
    }
    else
    {
        putbyte(c);
    }

    return (c);
}
void sys_printf(char *str)
{
#if 0
      read_rtc(&curr_time);
      chk_date_err();
      printf("%u:%u:%u   ",(u16)curr_time.hour,(u16)curr_time.min,(u16)curr_time.sec);
#endif	  
      printf(str);
      printf("\r\n"); 	  

}

/*
void printf_buf(u8 _xdata *buf, u16 len)
{
    u16 i;

    printf(":%04X", (u16)buf);
    for (i = 0; i < len; i++)
    {
        if ((i % 16) == 0)
            printf("\n");
        printf("%02bX ", buf[i]);
    }

    printf("\n");
}


void deg_string(u8 *p)
{
   while(*p)
   {
       putchar(*p);
       p++;
   }
}

void get_hex_data(u8 dat)
{
   u8 dat0;
   if(dat<0x0a)
   {
       dat0 = dat+'0';
   }
   else
   {
       dat0 = dat+'A'-10;
   }
   putchar(dat0);
}

void printf_u32(u32 dat)
{
    putchar('\n');
    get_hex_data(((u8 *)(&dat))[0] >> 4);
    get_hex_data(((u8 *)(&dat))[0] & 0xf);

    get_hex_data(((u8 *)(&dat))[1] >> 4);
    get_hex_data(((u8 *)(&dat))[1] & 0xf);

    get_hex_data(((u8 *)(&dat))[2] >> 4);
    get_hex_data(((u8 *)(&dat))[2] & 0xf);

    get_hex_data(((u8 *)(&dat))[3] >> 4);
    get_hex_data(((u8 *)(&dat))[3] & 0xf);
    putchar('\n');
}

void printf_u8(u8 dat)
{
    get_hex_data(dat >> 4);
    get_hex_data(dat & 0xf);
    putchar(' ');
	putchar('\n');
}
*/
