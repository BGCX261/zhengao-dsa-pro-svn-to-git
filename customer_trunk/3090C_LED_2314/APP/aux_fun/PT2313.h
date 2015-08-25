

#ifndef _PT2313_H_
#define _PT2313_H_


//#define SOUND_EFFECT_USE_EPPROM
#define USE_FRONT_CHANNEL
#define USE_REAR_CHANNEL
#define USE_REAR_CHANNEL_FOR_SUBWOOFER
#define PT_2313_OUT_GAIN_11DB
//#define USE_PT2313
#define USE_PT2314
//*************************************************AUDIO
#define	PT_2313_ADDR			0X88
#define	PT_MAIN_VOL_ADDR		0X00

#define	PT_SPK_L_ADDR			0X80
#define	PT_SPK_R_ADDR			0XA0
#define	PT_REAR_L_ADDR		0XC0
#define	PT_REAR_R_ADDR		0XE0

#define	PT_PATH_ADDR			0x40
#define	PT_LOUDNESS_ADDR		0X04

enum
{
    	AUX_CHAN1=0,
    	RADIO_CHAN,
    	AUX_CHAN,
    	DECODE_CHAN,
};
enum
{
    PT_MUTE =0,
    PT_UNMUTE,
};
#define	PT_BASS_ADDR			0X60
#define	PT_TRABLE_ADDR		0X70

#define	PT_BAL_R_ADDR			PT_SPK_R_ADDR
#define	PT_BAL_L_ADDR			PT_SPK_L_ADDR


#define 	PT_MAX_VOL				14
#define 	PT_MIN_VOL				(PT_MAX_VOL/2)

//#define 	PT_MAX_VOL				14
#define	PT_TABLE_MAX			PT_MAX_VOL		

typedef enum
{
    CHAN_ADJ,
    VOL_ADJ,
    BASS_ADJ,
    TRELBE_ADJ,
    EQ_ADJ,
    FADE_ADJ,
    BAL_ADJ,
    LOUD_ADJ,
    MUTE_ADJ,    
    SW_ADJ,
    MIC_ADJ,
    ECHO_ADJ,
}PT2313_CTRL;

#ifdef CUSTOM_DEFINED_PT_2313_CONFIG_CYCLE

typedef enum
{
 
    CONFIG_VOL=1,    
    CONFIG_TRE,
    CONFIG_BAS,    
    CONFIG_SW,
    CONFIG_MIC,        
    CONFIG_ECHO,    
    CONFIG_BAL,
    CONFIG_FAD,
    CONFIG_EQ,
    CONFIG_LUD,       

	
    CONFIG_INIT=CONFIG_VOL,       
    CONFIG_END=CONFIG_ECHO, 
    
}PT2313_CONFIG;

#else

typedef enum
{
    CONFIG_BAS=1,    
    CONFIG_TRE,
    CONFIG_BAL,
    CONFIG_FAD,
    CONFIG_VOL,    
    CONFIG_EQ,
    CONFIG_LUD,
    CONFIG_SW,
    CONFIG_MIC,        
    CONFIG_ECHO,     

    CONFIG_INIT=CONFIG_VOL,     
    CONFIG_END=CONFIG_EQ,       
    
}PT2313_CONFIG;

#endif

typedef enum
{
	PT_UP = 1,
	PT_DW,	
	
}PT_CTRL_CMD;

void PT2313_Config(u8 PT_PARA,PT2313_CTRL PT_CMD);
void PT2313_Init(void);
void PT2312_reset(void);

//bool get_pt_2313_londness_flag();

#endif
