/*--------------------------------------------------------------------------*/
/**@file   DISP.C
   @brief    ��ʾģ��
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "disp.h"
#include "lcd.h"
#include "led.h"
#include "resource.h"
#include "my_printf.h"
#include "lcd.h"
#include "led.h"
#include "device.h"
#include "dac.h"
#include "rtc_mode.h"

extern u8 LCDPAGE,LCDCOLUMN;
extern u16 frequency;
extern u8 fre_channel, total_channel;
extern u16 input_number;
extern u8 _bdata device_online;

extern u16 given_file_number;
extern u8 device_active;
extern u8 eq_mode;
extern u8 play_mode;
extern u8 music_type;
extern DECODER_MSG _xdata *dec_msg;
extern FSAPIMSG _pdata fs_msg;
extern _xdata u8 LCDBuff[8][132];
extern u8 _xdata rtc_coordinate;
extern u8 _xdata alm_coordinate;
extern u8 _code rtc_coordinate_tab[][3];
extern u8 _code alm_coordinate_tab[][3];
extern _xdata SYS_WORK_MODE work_mode;
extern u8 _idata last_work_mode;
extern u8 _code alm_request_tab[][3];
extern u8 _xdata alm_request_cnt;

u8  main_menu;			///<��¼���ֲ�ͬģʽ�µ�������
u8  cur_menu;        	///<��ǰ����
u8  main_menu_conter;						///<�뿪�������ʱ��
bool flash_en;									///<��ʾ��������
u8 bright_counter;								///<��ʾ���ȵ�����ʱ
/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ�ӿڣ���ͬ����ʾ����ָ����ͬ�ĺ���
   @param  ��
   @return ��
   @note   void my_putchar(void)
*/
/*----------------------------------------------------------------------------*/
void my_putchar(u8 dat)
{
#if ((monitor == DISP_LCD_12832) || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        lcd_putchar(dat);
    }
#elif(monitor == DISP_LED5X7)
    {
        led_putchar(dat);
    }
