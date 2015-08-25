/************************************************************************************/
/*公司名称：			KT Micro
//
//模 块 名：			KT092X驱动模块头文件
//
//创 建 人：								时间：
//修 改 人：Kanghekai						时间：2012-02-01
//功能描述：
//其他说明： Revision History
//  Version	Date		Description
//  V1.0.0	2011-08-29	Initial draft version
//  V1.0.1	2011-09-16	Modified the value of "AMBADFREQ3" in KT_AMFMdrv.h
//  V1.1.0	2011-10-19	Added the function of "KT_AM_GetCap".
//  V2.0.0	2011-12-26	Clean Up.
//  V2.1.0	2012-02-01	Added 50KHz seek step.
//版    本：V2.1.0
/************************************************************************************/

//#define u8 unsigned char
//#define ulong unsigned long
//#define u16 unsigned int

#define KTAMw_address 0x6A
#define KTAMr_address 0x6B

//#define AMOLDSEEK
//#define FMOLDSEEK

#define AMNEWSEEK
//#define FMNEWSEEK

//#define AM_SEEK_MODE2
//#define FM_SEEK_MODE2

//#define AM_SEEK_MODE3
#define FM_SEEK_MODE3

//#define AM_SEEK_MODE4

#define LOWFM_MODE
#define FMSMUTE						//to enable FM softmute
#define AMSMUTE						//to enable AM softmute
//#define GOODCHANNEL

#define KT0923

#define FM_50K_SPACE
//#define FM_100K_SPACE

#define X32P768K					//32.768KHz crystal
//#define R32P768K					//32.768KHz reference clock
//#define X38K						//38KHz crystal
//#define R38K						//38KHz reference clock
//#define R7P6M						//7.6MHz reference clock
//#define R12M						//12MHz reference clock
//#define R13M						//13MHz reference clock
//#define R24M						//24MHz reference clock
//#define R26M						//26MHz reference clock

#ifdef X32P768K
	#define C32P768K
#endif
#ifdef R32P768K
	#define C32P768K
#endif

#define FM_50KHz_STEP		5
#define FM_100KHz_STEP		10
#define FM_1MHz_STEP		100
#define AM_1KHz_STEP		1
#define AM_2KHz_STEP		2
#define AM_9KHz_STEP		9
#define AM_100KHz_STEP		100

#define FM_SEEK_UP_LIMIT	10800
#define FM_SEEK_DOWN_LIMIT	8600
#define FM_BAND_TOP			1080
#define FM_BAND_BOTTOM		875

#ifdef LOWFM_MODE
#define FM_BAND_BOTTOM		3200
#else
#define FM_BAND_BOTTOM		6400
#endif

#define MW_SEEK_UP_LIMIT	1710
#define MW_SEEK_DOWN_LIMIT	504
#define MW_BAND_TOP			1692
#define MW_BAND_BOTTOM		531


#define FM_AFCTH_PREV		20				//Range from 0 to 127
#define FM_AFCTH			10				//Range from 0 to 127
#define FM_AFCTH_NEXT		20				//Range from 0 to 127
#define FM_SNR_TH			0x10
#define FM_RSSI_TH			-100


#define MW_AFCTH_PREV		6				//Range from 128 to 127
#define MW_AFCTH			4				//Range from 128 to 127
#define MW_AFCTH_NEXT		6				//Range from 128 to 127
#define AM_SNR_TH			0x28
#define AM_RSSI_TH			-66


#define BAND_NUM			2

struct Str_Band
{
	enum Band_Mode	Band;						// 频段
	u16			Band_Top;					//	tune台频段上门限
	u16			Band_Bottom;				//	tune台频段下门限
	u16			Seek_Up_Limit;				//	seek频段上门限
	u16			Seek_Down_Limit;			//	seek频段下门限
	u8			Min_Step;					//
	u8			Max_Step;					//
	u8			Seek_Step;					// SeekFromCurrentCh 函数用的频率步进
	u8			ValidStation_Step;			// ValidStation 函数用的频率步进
	u8			AFCTH_Prev;					//
	u8			AFCTH;						//
	u8			AFCTH_Next;					// 
};
  

