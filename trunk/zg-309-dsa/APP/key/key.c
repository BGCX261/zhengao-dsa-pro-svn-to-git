/*--------------------------------------------------------------------------*/
/**@file   key.c
   @brief  ������Ϣɨ��ģ��
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "Custom_config.h"
#include "key.h"
#include "uart.h"
#include "adkey.h"
#include "irff00.h"
#include "dsp.h"
#include "dac.h"
#include "my_IR_key.h"
#include "tunch_key.h"

extern _xdata SYS_WORK_MODE  work_mode;
extern u8 _idata last_work_mode;
extern DECODER_MSG _xdata *dec_msg;

extern bit kv_flag;
u16 _xdata kv_rate_tab[6] _at_ 0x011E;
u8 _code lifo_msg_tab[] = 						//�����ȼ���Ϣ����Ҫ����ȳ�
{
    MSG_MUSIC_FFR_DONE,
};

extern _code MY_IR_KEY_STRUCT My_IRTab[];       /*user code is 0xFF*/
extern u8 get_my_IR_key_MAX();
static u8 _xdata MAX_IR_KEY = 0;

bool key_mode;			  ///<������Ϣ������
u16 _idata user_code;     ///<����ң����ȡ���û���
u8 _idata irda_state;     ///<IR��ǰ״̬
u16 _idata irda_data;     ///<IR��ȡ��ȡ��������
u16 _idata adkey_value1;  ///<adkey ����ֵ

u8 _xdata adc_vdd12;	  ///<�ο���ѹVDD1.25v�Ĳ���ֵ
u8 _xdata adc_vddio;	  ///<VDDI0�Ĳ���ֵ

bool key_voice_en;		  ///<������ʹ��λ
bool key_tab_sel=0;
//u8  (_code * adkey1_table)[10];	   ///<ADKEY ���Ա�
//u8  (_code * remote_table)[21];	   ///<ң�ز��Ա�

u16 _xdata key_voice_tab[3] _at_ 0x0118; ///<�����������밴��������Ӧ���Ȳ���

//u16 _code kv_sample_rate_tab[6] _at_ 0x7fa0;//= {0x4a3,0x4ae,0x493,0x4a2,0x481,0x492};

/**/


const u8 _code event_msg_table[] =
{
    MSG_USB_DISK_IN,
    MSG_USB_DISK_OUT,
    MSG_USB_PC_IN,
    MSG_USB_PC_OUT,
    MSG_SDMMC_IN,
    MSG_SDMMC_OUT,
    MSG_PC_MUTE,
    MSG_PC_UNMUTE,
    MSG_AUX_IN,
    MSG_AUX_OUT,
    MSG_ALM_ON
};
/*----------------------------------------------------------------------------*/
/**@brief  ��������ʼ������
   @param  ��
   @return ��
   @note   void kv_init(void)
*/
/*----------------------------------------------------------------------------*/
#define KV_441K_ADDR_STR  0x0493
#define KV_441K_ADDR_END  0x04a2
#define KV_48K_ADDR_STR	  0x0481
#define KV_48K_ADDR_END	  0x0492
#define KV_32K_ADDR_STR	  0x04a3
#define KV_32K_ADDR_END	  0x04ae
void kv_init(void)
{
    key_voice_tab[0] = 2000;///<��������
    key_voice_tab[1] = 16384;///<��������
    key_voice_tab[2] = 100;///<��������Ӧ����
////////////////
    kv_rate_tab[0] = KV_441K_ADDR_STR;
    kv_rate_tab[1] = KV_441K_ADDR_END;
////////////////
    kv_rate_tab[2] = KV_48K_ADDR_STR;
    kv_rate_tab[3] = KV_48K_ADDR_END;
////////////////
    kv_rate_tab[4] = KV_32K_ADDR_STR;
    kv_rate_tab[5] = KV_32K_ADDR_END;
    bsp_kv_init();
}
/*----------------------------------------------------------------------------*/
/**@brief  �������壬�ڲ����ʲ�����32/44.1/48kHz����ʱ������Ĭ�Ϸ���
   @param  ��
   @return ��
   @note   void alarm_tone(void)
*/
/*----------------------------------------------------------------------------*/
void alarm_tone(void)
{
    send_alm_voice();
}

