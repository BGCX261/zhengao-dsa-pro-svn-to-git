/************************************************************************************/
/*公司名称：			KT Micro
//
//模 块 名：			KT092X驱动模块
//
//创 建 人：								时间：
//修 改 人：Kanghekai						时间：2012-02-07
//功能描述：
//其他说明： Revision History
//  Version	Date		Description
//  V1.0.0	2011-08-29	Initial draft version
//  V1.0.1	2011-09-16	Modified the value of "AMBADFREQ3" in KT_AMFMdrv.h
//  V1.1.0	2011-10-19	Modified the parameter of "AM Tuning Indicator" in KT_AMFMdrv.h
						Added the function of "KT_AM_GetCap".
//  V2.0.0	2011-12-26	Clean Up.
//  V2.1.0	2012-01-17	Modified the parameter of "FM_50K_SPACE".
						Added the function of "KT_AM_GetCap".
//  V2.2.0	2012-02-07	Modified the function of "KT_AM_Tune".
//版    本：V2.2.0																	*/
/************************************************************************************/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "custom_config.h"

#ifdef KT_AMFM
#include "KT_AMFMdrv.h"
#include "iic.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#ifdef FMOLDSEEK
char mem_afc[3];			  //Rememberred afc values for previous, current and next stations
xd_u16 mem_freq[3];			  //Rememberred channel frequencies for previous, current and next stations
#endif
//u8 mem_vol;				  //Rememberred volume before mute

bool kt_band_mode=0;		


/************************************************************************************/
/*函 数 名：KT_Bus_Write												 			*/
/*功能描述：总线写程序																*/
/*函数说明：																		*/
/*调用函数：SPI_Write()、I2C_Word_Write()											*/
/*全局变量：无																		*/
/*输    入：u8 Register_Address, xd_u16 Word_Data									*/
/*返    回：无																		*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
void KT_Bus_Write(u8 Register_Address, u16 Word_Data) AT(FM_CODE)
{
#if 1
	u8 write_reg_data[2]={0};
	write_reg_data[1]=(u8)(Word_Data&0x00FF);
	write_reg_data[0]=(u8)(Word_Data>>8);
    	//EA =0;
	iic_write((KTAMw_address),Register_Address,write_reg_data,2);
    	//EA =1;
#else
	I2C_Start();
	I2C_Senddata(device_address & 0xFE);
	I2C_Ack();
	if (Ack_Flag == 0)
	{
		I2C_Senddata(reg_add);
		I2C_Ack();
		if (Ack_Flag == 0)
		{
			I2C_Senddata(writedata);
			I2C_Ack();
		}
		else
			SCL = 0;			
	}
	else
		SCL = 0;
	I2C_Stop();
#endif	
	
}

/************************************************************************************/
/*函 数 名：KT_Bus_Read															 	*/
/*功能描述：总线读程序																*/
/*函数说明：																		*/
/*调用函数：SPI_Read_3wire()、I2C_Word_Read()										*/
/*全局变量：无																		*/
/*输    入：u8 Register_Address													*/
/*返    回：u8 readdata															*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
u16 KT_Bus_Read(u8 Register_Address) AT(FM_CODE)
{
	u16 readdata;
#if 1
    //EA =0;
    iic_start();                    //I2C启动
    iic_sendbyte((KTAMw_address));             //写命令
    iic_sendbyte(Register_Address);         //写地址
    iic_start();                    //写转为读命令，需要再次启动I2C
    iic_sendbyte((KTAMw_address|0x01));             //读命令
    readdata = iic_revbyte(0);
    readdata=readdata<<8;
    readdata |= iic_revbyte(1);
    iic_stop();                     //I2C停止
    //EA =1;
#else
	iic_start();
	IiC_Senddata(device_address & 0xFE);
	I2C_Ack();
	if (Ack_Flag == 0)	//7.12 edit
	{
		I2C_Senddata(reg_add);
		I2C_Ack();
		if (Ack_Flag == 0)	//7.12 edit
		{
			I2C_Start();
			I2C_Senddata(device_address | 0x01);
			I2C_Ack();
			if (Ack_Flag == 0)
			{
//	SDA pin is high Z
				readdata = I2C_Receivedata();
				I2C_Ack();
			}
			else
			{
				SCL=0;
				return(0x00);
			}
		}
		else
		{
			SCL = 0;
		 	return(0x00);
		}			
	}
	else
	{
		SCL = 0;
		return(0x00);
	}

	I2C_Stop();	
#endif	
	return(readdata);
}

/************************************************************************************/
/*函 数 名：KT_AMFM_PreInit												 			*/
/*功能描述：芯片工作时钟初始化程序													*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：INIT_FAIL_TH															*/
/*输    入：无																		*/
/*返    回：正确：1					错误：0											*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.1																	*/
/************************************************************************************/
u8 KT_AMFM_PreInit(void)	 AT(FM_CODE)		
//This function should be called just after power-up (within 50ms) when crystal is used
//or before reference clock is applied
{
	u16 regx;
#if 0	
	u8 i;
	for (i = 0;i < INIT_FAIL_TH;i++)
	{
		delay_n10ms(1);
		regx = KT_Bus_Read(0x01);           			//Read Manufactory ID
	  	if (regx != 0x4B54) continue;
		break;
	}
    if (i == INIT_FAIL_TH) return(0);
#endif

#ifdef X32P768K
	KT_Bus_Write(0x14, 0x0001);       				//Divider P=1
	KT_Bus_Write(0x15, 0x029C);       				//Divider N=668
	KT_Bus_Write(0x16, 0x8000);
	KT_Bus_Write(0x17, 0x8000);
#endif

#ifdef R32P768K
	KT_Bus_Write(0x14, 0x0001);       				//Divider P=1
	KT_Bus_Write(0x15, 0x029C);       				//Divider N=668
	KT_Bus_Write(0x16, 0x8000);
	KT_Bus_Write(0x17, 0x8000);
	regx = KT_Bus_Read(0x2C);
	KT_Bus_Write(0x2C, regx | 0x1000);				//reference clock
#endif

#ifdef X38K
	KT_Bus_Write(0x14, 0x0001);       				//Divider P=1
	KT_Bus_Write(0x15, 0x0240);       				//Divider N=576
	KT_Bus_Write(0x16, 0x9470);
	KT_Bus_Write(0x17, 0x8000);
#endif

#ifdef R38K
	KT_Bus_Write(0x14, 0x0001);       				//Divider P=1
	KT_Bus_Write(0x15, 0x0240);       				//Divider N=576
	KT_Bus_Write(0x16, 0x9470);
	KT_Bus_Write(0x17, 0x8000);
	regx = KT_Bus_Read(0x2C);
	KT_Bus_Write(0x2C, regx | 0x1000);				//reference clock
#endif

#ifdef R7P6M
	KT_Bus_Write(0x14, 0x00C8);       				//Divider P=200
	KT_Bus_Write(0x15, 0x0240);       				//Divider N=576
	KT_Bus_Write(0x16, 0xF780);
	KT_Bus_Write(0x17, 0x8073);
	regx = KT_Bus_Read(0x2C);
	KT_Bus_Write(0x2C, regx | 0x1000);				//reference clock
#endif

#ifdef R12288KHz
	KT_Bus_Write(0x14, 0x0180);       				//Divider P=384
	KT_Bus_Write(0x15, 0x02AC);       				//Divider N=684
	KT_Bus_Write(0x16, 0x8000);
	KT_Bus_Write(0x17, 0x80BB);
	regx = KT_Bus_Read(0x2C);
	KT_Bus_Write(0x2C, regx | 0x1000);				//reference clock
#endif

#ifdef R12M
	KT_Bus_Write(0x14, 0x0177);       				//Divider P=375
	KT_Bus_Write(0x15, 0x02AC);       				//Divider N=684
	KT_Bus_Write(0x16, 0x1B00);
	KT_Bus_Write(0x17, 0x80B7);
	regx = KT_Bus_Read(0x2C);
	KT_Bus_Write(0x2C, regx | 0x1000);				//reference clock
#endif

#ifdef R13M
	KT_Bus_Write(0x14, 0x019B);       				//Divider P=411
	KT_Bus_Write(0x15, 0x02B4);       				//Divider N=692
	KT_Bus_Write(0x16, 0x5D40);
	KT_Bus_Write(0x17, 0x80C6);
	regx = KT_Bus_Read(0x2C);
	KT_Bus_Write(0x2C, regx | 0x1000);				//reference clock
#endif

#ifdef R24M
	KT_Bus_Write(0x14, 0x02EE);       				//Divider P=750
	KT_Bus_Write(0x15, 0x02A2);       				//Divider N=684
	KT_Bus_Write(0x16, 0x3600);
	KT_Bus_Write(0x17, 0x816E);
	regx = KT_Bus_Read(0x2C);
	KT_Bus_Write(0x2C, regx | 0x1000);				//reference clock
#endif

#ifdef R26M
	KT_Bus_Write(0x14, 0x0336);       				//Divider P=822
	KT_Bus_Write(0x15, 0x02B4);       				//Divider N=692
	KT_Bus_Write(0x16, 0xBA80);
	KT_Bus_Write(0x17, 0x818C);
	regx = KT_Bus_Read(0x2C);
	KT_Bus_Write(0x2C, regx | 0x1000);				//reference clock
#endif

	return(1);
}