#define INIT_FAIL_TH 3

#define SEEKUP 1
#define SEEKDOWN 0


bool KT_AMFM_Read_ID(void);
u8 KT_AMFM_PreInit(void);
u8 KT_AMFM_Init(void);
void KT_AMFM_Standby(void);
void KT_AMFM_WakeUp(void);
u8 KT_AMFM_VolumeSet(u8 cVol);
u8 KT_AMFM_Mute(void);
u8 KT_AMFM_UnMute(void);
u8 KT_AMFM_SetMode(u8 cAMFM_Mode);
u8 KT_AMFM_SetLineIn(u8 cLineNum);
bool KT_AMFM_SetBass(u8 cBass);
void KT_AMFM_Softmute_Initial(void);

u8 KT_AM_SetBW(u8 cFlt_Sel);
u16 KT_AM_GetCap(void);

u8 KT_FM_Tune(u16 iFrequency);
u8 KT_AM_Tune(u16 iFrequency);

u8 KT_FM_ReadRSSI(char *RSSI);
u8 KT_AM_ReadRSSI(char *RSSI);

u16 KT_FM_GetFreq(void);
u16 KT_AM_GetFreq(void);

char KT_FM_GetAFC(void);
char KT_AM_GetAFC(void);

u8 KT_FM_GetSNR(void);
u8 KT_AM_GetSNR(void);

u8 KT_AMFM_SeekFromCurrentCh(bool bSeekDir, u16 *Frequency);   //     seekDir: 0-->seek down 1-->seek up
u8 KT_FM_ValidStation(u16 iFrequency);
u8 KT_AM_ValidStation(u16 iFrequency);

void KT_FM_ST_Indicator_Initial(void);
u8 KT_FM_GetST(void);

bool KT_AMFM_Tuning_Indicator(void);
void KT_FM_Tuning_Indicator_Initial(void);
void KT_AM_Tuning_Indicator_Initial(void);

#ifdef GOODCHANNEL
void KT_FM_Good_Channel(void);
void KT_AM_Good_Channel(void);
#endif

void KT_Bus_Write(u8 Register_Address, u16 Word_Data);
u16 KT_Bus_Read(u8 Register_Address);

void KT_band_mode_switch_profile(u8 band_mode);


#define CHFLT_NOTCH	1				//0: 14kHz corner frequency, 1: 800Hz corner frequency
#define BP_180K		0				//0:enable 180kHz notch filter 1: bypass 180kHz notch filter
#define EN_150K		0				//0:bypass 150kHz notch filter 1: enable 150KHz notch filter
#define BP_190K		0				//0:enable 190kHz notch filter 1: bypass 190kHz notch filter

#define AU_GAIN		2				//0:3dB, 1:6dB, 2:-3dB, 3:0dB
#define AM_GAIN		6				//0:6dB, 1:3dB, 2:0dB, 3:-3dB, 4:-6dB, 5:-9dB, 6:-12dB, 7:-15dB, 8:-18dB
#define IFPGA		1				//0:0dB, 1:6dB, 2:9dB, 3:12dB
#define AMIFPGA		5				//0:11.8dB, 1:10.6dB, 2:9.3dB, 3:7.7dB, 4:5.9dB, 5:3.5dB, 6:-5.1dB, 7:NA

#define AMAFCD		0				//0: enable AM AFC loop, 1: disable AM AFC loop
#define FMAFCD		0				//0: enable FM AFC loop, 1: disable FM AFC loop
#define LOUPEG		0
#define AFCRATE		0
#define AFCBW		0
#define FM_TH_AFC	7
#define AM_TH_AFC	0 				//0:512Hz
#define FM_AFCRF	0				//1:AFC feedback to RF, 0:AFC feedback to DSP

#define DBLND		0				//0: blend enable, 1:blend disable
#define QUICK_BLEND	1				//0: slow blend, 1: quick blend
#define BLNDADJ		2				//

