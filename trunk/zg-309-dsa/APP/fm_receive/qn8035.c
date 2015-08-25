/*--------------------------------------------------------------------------*/
/**@file     qn8035.c
   @brief    qn8035收音底层驱动
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#include "qn8035.h"
//#include "entry.h"
#include "iic.h"



extern void delay_10ms(u8 delay);
extern bool iic_busy;
u16 _xdata aa;
u8   _xdata qnd_PrevMode;
u8   _xdata qnd_CH_STEP  = 1;
u8 _xdata qnd_ChipID;

//extern bool hp_in_busy;

u8 QND_ReadReg(u8 iic_addr)
{
    u8  byte;
//	while(hp_in_busy);
    iic_busy = 1;
    iic_start();                    //I2C启动
    iic_sendbyte(0x20);             //写命令
    iic_sendbyte(iic_addr);         //写地址
    iic_start();                    //写转为读命令，需要再次启动I2C
    iic_sendbyte(0x21);             //读命令
    byte = iic_revbyte(1);
    iic_stop();                     //I2C停止
    iic_busy = 0;

    return  byte;
}

void QND_WriteReg(u8 Regis_Addr,u8 Data)
{
    iic_write(0x20,Regis_Addr,&Data,1);
    //return dat;
}



/**********************************************************************
int QND_Delay()
**********************************************************************
Description: Delay for some ms, to be customized according to user
             application platform

Parameters:
        ms: ms counts
Return Value:
        None

**********************************************************************/
//#define		QND_Delay(ms)

void QND_Delay(u16 ms) 	  //1ms延时
{
    delay(30*ms);   		//rc
}

/**********************************************************************
void QNF_RXInit()
**********************************************************************
Description: set to SNR based MPX control. Call this function before
             tune to one specific channel

Parameters: None
Return Value:   None
**********************************************************************/
void QNF_RXInit()	//////////////
{
    u8 ReadOP;

    QND_WriteReg(0x1B, 0x70);
    QND_WriteReg(0x2C, 0x52);
    //QND_WriteReg(0x1D, 0xA9);
    // QND_WriteReg(0x41, 0xEA);
    QND_WriteReg(0x45, 0x50);

    QND_WriteReg(0x40, 0x70);		//0x71
    QND_WriteReg(0x19, 0xC2);		//0xc0
    //QND_WriteReg(0x3E, 0xB5);
    QND_WriteReg(0x41, 0xCA);

    if (qnd_ChipID == CHIPSUBID_QN8035A0)
    {
        //	QND_WriteReg(0x42, QND_ReadReg(0x42)|0x10);
        ReadOP = QND_ReadReg(0x42);
        ReadOP |= 0x10;
        QND_WriteReg(0x42, ReadOP);
    }


    QND_WriteReg(0x34, 0x19);
    QND_WriteReg(0x35, 0x51);
    QND_WriteReg(0x36, 0x25);
}

/**********************************************************************
void QNF_SetMute(u8 On)
**********************************************************************
Description: set register specified bit
Parameters: On: 1: mute, 0: unmute
Return Value:  None
**********************************************************************/
void QN8035_MUTE(u8 On)	/////////////////////////
{
    if (On)
    {
        if (qnd_ChipID == CHIPSUBID_QN8035A0)
        {
            QND_WriteReg(REG_DAC, 0x1B);
        }
        else
        {
            QND_WriteReg(0x4a, 0x30);
        }
    }
    else
    {
        if (qnd_ChipID == CHIPSUBID_QN8035A0)
        {
            QND_WriteReg(REG_DAC, 0x10);
        }
        else
        {
            QND_WriteReg(0x4a, 0x10);
        }
    }
    QND_Delay(50);
}

/**********************************************************************
void QNF_SetRegBit(u8 reg, u8 bitMask, u8 data_val)
**********************************************************************
Description: set register specified bit

Parameters:
    reg:        register that will be set
    bitMask:    mask specified bit of register
    data_val:    data will be set for specified bit
Return Value: None
***********************************************************************/
void QND_RXSetTH(u8 db) 	 //////设置门限
{
    QND_WriteReg(REG_REF,0x7A);

    //NFILT program is enabled
    QND_WriteReg(0x1B,0x78);

    //using Filter3
    QND_WriteReg(CCA1,0x75);

    //setting CCA IF counter error range value(256).
    QND_WriteReg(CCA_CNT2,0x01);

    QND_WriteReg(PLT1,0x00);

    QND_WriteReg(CCA,QND_ReadReg(CCA)&0xC0|30);

    QND_WriteReg(CCA_SNR_TH_1,8+db); //setting SNR threshold for CCA
}


