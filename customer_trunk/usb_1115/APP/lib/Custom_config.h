/************************************************************
*	SYSTEM GLOBAL OPTIONS
*************************************************************/
//#define USE_AUTO_FREQ
//#define AC209_28PIN		//28 PIN IC GPIO CONFIG

//#define SYS_CRYSTAL_USE_24M
//#define SYS_CRYSTAL_USE_12M

//#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE

//#define USE_SYS_MODE_RECOVER		//系统上电模式记忆功能

//#define USE_BAT_MANAGEMENT

//#define OTP_MUSIC_FUNC_ENABLE

//#define VOLUME_CUSTOMER_DEFINE

//#define KEY_100_ENABLE

//#define SUPPORT_PT2313

//#define NO_VOLUME_LIMITE

//#define VOLUME_DEFUALT 	0
/************************************************************
*	GPIO CTRL  OPTIONS
*************************************************************/
//#define ADKEY_NEW_METHOD

//#define EXTENDED_ADKEY_NUM

//#define TWO_ADKEY_ENABLE

//#define KEY_TONE_ENABEL

//#define USE_POWER_KEY

//#define INDEPENDENT_VOLUME_KEY

//#define  IR_MUTE_USE_NORMAL

/************************************************************
*	GPIO CTRL  OPTIONS
*************************************************************/
/*UART PORT ENABLE DEFINE*/
#define   UART_ENABLE
#ifdef UART_ENABLE
#define 	_USE_UART_P2_
//#define _USE_UART_P0_
#endif

//#define TURN_ON_PLAY_BREAK_POINT_MEM
#define EEPROM_RTC_RAM_COMPATIBLE

/*MUTE PORT DEFINE*/
//#define	MUTE_PORT_USE_P01
//#define   MUTE_PORT_USE_P00
#define MUTE_PORT_USE_P03

#define MUTE_CTRL_LEVEL_NORMAL
#define LED_CTRL_LEVEL_NORMAL
#define NEW_CUSTOMIZED_LED_METHOD

//#define IIC_GPIO_USE_P02_P03	//4 Default IIC GPIO
#define IIC_GPIO_USE_P00_P01

#define ADKEY_USE_PORT_P06

/*PLAY STATUS LED PORT DEFINE*/
//#define PLAY_STATUS_LED_P07
//#define PLAY_STATUS_LED_P27
//DEFAULT GPIO P07

//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT

/************************************************************
*	AUDIO DECODE  OPTIONS
*************************************************************/
//#define USB_SD_PLAY_INFO_DIV

#define USE_USB_AUDIO

//#define FF_FR_TURN_ON_MUSIC

//#define DECODE_STOP_MODE_ENABLE

//#define PLAY_MODE_MEM_RECOVER	//播放模式记忆功能
/************************************************************
*	FM REV OPTIONS
*************************************************************/
#define USE_RDAs_FM
#define USE_BK1080_FM
//#define USE_CL6017G_FM
//#define USE_SP3777_FM
#define USE_QN8035_FM
//#define FM_USE_KT0830EG
//#define FM_USE_KT0913

//#define USE_FM_GPIO

#define FM_INDEPENDENT_OSC

/*FM CRYSTAL DEFINE*/
//#define          _SHARE_CRYSTAL_24MHz_   	//共用24MHz晶振，请打开此宏
//#define       _SHARE_CRYSTAL_12MHz_   	//共用12MHz晶振，请打开此宏
//#define       _SHARE_CRYSTAL_32KHz_   	//4共用32KHz晶振，请打开此宏
//#define       _FM_STEP_50K_           		//50K步进，请打开此宏

//#define RADIO_AM_WM_ENABLE
//#define KEEP_SILENT_WHEN_SCAN_CHANNEL

//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define SEMI_AUTO_SCAN_FREQ	//半自动搜台

//#define IR_PLAY_KEY_SCAN_FREQ_DISABLE
//#define IR_NEXT_PREV_SHORT_AUTO_SCAN
//#define IR_NEXT_PREV_SHORT_ADJ_CH
//#define IR_NEXT_PREV_HOLD_AUTO_SCAN

//#define ADKEY_NEXT_ADJST_FREQ
//#define ADKEY_NEXT_PREV_SHORT_ADJ_CH
//#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN

//#define FM_TRANSMITTER
/************************************************************
*	AUX  OPTIONS
*************************************************************/
//#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

//#define USE_MANUAL_IDLE_FUNC		//手动切换到IDLE

//#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能

//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能

//#define ADC_DETECT_LINE_IN

//#define FM_BY_PASS

//#define LINE_IN_PLAY_KEY_PAUSE

//#define IPONE_INDEPENDENT_MODE

//#define IPONE_DOCK_FUNC_ENABLE

/************************************************************
*	RTC  OPTIONS
*************************************************************/

//#define USE_RTC_RAM_FUNC

//#define USE_RTC_FUNC

//#define USE_RTC_TIME_ONLY

//#define USE_RTC_YEAR_FUNCTION

//#define USE_RTC_ALARM_FUNCTION
/************************************************************
*	IR  OPTIONS
*************************************************************/
//#default: IR_USER_CODE_0xFF00

//#define IR_USER_CODE_0x7F80

//#define IR_REMOTER_WITH_POWER_MUTE_PRINT
//#define IR_REMOTER_WITH_CHANEL_SELECT

//#define IR_TYPE_DEFINE	NORMAL

/************************************************************
*	DISPLAY OPTIONS,LED TYPE SELECT
*************************************************************/
//#define DISPLAY_NO_DEV_WHEN_NO_SD_USB

#define LED_GPIO_DRV				//GPIO直接驱动LED
//#define LED_DRVER_USE_SM1628		// SM 1628 驱动IC
//#define LCD_GPIO_DRV				//GPIO直接驱动LCD
//#define USE_LCD_DRV_HT1621

//#define NO_LED_DISPLAY
//#define LED_USE_PLAY_STATUS	//默认LED 模组
//#define LED_USE_PLAY_MODE
//#define LED_USE_PLAY_MODE_MIXED
//#define LED_USE_1X888
//#define LED_USE_ROUND_LED

//#define LED_DRV_IN_COM_CATHODE	//LED 共阴类型
//#define LED_DRV_IN_COM_ANODE		//LED共阳类型


/************************************************************
*	OTHER CUSTOMED OPTIONS
*************************************************************/
//#define POWE_KEY_PLAY_KEY_IN_ONE_KEY	//PLAY POWER 共用一个按键
//#define  POWER_KEY_ON_WAIT_FOR_3_SEC
//#define  SYS_GO_IN_IDLE_IN_30_SEC
//#define  GPIO_SWITCH_SELECT_MODE
//#define JOG_STICK_FUNC
//#define NO_ADKEY_FUNC
//#define  USE_AMP_MODE_SELECT
/************************************************************
*	OTHER CUSTOMED OPTIONS  END
*************************************************************/
/**Customer & version **/
#if 0
#define   UART_ENABLE

#define NO_LED_DISPLAY
#define FM_TRANSMITTER
#define IIC_GPIO_USE_P00_P01
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif

#endif
//4 SW 声音级别限制到28
//#define SW_V001		
//#define SW_V002		//4 长按搜索，短按CH
//#define SW_V002_747		//4 长按搜索，短按CH
//#define K003_V001		//K026_XXX_V001
//#define SW_V007_502K
//#define Kxxx_931_V001

//4 按 主板编号定义宏
/***/
//#define K005_987_V001
//#define K009_968_SW006_V001	//(921)
//#define K009_968_SW006_ZHUOXIN_V001
//#define K010_931_V001
//#define K010_YJH_931_V001
//#define K010_QDX_PM21_V001
//#define K013_980_V001
//#define K015_983_SW005_V001
//#define K015_983_SW005_AMFM_V001
//#define K015_983_SW005_ZX_V001
//#define K015_983_JLH_V001
//#define K015_983_JLH_VOL50_V001
//#define K015_983_SW005_V8
//#define K015_983_1_SW005_V001
//#define K015_983_SW005_ZhuoXin_V001
//#define K015_983_SW005_ZhuoXin_KL001_V001
//#define K015_983_SW005_ZhuoXin_FB001_V001
//#define K015_983_SW005_ZhuoXin_KL002_V001
//#define K015_983_SW005_ZhuoXin_JR001_V001
//#define K002_SW_002_Zhuoxin_V001
//#define K031_XXX_V001
//#define K020_WEIQI_V001
//#define K021_XXX_V001
//#define K023_971_V001
//#define K011_011_V001
//#define K025_XXX_V001
//#define K080_YJH_985_V001
//#define K081_YJH_973_V001
//#define K026_XXX_V001
//#define K037_XXX_V001
//#define K077_BoDa_V001
//#define K085_YJH_085_V001
//#define K063_YJH_063_V001
//#define K116_FXK_V001
//#define K005_987_FOR_JLH_V001
//#define K101_TianCheng_101_V001
//#define K128_YJH_128_V001
//#define K133_QDX_133_V001
//#define K162_QDX_162_V001
//#define K105_SWD_2901_V001
//#define K105_SWD_2901A_V001
//#define K122_SWD_122_V001
//#define K196_MN_196_V001
//#define K180_LY_180_V001
//#define K181_LY_181_V001
//#define K181_YJH_181_V001
//#define K186_ZHHB_S30_V001
//#define K186_LM_186_V001
//#define K189_JM_201_V001
//#define K000_RS_228U_V001
//****************#define K208_ZY_KL208_V001
//#define K171_YJH_171_V001
//#define K171_SW_012_V001
//#define K171_ZX_SW012_ET1013FM_V001
//#define K171_LanQin_012_V001
//#define K171_LT_171_V001
//#define K170_ZHUOXIN_UK3_V001
//#define K170_ZK_170_V001
//#define K170_YJH_170_V001
//#define K170_LanQin_170_V001
//#define K170_YDS_170_V001
//#define K170_QDX_170_V001
//#define K170_QDX_PM_A01_V001
//#define K170_HAO_SHENG_170_V001
//#define K015_JLH_2946_V001
//#define K610_YJH_803_V001
//#define K619_FXK_619_V001
//#define K223_BTL_CP153_V001
//#define K305_ZhuoXin_305_V001
//#define K000_Zhongwei_SP_016_V001
//#define K307_ZX_307_V001
//#define K637_ZX_306_V001
//#define K643_FW_643_V001
//#define K532_YJH_532_V001
//#define K272_JH_272_V001
//#define K646_ZhuoXing_308_V001
//#define K523_DeYun_523_V001
//#define K202_JiaMei_202_V001
//#define K316_ZhuoXing_316_V001
//#define K317_ZhuoXing_317_V001
//#define K316_MONO_316_V001
//#define K704_JM_502_V001
//#define K704_JM_503_V001
//#define K709_AOKAILIN_709_V001
//#define K572_AOKAILIN_811_V001
//#define K573_AOKAILIN_812_V001
//#define K686_ZhengYang_686_V001
//#define K812_DingChuangXin_D903_V001
//#define K801_DingChuangXin_801_V001
//#define K668_YJH_815_V001
//#define K693_YJH_693_V001
//#define K719_YJH_719_V001
//#define K716_RiYueTong_716_V001
//#define K321_Zhuoxing_321_LED_V001
//#define K321_Zhuoxing_321_LCD_V001
//#define K720_YJH_720_V001
//#define K723_LUOMAO_723_V001
//#define K728_SUOERSI_728_V001
//#define K737_JinYiHeLi_737_V001
//#define K756_JinYiHeLi_756_V001
//#define K000_JLH_309F_V001
//#define K731_YJH_731_V001
//#define K731_YJH_820_V001
//#define K733_JM_733_V001
///////////////////////////////////#define K585_YJH_585_V001
//#define K565_FXK_565_V001
//#define K566_JinRui_566_V001
//#define K566_JLH_566_V001
//#define K565_JLH_565_V001
//#define K568_JinRui_568_V001
//#define K000_ZhuoYue_003_V001
//#define K739_YJH_739_V001
//#define K760_YJH_760_V001
//#define K745_SUOERSI_745_V001
//#define K591_JiaLe_591_V001
//#define K592_YJH_592_V001
//#define K593_YJH_593_V001
//#define K000_AOKAILIN_G01_V001
//#define K000_AOKAILIN_508_V001
//#define K000_XingChuang_x819_V001
//#define K000_XingChuang_x821_V001
//#define K000_KT_AMFM_V001
//#define K766_YJH_766_V001
//#define K771_YJH_771_V001
//#define K762_JinYiHeLi_762_V001
//#define K763_JinYiHeLi_763_V001
//#define K769_JinRui_769_V001
//#define K000_HG_898_V001
//#define K777_SW_777_V001
//#define K807_YJH_807_V001
//#define K779_YJH_779_V001
//#define K773_MingYang_773_V001
//#define K714_FW_016A_V001


