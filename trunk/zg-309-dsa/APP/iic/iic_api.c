/*--------------------------------------------------------------------------*/
/**@file     iic_api.c
   @brief    IIC_APIģ��
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/


#include "iic.h"
#include "config.h"
#include "pll_sof.h"

bool iic_busy = 0; ///<iic��æ���

/*----------------------------------------------------------------------------*/
/**@brief   IICд����
   @param   chip_id ��Ŀ��IC��ID��
   @param   iic_addr: Ŀ��IC��Ŀ��Ĵ����ĵ�ַ
   @param   *iic_dat: д��Ŀ��IC�����ݵ�ָ��
   @param   n:��Ҫд�����ݵ���Ŀ
   @return  ��
   @note    void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
*/
/*----------------------------------------------------------------------------*/
void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
{
    iic_busy  = 1;
    iic_start();                //I2C����
    iic_sendbyte(chip_id);         //д����
    if (0xff != iic_addr)
    {
        iic_sendbyte(iic_addr);   //д��ַ
    }
    for (;n>0;n--)
    {
        iic_sendbyte(*iic_dat++);      //д����
    }
    iic_stop();                 //I2Cֹͣʱ��
    iic_busy = 0;
}
/*----------------------------------------------------------------------------*/
/**@brief   IIC������һ��Ŀ��ID��ȡ��������
   @param   address : Ŀ��ID
   @param   *p     :  �浵��ȡ�������ݵ�bufferָ��
   @param   number :  ��Ҫ��ȡ�����ݵĸ���
   @return  ��
   @note    void i2c_read_nbyte(u8 address,u8 *p,u8 number)
*/
/*----------------------------------------------------------------------------*/
void iic_readn(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n)
{

    iic_busy = 1;
    iic_start();                //I2C����
    iic_sendbyte(chip_id);         //д����
    if (0xff != iic_addr)
    {
        iic_sendbyte(iic_addr);   //д��ַ
    }
    for (;n>1;n--)
    {
        *iic_dat++ = iic_revbyte(0);      //д����
    }
    *iic_dat++ = iic_revbyte(1);
    iic_stop();                 //I2Cֹͣʱ��
    iic_busy = 0;
}
/*----------------------------------------------------------------------------*/
/**@brief   EEROM������
   @param   addr ��Ҫд��EEROM�ĵ�ַ
   @param   ��
   @return  ��
   @note    u8 iic_read(u8 iic_addr)
*/
/*----------------------------------------------------------------------------*/
u8 read_eerom(u8 iic_addr)
{
    u8  byte;

    iic_busy = 1;
    iic_start();                    //I2C����
    iic_sendbyte(0xa0);             //д����
    iic_sendbyte(iic_addr);       //д��ַ
    iic_start();                    //дתΪ�������Ҫ�ٴ�����I2C
    iic_sendbyte(0xa1);             //������
    byte = iic_revbyte(1);
    iic_stop();                     //I2Cֹͣ
    iic_busy = 0;
    return  byte;

}


