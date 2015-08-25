#include "custom_config.h"

#ifdef BLUE_TOOTH_UART_FUNC
#include "bluetooth_mode.h"
#include "uart.h"
#include "main.h"
#include "config.h"
#include "clock.h"
#include "msg.h"
#include "gpio_if.h"


xd_u8 bt_led_status=0;

void set_led_status(u8 statu_cmd)
{
	bt_led_status = statu_cmd;
}
#ifdef BLUE_TOOTH_STATUS_LED_PARTTERN
bool bt_led_spark=0;

void blue_tooth_status_led_init(void)
{
    BLUE_TOOTH_STATUS_LED_INIT();
    BLUE_TOOTH_STATUS_LED_OFF();
    BLUE_TOOTH_CALL_STATUS_OFF();
    bt_led_status = 0x86;	
}

void blue_tooth_status_led_hdlr(void)
{
	if((bt_led_status&0x80)>0){

#ifdef BLUE_TOOTH_TWO_LED_STATUS
    		set_play_status_led(LED_SPARK_STOP);
		set_play_status_led_id2(LED_SPARK_FAST);	
#elif defined(JK_IBT_388_1096A_V001)
    		set_play_status_led(LED_SPARK_STOP);
		set_play_status_led_id2(LED_SPARK_FAST);			
#else		
		bt_led_status--;			
		if((bt_led_status&0x0F)==0){
			bt_led_status = BT_STA_LED_SDBY;
    			set_play_status_led(LED_SPARK_STOP);
    			BLUE_TOOTH_STATUS_LED_OFF();
		}
#endif		
		
	 }
	 else if(bt_led_status==BT_STA_LED_PAIR){
#ifdef BLUE_TOOTH_TWO_LED_STATUS
		set_play_status_led_id2(LED_SPARK_FAST);		
#elif defined(JK_IBT_388_1096A_V001)
		set_play_status_led_id2(LED_SPARK_FAST);		
#else
		bt_led_spark=1-bt_led_spark;
				
		if(bt_led_spark){
			BLUE_TOOTH_CALL_STATUS_OFF();
    			BLUE_TOOTH_STATUS_LED_ON();
		}
		else{
			BLUE_TOOTH_CALL_STATUS_ON();
    			BLUE_TOOTH_STATUS_LED_OFF();
		}
#endif		
		
	  }	    
	 else if(bt_led_status==BT_STA_LED_CALL){
	 	
#ifdef BLUE_TOOTH_TWO_LED_STATUS
    		set_play_status_led(LED_SPARK_NOR);
		set_play_status_led_id2(LED_SPARK_STOP);
#elif defined(JK_IBT_388_1096A_V001)
		set_play_status_led_id2(LED_SPARK_NOR);		
#else
		bt_led_spark=1-bt_led_spark;
				
		if(bt_led_spark){
			BLUE_TOOTH_CALL_STATUS_OFF();
		}
		else{
			BLUE_TOOTH_CALL_STATUS_ON();
		}
		BLUE_TOOTH_STATUS_LED_OFF();
#endif		
		
	  }	  
	 else if(bt_led_status==BT_STA_LED_SDBY){
	 	
#ifdef BLUE_TOOTH_TWO_LED_STATUS
    		set_play_status_led_id2(LED_SPARK_ON);
    		set_play_status_led(LED_SPARK_STOP);
#elif defined(JK_IBT_388_1096A_V001)
    		set_play_status_led_id2(LED_SPARK_ON);
#else

    		BLUE_TOOTH_STATUS_LED_ON();
#if 0
		bt_led_spark=1-bt_led_spark;
				
		if(bt_led_spark){
    			BLUE_TOOTH_STATUS_LED_ON();
		}
		else{
    			BLUE_TOOTH_STATUS_LED_OFF();
		}

		BLUE_TOOTH_CALL_STATUS_OFF();
#endif		
#endif		
	  }	 
	 else if(bt_led_status==BT_STA_LED_PLAY){

		BLUE_TOOTH_STATUS_LED_ON();
		BLUE_TOOTH_CALL_STATUS_OFF();
		
	  }			 
	 else if(bt_led_status==BT_STA_LED_INCOMING){

#ifdef BLUE_TOOTH_TWO_LED_STATUS
    		set_play_status_led(LED_SPARK_FAST);
		set_play_status_led_id2(LED_SPARK_FAST);	
#elif defined(JK_IBT_388_1096A_V001)
    		set_play_status_led_id2(LED_SPARK_VERY_FAST);		
#else
		BLUE_TOOTH_STATUS_LED_ON();
		BLUE_TOOTH_CALL_STATUS_ON();
#endif
	  }		 
	 else if(bt_led_status==BT_STA_LED_IDLE){
	 	
#ifdef BLUE_TOOTH_TWO_LED_STATUS
		set_play_status_led_id2(LED_SPARK_STOP);				
    		set_play_status_led(LED_SPARK_STOP);
#elif defined(JK_IBT_388_1096A_V001)
		set_play_status_led_id2(LED_SPARK_STOP);				
    		set_play_status_led(LED_SPARK_STOP);			
#else
		BLUE_TOOTH_CALL_STATUS_OFF();
    		BLUE_TOOTH_STATUS_LED_OFF();
#endif		
	  }		 
}
#endif

#endif

