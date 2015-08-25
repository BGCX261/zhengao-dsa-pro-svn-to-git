/*************************************************************/
/** @file:misc_hdlr_if.h
    @brief:
    @details:
    @author:
    @date: 2012-06-13,8:53
    @note:
*/
/*************************************************************/
#include "custom_config.h"

#ifndef _MISC_HDLR_IF_
#define _MISC_HDLR_IF_

#include "config.h"
#include "main.h"

#define POWER_KEY_HOLD_VALID_TIME_SEC	2

typedef enum {

#ifdef AUX_DETECTION_THREAD_ENABLE
	AUX_PLUG_THREAD,
#endif	
#ifdef PHONE_DETECTION_THREAD_ENABLE
	PHONE_PLUG_THREAD,
#endif
#ifdef CHARGER_DETECTION_THREAD_ENABLE
	CHARGER_PLUG_THREAD,
#endif
	OTHER_THREAD,
}EVENT_ID;

#ifdef AUX_DETECTION_THREAD_ENABLE
#define AUX_THREAD		1
#else
#define AUX_THREAD		0
#endif

#ifdef PHONE_DETECTION_THREAD_ENABLE
#define PHONE_THREAD	1
#else
#define PHONE_THREAD		0
#endif

#ifdef CHARGER_DETECTION_THREAD_ENABLE
#define CHARGER_THREAD		1
#else
#define CHARGER_THREAD		0
#endif


#define MAX_EVENT_LIST		(AUX_THREAD+PHONE_THREAD+CHARGER_THREAD)



#if MAX_EVENT_LIST
#define EVENT_DETECTION_THREAD_HDLR
#endif


typedef enum {

	SYS_PWR_ON,
	SYS_PWR_OFF,
	SYS_PWR_IDLE,
	
}SYS_PWR_HDLR;

typedef enum {
	LED_SPARK_ON,
	LED_SPARK_VERY_FAST,
	LED_SPARK_FAST,
	LED_SPARK_NOR,
	LED_SPARK_SLOW,
	LED_SPARK_STOP,
	
}LED_SPARK_TYPE;

typedef enum {

	PA_UNMUTE,
	PA_MUTE,
	PA_SUPERMUTE,
}MUTE_TYPE;

typedef enum {

	I_FUNC,
	O_FUNC,
	S_FUNC,
	F_FUNC,
}FUNC_CMD;


enum {

	MS_NOP,
	MS_500=1,
	MS_1000,
	MS_1500,
	MS_2000,
};


#ifdef AD_MODE_FUNC
enum {

	AD_MODE_MUSIC,
	AD_MODE_FM,
	AD_MODE_WM,
	AD_MODE_AUX,
	AD_MODE_ERROR,
};
void init_adc_mode_switcher(void);

#endif


#ifdef __SMART_CPU__

void ext_pa_mute(MUTE_TYPE M_Type);
void init_func_list(void);
u8 func_msg_hdlr(FUNC_CMD Func_CMD,u8 func_msg);
void adc_channel_init(u8 adc_port);
void detect_event_func_init();
void detect_event_func_register(	EVENT_ID thread_id,
									bool event_trig_levl,
									//bool *event_protect,
									u8 msg_in,u8 msg_out,
									void (*init)(),bool (*gpio_level)(),void (*release)(),bool (*gpio_protect)()
									);
void detect_event_func_hdlr(void);
bool get_event_detect_status(EVENT_ID thread_id);

void event_50ms_hdlr(void);

#if defined(USE_POWER_KEY) || defined(USE_POWER_IDLE_MODE)
void power_key_hdlr(SYS_PWR_HDLR pwr_cmd);
#endif
#endif


u8 get_ir_key_index(u8 ir_code);
#ifdef IR_UART_DEBUG
void debug_ir_func(void);
#endif
#ifdef ADKEY_UART_DEBUG
void debug_adkey_func(void);
#endif

#ifdef AD_DETECT_FUNC
bool ad_detect_hdlr(u16 adc_value);
#endif


#ifndef NO_PLAY_STATUS_LED
void play_status_led_init(void);
void play_status_led_hdlr(void);
#endif
void set_play_status_led(LED_SPARK_TYPE led_status);
void set_play_status_led_id2(LED_SPARK_TYPE led_status);

void activate_pop_noise_hdlr(u8 delay_second);
void pop_noise_handler(void);

void event_halfsecond_hdlr(u8 msg);

#endif



