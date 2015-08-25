/*--------------------------------------------------------------------------*/
/**@file    FM_API.c
   @brief   FM 模式功能接口函数
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/

#include "custom_config.h"
#include "FM_API.h"
#include "fm_radio.h"

#ifdef RADIO_MODE_ENABLE


struct Str_Band Current_Band;

#ifdef	BK1080
#include "BK1080.c"
#endif

#ifdef RDA5807
#include "RDA5807.c"
#endif

#ifdef KT0830EG
#include "KT0830EG.c"
#endif

#ifdef QN8035
#include "QN8035.c"
#endif

#ifdef AR1019
#include "AR1019.c"
#endif

#ifdef KT_AMFM
#include "KT_AMFMdrv.c"
#endif

#include "hot_msg.h"
#include "msg.h"
#include "key.h"
#include "main.h"
#include "iic.h"
#include "UI_API.h"
#include "clock.h"



xd_u8 radio_band_mode=0;
extern bool kt_band_mode;		
extern bool radio_play_pause;

void (* const fm_init[])(void) AT(FM_TABLE_CODE) =
{

#ifdef	RDA5807
    init_RDA5807,
#endif

#ifdef	BK1080
    init_BK1080,
#endif

#ifdef	KT0830EG
    init_KT0830,
#endif

#ifdef	QN8035
    init_QN8035,
#endif

#ifdef	AR1019
    init_AR1019,
#endif

#ifdef	KT_AMFM
    KT_AMFM_WakeUp,
#endif

};

bool (* const fm_set_fre[])(u16) AT(FM_TABLE_CODE)=
{
#ifdef	RDA5807
    set_fre_RDA5807,
#endif

#ifdef	 BK1080
    set_fre_BK1080,
#endif

#ifdef	 KT0830EG
    set_fre_KT0830,
#endif

#ifdef	QN8035
    set_fre_QN8035,
#endif

#ifdef	AR1019
    set_freq_AR1019,
#endif

#ifdef	KT_AMFM
    KT_set_freq,
#endif

};


void (* const fm_power_off[])(void) AT(FM_TABLE_CODE)=
{
#ifdef	RDA5807
    RDA5807_PowerDown,
#endif

#ifdef	 BK1080
    BK1080_PowerDown,
#endif

#ifdef	 KT0830EG
    KT0830_PowerDown,
#endif

#ifdef	 QN8035
    QN8035_powerdown,
#endif

#ifdef	AR1019
    AR1019_powerdown,
#endif

#ifdef	KT_AMFM
    KT_AMFM_Standby,
#endif


};


bool (* const fm_read_id[])(void) AT(FM_TABLE_CODE)=
{
#ifdef	RDA5807
    RDA5807_Read_ID,
#endif

#ifdef	 BK1080
    BK1080_Read_ID,
#endif

#ifdef	 KT0830EG
    KT0830_Read_ID,
#endif

#ifdef	 QN8035
    QN8035_Read_ID,
#endif

#ifdef	AR1019
    AR1019_Read_ID,
#endif

#ifdef	KT_AMFM
    KT_AMFM_Read_ID,
#endif

};

#if 0
void (* const fm_mute[])(u8) AT(FM_TABLE_CODE)=
{
#ifdef	RDA5807
    RDA5807_mute,
#endif

#ifdef	BK1080
    BK1080_mute,
#endif

#ifdef	KT0830EG
    KT0830_mute,
#endif

#ifdef	 QN8035
    QN8035_mute,
#endif

#ifdef	AR1019
    AR1019_mute,
#endif

#ifdef	KT_AMFM
    KT_AMFM_set_mute,
#endif

};
#endif

bool chk_fm_dev_online(void) AT(FM_CODE)
{
#if 1
	fm_mode_var.bAddr = 0;
	return 1;
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief   FM模块初始化接口函数
   @param
   @return
   @note    void init_fm_rev(void)
*/
/*----------------------------------------------------------------------------*/
void init_fm_rev(void) AT(FM_CODE)
{
      (* fm_init[fm_mode_var.bAddr])();
}


/*----------------------------------------------------------------------------*/
/**@brief   关闭FM模块电源
   @param
   @return
   @note    void fm_rev_powerdown(void
*/
/*----------------------------------------------------------------------------*/
void fm_rev_powerdown(void) AT(FM_CODE)
{
    (* fm_power_off[fm_mode_var.bAddr])();
}