//**********************Interference Frequency*******************//
#define FMBADFREQ0	1806 			//90.3MHz
#define FMDELTAN0	6
#define FMBADFREQ1	1934			//96.7MHz
#define FMDELTAN1	1
#define FMBADFREQ2	1970			//98.5MHz
#define FMDELTAN2	1
#define FMBADFREQ3	1984			//99.2MHz
#define FMDELTAN3	1
#define FMBADFREQ4	2044			//102.2MHz
#define FMDELTAN4	5
#define FMBADFREQ5	2046 			//102.3MHz
#define FMDELTAN5	6
#define FMBADFREQ6	2048 			//102.4MHz
#define FMDELTAN6	7
#define FMBADFREQ7	2104 			//105.2MHz
#define FMDELTAN7	7
#define FMDELTAN	0

#define AMBADFREQ0	1368			//1.368MHz
#define AMDELTAN0	3
#define AMBADFREQ1	684				//684kHz
#define AMDELTAN1	4
#define AMBADFREQ2	909				//909kHz
#define AMDELTAN2	2
#define AMBADFREQ3	1026			//1026kHz
#define AMDELTAN3	3
#define AMBADFREQ4	648				//
#define AMDELTAN4	2
#define AMBADFREQ5	873
#define AMDELTAN5	4
#define AMBADFREQ6	0
#define AMDELTAN6	0
#define AMBADFREQ7	0
#define AMDELTAN7	0
//**********************Interference Frequency end***************//

//***************ST Indicator Configuration**********************//
#define FM_ST_DLY			2		//0:50ms, 1:100ms, 2:150ms, 3:200ms
#define FMST_SEN_HIGHTH		3 		//0:-102, 1:-99,  2:-96, 3:-93
#define FMST_SEN_LOWTH		3 		//0:-105, 1:-102, 2:-99, 3:-96
#define FMST_IND_HIGHTH		3 		//0:5, 1:6, 2:7, 3:8
#define FMST_IND_LOWTH		0 		//0:1, 1:2, 2:3, 3:4
//***************ST Indicator Configuration end******************//

//***************FM Tuning Indicator Configuration***************//
#define FM_TUNE_VALID_WIN	0		//0:50ms, 1:75ms, 2:100ms,3:125ms, 4 :150ms, 5:200ms, 6:300ms, 7:400ms
#define FM_TUNE_VALID_DLY	1		//0:25ms 1:50ms 2:75ms 3:100ms 4 :125ms 5:150ms 6:200ms 7:300ms
#define FM_TUNE_SNR_HIGHTH	0		//0:18, 1:21, 2:24, 3:27, 4:30, 5:33, 6:36, 7:39
#define FM_TUNE_SNR_LOWTH	0		//0:15, 1:18, 2:21, 3:24, 4:27, 5:30, 6:33, 7:36
#define FM_TUNE_AFC_HIGHTH	7		//0:6, 1:9, 2:12, 3:15, 4:18, 5:21, 6:24, 7:27
#define FM_TUNE_AFC_LOWTH	2		//0:3, 1:6, 2:9, 3:12, 4:15, 5:18, 6:21, 7:24
#define FM_TUNE_RSSI_HIGHTH	0		//0:-103dBm 1:-100dBm 2:-97dBm 3:-94dBm 4:-91dBm 5:-88dBm 6:-85dBm 7:-82dBm
#define FM_TUNE_RSSI_LOWTH	0		//0:-106dBm 1:-103dBm 2:-100dBm 3:-97dBm 4:-94dBm 5:-91dBm 6:-88dBm 7:-85dBm
//***************FM Tuning Indicator Configuration end***********//

//***************AM Tuning Indicator*****************************//
#define AM_TUNE_VALID_WIN	0   	//0:50ms, 1:75ms, 2:100ms,3:125ms, 4 :150ms, 5:200ms, 6:300ms, 7:400ms
#define AM_TUNE_VALID_DLY	5		//0:25ms 1:50ms 2:75ms 3:100ms 4 :125ms 5:150ms 6:200ms 7:300ms
#define AM_TUNE_SNR_HIGHTH	0x2A	//Range from 0 to 127
#define AM_TUNE_SNR_LOWTH	0x1C	//Range from 0 to 127
#define AM_TUNE_AFC_HIGHTH	2		//0:4, 1:14, 2:24, 3:34, 4:44, 5:54, 6:64, 7:74
#define AM_TUNE_AFC_LOWTH	3		//0:0, 1:1, 2:2, 3:3, 4:4, 5:5, 6:6, 7:7
#define AM_TUNE_RSSI_HIGHTH	42		//Range from 90 to 127
#define AM_TUNE_RSSI_LOWTH	30		//Range from 90 to 127
//***************AM Tuning Indicator end*************************//

