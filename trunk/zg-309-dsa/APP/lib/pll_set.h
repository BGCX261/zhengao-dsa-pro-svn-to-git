/*--------------------------------------------------------------------------*/
/**@file     pll_set.h
   @brief    pll_set头文件
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _PLL_SET_
#define _PLL_SET_
#include "config.h"

#ifdef __C51__

/*-----------------------------------------------------------------------------------*/
/**@brief    选用HPRC时钟时,P01/P02外挂12M时钟开机时校准HPRC时钟函数，
			 校准后P00/P01可为普通IO用
   @param    无
   @return   无
   @note     void deal_clk(void)
*/
/*-----------------------------------------------------------------------------------*/
void deal_clk(void);

#endif



#endif               