/**********************************************************************
Function: u8 QNF_SetCh(u16 freq)
Description: set channel frequency
Parameters:	 freq:  channel frequency to be set
Return Value: 1: success
**********************************************************************/
void QNF_SetCh(u16 freq)    //////////////////
{
    // calculate ch parameter used for register setting
    u8 tStep;
    u8 tCh;
    u16 f;

    // QNF_SetRegBit(SYSTEM1, CCA_CH_DIS, CCA_CH_DIS);
    QND_WriteReg(0x00, 0x11);
    f = FREQ2CHREG(freq);

    // set to reg: CH
    tCh = (u8) f;
    QND_WriteReg(CH, tCh);

    // set to reg: CH_STEP
    tStep = QND_ReadReg(CH_STEP);
    tStep &= ~CH_CH;
    tStep |= ((u8) (f >> 8) & CH_CH);
    QND_WriteReg(CH_STEP, tStep);
}

/**********************************************************************
void QNF_ConfigScan(u16 start,u16 stop, u8 step)
**********************************************************************
Description: config start, stop, step register for FM/AM CCA or CCS

Parameters:
    start
        Set the frequency (10kHz) where scan to be started,
        eg: 7600 for 76.00MHz.
    stop
        Set the frequency (10kHz) where scan to be stopped,
        eg: 10800 for 108.00MHz
    step
        1: set leap step to (FM)100kHz / 10kHz(AM)
        2: set leap step to (FM)200kHz / 1kHz(AM)
        0:  set leap step to (FM)50kHz / 9kHz(AM)
Return Value:
         None
**********************************************************************/
void QNF_ConfigScan(u16 fre) ///
{
    // calculate ch para
    u8 tStep = 0;
    u8 tS;
    u16 fStart;

    fStart = FREQ2CHREG(fre);

    // set to reg: CH_START
    tS = (u8) fStart;
    QND_WriteReg(CH_START, tS);
    tStep |= ((u8) (fStart >> 6) & CH_CH_START);

    // set to reg: CH_STOP
    //   tS = (UINT8) fStart;
    QND_WriteReg(CH_STOP, tS);
    tStep |= ((u8) (fStart >> 4) & CH_CH_STOP);

    // set to reg: CH_STEP
    //    tStep |= QND_FSTEP_100KHZ << 6;
    tStep |= 0x40;
    QND_WriteReg(CH_STEP, tStep);
}

/**********************************************************************
void QN_ChipInitialization()
**********************************************************************
Description: chip first step initialization, called only by QND_Init()

Parameters:
None
Return Value:
None
**********************************************************************/
void QN_ChipInitialization()  	 /////初始化
{
    QND_WriteReg(0x00, 0x81);
    delay_10ms(1);//QND_Delay(10);

    qnd_ChipID = QND_ReadReg(CID1) & 0x03;

    // 32.768KHz
    QND_WriteReg(0x01, 0x80); 		//方波
    // QNF_SetRegBit(0x01,0x80,0x00); //SINWAVE

    //QND_WriteReg(0x15, 0x01);
    // QND_WriteReg(0x16, 0x08);
    // QND_WriteReg(0x17, 0x5c);

    QND_WriteReg(0x54, 0x47);		//mod pll setting
    //QND_WriteReg(0x19, 0x40);		//AGC setting
    QND_WriteReg(0x2d, 0xD6);		//notch filter threshold adjusting
    QND_WriteReg(0x43, 0x10);		//notch filter threshold enable
    // QND_WriteReg(0x00, 0x51);	//reset the FSM
    // QND_WriteReg(0x49, 0x7A); 	// reference charge current (enlarge)
    if (qnd_ChipID == CHIPSUBID_QN8035A1)
    {
        QND_WriteReg(0x47, 0x39);
    }

    QND_WriteReg(0x00, 0x11);		//enter RX mode
    // QND_RXConfigAudio(46);
    QND_WriteReg(0x1D,0xA9);
    //QND_WriteReg(VOL_CTL,0x4f);
    QN8035_MUTE(1);
}