/************************************************************************************/
/*函 数 名：KT_AMFM_Init															*/
/*功能描述：芯片初始化程序															*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：INIT_FAIL_TH															*/
/*输    入：无																		*/
/*返    回：正确：1					错误：0											*/
/*设 计 者：Yangpei					时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
u8 KT_AMFM_Init(void) AT(FM_CODE)                            //0->Fail 1->Success
{
	u16 regx;
	u16 i;
	//for (i = 0;i < INIT_FAIL_TH;i++)
	//{
	delay_n10ms(50);
	//regx = KT_Bus_Read(0x65);						//Read power-up indicator
	//if( (regx & 0x8D00) != 0x8D00 ) continue;
	//break;
	//}
	//if(i == INIT_FAIL_TH) return(0);
	//mem_vol =0x1F;
	
	regx=KT_Bus_Read(0x1D);
	KT_Bus_Write(0x1D, regx & 0xFF3F | (AU_GAIN << 6) );	   			

	regx=KT_Bus_Read(0x23);
	KT_Bus_Write(0x23, regx & 0x0FFF | (AM_GAIN << 12) );	   			

	regx=KT_Bus_Read(0x07);
	KT_Bus_Write(0x07, (regx | 0x2000) & 0xEFFF);   			

/*
	regx=KT_Bus_Read(0x09);
	KT_Bus_Write(0x09, regx & 0x7FFF |  (CHFLT_NOTCH << 15));	   					

	regx=KT_Bus_Read(0x5D);
	KT_Bus_Write(0x5D, regx & 0xFE3F | ( BP_180K << 8 ) | ( EN_150K << 7 ) | ( BP_190K << 6 ) );
*/
	regx=KT_Bus_Read(0x0B);
	KT_Bus_Write(0x0B, regx & 0xCFFF | ( IFPGA <<12 ));	   			

	regx=KT_Bus_Read(0x22);
	KT_Bus_Write(0x22, regx & 0xFFF8 | AMIFPGA);	

//afc
	regx=KT_Bus_Read(0x1D);
	KT_Bus_Write(0x1D, regx & 0xD8FF | ( AMAFCD << 13 ) | (AM_TH_AFC << 8) );	   			

	regx=KT_Bus_Read(0x09);
	KT_Bus_Write(0x09, regx & 0xFFF8);	   					

	regx=KT_Bus_Read(0x0C);
	KT_Bus_Write(0x0C, regx & 0xFEFF | ( FMAFCD << 8 ));	

	regx=KT_Bus_Read(0x0E);
	KT_Bus_Write(0x0E, regx & 0xFF87 | ( FM_TH_AFC << 4) | ( FM_AFCRF << 3) );	

	KT_Bus_Write(0x5E, 0x8000);	
// afc end


//blend
	regx=KT_Bus_Read(0x07);
	KT_Bus_Write(0x07, regx & 0xFC17 | ( BLNDADJ << 8 ) | ( DBLND << 5 ) | ( QUICK_BLEND << 3 ) );	
//blend end

//emc
//	regx=KT_Bus_Read(0x5C);
//	KT_Bus_Write(0x5C, regx | 0x8000 );	   			

	regx=KT_Bus_Read(0x5C);
	KT_Bus_Write(0x5C, regx & 0x7FFF);
//				
//*************************Interference Frequency********************************//

#ifdef GOODCHANNEL
	KT_FM_Good_Channel();
	KT_AM_Good_Channel();	
#endif
	
//	KT_Bus_Write(0x23, 0x48F6);	
	KT_Bus_Write(0x23, 0x4016);	
//	KT_Bus_Write(0x24, 0x5080);	
	KT_Bus_Write(0x24, 0x5087);	
	KT_Bus_Write(0x25, 0x0021);	
	KT_Bus_Write(0x26, 0x8405);	
	
	
	KT_AMFM_Softmute_Initial();
	KT_FM_ST_Indicator_Initial();
	KT_FM_Tuning_Indicator_Initial();			//FM Tuning Indicator Initia
	KT_AM_Tuning_Indicator_Initial();			//AM Tuning Indicator Initia

	regx=KT_Bus_Read(0x61);
	KT_Bus_Write(0x61, regx & 0x0FFF | ((0x000F) << 12));
	regx = KT_Bus_Read(0x62);
	KT_Bus_Write(0x62, regx & 0xEFFF | ((0x0001) << 12));
		
	return(1);
}