//***************Softmute****************************************//

#define SMUTE_RST_DIS		0		//
#define SMMD				1		//1:SNR mode, 0:RSSI mode

//FM
#define FM_MUTE_TYPE		2		//0:don't mute, 1: mute within 15ms, 2:mute during tune FSM
#define FM_TUNE_DLY			0		//0:0, 1:25ms, 2:50ms, 3:75ms
#define FM_SMUTE_GAIN		13		//0:-45dB,1:-42dB,2:-39dB,3:-36dB,4:-33dB,5:-30dB,6:-27dB,7:-24dB,
									//8:-21dB,9:-18dB,10:-15dB,11:-12dB,12:-9dB,13:-6dB,14:-3dB,15:0dB
#define FM_SMUTE_DLY		0		//
#define FM_SMUTE_WIN		0		//0:25ms, 1:50ms, 2:75ms, 3:100ms
#define FM_SMUTER			3		//0:longest time, 1:long time, 2:short time, 3:shortest time
#define FM_VOLUMET			5		//0:-21dB, 1:-18dB, 2:-15dB, 3:-12dB, 4:-9dB, 5:-6dB, 6:-3dB, 7:0dB
#define FM_SFTMUTE_OFST 	7		//0:6, 1:8, 2:10, 3:12, 4:14, 5:16, 6:18, 7:20
#define FM_SFTMUTE_HIGHTH	0		//RSSI MODE: 	0:-103, 1:-100, 2:-97, 3:-94, 4:-91, 5:-88, 6:-85, 7:-82
									//SNR MODE:		0:18, 2:21, 3:24, 4:27, 5:30, 6:33, 7:36
#define FM_SFTMUTE_LOWTH	0		//RSSI MODE: 	0:-106, 1:-103, 2:-100, 3:-97, 4:-94, 5:-91, 6:-88, 7:-85
									//SNR MODE:		0:15, 2:18, 3:21, 4:24, 5:27, 6:30, 7:33
#define FM_TUNE_SWCH_LATE	0		//0: tune interrupt tune, 1: tune don't interrupt tune

//AM
#define AM_MUTE_TYPE		0		//0:don't mute, 1: mute within 15ms, 2:mute during tune FSM
#define AM_TUNE_DLY			0		//0:0, 1:25ms, 2:50ms, 3:175ms
#define AM_SMUTE_GAIN		13		//0:-45dB,1:-42dB,2:-39dB,3:-36dB,4:-33dB,5:-30dB,6:-27dB,7:-24dB,
									//8:-21dB,9:-18dB,10:-15dB,11:-12dB,12:-9dB,13:-6dB,14:-3dB,15:0dB
#define AM_SMUTE_DLY		0		//0:0, 1:10ms, 2:20ms, 3:30ms, 4:40ms, 5:50ms, 6:60ms, 7:70ms, 
#define AM_SMUTE_WIN		0		//0:25ms, 1:50ms, 2:75ms, 3:100ms
#define AM_SMUTER			3		//0:longest time, 1:long time, 2:short time, 3:shortest time
#define AM_VOLUMET			5		//0:-21dB, 1:-18dB, 2:-15dB, 3:-12dB, 4:-9dB, 5:-6dB, 6:-3dB, 7:0dB
#define AM_SFTMUTE_OFST		7		//0:6, 1:8, 2:10, 3:12, 4:14, 5:16, 6:18, 7:20
#define AM_SFTMUTE_HIGHTH	0x18	//between 0~127
#define AM_SFTMUTE_LOWTH	0x8		//between 0~127
#define AM_TUNE_SWCH_LATE	0		//0: tune interrupt tune, 1: tune don't interrupt tune

//***************Softmute end************************************//
