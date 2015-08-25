/*************************************************************/
/** @file:voice_table.h
    @brief:
    @details:
    @author:Juntham
    @date: 2012-08-02,14:26
    @note:
*/
/*************************************************************/
#ifndef __VOICE_TABLE_H__
#define __VOICE_TABLE_H__

#include "config.h"

#ifdef __SMART_CPU__


typedef struct _voicetable
{
    u8 const _code * table_addr;
    u16 table_len;
}voicetable;

#endif

#endif