/*----------------------------------------------------------------------------*/
/**@brief  ����DSP����������������
   @param  ��
   @return ��
   @note   void set_key_tone(void)
*/
/*----------------------------------------------------------------------------*/
void set_key_tone(void)
{
	key_voice_en =0;
    if (!key_voice_en)
    {
        return ;
    }
    fun_send_kv();
}
/*----------------------------------------------------------------------------*/
/**@brief  ��ȡ��Ϣ�ص���Ϣ,�¼�����ת��Ϊ��Ϣ
   @param  ��
   @return ��Ϣ
   @note   u8 app_get_msg(void)
*/
/*----------------------------------------------------------------------------*/
u8 app_get_msg(void)
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
        msg = get_msg();

    if (msg == NO_MSG)
    {
        SYS_IDLE();
    }

    return msg;
}

/*----------------------------------------------------------------------------*/
/**@brief  AD������ʼ��
   @param  ��
   @return ��
   @note   void adckey_init(void)
*/
/*----------------------------------------------------------------------------*/
static void adckey_init(void)
{
#if defined(ADKEY_USE_PORT_P06)
    P0PD &= ~(BIT(6));
    P0IE = ~(BIT(6));
    P0DIR |= BIT(6);
#else
    P0PD &= ~(BIT(7));
    P0IE = ~(BIT(7));
    P0DIR |= BIT(7);
#endif	
    ADCCON = ADC_VDD_12;
//	ADCCON = 0xff;					//select P07 for ADC key

}
/*----------------------------------------------------------------------------*/
/**@brief  ������ʼ��
   @param  ��
   @return ��
   @note   void key_init(void)
*/
/*----------------------------------------------------------------------------*/
void key_init(void)
{
    adckey_init();
     MAX_IR_KEY = get_my_IR_key_MAX();
}
/*----------------------------------------------------------------------------*/
/**@brief  �������ܱ�ѡ��
   @param  sel:���
   @return ��
   @note   void key_table_sel(u8 sel)
*/
/*----------------------------------------------------------------------------*/
#pragma disable
void key_table_sel(u8 sel)
{
    if (sel == 0)
    {
    	 key_tab_sel =0;
        //adkey1_table = adkey1_msg_music_table;
        //remote_table = irff00_msg_music_table;
    }
    else
    {
	    key_tab_sel =1;
        //adkey1_table = adkey1_msg_fm_table;
        //remote_table = irff00_msg_fm_table;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  LDO IN �������
   @param  ��
   @return ��
   @note   u8 ldoin_voltage(void)
*/
/*----------------------------------------------------------------------------*/
u8 ldoin_voltage(void)
{
    return 	((((u16)adc_vddio*248+5)/10)/adc_vdd12);
}

/*----------------------------------------------------------------------------*/
/**@brief  ADCѭ��ɨ����� 2MS������һ��,�ֱ�ɨ��VDD1.2
   @param  ��
   @return ��
   @note   void adc_scan(void)
*/
/*----------------------------------------------------------------------------*/
void adc_scan(void)
{
    static u8 cnt;

    if (cnt == 0)
    {
        adc_vdd12 = ADCDATH;//
        //adc_vdd12l = ADCDATL;
        ADCCON = ADC_LDOIN;
    }
    else if (cnt == 1)
    {
        adc_vddio = ADCDATH;//
        //adc_vddiol = ADCDATL;//
#if defined(ADKEY_USE_PORT_P06)
        ADCCON = ADC_KEY_IO6; //
        P0IE = ~(BIT(6));	 
#else        
        ADCCON = ADC_KEY_IO7; //
        P0IE = ~(BIT(7));	 
#endif		
    }
    else if (cnt == 2)
    {
        ((u8 *)(&adkey_value1))[0] = ADCDATH;
        ((u8 *)(&adkey_value1))[1] = ADCDATL;
        ADCCON = ADC_VDD_12;
    }
    else
    {
        cnt = 0;
    }
    cnt++;
    if (cnt >= ADC_MAX_USED)
        cnt = 0;
}


/*----------------------------------------------------------------------------*/
/**@brief  ��ȡ��ֵkeyDetect
   @param  ��
   @return ��
   @note   u8 keyDetect(void)
*/
/*----------------------------------------------------------------------------*/
u8 keyDetect(void)
{
    u8 keyTemp=0;
    u8 key_index=0;

    keyTemp = NO_KEY;
    if (irda_state == 32)
    {
        if (((irda_data & 0xff) + ((irda_data >> 8) & 0xff)) != 0xff)
        {
            irda_state = 0;
            return keyTemp;
        }

        if (IR_FF00 == user_code)
        {
       #if 0
            	keyTemp = IRTabff00[(u8)irda_data];
       #else
		for(key_index = 0;key_index <MAX_IR_KEY;key_index++){
	            if((My_IRTab[key_index].IR_Key_Value)==(irda_data & 0xff)){
				keyTemp = (My_IRTab[key_index].APP_Key);
			        //printf(" IR  00000000keyDetect %d  \r\n",(u16)keyTemp);
				break;
		     }
		}     
	#endif
        }
        else if (0xfd02 == user_code)
        {
		for(key_index = 0;key_index <MAX_IR_KEY;key_index++){
	            if((My_IRTab[key_index].IR_Key_Value)==(irda_data & 0xff)){
				keyTemp = (My_IRTab[key_index].APP_Key);
			        //printf(" IR  11111111keyDetect %d  \r\n",(u16)keyTemp);
				break;
		     }
		}
	}

    }

    return keyTemp;
}


/*----------------------------------------------------------------------------*/
/**@brief  AD����ת��
   @param  ��
   @return ��
   @note void adkey2(u16 key_value)
   @note   ADkey group2 ����ֵ
   Range��				   voltage:
   @note   0xe900~0xe840   3.037
   @note   0xd200~0xd180   2.739
   @note   0xb380~0xb300   2.346
   @note   0x9980~0x9940   2.012
   @note   0x8600~0x8580   1.755
   @note   0x6800~0x6780   1.362
   @note   0x4ac0~0x4a40   0.982
   @note   0x3800~0x3780   0.737
   @note   0x1e80~0x1e40   0.406
   @note   0
*/
/*----------------------------------------------------------------------------*/

u8 adkey1(u16 key_value)
{
    u8 i;

    if (key_value > ADKEY1)
    {
        return NO_KEY;
    }
    else
    {
        for (i = 0; i < 9; i++)
            if (key_value > adkey1_check_table[i])
                break;
    }

    return i;
}

/*----------------------------------------------------------------------------*/
/**@brief  ����ɨ�赽�İ������������̰���HOLD����״̬����������� ��������Ҳ�����ﴦ��
   @param  ��
   @return ��
   @note void keyScan(void)
   @note ������ADKEY�����
   @note VOL-(0v): 0
   @note VOL+(0.43v): 0x21
   @note PREV(0.82v): 0x3F
   @note NEXT(1.237v): 0x5F
   @note PLAY(1.616v): 0x7C
   @note FM/MP3(2.05v): 0x9E
   @note EQ(2.50v): 0xC1
   @note PlayMode(2.93v): 0xE2
*/
/*----------------------------------------------------------------------------*/
void keyScan(void)
{
    static xd_u8 last_key;  ///<��һ�ΰ���ɨ����
    static xd_u8 key_counter;   ///<������Ч�İ���ɨ�����

    xd_u8 keyTemp;
    xd_u8 key_style = NO_KEY;


    keyTemp = adkey1(adkey_value1);
    if (keyTemp == NO_KEY)
    {
        //keyTemp = tunch_value();
    }
    if (keyTemp == NO_KEY)
    {
        keyTemp = keyDetect();
        if (keyTemp != NO_KEY)
        {
            key_mode = 1;														//����Ϊң�ذ���
        }
    }
    else
        key_mode = 0;															//����ΪAD����

    if ( (NO_KEY == keyTemp) /*|| (keyTemp != last_key)*/ )
    {
        if (key_counter >= KEY_LONG_CNT)			 //����̧��
        {
            key_style = 3;

        }
        else if (key_counter >= KEY_BASE_CNT)		//�̰�̧��
        {
            key_style = 0;
        }
        key_counter = 0;
    }
    else if (keyTemp != last_key)
    {
        key_counter = 0;
        put_msg_fifo(MSG_KEY_CHANGE);
    }
    else
    {
        key_counter++;
        if (KEY_BASE_CNT == key_counter)			//ȥ��
        {
            //key_style = 0;
            set_key_tone();
        }
        else if (KEY_LONG_CNT == key_counter)				//����
        {
            set_key_tone();
            key_style = 1;
        }
        else if ((KEY_LONG_CNT + KEY_HOLD_CNT) == key_counter)			//����
        {
            set_key_tone();
            key_style = 2;
            key_counter = KEY_LONG_CNT;
        }
    }
    if ((NO_KEY != last_key) && (key_style != NO_KEY))
    {
        u8 key, i;

        set_brightness_all_on();

        if (key_mode == 0)
        {
        	if(key_tab_sel==0){
	            key = adkey1_msg_music_table[key_style][last_key];
        	}
		else{
	            key = adkey1_msg_fm_table[key_style][last_key];
		}
        }
        else if (key_mode == 1)									//ң��
        {
          	if(key_tab_sel==0){
	            key = irff00_msg_music_table[key_style][last_key];
          	}
		else{
	            key = irff00_msg_fm_table[key_style][last_key];
		}
        }

        if (key == NO_MSG)										//��Ч
            goto _exit_keyScan;

        for (i = 0; i < sizeof(lifo_msg_tab); i++)
        {
            if (key == lifo_msg_tab[i])
            {
                put_msg_lifo(key);
                flush_low_msg();
                goto _exit_keyScan;
            }
        }
        put_msg_fifo(key);

    }
_exit_keyScan:
    last_key = keyTemp;
}

/*
5062.5 13.5ms
4218.75 11.25ms
36281.25 96.75ms
421.875  1.125ms
843.75   2.25ms
*/

/*----------------------------------------------------------------------------*/
/**@brief  ����ң���жϴ�����
   @param  ��
   @return ��
   @note void timer3isr(void)
*/
/*----------------------------------------------------------------------------*/
#if 1
void timer3isr(void)
{
    u8 counter;
    u16 ircnt;

    PSW = 0x08;
    DPCON = 0;

    if (T3CON & BIT(6))
    {
        T3CON &= ~BIT(6);

        if ((P5PU & 0x80))
            return;

        ircnt = T3PWMH ;
        ircnt <<= 8;
        ircnt |= T3PWML;
        T3CNTL = 0;
        T3CNTH = 0;
        counter = ((ircnt) / 375);

    }
    else
    {
        T3CON &= ~BIT(7);
        irda_state = 0;
        return;
    }


    if (counter == 1)
    {
        irda_data >>= 1;
        irda_state++;
        goto _exit_timer2;
    }
    else if (counter == 2)
    {
        irda_data >>= 1;
        irda_state++;
        irda_data |= 0x8000;
    }
//    else if ((counter == 13) || (counter == 11) || (counter == 96) || ((counter >= 31) && (counter <= 49)))
//    {
//        goto _exit2_timer2;
//    }
    else if ((counter == 13) || (counter < 9) || (counter > 96))
    {
        irda_state = 0;
    }
_exit_timer2:
    if (irda_state == 16)
    {
        user_code = irda_data;
    }
}
#endif
