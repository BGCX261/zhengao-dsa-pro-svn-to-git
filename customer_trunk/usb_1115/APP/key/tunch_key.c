/*--------------------------------------------------------------------------*/
/**@file   tunch_key.c
   @brief  ��������ģ��
   @details
   @author
   @date   2012-4-12
   @note   Ŀǰ����������֧�ֵ�P03,P04,P05,P06,P07.������������õ����ֿڣ�����ʾ������ֻ����P04��P06
*/
/*----------------------------------------------------------------------------*/

#include  "tunch_key.h"
#include  "key.h"

/*
CKCBEN: 
������������������������������������������������
        bit7     0 : ��ʹ��P07��������������
                 1 : ʹ��P07��������������
������������������������������������������������
        bit6     0 : ��ʹ��P06��������������
                 1 : ʹ��P06��������������
������������������������������������������������
        bit5     0 : ��ʹ��P05��������������
                 1 : ʹ��P05��������������
������������������������������������������������
        bit4     0 : ��ʹ��P04��������������
                 1 : ʹ��P04��������������
������������������������������������������������
        bit3     0 : ��ʹ��P03��������������
                 1 : ʹ��P03��������������
������������������������������������������������
*/

extern void ckc_initial(void);
extern u8 get_crckey_status(void);

//����ģ��ʱ��Ƶ��
//#define CKC_CLK 12000000
//ÿͨ����Ƶբ��ʱ��
#define GATE_TIME 0.004

/*/һ��������������ckc_initial����ʼ���������Ҫ���������ȣ�����ckc_initial֮���޸Ĵ˱���
	PRESSCFG =  -280;         
	RELEASECFG0 =-120;  
	RELEASECFG1 = -400; 
*/
s16 _xdata PRESSCFG _at_ 0x157;//         ///<�����о�����
s16 _xdata RELEASECFG0 _at_ 0x12e;//      ///<�ͷ��о�����0
s16 _xdata RELEASECFG1 _at_ 0x130;//      ///<�ͷ��о�����1


/*----------------------------------------------------------------------------*/
/**@brief   ��������io��ʼ��
   @param 	��
   @return  ��
   @note    static void crckey_init(void)
*/
/*----------------------------------------------------------------------------*/
static void crckey_init(u8 clk)
{
    // p04 p06
    //�����õ���IO���������رգ����õ����ָ���̬
    P0PU = 0x00;
    P0PD = 0x00;   
    P0DIR |= 0x50;
    //P0IE = 0x050;
	P0_IE |=0x50 ;
	port_pnie_init();

    CKCBEN = 0x50;	       //ʹ�ܴ�������ɨ���
	crc_key_prd(clk);
    IP0 |= BIT(5);                //�ж����ȼ�
    IE0 |= BIT(5);                //�ж�����
}

void crc_key_prd(u8 clk)
{

#if 0
	CKCCON = 0;
	if (clk == MAIN_CLK_12M)
	{
		CKCPRDH = (unsigned char)(((12000000/8)*GATE_TIME) / 256);
	    CKCPRDL = (unsigned char)(((12000000/8)*GATE_TIME));			 
	}
    else if (clk == MAIN_CLK_24M)
	{
		CKCPRDH = (unsigned char)(((24000000/8)*GATE_TIME) / 256);
	    CKCPRDL = (unsigned char)(((24000000/8)*GATE_TIME));
	}
    else if (clk == MAIN_CLK_48M)
	{
		CKCPRDH = (unsigned char)(((48000000/8)*GATE_TIME) / 256);
	    CKCPRDL = (unsigned char)(((48000000/8)*GATE_TIME));
	}
	CKCCON = 0x18;//0x28;//0x48;	
#endif	
}

/*----------------------------------------------------------------------------*/
/**@brief   ����������ʼ��
   @param 	��
   @return  ��
   @note    void tch_key_init(u8 clk)
*/
/*----------------------------------------------------------------------------*/
void tch_key_init(u8 clk)
{
    ckc_initial();
   	/*
    PRESSCFG =  -280;     //�ڴ�����������Щֵ������������    
	RELEASECFG0 =-120;  
	RELEASECFG1 = -400;
    */
    crckey_init(clk);
}

/*
///////////////////////
temp��ֵ��Ӧ��������
 
0111 1111  ///<P07�ϰ�������
1011 1111  ///<P06�ϰ�������
1101 1111  ///<P05�ϰ�������		
1110 1111  ///<P04�ϰ�������
1111 0111  ///<P03�ϰ�������
*/
/*----------------------------------------------------------------------------*/
/**@brief   �������������ж�
   @param 	��
   @return  ��
   @note    u8 tunch_value(void)
*/
/*----------------------------------------------------------------------------*/
u8 tunch_value(void)
{
    u8 temp;
    temp = get_crckey_status();
//    crc_key = temp;
    /*
    if(temp == 0x7f)
    {
        temp = 0;
    }
    else 
    */
    if( temp == 0xbf)
    {
        temp = 7;
    }/*
    else if( temp == 0xdf)
    {
        temp = 2;
    }
    */
    else if( temp == 0xef)
    {
        temp = 8;
    }
    /*
    else if( temp == 0xf7)
    {
        temp = 4;
    }
    */
    else
    {
        temp = 0xff;
    }
    
	return temp; 
}