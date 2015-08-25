/*--------------------------------------------------------------------------*/
/**@file     rda5807.c
   @brief    RDA5807�����ײ�����
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/



#include "rda5807.h"
#include "clock.h"

#define RDA5807_WR_ADDRESS      0x20       ///<RDA5807 д��ַ
#define RDA5807_RD_ADDRESS      0x21       ///<RDA5807 ����ַ

u8 _idata rda5807_dat[12] _at_ 0x80;    ///<5807���ƼĴ���ӳ���
u8 _idata read_dat[4] _at_ (0x80 + 12); /** RDA5807 ״̬�Ĵ���ӳ���  **/

#define rda5807_stc() (read_dat[0] & (1 << 6))       ///<��Ƶ����
#define rda5807_true() (read_dat[2] & (1 << 0))      ///<�Ƿ���̨
#define rda5807_rssi() ((read_dat[2] >> 1))          ///<�����ź�ǿ��
#define rda5807_st()   (read_dat[0] & (1 << 2))
/*----------------------------------------------------------------------------*/
/**@brief    RDA5807д�Ĵ�������
   @param    num ��Ҫ����Ŀ
   @return   ��
   @note     void rda5807_write(u8 num)
*/
/*----------------------------------------------------------------------------*/
void rda5807_write(u8 num)
{
    iic_write(RDA5807_WR_ADDRESS,0xff,rda5807_dat,num);
}
/*----------------------------------------------------------------------------*/
/**@brief    RDA5807���Ĵ�������
   @param    ��Ҫ��ȡ����Ŀ
   @return   ��
   @note     void rda5807_read(u8 num)
*/
/*----------------------------------------------------------------------------*/
void rda5807_read(u8 num)
{
    iic_readn(RDA5807_RD_ADDRESS,0xff,read_dat,num);
}
/*----------------------------------------------------------------------------*/
/**@brief    RDA5807 ��ʼ��
   @param    ��
   @return   ��
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
/**@brief    ����һ��Ƶ��RDA5807
   @param    fre Ƶ��  875~1080
   @return   1����ǰƵ����̨��0����ǰƵ����̨
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
/**@brief    �ر�RDA5807�ĵ�Դ
   @param    ��
   @return   ��
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
/**@brief    ��ȡRDA5807 оƬID��
   @param    ��
   @return   ��ȡ�ɹ���־λ
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
/**@brief    RDA5807 Mute����
   @param    flag��Muteʹ��λ
   @return   ��
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
/**@brief    RDA5807 Mute����
   @param    flag��Muteʹ��λ
   @return   ��
   @note     void rda5807_setch(u8 db)
*/
/*----------------------------------------------------------------------------*/
void rda5807_setch(u8 db)
{
    db=db;
}