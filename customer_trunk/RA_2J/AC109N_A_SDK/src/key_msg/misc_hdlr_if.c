/*--------------------------------------------------------------------------*/
/**@file    misc_hdlr_if.c
   @brief   misc_hdlr_if
   @details
   @author  R_A
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"
#include "misc_hdlr_if.h"
#include "hot_msg.h"
#include "msg.h"
#include "device.h"
#include "get_music_file.h"
#include "main.h"
#include "key.h"
#include "iic.h"
#include "DAC.h"
#include "music_play.h"
#include "UI_API.h"
#include "RTC_API.h"
#include "play_file.h"
#include "break_point.h"
#include "dac.h"
#include "IRTC.h"
#include "sdmmc_api.h"
#include "usb_host.h"
#include "FM_API.h"
#include "gpio_if.h"
#include "led_ind_drv.h"
#include "bluetooth_mode.h"
#include "FM_API.h"


#include "my_IR_key.c"
u8 get_ir_key_index(u8 ir_code)
{
	u8 ir_idx=0;

#if 0//def MISC_UART_DEBUG
	my_printf(" --->My_IRTab  SIZE  %d  \r\n",(u16)((sizeof(My_IRTab))));
	my_printf(" --->ir_code %x \r\n",(u16)ir_code);
#endif
	
	for(ir_idx=0;ir_idx<((u8)(sizeof(My_IRTab)));ir_idx++){

		if(My_IRTab[ir_idx] == ir_code){
			return ir_idx;
		}
	}
	return 0xFF;
}

#ifdef IR_UART_DEBUG
extern _no_init IR_CODE _idata IR_code;
void debug_ir_func(void)
{

       my_puts("-----> start  debug_ir_func -----\n");
#ifdef WDT_EN
    	config_wdt(0x40);  //关掉看门狗
#endif

	while(1){

		//my_printf(" --->debug_ir_func  state  %x \r\n",(u16)IR_code.bState);

		if(IR_code.bState == 32){		
			
			my_printf(" --->debug_ir_func -->  IR_code  : %x  --- > USER_code : %x	\r\n",
				(u16)(IR_code.wData&0x00FF),(u16)(IR_code.wUserCode));
		}
		delay_n10ms(10);
	}
}
#endif

#ifdef ADKEY_UART_DEBUG
extern _no_init AD_VAR _data AD_var;
void debug_adkey_func(void)
{
       my_puts("-----> start  debug_ir_func -----\n");
#ifdef WDT_EN
    	config_wdt(0x40);  //关掉看门狗
#endif
	while(1){
	
		my_printf(" --->debug_adkey_func -->  bChIndex  : %x  --- > wADValue   : %x	\r\n",
				(u16)(AD_var.bChIndex),(AD_var.wADValue[AD_var.bChIndex]));
		delay_n10ms(20);
	}		
}
#endif



#ifdef USE_ADKEY_DETECT_HP
static bool earphone_plugged=0;
static xd_u8 det_timer_hp=0;
#endif
#ifdef USE_ADKEY_DETECT_AUX
static bool aux_online=0;
static xd_u8 det_timer_aux=0;
#endif


static bool supper_mute_lock=0;
bool get_super_mute_lock()
{
	return supper_mute_lock;
}
void clear_super_mute_lock()
{
	supper_mute_lock =0;
}
void ext_pa_mute(MUTE_TYPE M_Type)
{
	static bool mute_flag=0;

	mute_gpio_init();
	
	if(M_Type == PA_UNMUTE){

		mute_port_unmute();
		mute_flag=0;
	}
	else if(M_Type == PA_MUTE){

		mute_port_mute();	
		mute_flag=1;
	}
	else if(M_Type == PA_SUPERMUTE){

		mute_flag=~mute_flag;
		
		if(mute_flag){

			mute_port_mute();	
			supper_mute_lock =1;
		}
		else{

			mute_port_unmute();
			supper_mute_lock =0;
		}
	}	

}
static xd_u8 delay_mute_timer=0;
void activate_pop_noise_hdlr(u8 delay_second)
{
	delay_mute_timer=delay_second;
	ext_pa_mute(PA_MUTE);
}
void pop_noise_handler(void)
{
	if(delay_mute_timer>0){
		delay_mute_timer--;
		if(delay_mute_timer==0){
			ext_pa_mute(PA_UNMUTE);
		}
	}
}
#define MAX_FUNC_LIST 		MAX_WORK_MODE
extern ENUM_WORK_MODE _data work_mode;
static xd_u16 Sys_Func_List=0;

void add_func_to_mode_list(ENUM_WORK_MODE Dev) AT(CSTART)
{
	Sys_Func_List |=BIT(Dev);
#ifdef MISC_UART_DEBUG
	my_printf(" --->add_func_to_mode_list %x \r\n",(u16)Sys_Func_List);
#endif
}
void remov_func_from_mode_list(ENUM_WORK_MODE Dev) AT(CSTART)
{
	Sys_Func_List &=~(BIT(Dev));
#ifdef MISC_UART_DEBUG	
	my_printf(" --->remov_func_from_mode_list %x \r\n",(u16)Sys_Func_List);
#endif
}
void set_curr_func_mode(ENUM_WORK_MODE curr_mod) AT(CSTART)
{
	work_mode = curr_mod;	
	Sys_Func_List =((curr_mod<<8)|(Sys_Func_List&0x00FF));	
#ifdef MISC_UART_DEBUG
	my_printf(" --->Set_Curr_Func %x \r\n",(u16)Sys_Func_List);
#endif
}
void init_func_list(void) AT(CSTART)
{
#ifdef MISC_UART_DEBUG
	my_printf("Init_Func_List  \r\n");
#endif
	Sys_Func_List=0;
	
#ifndef NOT_MOUNT_USB_SD_DEV
	if((get_usb_online_status()&BIT(0)))
		add_func_to_mode_list(SYS_USB_MODE);

#ifdef SDMMCA_EN
    	if(get_sdmmc_online_status(SDMMCA_ID)>0)
		add_func_to_mode_list(SYS_SD_MODE);
#endif

#endif

#ifdef FORCE_MOUNT_SD_CARD_DEV
		add_func_to_mode_list(SYS_SD_MODE);
#endif

#ifdef RADIO_MODE_ENABLE
#ifndef NO_FM_CHIP_ON_BOARD
       if(chk_fm_dev_online()){	//NO FM
       	add_func_to_mode_list(SYS_RADIO_MODE);
		fm_rev_powerdown();	
    	}
#endif
#endif


#ifndef NOT_USE_LINE_IN_FUNC

#ifdef AUX_DETECTION_THREAD_ENABLE

#ifdef AUX_DETECT_FUNC_WITH_MANUAL_SEL
	add_func_to_mode_list(SYS_AUX_MODE);
#else
	if(get_event_detect_status(AUX_PLUG_THREAD)){
		add_func_to_mode_list(SYS_AUX_MODE);
	}
#endif	

#elif defined(USE_ADKEY_DETECT_AUX)&&defined(AD_DETECT_FUNC)

#ifdef AUX_DETECT_FUNC_WITH_MANUAL_SEL
	add_func_to_mode_list(SYS_AUX_MODE);
#else
	if(aux_online){
		add_func_to_mode_list(SYS_AUX_MODE);
	}
#endif	


#else	

#ifndef DONT_MOUNT_AUX_FUNC
		add_func_to_mode_list(SYS_AUX_MODE);
#endif

#endif

#if defined(USE_LINE_IN_GPIO_SEL_MODE)
	AUX_GPIO_INIT();
	delay_10ms(1);
	if(AUX_GPIO_READ){
		add_func_to_mode_list(SYS_AUX_MODE);
	}
	else{
		remov_func_from_mode_list(SYS_AUX_MODE);
	}
#endif
#endif


#if defined(IPONE_INDEPENDENT_MODE)
		add_func_to_mode_list(IPH_DEV);
#endif
#ifdef USE_RTC_FUNCTION
		add_func_to_mode_list(RTC_DEV);
#ifdef DONT_MOUNT_RTC_FUNC
		remov_func_from_mode_list(RTC_DEV);
#endif
#endif

#ifdef BLUE_TOOTH_MODE_ENABLE
	add_func_to_mode_list(SYS_BLUETOOTH_MODE);
#endif

#if defined(USE_BT_GPIO_SEL_MODE)
	BT_GPIO_SEL_INIT();
	_nop_();
	_nop_();
	if(!BT_GPIO_SEL_READ){
		add_func_to_mode_list(BT_DEV);
#if defined(SYS_DEFAULT_IN_BLUETOOTH_MODE)
		Set_Curr_Func(SYS_BT);
#endif				
	}
	else{
		remov_func_from_mode_list(BT_DEV);
	}
#endif

#ifdef USE_MANUAL_IDLE_FUNC
		add_func_to_mode_list(SYS_IDLE_MODE);
#endif

#if defined(IPONE_DOCK_FUNC_ENABLE)
#if defined(IPHONE_DETECT_IN_USE)
#if defined(IPHONE_DOCKING_PRO)
	if(iphone_status){
		Set_Curr_Func(SYS_IPH);
	}
	else{
		remov_func_from_mode_list(IPH_DEV);
	}
#endif	
#endif
#endif

#ifdef PC_HOT_PLUGGED_POWER_ON_ENABLE
	 if ((get_usb_online_status() & BIT(1)) >0){
		func_msg_hdlr(S_FUNC,SYS_USB_DEVICE_MODE);	
	}
#endif


#ifdef AD_MODE_FUNC
	init_adc_mode_switcher();
#endif

}
u8 next_func_idx(void) AT(CSTART)
{
	u8 mod_idx;
	if((Sys_Func_List&0x00FF)>0)
	{
		for(mod_idx=(((Sys_Func_List&0xFF00)>>8)+1);mod_idx<MAX_FUNC_LIST;mod_idx++){
			if((Sys_Func_List&(BIT(mod_idx)))>0){
				return (ENUM_WORK_MODE)mod_idx;
			}
		}				
		for(mod_idx=0;mod_idx<=((Sys_Func_List&0xFF00)>>8);mod_idx++)
			if((Sys_Func_List&(BIT(mod_idx)))>0){
				return (ENUM_WORK_MODE)mod_idx;
		}
	}	
	return SYS_IDLE_MODE;
}
u8 func_msg_hdlr(FUNC_CMD Func_CMD,u8 func_msg) AT(CSTART)
{
	u8 ret_var=0;
	
	switch(Func_CMD){

		case I_FUNC:								//3add new func to list
			if(func_msg== MSG_USB_DISK_IN){
				func_msg = SYS_USB_MODE;
			}
			else if(func_msg== MSG_SDMMCA_IN){
				func_msg = SYS_SD_MODE;
			}
			else if(func_msg== MSG_AUX_IN){
				func_msg = SYS_AUX_MODE;
			}	
			else if(func_msg== MSG_USB_PC_IN){
				func_msg = SYS_USB_DEVICE_MODE;
			}
			add_func_to_mode_list((ENUM_WORK_MODE)func_msg);
			ret_var = 0xFF;
			break;
		case O_FUNC:				//3				remove func from list
			if(func_msg== MSG_USB_DISK_OUT){
				func_msg = SYS_USB_MODE;
			}
			else if(func_msg== MSG_SDMMCA_OUT){
				func_msg = SYS_SD_MODE;
			}
			else if(func_msg== MSG_AUX_OUT){
				func_msg = SYS_AUX_MODE;
			}	
			else if(func_msg== MSG_USB_PC_OUT){
				func_msg = SYS_USB_DEVICE_MODE;
			}			
			remov_func_from_mode_list((ENUM_WORK_MODE)func_msg);
			ret_var = 0xFF;
			break;
		case S_FUNC:					//3					Set curr func to list
			if(func_msg== MSG_USB_DISK_IN){
				func_msg = SYS_USB_MODE;
			}
			else if(func_msg== MSG_SDMMCA_IN){
				func_msg = SYS_SD_MODE;
			}
			else if(func_msg== MSG_AUX_IN){
				func_msg = SYS_AUX_MODE;
			}	
			else if(func_msg== MSG_USB_PC_IN){
				func_msg = SYS_USB_DEVICE_MODE;
			}
			set_curr_func_mode((ENUM_WORK_MODE)func_msg);
			ret_var = 0xFF;
			break;
		case F_FUNC:					//3					get next func from list
			ret_var = next_func_idx();
			break;
	}

	return ret_var;
}

void adc_channel_init(u8 adc_port)
{
	u8 adc_ch=0;
	if(adc_port<=0xF7){
		
		adc_ch = adc_port&0x0F;
		P0PD &= ~BIT(adc_ch);
	   	P0PU &= ~BIT(adc_ch);
	    	P0DIR |= BIT(adc_ch);
	    	P0DIE &= ~BIT(adc_ch);                               //设置AD key IO方向和模拟输入属性
	}
}

#ifdef EVENT_DETECTION_THREAD_HDLR
typedef struct{

	void (*gpio_init)(void);
	bool (*gpio_level)(void);
	void (*gpio_release)(void);
	bool (*gpio_protect)(void);
}GPIO_FUNC;

typedef struct{
	//u8 event_id;
	u8 event_deb_timer;
	bool event_valid;
	bool event_logic_level;
	//bool *event_pretect;
	u8 event_msg_in;
	u8 event_msg_out;
	GPIO_FUNC event_func;
}EVENT_STRUCT;

static EVENT_STRUCT event_tab[MAX_EVENT_LIST]={0};
void detect_event_func_init()
{
	u8 i=0;
	
	for(i=0;i<MAX_EVENT_LIST;i++){
		
	       event_tab[i].event_deb_timer = 0;
		event_tab[i].event_logic_level=FALSE;
		event_tab[i].event_valid=FALSE;
		event_tab[i].event_msg_in=0;
		event_tab[i].event_msg_out=0;

		
		event_tab[i].event_func.gpio_init=NULL;
		event_tab[i].event_func.gpio_level=NULL;
		event_tab[i].event_func.gpio_release=NULL;
		event_tab[i].event_func.gpio_protect=NULL;
	}
}
void detect_event_func_register(	EVENT_ID thread_id,
									bool event_trig_levl,
									//bool *event_protect,
									u8 msg_in,u8 msg_out,
									void (*init)(),bool (*gpio_level)(),void (*release)(),bool (*gpio_protect)()
									)
{
	event_tab[thread_id].event_logic_level=event_trig_levl;
	//event_tab[thread_id].event_pretect=event_protect;
	event_tab[thread_id].event_msg_in=msg_in;
	event_tab[thread_id].event_msg_out=msg_out;

	event_tab[thread_id].event_func.gpio_init=init;
	event_tab[thread_id].event_func.gpio_level=gpio_level;
	event_tab[thread_id].event_func.gpio_release=release;
	event_tab[thread_id].event_func.gpio_protect=gpio_protect;

#if 0
   	 my_printf(" --->func_register :init %x \r\n",(u16)init);
   	 my_printf(" --->func_register :gpio_level %x \r\n",(u16)gpio_level);
   	 my_printf(" --->func_register :release %x \r\n",(u16)release);
   	 my_printf(" --->func_register :event_protect	%x \r\n",(u16)event_protect);
   	 my_printf(" --->func_register :event_protect	%x \r\n",(u16)(*event_tab[thread_id].event_pretect));
#endif

}
void detect_event_func_hdlr(void)
{
	u8 i=0;

	for(i=0;i<MAX_EVENT_LIST;i++){


		if(event_tab[i].event_func.gpio_protect != NULL)
			if ( event_tab[i].event_func.gpio_protect() )continue;

#if 0
	   	 my_printf(" --->main :11111 %x \r\n",(u16)event_tab[i].event_func.gpio_init);
	   	 my_printf(" --->main :22222 %x \r\n",(u16)event_tab[i].event_func.gpio_level);
	   	 my_printf(" --->main :33333 %x \r\n",(u16)event_tab[i].event_func.gpio_release);
#endif	
		if(event_tab[i].event_func.gpio_init != NULL)
		event_tab[i].event_func.gpio_init();
		_nop_();  _nop_();

		if(event_tab[i].event_func.gpio_level != NULL){
			
			if (event_tab[i].event_func.gpio_level()==event_tab[i].event_logic_level){
				
			        event_tab[i].event_deb_timer = 0;
			        if (!event_tab[i].event_valid)
			        {
			            event_tab[i].event_valid=1;
			            put_msg_lifo(event_tab[i].event_msg_in);
			        }
			}
			else{
				
			        event_tab[i].event_deb_timer++;
			        if (event_tab[i].event_deb_timer  > 6)
			        {
			            if (event_tab[i].event_valid)
			            {
			            		put_msg_lifo(event_tab[i].event_msg_out);
			                	event_tab[i].event_valid = 0;
			            }
			        }
			}
		}
		if(event_tab[i].event_func.gpio_init != NULL)
			event_tab[i].event_func.gpio_release();
	}
}
bool get_event_detect_status(EVENT_ID thread_id)
{
	return (event_tab[thread_id].event_valid );
}
#endif

#ifndef NO_PLAY_STATUS_LED
#include "led_ind_drv.c"
static xd_u8 LED_Flash_mode =0xFF;
static xd_u8 LED_cnt=0;
#if 0
u8 get_work_mode_idx(u8 mod)
{
	u8 i=0;
	for(i=0;i<(sizeof(mode_led_tab)/3);){
		
		if(mode_led_tab[i].led_mode==mod)break;
		i++;
	}		
	return i;
}
void led_gpio_init()
{
	u8 i=0;
	for(i=0;i<(sizeof(mode_led_tab)/3);i++){
		
		if(mode_led_tab[i].led_port ==PORT_P0){

				P0DIR &=~(mode_led_tab[i].led_port_bit);
				P0PU |=(mode_led_tab[i].led_port_bit);
	#if defined(LED_CTRL_LEVEL_NORMAL)
				P0 &=~(mode_led_tab[i].led_port_bit);				
	#else
				P0 |=(mode_led_tab[i].led_port_bit);							
	#endif			
		}
		else if(mode_led_tab[i].led_port ==PORT_P1){
			
				P1DIR &=~(mode_led_tab[i].led_port_bit);
				P1PU |=(mode_led_tab[i].led_port_bit);
	#if defined(LED_CTRL_LEVEL_NORMAL)
				P1 &=~(mode_led_tab[i].led_port_bit);				
	#else
				P1 |=(mode_led_tab[i].led_port_bit);							
	#endif			
		}
		else if(mode_led_tab[i].led_port ==PORT_P2){

				P2DIR &=~(mode_led_tab[i].led_port_bit);	
				P2PU |=(mode_led_tab[i].led_port_bit);
	#if defined(LED_CTRL_LEVEL_NORMAL)
				P2 &=~(mode_led_tab[i].led_port_bit);				
	#else
				P2 |=(mode_led_tab[i].led_port_bit);							
	#endif			
		}
		else if(mode_led_tab[i].led_port ==PORT_P3){

				P3DIR &=~(mode_led_tab[i].led_port_bit);	
				P3PU |=(mode_led_tab[i].led_port_bit);	
	#if defined(LED_CTRL_LEVEL_NORMAL)
				P3 &=~(mode_led_tab[i].led_port_bit);				
	#else
				P3 |=(mode_led_tab[i].led_port_bit);							
	#endif
		}
		else if(mode_led_tab[i].led_port ==PORT_P4){

				P4DIR &=~(mode_led_tab[i].led_port_bit);	
				P4PU |=(mode_led_tab[i].led_port_bit);	
	#if defined(LED_CTRL_LEVEL_NORMAL)
				P4 &=~(mode_led_tab[i].led_port_bit);				
	#else
				P4 |=(mode_led_tab[i].led_port_bit);							
	#endif
		}		
		else if(mode_led_tab[i].led_port ==PORT_VPP){

	#if defined(LED_CTRL_LEVEL_NORMAL)
				//P5PU &=~(mode_led_tab[i].led_port_bit);
	#else
				//P5PU |= (mode_led_tab[i].led_port_bit);
	#endif

		}
	}
}
void turn_off_last_working_led()
{
	if(last_led_work_mode>SYS_IDLE_MODE)return;

		mod_idx = get_work_mode_idx(last_led_work_mode);
		
		if(mode_led_tab[mod_idx].led_port ==PORT_P0){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P0 &=~(mode_led_tab[mod_idx].led_port_bit);				
#else
			P0 |=(mode_led_tab[mod_idx].led_port_bit);							
#endif			
		}
		else if(mode_led_tab[mod_idx].led_port ==PORT_P1){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P1 &=~(mode_led_tab[mod_idx].led_port_bit);				
#else
			P1 |=(mode_led_tab[mod_idx].led_port_bit);							
#endif			
		}
		else if(mode_led_tab[mod_idx].led_port ==PORT_P2){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P2 &=~(mode_led_tab[mod_idx].led_port_bit);				
#else
			P2 |=(mode_led_tab[mod_idx].led_port_bit);							
#endif			
		}
		else if(mode_led_tab[mod_idx].led_port ==PORT_P3){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P3 &=~(mode_led_tab[mod_idx].led_port_bit);				
#else
			P3 |=(mode_led_tab[mod_idx].led_port_bit);							
#endif
		}	
		else if(mode_led_tab[mod_idx].led_port ==PORT_P4){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P4 &=~(mode_led_tab[mod_idx].led_port_bit);				
#else
			P4 |=(mode_led_tab[mod_idx].led_port_bit);							
#endif
		}

#ifdef EXTENDED_WORK_MODE_USE_TWO_GPIO_CTRL
		if(mode_led_tab[mod_idx].led_port_2==PORT_P0){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P0 &=~(mode_led_tab[mod_idx].led_port_bit_2);				
#else
			P0 |=(mode_led_tab[mod_idx].led_port_bit_2);							
#endif
		}
		else if(mode_led_tab[mod_idx].led_port_2==PORT_P1){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P1 &=~(mode_led_tab[mod_idx].led_port_bit_2);				
#else
			P1 |=(mode_led_tab[mod_idx].led_port_bit_2);							
#endif			
		}
		else if(mode_led_tab[mod_idx].led_port_2==PORT_P2){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P2 &=~(mode_led_tab[mod_idx].led_port_bit_2);				
#else
			P2 |=(mode_led_tab[mod_idx].led_port_bit_2);							
#endif			
		}
		else if(mode_led_tab[mod_idx].led_port_2==PORT_P3){

#if defined(LED_CTRL_LEVEL_NORMAL)
			P3 &=~(mode_led_tab[mod_idx].led_port_bit_2);				
#else
			P3 |=(mode_led_tab[mod_idx].led_port_bit_2);							
#endif
		}
		else if(mode_led_tab[i].led_port ==PORT_VPP){

#if defined(LED_CTRL_LEVEL_NORMAL)
			//P5PU &=~(mode_led_tab[mod_idx].led_port_bit);
#else
			//P5PU |=(mode_led_tab[mod_idx].led_port_bit);
#endif
		}		
#endif
		
}
 void led_set_new_method(u8 led_cmd)
{	
	switch(mode_led_tab[mod_idx].led_port){
		case PORT_P0:
			if(led_cmd)
				P0 |=(mode_led_tab[mod_idx].led_port_bit);			
			else
				P0 &=~(mode_led_tab[mod_idx].led_port_bit);	
			break;
		case PORT_P1:

			if(led_cmd)
				P1 |=(mode_led_tab[mod_idx].led_port_bit);			
			else
				P1 &=~(mode_led_tab[mod_idx].led_port_bit);			
			break;
		case PORT_P2:
			
			if(led_cmd)
				P2 |=(mode_led_tab[mod_idx].led_port_bit);			
			else
				P2 &=~(mode_led_tab[mod_idx].led_port_bit);			
			break;
		case PORT_P3:
		
			if(led_cmd)
				P3 |=(mode_led_tab[mod_idx].led_port_bit);			
			else
				P3 &=~(mode_led_tab[mod_idx].led_port_bit);			
			break;
		case PORT_P4:		
			if(led_cmd)
				P4 |=(mode_led_tab[mod_idx].led_port_bit);			
			else
				P4 &=~(mode_led_tab[mod_idx].led_port_bit);			
			break;			
		case PORT_VPP:
			//if(led_cmd)
			//	P5PU |=(mode_led_tab[mod_idx].led_port_bit);
			//else
			//	P5PU &=~(mode_led_tab[mod_idx].led_port_bit);
			break;
	}

#ifdef EXTENDED_WORK_MODE_USE_TWO_GPIO_CTRL
	switch(mode_led_tab[mod_idx].led_port_2){
		case PORT_P0:
			if(led_cmd>0)
				P0 |=(mode_led_tab[mod_idx].led_port_bit_2);			
			else
				P0 &=~(mode_led_tab[mod_idx].led_port_bit_2);	
			break;
		case PORT_P1:

			if(led_cmd>0)
				P1 |=(mode_led_tab[mod_idx].led_port_bit_2);			
			else
				P1 &=~(mode_led_tab[mod_idx].led_port_bit_2);			
			break;
		case PORT_P2:

			if(led_cmd>0)
				P2 |=(mode_led_tab[mod_idx].led_port_bit_2);			
			else
				P2 &=~(mode_led_tab[mod_idx].led_port_bit_2);			
			break;
		case PORT_P3:
		
			if(led_cmd>0)
				P3 |=(mode_led_tab[mod_idx].led_port_bit_2);			
			else
				P3 &=~(mode_led_tab[mod_idx].led_port_bit_2);			
			break;
		case PORT_P4:
		
			if(led_cmd>0)
				P4 |=(mode_led_tab[mod_idx].led_port_bit_2);			
			else
				P4 &=~(mode_led_tab[mod_idx].led_port_bit_2);			
			break;			
		case PORT_VPP:
			//if(led_cmd)
			//	P5PU |=(mode_led_tab[mod_idx].led_port_bit_2);
			//else
			//	P5PU &=~(mode_led_tab[mod_idx].led_port_bit_2);
			break;			
	}
#endif
	
}
#endif

#ifdef TWO_PLAY_STATUS_LED
static xd_u8 LED_Flash_mode_id2 =0xFF;
static xd_u8 LED_cnt_id2=0;
void play_status_led_hdlr_id2(void)
{
	static bool led_bit_id2=0;

#if defined(PLAY_STATUS_LED_SHARE_WITH_IIC_SCL)
	if(iic_busy)return;
#endif

	LED_cnt_id2++;
	
	if(LED_Flash_mode_id2 ==0xFF){	//LED_FLASH_STOP

		led_id2_set_port_off();
	}
	else if(LED_Flash_mode_id2 == 0xF6){	//LED_SPARK_ON

		led_id2_set_port_on();
	}
	else  if((LED_cnt_id2 % LED_Flash_mode_id2)==0){

		led_bit_id2 =1-led_bit_id2;
		if(led_bit_id2){
			led_id2_set_port_on();
		}
		else{
			led_id2_set_port_off();
		}
	}	
}
void set_play_status_led_id2(LED_SPARK_TYPE led_status)
{
#ifdef NO_PLAY_STATUS_LED
	led_status = led_status;
#else
	EA = 0;
#if 0//(LED_MAX_NUM>1)
	if(last_led_work_mode!=work_mode)
	{
		turn_off_last_working_led();
		mod_idx = get_work_mode_idx(work_mode);
		last_led_work_mode = work_mode;
	}
#endif

	if(led_status ==LED_SPARK_ON){
		LED_Flash_mode_id2 = 0xF6;
	}
	else if(led_status ==LED_SPARK_VERY_FAST){
		LED_Flash_mode_id2 = 1;
	}
	else if(led_status ==LED_SPARK_FAST){
		LED_Flash_mode_id2 = 2;
	}
	else if(led_status ==LED_SPARK_NOR){
		LED_Flash_mode_id2 = 6;
	}
	else if(led_status ==LED_SPARK_STOP){
		LED_Flash_mode_id2 = 0xFF;
	}
	EA =1;
#endif	
}
#endif


void play_status_led_hdlr(void)
{
	static bool led_bit=0;

#if defined(PLAY_STATUS_LED_SHARE_WITH_IIC_SCL)
	if(iic_busy)return;
#endif

#ifdef TWO_PLAY_STATUS_LED
	play_status_led_hdlr_id2();
#endif
	LED_cnt++;
	
	if(LED_Flash_mode ==0xFF){	//LED_FLASH_STOP

		led_set_port_off();
	}
	else if(LED_Flash_mode == 0xF6){	//LED_SPARK_ON

		led_set_port_on();
	}
	else  if((LED_cnt % LED_Flash_mode)==0){

		led_bit =1-led_bit;
		if(led_bit){
			led_set_port_on();
		}
		else{
			led_set_port_off();
		}
	}	
}
#endif
void set_play_status_led(LED_SPARK_TYPE led_status)
{
#ifdef NO_PLAY_STATUS_LED
	led_status = led_status;
#else
	EA = 0;
#if 0//(LED_MAX_NUM>1)
	if(last_led_work_mode!=work_mode)
	{
		turn_off_last_working_led();
		mod_idx = get_work_mode_idx(work_mode);
		last_led_work_mode = work_mode;
	}
#endif

	if(led_status ==LED_SPARK_ON){
		LED_Flash_mode = 0xF6;
	}
	else if(led_status ==LED_SPARK_VERY_FAST){
		LED_Flash_mode = 1;
	}
	else if(led_status ==LED_SPARK_FAST){
		LED_Flash_mode = 2;
	}
	else if(led_status ==LED_SPARK_NOR){
		LED_Flash_mode = 6;
	}
	else if(led_status ==LED_SPARK_STOP){
		LED_Flash_mode = 0xFF;
	}
	EA =1;
#endif	
}
#ifndef NO_PLAY_STATUS_LED
void play_status_led_init(void)
{
    led_port_init();
    led_set_port_off();
    LED_Flash_mode = 0xFF;
#ifdef TWO_PLAY_STATUS_LED
    led_id2_port_init();
    led_id2_set_port_off();
    LED_Flash_mode_id2 = 0xFF;
#endif
}
#endif

#if defined(USE_POWER_KEY) || defined(USE_POWER_IDLE_MODE)
void power_key_hdlr(SYS_PWR_HDLR pwr_cmd)
{
	u8 key_msg=0;

	if(pwr_cmd == SYS_PWR_ON){

#ifdef USE_POWER_KEY

		u8 key_hold_timer=4,pwr_key_valid_sec=0;

		sys_gpio_ctrl_pwr(SYS_PWR_ON);
		
		while(1){

			key_msg = app_get_msg();

#if 0
			if(key_msg!= NO_MSG)
		   	 my_printf(" --->power_key_hdlr  key_msg : %x \r\n",(u16)key_msg);
#endif



			switch(key_msg){

			        case MSG_HALF_SECOND:
						
#ifdef PC_HOT_PLUGGED_POWER_ON_ENABLE
	    				if ((get_usb_online_status() & BIT(1)) >0){

				     		func_msg_hdlr(S_FUNC,SYS_USB_MODE);	
						goto __POWER_ON;
					}
#endif

#ifdef DC_POWER_PLUGGED_POWER_ON_ENABLE
	  		   		if(get_event_detect_status(CHARGER_PLUG_THREAD)){
						goto __POWER_IDLE;
					}
#endif
				   	//my_printf(" --->power_key_hdlr  %x \r\n",(u16)key_hold_timer);
						
					if(key_hold_timer>3){
						pwr_key_valid_sec++;

						if(pwr_key_valid_sec == (POWER_KEY_HOLD_VALID_TIME_SEC*2)){
							goto __POWER_ON;
						}
					}

				 	key_hold_timer--;
					if(key_hold_timer==0){
						goto __POWER_OFF;
					}
					
					break;
			        case MSG_POWER_KEY_HOLD:

				   	// my_printf(" --->power_key_hdlr key_msg %x \r\n",(u16)key_msg);
						
					key_hold_timer=5;
					break;
				 default:

				 	break;
			}
		}
__POWER_ON:
		UI_menu(MENU_POWER_UP);
		sys_gpio_ctrl_pwr(SYS_PWR_ON);
#endif		
	}
	else if(pwr_cmd == SYS_PWR_OFF){
#ifdef USE_POWER_KEY
__POWER_OFF:

            	//my_puts("__POWER_OFF \r\n");
		set_play_status_led(LED_SPARK_STOP);

#ifdef DC_POWER_PLUGGED_POWER_OFF_IN_IDLE_MODE
  		if(get_event_detect_status(CHARGER_PLUG_THREAD)){
			goto __POWER_IDLE;
		}
#endif
	    	UI_menu(MENU_POWER_DOWN);
		sys_gpio_ctrl_pwr(SYS_PWR_OFF);
		ext_pa_mute(PA_MUTE);

		delay_n10ms(20);
		EA = 0;
#ifdef WDT_EN
    		config_wdt(0x40);  //关掉看门狗
#endif

		while(1);
#endif		
		
	}
	else if(pwr_cmd == SYS_PWR_IDLE){

__POWER_IDLE:		
#ifdef USE_POWER_IDLE_MODE

	    	UI_menu(MENU_POWER_DOWN);
		ext_pa_mute(PA_MUTE);
		set_play_status_led(LED_SPARK_STOP);
		while(1){
			
			key_msg = app_get_msg();

	 		event_halfsecond_hdlr(key_msg);

			switch(key_msg){

#ifdef PC_HOT_PLUGGED_POWER_ON_ENABLE
#ifdef USB_DEVICE_EN
			    case MSG_USB_PC_IN:
#ifdef SDMMCA_EN
			        music_device_info[DEVICE_SDMMCA].wBreak_point_filenum = 0;
			        music_device_info[DEVICE_SDMMCA].wfileTotal = 0;
#endif
#ifdef SDMMCB_EN
			        music_device_info[DEVICE_SDMMCB].wBreak_point_filenum = 0;
			        music_device_info[DEVICE_SDMMCB].wfileTotal = 0;
#endif
			        LED_FADE_ON();

				 func_msg_hdlr(S_FUNC,SYS_USB_DEVICE_MODE);
			        //put_msg_lifo(MSG_CHANGE_WORK_MODE);
			        return;

#endif

#endif										
			        case MSG_POWER_DOWN:
				     set_play_status_led(LED_SPARK_ON);						
				     func_msg_hdlr(S_FUNC,SYS_USB_MODE);
			            return;
			        default:
			            //ap_handle_hotkey(key_msg);
			            break;
			}
		}
#endif		
	}	

}
#endif


#ifdef USE_BAT_MANAGEMENT
#include "adc_bat_level.h"
static xd_u8 LDO_IN_Volt=0,batt_level=0;

#ifdef CHARGER_DETECTION_THREAD_ENABLE
bool charger_detect(void)
{	
     if(get_event_detect_status(CHARGER_PLUG_THREAD)){
#if 1
		if(LDO_IN_Volt>=adc_bat_volt[sizeof(adc_bat_volt)-1]){
				
			batt_level = sizeof(adc_bat_volt)-1;
		}
		else{
			
			if(batt_level++>=(sizeof(adc_bat_volt)-2))
				batt_level=1;
		}
#endif		
#ifdef BAT_UART_DEBUG
    		my_printf(" --->charger_detect :batt_level  %x \r\n",(u16)(batt_level));
#endif
		return 1;
     }

     return 0;
}
#endif
u8 get_bat_volt_level(void){
	return batt_level;
}
void disp_bat_icon_buf(void)
{
#if 0
	if(work_mode==IDLE_MODE)return;
	
	led_clr_icon(LED0_BFUL);
	led_clr_icon(LED0_BHAL);
	
	switch(batt_level)
	{
		case 0:
			if(low_bat_blink)
				led_disp_icon(LED0_BHAL);
			break;
		case 1:
			led_disp_icon(LED0_BHAL);
			break;		
		case 2:
			led_disp_icon(LED0_BFUL);
		break;
	}
#endif	
}
#ifdef BAT_LOW_LEVEL_HLDR
xd_u8 bat_alert_timer=1;
void bat_low_level_hldr(u8 bat_level)
{
	static xd_u8 bat_low_level_cnt=0;
#ifdef BAT_LOW_BEEP_ALERT
	if(bat_level<=BAT_LEVEL_ALERT){

#ifdef BAT_UART_DEBUG
   	my_printf(" --->bat_low_level_hldr :bat_level  %x \r\n",(u16)bat_level);
   	my_printf(" --->bat_low_level_hldr :bat_low_level_cnt  %x \r\n",(u16)bat_low_level_cnt);
#endif

		if(bat_low_level_cnt >=(LOW_BAT_POWER_VALID_CNT*bat_alert_timer)){
			
			bat_low_level_cnt =0;
			set_key_tone();
			delay_n10ms(60);
			set_key_tone();
			delay_n10ms(60);
			set_key_tone();
			delay_n10ms(60);
			
			if(bat_alert_timer==2){
	            		put_msg_lifo(MSG_POWER_DOWN);
				bat_alert_timer=1;
			}
			bat_alert_timer++;
		}
		else{
			bat_low_level_cnt++;
		}
	}
#endif			

}
#endif
#ifdef BAT_CHARGER_IND_HLDR
void bat_charger_ind_hldr()
{
#ifdef BAT_CHARGE_LED_IND

	charger_led_ind_gpio_init();

	if(batt_level>=BAT_LEVEL_CHRG_OVER){
		charger_led_ind_gpio_off();
	}
	else{
		charger_led_ind_gpio_on();
	}
#endif			
}
void bat_charger_ind_hldr_end()
{
#ifdef BAT_CHARGE_LED_IND
	charger_led_ind_gpio_off();
#endif			

}
#endif			

void bmt_hdlr(void)
{
	 u8 adc_volt_level=0;
	LDO_IN_Volt=(u8)(AD_var.wADValue[ADC_CHARGER_CH]>>8);
#ifdef BAT_UART_DEBUG
   	my_printf(" --->bmt_hdlr :LDO_IN_Volt  %x \r\n",(u16)LDO_IN_Volt);
#endif

#ifdef CHARGER_DETECTION_THREAD_ENABLE

	if(charger_detect()){
#ifdef BAT_CHARGER_IND_HLDR
		bat_charger_ind_hldr();
#endif
#ifdef BAT_LOW_LEVEL_HLDR
		bat_alert_timer=1;
#endif
		return;
	}
#endif	
#ifdef BAT_CHARGER_IND_HLDR
	bat_charger_ind_hldr_end();
#endif
	for(adc_volt_level =0; adc_volt_level<(sizeof(adc_bat_volt));adc_volt_level++){

		if(LDO_IN_Volt<=adc_bat_volt[adc_volt_level]){
			batt_level = adc_volt_level;
#ifdef BAT_LOW_LEVEL_HLDR
			bat_low_level_hldr(adc_volt_level);
#endif			
			break;
		}
	}
#ifdef BAT_UART_DEBUG
    	my_printf(" --->bmt_hdlr :batt_level  %x \r\n",(u16)(batt_level));
#endif
	disp_bat_icon_buf();

}
#endif

#ifdef USB_ERP2_FUNC
xd_u16 erp2_timer=0;
bool erp2_func_pwrdn=0;
void erp2_func_hdlr(void)
{
	if((((((get_usb_online_status()&BIT(0))==0)&&((get_sdmmc_online_status(SDMMCA_ID))==0))||
		(Music_Play_var.bPlayStatus== MAD_PAUSE))&&((work_mode==SYS_USB_MODE)||(work_mode==SYS_SD_MODE)))||
#ifdef BLUE_TOOTH_ERP2_FUNC
		((get_blue_tooth_connect_status()==0)&&(work_mode==SYS_BLUETOOTH_MODE))
#endif		
		){

		if(erp2_timer++>=(2*60*ERP2_TIMER_UNIT_IN_MIN)){
		//if(erp2_timer++>=(20)){

			erp2_timer=0;
			 erp2_func_pwrdn=1;

			if(work_mode !=SYS_IDLE_MODE){
				
    				set_play_status_led(LED_SPARK_STOP);
				func_msg_hdlr(S_FUNC,SYS_IDLE_MODE);

	       	 	put_msg_lifo(MSG_CHANGE_WORK_MODE);

#ifdef UART_ENABLE
    					printf(" ---> erp2_func_pwrdn MSG_CHANGE_WORK_MODE\r\n");
#endif

			}    			
		}
	}
	else{
		
		erp2_func_pwrdn=0;
		erp2_timer=0;
	}

}
#endif

#ifdef AD_DETECT_FUNC

#define AD_DETECT_NOKEY		((0xff40-0xe840)/2+0xF140)		//==FDC0
#define AD_RES_PULL_UP			22		/// 22K
#define AUX_RES_VALUE			220		/// 100K
#define HP_RES_VALUE			680		/// 220K
#define TWO_RES_VALUE			((AUX_RES_VALUE*HP_RES_VALUE)/(AUX_RES_VALUE+HP_RES_VALUE))

#define AD_VOLT_FOR_DET    	(((255*TWO_RES_VALUE)/(TWO_RES_VALUE+AD_RES_PULL_UP))-6)
#define AD_VOLT_FOR_DET		(0xD0)
#define AD_VOLT_FOR_AUX		(0xE0)
#define AD_VOLT_FOR_HP			(0xEF)

bool ad_detect_hdlr(u16 adc_value)
{
	u8 adc_volt=0;
	
    	if (adc_value > AD_DETECT_NOKEY){
			
#ifdef USE_ADKEY_DETECT_AUX						
		 	if (aux_online)
	        	{
				det_timer_aux =0;
	            		put_msg_lifo(MSG_AUX_OUT);
	            		aux_online = 0;
	        	}
#endif	

#ifdef USE_ADKEY_DETECT_HP		
			if(earphone_plugged){
				det_timer_hp =0;
				earphone_plugged =0;
			}
#endif		
		return 1;
	}
	else{

		adc_volt = (u8)(adc_value>>8);

#if 0
		my_printf(" --->ad_detect_hdlr :  adc_volt  %x \r\n",(u16)adc_volt);
		my_printf(" --->ad_detect_hdlr :  AD_VOLT_FOR_DET  %x \r\n",(u16)AD_VOLT_FOR_DET);
		my_printf(" --->ad_detect_hdlr :  AD_VOLT_FOR_HP  %x \r\n",(u16)AD_VOLT_FOR_HP);
		my_printf(" --->ad_detect_hdlr :  AD_VOLT_FOR_AUX  %x \r\n",(u16)AD_VOLT_FOR_AUX);


		my_printf(" --->ad_detect_hdlr :  earphone_plugged  %x \r\n",(u16)earphone_plugged);
		my_printf(" --->ad_detect_hdlr :  aux_online  %x \r\n",(u16)aux_online);
#endif
			if(adc_volt>AD_VOLT_FOR_DET){

				if(adc_volt>AD_VOLT_FOR_HP){

#ifdef USE_ADKEY_DETECT_AUX						
				 	if (aux_online)
			        	{
						det_timer_aux =0;
			            		put_msg_lifo(MSG_AUX_OUT);
			            		aux_online = 0;
			        	}
#endif		
					
#ifdef USE_ADKEY_DETECT_HP
					if(det_timer_hp++>20){

						det_timer_hp =0;
						if(!earphone_plugged){
							earphone_plugged =1;
						}
					}
#endif				
				}
				else if(adc_volt>AD_VOLT_FOR_AUX){

#ifdef USE_ADKEY_DETECT_HP		
					if(earphone_plugged){
						det_timer_hp =0;
						earphone_plugged =0;
					}
#endif		
					
#ifdef USE_ADKEY_DETECT_AUX				
					if(det_timer_aux++>20){
						det_timer_aux =0;
				            if (!aux_online)
				            {
				                put_msg_lifo(MSG_AUX_IN);
				                aux_online = 1;
				            }
					}
#endif				
				}
				else{

#ifdef USE_ADKEY_DETECT_HP
					if(det_timer_hp++>10){

						det_timer_hp =0;

						if(!earphone_plugged){
							earphone_plugged =1;
						}
					}
#endif				

#ifdef USE_ADKEY_DETECT_AUX				
					if(det_timer_aux++>10){
						det_timer_aux =0;
				            if (!aux_online)
				            {
				                put_msg_lifo(MSG_AUX_IN);
				                aux_online = 1;
				            }
					}
#endif				
				}

			return 1;	// NO KEY
		}	
	}

	return 0;	// ADKEY
}

#endif

#ifdef AD_MODE_FUNC
extern const u16 ad_key_table[];
static u8 adc_mode_reg=0;
void init_adc_mode_switcher(void)
{
	adc_mode_reg=0xFF;
}
void adc_mode_switcher(void)
{
       u8 mod_idx=0;
	u16 adc_mode_volt=0;
	
	adc_mode_volt=(AD_var.wADValue[AD_CH_MODE]);

	for (mod_idx = 0; mod_idx < 8;mod_idx++)
	{
	       if (adc_mode_volt > ad_key_table[mod_idx])
	         break;
	}

	mod_idx =8- mod_idx;
	
	if(mod_idx != adc_mode_reg ){

		adc_mode_reg = mod_idx;

#ifdef AD_MODE_FUNC_DEBUG
		my_printf(" --->adc_mode_switcher :  adc_mode_reg  %x \r\n",(u16)adc_mode_reg);

#endif

		if(adc_mode_reg  >=AD_MODE_ERROR ){
			return;
		}
		
		if(adc_mode_reg == AD_MODE_MUSIC){
			if(work_mode > SYS_SD_MODE){
				work_mode = SYS_USB_MODE;
			       put_msg_lifo(MSG_CHANGE_WORK_MODE);				
			}
		}
		else if(adc_mode_reg == AD_MODE_FM){

			if(work_mode != SYS_RADIO_MODE){
				work_mode = SYS_RADIO_MODE;
				radio_band_set(FM_MODE);
			       put_msg_lifo(MSG_CHANGE_WORK_MODE);							
			}			
		}
		else if(adc_mode_reg == AD_MODE_WM){
			
			if(work_mode != SYS_RADIO_MODE){
				work_mode = SYS_RADIO_MODE;
				radio_band_set(MW_MODE);
			       put_msg_lifo(MSG_CHANGE_WORK_MODE);				
			}
			else{				
				radio_band_set(MW_MODE);
			       put_msg_lifo(MSG_RADIO_BAND_SWITCH);				
			}
		}
		else if(adc_mode_reg == AD_MODE_AUX){
			if(work_mode != SYS_AUX_MODE){
				work_mode = SYS_AUX_MODE;
			       put_msg_lifo(MSG_CHANGE_WORK_MODE);				
			}				
		}		
	}
	
}
#endif





































#ifdef EVENT_50MS_HANDLER_ENABLE
void event_50ms_hdlr(void) AT(CSTART)
{
#ifdef PHONE_DETECTION_THREAD_ENABLE
	if(get_event_detect_status(PHONE_PLUG_THREAD)){
		ext_pa_mute(PA_MUTE);
	}
	else{
		ext_pa_mute(PA_UNMUTE);
	}
#endif	

#ifdef AD_DETECT_FUNC
#ifdef USE_ADKEY_DETECT_HP
	if(earphone_plugged){
		ext_pa_mute(PA_MUTE);
	}
	else{
		ext_pa_mute(PA_UNMUTE);
	}
#endif
#endif

#ifdef AD_MODE_FUNC
	adc_mode_switcher();
#endif

}
#endif

void event_halfsecond_hdlr(u8 msg) AT(CSTART)
{
	if(msg != MSG_HALF_SECOND)return;

#ifdef USE_BAT_MANAGEMENT
	bmt_hdlr();
#endif

#ifdef USB_ERP2_FUNC
	erp2_func_hdlr();
#endif

#ifdef JK_SM_001_1096A_V001
	if( (device_online & BIT(DEVICE_UDISK))>0){

		if(device_active==DEVICE_UDISK){
			set_play_status_led(LED_SPARK_ON);
		}
		else{
			set_play_status_led(LED_SPARK_NOR);
		}
	}
	else{
		set_play_status_led(LED_SPARK_STOP);
	}

	if( (device_online & BIT(DEVICE_SDMMCA))>0){

		if(device_active==DEVICE_SDMMCA){
			set_play_status_led_id2(LED_SPARK_ON);
		}
		else{
			set_play_status_led_id2(LED_SPARK_NOR);
		}
	}
	else{
		set_play_status_led_id2(LED_SPARK_STOP);
	}
#endif
}
