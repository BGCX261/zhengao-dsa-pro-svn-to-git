/*--------------------------------------------------------------------------*/
/**@file   my_printf.h
   @brief    格式化输出头文件
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef   _MY_PRINTF_H_
#define  _MY_PRINTF_H_

#include "config.h"
#ifdef __C51__
#include "stdarg.h"
extern void my_putchar(u8);
#define printf_cmd(cmd) my_putchar(cmd)
void printf_cmd(u8 cmd);
void printf_str(u8 *str);
void my_printf(u8 _code * fmt, ...) compact;

#endif

/*
%:命令转换符:
x: 设置X坐标
y: 设置Y坐标
m: 显示图片,通过参数
e: 显示字符大小加倍
n: 显示字符大小正常
a: 显示小数字
k: 显示小数字，并且加上划线
p: 显示频谱
f: LED 屏 闪动控制,指定ICON部分闪动
c: 清除所有显示区域
*/

#endif