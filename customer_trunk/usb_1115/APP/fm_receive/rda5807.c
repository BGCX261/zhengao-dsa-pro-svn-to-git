/*--------------------------------------------------------------------------*/
/**@file     rda5807.c
   @brief    RDA5807收音底层驱动
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/



#include "rda5807.h"
#include "clock.h"

#define RDA5807_WR_ADDRESS      0x20       ///<RDA5807 写地址
#define RDA5807_RD_ADDRESS      0x21       ///<RDA5807 读地址

u8 _idata rda5807_dat[12] _at_ 0x80;    ///<5807控制寄存器映射表
u8 _idata read_dat[4] _at_ (0x80 + 12); /** RDA5807 状态寄存器映射表  **/

#define rda5807_stc() (read_dat[0] & (1 << 6))       ///<锁频结束
#define rda5807_true() (read_dat[2] & (1 << 0))      ///<是否有台
#define rda5807_rssi() ((read_dat[2] >> 1))          ///<接收信号强度
#define rda5807_st()   (read_dat[0] & (1 << 2))
/*----------------------------------------------------------------------------*/
/**@brief    RDA5807写寄存器函数
   @param    num 需要的数目
   @return   无
   @note     void rda5807_write(u8 num)
*/
/*----------------------------------------------------------------------------*/
void rda5807_write(u8 num)
{
    iic_write(RDA5807_WR_ADDRESS,0xff,rda5807_dat,num);
}
/*----------------------------------------------------------------------------*/
/**@brief    RDA5807读寄存器函数
   @param    需要读取的数目
   @return   无
   @note     void rda5807_read(u8 num)
*/
/*----------------------------------------------------------------------------*/
void rda5807_read(u8 num)
{
    iic_readn(RDA5807_RD_ADDRESS,0xff,read_dat,num);
}
/*----------------------------------------------------------------------------*/
/**@brief    RDA5807 初始化
   @param    无
   @return   无
   @note     void init_rda5807(void)
*/
/*----------------------------------------------------------------------------*/

void init_rda5807(void)
{
    read_dat[0] = 0;
    read_dat[1] = 0;
    read_dat[2] = 0;
    read_dat[3] = 0;
    rda5807_dat[0] = 0;
    rda5807_dat[1] = 2;
    rda5807_dat[2] = 0;
    rda5807_dat[3] = 0x10;
    rda5807_dat[4] = 0x04;
    rda5807_dat[5] = 0x0;
    rda5807_dat[6] = 0x80 | 0x6;
    rda5807_dat[7] = 0xbf;
    rda5807_dat[8] = 0x0;
    rda5807_dat[9] = 0x0;
    rda5807_dat[10] = 0x7e;
    rda5807_dat[11] = 0xc6;
    rda5807_write(2);
    delay_10ms(40);
    rda5807_dat[0] = 0xc0;
    rda5807_dat[1] = 0x01;
    rda5807_dat[7] &=~0x0F;
    rda5807_dat[7] |= 0x07;
    rda5807_dat[0] = 0xC0;
    rda5807_write(12);
    delay_10ms(10);
}
/*----------------------------------------------------------------------------*/
/**@brief    设置一个频点RDA5807
   @param    fre 频点  875~1080
   @return   1：当前频点有台，0：当前频点无台
   @note     bool set_fre_rda5807(u16 fre, u8 mode)
*/
/*----------------------------------------------------------------------------*/
bool set_fre_rda5807(u16 fre)
{
    u16 pll;
    u8 i;

    pll = (fre - 870);
    rda5807_dat[2] = pll >> 2;
    rda5807_dat[3] = ((pll & 0x0003)<<6)|0x10;

    rda5807_write(4);
    delay_10ms(10);
    i = 0;
    do
    {
        rda5807_read(4);
        i++;
        delay_10ms(1);
        if (rda5807_true())
        {
            return 1;
        }
    }
    while (i<5);

    return 0;
}

/*----------------------------------------------------------------------------*/
/**@brief    关闭RDA5807的电源
   @param    无
   @return   无
   @note     void rda5807_poweroff(void)
*/
/*----------------------------------------------------------------------------*/
void rda5807_poweroff(void)
{
    rda5807_dat[1] &= ~(1<<0);
    rda5807_write(2);
    delay_10ms(5);
}
/*----------------------------------------------------------------------------*/
/**@brief    获取RDA5807 芯片ID号
   @param    无
   @return   获取成功标志位
   @note     bool rda5807_read_id(void)
*/
/*----------------------------------------------------------------------------*/
bool rda5807_read_id(void)
{
    iic_readn(RDA5807_RD_ADDRESS,0xff,rda5807_dat,10);

    if ((0x58 == rda5807_dat[4]) || (0x58 == rda5807_dat[6]) || (0x58 == rda5807_dat[8]))
    {
        return TRUE;
    }
    return FALSE;
}

/*----------------------------------------------------------------------------*/
/**@brief    RDA5807 Mute函数
   @param    flag：Mute使能位
   @return   无
   @note     void rda5807_mute(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void rda5807_mute(u8 flag)
{
    if (flag)
        rda5807_dat[0] &= ~BIT(6); 	//mute
    else
        rda5807_dat[0] |= BIT(6);

    rda5807_write(2);
}
/*----------------------------------------------------------------------------*/
/**@brief    RDA5807 Mute函数
   @param    flag：Mute使能位
   @return   无
   @note     void rda5807_setch(u8 db)
*/
/*----------------------------------------------------------------------------*/
void rda5807_setch(u8 db)
{
    db=db;
}