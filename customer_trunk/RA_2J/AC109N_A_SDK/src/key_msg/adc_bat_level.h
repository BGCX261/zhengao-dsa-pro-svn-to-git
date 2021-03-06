#include "custom_config.h"

#ifdef USE_BAT_MANAGEMENT

#ifdef BAT_MEASURE_USE_ADC_PORT

#define 	_5V		0xC000
#define 	_4V2	0xA100
#define 	_3V7	0x8E00
#define 	_3V3	0x8200

u8 const _code adc_bat_volt[]={

	0x70,	/// below 3V0	
	0x75,	/// 3V3
	0x8E,	/// 3V7
	0xA0,	//// 4V2
	0xA2,	//CHARGE_FULL  4V3
};

#else

#define 	_5V		0xC000
#define 	_4V2	0xA100
#define 	_3V7	0x8E00
#define 	_3V3	0x8200

u8 const _code adc_bat_volt[]={

	0x82,	/// below 3V3	
	0x83,	/// 3V3
	0x8E,	/// 3V7
	0xA1,	//// 4V2
	0xA6,	//CHARGE_FULL  4V3
};

#endif

enum
{
	BAT_LEVEL_DEAD,
	BAT_LEVEL_ALERT,
	BAT_LEVEL_LOW,
	BAT_LEVEL_FULL,
	BAT_LEVEL_CHRG_OVER,	
};


#define LOW_BAT_POWER_VALID_CNT		120
#endif