/************************************************************************************/
/*函 数 名：KT_AMFM_Softmute_Initial											 	*/
/*功能描述：																		*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read(),KT_Bus_Write()											*/
/*全局变量：																		*/
/*输    入：无																		*/
/*返    回：无																		*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
void KT_AMFM_Softmute_Initial(void) AT(FM_CODE)
{
	u16 regx;

#ifdef FMSMUTE
	
	regx=KT_Bus_Read(0x03);
	KT_Bus_Write(0x03, regx & 0x7FFF | 0x0000);

#endif	

#ifdef AMSMUTE
	
	regx=KT_Bus_Read(0x03);
	KT_Bus_Write(0x03, regx & 0xBFFF | 0x0000);

#endif	

//FM	
	regx = KT_Bus_Read(0x03);
	KT_Bus_Write(0x03, (regx & 0xFFFC) | FM_MUTE_TYPE);
	
	KT_Bus_Write(0x04,  (FM_SMUTE_WIN<<14) | (FM_SMUTER<<12) | (SMMD <<11) | (FM_VOLUMET<<8) | (FM_SMUTE_DLY << 4) | FM_SMUTE_GAIN );	
	
	KT_Bus_Write(0x05, (AM_SFTMUTE_OFST<<12) | (FM_SFTMUTE_OFST<<8) | (FM_SFTMUTE_HIGHTH<<4) | FM_SFTMUTE_LOWTH );	

	regx = KT_Bus_Read(0x38);
	KT_Bus_Write(0x38, regx & 0xC7FF | (FM_TUNE_DLY << 12) | (FM_TUNE_SWCH_LATE << 11) );

//AM
	KT_Bus_Write(0x06, (AM_SFTMUTE_HIGHTH<<8) | (SMUTE_RST_DIS<<3) | AM_SFTMUTE_LOWTH);

	regx = KT_Bus_Read(0x37);
	KT_Bus_Write(0x37, regx & 0xC100 | (AM_MUTE_TYPE << 12 ) | (AM_VOLUMET << 9 ) | (AM_SMUTE_GAIN << 4) | (AM_SMUTE_DLY << 0) );

	regx = KT_Bus_Read(0x38);
	KT_Bus_Write(0x38, regx & 0xFBFF | (AM_TUNE_SWCH_LATE << 10 ));

	regx = KT_Bus_Read(0x5F);
	KT_Bus_Write(0x5F, regx & 0xF0FF | (AM_SMUTE_WIN << 10) | (AM_TUNE_DLY << 8) );
}

/************************************************************************************/
/*函 数 名：KT_FM_ST_Indicator_Initial											 	*/
/*功能描述：																		*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Write()															*/
/*全局变量：																		*/
/*输    入：无																		*/
/*返    回：无																		*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
void KT_FM_ST_Indicator_Initial(void) AT(FM_CODE)
{
	KT_Bus_Write(0x55, (FM_ST_DLY<<8) | (FMST_SEN_HIGHTH <<6) | (FMST_SEN_LOWTH <<4) | (FMST_IND_HIGHTH <<2) | FMST_IND_LOWTH);	
}

/************************************************************************************/
/*函 数 名：KT_AM_Tuning_Indicator_Initial										 	*/
/*功能描述：																		*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Write()															*/
/*全局变量：																		*/
/*输    入：无																		*/
/*返    回：无																		*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
void KT_AM_Tuning_Indicator_Initial(void) AT(FM_CODE)
{
	u16 regx;

	KT_Bus_Write(0x59, (AM_TUNE_SNR_HIGHTH) << 8 | AM_TUNE_SNR_LOWTH);	
	KT_Bus_Write(0x5a, (AM_TUNE_AFC_HIGHTH) <<4 | AM_TUNE_AFC_LOWTH);	
	KT_Bus_Write(0x5b, (AM_TUNE_RSSI_HIGHTH <<8) | AM_TUNE_RSSI_LOWTH);	

	regx = KT_Bus_Read(0x5F);
	KT_Bus_Write(0x5F, regx & 0xFF88 | (AM_TUNE_VALID_WIN << 4) | (AM_TUNE_VALID_DLY ) );
}

/************************************************************************************/
/*函 数 名：KT_FM_Tuning_Indicator_Initial										 	*/
/*功能描述：																		*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Write()															*/
/*全局变量：																		*/
/*输    入：无																		*/
/*返    回：无																		*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
void KT_FM_Tuning_Indicator_Initial(void) AT(FM_CODE)
{
	KT_Bus_Write(0x57, (FM_TUNE_VALID_WIN<<12) | (FM_TUNE_VALID_DLY<<8) | (FM_TUNE_SNR_HIGHTH<<4) | FM_TUNE_SNR_LOWTH );	
	KT_Bus_Write(0x58, (FM_TUNE_AFC_HIGHTH<<12) | (FM_TUNE_AFC_LOWTH<<8) | (FM_TUNE_RSSI_HIGHTH<<4) | FM_TUNE_RSSI_LOWTH );	
}

#ifdef GOODCHANNEL
/************************************************************************************/
/*函 数 名：KT_FM_Good_Channel													 	*/
/*功能描述：																		*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Write()															*/
/*全局变量：																		*/
/*输    入：无																		*/
/*返    回：无																		*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
void KT_FM_Good_Channel(void) AT(FM_CODE)
{
	u16 regx;

	KT_Bus_Write(0x41, ( FMDELTAN0 << 12 ) | FMBADFREQ0 );	
	KT_Bus_Write(0x42, ( FMDELTAN1 << 12 ) | FMBADFREQ1 );	
	KT_Bus_Write(0x43, ( FMDELTAN2 << 12 ) | FMBADFREQ2 );	
	KT_Bus_Write(0x44, ( FMDELTAN3 << 12 ) | FMBADFREQ3 );	
	KT_Bus_Write(0x45, ( FMDELTAN4 << 12 ) | FMBADFREQ4 );	
	KT_Bus_Write(0x46, ( FMDELTAN5 << 12 ) | FMBADFREQ5 );	
	KT_Bus_Write(0x47, ( FMDELTAN6 << 12 ) | FMBADFREQ6 );	
	KT_Bus_Write(0x48, ( FMDELTAN7 << 12 ) | FMBADFREQ7 );	

	regx = KT_Bus_Read(0x14);
	KT_Bus_Write(0x14, regx & 0x7FFF |(FMDELTAN <<15 ));	
}

/************************************************************************************/
/*函 数 名：KT_AM_Good_Channel													 	*/
/*功能描述：																		*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Write()															*/
/*全局变量：																		*/
/*输    入：无																		*/
/*返    回：无																		*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
void KT_AM_Good_Channel(void) AT(FM_CODE)
{
	KT_Bus_Write(0x49, AMBADFREQ0);	
	KT_Bus_Write(0x4A, AMBADFREQ1);	
	KT_Bus_Write(0x4B, AMBADFREQ2);	
	KT_Bus_Write(0x4C, AMBADFREQ3);	
	KT_Bus_Write(0x4D, AMBADFREQ4);	
	KT_Bus_Write(0x4E, AMBADFREQ5);	
	KT_Bus_Write(0x4F, AMBADFREQ6);	
	KT_Bus_Write(0x50, AMBADFREQ7);	

	KT_Bus_Write(0x51, (AMDELTAN3 << 12) | ( AMDELTAN2 << 8) | ( AMDELTAN1 << 4) | ( AMDELTAN0));	
	KT_Bus_Write(0x52, (AMDELTAN7 << 12) | ( AMDELTAN6 << 8) | ( AMDELTAN5 << 4) | ( AMDELTAN4));
}
#endif

/************************************************************************************/
/*函 数 名：KT_AMFM_SetMode														 	*/
/*功能描述：工作模式设置程序														*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：FM_MODE、MW_MODE														*/
/*输    入：u8 cAMFM_Mode																		*/
/*返    回：设置完毕：1																*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
u8  KT_AMFM_SetMode(u8 cAMFM_Mode) AT(FM_CODE)
{
	u16 reg60;

	reg60=KT_Bus_Read(0x60);
	if (cAMFM_Mode == FM_MODE)
	{
		KT_Bus_Write(0x60,	reg60 & 0xBFFF);			//AM_FM=0
	}
	else
	{
		KT_Bus_Write(0x60,	reg60 | 0x4000);			//AM_FM=1
	}

	return(1);
}

/************************************************************************************/
/*函 数 名：KT_AM_SetBW														 	*/
/*功能描述：AM Channel Bandwidth设置程序											*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：																	*/
/*输    入：u8 cFlt_Sel																*/
/*返    回：设置完毕：1																*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
#if 0
u8 KT_AM_SetBW(u8 cFlt_Sel)
{
	u16 regx;

	cFlt_Sel = cFlt_Sel - 1;
	regx = KT_Bus_Read(0x23);
	KT_Bus_Write(0x23, ( regx & 0xF8FF ) | ( (xd_u16)cFlt_Sel << 8 ) );

	return(1);
}
#endif
/************************************************************************************/
/*函 数 名：KT_AMFM_SetLineIn													 	*/
/*功能描述：AM Line In设置程序														*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：																		*/
/*输    入：u8 LineNum															*/
/*返    回：设置完毕：1																*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
#if 0

u8 KT_AMFM_SetLineIn(u8 cLineNum)				//AM Channel Bandwidth=2 for 2KHz; 4 for 4KHz; 6 for 6KHz
{
	u16 regx;

	regx = KT_Bus_Read(0x1D);
	KT_Bus_Write(0x1D, (regx & 0xFFFC) | cLineNum);

	return(1);
}
#endif

/************************************************************************************/
/*函 数 名：KT_AMFM_Standby														 	*/
/*功能描述：Standby程序																*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：无																		*/
/*输    入：u8 AMBW																*/
/*返    回：设置完毕：1																*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
void KT_AMFM_Standby(void) AT(FM_CODE)					//0->Fail 1->Success
{
	u16 regx;

	regx = KT_Bus_Read(0x1A);
	KT_Bus_Write(0x1A, regx | 0x1000);		//Write Standby bool to 1
	delay_n10ms(2);
}

/************************************************************************************/
/*函 数 名：KT_AMFM_WakeUp														 	*/
/*功能描述：唤醒程序																*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()、KT_AMFM_Init()							*/
/*全局变量：无																		*/
/*输    入：u8 AMBW																*/
/*返    回：KT_AMFM_Init()															*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
void KT_AMFM_WakeUp(void)  AT(FM_CODE)//0->Fail 1->Success
{
	u16 regx;

	regx = KT_Bus_Read(0x1A);
	KT_Bus_Write(0x1A, (regx&0xEFFF));			//Write Standby bool to 0
	(KT_AMFM_Init());
}

/************************************************************************************/
/*函 数 名：KT_AMFM_VolumeSet													 	*/
/*功能描述：音量设置程序															*/
/*函数说明：vol=0~31																*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：mem_vol																	*/
/*输    入：u8 vol																*/
/*返    回：设置完毕：1																*/
/*设 计 者：Yangpei					时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
#if 0
u8 KT_AMFM_VolumeSet(u8 cVol)			//Input: 0~31
{
	u16 regx;
	u16 mem_vol_lsb;
	u16 mem_vol_msb;

	mem_vol = cVol;
	mem_vol_lsb = mem_vol & 0x000F;
	mem_vol_msb = (mem_vol >> 4) & 0x0001;
	regx = KT_Bus_Read(0x61);
	KT_Bus_Write(0x61, regx & 0x0FFF | (mem_vol_lsb << 12));
	regx = KT_Bus_Read(0x62);
	KT_Bus_Write(0x62, regx & 0xEFFF | (mem_vol_msb << 12));

	return(1);
}
#endif
/************************************************************************************/
/*函 数 名：KT_AMFM_Mute														 	*/
/*功能描述：静音程序																*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：无																		*/
/*输    入：无																		*/
/*返    回：设置完毕：1																*/
/*设 计 者：Yangpei					时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
#if 0
u8 KT_AMFM_Mute(void)
{
	u16 regx;

	regx = KT_Bus_Read(0x61);
	KT_Bus_Write(0x61, regx & 0x0FFF);		//Write volume to 0
	
	regx = KT_Bus_Read(0x62);
	KT_Bus_Write(0x62, regx & 0xEFFF);		//Write volume to 0

	return(1);
}
/************************************************************************************/
/*函 数 名：KT_AMFM_UnMute														 	*/
/*功能描述：AMFM默认音频增益程序													*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：mem_vol																	*/
/*输    入：无																		*/
/*返    回：设置完毕：1																*/
/*设 计 者：Yangpei					时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
u8 KT_AMFM_UnMute(void)
{
	u16 regx;
	u16 mem_vol_lsb;
	u16 mem_vol_msb;

	mem_vol_lsb = mem_vol & 0x000F;
	mem_vol_msb = (mem_vol >> 4) & 0x0001;
	regx=KT_Bus_Read(0x61);
	KT_Bus_Write(0x61, regx & 0x0FFF | (mem_vol_lsb << 12));
	regx = KT_Bus_Read(0x62);
	KT_Bus_Write(0x62, regx & 0xEFFF | (mem_vol_msb << 12));

	return(1);
}
#endif
/************************************************************************************/
/*函 数 名：KT_FM_Tune															 	*/
/*功能描述：FM Tune台程序															*/
/*函数说明：在Tune台的过程中静音													*/
/*调用函数：KT_AMFM_Mute()、KT_Bus_Read()、KT_Bus_Write()、delay_n10ms()				*/
/*全局变量：无																		*/
/*输    入：xd_u16 Frequency															*/
/*返    回：设置完毕：1																*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V2.1																	*/
/************************************************************************************/
/*
u8 KT_FM_Tune(xd_u16 iFrequency) //87.5MHz-->Frequency=8750; Mute the chip and Tune to Frequency
{
	xd_u16 reg60;
	char afc;
	char snr;

	KT_AMFM_Mute();

	reg60=KT_Bus_Read(0x60);
	KT_Bus_Write(0x60, (reg60 & 0xB000) | 0x8000 | (iFrequency /  5));	   		//set tune bool to 1
	delay_n10ms(50);

	afc = KT_FM_GetAFC();
	CODE_Send(0x9D);
	DATA_Send(HexToASCII(afc >> 4));
	DATA_Send(HexToASCII(afc));

	snr = KT_FM_GetSNR();
	CODE_Send(0x9E);
	DATA_Send(HexToASCII(snr >> 4));
	DATA_Send(HexToASCII(snr));

	return(1);
}
*/
u8 KT_FM_Tune(u16 iFrequency)  AT(FM_CODE)//87.5MHz-->Frequency=8750; Mute the chip and Tune to Frequency
{
	u16 reg60;
	char afc;
	char snr;

	//KT_AMFM_Mute();
/*
#ifdef C32P768K
	if((iFrequency == 8050) || (iFrequency == 8080) || (iFrequency == 8220) || (iFrequency == 8040) || (iFrequency == 8360))
		KT_Bus_Write(0x15, 0x0294);
	else if((iFrequency == 8070) || (iFrequency == 8880))
		KT_Bus_Write(0x15, 0x0295);
	else if((iFrequency == 8200) || (iFrequency == 8210) || (iFrequency == 8340) || (iFrequency == 8470))
		KT_Bus_Write(0x15, 0x0296);
	else if((iFrequency == 7670) || (iFrequency == 8350))
		KT_Bus_Write(0x15, 0x0297);
	else if((iFrequency == 7650) || (iFrequency == 9030) || (iFrequency == 9035) || (iFrequency == 9170) ||
			(iFrequency == 9435) || (iFrequency == 9575) || (iFrequency == 9580) || (iFrequency == 9840) ||
			(iFrequency == 9845) || (iFrequency == 9850) || (iFrequency == 9855) || (iFrequency == 10260) ||
			(iFrequency == 10395) || (iFrequency == 10535) || (iFrequency == 10670))
		KT_Bus_Write(0x15, 0x0298);
	else if((iFrequency == 7660) || (iFrequency == 7790) || (iFrequency == 8060) || (iFrequency == 8770) ||
			(iFrequency == 9565) || (iFrequency == 9860) || (iFrequency == 10400))
		KT_Bus_Write(0x15, 0x0299);
	else if((iFrequency == 7800) || (iFrequency == 7890) || (iFrequency == 7930) || (iFrequency == 7935) ||
			(iFrequency == 8480) || (iFrequency == 9020) || (iFrequency == 9025) || (iFrequency == 9295) ||
			(iFrequency == 9300) || (iFrequency == 9305) || (iFrequency == 9470) || (iFrequency == 10120) ||
			(iFrequency == 10125) || (iFrequency == 10200) || (iFrequency == 10205))
		KT_Bus_Write(0x15, 0x029A);
	else if((iFrequency == 7680) || (iFrequency == 7810) || (iFrequency == 8490) || (iFrequency == 8900))
		KT_Bus_Write(0x15, 0x029B);
	else if((iFrequency == 8610) || (iFrequency == 9620) || (iFrequency == 9985))
		KT_Bus_Write(0x15, 0x029D);
	else if((iFrequency == 8345) || (iFrequency == 8620) || (iFrequency == 8890) || (iFrequency == 8895) ||
			(iFrequency == 9165) || (iFrequency == 9440) || (iFrequency == 9990))
		KT_Bus_Write(0x15, 0x029E);
	else if((iFrequency == 8750) || (iFrequency == 10190) || (iFrequency == 10195))
		KT_Bus_Write(0x15, 0x029F);
	else if((iFrequency == 8690) || (iFrequency == 9570) || (iFrequency == 10210))
		KT_Bus_Write(0x15, 0x02A0);
	else if((iFrequency == 8710) || (iFrequency == 8740))
		KT_Bus_Write(0x15, 0x02A1);
	else if((iFrequency == 7940) || (iFrequency == 8630) || (iFrequency == 8720) || (iFrequency == 8030))
		KT_Bus_Write(0x15, 0x02A2);
	else if((iFrequency == 8730) || (iFrequency == 8760) || (iFrequency == 8780) || (iFrequency == 8790))
		KT_Bus_Write(0x15, 0x02A3);
	else if((iFrequency == 8700))
		KT_Bus_Write(0x15, 0x02A4);
	else
		KT_Bus_Write(0x15, 0x029C);                                     //Divider N=668
#endif

*/
#ifdef C32P768K
	if(		(iFrequency == 7650)	||	(iFrequency == 8040)	||	(iFrequency == 8360)	||	(iFrequency == 9030)	||
			(iFrequency == 9035)	||	(iFrequency == 8780)	||	(iFrequency == 9170)	||	(iFrequency == 9435)	||
			(iFrequency == 9575)	||	(iFrequency == 9580)	||	(iFrequency == 9840)	||	(iFrequency == 9845)	||
			(iFrequency == 9850)	||	(iFrequency == 9855)	||	(iFrequency == 10260)	||	(iFrequency == 10395)	||
			(iFrequency == 10535)	||	(iFrequency == 10670))
		KT_Bus_Write(0x15, 0x0298);

	else if((iFrequency == 7660)	||	(iFrequency == 7790)	||	(iFrequency == 8060)	||	(iFrequency == 8470)	||
			(iFrequency == 8760)	||	(iFrequency == 8770)	||	(iFrequency == 8790)	||	(iFrequency == 8880)	||
			(iFrequency == 9565)	||	(iFrequency == 9860)	||	(iFrequency == 10400))
		KT_Bus_Write(0x15, 0x0299);

	else if((iFrequency == 7800)	||	(iFrequency == 7890)	||	(iFrequency == 7930)	||	(iFrequency == 7935)	||	
			(iFrequency == 7940)	||	(iFrequency == 8070)	||	(iFrequency == 8080)	||	(iFrequency == 8210)	||
			(iFrequency == 8340)	||	(iFrequency == 8480)	||	(iFrequency == 9020)	||	(iFrequency == 9025)	||
			(iFrequency == 9295)	||	(iFrequency == 9300)	||	(iFrequency == 9305)	||	(iFrequency == 9470)	||
			(iFrequency == 10120)	||	(iFrequency == 10125)	||	(iFrequency == 10200)	||	(iFrequency == 10205))
		KT_Bus_Write(0x15, 0x029A);

	else if((iFrequency == 7670)	||	(iFrequency == 7680)	||	(iFrequency == 7810)	||	(iFrequency == 8220)	||	
			(iFrequency == 8350)	||	(iFrequency == 8490)	||	(iFrequency == 8900))
		KT_Bus_Write(0x15, 0x029B);

	else if((iFrequency == 8200)	||	(iFrequency == 8610)	||	(iFrequency == 9620)	||	(iFrequency == 9985))
		KT_Bus_Write(0x15, 0x029D);

	else if((iFrequency == 8030)	||	(iFrequency == 8345)	||	(iFrequency == 8620)	||	(iFrequency == 8720)	||	(iFrequency == 8890)	||	
			(iFrequency == 8895)	||	(iFrequency == 9165)	||	(iFrequency == 9440)	||	(iFrequency == 9990))
		KT_Bus_Write(0x15, 0x029E);

	else if((iFrequency == 8730)	||	(iFrequency == 8750)	||	(iFrequency == 10190)	||	(iFrequency == 10195))
		KT_Bus_Write(0x15, 0x029F);

	else if((iFrequency == 8630)	||	(iFrequency == 8690)	||	(iFrequency == 8700)	||	(iFrequency == 9570)	||	
			(iFrequency == 10210))
		KT_Bus_Write(0x15, 0x02A0);

	else
		KT_Bus_Write(0x15, 0x029C);                                     //Divider N=668
#endif

	reg60=KT_Bus_Read(0x60);
	KT_Bus_Write(0x60, (reg60 & 0xB000) | 0x8000 | (iFrequency /  5));                       //set tune bool to 1
	delay_n10ms(5);

	afc = KT_FM_GetAFC();
	//CODE_Send(0x9D);
	//DATA_Send(HexToASCII(afc >> 4));
	//DATA_Send(HexToASCII(afc));

	snr = KT_FM_GetSNR();
	//CODE_Send(0x9E);
	//DATA_Send(HexToASCII(snr >> 4));
	//DATA_Send(HexToASCII(snr));

	return(1);
}