/************************************************************
*	28PIN BOARD DEFINE
************************************************************/
//#define K088_JLH_23108_V001
//#define K113_SW_113_V001
//#define K115_SW_115_V001
//#define K163_ZHHB_163_V001
//#define K169_KR_169_V001
//#define K188_YJH_188_V001
//#define K188_YJH_188_V002
//#define K139_JLH_xxx_V001
//#define K139_FuWei_xxx_V001
//#define K139_YDS_xxx_V001
//#define K000_DT_078_V001
//#define K109_SW001D_V001
//#define K198_SW198_V001
//#define K608_TC_608_V001
//#define K608_TC_608_V002
//#define K801_TC_801_V001
//#define K801_TC_801_V002
//#define K987_YJH_987_V001
//#define K172_AJE_172_V001
//#define K200_KY_021_V001
//#define K209_WS_GKD209_V001
//#define K202_WS_01_V001
//#define K609_KL_609_V001
//#define K505_CJB_505_V001
//#define K507_YJH_507_V001
//#define K617_LHGC_617_V001
//#define K627_LHGC_627_V001
//#define K639_YJH_639_V001
//#define K519_YJH_808_V001
//#define K519_YJH_808_V002
//#define K232_GKD_232_V001
//#define K525_DeYun_525_V001
//#define K667_YJH_667_V001
//#define K302_ZhengYang_ZY302_V001
//#define K071_ZhengYang_ZY071_V001
//#define K676_FXK_676_V001
//#define K555_FXK_555_V001
//#define K703_JM_YX006_V001
//#define K711_JM_YX450_V001
//#define K705_YJH_705_V001
//#define K679_YJH_679_V001
//#define K560_YJH_560_V001
//#define K710_AoKaiLin_710_V001
//#define K811_DingChuangXin_811_V001
//#define K692_SES_692_V001
//#define K695_SES_695_V001
//#define K120_YJH_120_V001
//#define K120_SW_015_V001
//#define K562_QDX_562_V001
//#define K800_MingYang_800_V001
//////////#define K319_ZhuoXing_319_V001
//#define K320_ZhuoXing_320_V001
//#define K722_YJH_722_V001
//#define K806_LiHaoDe_806_V001
//#define K727_LiHaoDe_727_V001
//#define K202_WEISI_KL202_V001
//#define K583_ZX_583_V001
/////#define K586_LHD_LT30_V001
//#define K738_LHD_LTB1_V001
//#define K740_LHD_916_V001
//#define K000_XingChuang_X816_V001
//#define K736_TaiYangSheng_736_V001
//#define K589_JYHL_589_V001
//#define K746_JIALE_746_V001
//#define K755_JinYeHeLi_755_V001
//#define K755_AnJieEr_755_V001
//#define K765_YJH_765_V001
//#define K598_YJH_598_V001
//#define K599_JinRui_599_V001
//#define K770_JinRui_770_V001
//#define K000_MingYang_1003A_V001
//#define K086_JLH_2096_V001
//#define K776_CaiRun_776_V001
#define K1115_USB_V001


#ifdef K1115_USB_V001

#define NO_IRC_FUNC
#define ADKEY_USE_PORT_P06
#define DSA_PORT_P15_P16_P17

#define DISABLE_P05_OSC_OUTPUT
#define USE_FOLDER_SELECT_FUNC
#define ADKEY_NEXT_PREV_LONG_SEL_FOLDER
#define NO_PLAY_STATUS_LED
#define NOT_USE_LINE_IN_FUNC
#define DECODE_STOP_MODE_ENABLE

#define AC_SLAVE_ENABLE
#define SYS_DEFAULT_IN_IDLE
#define DEFAULT_GO_TO_IDLE

#define NEXT_PREV_10_FUNC
#define VOLUME_DEFUALT	30

#endif


/*****************按 主板编号定义宏******************/

#ifdef K773_MingYang_773_V001

#define NO_LED_DISPLAY

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define ADKEY_USE_P04_PORT

#define DECODE_STOP_MODE_ENABLE
#define PLAY_LONG_PRESS_STOP

#define FM_BY_PASS
#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define ADKEY_PLAY_SHORT_SCAN_FRE

#define INDEPENDENT_VOLUME_KEY

#define IPONE_DOCK_FUNC_ENABLE
#define IPONE_INDEPENDENT_MODE
#define IPHONE_TX_USE_P06
#define TURN_ON_MUSIC_WHEN_IPHONE_DOCK

#endif


#ifdef K714_FW_016A_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED

//#define INDEPENDENT_VOLUME_KEY
#define LED_USE_1X888
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE

#define USE_LINE_IN_DETECT_FUNC
#define AUX_DETECT_USE_P02

#endif

#ifdef K779_YJH_779_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03

#define NO_PLAY_STATUS_LED

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define CUSTOMIZED_KEY_FUNC_ENABLE

#define INDEPENDENT_VOLUME_KEY

#endif

#ifdef K807_YJH_807_V001

#define LED_USE_ROUND_LED

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define NO_PLAY_STATUS_LED
#define NEW_SD_DETECT_MOD

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN

#define INDEPENDENT_VOLUME_KEY
#define NOT_USE_LINE_IN_FUNC

#endif

#ifdef K777_SW_777_V001

#define NO_PLAY_STATUS_LED
#define LED_USE_PLAY_MODE_MIXED

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define ADKEY_NEW_METHOD
#define TWO_ADKEY_ENABLE
#define EXTENDED_ADKEY_NUM
#define KEY_100_ENABLE
#define CUSTOMIZED_EQ_MODE
#define INDEPENDENT_VOLUME_KEY
#define IR_REMOTER_WITH_POWER_MUTE_PRINT

#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_HOLD_AUTO_SCAN

#endif

#ifdef K000_HG_898_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_DUMP

#define MP3_PUASE_FLASH_FIGURE
#define DECODE_STOP_MODE_ENABLE
#define STOP_MODE_SHOW_STOP
#define EQ_ADJ_USE_STOP_KEY_LONG

#define CUSTOMER_DEFINED_ADKEY_RESISTOR

#define NO_PLAY_STATUS_LED
#define USE_USB_AUDIO
#define MP3_DISP_LOAD_STRING
#define DEFAULT_GO_TO_IDLE

#define FORCE_GO_TO_MP3_MODE
#define USE_MANUAL_IDLE_FUNC
#define MUTE_ON_FLASH_WHOLE_SCREEN

#define ADKEY_NEXT_ADJST_FREQ


#define NOT_USE_LINE_IN_FUNC

#endif


#ifdef K769_JinRui_769_V001

#define LED_USE_PLAY_MODE
//#define LED_GPIO_PORT_CUSTOMERIZED

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define NO_PLAY_STATUS_LED
//#define USE_USB_AUDIO
#define NEW_CUSTOMED_VOLUME_DIVIDED_METHOD
#define DECODE_STOP_MODE_ENABLE
#define STOP_MODE_SHOW_STOP
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define LINE_IN_PLAY_KEY_PAUSE
#define LINE_IN_PLAY_KEY_NO_PAUSE_ICON_INDICATOR

#endif


#ifdef K771_YJH_771_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED

#endif
#ifdef K766_YJH_766_V001

#define LED_USE_1X888

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NO_PLAY_STATUS_LED

#define USE_GPIO_DETECT_EARPHONE_PLUGGED

#endif

#ifdef K000_KT_AMFM_V001
#define FM_USE_KT0913

#ifdef USE_BK1080_FM
#undef USE_BK1080_FM
#endif

#ifdef USE_QN8035_FM
#undef USE_QN8035_FM
#endif

#ifdef LED_GPIO_DRV
#undef  LED_GPIO_DRV
#endif
#define LCD_GPIO_DRV

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_WKUP

//#define MUTE_ON_FLASH_WHOLE_SCREEN
//#define IR_REMOTER_WITH_POWER_MUTE_PRINT

//#define PLAY_STATUS_LED_P04

#define RADIO_AM_WM_ENABLE

//#define ADKEY_USE_P07_PORT
//#define TWO_ADKEY_ENABLE
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define DECODE_STOP_MODE_ENABLE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define ADKEY_NEXT_ADJST_FREQ

#define USE_RTC_FUNCTION
#define USE_RTC_TIME_ONLY
#define USE_RTC_ALARM_FUNCTION

#define SPECTRUM_FUNC_ENABLE
#define JOG_STICK_FUNC
#endif


