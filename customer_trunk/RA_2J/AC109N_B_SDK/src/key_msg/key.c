/*--------------------------------------------------------------------------*/
/**@file    key.c
   @brief   ��������
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC109N
*/
/*----------------------------------------------------------------------------*/
#include "custom_config.h"
#include "key.h"
#include "irff00.h"
#include "ad_key.h"
#include "DAC.h"
#include "UI_API.h"
#include "play_file.h"
#include "main.h"
#include "clock.h"
#include "RTC_API.h"
#include "RTC_Mode.h"
#include "IRTC.h"
#include "misc_hdlr_if.h"
#include "my_IR_key.h"
#include "LCD_SEG5X9.h"

_no_init IR_CODE _idata IR_code;    //<����ң����Ϣ
_no_init AD_VAR _data AD_var;      //AD ����
_no_init static bool _bit key_type;
_no_init void (_near_func * _data key_msg_filter)(u8, u8);

const u8 ad_table[] AT(TABLE_CODE)= 
{
    ADC_CH_FOR_KEY,               ///<��4λΪ��ʱ����4λΪͨ��ѡ��
#ifdef BAT_MEASURE_USE_ADC_PORT    
    AD_CH_BAT_PORT,
#endif    
#ifdef AD_MODE_FUNC
    AD_CH_MODE_PORT,
#endif
    0xfc,
    0xfd,
    0xfe,
    0xff,
};

/*----------------------------------------------------------------------------*/
/** @brief:�¼���Ϣת����
    @param:
    @return:
    @author:Juntham
    @note:
*/
/*----------------------------------------------------------------------------*/
const u8 _code event_msg_table[] AT(TABLE_CODE)=
{
    MSG_USB_DISK_IN,
    MSG_USB_DISK_OUT,
    MSG_USB_PC_IN,
    MSG_USB_PC_OUT,
    MSG_SDMMCA_IN,
    MSG_SDMMCA_OUT,
    MSG_SDMMCB_IN,
    MSG_SDMMCB_OUT,
    MSG_PC_MUTE,
    MSG_PC_UNMUTE,
    MSG_AUX_IN,
    MSG_AUX_OUT,
    MSG_ALM_ON,
    MSG_PC_AUDIO_VOL,
    MSG_FM_SCAN_ALL_INIT
};
/*----------------------------------------------------------------------------*/
/**@brief   Music ģʽ������Ϣ���˴���
   @param   msg��������Ϣ
   @return  ��
   @author  Change.tsai
   @note    void music_msg_filter(u8 sel)
*/
/*----------------------------------------------------------------------------*/
_near_func void music_msg_filter(u8 key_status, u8 back_last_key) AT(KEY_CODE)
{
    u8 msg;
    
    if (key_type == KEY_TYPE_IR)
    {
        msg = irff00_msg_music_table[key_status][back_last_key];
    }
    else
    {
        msg = adkey_msg_music_table[key_status][back_last_key];
    }
    
    if ((work_mode == SYS_USB_MODE)||(work_mode == SYS_SD_MODE))            //������ģʽ���ã���ֻ��musicģʽ��Ҫ�˴���
    if ((msg == MSG_MUSIC_NEXT_FILE) || (msg == MSG_MUSIC_PREV_FILE))
    {
        put_msg_lifo(msg);
        user_exit_decoder();
        return;
    }
    
    put_msg_fifo(msg);
}

/*----------------------------------------------------------------------------*/
/**@brief   FM ģʽ������Ϣ���˴���
   @param   msg��������Ϣ
   @return  ��
   @author  Change.tsai
   @note    void fm_msg_filter(u8 sel)
*/
/*----------------------------------------------------------------------------*/
_near_func void fm_msg_filter(u8 key_status, u8 back_last_key) AT(KEY_CODE)
{
    u8 msg;
    
    if (key_type == KEY_TYPE_IR)
    {
        msg = irff00_msg_fm_table[key_status][back_last_key];
    }
    else
    {
        msg = adkey_msg_fm_table[key_status][back_last_key];
    }
    
#if 0
    if (msg == MSG_FM_SCAN_ALL_INIT)
    {
        put_event(EVENT_SCAN_ALL);
        return;
    }
#endif
    put_msg_fifo(msg);
}

