$NOMOD51
                NAME    OTP_MUSIC_SECTION
#include "AC309N.h"
#include "config.h"
#if ENABLE_MUSIC_OTP

?PR?_read_file_otp?otp_music SEGMENT CODE 		 
        RSEG     ?PR?_read_file_otp?otp_music
        EXTRN    CODE (_read_file_otp1)
        PUBLIC   _read_file_otp
_read_file_otp:
        PUSH    DPCON
        MOV     DPCON,#0x0             
        CALL    _read_file_otp1
        POP     DPCON
        RET

?PR?_seek_file_otp?otp_music SEGMENT CODE 		 
        RSEG     ?PR?_seek_file_otp?otp_music
        EXTRN    CODE (_seek_file_otp1)
        PUBLIC   _seek_file_otp
_seek_file_otp:
        PUSH    DPCON
        MOV     DPCON,#0x0             
        CALL    _seek_file_otp1
        POP     DPCON
        RET

?PR?file_status_otp?otp_music SEGMENT CODE 		 
        RSEG     ?PR?file_status_otp?otp_music
        EXTRN    CODE (file_status_otp1)
        PUBLIC   file_status_otp
file_status_otp:
        PUSH    DPCON
        MOV     DPCON,#0x0             
        CALL    file_status_otp1
        POP     DPCON
        RET
#endif
    END