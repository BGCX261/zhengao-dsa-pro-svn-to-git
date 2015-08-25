/*--------------------------------------------------------------------------*/
/**@file   clock.h
   @brief  ʱ������
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef __CLCOK_H__
#define __CLOCK_H__


#ifdef __C51__
#include "config.h"
/*----------------------------------------------------------------------------*/
/**@brief   PLL����ʱ��ѡ��
   @param   select: #define PLL_IN_AUTO     0			//system auto detect 32K or 1M or 4M or 7.6M or 12M at osc0
					#define PLL_IN_32K      1			//crystal = 32K at osc1
					#define PLL_IN_4M       2			//crystal = 4M at osc1
					#define PLL_IN_76M      3			//crystal = 7.6M at osc1
					#define PLL_IN_12M      4			//crystal = 12M at osc1
   @param   share_osc: 0:�����ⲿ�豸��������1�����ⲿ�豸��������(��OSC OUT�����������豸)
   @return  ��
   @note
*/
/*----------------------------------------------------------------------------*/
void PLL_init(u8 select, u8 share_osc);

/*----------------------------------------------------------------------------*/
/**@brief   PLL�����ʽѡ��
   @param   select: 0--ѡ������ʱ�ӳ���2�� 1--ѡ��48M�����ֻ��������ʱ��Ϊ32K,7.6M, 12Mʱʹ�ã�
   @return  ��
   @note
*/
/*----------------------------------------------------------------------------*/
void PLL_output(u8 select);

/*----------------------------------------------------------------------------*/
/**@brief   ��ʱ����ѡ��
   @param   select: 0--ѡ��RC��1--����ʱ�ӣ�2--PLL�������3--32K
   @return  ��
   @note
*/
/*----------------------------------------------------------------------------*/
void mainclock_select(u8 select);


/*----------------------------------------------------------------------------*/
/**@brief   ϵͳʱ��ѡ�񣨸�CPU���󲿷����裩
   @param   select: 0--����ʱ����ͬƵ��1--��ʱ��Ƶ�ʵ�һ��
   @return  ��
   @note
*/
/*----------------------------------------------------------------------------*/
void sysclock_div2(u8 select);

/*----------------------------------------------------------------------------*/
/**@brief   ����ģ��ʱ��ѡ��
   @param   select: 0--����ʱ����ͬƵ��1--��ʱ��Ƶ�ʵ�һ��
   @return  ��
   @note
*/
/*----------------------------------------------------------------------------*/
void decodeclock_div2(u8 select);


/*----------------------------------------------------------------------------*/
/**@brief   OTPģ��ʱ��ѡ��
   @param   select: 0--����ʱ����ͬƵ��1--��ʱ��Ƶ�ʵ�һ��
   @return  ��
   @note
*/
/*----------------------------------------------------------------------------*/
void otpclock_div2(u8 select);

/*----------------------------------------------------------------------------*/
/**@brief   P05���ʱ��Դѡ��
   @param   select: 0--��ͨIO��1--RTC����ʹ�õľ���, 3--PLL���ʱ�ӣ����PLLδ�򿪣������RCʱ��
   @return  ��
   @note	void P05_source_select(u8 select)
*/
/*----------------------------------------------------------------------------*/
void P05_source_select(u8 select);

/*----------------------------------------------------------------------------*/
/**@brief   ι������
   @param   void
   @return  ��
   @note   void WDT_CLEAR(void)
*/
/*----------------------------------------------------------------------------*/
extern void WDT_CLEAR(void);

/*----------------------------------------------------------------------------*/
/**@brief   ʹ��TIMER��ʼ�����������Ը��ݲ�ͬ��ϵͳʱ��������
   @param   clk : MAIN_CLK_24M (ϵͳʱ��ʹ��24Mhzʱ�Ĳ���);MAIN_CLK_48M(ϵͳʱ��ʹ��48Mhzʱ�Ĳ���)
   @return  void
   @note    void timer_init(u8 clk)
*/
/*----------------------------------------------------------------------------*/
void timer_init(u8 clk);

/*----------------------------------------------------------------------------*/
/**@brief   ʹ��SDMMC CLK��SDMMC���߼��ĺ���
   @param   mode:0 ��ͨ��⣬ 1 SDMMC���߼��
   @return  0:IO�ͣ�1��IO�ߣ��������˴μ����Ч
   @note    u8 sdmmc_online_chk(u8 mode)
*/
/*----------------------------------------------------------------------------*/
extern u8 sdmmc_online_chk(u8 mode);

///
/*----------------------------------------------------------------------------*/
/**@brief   ����һ��������
   @param   void
   @return  void
   @note    void fun_send_kv(void)
*/
/*----------------------------------------------------------------------------*/
extern void fun_send_kv(void);
///
/*----------------------------------------------------------------------------*/
/**@brief   ����һ��������
   @param   void
   @return  void
   @note    void send_alm_voice(void)
*/
/*----------------------------------------------------------------------------*/
extern void send_alm_voice(void);
///
/*----------------------------------------------------------------------------*/
/**@brief   ����������������״̬��ѯ
   @param   void
   @return  1�����У�0����æ
   @note   void bsp_kv_init(void)
*/
/*----------------------------------------------------------------------------*/
extern u8 kv_send_finish(void);
/*----------------------------------------------------------------------------*/
/**@brief   ������������������ʼ��
   @param   void
   @return  ��
   @note   void bsp_kv_init(void)
*/
/*----------------------------------------------------------------------------*/
extern void bsp_kv_init(void);