/*----------------------------------------------------------------------------*/
/**@brief   设置一个FM频点的接口函数
   @param   mode = 0: 使用frequency中的值，= 1:频点加1， = 2:频点减1
   @return  1：有台；0：无台
   @note    bool set_fre(u16 fre, u8 mode)
*/
/*----------------------------------------------------------------------------*/
bool set_fre(u8 mode) AT(FM_CODE)
{
    if(radio_play_pause){		

		radio_play_pause=0;
    	  	ext_pa_mute(PA_UNMUTE);
    }
	
    //fm_module_mute(1);

    if (mode == FM_FRE_INC)
    {
        fm_mode_var.wFreq=fm_mode_var.wFreq+Current_Band.Seek_Step;
    }
    else if (mode == FM_FRE_DEC)
    {
        fm_mode_var.wFreq=fm_mode_var.wFreq-Current_Band.Seek_Step;
    }
    if (fm_mode_var.wFreq > Current_Band.Band_Top)
        fm_mode_var.wFreq = Current_Band.Band_Bottom;
    if (fm_mode_var.wFreq < Current_Band.Band_Bottom)
        fm_mode_var.wFreq = Current_Band.Band_Top;

#ifdef FM_UART_DEBUG
    	my_printf(" --->set_fre  :wFreq  %4u  \r\n",(u16)(fm_mode_var.wFreq));
#endif

    save_curr_freq(fm_mode_var.wFreq);

    return (* fm_set_fre[fm_mode_var.bAddr])(fm_mode_var.wFreq);
}


/*----------------------------------------------------------------------------*/
/**@brief   FM模块Mute开关
   @param   flag：Mute使能位
   @return  无
   @note    void fm_module_mute(u8 flag)
*/
/*----------------------------------------------------------------------------*/
#if 0
void fm_module_mute(u8 flag) AT(FM_CODE)
{
    (* fm_mute[fm_mode_var.bAddr])(flag);
}
#endif
void save_radio_freq(u16 radio_freq,u8 ch)
{
	u8 freq_reg=0;

	freq_reg =(u8)radio_freq&(0x00FF);
	set_memory(ch, freq_reg);

	freq_reg =(u8)(radio_freq>>8);
	set_memory(ch+1, freq_reg);
}
u16 read_radio_freq(u8 ch)
{
	u16 freq_reg=0;

	freq_reg = get_memory(ch+1);
	freq_reg=freq_reg<<8;
	freq_reg |= get_memory(ch);

	return freq_reg;	
}
void save_curr_freq(u16 wFreq)
{
	save_radio_freq(wFreq , (MEM_CUR_FRE_BASE+kt_band_mode*2));
}
u16 read_curr_freq(void)
{
	return read_radio_freq((MEM_CUR_FRE_BASE+kt_band_mode*2));
}
void save_curr_channel(u8 c_channel)
{
	set_memory((MEM_CUR_CHAN_BASE+kt_band_mode),c_channel);
}
u8 read_curr_channel(void)
{
	return (get_memory((MEM_CUR_CHAN_BASE+kt_band_mode)));
}
void save_tatol_channel(u8 a_channel)
{
	set_memory((MEM_TATOL_CHAN_BASE+kt_band_mode),a_channel);
}
u8 read_tatol_channel(void)
{
	return (get_memory((MEM_TATOL_CHAN_BASE+kt_band_mode)));
}
void save_scan_station(u16 wFreq,u8 s_channel)
{
	//my_printf(" --->save_scan_station :   .wFreq  %4u \r\n",(u16)wFreq);

	if(kt_band_mode==0){
		save_radio_freq(wFreq,(s_channel*2+MEM_FM_CHAN_BASE));
	}
	else if(kt_band_mode==1){
		save_radio_freq(wFreq,(s_channel*2+MEM_AM_CHAN_BASE));
	}
	save_tatol_channel(s_channel);
}
void restore_station_from_ch(void)
{
	if(kt_band_mode==0){
		fm_mode_var.wFreq  = read_radio_freq(fm_mode_var.bFreChannel*2+MEM_FM_CHAN_BASE);
	}
	else if(kt_band_mode==1){
		fm_mode_var.wFreq  = read_radio_freq(fm_mode_var.bFreChannel*2+MEM_AM_CHAN_BASE);
	}

	//my_printf(" --->restore_station_from_ch :   .wFreq  %4u \r\n",(u16)fm_mode_var.wFreq);
	
	save_curr_channel(fm_mode_var.bFreChannel);
}

u16 const _code radio_preset[][10] =
{
	760,800,820,880,900,760,760,760,760,760,
	531,612,999,1404,1629,531,531,531,531,531,
};

