/*************************************************************/
/** @file:voice_play.c
    @brief:
    @details:
    @author:Juntham
    @date: 2012-08-02,13:46
    @note:
*/
/*************************************************************/
#include "custom_config.h"

#ifdef OTP_MUSIC_FUNC_ENABLE

#include "play_voice.h"
#include "play_file.h"
#include "key.h"
#include "device.h"
#include "hot_msg.h"
#include "voice_table.c"
#include "break_point.h"
#include "music_play.h"

_no_init const u8 _code * _data voice_table;

/*----------------------------------------------------------------------------*/
/** @brief:
    @param:
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
_near_func FRESULT my_seek(FIL _xdata *fp, u8 seek_mode, u32 len)
{   
    if(seek_mode == SEEK_SET)
    {
        music_file.fptr = len;
    }
    else
    {
        music_file.fptr += len;
    }
    
    return FR_OK;
}

/*----------------------------------------------------------------------------*/
/** @brief:
    @param:
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
_near_func u16 my_read (FIL _xdata *fp, u8 _xdata *buffer, u16 btr)
{
    u16 fsize,fptr, len;
    u16 rlen;
    
    fsize = music_file.fsize;
    fptr = music_file.fptr;

    len = (fsize - fptr);
    
    if (btr > len)
    {
        rlen = len;
        my_memset(buffer + rlen, 0, btr - rlen);            //将不够的部分清0
        btr = len;		                                /* Truncate btr by remaining bytes */
    }
    
    rlen = btr;
    
    my_memcpy(buffer, (u8 *)(voice_table+fptr), btr);
    //printf_buf(buffer, btr);
    music_file.fptr = fptr+btr;
    return rlen;
}

/*----------------------------------------------------------------------------*/
/** @brief:
    @param:
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
bool voice_play_file(u8 index)
{
    init_decode_api(my_read, my_seek);
    voice_table = voice_main_table[index].table_addr;
    music_file.fsize = voice_main_table[index].table_len;
    decode_init(0);
    set_eq(0, 0);
    start_decode();

    ext_pa_mute(PA_UNMUTE);   

    while(1)
    {
        WDT_CLEAR();

        if (dec_exit)           //用户提前结束
            return false;

        if (Music_Play_var.bPlayStatus == MAD_STOP)
            return true;
    }
}

/*----------------------------------------------------------------------------*/
/** @brief:
    @param:
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
bool voice_play_by_index(u16 index)
{
    stop_decode();
    voice_playing = 1;
    dec_exit = 0;

    if (!voice_play_file(index))
    {
        stop_decode();
        Music_Play_var.bPlayStatus = MAD_VOICE_STOP;
        voice_playing = 0;
        return false;
    }
	
    ext_pa_mute(PA_MUTE);
	
    //my_puts("play voice end\n");
    stop_decode();
    Music_Play_var.bPlayStatus = MAD_VOICE_STOP;
    voice_playing = 0;
         
    return true;
}
#endif
