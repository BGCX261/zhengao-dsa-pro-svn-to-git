/*--------------------------------------------------------------------------*/
/**@file    msgfor_hot.c
   @brief   HOT 消息处理模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"

#include "msgfor_hot.h"
#include "disp.h"
#include "main.h"
#include "device.h"
#include "eq.h"
#include "dac.h"
#include "rtc_api.h"
#include "fm_api.h"

extern void disk_remove_deal_for_music(void);

#ifdef AC_SLAVE_ENABLE
extern void DSA_init(void);
extern void DSA_if_hdlr(void);
extern bool DSA_GETHERING_DATA_ENABLE_BIT;
extern xd_u8 DSA_SEL_DEV,disk_toc_ok;
#endif

_xdata SYS_WORK_MODE  work_mode;
extern u8 _idata last_work_mode;
extern bool input_number_en;
extern bool eq_change_en;
extern bool play_mode_change_en;

extern u8 given_device;
extern u16 given_file_number;
extern u8 given_file_method;
extern u8 eq_mode;
extern u8 play_mode;
extern u8  main_menu, cur_menu, main_menu_conter;

#ifdef MATRIX_KEY_ENABLE
bool key_scan_en=1;
#endif

static bool supper_mute_lock=0;

u16 input_number;	 ///<输入的数字的实际值
bool vol_change_en;	 ///<音量修改允许位

bool get_super_mute_lock()
{
	return supper_mute_lock;
}
void clear_super_mute_lock()
{
	 ext_amp_mute(0);	
	supper_mute_lock =0;
}
void sys_mute_hdlr()
{
	supper_mute_lock=~supper_mute_lock;

	if(supper_mute_lock){
		ext_amp_mute(1);
	       dac_mute_control(1,1);					//调节音量时，自动UNMUTE
	}
	else{		
	       dac_mute_control(0,1);					//调节音量时，自动UNMUTE
		ext_amp_mute(0);
	}
}
#if defined(USE_MANUAL_IDLE_FUNC)||defined(IPONE_INDEPENDENT_MODE)
#define MAX_FUNC_LIST 		IDLE+1
#else
#define MAX_FUNC_LIST 		IDLE
#endif
static xd_u16 Sys_Func_List=0;

void Add_Func_To_List(DEV_ON_LIST Dev)
{
	Sys_Func_List |=BIT(Dev);
	printf(" --->Add_Func_To_List %x \r\n",(u16)Sys_Func_List);

}
void Remov_Func_From_List(DEV_ON_LIST Dev)
{
	Sys_Func_List &=~(BIT(Dev));

	printf(" --->Remov_Func_From_List %x \r\n",(u16)Sys_Func_List);
	
}
void Set_Curr_Func(SYS_WORK_MODE curr_mod)
{
	work_mode = curr_mod;	
	Sys_Func_List =((curr_mod<<8)|(Sys_Func_List&0x00FF));	
	//printf(" --->Set_Curr_Func %x \r\n",(u16)Sys_Func_List);
	
}
void Init_Func_List()
{
	//sys_printf("Init_Func_List");
	Sys_Func_List=0;
	
	if((get_device_online_status()&0x02))
		Add_Func_To_List(USB_DEV);

	if((get_device_online_status()&0x01))
		Add_Func_To_List(SD_DEV);
		
       if(fm_chip_online_chk()){	

		Add_Func_To_List(FM_DEV);
 	    	//enter_fm_rev();  
		fm_rev_powerdown();
	}
		
#ifndef NOT_USE_LINE_IN_FUNC

#ifdef USE_LINE_IN_DETECT_FUNC
#ifdef AUX_DETECT_FUNC_WITH_MANUAL_SEL
	Add_Func_To_List(AUX_DEV);
#else
	delay_10ms(20);
	if(aux_online)
		Add_Func_To_List(AUX_DEV);
#endif	
#else	
#ifndef DONT_MOUNT_AUX_FUNC
		Add_Func_To_List(AUX_DEV);
#endif
#endif
#endif

#if defined(IPONE_INDEPENDENT_MODE)
		Add_Func_To_List(IPH_DEV);
#endif
#ifdef USE_RTC_FUNCTION
		Add_Func_To_List(RTC_DEV);
#endif

#ifdef USE_MANUAL_IDLE_FUNC
		Add_Func_To_List(IDLE);
#endif

#if defined(IPONE_DOCK_FUNC_ENABLE)
#if defined(IPHONE_DETECT_IN_USE)
	if(iphone_status){
		Set_Curr_Func(SYS_IPH);
	}
#endif
#endif
}
static SYS_WORK_MODE Next_Func()
{
	u8 i;
	//printf(" -111-->Sys_Func_List %x \r\n",(u16)Sys_Func_List);
	//printf(" -222-->CURR FUNC %x \r\n",(u16)((Sys_Func_List&0xFF00)));
	
	if((Sys_Func_List&0x0FF)>0)
	{
		for(i=(((Sys_Func_List&0xFF00)>>8)+1);i<MAX_FUNC_LIST;i++){
			//printf(" --%x->Next_Func --->BIT  %x \r\n",(u16)i,(u16)(BIT(i)));
			if((Sys_Func_List&(BIT(i)))>0){
				return i;
			}
		}				
		for(i=0;i<=((Sys_Func_List&0xFF0)>>8);i++)
			if((Sys_Func_List&(BIT(i)))>0){
				return i;
		}
	}
	
	return SYS_IDLE;
}
/*----------------------------------------------------------------------------*/
/**@brief   几个任务都会用到的消息集中处理的函数
   @param   key： 需要处理的消息
   @return  0：需要切换工作模式;
   @note    unsigned char I2C_sendbyte(unsigned char I2Cdata)
*/
/*----------------------------------------------------------------------------*/
void ap_handle_hotkey(u8 key)
{
    SYS_WORK_MODE mode_reg=0;

#ifdef MATRIX_KEY_ENABLE
	if(key_scan_en){
		key_scan_en =0;
		key_matrix_scan();
	}
#endif
#ifdef AC_SLAVE_ENABLE
	if(DSA_GETHERING_DATA_ENABLE_BIT){
		DSA_GETHERING_DATA_ENABLE_BIT =0;
		DSA_if_hdlr();
	}
#endif

    switch (key)
    {
    case MSG_POWER_DOWN:
	 Set_Curr_Func(SYS_IDLE);
      	 put_msg_lifo(MSG_CHANGE_WORK_MODE);
        put_msg_fifo(MSG_SYS_IDLE);	 
		 
	break;
    case MSG_MUTE_UNMUTE:
	sys_mute_hdlr();
	break;
    case MSG_USB_DISK_OUT:

	if(DSA_SEL_DEV==DEVICE_UDISK){

#ifdef AC_SLAVE_ENABLE
	DSA_init();
#endif		

        device_check();
	 Remov_Func_From_List(USB_DEV);
        //set_brightness_all_on();
        put_msg_lifo(MSG_DEVICE_REMOVED);
	}		
	break;
	
    case MSG_SDMMC_OUT:

	if(DSA_SEL_DEV==DEVICE_SDMMC0){

#ifdef AC_SLAVE_ENABLE
	DSA_init();
#endif		
        device_check();
	 Remov_Func_From_List(SD_DEV);
        //set_brightness_all_on();
        put_msg_lifo(MSG_DEVICE_REMOVED);

	}	
		
        break;
		
#if USB_DEVICE_ENABLE
    case MSG_USB_PC_IN:

        set_brightness_all_on();
        device_check();
	 Set_Curr_Func(SYS_USB_DEVICE);
        put_msg_lifo(MSG_CHANGE_WORK_MODE);        
	break;

    case MSG_USB_PC_OUT:
        set_brightness_all_on();
        break;
#endif
    case MSG_AUX_IN :
    	 Add_Func_To_List(AUX_DEV);
        set_brightness_all_on();
#if USB_DEVICE_ENABLE
        if ((SYS_AUX  != work_mode) && (work_mode != SYS_USB_DEVICE))
#else
        if (SYS_AUX != work_mode)
#endif
        {
	     Set_Curr_Func(SYS_AUX);
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
        }
        break;

    case MSG_AUX_OUT :
	 Remov_Func_From_List(AUX_DEV);
        set_brightness_all_on();
        break;

    case MSG_SDMMC_IN :
        device_check();

		
	if(DSA_SEL_DEV==DEVICE_SDMMC0){
		 //       put_msg_lifo(MSG_SDMMC_IN_SEL);
		//}
	}
	else{
		break;
	}
   case MSG_SDMMC_IN_SEL:		
	 Add_Func_To_List(SD_DEV);
	 Set_Curr_Func(SYS_MP3DECODE_SD);
        set_brightness_all_on();
        device_check();
	DSA_SEL_DEV=DEVICE_SDMMC0;
#if USB_DEVICE_ENABLE
        if (work_mode == SYS_USB_DEVICE)
            break;
#endif
#ifdef AC_SLAVE_ENABLE
	DSA_init();
#endif	

        given_file_method = PLAY_BREAK_POINT;
        given_device = DEVICE_SDMMC0;
        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        break;

    case MSG_USB_DISK_IN :

        device_check();
	//if(work_mode == SYS_MP3DECODE_USB){
	if(DSA_SEL_DEV==DEVICE_UDISK){
		//        put_msg_lifo(MSG_USB_DISK_IN_SEL);
		//}		
	}
	else{
		break;
	}
    case MSG_USB_DISK_IN_SEL:
	 Add_Func_To_List(USB_DEV);
	 Set_Curr_Func(SYS_MP3DECODE_USB);
	 DSA_SEL_DEV=DEVICE_UDISK;

#ifdef AC_SLAVE_ENABLE
	 DSA_init();
#endif	
        set_brightness_all_on();
        device_check();
        given_file_method = PLAY_BREAK_POINT;
        given_device = DEVICE_UDISK;
        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        break;

    case MSG_NEXT_WORKMODE:
		
#if 1
		mode_reg =Next_Func();
	        //printf(" ----->Next_Func %x -- \r\n",(u16)mode_reg);

		if(work_mode ==mode_reg){
			break;
		}
		else{
			work_mode = mode_reg;
		}
	        //printf(" ----->INFO_MODE %x -- \r\n",(u16)work_mode);

		Set_Curr_Func(work_mode);
	   
		if(work_mode==SYS_MP3DECODE_USB){
			
		        given_file_method = PLAY_BREAK_POINT;
		        given_device = DEVICE_UDISK;
		        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
			break;				
		}
		else if(work_mode==SYS_MP3DECODE_SD){

		        given_file_method = PLAY_BREAK_POINT;
		        given_device = DEVICE_SDMMC0;
		        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
			 break;
		}
		else if(work_mode==SYS_FMREV){
			
	 	}
	 	else if(work_mode==SYS_AUX){

		}
#if defined(IPONE_INDEPENDENT_MODE)
	 	else if(work_mode==SYS_IPH){

		}
#endif
		else if(work_mode==SYS_RTC){
		}
		else if(work_mode==SYS_IDLE){
			put_msg_lifo(MSG_SYS_IDLE);
		}
		
      		put_msg_lifo(MSG_CHANGE_WORK_MODE);	   
#else
        work_mode++;
        if (work_mode > MAX_WORK_MODE)
            work_mode = MUSIC_MODE;

        put_msg_lifo(MSG_CHANGE_WORK_MODE);
#endif		
        break;

    case MSG_VOL_UP:
        if (vol_change_en==0)
            break;
        dac_mute_control(0,1);					//调节音量时，自动UNMUTE
        write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_INC));
        disp_port(MENU_MAIN_VOL);
	 clear_super_mute_lock();
        break;

    case MSG_VOL_DOWN:
        if (vol_change_en==0)
            break;
        dac_mute_control(0,1);					//调节音量时，自动UNMUTE
        write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_DEC));
        disp_port(MENU_MAIN_VOL);
	 clear_super_mute_lock();
        break;

    case MSG_0:
    case MSG_1:
    case MSG_2:
    case MSG_3:
    case MSG_4:
    case MSG_5:
    case MSG_6:
    case MSG_7:
    case MSG_8:
    case MSG_9:
        if (!input_number_en)
            break;

        if (input_number > 999)
            input_number = 0;

        input_number = input_number * 10 + key;
        disp_port(MENU_INPUT_NUMBER);
        break;
    }
}
