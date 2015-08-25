/*--------------------------------------------------------------------------*/
/**@file   tunch_key.c
   @brief  触摸按键模块
   @details
   @author
   @date   2012-4-12
   @note   目前触摸按键能支持到P03,P04,P05,P06,P07.有与程序中有用到部分口，现在示例程序只做客P04和P06
*/
/*----------------------------------------------------------------------------*/

#include  "tunch_key.h"
#include  "key.h"

/*
CKCBEN: 
－－－－－－－－－－－－－－－－－－－－－－－－
        bit7     0 : 不使用P07做触摸按键检测脚
                 1 : 使用P07做触摸按键检测脚
－－－－－－－－－－－－－－－－－－－－－－－－
        bit6     0 : 不使用P06做触摸按键检测脚
                 1 : 使用P06做触摸按键检测脚
－－－－－－－－－－－－－－－－－－－－－－－－
        bit5     0 : 不使用P05做触摸按键检测脚
                 1 : 使用P05做触摸按键检测脚
－－－－－－－－－－－－－－－－－－－－－－－－
        bit4     0 : 不使用P04做触摸按键检测脚
                 1 : 使用P04做触摸按键检测脚
－－－－－－－－－－－－－－－－－－－－－－－－
        bit3     0 : 不使用P03做触摸按键检测脚
                 1 : 使用P03做触摸按键检测脚
－－－－－－－－－－－－－－－－－－－－－－－－
*/

extern void ckc_initial(void);
extern u8 get_crckey_status(void);

//控制模块时钟频率
//#define CKC_CLK 12000000
//每通道测频闸门时间
#define GATE_TIME 0.004

/*/一下三个参数会在ckc_initial被初始化，如果需要调节灵敏度，请在ckc_initial之后修改此变量
	PRESSCFG =  -280;         
	RELEASECFG0 =-120;  
	RELEASECFG1 = -400; 
*/
s16 _xdata PRESSCFG _at_ 0x157;//         ///<按下判决门限
s16 _xdata RELEASECFG0 _at_ 0x12e;//      ///<释放判决门限0
s16 _xdata RELEASECFG1 _at_ 0x130;//      ///<释放判决门限1


/*----------------------------------------------------------------------------*/
/**@brief   触摸按键io初始化
   @param 	无
   @return  无
   @note    static void crckey_init(void)
*/
/*----------------------------------------------------------------------------*/
static void crckey_init(u8 clk)
{
    // p04 p06
    //将所用到的IO口上下拉关闭，设置到数字高阻态
    P0PU = 0x00;
    P0PD = 0x00;   
    P0DIR |= 0x50;
    //P0IE = 0x050;
	P0_IE |=0x50 ;
	port_pnie_init();

    CKCBEN = 0x50;	       //使能触摸按键扫描口
	crc_key_prd(clk);
    IP0 |= BIT(5);                //中断优先级
    IE0 |= BIT(5);                //中断允许
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
/**@brief   触摸按键初始化
   @param 	无
   @return  无
   @note    void tch_key_init(u8 clk)
*/
/*----------------------------------------------------------------------------*/
void tch_key_init(u8 clk)
{
    ckc_initial();
   	/*
    PRESSCFG =  -280;     //在此重新设置这些值来调节灵敏度    
	RELEASECFG0 =-120;  
	RELEASECFG1 = -400;
    */
    crckey_init(clk);
}

/*
///////////////////////
temp的值对应按键如下
 
0111 1111  ///<P07上按键按下
1011 1111  ///<P06上按键按下
1101 1111  ///<P05上按键按下		
1110 1111  ///<P04上按键按下
1111 0111  ///<P03上按键按下
*/
/*----------------------------------------------------------------------------*/
/**@brief   触摸按键按下判断
   @param 	无
   @return  无
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