/************************************************************************************/
/*函 数 名：KT_AM_Tune															 	*/
/*功能描述：AM Tune台程序															*/
/*函数说明：在Tune台的过程中静音													*/
/*调用函数：KT_AMFM_Mute()、KT_Bus_Read()、KT_Bus_Write()							*/
/*全局变量：无																		*/
/*输    入：xd_u16 iFrequency															*/
/*返    回：设置完毕：1																*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2012-02-07								*/
/*版    本：V2.2																	*/
/************************************************************************************/
u8 KT_AM_Tune(u16 iFrequency)  AT(FM_CODE)//1710KHz --> Frequency=1710; Mute the chip and Tune to Frequency
{
//	char afc;
//	char snr;
	u16 reg1E;

	//KT_AMFM_Mute();

#ifdef C32P768K
	KT_Bus_Write(0x15, 0x029C);       				//Divider N=668	reg1E	=	KT_Bus_Read(0x1E);
	KT_Bus_Write(0x1E, reg1E  & 0x7FFF);
	KT_Bus_Write(0x63, 0x8000 | iFrequency);	   			//set tune bool to 1
	delay_n10ms(2);
	reg1E	=	KT_Bus_Read(0x1E);
	KT_Bus_Write(0x1E, reg1E  | 0x8000);

	if((iFrequency == 1377))
		KT_Bus_Write(0x15, 0x0274);
	else if((iFrequency == 1368))
		KT_Bus_Write(0x15, 0x0276);
	else if((iFrequency == 720)		||	(iFrequency == 990))
		KT_Bus_Write(0x15, 0x027D);
	else if((iFrequency == 684)		||	(iFrequency == 1134)	||	(iFrequency == 1404))
		KT_Bus_Write(0x15, 0x0280);
	else if((iFrequency == 801)		||	(iFrequency == 918)		||	(iFrequency == 1359)	||	(iFrequency == 1557))
		KT_Bus_Write(0x15, 0x0282);
	else if((iFrequency == 675)		||	(iFrequency == 1035))
		KT_Bus_Write(0x15, 0x0284);
	else if((iFrequency == 1260))
		KT_Bus_Write(0x15, 0x0288);
	else if((iFrequency == 1296))
		KT_Bus_Write(0x15, 0x028B);
	else if((iFrequency == 1179))
		KT_Bus_Write(0x15, 0x0290);
	else if((iFrequency == 648))
		KT_Bus_Write(0x15, 0x0291);
	else if((iFrequency == 837)		||	(iFrequency == 1341))
		KT_Bus_Write(0x15, 0x0296);
	else if((iFrequency == 1593))
		KT_Bus_Write(0x15, 0x02A6);
	else if((iFrequency == 531)		||	(iFrequency == 567)		||	(iFrequency == 873)		||	(iFrequency == 909)		||
			(iFrequency == 1026)	||	(iFrequency == 1062)	||	(iFrequency == 1143)	||	(iFrequency == 1251)	||
			(iFrequency == 1332)	||	(iFrequency == 1485)	||	(iFrequency == 1521))
		KT_Bus_Write(0x15, 0x02AA);
	else if((iFrequency == 1449)	||	(iFrequency == 1476)	||	(iFrequency == 1602))
		KT_Bus_Write(0x15, 0x02AE);
	else
		KT_Bus_Write(0x15, 0x029C);       				//Divider N=668
#endif
	
	KT_Bus_Write(0x63, 0x8000 | iFrequency);	   			//set tune bool to 1
	delay_n10ms(12);

/*	afc = KT_AM_GetAFC();
	CODE_Send(0x9D);
	DATA_Send(HexToASCII(afc>>4));
	DATA_Send(HexToASCII(afc));

	snr = KT_AM_GetSNR();
	CODE_Send(0x9E);
	DATA_Send(HexToASCII(snr>>4));
	DATA_Send(HexToASCII(snr));
*/
	return(1);
}
#if 0
/************************************************************************************/
/*函 数 名：KT_AMFM_SetBass														 	*/
/*功能描述：																		*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()、KT_Bus_Write()											*/
/*全局变量：无																		*/
/*输    入：无																		*/
/*返    回：xd_u16 cBass																*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
bool KT_AMFM_SetBass(u8 cBass)
{
	u16 regx;

	regx= KT_Bus_Read(0x03);
	KT_Bus_Write(0x03, (regx & 0xFCFF) | ((xd_u16)cBass << 8) );	   			//set tune bool to 1

	return(1);
}

/************************************************************************************/
/*函 数 名：KT_FM_GetFreq														 	*/
/*功能描述：FM读当前电台频率程														*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()															*/
/*全局变量：无																		*/
/*输    入：无																		*/
/*返    回：																		*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-12-26								*/
/*版    本：V1.1																	*/
/************************************************************************************/
u16 KT_FM_GetFreq(void)
{
//	xd_u16 regx;

//	regx= KT_Bus_Read(0x66);

//	return( (regx & 0x7FFF) * 5 );
	return( KT_AM_GetFreq() * 5 );
}