#ifdef K000_AOKAILIN_508_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P04
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define ADKEY_USE_P07_PORT

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NO_PLAY_STATUS_LED

#define LED_GPIO_PORT_CUSTOMERIZED


#define USE_POWER_KEY
#define PWR_CTRL_WKUP
//#define USE_ONLY_POWER_HOLD_CTRL
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define CUSTOMER_DEFINED_ADKEY_RESISTOR

#define USE_POWER_KEY_SHORT_SCAN

#define USE_LINE_IN_DETECT_FUNC
#define AUX_DETECT_USE_P06
#define USE_BAT_MANAGEMENT
//#define CHARGER_DETECT_INDICATOR
#define USE_USB_AUDIO
#define FM_USE_KT0830EG

#endif

#ifdef K000_AOKAILIN_G01_V001

#define LED_USE_PLAY_MODE

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NO_PLAY_STATUS_LED

#define USE_POWER_KEY
#define PWR_CTRL_P02_KEY_P04
#define USE_ONLY_POWER_HOLD_CTRL
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define CUSTOMER_DEFINED_ADKEY_RESISTOR

#define USE_POWER_KEY_SHORT_SCAN

#define USE_LINE_IN_DETECT_FUNC
#define AUX_DETECT_USE_P07
#define USE_BAT_MANAGEMENT
#define CHARGER_DETECT_INDICATOR
#define USE_USB_AUDIO

#endif

#ifdef K593_YJH_593_V001

#define LED_USE_ROUND_LED

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define PLAY_STATUS_LED_P04

#define USE_USB_AUDIO

#endif

#ifdef K592_YJH_592_V001

#define LED_USE_1X888

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NO_PLAY_STATUS_LED

#define USE_USB_AUDIO

#endif

#ifdef K760_YJH_760_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NO_PLAY_STATUS_LED

#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_USB_AUDIO

#endif

#ifdef K739_YJH_739_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NO_PLAY_STATUS_LED

#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_USB_AUDIO

#endif


#ifdef K000_XingChuang_x821_V001

#define ADKEY_USE_P07_PORT

#ifdef LED_GPIO_DRV
#undef  LED_GPIO_DRV
#endif
#define LCD_GPIO_DRV

#define FM_BY_PASS

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
//#define INDEPENDENT_VOLUME_KEY
#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define KEY_100_ENABLE

#define IPONE_DOCK_FUNC_ENABLE
#define IPONE_INDEPENDENT_MODE
#define IPHONE_TX_USE_P06
#define IPHONE_DETECT_USE_P04
#define IPHONE_DETECT_IN_USE
#define IPHONE_DOCKING_PRO
#define TURN_ON_MUSIC_WHEN_IPHONE_DOCK

#define LED_STATUS_STOP_AT_VALID_STATION
#ifdef  MUTE_CTRL_LEVEL_NORMAL
#undef MUTE_CTRL_LEVEL_NORMAL
#endif
#ifdef  LED_CTRL_LEVEL_NORMAL
#undef LED_CTRL_LEVEL_NORMAL
#endif

#define ONE_WIRE_TUNE_ENABLE
#define NEW_CUSTOMIZED_LED_METHOD
#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_LINE_IN_DETECT_FUNC
#define AUX_DETECT_USE_P03

#define USE_SPECTRUM_PARTTERN

#endif

#ifdef K000_XingChuang_x819_V001

#define ADKEY_USE_P07_PORT

#define NO_LED_DISPLAY
#define FM_BY_PASS

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define INDEPENDENT_VOLUME_KEY
#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define KEY_100_ENABLE

#define IPONE_DOCK_FUNC_ENABLE
#define IPONE_INDEPENDENT_MODE
#define IPHONE_TX_USE_P06
#define IPHONE_DETECT_USE_P04
#define IPHONE_DETECT_IN_USE
#define IPHONE_DOCKING_PRO
#define TURN_ON_MUSIC_WHEN_IPHONE_DOCK

#define LED_STATUS_STOP_AT_VALID_STATION
#ifdef  MUTE_CTRL_LEVEL_NORMAL
#undef MUTE_CTRL_LEVEL_NORMAL
#endif
#ifdef  LED_CTRL_LEVEL_NORMAL
#undef LED_CTRL_LEVEL_NORMAL
#endif

#define ONE_WIRE_TUNE_ENABLE
#define NEW_CUSTOMIZED_LED_METHOD
#define ADKEY_PLAY_SHORT_SCAN_FRE

#endif

#ifdef K000_ZhuoYue_003_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03

#ifdef LED_GPIO_DRV
#undef  LED_GPIO_DRV
#endif
#define LCD_GPIO_DRV

#define NO_PLAY_STATUS_LED
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define IPONE_DOCK_FUNC_ENABLE
#define IPONE_INDEPENDENT_MODE
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define ADKEY_USE_P07_PORT
#define IPHONE_TX_USE_P06
#define TIME_FORCE_SHOW_ON_SCREEN
//#define PWR_CTRL_P04_KEY_P02
#define DONT_MOUNT_AUX_FUNC
#define SPECTRUM_FUNC_ENABLE
#define IPHONE_USE_LINE_IN_CHANNEL_AUX0

#define USE_RTC_FUNCTION
#define USE_RTC_TIME_ONLY
#define USE_RTC_ALARM_FUNCTION
//#define USE_SPECTRUM_PARTTERN
#endif

#ifdef K568_JinRui_568_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define USE_USB_AUDIO
#define NEW_CUSTOMED_VOLUME_DIVIDED_METHOD
#define DECODE_STOP_MODE_ENABLE
#define STOP_MODE_SHOW_STOP
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define LINE_IN_PLAY_KEY_PAUSE
#define LINE_IN_PLAY_KEY_NO_PAUSE_ICON_INDICATOR

#endif

#ifdef K566_JLH_566_V001

#ifdef IIC_GPIO_USE_P02_P03
//#undef IIC_GPIO_USE_P02_P03
#endif
//#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
//#undef  MUTE_PORT_USE_P01
#endif
//#define MUTE_PORT_USE_P03
//#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define NO_PLAY_STATUS_LED
//#define USE_USB_AUDIO
#define NEW_CUSTOMED_VOLUME_DIVIDED_METHOD
#define DECODE_STOP_MODE_ENABLE
#define STOP_MODE_SHOW_STOP
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define LINE_IN_PLAY_KEY_PAUSE
#define LINE_IN_PLAY_KEY_NO_PAUSE_ICON_INDICATOR
#define IR_USER_CODE_0x7F80
#define EQ_DOWN_SCAN_ALL

#endif

#ifdef K566_JinRui_566_V001

#ifdef IIC_GPIO_USE_P00_P01
#undef IIC_GPIO_USE_P00_P01
#endif
#define IIC_GPIO_USE_P02_P03


#define MUTE_PORT_USE_P01

//#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define VOLUME_DEFUALT	30
#ifdef LED_CTRL_LEVEL_NORMAL
#undef  LED_CTRL_LEVEL_NORMAL
#endif

#define IR_REMOTE_TYPE_016
#define NO_REM_LAST_DEV
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define NO_LED_DISPLAY
//#define NO_DEV_DEFAULT_GO_TO_IDLE
//#define NEW_CUSTOMED_VOLUME_DIVIDED_METHOD
#define DECODE_STOP_MODE_ENABLE

#define LINE_IN_PLAY_KEY_PAUSE
#define LINE_IN_PLAY_KEY_NO_PAUSE_ICON_INDICATOR

#endif

#ifdef K585_YJH_585_V001

#define LED_USE_PLAY_MODE
#define USE_BAT_MANAGEMENT

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P02_KEY_P04
#define USE_ONLY_POWER_HOLD_CTRL
#define USE_PWR_KEY_LONG_PWR_ON

#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define NO_PLAY_STATUS_LED
#define TWO_ADKEY_ENABLE
#define TWO_ADKEY_USE_PORT_P07
#define INDEPENDENT_VOLUME_KEY
#define SEMI_AUTO_SCAN_FREQ
#define USE_POWER_KEY_SHORT_SCAN
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define NOT_USE_LINE_IN_FUNC
#define USE_USB_AUDIO

#define USE_RTC_FUNCTION
#define USE_RTC_ALARM_FUNCTION
#endif


#ifdef K733_JM_733_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define INDEPENDENT_VOLUME_KEY
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define NO_PLAY_STATUS_LED
#define ROUND_LED_USE_OFFEN
#define USE_USB_AUDIO

#endif
#ifdef K731_YJH_731_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define NO_PLAY_STATUS_LED
#define USE_USB_AUDIO
#define LED_GPIO_PORT_CUSTOMERIZED
#define NO_VOLUME_LIMITE

#endif
#ifdef K731_YJH_820_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define NO_PLAY_STATUS_LED
#define USE_USB_AUDIO
#define LED_GPIO_PORT_CUSTOMERIZED
#define NO_VOLUME_LIMITE

#endif

#ifdef K000_JLH_309F_V001

#define LED_USE_PLAY_MODE
#define EXCHANGE_LINE_IN_CHANNEL		//交换LINE IN 通道

#define ADKEY_USE_P07_PORT
#define NO_PLAY_STATUS_LED
#define EXCHANGE_FM_AUX_PRIO
#define VOLUME_DEFUALT	32
#define VOLUME_CUSTOMER_DEFINE_32

#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define ADKEY_NEXT_ADJST_FREQ
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define PALY_MODE_USE_REP_ONE_ALL
#define LED_GPIO_PORT_CUSTOMERIZED
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define USE_IR_VPP_PORT_FORDETECTION
#define KEY_100_ENABLE
#define DEFAULT_GO_TO_FM
#endif

#ifdef K763_JinYiHeLi_763_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define NO_PLAY_STATUS_LED

//#define LED_USE_ROUND_LED
#define LED_USE_PLAY_MODE
#define USE_BAT_MANAGEMENT
#define INDEPENDENT_VOLUME_KEY

#define USE_GPIO_DETECT_EARPHONE_PLUGGED


#define USB_SD_PLAY_INFO_DIV

//#define LINE_IN_PLAY_KEY_PAUSE
//#define LINE_IN_PLAY_KEY_NO_PAUSE_ICON_INDICATOR
//#define USE_POWER_KEY_FOR_AUX_PLAY
#endif

#ifdef K762_JinYiHeLi_762_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define NO_PLAY_STATUS_LED
#define TWO_ADKEY_ENABLE
#define TWO_ADKEY_USE_PORT_P04

#define POWER_KEY_LONG_POWER_OFF
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define USE_POWER_KEY_SHORT_SCAN

