#ifndef _ID3_H_
#define _ID3_H_

#ifdef __C51__
#include "config.h"

#include "tff.h"

#include "device.h"
#define ID3_DISP_BUF_LEN				128

void get_music_tag(void);
//void get_filetag(u8 _xdata * buffer);
#endif

#endif