/************************************************************************************/
/*函 数 名：KT_AM_GetFreq														 	*/
/*功能描述：AM读当前电台频率程														*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()															*/
/*全局变量：无																		*/
/*输    入：无																		*/
/*返    回：																		*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
u16 KT_AM_GetFreq(void)
{
	u16 regx;

	regx= KT_Bus_Read(0x66);

	return( (regx & 0x7FFF) );
}

/************************************************************************************/
/*函 数 名：KT_FM_GetST															 	*/
/*功能描述：FM 判断单声道OR立体声程序												*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()															*/
/*全局变量：TST_TH																	*/
/*输    入：无																		*/
/*返    回：立体声：1				单声道：0										*/
/*设 计 者：Yangpei					时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/

u8 KT_FM_GetST(void)
{
	u16 regx;

	regx = KT_Bus_Read(0x65);
	regx = regx & 0x0200;
		
	if( regx == 0x0200 )
		return(1);
	else
		return(0);
}
/************************************************************************************/
/*函 数 名：KT_FM_ReadRSSI														 	*/
/*功能描述：读FM RSSI程序															*/
/*函数说明：RSSI=-100(dbm) to -6(dbm)												*/
/*调用函数：KT_Bus_Read()															*/
/*全局变量：无																		*/
/*输    入：char *RSSI																*/
/*返    回：设置完毕：1																*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
u8 KT_FM_ReadRSSI(char *RSSI) //range from -100 to -6, unit is dbm
{
	u16 regx;

	regx = KT_Bus_Read(0x6A);
	*RSSI = -(110 - (regx >> 8));

	return(1);
}
#endif
/************************************************************************************/
/*函 数 名：KT_AM_ReadRSSI														 	*/
/*功能描述：读AM RSSI程序															*/
/*函数说明：RSSI=-90(dbm) to -6(dbm)												*/
/*调用函数：KT_Bus_Read()															*/
/*全局变量：无																		*/
/*输    入：无																		*/
/*返    回：设置完毕：1																*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
u8 KT_AM_ReadRSSI(char *RSSI)  AT(FM_CODE)//range from -90 to -6, unit is dbm
{
	u16 regx;

	regx = KT_Bus_Read(0x6C);
	*RSSI = -(110 - (regx >> 8));

	return(1);
}

/************************************************************************************/
/*函 数 名：KT_FM_GetSNR														 	*/
/*功能描述：FM 读SNR程序															*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()															*/
/*全局变量：无																		*/
/*输    入：无																		*/
/*返    回：xd_u16 SNR																*/
/*设 计 者：Yanpei				时间：												*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
u8 KT_FM_GetSNR(void) AT(FM_CODE)
{
	xd_u16 regx;

	regx = KT_Bus_Read(0x6A);
	regx = regx & 0x00FF;
	regx = regx >> 2;

	return(regx);
}

/************************************************************************************/
/*函 数 名：KT_AM_GetSNR														 	*/
/*功能描述：AM 读SNR程序															*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()															*/
/*全局变量：无																		*/
/*输    入：无																		*/
/*返    回：xd_u16 SNR																*/
/*设 计 者：Yanpei				时间：												*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
u8 KT_AM_GetSNR(void) AT(FM_CODE)
{
	u16 regx;

	regx = KT_Bus_Read( 0x6D );
	regx = regx & 0x03FF;
	regx = regx >> 3;								//

	return(regx);
}

/************************************************************************************/
/*函 数 名：KT_AMFM_SeekFromCurrentCh											 	*/
/*功能描述：AMFM从指定频率搜台程序													*/
/*函数说明：																		*/
/*调用函数：																		*/
/*全局变量：FM_MODE、SEEKUP、Current_Band.Seek_Down_Limit、							*/
/*			Current_Band.Seek_Up_Limit、Current_Band.Seek_Step、					*/
/*			mem_afc、mem_freq														*/
/*输    入：bool bSeekDir, xd_u16 *iFrequency											*/
/*返    回：正确：1					错误：0											*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
#if 0
u8 KT_AMFM_SeekFromCurrentCh(bool bSeekDir, u16 *iFrequency)   //     bSeekDir: 0-->seek down 1-->seek up
{
	u16 NextFreq;
	u8 (*pValidStation)(u16);

#ifdef FMOLDSEEK
	mem_afc[0]=0;mem_afc[1]=0;mem_afc[2]=0;
	mem_freq[0]=0;mem_freq[1]=0;mem_freq[2]=0;
#endif
			
	if(Current_Band.Band == FM_MODE)
		*pValidStation = KT_FM_ValidStation;
	else
		*pValidStation = KT_AM_ValidStation;

	if (bSeekDir == SEEKUP)
	{
		if ((*iFrequency) > Current_Band.Seek_Up_Limit - Current_Band.Seek_Step)		//if current channel reaches 108MHz, then start seeking from 87.5MHz
			NextFreq = Current_Band.Seek_Down_Limit;
		else									//else start from 100KHz after current channel
			NextFreq = (*iFrequency) + Current_Band.Seek_Step;
		while (1)
		{

			if ((*pValidStation)(NextFreq))	//if nextfreq is a true channel, then stop seeking and return seek success
			{
				*iFrequency = NextFreq;
				return(1);
			}
			else
			{
				if (NextFreq > Current_Band.Seek_Up_Limit - Current_Band.Seek_Step)	//if current channel reach 108MHz, then stop seeking and return seek fail
				{
					*iFrequency = NextFreq;
					return(0);
				}
				NextFreq = NextFreq + Current_Band.Seek_Step;	//Try next channel
			}
		}
	}
	else
	{
		if ((*iFrequency) < Current_Band.Seek_Down_Limit + Current_Band.Seek_Step)		//if current channel reaches 87.5MHz, then start seeking from 108MHz
			NextFreq = Current_Band.Seek_Up_Limit;
		else									//else start from 100KHz before current channel
			NextFreq = (*iFrequency) - Current_Band.Seek_Step;
		while (1)
		{
			if ((*pValidStation)(NextFreq))	//if nextfreq is a true channel, then stop seeking and return seek success
			{
				*iFrequency = NextFreq;
				return(1);
			}
			else
			{
				if (NextFreq < Current_Band.Seek_Down_Limit + Current_Band.Seek_Step)	//if current channel reach 87.5MHz, then stop seeking and return seek fail
				{
					*iFrequency = NextFreq;
					return(0);
				}
				NextFreq = NextFreq - Current_Band.Seek_Step;	//Try next channel
			}
		}
	}
}
#endif

/************************************************************************************/
/*函 数 名：KT_FM_ValidStation														*/
/*功能描述：FM 有效态判断程序														*/
/*函数说明：																		*/
/*调用函数：Display_Channel()、KT_FM_Tune()、KT_FM_GetSNR()、KT_FM_GetAFC()			*/
/*全局变量：Current_Band.ValidStation_Step											*/
/*输    入：xd_u16 iFrequency															*/
/*返    回：正确：1					错误：0											*/
/*设 计 者：Yanpei					时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
bool KT_FM_ValidStation(u16 iFrequency) AT(FM_CODE) //0-->False Station 1-->Good Station //check AFC_DELTA only
{
#ifdef FMOLDSEEK

	u16 nextfreq;
	u16 snr;
	char afc[3];							//AFC value for previous, current and next channels
	u16 freq[3];							//frequency values for previous, current and next channels
	char i,j;
    //Display_Channel(iFrequency);	 			//display current channel frequency
	snr = KT_FM_GetSNR();
	afc[0]=0;afc[1]=0;afc[2]=0;				//initialize
	freq[0]=0;freq[1]=0;freq[2]=0;			//initialize
	nextfreq = iFrequency-Current_Band.ValidStation_Step;		
	//Get AFC values of previous, current and next channels
	for (i=0;i<3;i++)
	{
		//get AFC values for the last station's information
		for (j=0;j<3;j++)
			if (mem_freq[j]==nextfreq)
			{
				afc[i]=mem_afc[j];
				freq[i]=mem_freq[j];
			}
		//get new AFC value if the station information is not investigated in the last run
		if (!freq[i])
		{
		    KT_FM_Tune(nextfreq);
			afc[i]=KT_FM_GetAFC();
			freq[i]=nextfreq;
		}
		nextfreq = nextfreq + Current_Band.ValidStation_Step;
	}
	//Record AFC values
	mem_afc[0]=afc[0];mem_afc[1]=afc[1];mem_afc[2]=afc[2];
	mem_freq[0]=freq[0];mem_freq[1]=freq[1];mem_freq[2]=freq[2];

	//Determine the validation of current station
	if ((afc[0]<afc[1]) && (afc[1]<afc[2]) && (afc[0]<-FM_AFCTH_PREV) && (afc[1]>-FM_AFCTH) && (afc[1]<FM_AFCTH) && (afc[2]>FM_AFCTH_NEXT))
	{
		if (snr>=FM_SNR_TH)
		{
			return(1);
		}
		else
		{
			return(0);
		}

	}
	else
	{
		return(0);
	}
#endif

#ifdef FMNEWSEEK

	char afc;
	u8 snr;
	char xdata rssi;
    Display_Channel(iFrequency);	 			//display current channel frequency

	KT_FM_Tune(iFrequency);

	KT_FM_ReadRSSI(& rssi);
	afc=KT_FM_GetAFC();
	snr=KT_FM_GetSNR();

	if (rssi > FM_RSSI_TH)
	{	
		if ((afc>-FM_AFCTH) && (afc<FM_AFCTH) &&(snr>=FM_SNR_TH) )
			return(1);
		else
			return(0);
	}
	else
		return(0);

#endif

#ifdef FM_SEEK_MODE2
	char afc_prev,afc_next;

    //Display_Channel(iFrequency);	 			//display current channel frequency

	KT_FM_Tune(iFrequency);
	delay_n10ms(1);
	if( KT_AMFM_Tuning_Indicator() )
	{
		KT_FM_Tune(iFrequency - Current_Band.ValidStation_Step);
		afc_prev = KT_FM_GetAFC();
		if ( afc_prev < -Current_Band.AFCTH_Prev)
		{
			KT_FM_Tune(iFrequency + Current_Band.ValidStation_Step);
			afc_next = KT_FM_GetAFC();
			if ( afc_next > Current_Band.AFCTH_Next)
				return(1);
			else
				return(0);
		}
		else
			return(0);
	}
	else
		return(0);
#endif


#ifdef FM_SEEK_MODE3

#if 1
		u16 FrequencyTemp=0;
		signed char  afc[3];			 
		u8 snr[3];
		FrequencyTemp=iFrequency;
	       KT_FM_Tune(FrequencyTemp);
		afc[1]=KT_FM_GetAFC();
		if((afc[1]>-FM_AFCTH)&&(afc[1]<FM_AFCTH))
		{

			snr[1]=KT_FM_GetSNR();
			if(snr[1]>=FM_SNR_TH)
				{

				FrequencyTemp=iFrequency-Current_Band.ValidStation_Step;
				KT_FM_Tune(FrequencyTemp);
				afc[0]=KT_FM_GetAFC();
				
				if (afc[1]>afc[0])
					{
					FrequencyTemp=iFrequency+Current_Band.ValidStation_Step;
					KT_FM_Tune(FrequencyTemp);
					afc[2]=KT_FM_GetAFC();

					KT_FM_Tune(iFrequency);

					if (afc[1]<afc[2])
						return(1);
					}
				}
				
		}	

	KT_FM_Tune(iFrequency);
		
	return(0);
#else
	signed char afc_prev,afc_next;
	u8 snr;

    //Display_Channel(iFrequency);	 			//display current channel frequency

	KT_FM_Tune(iFrequency);
	snr=KT_FM_GetSNR();
	delay_n10ms(2);
	if( KT_AMFM_Tuning_Indicator() && (snr > FM_SNR_TH) )
	{
		KT_FM_Tune(iFrequency - Current_Band.ValidStation_Step);
		afc_prev = KT_FM_GetAFC();

		if( afc_prev < -Current_Band.AFCTH_Prev )
		{
			KT_FM_Tune(iFrequency + Current_Band.ValidStation_Step);
			afc_next = KT_FM_GetAFC();

			if( afc_next > Current_Band.AFCTH_Next )
				return(1);
			else
				return(0);
		}
		else
			return(0);
	}
	else
		return(0);

#endif
#endif

}

/************************************************************************************/
/*函 数 名：KT_AM_ValidStation														*/
/*功能描述：AM 有效态判断程序														*/
/*函数说明：																		*/
/*调用函数：Display_Channel_AM()、KT_AM_GetAFC() 									*/
/*全局变量：Current_Band.ValidStation_Step、Current_Band.AFCTH_Prev					*/
/*输    入：xd_u16 iFrequency															*/
/*返    回：正确：1					错误：0											*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
bool KT_AM_ValidStation(u16 iFrequency)  AT(FM_CODE)//0-->False Station 1-->Good Station //check AFC_DELTA only
{
#ifdef AMOLDSEEK
	char AM_afc[3];							//AFC value for previous, current and next channels
	u16 snr;
	char rssi;

	AM_afc[0] = 0;AM_afc[1] = 0;AM_afc[2] = 0;	//initialize

    Display_Channel_AM(iFrequency);			//display current channel frequency

	KT_AM_Tune( iFrequency - Current_Band.ValidStation_Step );
	AM_afc[0] = KT_AM_GetAFC();
	CODE_Send(0x96);
	DATA_Send(' ');
	DATA_Send(' ');

	if( AM_afc[0] < -Current_Band.AFCTH_Prev )
	{
		KT_AM_Tune( iFrequency );
		AM_afc[1] = KT_AM_GetAFC();
//		delay_n10ms(50);
		snr = KT_AM_GetSNR();
		KT_AM_ReadRSSI( & rssi);		
		CODE_Send(0x96);
		DATA_Send(HexToASCII(snr>>4));
		DATA_Send(HexToASCII(snr));
		
		if (rssi > AM_RSSI_TH)
		{
			if( (AM_afc[1] > -Current_Band.AFCTH) && (AM_afc[1] < Current_Band.AFCTH) && (snr > AM_SNR_TH) )
			{
				KT_AM_Tune( iFrequency + Current_Band.ValidStation_Step );
				AM_afc[2] = KT_AM_GetAFC();
				CODE_Send(0x96);
				DATA_Send(' ');
				DATA_Send(' ');
		
				if( AM_afc[2] > Current_Band.AFCTH_Next )
				{
					if ( (AM_afc[2] > AM_afc[1]) && (AM_afc[1] > AM_afc[0]) )
					{
						return(1);
					}				
					else
						return(0);
				}
				else
				{
					return(0);
				}
			}
			else
			{
				return(0);
			}
		}
		else
		{
			return(0);
		}
	}
	else
	{
		return(0);
	}

#endif

#ifdef AMNEWSEEK
	signed char afc;							//AFC value for previous, current and next channels
	signed char rssi;
	xd_u16 snr;

    //Display_Channel_AM(iFrequency);			//display current channel frequency
	KT_AM_Tune(iFrequency);
	afc = KT_AM_GetAFC();
	KT_AM_ReadRSSI( & rssi);
	if (rssi > AM_RSSI_TH)
	{	
		if ((afc > -MW_AFCTH) && (afc < MW_AFCTH))
		{
//			delay_n10ms(50);
			snr = KT_AM_GetSNR();
			if (snr >= AM_SNR_TH)
				return(1);
			else
				return(0);
		}
		else
			return(0);
	}
	else
		return(0);
#endif

#ifdef AM_SEEK_MODE2
	char afc_prev,afc_next;

    Display_Channel_AM(iFrequency);			//display current channel frequency

	KT_AM_Tune(iFrequency);
	if( KT_AMFM_Tuning_Indicator() )
	{
		KT_AM_Tune(iFrequency - Current_Band.ValidStation_Step);
		afc_prev = KT_AM_GetAFC();
		if ( afc_prev < -Current_Band.AFCTH_Prev)
		{
			KT_AM_Tune(iFrequency + Current_Band.ValidStation_Step);
			afc_next = KT_AM_GetAFC();
			if ( afc_next > Current_Band.AFCTH_Next)
				return(1);
			else
				return(0);
		}
		else
			return(0);
	}
	else
		return(0);
#endif

#ifdef AM_SEEK_MODE3
	char afc;							//AFC value for previous, current and next channels
	char xdata rssi;
	xd_u16 snr;

    Display_Channel_AM(iFrequency);			//display current channel frequency
	KT_AM_Tune(iFrequency);
	afc = KT_AM_GetAFC();
	if ((afc > -MW_AFCTH) && (afc < MW_AFCTH))
	{	
		KT_AM_ReadRSSI( & rssi);
		if (rssi > AM_RSSI_TH)
		{
			snr = KT_AM_GetSNR();
			if (snr >= AM_SNR_TH)
				return(1);
			else
				return(0);
		}
		else
			return(0);
	}
	else
		return(0);
#endif

#ifdef AM_SEEK_MODE4
	char afc;							//AFC value for previous, current and next channels
	char xdata rssi;
	xd_u16 snr;

    Display_Channel_AM(iFrequency);			//display current channel frequency
	KT_AM_Tune(iFrequency);
	snr = KT_AM_GetSNR();
	KT_AM_ReadRSSI( & rssi);

	if ((snr >= AM_SNR_TH) && (rssi  > AM_RSSI_TH))
	{	
		KT_AM_Tune(iFrequency - AM_1KHz_STEP);
		afc = KT_AM_GetAFC();
		if (afc > Current_Band.AFCTH_Prev)
		{
			KT_AM_Tune(iFrequency + AM_1KHz_STEP);
			afc = KT_AM_GetAFC();
			if (afc  < -Current_Band.AFCTH_Next)
			{
				return(1);
			}
			else
			{
 				delay_n10ms(10);
				afc = KT_AM_GetAFC();
				if (afc  < -Current_Band.AFCTH_Next)
					return(1);
				else
					return(0);
			}
		}
		else
		{
 			delay_n10ms(10);
			afc = KT_AM_GetAFC();
			if(afc > Current_Band.AFCTH_Prev)
			{
				KT_AM_Tune(iFrequency + AM_1KHz_STEP);
				afc = KT_AM_GetAFC();
				if (afc  < -Current_Band.AFCTH_Next)
				{
					return(1);
				}
				else
				{
 					delay_n10ms(10);
					afc = KT_AM_GetAFC();
					if (afc  < -Current_Band.AFCTH_Next)
						return(1);
					else
						return(0);
				}
			}
			else
				return(0);
		}
	}
	else
		return(0);
#endif

}

/************************************************************************************/
/*函 数 名：KT_FM_GetAFC															*/
/*功能描述：FM 读取AFC（自动频率控制）程序											*/
/*函数说明：Frequency=-127(KHz) to 127(KHz)											*/
/*调用函数：KT_Bus_Read()						 									*/
/*全局变量：无																		*/
/*输    入：xd_u16 Frequency															*/
/*返    回：char afc_delta															*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
signed char KT_FM_GetAFC(void)  AT(FM_CODE)// returned value's range is from -127 to 127, unit is KHz
{
	signed char afc_delta;
	u16 regx;

	regx = KT_Bus_Read(0x6B);								// read AFC_DELTAF
	afc_delta =(signed char)( regx & 0x00FF);
	return	(afc_delta);	
}

/************************************************************************************/
/*函 数 名：KT_AM_GetAFC															*/
/*功能描述：AM 读取AFC（自动频率控制）程序											*/
/*函数说明：Frequency=-127(KHz) to 127(KHz)											*/
/*调用函数：KT_Bus_Read()						 									*/
/*全局变量：无																		*/
/*输    入：无																		*/
/*返    回：char afc_delta															*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
signed char  KT_AM_GetAFC(void)  AT(FM_CODE)// returned value's range is from -127 to 127, unit is KHz
{
	signed char  afc_delta;
	u16 regx;

	regx = KT_Bus_Read(0x6B);								// read AFC_DELTAF
	afc_delta = (signed char )(regx >> 8);

	return(afc_delta);	
}

/************************************************************************************/
/*函 数 名：KT_AMFM_Tuning_Indicator												*/
/*功能描述：FM tuning灯指示程序														*/
/*函数说明：																		*/
/*调用函数：KT_FM_GetAFC()															*/
/*全局变量：FM_SNR_TH																*/
/*输    入：无																		*/
/*返    回：正确：1					错误：0											*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-08-29								*/
/*版    本：V1.0																	*/
/************************************************************************************/
#if 0
bool KT_AMFM_Tuning_Indicator(void)
{
	u16 regx;

	regx = KT_Bus_Read(0x65);
	regx = regx & 0x2000;
		
	if( regx == 0x2000 )
		return(1);
	else
		return(0);
}
#endif
/************************************************************************************/
/*函 数 名：KT_AM_GetCap															*/
/*功能描述：																		*/
/*函数说明：																		*/
/*调用函数：KT_Bus_Read()															*/
/*全局变量：FM_SNR_TH																*/
/*输    入：无																		*/
/*返    回：正确：1					错误：0											*/
/*设 计 者：Kanghekai				时间：											*/
/*修 改 者：Kanghekai				时间：2011-10-19								*/
/*版    本：V1.1																	*/
/************************************************************************************/
#if 0
u16 KT_AM_GetCap(void)
{
	u16 regx;

	regx = KT_Bus_Read(0x1E);								// read CAP
	return(regx & 0x3FFF);	
}
#endif
#if 0
void KT_AMFM_set_mute(u8 m_flag)
{
	m_flag=m_flag;

	u16 regx;
	if(m_flag){
		regx = KT_Bus_Read(0x61);
		KT_Bus_Write(0x61, regx & 0x0FFF);		//Write volume to 0
		
		regx = KT_Bus_Read(0x62);
		KT_Bus_Write(0x62, regx & 0xEFFF);		//Write volume to 0
	}
	else{
		regx=KT_Bus_Read(0x61);
		KT_Bus_Write(0x61, regx & 0x0FFF | ((0x000F) << 12));
		regx = KT_Bus_Read(0x62);
		KT_Bus_Write(0x62, regx & 0xEFFF | ((0x0001) << 12));
	}
}
#endif	
bool KT_AMFM_Read_ID(void) AT(FM_CODE)
{
	//u8 i;
	u16 regx;

	delay_n10ms(2);
	regx = KT_Bus_Read(0x01);           			//Read Manufactory ID
	// if (regx != 0x4B54) continue;
	//	break;

	if (0x4B54 == regx)
	{
	      KT_AMFM_PreInit();
	      return TRUE;
	}
	return FALSE;		
}
void KT_band_mode_switch_profile(u8 band_mode) AT(FM_CODE)
{
	if(band_mode==FM_MODE){
		
		Current_Band.Band_Top=FM_BAND_TOP;		
		Current_Band.Band_Bottom = FM_BAND_BOTTOM;
		kt_band_mode = 0;

		Current_Band.ValidStation_Step =FM_100KHz_STEP;
		Current_Band.Seek_Step=FM_100KHz_STEP/10;		
		Current_Band.AFCTH_Next =FM_AFCTH_NEXT;
		Current_Band.AFCTH_Prev=FM_AFCTH_PREV;		
	}
	else if(band_mode==MW_MODE){

		Current_Band.Band_Top=MW_BAND_TOP;		
		Current_Band.Band_Bottom = 	MW_BAND_BOTTOM;	
		
		kt_band_mode = 1;

		Current_Band.ValidStation_Step =AM_9KHz_STEP;
		Current_Band.Seek_Step=AM_9KHz_STEP;

	}
#ifdef FM_UART_DEBUG
		my_printf(" --->KT_band_mode_switch_profile :  Current_Band.Band_Top  %4u \r\n",(u16)Current_Band.Band_Top);
		my_printf(" --->KT_band_mode_switch_profile :  Current_Band.Band_Bottom  %4u \r\n",(u16)Current_Band.Band_Bottom);
#endif

	KT_AMFM_SetMode(band_mode);
}
bool KT_set_freq(u16 Freq) AT(FM_CODE)
{
	if(kt_band_mode){
		return KT_AM_ValidStation(Freq);
	}
	else{
		return KT_FM_ValidStation(Freq*10);
	}
}
#endif