#define CUSTOMER_DEFINED_ADKEY_RESISTOR
//#define LED_USE_ROUND_LED
#define LED_USE_PLAY_MODE
#define USE_BAT_MANAGEMENT
#define INDEPENDENT_VOLUME_KEY

#define USE_GPIO_DETECT_EARPHONE_PLUGGED

//#define USE_LINE_IN_DETECT_FUNC
//#define AUX_DETECT_USE_P07
#define USB_SD_PLAY_INFO_DIV

#define LINE_IN_PLAY_KEY_PAUSE
#define LINE_IN_PLAY_KEY_NO_PAUSE_ICON_INDICATOR
#define USE_POWER_KEY_FOR_AUX_PLAY
#endif


#ifdef K756_JinYiHeLi_756_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define NO_PLAY_STATUS_LED
#define TWO_ADKEY_ENABLE
#define TWO_ADKEY_USE_PORT_P04

#define POWER_KEY_LONG_POWER_OFF
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define USE_POWER_KEY_SHORT_SCAN

#define CUSTOMER_DEFINED_ADKEY_RESISTOR
//#define LED_USE_ROUND_LED
#define LED_USE_PLAY_MODE
#define USE_BAT_MANAGEMENT
#define INDEPENDENT_VOLUME_KEY

#define USE_GPIO_DETECT_EARPHONE_PLUGGED

//#define USE_LINE_IN_DETECT_FUNC
//#define AUX_DETECT_USE_P07
#define USB_SD_PLAY_INFO_DIV

#define LINE_IN_PLAY_KEY_PAUSE
#define LINE_IN_PLAY_KEY_NO_PAUSE_ICON_INDICATOR
#define USE_POWER_KEY_FOR_AUX_PLAY
#endif

#ifdef K737_JinYiHeLi_737_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P02_KEY_P04
#define USE_ONLY_POWER_HOLD_CTRL
#define USE_PWR_KEY_LONG_PWR_ON

#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define LED_USE_ROUND_LED
#define LED_USE_PLAY_MODE
#define USE_POWER_KEY_SHORT_SCAN
#define USE_BAT_MANAGEMENT

#define USE_LINE_IN_DETECT_FUNC
#define AUX_DETECT_USE_P07
#define NO_PLAY_STATUS_LED
#define LINE_IN_PLAY_KEY_PAUSE
#define LINE_IN_PLAY_KEY_NO_PAUSE_ICON_INDICATOR
#define USE_POWER_KEY_FOR_AUX_PLAY
#define NEW_SD_DETECT_MOD
#define USB_SD_PLAY_INFO_DIV

#endif

#ifdef K728_SUOERSI_728_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P02_KEY_P04
#define USE_ONLY_POWER_HOLD_CTRL
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define LED_USE_ROUND_LED
#define USE_POWER_KEY_SHORT_SCAN

#define USE_LINE_IN_DETECT_FUNC
#define AUX_DETECT_USE_P07
#define NO_PLAY_STATUS_LED
#define FM_MAX_CHANNAL_50
#define USE_BAT_MANAGEMENT
#endif

#ifdef K745_SUOERSI_745_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P04_KEY_P02
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY	//PLAY POWER 共用一个按键
#define POWER_KEY_ON_WAIT_FOR_3_SEC
#define USE_POWER_KEY_SHORT_SCAN

#define NO_PLAY_STATUS_LED
#define FM_MAX_CHANNAL_50
#define USE_BAT_MANAGEMENT
#define CHARGER_DETECT_INDICATOR
#define CHARGER_FLASH_TYPE_1

#endif

#ifdef K723_LUOMAO_723_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P04_KEY_P02
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_POWER_KEY_TO_SWITCH_MODE
#define USE_USB_AUDIO

#endif

#ifdef K101_TianCheng_101_V001
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define LED_USE_PLAY_MODE
#define MUTE_PORT_USE_P01

#define SEMI_AUTO_SCAN_FREQ
#define VOLUME_DEFUALT 25
#define DEFAULT_GO_TO_AUX
#define TianCheng_Remote
#define LED_REVERSE_VIEW
#define COMMON_CATHODE

#endif

#ifdef K321_Zhuoxing_321_LCD_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif

#ifdef LED_GPIO_DRV
#undef  LED_GPIO_DRV
#endif
#define LCD_GPIO_DRV
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P04_KEY_P02

#endif

#ifdef K321_Zhuoxing_321_LED_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P04_KEY_P02

#endif

#ifdef K716_RiYueTong_716_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define KEY_TONE_ENABEL
#endif


#ifdef K720_YJH_720_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif

#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_POWER_KEY
#define PWR_CTRL_P04_KEY_P02
#define FM_USE_KT0830EG
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY	//PLAY POWER 共用一个按键
#define INDEPENDENT_VOLUME_KEY
#define USE_POWER_KEY_SHORT_SCAN

#endif

#ifdef K719_YJH_719_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED


#endif
#ifdef K693_YJH_693_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define VOLUME_CUSTOMER_DEFINE_16

#endif


#ifdef K668_YJH_815_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define AUX_DETECT_USE_P02
#define VOLUME_CUSTOMER_DEFINE
#define MAX_VOL_SHOW 16
#endif

#ifdef K801_DingChuangXin_801_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED

#define INDEPENDENT_VOLUME_KEY
#define LED_USE_1X888
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE

#endif

#ifdef K812_DingChuangXin_D903_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define AUX_DETECT_USE_P02

#endif


#ifdef K686_ZhengYang_686_V001

#ifdef LED_GPIO_DRV
#undef LED_GPIO_DRV
#endif
#define LCD_GPIO_DRV				//GPIO直接驱动LCD

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P04_KEY_P02
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY	//PLAY POWER 共用一个按键

#define USE_POWER_KEY_SHORT_SCAN

#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define AUX_DETECT_USE_P07
#define NO_PLAY_STATUS_LED

#define NEW_VOLUME_KEY_FEATURE
#define VOLUME_DEFUALT 28

#define USE_RTC_FUNCTION

#define USE_RTC_TIME_ONLY

#endif

#ifdef K565_FXK_565_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define PLAY_STATUS_LED_P04
#define ADKEY_USE_P07_PORT

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define FM_BY_PASS

#define IPONE_INDEPENDENT_MODE
#define IPONE_DOCK_FUNC_ENABLE
#define IPHONE_TX_USE_P06
//#define IPHONE_DETECT_USE_TX
#define IPHONE_CTRL_FAKE
//#define IPHONE_PP_FLASH

#endif
#ifdef K573_AOKAILIN_812_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NEW_SD_DETECT_MOD
//#define JOG_STICK_FUNC

#endif

#ifdef K572_AOKAILIN_811_V001

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NEW_SD_DETECT_MOD

#endif

#ifdef K709_AOKAILIN_709_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NOT_USE_LINE_IN_FUNC

#endif


#ifdef K704_JM_502_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#endif

#ifdef K704_JM_503_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define EARPHONE_DETECT_USE_P02
#define INDEPENDENT_EARPHONE_DETECT_GPIO

#define ROUND_LED_USE_OFFEN

#endif


#ifdef K317_ZhuoXing_317_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define AUX_DETECT_USE_P02

#endif

#ifdef K202_JiaMei_202_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P04_KEY_P02
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY	//PLAY POWER 共用一个按键
//#define POWER_KEY_ON_WAIT_FOR_3_SEC
#define USE_POWER_KEY_SHORT_SCAN
#endif

#ifdef K316_ZhuoXing_316_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P04_KEY_P02
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY	//PLAY POWER 共用一个按键
//#define POWER_KEY_ON_WAIT_FOR_3_SEC
#define USE_POWER_KEY_SHORT_SCAN
#endif

#ifdef K316_MONO_316_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_POWER_KEY
#define PWR_CTRL_P04_KEY_P02
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY	//PLAY POWER 共用一个按键
//#define POWER_KEY_ON_WAIT_FOR_3_SEC
#define USE_POWER_KEY_SHORT_SCAN
#endif


#ifdef K523_DeYun_523_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P17

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define JOG_STICK_FUNC
#define ADKEY_NEXT_ADJST_FREQ

#endif


#ifdef K646_ZhuoXing_308_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能

#define AUX_DETECT_USE_P02
#define USE_BAT_MANAGEMENT

#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define KEY_100_ENABLE
#define USE_USB_AUDIO
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define USB_SD_PLAY_INFO_DIV
#define MUTE_ON_FLASH_WHOLE_SCREEN

#endif




#ifdef K272_JH_272_V001
#define NO_LED_DISPLAY
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define POWE_KEY_PLAY_KEY_IN_ONE_KEY	//PLAY POWER 共用一个按键

#define USE_POWER_KEY
#define PWR_CTRL_P10_KEY_P02
#define USE_USB_AUDIO
#define USE_POWER_KEY_SHORT_SCAN

#endif

#ifdef K532_YJH_532_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define JOG_STICK_FUNC
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define USE_AMP_MODE_SELECT
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
#endif

#ifdef K643_FW_643_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03

#define LED_USE_PLAY_MODE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define AUX_DETECT_USE_P04
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define EARPHONE_DETECT_USE_P02

#endif


#ifdef K637_ZX_306_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define USE_BAT_MANAGEMENT

#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define KEY_100_ENABLE
//#define LED_USE_PLAY_MODE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define AUX_DETECT_USE_P04
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define EARPHONE_DETECT_USE_P02
#define INDEPENDENT_EARPHONE_DETECT_GPIO
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define USB_SD_PLAY_INFO_DIV
#define MUTE_ON_FLASH_WHOLE_SCREEN
//#define SHORT_TIME_RETURN

#endif

#ifdef  K307_ZX_307_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03

#define LED_USE_PLAY_MODE
//#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能

#endif

#ifdef K000_Zhongwei_SP_016_V001

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define NO_LED_DISPLAY
#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能
#define USE_MANUAL_IDLE_FUNC		//手动切换到IDLE
#define VOLUME_DEFUALT 30

#endif


#ifdef K305_ZhuoXin_305_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03

#define LED_USE_PLAY_STATUS
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

//#define ADKEY_PLAY_SHORT_SCAN_FRE
#endif

#ifdef K223_BTL_CP153_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_BAT_MANAGEMENT

#define USE_POWER_KEY_SHORT_SCAN

//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define  GPIO_SWITCH_SELECT_MODE
//#define LED_USE_ROUND_LED
#define NO_PLAY_STATUS_LED
#define PWR_CTRL_P02_KEY_P04
#define USE_POWER_KEY
#define LED_USE_PLAY_MODE
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define POWER_KEY_ON_WAIT_FOR_3_SEC
#define INDEPENDENT_VOLUME_KEY