/*----------------------------------------------------------------------------*/
/**@brief   ���к�����ʱ��EEROMд����
   @param   addr ��Ҫд��EEROM�ĵ�ַ
   @param   dat    ����Ҫд������
   @return  ��
   @note    void write_info(u8 addr,u8 dat)
*/
/*----------------------------------------------------------------------------*/
void write_eerom(u8 addr,u8 dat)
{
    iic_write(0xa0,addr,&dat,1);
    delay_10ms(2);
}
/*----------------------------------------------------------------------------*/
/**@brief   EEROM/RTC RAM������
   @param   addr ��Ҫд��EEROM/RTC RAM�ĵ�ַ
   @return  ����������
   @note    u8 read_info(u8 addr)
*/
/*----------------------------------------------------------------------------*/
u8 read_info(u8 addr)
{
#if USE_RTC_RAM
    return read_rtc_ram(addr);
#else

    return read_eerom(addr);
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief   EEROM/RTC RAMд����
   @param   addr ��Ҫ����EEROM/RTC RAM�ĵ�ַ
   @param   dat    ����Ҫ��������
   @return  ��
   @note    void write_info(u8 addr,u8 dat)
*/
/*----------------------------------------------------------------------------*/
void write_info(u8 addr,u8 dat)
{
#if USE_RTC_RAM
    //printf("write RAM addr:%u\n",(u16)addr);
    write_rtc_ram(addr,dat);
#else
    //printf("write EEPROM addr:%u\n",(u16)addr);
    write_eerom(addr,dat);
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief   eeprom START
   @param   ��
   @return  ��
   @note    void  eeprom_page_write_start(void)
*/
/*----------------------------------------------------------------------------*/
void  eeprom_page_write_start(void)
{
    iic_busy  = 1;
    iic_start();                //I2C����
    iic_sendbyte(0xa0);         //д����
}
/*----------------------------------------------------------------------------*/
/**@brief   IIC STOP
   @param   ��
   @return  ��
   @note    void eeprom_page_write_stop(void)
*/
/*----------------------------------------------------------------------------*/
void eeprom_page_write_stop(void)
{
    iic_stop();                     //I2Cֹͣ
    iic_busy = 0;
}

#if((PLL_IN_HPRC == INPUT_OSC_SELECT) && USE_SOF_PLL)

/*----------------------------------------------------------------------------*/
/**@brief   PC����HPRCʱ�ӽ�����д�뺯��
   @param   mem_correct_cnt������д�����׵�ַ
   			mem_correct_cnt+0��mem_correct_cnt+1��
			mem_correct_cnt+2��mem_correct_cnt+3
   @return  ��
   @note    void write_hprc_cnt(u8 mem_correct_cnt, u8 *memery_hprc_counter)
*/
/*----------------------------------------------------------------------------*/
void write_hprc_cnt(u8 mem_correct_cnt, u8 *memery_hprc_counter)
{
	write_info(mem_correct_cnt,  memery_hprc_counter[0]);  		///<MEM_PLLCON0
	write_info(mem_correct_cnt+1,memery_hprc_counter[1]);		///<MEM_PLLCON1
    write_info(mem_correct_cnt+2,memery_hprc_counter[2]);		///<MEM_NULL0
    write_info(mem_correct_cnt+3,memery_hprc_counter[3]);		///<MEM_NULL1
}

/*----------------------------------------------------------------------------*/
/**@brief   ��ȡPC����HPRCʱ�ӽ���������
   @param   mem_correct_cnt����������ȡ�׵�ַ
   			mem_correct_cnt+0��mem_correct_cnt+1��
			mem_correct_cnt+2��mem_correct_cnt+3
   @return  ��
   @note    void read_hprc_cnt(u8 mem_correct_cnt, u8 *memery_hprc_counter)
*/
/*----------------------------------------------------------------------------*/
void read_hprc_cnt(u8 mem_correct_cnt, u8 *memery_hprc_counter)
{
	memery_hprc_counter[0] = read_info(mem_correct_cnt);		///<MEM_PLLCON0
	memery_hprc_counter[1] = read_info(mem_correct_cnt+1);		///<MEM_PLLCON1	
	memery_hprc_counter[2] = read_info(mem_correct_cnt+2);		///<MEM_NULL0
	memery_hprc_counter[3] = read_info(mem_correct_cnt+3);		///<MEM_NULL1
}

/*----------------------------------------------------------------------------*/
/**@brief  Ӧ��PC����ʱ����Ⲣ��ȡHPRC����������
   @param  ��
   @return ��
   @note   void check_hprc_sof(void)
*/
/*----------------------------------------------------------------------------*/
void check_hprc_sof(void)	
{
	u8 xdata tmp0;
	u8 xdata tmp1;

	tmp0 = read_info(MEM_0X55_DAT);
	tmp1 = read_info(MEM_0XAA_DAT);	

	if((0x55 != tmp0) || (0xaa != tmp1))
	{		
		write_info(MEM_0X55_DAT,0X55);
		write_info(MEM_0XAA_DAT,0XAA);
		
        get_pll_sof(0);
	}
    else
	{
        read_hprc_cnt(MEM_PLLCON0, memery_hprc_cnt);
		get_pll_sof(1);
	}
}
#endif
