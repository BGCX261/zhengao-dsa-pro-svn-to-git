/*--------------------------------------------------------------------------*/
/**@file     tunch_key.h
   @brief    IICÍ·ÎÄ¼þ
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _TUNCH_KEY_
#define _TUNCH_KEY_
#include "config.h"
#include "clock.h"

#ifdef __C51__
    void tch_key_init(u8 clk);
    u8 tunch_value(void);
	void crc_key_prd(u8 clk);
#endif

#endif