#define KEEP_SILENT_WHEN_SCAN_CHANNEL
//#define SEMI_AUTO_SCAN_FREQ	//半自动搜台
//#define ADKEY_NEXT_PREV_SHORT_AUTO_SCAN
//#define ADKEY_PLAY_SHORT_ADJ_CH
#endif

#ifdef K619_FXK_619_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
//#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define  GPIO_SWITCH_SELECT_MODE
#define LED_USE_ROUND_LED
#define NO_PLAY_STATUS_LED

#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define SEMI_AUTO_SCAN_FREQ	//半自动搜台
#define NO_VOLUME_LIMITE
#define USE_USB_AUDIO
#define USE_CL6017G_FM
#define ADKEY_NEXT_PREV_SHORT_AUTO_SCAN
#define ADKEY_PLAY_SHORT_ADJ_CH
#endif

#ifdef K610_YJH_803_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define  GPIO_SWITCH_SELECT_MODE

#endif

#ifdef K015_JLH_2946_V001
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能
#define NO_ADKEY_FUNC
#define LED_USE_PLAY_MODE
#define MATRIX_KEY_ENABLE
#define PLAY_STATUS_LED_P04
#define VOLUME_DEFUALT 30
#define MAX_VOL_SHOW 30
#define USE_VOL_LIMTATION
#define MUTE_PORT_USE_P01
#endif

#ifdef K170_HAO_SHENG_170_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define INDEPENDENT_VOLUME_KEY
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_RTC_FUNCTION

#endif

#ifdef K010_QDX_PM21_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define JOG_STICK_FUNC
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_AMP_MODE_SELECT

#endif

#ifdef K010_YJH_931_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define JOG_STICK_FUNC
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_AMP_MODE_SELECT

#endif

#ifdef K170_QDX_PM_A01_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define INDEPENDENT_VOLUME_KEY
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define LINE_IN_PLAY_KEY_PAUSE

#define USE_USB_AUDIO

#endif

#ifdef K170_QDX_170_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define INDEPENDENT_VOLUME_KEY
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define LINE_IN_PLAY_KEY_PAUSE

#define USE_USB_AUDIO

#endif

#ifdef K170_YDS_170_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define INDEPENDENT_VOLUME_KEY
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_USB_AUDIO

#endif

#ifdef K170_LanQin_170_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define INDEPENDENT_VOLUME_KEY
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_USB_AUDIO

#endif

#ifdef K170_YJH_170_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define INDEPENDENT_VOLUME_KEY
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_USB_AUDIO

#endif

#ifdef K170_ZK_170_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道


//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT

#define USE_USB_AUDIO

#endif

#ifdef K170_ZHUOXIN_UK3_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道


#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT

#define USE_USB_AUDIO

#endif

#ifdef K171_LT_171_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define LINE_IN_PLAY_KEY_PAUSE
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT

#endif

#ifdef K171_LanQin_012_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
//#define LED_USE_PLAY_MODE

#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define LINE_IN_PLAY_KEY_PAUSE
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
//#define VOLUME_CUSTOMER_DEFINE_28
#define VOLUME_DEFUALT 30
#define NO_VOLUME_LIMITE

#endif

#ifdef K171_ZX_SW012_ET1013FM_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define LED_USE_PLAY_MODE

#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define LINE_IN_PLAY_KEY_PAUSE
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
//#define VOLUME_CUSTOMER_DEFINE_28
#define USE_BAT_MANAGEMENT
#define USB_SD_PLAY_INFO_DIV
#endif


#ifdef K171_SW_012_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define LED_USE_PLAY_MODE

#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define LINE_IN_PLAY_KEY_PAUSE
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT
#define VOLUME_CUSTOMER_DEFINE_28

#endif

#ifdef K171_YJH_171_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define LINE_IN_PLAY_KEY_PAUSE
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT

#endif


#if 0//def K208_ZY_KL208_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define LINE_IN_PLAY_KEY_PAUSE
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_RTC_FUNCTION
#define USE_RTC_TIME_ONLY
#define USE_RTC_ALARM_FUNCTION

#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_HOLD_AUTO_SCAN

#endif

#ifdef K000_RS_228U_V001
#define NO_LED_DISPLAY
#define ADKEY_USE_P07_PORT
#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能
#define VOLUME_DEFUALT 27

#endif

#ifdef K189_JM_201_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define LINE_IN_PLAY_KEY_PAUSE
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_EQ_TABLE_CUSTOM
#endif

#ifdef K063_YJH_063_V001
#define NO_LED_DISPLAY

#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P00
//#define LED_USE_ROUND_LED
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define SEMI_AUTO_SCAN_FREQ
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define USE_POWER_KEY
#define PWR_CTRL_P10_KEY_P04
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define INDEPENDENT_VOLUME_KEY
#define USE_POWER_KEY_SHORT_SCAN
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define FM_USE_KT0830EG
#define USE_GPIO_DETECT_EARPHONE_PLUGGED

#endif

#ifdef K020_WEIQI_V001
#define NO_LED_DISPLAY

#endif


#ifdef  K186_LM_186_V001
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
//#define LED_USE_ROUND_LED

#define USE_POWER_KEY
#define PWR_CTRL_P02_KEY_P04
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define INDEPENDENT_VOLUME_KEY
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define EQ_MODE_DEFUALT_ROCK
#define USE_USB_AUDIO

#endif

#ifdef  K186_ZHHB_S30_V001
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
//#define LED_USE_ROUND_LED

#define USE_POWER_KEY
#define PWR_CTRL_P02_KEY_P04
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define INDEPENDENT_VOLUME_KEY
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define EQ_MODE_DEFUALT_ROCK
#endif

#ifdef K181_YJH_181_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define LED_USE_1X888
#define NOT_USE_LINE_IN_FUNC	//无LINE 功能

#define ADKEY_PLAY_SHORT_SCAN_FRE

//#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define IR_NEXT_PREV_HOLD_AUTO_SCAN

#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define SEMI_AUTO_SCAN_FREQ
#define KEY_100_ENABLE

#endif

#ifdef K181_LY_181_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define LED_USE_1X888
#define NOT_USE_LINE_IN_FUNC	//无LINE 功能

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define IR_NEXT_PREV_HOLD_AUTO_SCAN

#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define SEMI_AUTO_SCAN_FREQ
#endif

#ifdef K180_LY_180_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define LED_USE_1X888
#define NOT_USE_LINE_IN_FUNC	//无LINE 功能

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define SEMI_AUTO_SCAN_FREQ
#endif


#ifdef K077_BoDa_V001
#define NO_LED_DISPLAY
//#define FM_TRANSMITTER
#define IIC_GPIO_USE_P00_P01
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#endif

#ifdef K003_V001
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define	MUTE_PORT_USE_P01
#endif

#ifdef K010_931_V001
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define	MUTE_PORT_USE_P01
#endif

#ifdef SW_V001
#define NO_LED_DISPLAY
#undef ADKEY_PLAY_SHORT_SCAN_FRE
#define	MUTE_PORT_USE_P01
#define USE_VOL_LIMTATION
#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 28
#endif
#define LED_RUN_FAST_WHEN_PLAY_MODE_CHANGE
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define VOLUME_DEFUALT 27
#endif

#ifdef SW_V002_747
#define LED_USE_PLAY_MODE

#undef ADKEY_PLAY_SHORT_SCAN_FRE
#define ADKEY_NEXT_ADJST_FREQ
#define MUTE_PORT_USE_P01
#define SEMI_AUTO_SCAN_FREQ
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define KEY_100_ENABLE
#define USE_VOL_LIMTATION
#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 50
#endif
#define LED_RUN_FAST_WHEN_PLAY_MODE_CHANGE
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define VOLUME_CUSTOMER_DEFINE

#endif

#ifdef SW_V002
#define LED_USE_PLAY_MODE

#undef ADKEY_PLAY_SHORT_SCAN_FRE
#define ADKEY_NEXT_ADJST_FREQ
#define MUTE_PORT_USE_P01
#define SEMI_AUTO_SCAN_FREQ
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define KEY_100_ENABLE
#define USE_VOL_LIMTATION
#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 28
#endif
#define LED_RUN_FAST_WHEN_PLAY_MODE_CHANGE
#define CUSTOMER_DEFINED_ADKEY_RESISTOR

#endif

#ifdef K002_SW_002_Zhuoxin_V001
//#define LED_USE_PLAY_MODE
//#define SW_V002
#undef ADKEY_PLAY_SHORT_SCAN_FRE
#define ADKEY_NEXT_ADJST_FREQ
#define MUTE_PORT_USE_P01
#define SEMI_AUTO_SCAN_FREQ
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define KEY_100_ENABLE
#define USE_VOL_LIMTATION
#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 28
#endif
#define LED_RUN_FAST_WHEN_PLAY_MODE_CHANGE
#define CUSTOMER_DEFINED_ADKEY_RESISTOR

#endif

#ifdef K003_V001
#undef SW_V001
#undef SW_V002
#endif
#ifdef SW_V007
#undef _SHORT_PLAY_SCAN_FRE_
#define   MUTE_PORT_USE_P01
#define USE_VOL_LIMTATION
#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif
#endif

#ifdef SW_V007_502K
#undef _SHORT_PLAY_SCAN_FRE_
#define   MUTE_PORT_USE_P01
#define   NOT_USE_LINE_IN_FUNC
#define USE_VOL_LIMTATION
#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif
#endif

/*****************按 主板编号定义宏******************/
#ifdef K005_987_V001
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define MUTE_PORT_USE_P01
#define NO_LED_DISPLAY
#endif

#ifdef K005_987_FOR_JLH_V001
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define MUTE_PORT_USE_P01
#define DECODE_STOP_MODE_ENABLE
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
//#define NO_LED_DISPLAY
#endif

#ifdef K009_968_SW006_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_VOL_LIMTATION
#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif
#endif

#ifdef K009_968_SW006_ZHUOXIN_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_VOL_LIMTATION
#define VOLUME_CUSTOMER_DEFINE_1
#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 50
#endif
#endif

#ifdef K021_XXX_V001
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define MUTE_PORT_USE_P01
#define NO_LED_DISPLAY
#endif

#ifdef K023_971_V001
#define MUTE_PORT_USE_P01
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define INDEPENDENT_VOLUME_KEY
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_VOL_LIMTATION
#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif

#define USE_RTC_FUNCTION
#define USE_RTC_ALARM_FUNCTION

#endif

#ifdef K013_980_V001
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define MUTE_PORT_USE_P01
#define NO_LED_DISPLAY
#endif


