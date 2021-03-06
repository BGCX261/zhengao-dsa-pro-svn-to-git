/*--------------------------------------------------------------------------*/
/**@file    iic.c
   @brief   IIC 接口函数
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
/** @brief: IIC dat I/O 设置输出函数
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
/** @brief: IIC dat I/O 设置输入函数
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
/** @brief: IIC dat I/O 读取函数
    @param: void
    @return:读取数值
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
/** @brief: IIC dat I/O 输出值设置函数
    @param: flag：输出电平
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
/** @brief: IIC dat I/O 输出值设置函数
    @param: flag：输出电平
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
/** @brief: IIC dat I/O 输出值设置函数
    @param: flag：输出电平
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
/** @brief: IIC 模块初始化函数
    @param: void
    @return:void
    @author:Juntham
    @note:  void iic_init(void)
*/
/*----------------------------------------------------------------------------*/
void iic_init(void) AT(IIC_CODE)
{
    set_iic_io((u16 __code *)iic_io_tab);       ///<配置接口函数IO
}
#ifdef USE_AUTO_SELECT_EEPROM_RTC_MEM
bool eeprom_online =0;
#endif
void eeprom_verify(void) AT(IIC_CODE)
{
#ifdef USE_AUTO_SELECT_EEPROM_RTC_MEM
	 eeprom_online =0;
#endif
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
        //外接eeprom无效
    }
    else
    {
    
#ifdef USE_AUTO_SELECT_EEPROM_RTC_MEM
	 eeprom_online =1;
#endif
        //有外接eeprom
        //my_puts("find eeprom\n");
    }
#endif

}
/*----------------------------------------------------------------------------*/
/** @brief: 记忆信息到存储器（EEPROM）
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

#ifdef USE_EEPROM_MEMORY
    write_eerom(addr, dat);
#endif
#ifdef USE_IRTC_MEMORY
    write_IRTC_RAM(addr, dat);
#endif

#endif

}
/*----------------------------------------------------------------------------*/
/** @brief: 获取记忆信息（EEPROM）
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

#ifdef USE_EEPROM_MEMORY
    return read_eerom(addr);
#endif
#ifdef USE_IRTC_MEMORY
    return read_IRTC_RAM(addr);
#endif

#endif
}