/*----------------------------------------------------------------------------*/
/**@brief   �������ܱ�ѡ��
   @param   sel:
   @return  ��
   @author  Change.tsai
   @note    void key_table_sel(u8 sel)
*/
/*----------------------------------------------------------------------------*/
_near_func __monitor void key_table_sel(u8 sel) AT(KEY_CODE)
{
    if (sel == 0)
    {
        key_msg_filter = music_msg_filter;
    } 
    else
    {
        key_msg_filter = fm_msg_filter;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   ��ȡ��Ϣ�ص���Ϣ,�¼�����ת��Ϊ��Ϣ
   @param   ��
   @return  ��Ϣ
   @author  Change.tsai
   @note    u8 app_get_msg(void)
*/
/*----------------------------------------------------------------------------*/
_near_func u8 app_get_msg(void) AT(KEY_CODE)
{
    u8 event, msg;

    WDT_CLEAR();
    
    event = get_event();

    if (event != NO_EVENT)
    {
        clear_one_event(event);
        msg = event_msg_table[event];
    }
    else
        msg = get_msg_v10();

    //if (msg == NO_MSG)
    //{
    //}

    return msg;
}

/*----------------------------------------------------------------------------*/
/**@brief   IR ң�ذ�����Ż�ȡ����
   @param   ��
   @return  ����ң�ذ�����
   @author  Change.tsai
   @note    u8 IR_key(void)
*/
/*----------------------------------------------------------------------------*/
#ifndef NOT_USE_IR_FUNC
_near_func static u8 IR_key(void) AT(COMMON_CODE)
{
    u8 key = NO_KEY;

    if (IR_code.bState != 32)
        return key;

    if ((((u8 _idata*)&IR_code.wData)[0] ^ ((u8 _idata *)&IR_code.wData)[1]) == 0xff)
    {
        if (IR_code.wUserCode == USER_CODE_ID)
        {
            //key = IRTabFF00[(u8)IR_code.wData];
            key = get_ir_key_index((u8)(IR_code.wData&0xff));		
        }
    }
    else
    {
        IR_code.bState = 0;
    }

    return key;
}
#endif
#ifndef NO_ADKEY_FUNC  
/*----------------------------------------------------------------------------*/
/**@brief   A/D ������Ż�ȡ����
   @param   key_value��AD��ֵ
   @return  �������
   @author  Change.tsai
   @note    u8 AD_key(u16 key_value)
*/
/*----------------------------------------------------------------------------*/
_near_func static u8 AD_key(u16 key_value)  AT(COMMON_CODE)
{
    u8 key_number;

#ifdef AD_DETECT_FUNC

	if(ad_detect_hdlr(key_value)){
        	return NO_KEY;
	}
	
#else
    if (key_value > AD_NOKEY)
        return NO_KEY;
#endif

    for (key_number = 0; key_number < sizeof (ad_key_table) / sizeof (ad_key_table[0]); key_number++)
    {
        if (key_value > ad_key_table[key_number])
            break;
    }
    return key_number;
}

/*----------------------------------------------------------------------------*/
/**@brief   ����ȥ������������ȶ���ֵ
   @param   key����ֵ
   @return  �ȶ�����
   @author  Change.tsai
   @note    u8 keyFilter(u8 key)
*/
/*----------------------------------------------------------------------------*/
_near_func static u8 key_filter(u8 key) AT(COMMON_CODE)
{
    static u8 _data used_key = NO_KEY;
    _no_init static u8 _data old_key;
    _no_init static u8 _data key_counter;
    
    if (old_key != key)
    {
        key_counter = 0;
        old_key = key;
    }
    else
    {
        key_counter++;
        if (key_counter == KEY_BASE_CNT)
        {
            used_key = key;
        }
    }
    
    return used_key;
}

/*----------------------------------------------------------------------------*/
/**@brief   ����-��Ϣת������,��������˳�򣺶̰�̧��/����-->����
   @param   key���������
   @param   key_type����������
   @return  void
   @author  Change.tsai
   @note    void key2msg(u8 key, u8 key_type)
*/
/*----------------------------------------------------------------------------*/
_near_func void key_scan(void) AT(COMMON_CODE)
{
    static u8 _data last_key = NO_KEY;
    _no_init static u8 _data key_press_counter;
    u8 cur_key, key_status, back_last_key;

    cur_key = AD_key(AD_var.wADValue[AD_CH_KEY]);       //4AD��������

    if (cur_key == NO_KEY)
    {
#ifndef NOT_USE_IR_FUNC
        cur_key = IR_key();                             //4����Ƿ���ң��
        if (cur_key != NO_KEY)
        {
            key_type = KEY_TYPE_IR;
        }
#endif
    }
    else
    {
        key_type = KEY_TYPE_AD;
    }

    cur_key = key_filter(cur_key);                    //4���˰������൱��ȥ��
    
    back_last_key = last_key; 
    
    if (cur_key == last_key)                            //4��ʱ�䰴��
    {   
        if (cur_key == NO_KEY)
            return;
        
        key_press_counter++;
        
        if (key_press_counter == KEY_LONG_CNT)          //4����
        {
            LCD_backlight_turn_on();                
            key_status = KEY_LONG;
        }
        else if (key_press_counter == (KEY_LONG_CNT + KEY_HOLD_CNT))        //4����
        {
            LCD_backlight_turn_on();        
            key_status = KEY_HOLD;
            key_press_counter = KEY_LONG_CNT;
        }
        else
        {
            return;
        }
    }   
    else  //4cur_key = NO_KEY, ̧��
    {    
        last_key = cur_key; 
        
        if ((key_press_counter < KEY_LONG_CNT) && (cur_key == NO_KEY))      //4�̰�̧��
        {
            LCD_backlight_turn_on();
            key_press_counter = 0;
            key_status = KEY_SHORT_UP;
        }
        else
        {
            key_press_counter = 0;
            return;
        }
    }
#ifdef RTC_EN
    RTC_setting_var.bStandbyCnt = 0;
#endif
    LED_FADE_ON();
#ifdef KEY_TONE_INDICATOR_ENABLE
    kick_key_voice();
#endif
    key_msg_filter(key_status, back_last_key);
}
/*----------------------------------------------------------------------------*/
/**@brief   A/D ģ���ʼ��
   @param   void
   @return  void
   @author  Change.tsai
   @note    void AD_init(void)
*/
/*----------------------------------------------------------------------------*/
void AD_init(void) AT(CSTART)
{
    ADC_CON0 = BIT(4) | BIT(3) ;
#if 1
	adc_channel_init(ad_table[AD_CH_KEY]);
#ifdef BAT_MEASURE_USE_ADC_PORT    
	adc_channel_init(ad_table[AD_CH_CHG]);
#endif

#ifdef AD_MODE_FUNC    
	adc_channel_init(ad_table[AD_CH_MODE]);
#endif

#else
    P0PD &= ~BIT(7);
    P0PU &= ~BIT(7);
    P0DIR |= BIT(7);
    P0DIE &= ~BIT(7);                               //����AD key IO�����ģ����������
#endif    
    LDO_CON |= BIT(1);                              //��VBG
    key_msg_filter = music_msg_filter;              //Ĭ������
    ADC_CON1 = ad_table[0];
    ADC_CON0 |= BIT(7);
}

/*----------------------------------------------------------------------------*/
/**@brief   AD ɨ�躯��
   @param   void
   @return  void
   @author  Change.tsai
   @note    void ADC_scan(void)
*/
/*----------------------------------------------------------------------------*/
_near_func void ADC_scan(void) AT(COMMON_CODE)
{
    _no_init static _data u8 channel;
    
    /*get last set AD channel value*/
    AD_var.wADValue[channel++] = ((u16)ADC_DATH<<8) | ADC_DATL;

    if (channel == MAX_AD_CHANNEL)
        channel = 0;
    
    ADC_CON1 = ad_table[channel];
    ADC_CON0 |= BIT(7);         //[7]Start
}
#endif