#ifdef K015_983_1_SW005_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define IR_USER_CODE_0x7F80
//#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define KEY_100_ENABLE

#endif

#ifdef K015_983_JLH_VOL50_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_USB_AUDIO

#define IR_NEXT_PREV_SHORT_ADJ_CH
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define SEMI_AUTO_SCAN_FREQ
#define NEW_CUSTOMED_VOLUME_DIVIDED_METHOD

#endif
#ifdef K015_983_JLH_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_USB_AUDIO

#define IR_NEXT_PREV_SHORT_ADJ_CH
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define SEMI_AUTO_SCAN_FREQ

#endif


#ifdef K015_983_SW005_AMFM_V001

#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
#define RADIO_AM_WM_ENABLE
#define FM_USE_KT0913
//#define ADKEY_PLAY_SHORT_SCAN_FRE

#endif

#ifdef K015_983_SW005_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#endif

#ifdef K015_983_SW005_ZX_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USB_SD_PLAY_INFO_DIV
#define VOLUME_DEFUALT 30
#endif

#ifdef K015_983_SW005_V8
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define EARPHONE_DETECT_USE_P04
#endif

#ifdef K015_983_SW005_ZhuoXin_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define VOLUME_CUSTOMER_DEFINE_1
#define MAX_VOL_SHOW 50
#define VOLUME_DEFUALT 50
#define USB_SD_PLAY_INFO_DIV
#endif

#ifdef K015_983_SW005_ZhuoXin_FB001_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define VOLUME_CUSTOMER_DEFINE_1
//#define MAX_VOL_SHOW 50
//#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define SEMI_AUTO_SCAN_FREQ
//#define IR_NEXT_PREV_HOLD_AUTO_SCAN
//#define IR_NEXT_PREV_SHORT_ADJ_CH
#define USB_SD_PLAY_INFO_DIV
//#define USE_BAT_MANAGEMENT
//#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能
#define USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#define VOLUME_DEFUALT 27
#define IR_USER_CODE_0xBF00
#define KEY_10_ENABLE
//#define INDEPENDENT_VOLUME_KEY
#define IR_NEXT_PREV_SHORT_ADJ_CH

#endif

#ifdef K015_983_SW005_ZhuoXin_KL001_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define VOLUME_CUSTOMER_DEFINE_1
//#define MAX_VOL_SHOW 50
#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define SEMI_AUTO_SCAN_FREQ
//#define IR_NEXT_PREV_HOLD_AUTO_SCAN
//#define IR_NEXT_PREV_SHORT_ADJ_CH
#define USB_SD_PLAY_INFO_DIV
//#define USE_BAT_MANAGEMENT
#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能
#define USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#define VOLUME_DEFUALT 27

#endif
#ifdef K015_983_SW005_ZhuoXin_KL002_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define VOLUME_CUSTOMER_DEFINE_1
//#define MAX_VOL_SHOW 50
#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define SEMI_AUTO_SCAN_FREQ
//#define IR_NEXT_PREV_HOLD_AUTO_SCAN
//#define IR_NEXT_PREV_SHORT_ADJ_CH
#define USB_SD_PLAY_INFO_DIV
//#define USE_BAT_MANAGEMENT
//#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能
#define USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#define VOLUME_DEFUALT 27

#endif

#ifdef K015_983_SW005_ZhuoXin_JR001_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define VOLUME_CUSTOMER_DEFINE_1
#define MAX_VOL_SHOW 50
#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define SEMI_AUTO_SCAN_FREQ
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define USB_SD_PLAY_INFO_DIV
#define USE_BAT_MANAGEMENT
#endif

#ifdef Kxxx_931_V001
#define LED_USE_PLAY_STATUS
#define MUTE_PORT_USE_P01
#define ADKEY_PLAY_SHORT_SCAN_FRE
#endif

#ifdef K011_011_V001
#define MUTE_PORT_USE_P01
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define INDEPENDENT_VOLUME_KEY
#define USE_VOL_LIMTATION
#define USE_USB_AUDIO

#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif
#define LED_USE_1X888
#endif

#ifdef K080_YJH_985_V001
#define MUTE_PORT_USE_P01
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define INDEPENDENT_VOLUME_KEY
#define USE_VOL_LIMTATION
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define NO_PLAY_STATUS_LED
#define _KEY_TONE_ENABEL_

#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif
#define LED_USE_1X888
#endif

#ifdef K081_YJH_973_V001
#define MUTE_PORT_USE_P01
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define INDEPENDENT_VOLUME_KEY
#define USE_VOL_LIMTATION
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define NO_PLAY_STATUS_LED
#define _KEY_TONE_ENABEL_

#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif
#define LED_USE_1X888
#endif

#ifdef K025_XXX_V001
#define MUTE_PORT_USE_P01
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define INDEPENDENT_VOLUME_KEY
#define USE_VOL_LIMTATION

#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif
#define LED_USE_1X888
#endif


#ifdef K037_XXX_V001
#define MUTE_PORT_USE_P01
#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define INDEPENDENT_VOLUME_KEY
#define USE_VOL_LIMTATION
#define DECODE_STOP_MODE_ENABLE

#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif
#define LED_USE_1X888
#endif


#ifdef K026_XXX_V001
#define MUTE_PORT_USE_P01
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define NO_LED_DISPLAY
#endif

#ifdef K031_XXX_V001
#define MUTE_PORT_USE_P01
#define NO_LED_DISPLAY
#define NOT_USE_LINE_IN_FUNC
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#endif

#ifdef K085_YJH_085_V001
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define MUTE_PORT_USE_P01
#define NOT_USE_LINE_IN_FUNC
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define NO_LED_DISPLAY
#endif

#ifdef K116_FXK_V001
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#define NO_PLAY_STATUS_LED
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define SEMI_AUTO_SCAN_FREQ	//半自动搜台
#define NO_VOLUME_LIMITE
#define USE_USB_AUDIO
#define USE_CL6017G_FM
#define ADKEY_NEXT_PREV_SHORT_AUTO_SCAN
#define ADKEY_PLAY_SHORT_ADJ_CH
#define USE_SYS_MODE_RECOVER
#endif

#ifdef K128_YJH_128_V001
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define INDEPENDENT_VOLUME_KEY
#define USE_VOL_LIMTATION
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#ifdef USE_VOL_LIMTATION
#define MAX_VOL_SHOW 30
#endif
#define LED_USE_1X888
#define  GPIO_SWITCH_SELECT_MODE

#endif

#ifdef K133_QDX_133_V001
#define LED_GPIO_DRV		//GPIO直接驱动LED
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define LED_USE_ROUND_LED
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#endif


#ifdef K591_JiaLe_591_V001

#define LED_GPIO_DRV		//GPIO直接驱动LED
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define LED_USE_ROUND_LED
#define LED_USE_PLAY_MODE

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define PLAY_MODE_REPEAT_ALL
#define EQ_MODE_DEFUALT_ROCK
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define INDEPENDENT_VOLUME_KEY

#define CHARGER_DETECT_INDICATOR
#define USE_BAT_MANAGEMENT

#endif

#ifdef K162_QDX_162_V001
#define LED_GPIO_DRV		//GPIO直接驱动LED
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define LED_USE_ROUND_LED
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define PLAY_MODE_REPEAT_ALL
#define EQ_MODE_DEFUALT_ROCK
#define USE_GPIO_DETECT_EARPHONE_PLUGGED

#endif

#ifdef K105_SWD_2901_V001
#ifdef LED_GPIO_DRV
#undef LED_GPIO_DRV
#endif
#define USE_LCD_DRV_HT1621
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define LINE_IN_PLAY_KEY_PAUSE
#define IR_USER_CODE_0x7F80
#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_PLAY_KEY_SCAN_FREQ_DISABLE
#define SEMI_AUTO_SCAN_FREQ

#endif

#ifdef K105_SWD_2901A_V001
#ifdef LED_GPIO_DRV
#undef LED_GPIO_DRV
#endif
#define USE_LCD_DRV_HT1621
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define LINE_IN_PLAY_KEY_PAUSE
#define IR_USER_CODE_0x7F80
#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_PLAY_KEY_SCAN_FREQ_DISABLE
#define SEMI_AUTO_SCAN_FREQ
#define SWD_NEW_LCD_BOARD
#endif

#ifdef K122_SWD_122_V001
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define LED_USE_1X888
#define USE_CL6017G_FM
#define NOT_USE_LINE_IN_FUNC	//无LINE 功能
#define IR_USER_CODE_0x7F80
#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_PLAY_KEY_SCAN_FREQ_DISABLE
#define USE_QN8035_FM

#endif

#ifdef K196_MN_196_V001

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef  MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P03
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define LED_USE_PLAY_STATUS

#define IR_REMOTER_WITH_POWER_MUTE_PRINT
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_PLAY_KEY_SCAN_FREQ_DISABLE
//#define INDEPENDENT_VOLUME_KEY

#endif

/************************************************************
*	28PIN BOARD DEFINE
************************************************************/
#ifdef  K088_JLH_23108_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#undef USE_BK1080_FM
//#define NO_LED_DISPLAY
#define USE_POWER_KEY
#define NOT_USE_LINE_IN_FUNC	//无LINE 功能
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY	//PLAY POWER 共用一个按键
#define VOLUME_DEFUALT 27
#define USE_RTC_RAM_FUNC
#ifdef MUTE_CTRL_LEVEL_NORMAL
#undef MUTE_CTRL_LEVEL_NORMAL
#endif
#define  POWER_KEY_ON_WAIT_FOR_3_SEC
#define  SYS_GO_IN_IDLE_IN_30_SEC

#ifdef MUTE_CTRL_LEVEL_NORMAL
#undef MUTE_CTRL_LEVEL_NORMAL
#endif
#endif

#ifdef  K113_SW_113_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
//#define NO_LED_DISPLAY
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define PLAY_STATUS_LED_P27
#define VOLUME_DEFUALT 27
#define NOT_USE_LINE_IN_FUNC
#define USE_MANUAL_IDLE_FUNC		//手动切换到IDLE

#endif

#ifdef  K115_SW_115_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
//#define NO_LED_DISPLAY
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define PLAY_STATUS_LED_P27
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT	//打开此宏来启动LINE IN 检测功能
#define VOLUME_DEFUALT 27
#define FM_BY_PASS

#endif

#ifdef  K163_ZHHB_163_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
//#define NO_LED_DISPLAY
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define PLAY_STATUS_LED_P27
#define LINE_IN_DETECT_USE_P02
#define FM_BY_PASS

#endif


#ifdef  K169_KR_169_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
//#define NO_LED_DISPLAY
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define PLAY_STATUS_LED_P27
#define NOT_USE_LINE_IN_FUNC
#undef USE_BK1080_FM

