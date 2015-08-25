/*--------------------------------------------------------------------------*/
/**@file    iic.c
   @brief   IIC �ӿں���
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"
#include "iic.h"
#include "RTC_API.h"
#include "sdmmc_api.h"
#include "play_file.h"
#include "device.h"
#include "IRTC.h"

bool iic_busy;

__code const u16 iic_io_tab[8] AT(TABLE_CODE)=
{
    (u16)iic_data_out,
    (u16)iic_data_in,
    (u16)iic_data_r,
    (u16)iic_data,
    (u16)iic_clk_out,
    (u16)iic_clk,
};


/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O �����������
    @param: void
    @return:void
    @author:Juntham
    @note:  void iic_data_out(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_data_out(void) AT(COMMON_CODE)
{
	SET_IIC_DATA_OUT();
    //P0DIR &= ~(1<<2);
}


/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O �������뺯��
    @param: void
    @return:void
    @author:Juntham
    @note:  void iic_data_in(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_data_in(void) AT(COMMON_CODE)
{
	SET_IIC_DATA_IN();
    //P0DIR |= (1<<2);
    //P0PU |= (1<<2);
}


/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O ��ȡ����
    @param: void
    @return:��ȡ��ֵ
    @author:Juntham
    @note:  bool iic_data_r(void)
*/
/*----------------------------------------------------------------------------*/
_near_func bool iic_data_r(void) AT(COMMON_CODE)
{
	return (IIC_DATA_PIN);
    //return P02;
}

/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O ���ֵ���ú���
    @param: flag�������ƽ
    @return:void
    @author:Juntham
    @note:  void iic_data(bool flag)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_data(bool flag) AT(COMMON_CODE)
{
	IIC_DATA_PIN =flag;
    //P02 = flag;
}

/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O ���ֵ���ú���
    @param: flag�������ƽ
    @return:void
    @author:Juntham
    @note:  void iic_clk_out(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_clk_out(void) AT(COMMON_CODE)
{
	SET_IIC_CLK_OUT();
    	//P0DIR &= ~(1<<3);
}

/*----------------------------------------------------------------------------*/
/** @brief: IIC dat I/O ���ֵ���ú���
    @param: flag�������ƽ
    @return:void
    @author:Juntham
    @note:  void iic_clk(bool flag)
*/
/*----------------------------------------------------------------------------*/
_near_func void iic_clk(bool flag) AT(COMMON_CODE)
{

	IIC_CLK_PIN =flag;
    //P03 = flag;
}



/*----------------------------------------------------------------------------*/
/** @brief: IIC ģ���ʼ������
    @param: void
    @return:void
    @author:Juntham
    @note:  void iic_init(void)
*/
/*----------------------------------------------------------------------------*/
void iic_init(void) AT(IIC_CODE)
{
    set_iic_io((u16 __code *)iic_io_tab);       ///<���ýӿں���IO
}
#ifdef USE_AUTO_SELECT_EEPROM_RTC_MEM
bool eeprom_online =0;
void eeprom_verify(void) AT(IIC_CODE)
{
	 eeprom_online =0;
#ifdef CHECK_EEPROM_ON_POWER_ON
	if ((read_eerom(100) != 0x55)
        ||(read_eerom(101) != 0xAA))
	{
        write_eerom(100, 0x55);
        write_eerom(101, 0xAA);
    }

    if ((read_eerom(100) != 0x55)
        ||(read_eerom(101) != 0xAA))
	{
        //���eeprom��Ч
    }
    else
    {
    
	 eeprom_online =1;
        //�����eeprom
        //my_puts("find eeprom\n");
    }
#endif
}
#endif

/*----------------------------------------------------------------------------*/
/** @brief: ������Ϣ���洢����EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  void set_memory(u8 addr, u8 dat)
*/
/*----------------------------------------------------------------------------*/
_near_func void set_memory(u8 addr, u8 dat) AT(COMMON_CODE)
{
#ifdef USE_AUTO_SELECT_EEPROM_RTC_MEM

	 if(eeprom_online){
		write_eerom(addr, dat);
	 }
	 else{
   	 	write_IRTC_RAM(addr, dat);
	 }
	 
#else

#if 1//def USE_EEPROM_MEMORY
    write_eerom(addr, dat);
#endif
#ifdef USE_IRTC_MEMORY
    write_IRTC_RAM(addr, dat);
#endif

#endif

}
/*----------------------------------------------------------------------------*/
/** @brief: ��ȡ������Ϣ��EEPROM��
    @param: void
    @return:void
    @author:Juntham
    @note:  u8 get_memory(u8 addr)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 get_memory(u8 addr) AT(COMMON_CODE)
{
#ifdef USE_AUTO_SELECT_EEPROM_RTC_MEM

	 if(eeprom_online){
    		return read_eerom(addr);
	 }
	 else{
    		return read_IRTC_RAM(addr);
	 }

#else

#if 1//def USE_EEPROM_MEMORY
    return read_eerom(addr);
#endif
#ifdef USE_IRTC_MEMORY
    return read_IRTC_RAM(addr);
#endif

#endif
}

