/*--------------------------------------------------------------------------*/
/**@file   RDA5807.h
   @brief  RDA5807驱动头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _RDA_5807_H_
#define _RDA_5807_H_
#include "iic.h"
#include "typedef.h"


#ifdef __C51__
void init_rda5807(void);
bool set_fre_rda5807(u16 fre);
void rda5807_poweroff(void);
bool rda5807_read_id(void);
void  rda5807_mute(u8 flag);
void rda5807_setch(u8 db);
#endif

#endif