#endif

#ifdef  K000_DT_078_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P01_P02

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P00

#define PLAY_STATUS_LED_P27
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define SYS_CRYSTAL_USE_24M
#define FM_BY_PASS

#endif

#ifdef  K188_YJH_188_V002
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
//#define NO_LED_DISPLAY
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define PLAY_STATUS_LED_P27
//#define LINE_IN_DETECT_USE_P02
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
//#define INDEPENDENT_VOLUME_KEY

#define VOLUME_DEFUALT 16
#define FM_BY_PASS
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define _KEY_TONE_ENABEL_

#endif

#ifdef  K188_YJH_188_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
//#define NO_LED_DISPLAY
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define PLAY_STATUS_LED_P27
//#define LINE_IN_DETECT_USE_P02
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define INDEPENDENT_VOLUME_KEY

#define VOLUME_DEFUALT 16
#define FM_BY_PASS
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define _KEY_TONE_ENABEL_

#define TURN_ON_PLAY_BREAK_POINT_MEM
#endif


#ifdef  K139_YDS_xxx_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define DECODE_STOP_MODE_ENABLE
#define PLAY_LONG_PRESS_STOP
#define INDEPENDENT_VOLUME_KEY
#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
#define FM_BY_PASS
#define LINE_IN_DETECT_USE_P02
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#endif

#ifdef  K139_FuWei_xxx_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define INDEPENDENT_VOLUME_KEY
#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
#define FM_BY_PASS
//#define LINE_IN_DETECT_USE_P02
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#endif

#ifdef  K139_JLH_xxx_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
#define FM_BY_PASS
#define LINE_IN_DETECT_USE_P02
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#endif

#ifdef K109_SW001D_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#define VOLUME_DEFUALT 	27
#define NO_LED_DISPLAY
//#define ADC_DETECT_LINE_IN
#define FM_BY_PASS
#undef ADKEY_PLAY_SHORT_SCAN_FRE
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define LED_RUN_FAST_WHEN_PLAY_MODE_CHANGE

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#endif


#ifdef K198_SW198_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

//#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
#define FM_BY_PASS
#define NOT_USE_LINE_IN_FUNC

#endif

#ifdef K801_TC_801_V002
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#define TianCheng_Remote
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P27
#define USE_FM_GPIO
#define MUTE_GPIO_FM_GPIO_COMPATIBALE

#define VOLUME_DEFUALT 27
//#define PLAY_STATUS_LED_P02
#define PALY_MODE_USE_REP_ONE_ALL
#define DEFAULT_GO_TO_AUX


#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define CUSTOMER_DEFINED_ADKEY_RESISTOR

#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_SHORT_ADJ_CH
#endif

#ifdef K801_TC_801_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#define TianCheng_Remote
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P27
#define USE_FM_GPIO
#define MUTE_GPIO_FM_GPIO_COMPATIBALE

#define VOLUME_DEFUALT 27
//#define PLAY_STATUS_LED_P02
#define PALY_MODE_USE_REP_ONE_ALL


#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define CUSTOMER_DEFINED_ADKEY_RESISTOR

#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_SHORT_ADJ_CH
#endif

#ifdef K608_TC_608_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#define TianCheng_Remote

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
#define FM_BY_PASS
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define CUSTOMER_DEFINED_ADKEY_RESISTOR

#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_SHORT_ADJ_CH
#endif

#ifdef K608_TC_608_V002
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#define TianCheng_Remote

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
#define FM_BY_PASS
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define DEFAULT_GO_TO_AUX

#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define IR_NEXT_PREV_SHORT_ADJ_CH
#endif

#ifdef K987_YJH_987_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
#define FM_BY_PASS
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define INDEPENDENT_EARPHONE_DETECT_GPIO
//#define SEMI_AUTO_SCAN_FREQ
//#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#endif

#ifdef K172_AJE_172_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define USE_QN8035_FM

#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
#define FM_BY_PASS
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED

//#define SEMI_AUTO_SCAN_FREQ
//#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#endif

#ifdef K200_KY_021_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
//#define FM_BY_PASS
//#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define FM_USE_KT0830EG
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define USE_USB_AUDIO
#define EQ_MODE_DEFUALT_ROCK
#define USE_RTC_RAM_FUNC
//#define SEMI_AUTO_SCAN_FREQ
//#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#endif

#ifdef K209_WS_GKD209_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define VOLUME_DEFUALT 27
#define PLAY_STATUS_LED_P27
#define FM_BY_PASS
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define LINE_IN_DETECT_USE_P02
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能

#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define ADKEY_PLAY_SHORT_SCAN_FRE

//#define SEMI_AUTO_SCAN_FREQ
//#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN
#endif


#ifdef K202_WS_01_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define VOLUME_DEFUALT 27
#define FM_BY_PASS
#define LED_MODE_INDICATOR_ENABLE
#define ADKEY_PLAY_SHORT_SCAN_FRE

#endif

#ifdef K609_KL_609_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define VOLUME_DEFUALT 27
#define FM_BY_PASS
#define LED_MODE_INDICATOR_ENABLE
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define LED_DRVER_USE_SM1628	// SM 1628 驱动IC

#endif

#ifdef K505_CJB_505_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27
//#define LINE_IN_DETECT_USE_P02
#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define INDEPENDENT_VOLUME_KEY

#endif


#ifdef K507_YJH_507_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define USE_POWER_KEY
#define PWR_CTRL_P24_KEY_P25
#define USE_GPIO_DETECT_EARPHONE_PLUGGED

#endif

#ifdef K617_LHGC_617_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#ifdef LED_CTRL_LEVEL_NORMAL
#undef LED_CTRL_LEVEL_NORMAL
#endif

#define VOLUME_DEFUALT	   24
#define PLAY_STATUS_LED_P02
#define PALY_MODE_USE_REP_ONE_ALL
#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能

#endif


#ifdef K627_LHGC_627_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#ifdef LED_CTRL_LEVEL_NORMAL
#undef LED_CTRL_LEVEL_NORMAL
#endif

#define VOLUME_DEFUALT	   24
#define PLAY_STATUS_LED_P02
#define PALY_MODE_USE_REP_ONE_ALL
#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能
#define MATRIX_KEY_ENABLE

#endif

#ifdef K639_YJH_639_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG

#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能
#define FM_TRANSMITTER

#endif

#ifdef  K519_YJH_808_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
//#define NO_LED_DISPLAY
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define PLAY_STATUS_LED_P27
//#define LINE_IN_DETECT_USE_P02
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define INDEPENDENT_VOLUME_KEY

#define VOLUME_DEFUALT 30
#define FM_BY_PASS
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define _KEY_TONE_ENABEL_

#endif

#ifdef  K519_YJH_808_V002

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
//#define NO_LED_DISPLAY
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01
#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define PLAY_STATUS_LED_P27
//#define LINE_IN_DETECT_USE_P02
//#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define INDEPENDENT_VOLUME_KEY

#define VOLUME_DEFUALT 30
#define FM_BY_PASS
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define _KEY_TONE_ENABEL_
#define USE_USB_AUDIO
#endif

#ifdef K232_GKD_232_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27
#define LINE_IN_DETECT_USE_P02
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define INDEPENDENT_VOLUME_KEY

#endif

#ifdef K525_DeYun_525_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define INDEPENDENT_VOLUME_KEY
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#endif

#ifdef K667_YJH_667_V001


#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define INDEPENDENT_VOLUME_KEY
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define LINE_IN_DETECT_USE_P02
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#endif

#ifdef K071_ZhengYang_ZY071_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P01_P02

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P01
#define PLAY_STATUS_LED_SHARE_WITH_IIC_SCL

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define VOLUME_DEFUALT 28
#define USE_USB_AUDIO
#define USE_LONG_PLAY_MODE_KEY_TO_SWITCH_MODE
#define NEW_SD_DETECT_MOD
#endif


#ifdef K302_ZhengYang_ZY302_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P01_P02

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define KEY_100_ENABLE

#define PLAY_STATUS_LED_P27

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define IR_REMOTER_WITH_POWER_MUTE_PRINT

#define FM_BY_PASS
//#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define INDEPENDENT_VOLUME_KEY
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define VOLUME_DEFUALT 28
#define DEFAULT_GO_TO_AUX
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define DECODE_STOP_MODE_ENABLE
#define USE_QN8035_FM
#define KEY_PRESS_LED_INDICATOR
#define IR_NEXT_PREV_SHORT_ADJ_CH

#define USE_TWO_IR_REMOTE

#endif


#ifdef K676_FXK_676_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define NOT_USE_LINE_IN_FUNC	//打开此宏来关闭AUX功能

#endif

#ifdef K555_FXK_555_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#endif


#ifdef K711_JM_YX450_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE

#endif
#ifdef K703_JM_YX006_V001


#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE

#endif

#ifdef K705_YJH_705_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED

#endif

#ifdef K679_YJH_679_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE

#endif

#ifdef K560_YJH_560_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define USE_RTC_RAM_FUNC

#endif


#ifdef K710_AoKaiLin_710_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_USE_P02

#endif

#ifdef K811_DingChuangXin_811_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_USE_P02

#endif

#if defined(K692_SES_692_V001)||defined(K695_SES_695_V001)

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27
#define VOLUME_DEFUALT 	28

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define USE_RTC_RAM_FUNC

#endif
 
 #ifdef K120_SW_015_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define PLAY_STATUS_LED_P27
#define VOLUME_DEFUALT 	27
#define NO_LED_DISPLAY
//#define ADC_DETECT_LINE_IN
#define FM_BY_PASS
#undef ADKEY_PLAY_SHORT_SCAN_FRE
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define LED_RUN_FAST_WHEN_PLAY_MODE_CHANGE
#endif

#ifdef K120_YJH_120_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27
#define USB_DAC_CHANNEL_DELAY_OPEN

#define USE_RTC_RAM_FUNC

#define VOLUME_DEFUALT 30
//#define VOLUME_DEFUALT 28

#define NO_VOLUME_LIMITE
#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define IR_PLAY_KEY_SCAN_FREQ_DISABLE
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define SEMI_AUTO_SCAN_FREQ
#define IR_NEXT_PREV_HOLD_AUTO_SCAN
#define NEW_SD_DETECT_MOD
#define NEXT_PREV_HOLD_USE_VOL_TUNE
#define CUSTOM_KEY_FEATURE_USE
#endif


#ifdef K562_QDX_562_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define USE_RTC_RAM_FUNC

#endif

