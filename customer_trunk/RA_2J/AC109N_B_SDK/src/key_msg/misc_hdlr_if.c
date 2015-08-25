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
#include "LCD_SEG5X9.h"


#ifndef NOT_USE_IR_FUNC
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
#endif

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

		if(work_mode == SYS_RADIO_MODE){

			main_vol_L =main_vol_R=MAX_MAIN_VOL_R;
        		set_main_vol(MAX_MAIN_VOL_L, MAX_MAIN_VOL_R);
		}		
		else{

			main_vol_L = 26;
    			main_vol_R = 26;
        		set_main_vol(main_vol_L, main_vol_R);
		}
		mute_port_unmute();
		mute_flag=0;
	}
	else if(M_Type == PA_MUTE){

		mute_port_mute();	
       	set_main_vol(0, 0);
		mute_flag=1;
	}
#if 0	
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
#endif	

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
	u8 i=0;
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


#ifdef AD_MODE_FUNC
	init_adc_mode_switcher();
	for(i=0;i<9;i++){
		adc_mode_switcher();
		delay_n10ms(1);
	};
#endif

	charger_detect_gpio_init();

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
#ifdef BAT_LED_LCD_ICON
#include "LCD_SEG5X9.h"
#ifdef BAT_LOW_LEVEL_BLINK_ICON
static bool low_bat_blink=0;
#endif
void disp_bat_icon_buf(void)
{
	LCD_clear_icon(LCD_BAT_L2_ICON);
	LCD_clear_icon(LCD_BAT_L1_ICON);
	LCD_show_icon(LCD_BAT_SHELL_ICON);

	switch(batt_level)
	{
		case 0:
#if 1//def BAT_LOW_LEVEL_BLINK_ICON
			if(low_bat_blink){
				LCD_clear_icon(LCD_BAT_SHELL_ICON);				
			}
			else{
				LCD_show_icon(LCD_BAT_SHELL_ICON);
			}
			break;
#endif
		case 1:
			LCD_show_icon(LCD_BAT_L1_ICON);
			break;		
		case 2:
			LCD_show_icon(LCD_BAT_L1_ICON);			
			LCD_show_icon(LCD_BAT_L2_ICON);
		break;
	}
}
#endif

#ifdef BAT_CHARGER_IND_HLDR
void bat_charger_ind_hldr()
{
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

#if 1//def CHARGER_DETECTION_THREAD_ENABLE
	if(charger_detect_level()){

		if(LDO_IN_Volt>=adc_bat_volt[4]){
			batt_level=2;
		}
		else{
			batt_level++;
			if(batt_level>2)batt_level=0;
		}
#ifdef BAT_LED_LCD_ICON
		disp_bat_icon_buf();
		LCD_drive5X9_12();
	       //UI_menu(MENU_MAIN);
#endif
		
		return;
	}
#endif	

	//for(adc_volt_level =0; adc_volt_level<(sizeof(adc_bat_volt));adc_volt_level++){

		if(LDO_IN_Volt>adc_bat_volt[2]){
			batt_level = 2;
		}
		else if(LDO_IN_Volt>adc_bat_volt[1]){
			batt_level = 1;
		}
		else{
			low_bat_blink =1-low_bat_blink;
			batt_level = 0;
		}
	//}
#ifdef BAT_UART_DEBUG
    	my_printf(" --->bmt_hdlr :batt_level  %x \r\n",(u16)(batt_level));
#endif

#ifdef BAT_LED_LCD_ICON
	disp_bat_icon_buf();
	LCD_drive5X9_12();
#endif
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
//extern const u16 ad_key_table[];
//#include "ad_key.h"
xd_u8 adc_mode_reg=0;
xd_u8 mod_reg_filter=0;
void init_adc_mode_switcher(void)
{
	adc_mode_reg=0xFF;
}
void adc_mode_switcher(void)
{
       u8 mod_idx=0;
	u16 adc_mode_volt=0;

	if(work_mode == SYS_USB_DEVICE_MODE)return;
	
	adc_mode_volt=(AD_var.wADValue[AD_CH_MODE]);
#if 0
	for (mod_idx = 0; mod_idx < 8;mod_idx++)
	{
	       if (adc_mode_volt > ad_key_table[mod_idx])
	         break;
	}

	mod_idx =8- mod_idx;
#endif	
	if (adc_mode_volt > AD_ERROR_VAL){

		mod_idx = AD_MODE_ERROR;
	}
	else if (adc_mode_volt > AD_AUX_VAL){
		mod_idx = AD_MODE_AUX;
	}
	else if (adc_mode_volt > AD_MW_VAL){

		mod_idx = AD_MODE_MW;
	}
	else if (adc_mode_volt > AD_FM_VAL){
		mod_idx = AD_MODE_FM;
	}
	else {//if (adc_mode_volt > AD_MUSIC_VAL){

		mod_idx = AD_MODE_MUSIC;
	}

	
	if(mod_idx != adc_mode_reg ){

		mod_reg_filter++;
		if(mod_reg_filter==2){
			
			adc_mode_reg = mod_idx;
			mod_reg_filter=0;
		}
		else{
			return;
		}
#ifdef AD_MODE_FUNC_DEBUG
		my_printf(" --->adc_mode_switcher :  adc_mode_reg  %x \r\n",(u16)adc_mode_reg);

#endif
		LCD_backlight_turn_on();

              //flush_all_msg();
		
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
			else{

				radio_band_set(FM_MODE);
			       put_msg_lifo(MSG_RADIO_BAND_SWITCH);				

			}
		}
		else if(adc_mode_reg == AD_MODE_MW){
			
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
#ifndef NOT_USE_LINE_IN_FUNC	
		else if(adc_mode_reg == AD_MODE_AUX){
			if(work_mode != SYS_AUX_MODE){
				work_mode = SYS_AUX_MODE;
			       put_msg_lifo(MSG_CHANGE_WORK_MODE);				
			}				
		}		
#endif		
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

	LCD_backlight_turn_off();

#ifdef USE_BAT_MANAGEMENT
	bmt_hdlr();
#endif

#ifdef USB_ERP2_FUNC
	erp2_func_hdlr();
#endif

}
