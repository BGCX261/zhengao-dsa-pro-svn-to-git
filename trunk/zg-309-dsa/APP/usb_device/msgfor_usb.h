/*--------------------------------------------------------------------------*/
/**@file     msgfor_usb.h
   @brief    usb从机任务头
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _MSGFOR_USB_H_
#define _MSGFOR_USB_H_

#ifdef __C51__
#include "config.h"
#include "key.h"
#include "disp.h"
#include "msgfor_hot.h"


void usb_audio_massstorage(void);
#endif
//#define USB_AUDIO         0x1 	//USB Speaker & Microphone
#define USB_HID             0x02
#define USB_MASS            0x04
#define USB_SPEAKER			0x08
#define USB_MIC			  	0x10

#define USB_DEVICE_CFG        (USB_MASS | USB_SPEAKER | USB_MIC |USB_HID)//(USB_SPEAKER | USB_HID | USB_MASS)

#define USB_AUDIO_STOP        0x80
#define USB_AUDIO_FASTFORWARD 0x40
#define USB_AUDIO_PREFILE     0x20
#define USB_AUDIO_NEXTFILE    0x10
#define USB_AUDIO_PP          0x08
#define USB_AUDIO_MUTE        0x04
#define USB_AUDIO_VOLDOWN     0x02
#define USB_AUDIO_VOLUP       0x01
#define USB_AUDIO_NONE        0x00

#endif