#else
    {
        dat = dat;
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief  ����x����
   @param  x:������
   @return ��
   @note   void set_pos_x(u8 x)
*/
/*----------------------------------------------------------------------------*/
void set_pos_x(u8 x)
{
#if ((monitor == DISP_LCD_12832) || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        LCD_Buff_setx(x);
    }
#elif(monitor == DISP_LED5X7)
    {
        led_setx(x);
    }
#else
    {
        x = x;
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief  ����y����
   @param  y:������
   @return ��
   @note   void set_pos_y(u8 y)
*/
/*----------------------------------------------------------------------------*/
void set_pos_y(u8 y)
{
#if ((monitor == DISP_LCD_12832) || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        LCD_Buff_sety(y);
    }
#else
    {
        y = y;
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief  ��������
   @param  ��
   @return ��
   @note   void set_brightness(void)
*/
/*----------------------------------------------------------------------------*/
void set_brightness(u8 br)
{
#if ((monitor == DISP_LCD_12832) || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        br = br;
    }
#elif(monitor == DISP_LED5X7)
    {
        led_set_brightness(br);
    }
#else
    {
        br = br;
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief  �������Ƚ���
   @param  ��
   @return ��
   @note   void set_brightness_fade_out(void)
*/
/*----------------------------------------------------------------------------*/
void set_brightness_fade_out(void)
{
    if (bright_counter < 20)
    {
        bright_counter++;
        set_brightness(23 - bright_counter);
    }
}
/*----------------------------------------------------------------------------*/
/**@brief  ��������ȫ��
   @param  ��
   @return ��
   @note   void set_brightness_all_on(void)
*/
/*----------------------------------------------------------------------------*/
void set_brightness_all_on(void)
{
    set_brightness(16);
    bright_counter = 0;
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾͼƬ
   @param  id:��ʾͼƬ�����
   @return ��
   @note   void disp_bmp(u8 id)
*/
/*----------------------------------------------------------------------------*/
void disp_bmp(u8 id)
{
#if ((monitor == DISP_LCD_12832) || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        lcd_disp_bmp_via_id(id);
    }
#elif(monitor == DISP_LED5X7)
    {
        led_disp_icon(id);
    }
#else
    {
        id = id;
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ��˸ͼ��
   @param  id:��˸����
   @return ��
   @note   void disp_flash_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/
void disp_flash_icon(u8 id)
{
#if ((monitor == DISP_LCD_12832) || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        id = id;//lcd_disp_bmp_via_id(id);
    }
#elif(monitor == DISP_LED5X7)
    {
        led_flash_set(id);
    }
#else
    {
        id = id;
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ��ʼ��
   @param  ��
   @return ��
   @note   void init_display(void)
*/
/*----------------------------------------------------------------------------*/
void init_display(void)
{
#if ((monitor == DISP_LCD_12832) || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        init_dot_lcd_disp();
        disp_port(MENU_POWER_UP);

    }
#elif(monitor == DISP_LED5X7)
    {
        init_led_disp();
        disp_power_on();
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ�����ϵ�Ľ���
   @param  ��
   @return ��
   @note   void disp_power_on(void)
*/
/*----------------------------------------------------------------------------*/
void disp_power_on(void)
{
#if (monitor == DISP_LCD_12832)
    {
        my_printf("%c   %eHello%o");
    }
#elif ((monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%c   %Y\x02%eHello%o");
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%X\x0HI--");
    }
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ�ػ�����
   @param  ��
   @return ��
   @note   void disp_power_off(void)
*/
/*----------------------------------------------------------------------------*/
void disp_power_off(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("     %eOFF%o");
        delay_10ms(50);
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%c");
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾFM������
   @param  ��
   @return ��
   @note   void disp_fm_main(void)
*/
/*----------------------------------------------------------------------------*/
void disp_fm_main(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%c    %3b/%3b\n\n    FM %3u.%1bMHZ", fre_channel,total_channel,frequency / 10, (u8)(frequency % 10));
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%c%X\x0%4u%m%m", frequency, LED_FM_ICON, LED_1DOT_ICON);
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾFMƵ��
   @param  ��
   @return ��
   @note   void disp_fm_freq(void)
*/
/*----------------------------------------------------------------------------*/
void disp_fm_freq(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        disp_fm_main();
    }
#elif(monitor == DISP_LED5X7)
    {
        disp_fm_main();
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ��������FMƵ��
   @param  ��
   @return ��
   @note   void disp_fm_find_station(void)
*/
/*----------------------------------------------------------------------------*/
void disp_fm_find_station(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        disp_fm_main();
    }
#elif(monitor == DISP_LED5X7)
    {
        disp_fm_main();
        delay_10ms(50);
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾFMƵ��
   @param  ��
   @return ��
   @note   void disp_fm_channel(void)
*/
/*----------------------------------------------------------------------------*/
void disp_fm_channel(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        disp_fm_main();
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%4u", frequency);
    }
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ��������
   @param  num:��ֵ
   @return ��
   @note   void disp_input_number(u16 num)
*/
/*----------------------------------------------------------------------------*/
void disp_input_number(u16 num)
{
#if (monitor == DISP_LCD_12832)
    {
        my_printf("%c%e  %04u%o", num);
    }
#elif ( (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%c%e  %Y\x02%04u%o", num);
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%c%04u", num);
    }
#else
    {
        num = num;
    }
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ������
   @param  vol:��ʾ������ֵ
   @return ��
   @note   void disp_main_vol(u8 vol)
*/
/*----------------------------------------------------------------------------*/
void disp_main_vol(u8 vol)
{
#if (monitor == DISP_LCD_12832)
    {
        my_printf("%c%e  %m%02b%o", LCD_BMP_VOL, vol);
    }
#elif ((monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%c%Y\x02%e  %m%02b%o", LCD_BMP_VOL, vol);
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%c U%02b", vol);
    }
#else
    {
        vol = vol;
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ��Ƶ����ʱ�䣬��ʱ��
   @param  ��
   @return ��
   @note   void disp_music_play_time(void)
*/
/*----------------------------------------------------------------------------*/
void disp_music_play_time(void)
{
    u16 play_time;
    u8 min,sec;

    play_time = dec_msg->play_time;
    min = play_time / 60;
    sec = play_time % 60;

#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    my_printf("%a%Y\x0%X\x12%03b:%02b%o", min,sec);			//��ʾ����ʱ��
    play_time = dec_msg->total_time;		//��ʾ������ʱ��
    min = play_time / 60;
    sec = play_time % 60;
    my_printf("%a%Y\x01%X\x12%03b:%02b%o", min,sec);
#elif(monitor == DISP_LED5X7)
    my_printf("%c%02b:%02b", min, sec);
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief  ��ʾEQģʽͼ��1
   @param  ��
   @return ��
   @note   void disp_eq1(void)
*/
/*----------------------------------------------------------------------------*/
void disp_eq1(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%Y\x0%X\x33%m%o", eq_mode + LCD_BMP_EQ_NOR);
    }
#elif(monitor == DISP_LED5X7)
    {
        //my_printf(" U%02", vol);
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ����ģʽͼ��1
   @param  ��
   @return ��
   @note   void disp_play_mode1(void)
*/
/*----------------------------------------------------------------------------*/
void disp_play_mode1(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%Y\x0%X\x45%m%o", play_mode + LCD_BMP_PM_ALL);
    }
#elif(monitor == DISP_LED5X7)
    {
        //my_printf(" U%02", vol);
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾС�ļ���Ŀ���
   @param  ��
   @return ��
   @note   void disp_small_file_number(void)
*/
/*----------------------------------------------------------------------------*/
void disp_small_file_number(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%Y\x0%X\x52%a%04u%Y\x1%X\x52%a%04u%o", fs_msg.fileNumber,  fs_msg.fileTotal);
    }
#elif(monitor == DISP_LED5X7)
    {

    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ��Ƶ�����ʽ
   @param  ��
   @return ��
   @note   void disp_music_format(voids)
*/
/*----------------------------------------------------------------------------*/
void disp_music_format(void)
{

#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    if (music_type == IS_WAV)
    {
        my_printf("%Y\x0%X\x6a%m%Y\x00%X\x6d%k%03u%o", LCD_BMP_WAV, (u16)(dec_msg->bit_rate/(dec_msg->total_time*125)));
    }
    else if (music_type == IS_WMA)
    {
        my_printf("%Y\x0%X\x6a%m%Y\x00%X\x6d%k%03u%o",LCD_BMP_WMA, (u16)(dec_msg->bit_rate / 1000));
    }
    else
    {
        my_printf("%Y\x0%X\x6a%m%Y\x00%X\x6d%k%03u%o", LCD_BMP_MP3, (u16)(dec_msg->bit_rate * 2));
    }
#elif(monitor == DISP_LED5X7)
    if (music_type == IS_WAV)
    {
        my_printf("%m", LED_WAV_ICON);
    }
    else if (music_type == IS_WMA)
    {
        my_printf("%m", LED_WMA_ICON);
    }
    else
    {
        my_printf("%m", LED_MP3_ICON);
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ MUSIC������
   @param  ��
   @return ��
   @note   void diso_music_main(void)
*/
/*----------------------------------------------------------------------------*/
void disp_music_main(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        if (device_active == DEVICE_SDMMC0)
        {
            // my_printf("%c%m", LCD_BMP_SDMMC0);
            my_printf("%c%Y\x0%X\x2%m%o", LCD_BMP_SDMMC0);
        }
        else if (device_active == DEVICE_UDISK)
        {
            my_printf("%c%Y\x0%X\x2%m%o", LCD_BMP_UDISK);
        }

        disp_music_play_time();
        disp_eq1();
        disp_play_mode1();
        disp_small_file_number();
        disp_music_format();
        lcd_roll_disp(0);					//reset lcd roll conter
    }
#elif(monitor == DISP_LED5X7)
    {
        disp_music_play_time();
        disp_music_format();

        my_printf("%f", LED_ALL_NO_FLASH);

        if (device_online & DEVICE_SDMMC0)
        {
            my_printf("%m", LED_SD_ICON);
        }
        if (device_online & DEVICE_UDISK)
        {
            my_printf("%m", LED_UDISK_ICON);
        }

        if (device_active == DEVICE_SDMMC0)
        {
            my_printf("%f", LED_SD_ICON);
        }
        else if (device_active == DEVICE_UDISK)
        {
            my_printf("%f", LED_UDISK_ICON);
        }

    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ EQ
   @param  ��
   @return ��
   @note   void disp_eq(void)
*/
/*----------------------------------------------------------------------------*/
void disp_eq(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        disp_main_menu_refresh();
    }
#elif(monitor == DISP_LED5X7)
    {

        my_printf("%c EQ%02b", eq_mode);

    }
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ ����ģʽ
   @param  ��
   @return ��
   @note   void disp_play_mode(void)
*/
/*----------------------------------------------------------------------------*/
void disp_play_mode(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        disp_main_menu_refresh();
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%c P%02b", play_mode);	
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ�����
   @param  key:��ʾ����
   @return ��
   @note   void disp_cmd(u8 key)
*/
/*----------------------------------------------------------------------------*/
void disp_cmd(u8 key)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        lcd_cmd(key);
    }
#elif(monitor == DISP_LED5X7)
    {
        led_cmd(key);
    }
#else
    {
        key = key;
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾ��������
   @param  mode: 0,������ʾ��λ, 1,������ʾһ��
   @return ��
   @note   ��
*/
/*----------------------------------------------------------------------------*/
void disp_roll_ctrl(u8 mode)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        if (cur_menu ==	MENU_MUSIC_MAIN)
        {
            lcd_roll_disp(mode);
        }
    }
#else
    {
        mode = mode;
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ��ʾƵ��
   @param  ��
   @return ��
   @note   void diso_spec(void)
*/
/*----------------------------------------------------------------------------*/
void disp_spec(void)
{
#if ( (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%p");
    }
#elif(monitor == DISP_LED5X7)
    {
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  ˢ��������ʾ������
   @param  ��
   @return ��
   @note   ��
*/
/*----------------------------------------------------------------------------*/
void disp_main_menu_refresh(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    if (cur_menu ==	MENU_MUSIC_MAIN)
    {
        disp_music_play_time();
        disp_music_format();
        disp_eq1();
        disp_play_mode1();
        draw_lcd(0,2);
    }
    else if (main_menu == MENU_FM_MAIN)
    {
    }
#elif(monitor == DISP_LED5X7)
    {
        if (cur_menu ==	MENU_MUSIC_MAIN)
        {
            disp_music_main();
        }
        else if (main_menu == MENU_FM_MAIN)
        {
        }
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief ��ʾ����ģʽ�µ���ͣ����
   @param 	void
   @return  void
   @note  void disp_music_pause(void)
*/
/*----------------------------------------------------------------------------*/
void disp_music_pause(void)
{
#if (monitor == DISP_LCD_12832)
    {
        my_printf("%c%Y\x0   %ePAUSE%o");
    }
#elif ((monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%c%Y\x02   %ePAUSE%o");
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%cPAU");
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief ��ʾɨ���豸����
   @param 	void
   @return  void
   @note  void disp_scan_disk(void)
*/
/*----------------------------------------------------------------------------*/
void disp_scan_disk(void)
{
#if (monitor == DISP_LCD_12832)
    {
        if (device_active == DEVICE_SDMMC0)
        {
            my_printf("%c   SCAN SDMMC");
        }
        else if (device_active == DEVICE_UDISK)
        {
            my_printf("%c   SCAN UDISK");
        }
    }
#elif ((monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        if (device_active == DEVICE_SDMMC0)
        {
            my_printf("%c%Y\x02   SCAN SDMMC");
        }
        else if (device_active == DEVICE_UDISK)
        {
            my_printf("%c%Y\x02   SCAN UDISK");
        }
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%cLod");
    }
#endif
}
void disp_no_dev(void)
{
#if (monitor == DISP_LCD_12832)
    {

    }
#elif ((monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {

    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%c NO");
    }
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief ��ʾLine Inģʽ����
   @param 	void
   @return  void
   @note  void disp_aux(void)
*/
/*----------------------------------------------------------------------------*/
void disp_aux(void)
{
#if (monitor == DISP_LCD_12832)
    {
        my_printf("%c%Y\x0     %eAUX%o");
    }
#elif ((monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%c%Y\x0     %eAUX%o");
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%cAUX%m", LED_AUX_ICON);
    }
#endif
}
#if USB_DEVICE_ENABLE
/*----------------------------------------------------------------------------*/
/**@brief ��ʾ�ӻ�ģʽ����
   @param 	void
   @return  void
   @note  void disp_usb_device(void)
*/
/*----------------------------------------------------------------------------*/
void disp_usb_device(void)
{
#if (monitor == DISP_LCD_12832)
    {
        my_printf("%c%Y\x0   %eTO PC%o");
    }
#elif ((monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%c%Y\x0   %eTO PC%o");
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%cu5b");
    }
#endif
}
#endif


/*----------------------------------------------------------------------------*/
/**@brief ��ո�����Ļ
   @param 	void
   @return  void
   @note  void disp_nothing(void)
*/
/*----------------------------------------------------------------------------*/
void disp_nothing(void)
{
    my_printf("%c");
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    draw_lcd(0,LCDPAGE);
    my_printf("%w");
#endif
}
#if RTC_ENABLE


extern RTC_TIME _xdata curr_time;
extern ALM_TIME _xdata alarm;
extern u8 _xdata rtc_mode_setting;
/*----------------------------------------------------------------------------*/
/**@brief ʱ��λѡ�к������ʾ
   @param 	void
   @return  void
   @note  void rtc_selectd(u8 coordinate)
*/
/*----------------------------------------------------------------------------*/
void rtc_selectd(u8 coordinate)
{
#if(DISP_DOT_LCD==1)
	u8 cnt;
    for (cnt = 0;cnt < rtc_coordinate_tab[coordinate][2]; cnt++)
    {
        LCDBuff[rtc_coordinate_tab[coordinate][1]][rtc_coordinate_tab[coordinate][0]+cnt] = ~LCDBuff[rtc_coordinate_tab[coordinate][1]][rtc_coordinate_tab[coordinate][0]+cnt];
        LCDBuff[rtc_coordinate_tab[coordinate][1]+1][rtc_coordinate_tab[coordinate][0]+cnt] = ~LCDBuff[rtc_coordinate_tab[coordinate][1]+1][rtc_coordinate_tab[coordinate][0]+cnt];
    }
#else
	coordinate = coordinate;
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief ����λѡ�к������ʾ
   @param 	void
   @return  void
   @note  void alm_selectd(u8 coordinate)
*/
/*----------------------------------------------------------------------------*/
void alm_selectd(u8 coordinate)
{
#if(DISP_DOT_LCD==1)
    u8 cnt;
    for (cnt = 0;cnt < alm_coordinate_tab[coordinate][2]; cnt++)
    {
        LCDBuff[alm_coordinate_tab[coordinate][1]][alm_coordinate_tab[coordinate][0]+cnt] = ~LCDBuff[alm_coordinate_tab[coordinate][1]][alm_coordinate_tab[coordinate][0]+cnt];
        LCDBuff[alm_coordinate_tab[coordinate][1]+1][alm_coordinate_tab[coordinate][0]+cnt] = ~LCDBuff[alm_coordinate_tab[coordinate][1]+1][alm_coordinate_tab[coordinate][0]+cnt];
    }
#else
	coordinate = coordinate;
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief ��ʾ��ǰʱ�����
   @param 	void
   @return  void
   @note  void disp_curr_time(void)

   Coordinate��
   	RTC_YEAR_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 0
	RTC_MONTH_COORDINATE	(RTC_END_COLUMN - 12*8)/2 + 40
	RTC_DAY_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 64
	RTC_HOUR_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 0
	RTC_MIN_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 24
	RTC_SEC_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 48
*/
/*----------------------------------------------------------------------------*/
void disp_curr_time(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    if ((rtc_mode_setting == RTC_DISPLAY)||(rtc_mode_setting == RTC_SETTING))
    {
        //��ʾ��ǰʱ��
        my_printf("%c%y%x%04u/%y%x%02b/%y%x%02b%o",0,RTC_YEAR_COORDINATE,curr_time.year,0,RTC_MONTH_COORDINATE,curr_time.month,0,RTC_DAY_COORDINATE,curr_time.day);
        my_printf("%y%x%02b:%y%x%02b:%y%x%02b*%01b%o",2,RTC_HOUR_COORDINATE,curr_time.hour,2,RTC_MIN_COORDINATE,curr_time.min,2,RTC_SEC_COORDINATE,curr_time.sec,curr_time.weekday);
        if (rtc_mode_setting == RTC_SETTING)
        {
            rtc_selectd(rtc_coordinate);
        }
    }
#elif(monitor == DISP_LED5X7)
    //my_printf("%c%02b:%02b", min, sec);
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief ��ʾ��ǰ������Ϣ����
   @param 	void
   @return  void
   @note  void disp_alarm(void)

   Coordinate��
	ALM_ICON_COORDINATE		1*8
	ALM_SW_COORDINATE		8*8//(RTC_END_COLUMN - 12*8)/2 +
	ALM_HOUR_COORDINATE		8*8//(RTC_END_COLUMN - 12*8)/2 +
	ALM_MIN_COORDINATE		(8*8+24)//(RTC_END_COLUMN - 12*8)/2 +
	ALM_MON_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_TUE_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_WED_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_THU_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_FRI_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_SAT_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_SUN_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
*/
/*----------------------------------------------------------------------------*/
void disp_alarm(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    if (rtc_mode_setting == ALARM_SETTING)
    {
        my_printf("%c%y%xALARM:%o",0,ALM_ICON_COORDINATE);
        //my_printf("%c%y%xALARM%01b:%o",0,ALM_ICON_COORDINATE,num+1);
        //��ʾ��ǰ����
        my_printf("%y%x%02b:%y%x%02b%o",2,ALM_HOUR_COORDINATE,alarm.hour,2,ALM_MIN_COORDINATE,alarm.min);
        if (alarm.sw)
        {
            my_printf("%y%xON%o",0,ALM_SW_COORDINATE);
        }
        else
        {
            my_printf("%y%xOFF%o",0,ALM_SW_COORDINATE);
        }
        //my_printf("%Y\x02%X\x28%01b%01b%01b%01b%01b%01b%01b%o",(alarm[0].days&BIT(1))>>1,(alarm[0].days&BIT(2))>>2,(alarm[0].days&BIT(3))>>3,(alarm[0].days&BIT(4))>>4,(alarm[0].days&BIT(5))>>5,(alarm[0].days&BIT(6))>>6,(alarm[0].days&BIT(7))>>7);
        alm_selectd(alm_coordinate);
    }
#elif(monitor == DISP_LED5X7)
    //my_printf("%c%02b:%02b", min, sec);
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief ��ʾ�������ֽ���
   @param 	void
   @return  void
   @note  void disp_alarm_up(void)
*/
/*----------------------------------------------------------------------------*/
void disp_alarm_up(void)
{
#if (monitor == DISP_LCD_12832)
    {
        my_printf("%c%Y\x0%e ALARM %o");
    }
#elif ((monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        my_printf("%c%Y\x02 %e ALARM  %o");
    }
#elif(monitor == DISP_LED5X7)
    {
        my_printf("%cAUX%m", LED_AUX_ICON);
    }
#endif
}

#if USB_DEVICE_ENABLE
/*----------------------------------------------------------------------------*/
/**@brief ��ʾ���������������
   @param 	void
   @return  void
   @note  void disp_alarm_up(void)
*/
/*----------------------------------------------------------------------------*/
void disp_alm_request(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    my_printf("%c%y%xALARM ON%o",0,24);

    my_printf("%Y\x2%X\x18Y%Y\x2%X\x38%02b%Y\x2%X\x58N%o",(30-alm_request_cnt/2));
#elif(monitor == DISP_LED5X7)
    //my_printf("%c%02b:%02b", min, sec);
#endif
}
#endif

#endif

/*----------------------------------------------------------------------------*/
/**@brief ���½���
   @param 	void
   @return  void
   @note  void draw_disp(void)
*/
/*----------------------------------------------------------------------------*/
void draw_disp(void)
{
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
    {
        draw_lcd(0,LCDPAGE);
        //draw_lcd(0,4);
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief ��ʾ���漯�д���
   @param 	void
   @return  void
   @note  void disp_port(u8 menu)
*/
/*----------------------------------------------------------------------------*/
void disp_port(u8 menu)
{
    if (
        ( (MENU_SET_EQ == menu) || (MENU_SET_PLAY_MODE == menu) )
        && (MENU_MUSIC_MAIN != cur_menu)&& (work_mode<=SYS_MP3DECODE_SD)
    )
    {
        menu = MENU_MUSIC_MAIN;
    }



    if (menu < 0x80)							//��ʾ�����л���������ʾ�������
    {
        cur_menu = menu;
        main_menu_conter = 0;

        if (menu != MENU_INPUT_NUMBER)
            input_number = 0;

        switch (menu)
        {
        case MENU_NULL:
            my_printf("%c");
            break;
        case MENU_PAUSE:
            disp_music_pause();
            break;
        case MENU_SCAN_DISK:
            disp_scan_disk();
            break;
	case MENU_NODEVICE:
            disp_no_dev();
		break;
        case MENU_MAIN_VOL:
            disp_main_vol(get_dac_vol(0));
            break;

        case MENU_FILENUM:
            disp_input_number(fs_msg.fileNumber);
            break;

        case MENU_MUSIC_MAIN:
            disp_music_main();
            break;

        case MENU_INPUT_NUMBER:
            disp_input_number(input_number);
            break;

        case MENU_FM_MAIN:
            disp_fm_main();
            break;

        case MENU_FM_CHANNEL:
            disp_fm_channel();
            break;

        case MENU_POWER_UP:
            disp_power_on();
            break;
        case MENU_POWER_OFF:
            disp_power_off();
            break;
			
        case MENU_FM_DISP_FRE:
            disp_fm_freq();
            break;

        case MENU_FM_FIND_STATION:
            disp_fm_find_station();
            break;

        case MENU_AUX:
            disp_aux();
            break;
#if USB_DEVICE_ENABLE
        case MENU_USBDEV_MAIN:
            disp_usb_device();
            break;
#endif

#if RTC_ENABLE
        case MENU_RTC:
            disp_curr_time();
            break;

        case MENU_ALM_SET:
            disp_alarm();
            break;

        case MENU_ALM_UP:
            disp_alarm_up();
            break;

#if USB_DEVICE_ENABLE
        case MENU_ALM_REQUEST:
            disp_alm_request();
            break;
#endif
#endif
        }

        draw_disp();
    }
    else												//�ֲ���ʾ�滻�͸���
    {

        switch (menu)
        {
        case MENU_100MS_REFRESH:
#if (MUSIC_SPECTRUM_EN == 1)
            disp_spec();
#endif
            break;

        case MENU_200MS_REFRESH:
            disp_roll_ctrl(1);							//����ʱ�Ĺ�����ʾ
            break;

        case MENU_HALF_SEC_REFRESH:
            disp_main_menu_refresh();
            break;

        case MENU_SET_EQ:
            disp_eq();
            break;
        case MENU_SET_PLAY_MODE:
            disp_play_mode();
            break;
        case MENU_POWER_DOWN:
            disp_nothing();
            break;
        }
    }
}