#ifdef K800_MingYang_800_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_DUMP

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
//#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define USE_POWER_KEY
#define USE_ONLY_POWER_HOLD_CTRL
#define USE_LONG_MODE_FOR_CUSTOM_FUNC
#define VOLUME_DEFUALT 28
#define USE_USB_AUDIO
#define CUSTOMER_DEFINED_ADKEY_RESISTOR

#endif

#ifdef K319_ZhuoXing_319_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define USE_POWER_KEY
#define PWR_CTRL_P25_KEY_P24

#endif


#ifdef K320_ZhuoXing_320_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27

#define FM_BY_PASS
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define USE_LINE_IN_DETECT_FUNC	//打开此宏来启动LINE IN 检测功能
#define LINE_IN_DETECT_USE_P02

#endif

#ifdef K722_YJH_722_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define USE_MUTE_LED_INDICATOR
#define PLAY_STATUS_LED_P27
#define TWO_PLAY_LED_IN_USE

#define FM_BY_PASS
//#define ADKEY_PLAY_SHORT_SCAN_FRE
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define IR_USER_CODE_0x7F80

#define IR_PLAY_KEY_LONG_SCAN_FREQ
#define IR_NEXT_PREV_SHORT_ADJ_CH
#define SEMI_AUTO_SCAN_FREQ
#define IR_PLAY_KEY_SCAN_FREQ_DISABLE
#define LINE_IN_PLAY_KEY_PAUSE
#define AUX_PAUSE_LED_INDICATOR
#define DEFAULT_GO_TO_AUX
#define FM_PLAY_KEY_PAUSE
#define FM_PAUSE_LED_INDICATOR
#define VOLUME_DEFUALT 28

#endif


#ifdef K806_LiHaoDe_806_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P02
#define VOLUME_DEFUALT 28

#define USE_RTC_RAM_FUNC
#define NOT_USE_LINE_IN_FUNC

#endif


#ifdef K727_LiHaoDe_727_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

#define PLAY_STATUS_LED_P27
#define VOLUME_DEFUALT 28

#define USE_RTC_RAM_FUNC
#define NOT_USE_LINE_IN_FUNC
#define _KEY_TONE_ENABEL_
#endif

#ifdef K202_WEISI_KL202_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

//#define NO_PLAY_STATUS_LED
#define VOLUME_DEFUALT 28

#define FM_BY_PASS

#define NOT_USE_LINE_IN_FUNC
#define NEW_CUSTOMIZED_LED_METHOD

#endif


#ifdef K583_ZX_583_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define FM_BY_PASS

#define PLAY_STATUS_LED_P27
#define PLAY_STATUS_LED_SHARE_WITH_IIC_SCL
#define TWO_PLAY_LED_IN_USE
#define TWO_PLAY_LED_USE_PORT_P00
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define VOLUME_DEFUALT 28

#define USE_RTC_RAM_FUNC
#define USE_POWER_KEY
#define USE_ONLY_POWER_HOLD_CTRL
#define PWR_CTRL_P02
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY

#define USE_POWER_KEY_SHORT_SCAN
#endif


#ifdef K586_LHD_LT30_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26
//#define NO_PLAY_STATUS_LED
#define PLAY_STATUS_LED_P27
#define VOLUME_DEFUALT 28

//#define FM_BY_PASS
#define _KEY_TONE_ENABEL_
#define NOT_USE_LINE_IN_FUNC
//#define LED_MODE_INDICATOR_ENABLE

#endif

#ifdef K738_LHD_LTB1_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_DUMP
//#define NO_PLAY_STATUS_LED
#define PLAY_STATUS_LED_P02
#define VOLUME_DEFUALT 	28
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define KEY_TONE_ENABEL

//#define DEFAULT_GO_TO_IDLE	//????????????????????????

#define INDEPENDENT_VOLUME_KEY
//#define NOT_USE_LINE_IN_FUNC
//#define LED_MODE_INDICATOR_ENABLE
#endif

#ifdef K740_LHD_916_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

//#define NO_PLAY_STATUS_LED
#define PLAY_STATUS_LED_P27

#define VOLUME_DEFUALT 	28
//#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define ADKEY_PLAY_SHORT_SCAN_FRE
//#define FM_BY_PASS
//#define NOT_USE_LINE_IN_FUNC
#define _KEY_TONE_ENABEL_
#define INDEPENDENT_VOLUME_KEY

//#define LED_MODE_INDICATOR_ENABLE
#endif

#ifdef K000_XingChuang_X816_V001
#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P01_P02

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P00

//#define NO_PLAY_STATUS_LED
#define PLAY_STATUS_LED_P01
#define PLAY_STATUS_LED_SHARE_WITH_IIC_SCL
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define VOLUME_DEFUALT 28
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define USE_IR_VPP_PORT_FOR_DETECTION
#define ADKEY_PLAY_SHORT_SCAN_FRE
#endif

#ifdef K736_TaiYangSheng_736_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif

//#define NO_PLAY_STATUS_LED
#define PLAY_STATUS_LED_P27
#define VOLUME_DEFUALT 	28
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define FM_BY_PASS
//#define NOT_USE_LINE_IN_FUNC
//#define LED_MODE_INDICATOR_ENABLE
#endif


#ifdef K589_JYHL_589_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define FM_BY_PASS
#define PLAY_STATUS_LED_P27

#define INDEPENDENT_VOLUME_KEY

#define VOLUME_DEFUALT 28
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define USE_POWER_KEY
#define USE_ONLY_POWER_HOLD_CTRL
#define PWR_CTRL_P02
#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE
#define LINE_IN_PLAY_KEY_PAUSE
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define USE_PWR_KEY_LONG_PWR_ON

#define SEMI_AUTO_SCAN_FREQ
#define ADKEY_NEXT_PREV_HOLD_AUTO_SCAN


#endif


#ifdef K746_JIALE_746_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

#define PLAY_STATUS_LED_P27
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define FM_BY_PASS

#define VOLUME_DEFUALT 28

#define ADKEY_PLAY_SHORT_SCAN_FRE

#endif

#ifdef K755_AnJieEr_755_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P27
#define FM_BY_PASS
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define PLAY_STATUS_LED_P02

#define VOLUME_DEFUALT 28
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define USE_POWER_KEY
#define USE_ONLY_POWER_HOLD_CTRL
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define INDEPENDENT_VOLUME_KEY

#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define USE_POWER_KEY_SHORT_SCAN
#define NEXT_PREV_HOLD_DO_NOTHING

#define USE_PWR_KEY_LONG_PWR_ON

#define FM_USE_KT0830EG
#endif

#ifdef K783_JinYeHeLi_783_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P27
#define FM_BY_PASS
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define PLAY_STATUS_LED_P02

#define VOLUME_DEFUALT 28
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define USE_POWER_KEY
#define USE_ONLY_POWER_HOLD_CTRL
#define ADKEY_PLAY_SHORT_SCAN_FRE

#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define USE_POWER_KEY_SHORT_SCAN
#define NEXT_PREV_HOLD_DO_NOTHING

#define USE_PWR_KEY_LONG_PWR_ON

#define FM_USE_KT0830EG
#endif

#ifdef K755_JinYeHeLi_755_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P27
#define FM_BY_PASS
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道

#define PLAY_STATUS_LED_P02

#define VOLUME_DEFUALT 28
#define CUSTOMER_DEFINED_ADKEY_RESISTOR
#define USE_POWER_KEY
#define USE_ONLY_POWER_HOLD_CTRL
#define ADKEY_PLAY_SHORT_SCAN_FRE
#define INDEPENDENT_VOLUME_KEY

#define POWE_KEY_PLAY_KEY_IN_ONE_KEY
#define USE_POWER_KEY_SHORT_SCAN
#define NEXT_PREV_HOLD_DO_NOTHING

#define USE_PWR_KEY_LONG_PWR_ON

#define FM_USE_KT0830EG
#endif


#ifdef K765_YJH_765_V001


#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

#define NO_PLAY_STATUS_LED

//#define PLAY_STATUS_LED_P27
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define FM_BY_PASS

#define VOLUME_DEFUALT 28

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define USE_GPIO_DETECT_EARPHONE_PLUGGED
#define EARPHONE_DETECT_USE_P02

#endif

#ifdef K598_YJH_598_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

//#define PLAY_STATUS_LED_P27

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define FM_BY_PASS

#define USE_POWER_KEY
#define USE_ONLY_POWER_HOLD_CTRL
#define PWR_CTRL_P02
#define POWE_KEY_PLAY_KEY_IN_ONE_KEY

#define USE_POWER_KEY_SHORT_SCAN

#define VOLUME_DEFUALT 28
#define BATT_DETECT_FUNC

#endif

#ifdef K599_JinRui_599_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_DUMP

//#define PLAY_STATUS_LED_P27

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define DECODE_STOP_MODE_ENABLE

#define VOLUME_DEFUALT 28

#endif


#ifdef K770_JinRui_770_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

#define PLAY_STATUS_LED_P27

#define VOLUME_DEFUALT 28

#define NOT_USE_LINE_IN_FUNC
#endif

#ifdef K000_MingYang_1003A_V001


#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

#define PLAY_STATUS_LED_P27
#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define FM_BY_PASS

#define VOLUME_DEFUALT 28

#define ADKEY_PLAY_SHORT_SCAN_FRE
#define LED_STATUS_STOP_AT_VALID_STATION

#define NEW_SD_DETECT_MOD

#define USE_LINE_IN_DETECT_FUNC
#define LINE_IN_DETECT_SHARE_LED_STATUS_PORT

#endif

#ifdef K086_JLH_2096_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

#define NO_PLAY_STATUS_LED

#define CUSTOMIZED_VOL_LIMITATION
#define VOLUME_DEFUALT 26

#define NOT_USE_LINE_IN_FUNC
#endif

#ifdef K776_CaiRun_776_V001

#define AC209_28PIN		//28 PIN IC GPIO CONFIG
#ifdef IIC_GPIO_USE_P02_P03
#undef IIC_GPIO_USE_P02_P03
#endif
#define IIC_GPIO_USE_P00_P01

#ifdef MUTE_PORT_USE_P01
#undef MUTE_PORT_USE_P01
#endif
#define MUTE_PORT_USE_P26

#define PLAY_STATUS_LED_P27

#define ADKEY_PLAY_SHORT_SCAN_FRE

#define EXCHANGE_LINE_IN_CHANNEL	//交换LINE IN 通道
#define FM_BY_PASS

#define VOLUME_DEFUALT 30

#define NO_VOLUME_LIMITE

#define USE_LONG_PLAY_KEY_TO_SWITCH_MODE

#define NOT_USE_LINE_IN_FUNC
#endif

