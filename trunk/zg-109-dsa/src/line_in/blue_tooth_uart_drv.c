#include "custom_config.h"

#ifdef BLUE_TOOTH_UART_FUNC
#include "bluetooth_mode.h"
#include "uart.h"
#include "main.h"
#include "config.h"
#include "clock.h"
#include "msg.h"
#include "blue_tooth_msg_if.h"

bool bt_frame_rev_finished=0;
xd_u8  uart_rev=0;
xd_u8 rev_phase=0,rev_length=0;
xd_u8 rev_cmd[7]={0};

#define EN_UART_MASK		0x01
#define INT_UART_MASK		0x08

#define UART_AT_P06P07		0x00
#define UART_AT_P24P25		0x40
#define UART_AT_P32P33		0x80
#define UART_AT_DPDM		0xC0

#ifdef BLUE_TOOTH_UART_BAUDRATE_AT_9600
#define BAUDRATE_9600		0x10
#else
#define BAUDRATE_9600		0x00
#endif

//#define BLUETOOTH_UART_DRV_DEBUG

#define UART_REG	(INT_UART_MASK|EN_UART_MASK|BAUDRATE_9600)

_near_func __root void uart_isr(void) AT(COMMON_CODE)
{
       uart_rev = UART_BUF;
	UART_STA &= ~(BIT(6));
	UART_STA |=BIT(4);
	
    	if((uart_rev==0xAA)&&(rev_phase==0)){

		rev_phase=1;
    	}
	
	if(rev_phase>0){
		
	   rev_cmd[rev_phase-1]=uart_rev;
	
	   rev_phase++;

	   if(rev_phase>7){	   	
	   	rev_phase=0;
		bt_frame_rev_finished=1;
	   }
   	}
	else{
	   	rev_phase=0;
	}

}
void blue_tooth_uart_init(void)
{
       system_clk_div(CLK_24M);

	int_enter_pro[INT_UART_BRK] = uart_isr;


#ifdef BLUE_TOOTH_UART_AT_DPDM

    	USB_CON0 = 0x11;
    	USB_CON2 &= ~(BIT(1));
	
       P3PU &= ~((BIT(6))|(BIT(7)));
       P3PD &= ~((BIT(6))|(BIT(7)));
    	P3DIR &= ~(BIT(6));
    	P3DIR |= (BIT(7));
	IO_MC0 |= (BIT(7) | BIT(6));
#elif defined(BLUE_TOOTH_UART_AT_P24P25)    
    	P2DIR &= ~(BIT(4));
    	P2DIR |= BIT(5);

       P2PU &= ~(BIT(3));
       P2PD &= ~(BIT(3));
    	P2DIR |= BIT(3);
		
    	IO_MC0 |= BIT(6);
#elif defined(BLUE_TOOTH_UART_AT_P32P33)    
   	P3DIR &= ~BIT(2);
    	P3DIR |= BIT(3);
    	IO_MC0 |= BIT(7);	
#else		
       P0PU &= ~((BIT(6))|(BIT(7)));
       P0PD &= ~((BIT(6))|(BIT(7)));
	
	P0DIR &= ~(BIT(6));							/* P06 for transmit */
	P0DIR |= (BIT(7));							/* P07 for receive */

	IO_MC0 &=~(BIT(7) | BIT(6));

#endif
#ifdef BLUE_TOOTH_UART_BAUDRATE_AT_9600
	UART_BAUD = 0x38 ;
#else
	UART_BAUD = 0x9C;	//12MHZ_19200:  0x4E ;	
#endif
	UART_CON = UART_REG;							/* enable uart */

#ifdef BLUETOOTH_UART_DRV_DEBUG
      	my_puts("blue_tooth_uart_init   \r\n");
#endif
	delay_n10ms(1);
}
void blue_tooth_uart_release(void)
{
	UART_CON = 0x00;
}

#define REV_CMD_LEN		BT_STATUS_MAX

u8 const _code BT_REV_CMD[REV_CMD_LEN][7] =
{
	0xAA ,0x00 ,0x03 ,0x01 ,0x02 ,0x00 ,0xFA,				//Power on
	0xAA ,0x00 ,0x03 ,0x01 ,0x01 ,0x00 ,0xFB,				// In pairing mode
	0xAA ,0x00 ,0x03 ,0x01 ,0x03 ,0x00 ,0xF9,				//Pairing completed
  	0xAA ,0x00 ,0x03 ,0x01 ,0x06 ,0x00 ,0xF6,				//|| A connect A2DP
  	0xAA ,0x00 ,0x03 ,0x01 ,0x0B ,0x00 ,0xF1,				//|| A connect AVRCP
	0xAA ,0x00 ,0x03 ,0x01 ,0x05 ,0x00 ,0xF7,				//|| A connect HF 
	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x02 ,0xF9,				//|| Call incoming..
	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x03 ,0xF8,				//|| Outgoing call
	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x00 ,0xFB,				//|| No Call..
	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x04 ,0xF7,				//|| Call active..
  	0xAA ,0x00 ,0x03 ,0x01 ,0x08 ,0x00 ,0xF4,				// A disconnect A2DP
  	0xAA ,0x00 ,0x03 ,0x01 ,0x0C ,0x00 ,0xF0,				// A disconnect AVRCP
  	0xAA ,0x00 ,0x02 ,0x00 ,0x02 ,0xFC ,0xAA,				//|| ACK
	0xAA ,0x00 ,0x03 ,0x0F ,0x0F ,0x00 ,0xDF,				// DEVICE START PLAY
};