void reset_radio_mem(u8 preset_band)
{
	u8 i=0;
	kt_band_mode = preset_band;
	
	for(i=0;i<10;i++){
		 save_scan_station(radio_preset[preset_band][i],(1+i));
	}
	
       save_curr_channel(1);
	save_curr_freq(radio_preset[preset_band][0]);
	
	
}
/*----------------------------------------------------------------------------*/
/**@brief  FM 模式信息初始化
   @param  无
   @return 无
   @note   void fm_info_init(void)
*/
/*----------------------------------------------------------------------------*/
void fm_info_init(void) AT(FM_CODE)
{
    /*------------System configuration-----------*/
    Sys_IRInput = 1;
    Sys_Volume = 1;
    key_table_sel(1);

    fm_mode_var.wFreq = read_curr_freq();

    if ((fm_mode_var.wFreq >Current_Band.Band_Top) ||(fm_mode_var.wFreq < Current_Band.Band_Bottom))
    {
        fm_mode_var.wFreq = Current_Band.Band_Bottom;
    }

	
    UI_menu(MENU_FM_MAIN);

    fm_mode_var.bTotalChannel = read_tatol_channel();

    if (!fm_mode_var.bTotalChannel)
    {
        fm_mode_var.bTotalChannel = 1;
    }

    fm_mode_var.bFreChannel = read_curr_channel();

    if (fm_mode_var.bFreChannel > fm_mode_var.bTotalChannel)					//台号为1;总台数为1
    {
        fm_mode_var.bFreChannel = 1;
        fm_mode_var.bTotalChannel = 1;
    }
    else if (!fm_mode_var.bFreChannel)
    {
        fm_mode_var.bFreChannel = 1;
    }

    set_fre(FM_CUR_FRE);
    //fm_module_mute(0);
    scan_mode = FM_SCAN_STOP;
    /*---------FM MAIN UI--------------*/
    SET_UI_MAIN(MENU_FM_MAIN);
    UI_menu(MENU_FM_MAIN);
}


/*----------------------------------------------------------------------------*/
/**@brief    全频段搜索
   @param    mode: 0全频段, 1:上一个有效频点， 2:下一个有效频点
   @return   0:未找到频点 1:搜索完成 2:退出FM模式 3：闹钟响起退出
   @note     u8 fm_scan(u8 mode)
*/
/*----------------------------------------------------------------------------*/
bool fm_scan(u8 mode) AT(FM_CODE)
{
    bool res;

#ifdef  QN8035
	if (qn8035_online)
        QN8035_setch(4);
#endif

	if (mode == FM_SCAN_PREV)
	    res = set_fre(FM_FRE_DEC);
	else
	    res = set_fre(FM_FRE_INC);

    UI_menu(MENU_FM_DISP_FRE);

    if (res)						//找到一个台
    {
    
        //fm_module_mute(0);

	 fm_mode_var.bFreChannel++;
	 if(fm_mode_var.bFreChannel>=10){
		 fm_mode_var.bTotalChannel=fm_mode_var.bFreChannel;
	 }
	 save_scan_station(fm_mode_var.wFreq,fm_mode_var.bFreChannel);
	 
	if(scan_mode ==FM_SCAN_ALL){
		UI_menu(MENU_FM_FIND_STATION);	 
	}
	
	 if(fm_mode_var.bFreChannel==20){
		scan_mode = FM_SCAN_END;
	 }
#if 0
       my_puts(" --------------------------------------->  \n");
	my_printf(" --->fm_scan :  fm_mode_var.bFreChannel  %4u \r\n",(u16)fm_mode_var.bFreChannel);
	my_printf(" --->fm_scan :  fm_mode_var.bFreChannel  %4u \r\n",(u16)fm_mode_var.bFreChannel);
	my_printf(" --->fm_scan :  fm_mode_var.bTotalChannel  %4u \r\n",(u16)Current_Band.Max_channel);
#endif		

	return true;            		
    }
	
    return false;
}

void radio_band_set(u8 band_mod)
{
	radio_band_mode=band_mod;
}
void radio_band_switcher(void)
{
    	ext_pa_mute(PA_MUTE);
	
	if(radio_band_mode==FM_MODE){

		KT_band_mode_switch_profile(FM_MODE);
		Current_Band.Max_channel = Current_Band.Band_Top-Current_Band.Band_Bottom;
	}
	else if(radio_band_mode==MW_MODE){

		KT_band_mode_switch_profile(MW_MODE);
		Current_Band.Max_channel = (Current_Band.Band_Top-Current_Band.Band_Bottom)/9;
	}

	fm_info_init();
	set_fre(FM_CUR_FRE);
	
}
#endif