/*----------------------------------------------------------------------------*/
/**@brief   ����ģ�⡢�������������ֵ��
   @param   ģ�������� anolog_vol 0~30
   @param   ���������� digtal_vol 0~55
   @return  ��
   @note   void set_max_vol(u8 anolog_vol,digtal_vol)
*/
/*----------------------------------------------------------------------------*/
extern void set_max_vol(u8 anolog_vol,digtal_vol);

/*----------------------------------------------------------------------------*/
/**@brief   оƬ�ڲ��ϵ�
   @param   ��
   @return  ��
   @note   void core_power_on(void)
*/
/*----------------------------------------------------------------------------*/
void core_power_on(void);

/*----------------------------------------------------------------------------*/
/**@brief  sdmmc�����ⷽʽ��ʱ���ʹ�ܺ���,ֻ���������ⷽʽ��ʹ��
   @param  flag:Sd_api_cmd
   @return void
   @note   void sd_chk_ctl(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void sd_chk_ctl(u8 flag);

/*----------------------------------------------------------------------------*/
/**@brief  ʵ��sdmmc IO��⹦�ܣ�Ĭ��ʹ��CMD���
   @param  flag:0 : remove sd;1 : insert sd
   @return void
   @note   void sdmmc_chk_io(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void sdmmc_chk_io(u8 flag);
extern void crc_key_prd(u8 clk);

/*******************************************************************************/
//APP ����
/*******************************************************************************/
#include "Custom_config.h"

#ifdef UART_ENABLE	
#define WDT_EN()		WDTCON = 0x9D; while(WDTCON & BIT(6)); WDTCON = 0xBD			//������λ���ܣ����ʱ��Ϊ6.7S
//#define WDT_CLEAR()     WDTCON |= BIT(7)			//��WDT��������WDT���֮ǰ���WDT������
#define SYS_IDLE()         PCON |= BIT(6)
//#define SYSTEM_CLK_DIV4()  CLKCON1 |= 0x80; PCON |= BIT(1);timer_init(MAIN_CLK_12M)	 /*����ģʽ�²���ʹ��*/
//#define SYSTEM_CLK_DIV4()  CLKCON1 &= ~0x80;PCON |= BIT(1);timer_init(MAIN_CLK_24M)
//#define SYSTEM_CLK_DIV2()  CLKCON1 &= ~0x80;PCON |= BIT(1);timer_init(MAIN_CLK_24M)
#define SYSTEM_CLK_DIV1()  CLKCON1 &= ~0x80;PCON &= ~(BIT(1));timer_init(MAIN_CLK_48M)
#define SYSTEM_CLK_DIV4()  CLKCON1 &= ~0x80;PCON &= ~(BIT(1));timer_init(MAIN_CLK_48M)
#define SYSTEM_CLK_DIV2()  CLKCON1 &= ~0x80;PCON &= ~(BIT(1));timer_init(MAIN_CLK_48M)
#define OTP_CLK_DIV2()  PCON |= BIT(3)
#define OTP_CLK_DIV1()  PCON &= ~(BIT(3))
#define DECODER_DIV1()	PCON &= ~(BIT(2))
#define DECODER_DIV2()	PCON |= BIT(2)
#else
#define WDT_EN()			WDTCON = 0x9D; while(WDTCON & BIT(6)); WDTCON = 0xBD			//������λ���ܣ����ʱ��Ϊ6.7S
//#define WDT_CLEAR()     	WDTCON |= BIT(7)			//��WDT��������WDT���֮ǰ���WDT������
#define SYS_IDLE()         	PCON |= BIT(6)
#define SYSTEM_CLK_DIV4()  	CLKCON1 |= 0x80; PCON |= BIT(1);crc_key_prd(MAIN_CLK_12M);timer_init(MAIN_CLK_12M);UTBAUD = (12000000/(8 * 115200)) - 1	 /*����ģʽ�²���ʹ��*/
#define SYSTEM_CLK_DIV2()  	CLKCON1 &= ~0x80;PCON |= BIT(1);crc_key_prd(MAIN_CLK_24M);timer_init(MAIN_CLK_24M);UTBAUD = (24000000/(8 * 115200)) - 1
#define SYSTEM_CLK_DIV1()  	CLKCON1 &= ~0x80;PCON &= ~BIT(1);crc_key_prd(MAIN_CLK_48M);timer_init(MAIN_CLK_48M);UTBAUD = (48000000/(8 * 115200)) - 1
#define OTP_CLK_DIV2()  PCON |= BIT(3)
#define OTP_CLK_DIV1()  PCON &= ~(BIT(3))
#define DECODER_DIV1()	PCON &= ~(BIT(2))
#define DECODER_DIV2()	PCON |= BIT(2)
#endif
#endif

//PLL ����
//��������ʱ��ѡ��
//OSC0: RTCģ����������ɽ�32768����͸��پ���
//OSC1: P00/P01�ϵ�������ֻ�ܽӸ��پ���
#define PLL_IN_OSC1_24M      0x0			//crystal = 24M at osc1
#define PLL_IN_OSC0_32K      0x1			//crystal = 32K at osc0
#define PLL_IN_OSC0_4M       0x2			//crystal = 4M at osc0
#define PLL_IN_OSC0_12M      0x4			//crystal = 12M at osc0
#define PLL_IN_OSC1_4M       0x20			//crystal = 4M at osc1
#define PLL_IN_OSC1_12M      0x40			//crystal = 12M at osc1(ѡ��P00��P01��ʹ��12M����)
#define PLL_IN_HPRC     	 0x80			//use HPRC

//ϵͳʱ��ѡ��
#define MAIN_CLK_12M     0
#define MAIN_CLK_24M     1
#define MAIN_CLK_48M     2

//P05���ѡ��
#define P05_SEL_IO			0
#define P05_SEL_OSC1		1
#define P05_SEL_PLL			2
#endif