void init_QN8035(void)
{
    QN_ChipInitialization();
//	QND_SetSysMode(QND_MODE_RX|QND_MODE_FM);
    QND_WriteReg(0x00,0x11);
    QN8035_MUTE(0);
}


void QN8035_powerdown(void)
{
//	QND_SetSysMode(0);
    QND_WriteReg(SYSTEM1, 0x20);
}


/**********************************************************************
void QND_TuneToCH(u16 Frequen)
**********************************************************************
Description: Tune to the specific channel. call QND_SetSysMode() before
call this function
Parameters:	 ch
Set the frequency (10kHz) to be tuned,
eg: 101.30MHz will be set to 10130.
Return Value:
None
**********************************************************************/
void QND_TuneToCH(u16 Frequen)	   //设置频点
{

    u8 reg;
    u16 ch;

    ch = Frequen * 10;

    QNF_RXInit();


    QN8035_MUTE(1);
    QNF_ConfigScan(ch);
    QNF_SetCh(ch);
    QND_WriteReg(0x00, 0x13);


    QND_WriteReg(0x4F, 0x80);
    reg = QND_ReadReg(0x4F);
    reg >>= 1;
    QND_WriteReg(0x4F, reg);


//    QND_Delay(500);  // 800 // 500
    delay_10ms(30);
//	QND_WriteReg(REG_REF,0x70);

    QN8035_MUTE(0);
//  QNF_SetMute(0);
// return TRUE;
}



/***********************************************************************
u16 QND_RXValidCH(u16 Frequen);
***********************************************************************
Description: to validate a ch (frequency)(if it's a valid channel)
Freq: specific channel frequency, unit: 10Khz
  eg: 108.00MHz will be set to 10800.
Step:
  FM:
  QND_FMSTEP_100KHZ: set leap step to 100kHz
  QND_FMSTEP_200KHZ: set leap step to 200kHz
  QND_FMSTEP_50KHZ:  set leap step to 50kHz
Return Value:
  0: not a valid channel
  other: a valid channel at this frequency
***********************************************************************/
bool QND_RXValidCH(u16 Frequen)  //判断真假台
{
    u8 regValue;
    u8 timeOut = CCA_TIME_OUT;

    u8 snr;

    u16 freq;

    u8 readCnt=0,stereoCount=0;

    freq = Frequen * 10;

    QNF_ConfigScan(freq);

    QND_WriteReg(SYSTEM1, 0x12);

    do
    {
        QND_Delay(5);   		//delay 5ms
        regValue = QND_ReadReg(SYSTEM1);
        timeOut--;
    }
    while ((regValue & CHSC) && timeOut);		//when seeking a channel or time out,be quited the loop
    //read out the rxcca_fail flag of RXCCA status

    regValue = QND_ReadReg(0x04)& 0x08;//reading the rxcca_fail flag of RXCCA status

    if (!regValue)
    {
        QND_Delay(80);
        snr = QND_ReadReg(SNR);
        if (snr> 25)
        {
            return 1;
        }
        for (readCnt=10;readCnt>0;readCnt--)
        {
            QND_Delay(2);
            stereoCount += ((QND_ReadReg(STATUS1) & ST_MO_RX) ? 0:1);
            if (stereoCount >= 3)
            {
                return 1;
            }
        }
    }
    return 0;
}


bool set_fre_QN8035(u16 fre)
{
    /*	if(mode)
    	{
    		QND_TuneToCH(fre);
    		return 1;
    	}
    	else
    	{
    		return QND_RXValidCH(fre);
    	} */
    if (QND_RXValidCH(fre))
    {
        QND_TuneToCH(fre);
        return TRUE;
    }
    return FALSE;
}


bool QN8035_Read_ID(void)
{
    u8  xdata cQNChipID;

    cQNChipID = QND_ReadReg(CID2);
    cQNChipID &= 0xfc;

    if (0x84 == cQNChipID)
    {
        return TRUE;
    }
    return FALSE;
}

void QN8035_setch(u8 db)
{
    QND_RXSetTH(db);
}
