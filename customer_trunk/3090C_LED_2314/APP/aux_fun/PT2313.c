/*--------------------------------------------------------------------------
   @file   display_common.c
   @brief    显示模块头文件
   @details
   @author
   @date   2010-04-20
   @note

----------------------------------------------------------------------------*/
#include "iic.h"
#include "config.h"
#include "PT2313.h"



#ifdef SUPPORT_PT2313
u8 _xdata PT_Bass_Val=PT_MAX_VOL/2;
u8  _xdata PT_Treble_Val=PT_MAX_VOL/2;
extern u8 eq_mode;
u8 _code VOL_Table[36] = {63,63,63,63,63,63,50,44,38,34,30,28,26,24,22,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};

u8 _code EQTable1[]=
{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,		//0x07,
     // -14 -12  -10    -8      -6    -4      -2   0
	0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08
    //  0      2      4      6       8     10     12     14		
};

u8 _code PT_EQ_Table[6][2]={	
	{0x6f,0x7f},
	{0x6e,0x7c},
	{0x6f,0x7f},
	{0x6d,0x7b},
	{0x6b,0x7d},
	{0x68,0x78},	
};

void PT2313WriteByte(u8 cDevAddr,u8 cData)
{
    //EA=0;
    /* start condition */
    iic_start();                //I2C启动
    cDevAddr &= 0xFE;   // Force WRITE address
    /* send device ID and write data */
    iic_sendbyte(cDevAddr);   //写地址
    //r_ack();
    iic_sendbyte(cData);      //写数据
    //r_ack();	
    iic_stop();                 //I2C停止时序	
    //EA=1;
    WDT_CLEAR();
    
}

void PT_2313_Treble_config(PT_CTRL_CMD PT_CMD)
{
	if(PT_CMD ==PT_UP){
		if((PT_Treble_Val++)>=PT_TABLE_MAX)PT_Treble_Val =PT_TABLE_MAX;
	}
	else if(PT_CMD ==PT_DW){
		
		if((PT_Treble_Val--)==0)PT_Treble_Val =0;
	}

	
	PT2313WriteByte(PT_2313_ADDR,EQTable1[PT_Treble_Val]|PT_TRABLE_ADDR);

	//write_info(MEM_TREB,PT_Treble_Val);

#ifdef UART_ENABLE_PT2313
	printf(" PT_2313_Treble_config   -->PT_Treble_Val  %d \r\n",(u16)PT_Treble_Val);
#endif
}
void PT_2313_Bass_config(PT_CTRL_CMD PT_CMD)
{
	if(PT_CMD ==PT_UP){
		if((PT_Bass_Val++)>=PT_TABLE_MAX)PT_Bass_Val =PT_TABLE_MAX;
	}
	else if(PT_CMD ==PT_DW){
		
		if((PT_Bass_Val--)==0)PT_Bass_Val =0;
	}

	
	PT2313WriteByte(PT_2313_ADDR,EQTable1[PT_Bass_Val]|PT_BASS_ADDR);

	//write_info(MEM_BASE,PT_Bass_Val);

#ifdef UART_ENABLE_PT2313
	printf(" PT_2313_Bass_config   -->PT_Bass_Val  %d \r\n",(u16)PT_Bass_Val);
#endif
	
}

void PT_2313_EQ_config(void)
{
#if 1
	if(eq_mode==0)
	{
		PT2313WriteByte(PT_2313_ADDR,EQTable1[PT_Bass_Val]|PT_BASS_ADDR);
		PT2313WriteByte(PT_2313_ADDR,EQTable1[PT_Treble_Val]|PT_TRABLE_ADDR);
	}
	else
	{
		PT2313WriteByte(PT_2313_ADDR,PT_EQ_Table[eq_mode][0]);
		PT2313WriteByte(PT_2313_ADDR,PT_EQ_Table[eq_mode][1]);
	} 
#ifdef UART_ENABLE_PT2313
	printf(" PT_2313_EQ_config   -->eq_mode  %x \r\n",(u16)eq_mode);
#endif

#endif
}
void PT_2313_Vol_config(u8 PT_PARA)
{
#if defined(VOLUME_CUSTOMER_DEFINE_63)
	PT2313WriteByte(PT_2313_ADDR, PT_MAIN_VOL_ADDR|(63-PT_PARA));
#else
	PT2313WriteByte(PT_2313_ADDR, PT_MAIN_VOL_ADDR|VOL_Table[PT_PARA]);
#endif
}
void PT_2313_Chan_config(u8 PT_PARA)
{
	u8 reg_temp=0;

#ifdef PT_2313_OUT_GAIN_11DB
	reg_temp = (PT_PATH_ADDR|0x00|PT_PARA);
#else
	reg_temp = (PT_PATH_ADDR|0x18|PT_PARA);
#endif
#if 0
	if(!PT_Londness_Flag){
		
		reg_temp|=(PT_LOUDNESS_ADDR);
	}
#endif
			
	PT2313WriteByte(PT_2313_ADDR, reg_temp);
}
void PT2313_Init(void)
{	
	PT_Bass_Val =7;
	PT_Treble_Val =7;
	PT2313_Config(0xFF,TRELBE_ADJ);
	PT2313_Config(0xFF,BASS_ADJ);
	PT2313_Config(0xFF,EQ_ADJ);
	
#ifdef USE_PT2314
 	PT2313WriteByte(PT_2313_ADDR,PT_REAR_L_ADDR);
	PT2313WriteByte(PT_2313_ADDR,PT_REAR_R_ADDR);
#endif

}
void PT2313_Config(u8 PT_PARA,PT2313_CTRL PT_CMD)
{
	switch(PT_CMD)
		{
		case CHAN_ADJ:
			PT_2313_Chan_config(PT_PARA);
			break;
		case VOL_ADJ:
			PT_2313_Vol_config(PT_PARA);
			break;
		case BASS_ADJ:
			PT_2313_Bass_config(PT_PARA);
			break;
		case TRELBE_ADJ:
			PT_2313_Treble_config(PT_PARA);
			break;	
		case EQ_ADJ:			
			PT_2313_EQ_config();
			break;						
		}
}
#endif