#define AT_CMD_LEN		(BT_CMD_SET_MAX)

u8 const _code BT_AT_CMD[AT_CMD_LEN][7] =
{
	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x32 ,0xC9,				//PLAY
  	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x34 ,0xC7,				// NEXT
  	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x35 ,0xC6,				//PREV	
  	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x30 ,0xCB,				//V +
  	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x31 ,0xCA,				//V -
	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x36 ,0xC5,				//FF
	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x37 ,0xC4,				// FR
	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x33 ,0xC8,				//STOP
	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x3B ,0xC0,				// DISCONNEXT
  	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x50 ,0xAB,				// entern piaring mode
  	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x5D ,0x9E,				// fast pairing mode
  	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x04 ,0xF7,				// answer call
  	0xAA ,0x00 ,0x03 ,0x02 ,0x00 ,0x06 ,0xF5,				// end call
};


void promt_bt_cmd(AT_PROMPT_CMD cmd)
{
	u8 i=0;
	if(cmd<AT_CMD_LEN){

		//UTCON = 0x01;

		for(i=0;i<7;i++){
			putbyte(BT_AT_CMD[cmd][i]);
		}

		//UTCON = 0x09;		
	}
}
#ifdef BLUE_TOOTH_CONFIG_DEV_NAME
/*
AA 00 06 05 49 50 30 30 32 CA
checksum: 0xCA =0 - (00+0x06+0x05+0x49+0x50+0x30+0x30+0x32)
*/
u8 const _code bt_dev_name[]=
{
#ifdef JK_IBT40_1094A_V001
	0xAA ,0x00 ,0x06 ,0x05 ,0x49 ,0x42 ,0x54 ,0x34 ,0x30 ,0xB2,	//IBT40
#endif
#ifdef JK_IBT_388_1096A_V001
	0xAA ,0x00 ,0x07 ,0x05 ,0x49 ,0x42 ,0x54 ,0x33 ,0x38 ,0x38,0x72,
#endif
};
void config_dev_name(void)
{
	u8 i=0;
	for(i=0;i<(sizeof(bt_dev_name));i++){
		putbyte(bt_dev_name[i]);
	}
}
#endif
xd_u8 parse_i=0;
u8 bluetooth_cmd_parse(void)
{
	u8 i=0xFF,j=0;
	u8 rev_reg[5]={0};
	//UART_CON = (UART_REG&(~INT_UART_MASK));							/* enable uart */
       my_memcpy(rev_reg,rev_cmd+2,5);

#ifdef BLUETOOTH_UART_DRV_DEBUG
	my_puts("   ");
	for(j=0;j<5;j++)
		my_printf("--->rev   data  %x \r\n",(u16)rev_reg[j]);
#endif

	parse_i=rev_reg[0]+1;
	for(i=0;i<REV_CMD_LEN;i++){

		for(j=0;j<parse_i;){


			if(rev_reg[j]!=BT_REV_CMD[i][2+j]){
				j=0;
				break;
			}
			j++;
		}
		if(j==parse_i){
			break;
		}
	}

	if(j==0){
		i= 0xFF;
	}
		
	//UART_CON = UART_REG;

	return i;
}

void bluetooth_rev_msg_hdlr(void)
{
    u8 rev_cmd=0,cmd_idx=0;

	 if(bt_frame_rev_finished){
	 	
		bt_frame_rev_finished = 0;
		rev_cmd = bluetooth_cmd_parse();
#ifdef BLUETOOTH_UART_DRV_DEBUG		
		my_printf(" --------->     %x \r\n",(u16)rev_cmd);
#endif
		if(rev_cmd!= 0xFF){
			
			for(cmd_idx = 0;cmd_idx < (sizeof(bt_rev_msg)/2);cmd_idx++){
				
				if(bt_rev_msg[cmd_idx].bt_cmd == rev_cmd){
#ifdef BLUETOOTH_UART_DRV_DEBUG							
				   my_printf("rev msg     %x \r\n",(u16)cmd_idx);
#endif
				   put_msg_fifo(bt_rev_msg[cmd_idx].sys_msg);
				}	
			}
		}
	 }
}
void bluetooth_promt_msg_hdlr(u8 key_msg)
{
	u8 cmd_idx =0;

	if(key_msg >= MSG_HALF_SECOND)return;

	if(key_msg!= NO_MSG){
					
		for(cmd_idx = 0;cmd_idx < (sizeof(bt_promt_msg)/2);cmd_idx++){

				if(bt_promt_msg[cmd_idx].sys_msg == key_msg){
#ifdef BLUETOOTH_UART_DRV_DEBUG												
					my_printf("bluetooth_promt_msg_hdlr    cmd_idx  %x \r\n",(u16)cmd_idx);
#endif					
				   	promt_bt_cmd((AT_PROMPT_CMD)(bt_promt_msg[cmd_idx].bt_cmd));
				}	
			}
		}
}
#endif

