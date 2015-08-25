/*--------------------------------------------------------------------------*/
/**@file   dac.h
   @brief  dac头文件
   @details
   @author
   @date   2011-5-18
   @note
*/
/*----------------------------------------------------------------------------*/
#include "dac.h"
#include "uart.h"

/*----------------------------------------------------------------------------*/
/**@brief    功放Mute开关函数
   @param	 mute：Mute开关
   @return	 无
   @note     void amp_mute(bool mute)
*/
/*----------------------------------------------------------------------------*/
#if 0
#define AMP_MUTE_PORT_INIT() 	 P0DIR &= ~BIT(1);P0PU &= ~BIT(1);P0PD &= ~BIT(1)
#define AMP_MUTE_DISABLE() 	 P01 = 0
#define AMP_MUTE_ENABLE() 	 P01 = 1
#endif 

void ext_amp_mute(bool mute)
{
    INIT_MUTE_PORT();
    if (mute)
    {
    	 //sys_printf(" --->AMP_MUTE_ENABLE  ");
        AMP_MUTE_ENABLE();
    }
    else
    {
      	 //sys_printf(" --->AMP_MUTE_DISABLE  ");
        AMP_MUTE_DISABLE();
    }
}

