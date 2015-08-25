/*--------------------------------------------------------------------------
File : dsa.c
Contents : DSA protocol function
--------------------------------------------------------------------------*/
#include "Custom_config.h"
#include "main.h"
#include "key.h"
#include "device.h"
#include "id3.h"

#ifdef AC_SLAVE_ENABLE

#ifdef DSA_PORT_P15_P16_P17

#define DSA_PORT_INIT()		P1DIR &=~(BIT(5)|BIT(6)|BIT(7));P1PU |=(BIT(5)|BIT(6)|BIT(7))
//// GPIOE2 Pin73
#define SET_DATA_READ 		P1DIR &=~(BIT(7));P1PU |=(BIT(7));P17 = 1;P1DIR |=(BIT(7));P1PD&=~(BIT(7))
#define SET_DATA_WRITE 	P1DIR &=~(BIT(7));P1PU |=(BIT(7))
#define SET_DATA_HIGH 		P17 = 1
#define SET_DATA_LOW 		P17 = 0
#define GET_DATA 			P17

//// GPIOE2 Pin74
#define SET_STB_READ 		P1DIR &=~(BIT(5));P1PU |=(BIT(5));P15 = 1;P1DIR |=(BIT(5));P1PD&=~(BIT(5));
#define SET_STB_WRITE 		P1DIR &=~(BIT(5));P1PU |=(BIT(5))
#define SET_STB_HIGH 		P15 = 1
#define SET_STB_LOW		P15 = 0
#define GET_STB 				P15

/// GPIOE0 Pin72
#define SET_ACK_READ 		P1DIR &=~(BIT(6));P1PU |=(BIT(6));P16 = 1;P1DIR |=(BIT(6));P1PD&=~(BIT(6))
#define SET_ACK_WRITE 		P1DIR &=~(BIT(6));P1PU |=(BIT(6))
#define SET_ACK_HIGH 		P16 = 1
#define SET_ACK_LOW 		P16 = 0
#define GET_ACK 				P16

#else
#define DSA_PORT_INIT()		P0DIR &=~(BIT(1)|BIT(5)|BIT(7));P0PU |=(BIT(1)|BIT(5)|BIT(7))
//// GPIOE2 Pin73
#define SET_DATA_READ 		P0DIR &=~(BIT(7));P0PU |=(BIT(7));P07 = 1;P0DIR |=(BIT(7));P0PD&=~(BIT(7))
#define SET_DATA_WRITE 	P0DIR &=~(BIT(7));P0PU |=(BIT(7))
#define SET_DATA_HIGH 		P07 = 1
#define SET_DATA_LOW 		P07 = 0
#define GET_DATA 			P07

//// GPIOE2 Pin74
#define SET_STB_READ 		P0DIR &=~(BIT(1));P0PU |=(BIT(1));P01 = 1;P0DIR |=(BIT(1));P0PD&=~(BIT(1));
#define SET_STB_WRITE 		P0DIR &=~(BIT(1));P0PU |=(BIT(1))
#define SET_STB_HIGH 		P01 = 1
#define SET_STB_LOW		P01 = 0
#define GET_STB 				P01

/// GPIOE0 Pin72
#define SET_ACK_READ 		P0DIR &=~(BIT(5));P0PU |=(BIT(5));P05 = 1;P0DIR |=(BIT(5));P0PD&=~(BIT(5))
#define SET_ACK_WRITE 		P0DIR &=~(BIT(5));P0PU |=(BIT(5))
#define SET_ACK_HIGH 		P05 = 1
#define SET_ACK_LOW 		P05 = 0
#define GET_ACK 				P05

#endif

#define DSA_Ideal 0
#define DSA_Sync 1
#define DSA_Comm 2
#define DSA_Ack 3
#define DSA_Ack2 4

#define DSA_Ideal_Send 10
#define DSA_Sync_Send 11
#define DSA_Comm_Send 12
#define DSA_Ack_Send 13
#define DSA_Ack2_Send 14

#define WAITE_ACK_DELAY_TIME 		1200
#define DCK_STABLE_TIME	12
#define STB_STABLE_TIME	8
#define ACK_STABLE_TIME	6


xd_u8 DSAState,UI2DSA_STATE;
xd_u8 DSA_Count,DSA_Count;
xd_u16 DSA_Timer,DSA_Delay;
xd_u16 DSA_Rdata,DSA_Sdata,DSA_Sdata_backup,DSA_flag;
bool DSA_GETHERING_DATA_ENABLE_BIT=1,DSA_REV_OK;
xd_u8 sec;
xd_u8 min;
xd_u32 file_play_time;
xd_u8 gether_info_timer=0;
xd_u16  DSA_DATA[8];
xd_u8 DSA_SEL_DEV =0;
extern DECODER_MSG _xdata *dec_msg;
extern FSINFO _xdata fs_info;
extern u8 _bdata device_online;
extern xd_u8 disk_toc_ok,dev_invalid;
extern _xdata SYS_WORK_MODE work_mode;
extern u8 play_status,play_mode,device_active,music_type,given_device;
extern u16 given_file_number;
extern FSAPIMSG _pdata fs_msg;

extern u8 _xdata id3_tag_buf[ID3_DISP_BUF_LEN];	///<ID3 tag buff
extern xd_u8 id3_artist_len,id3_title_len,id3_alb_len;
extern u8 id3_tag_len;								///<ID3 tag³¤¶È
xd_u8 DSA_id3=0;
bool DSA_id3_frame=0;


u8 _code DSA_Key[][3]={
	
  {0x55,0x00,(0)},
  {0x55,0x01,(1)},
  {0x55,0x02,(2)},
  {0x55,0x03,(3)},
  {0x55,0x04,(4)},
  {0x55,0x05,(5)},
  {0x55,0x06,(6)},
  {0x55,0x07,(7)},
  {0x55,0x08,(8)},
  {0x55,0x09,(9)},
  {0x55,0x0a,(MSG_MUSIC_PP)},
  {0x55,0x0b,(MSG_MUSIC_STOP)},
  {0x55,0x0c,(MSG_MUSIC_NEXT_FILE)},
  {0x55,0x0d,(MSG_MUSIC_PREV_FILE)},
  {0x55,0x0e,(MSG_NEXT_PLAYMODE)},
  {0x55,0x0F,(MSG_USB_DISK_IN_SEL)},
  {0x55,0x10,(MSG_POWER_DOWN)},
  {0x55,0x11,(MSG_NEXT_FOLDER)},
  {0x55,0x12,(MSG_PREV_FOLDER)},
  {0x55,0x13,0xFF},
  {0x55,0x14,(MSG_MUSIC_FF)},
  {0x55,0x15,(MSG_MUSIC_FR)},
  {0x55,0x16,(MSG_VOL_UP)},
  {0x55,0x17,(MSG_VOL_DOWN)},
  {0x55,0x18,(MSG_SDMMC_IN_SEL)},
  {0x55,0x19,(MSG_MUSIC_FFR_DONE)},
  {0x55,0x1A,(MSG_10_PLUS)},
  {0x55,0x1B,(MSG_10_MINUS)},
 };
#define DSA_KEYNUM (sizeof(DSA_Key)/3)

#define FLAG0 			0x90  
#define F_READ_TOC	 	0x80
#define F_READ_DEVICE	0x80
#define F_TOC_OK  	 	0x40
#define F_MP3     		 	0x20
#define F_WMA     	 	0x10
#define F_CD     		 	0x08
#define F_PLAY   		 	0x04
#define F_STOP  		 	0x02
#define F_PAUSE   		0x01

#define FLAG1 			0x91
#define F_FORWARD		0x80
#define F_BACKWARD		0x40
#define F_PROG 			0x20
#define F_REP_ONE 		0x10
#define F_REP_DIR 		0x08
#define F_REP_ALL 		0x04
#define F_RANDOM 		0x02
#define F_INTRO 			0x01

#define FLAG2 			0x92
#define F_TRACK_END	 	0x80
#define F_DISC_END 		0x40
#define F_HOSTSD_END	0x40
#define F_MUTE_ON 		0x20
#define F_MUTE_OFF 		0x10
#define F_NO_DISC  		0x08
#define F_NO_DEVICE 	0x08
#define F_ERR_DISC		0x04
#define F_NO_FILE 		0x04
#define F_STOP_DISC		0x02
#define F_ID3_EXIST 		0x01

#define FLAG3			0x93
#define CD_SOURCE		0x80
#define USB_SOURCE		0x40
#define SD_SOURCE		0x20

//#define DSA_DEBUG
#define DSA_DEBUG_REV_KEY
//#define DSA_DEBUG_SEND
#define DSA_DEBUG_SEND_DATA_ONLY
#define DSA_DEBUG_REV
#define DSA_DEBUG_SEND_ID3

void DSA_Delay_us(u16 del)
{
	while(del-->0);
}
void DSA_init(void)
{
 	u8 i;
	
	for(i=0;i<8;i++)
		DSA_DATA[i]=0x00;
 	SET_DATA_READ;
 	SET_STB_READ;
 	SET_ACK_READ;
 	DSAState=DSA_Ideal;
	UI2DSA_STATE=0;
	DSA_Sdata = 0;
	disk_toc_ok=0;

	DSA_id3_frame=0;
	DSA_id3=0;
}
void DSA_clr_datapool(void)
{
 	u8 i;
	
	for(i=0;i<8;i++)
		DSA_DATA[i]=0x00;
	
	UI2DSA_STATE=0;
	DSA_Sdata = 0;
}
void DSA_clr_ID3_info()
{
	DSA_id3_frame = 1;
}
void   DSA_Detect(void)
{
	xd_u8 key_temp=0;
DSA_Loop:       
	switch (DSAState)
	{
	     case DSA_Ideal:
#ifdef DSA_DEBUG_REV			  		 	
		   //sys_printf(" DSA_Ideal ");
#endif
	       DSA_Timer=0;
           SET_DATA_READ;
		   SET_STB_READ;
 	       SET_ACK_WRITE;
 	       SET_ACK_HIGH;
		   //for (DSA_Delay=0;DSA_Delay<5;DSA_Delay++);
//		   DSA_Delay_us(6);
		   
		   DSA_Delay=0;
//		   while((GET_DATA)&&(DSA_Delay<20))
//		   	DSA_Delay++;

	          if(!GET_DATA) 
	          { 
	          	DSAState++;
			    SET_ACK_LOW;
			    goto DSA_Loop;
	          }
	        break;
	     case DSA_Sync:
#ifdef DSA_DEBUG_REV
		   sys_printf(" DSA_Sync ");
#endif		 	
	          if (DSA_Timer>250) 
	          {
	          	//DSAState=DSA_Ideal;
	             // break;
	          }
	         DSA_Delay_us(10);
//	          SET_ACK_WRITE;
	          
//		   DSA_Delay_us(6);


//		   DSA_Delay=0;
//		   while((!GET_DATA)&&(DSA_Delay<20))
//		   	DSA_Delay++;
	          if (GET_DATA) 
	          {
	           	DSAState++;
	           	SET_ACK_HIGH;
	           	goto	DSA_Loop;
//			DSA_Delay_us(6);				
	          }
		   else 
		   {
		   	DSA_Timer++;
		   }
		  break;
	     case DSA_Comm:
#ifdef DSA_DEBUG_REV			  
		   sys_printf(" DSA_Comm ");
#endif
                 SET_DATA_READ;
	          SET_ACK_WRITE;		   
		   SET_STB_READ;
		   //for (DSA_Delay=0;DSA_Delay<5;DSA_Delay++);
		   
	          DSA_Rdata=0;
	          for (DSA_Count=0;DSA_Count<16;DSA_Count++)
	           {
	           	DSA_Timer=0;
	           	while ((GET_STB)&&(DSA_Timer<620)){
					DSA_Delay_us(10);
	           	    DSA_Timer++;
	           	}
	           	//if (DSA_Timer>=600)
	              {
	              	//DSAState=DSA_Ideal;
	                  //      goto DSA_Loop;
	               }
	
	           	DSA_Rdata<<=1;	  
	           	if (GET_DATA)
	           	    DSA_Rdata |=0x01;         	
	                SET_ACK_LOW;
			//for (DSA_Delay=0;DSA_Delay<18;DSA_Delay++);
		   	//DSA_Delay_us(12);
			DSA_Timer=0;
			
	           	while ((!GET_STB)&&(DSA_Timer<250))
	           		{
				DSA_Timer++;
				DSA_Delay_us(10);	
	           		}
				
	           	if (DSA_Timer>=250)             
			{
		  		//EA =1;
				//DSAState=DSA_Ideal;
	                     //goto DSA_Loop;
			}
	               SET_ACK_HIGH;   
			 //DSA_Delay_us(12);
				   
	           }

		    DSA_REV_OK=1;			  
#if 0		  
#ifdef DSA_DEBUG			  
		    printf(" dsa -DSA_Rdata--->%x \r\n",DSA_Rdata);
#endif
		   if(((DSA_Rdata&0xFF00)==0x5500))
		   {
			 for (DSA_Delay=0;DSA_Delay<DSA_KEYNUM;DSA_Delay++)
			 {
				if ((u8)(DSA_Rdata&0x00ff)==DSA_Key[DSA_Delay][1]){
					key_temp=DSA_Key[DSA_Delay][2];
#ifdef DSA_DEBUG
					  printf(" dsa -DSA_Rdata  key--->%x \r\n",(u16)key_temp);
#endif
					  put_msg_lifo(key_temp);			  
		   		}
			 }
		   }
#endif
	          DSAState++; 
	          DSA_Timer=0;
//	          goto DSA_Loop;
//	          break;
	     case DSA_Ack:	      
#ifdef DSA_DEBUG_REV
		   sys_printf(" DSA_Ack ");
#endif			
	          if (DSA_Timer>250) 
		   {
		   	DSAState=DSA_Ideal;
	              break;
		   }
	          SET_ACK_READ;
		  DSA_Delay=0;
		   while ((DSA_Delay<250)&&(GET_ACK))
		   	{
		   	DSA_Delay_us(10);	
		   	DSA_Delay++; 
		   	}
	          SET_DATA_WRITE;
	          SET_DATA_HIGH;
	          //for (DSA_Delay=0;DSA_Delay<15;DSA_Delay++);
	   	   DSA_Delay_us(1);

	          SET_STB_WRITE;
	          SET_STB_LOW;
		   DSA_Delay_us(6);
			  
	          DSA_Timer=0;
	          DSAState++; 
	          goto DSA_Loop;
	          break;
	    case DSA_Ack2:      
#ifdef DSA_DEBUG_REV
		   sys_printf(" DSA_Ack2 ");
#endif			
	    	  if (DSA_Timer>250) 
	         {
	         	DSAState=DSA_Ideal;
	              break;
		  }
              	DSA_Delay=0;       
	         	while ((DSA_Delay<250)&&(!GET_ACK))
		   	{
		   	DSA_Delay_us(10);	
		   	DSA_Delay++; 
		   	}
	          SET_DATA_READ;
 	          SET_STB_READ;
 	          SET_ACK_READ;
	          DSAState=DSA_Ideal;
	          break;	          	          	     
        default:
	          DSAState=DSA_Ideal;
	          break;	          	          	     
        }
}



void   DSA_Send(void)
{

DSA_Loop2:       
	switch (DSAState)
	{		
	     case DSA_Ideal_Send:
#ifdef DSA_DEBUG_SEND
		   sys_printf(" DSA_Ideal_Send ");
#endif
	          SET_ACK_READ;	          
	          DSA_Timer=0;
		   //for (DSA_Delay=0;DSA_Delay<10;DSA_Delay++);
	   	   DSA_Delay_us(18);
		   
	          if (GET_ACK)
	          {
	          	SET_DATA_READ;		
  		     	//for (DSA_Delay=0;DSA_Delay<20;DSA_Delay++);
		   	DSA_Delay_us(18);

	          	if (!GET_DATA)
			{
				DSAState=DSA_Ideal;
		           	break;
	           	}
	          }
	        SET_DATA_WRITE;
 	        SET_STB_WRITE;		
		 //for (DSA_Delay=0;DSA_Delay<15;DSA_Delay++);
	   	 DSA_Delay_us(12);

		 SET_STB_HIGH;		
		 SET_DATA_LOW;
	   	 DSA_Delay_us(6);

           		DSA_Delay=0;			
			while ((DSA_Delay<WAITE_ACK_DELAY_TIME)&&(GET_ACK)){
			       DSA_Delay++;
				 DSA_Delay_us(6);
			}

		        if (!GET_ACK) 
		        { 
		        
		        	DSAState++;
				goto DSA_Loop2;
		        }		 
			else
			{
				DSAState=0;
			}
	          break;
	     case DSA_Sync_Send:
#ifdef DSA_DEBUG_SEND
		  sys_printf(" DSA_Sync_Send ");
#endif		 	
	         if (DSA_Timer>3) 
	         {
	         	DSAState=DSA_Ideal_Send;
                  	break;
		   }
	          SET_DATA_HIGH;
		   DSA_Delay_us(6);
			  
           	   DSA_Delay=0;
		   while ((DSA_Delay<600)&&(!GET_ACK)){
		   	DSA_Delay++; 
			DSA_Delay_us(10);
		   }
	          if (GET_ACK) 
	          {
	           	DSAState++;
	           	goto DSA_Loop2;
	          }
		   else
		   {
		   	DSA_Timer++;
		   }	  
	          break;
	     case DSA_Comm_Send:
#ifdef DSA_DEBUG_SEND
		 sys_printf(" DSA_Comm_Send ");
#endif
	        SET_DATA_WRITE;
 	        SET_STB_WRITE;		
          	 SET_ACK_READ;	        
	   	 DSA_Delay_us(12);

#if defined(DSA_DEBUG_SEND)||defined(DSA_DEBUG_SEND_DATA_ONLY)
			printf(" dsa -DSA_Comm_Send--->%x \r\n",DSA_Sdata);
#endif			 
	          DSA_Sdata_backup=DSA_Sdata;
	          for (DSA_Count=0;DSA_Count<16;DSA_Count++)
	           {

	           	DSA_Timer=0;
	           	if (DSA_Sdata&0x8000)
	           	   SET_DATA_HIGH;
	           	   else  
	           	   SET_DATA_LOW;
	           	DSA_Sdata<<=1;	
		   	DSA_Delay_us(12);
				
	           	SET_STB_LOW;
		   	DSA_Delay_us(8);				
	           	while ((GET_ACK)&&(DSA_Timer<300))
	           	{
	           		DSA_Delay_us(6);
	           	       DSA_Timer++;
	           	}
	           	if (DSA_Timer>=300) 
			{
				DSAState=DSA_Ideal;
	            	          DSA_Sdata=DSA_Sdata_backup;
	                          goto DSA_Loop2;
			}
	               SET_STB_HIGH;
			 DSA_Delay_us(6);
					
	           	while ((!GET_ACK)&&(DSA_Timer<300)){
	           	             DSA_Timer++;
				      DSA_Delay_us(6);							 
	           	}
	           	if (DSA_Timer>=300)
			{
				DSAState=DSA_Ideal;
	            	          DSA_Sdata=DSA_Sdata_backup;
	                        goto DSA_Loop2;
			}
	           }
		   DSA_Sdata =0;
	          DSAState++; 
	          DSA_Timer=0;
	          goto DSA_Loop2;
	          break;
	     case DSA_Ack_Send:
#ifdef DSA_DEBUG_SEND
		   sys_printf(" DSA_Ack_Send ");
#endif		 	
	          if (DSA_Timer>3) 
	          {
	          	   DSAState=DSA_Ideal;
         	          DSA_Sdata=DSA_Sdata_backup;
	              break;
	          }
	          SET_STB_READ;
	          SET_DATA_READ;		   
	          SET_ACK_WRITE;
		   //for (DSA_Delay=0;DSA_Delay<10;DSA_Delay++);
   	   	   DSA_Delay_us(12);
	          SET_ACK_LOW;
  	   	   DSA_Delay_us(8);
                 DSA_Delay=0;  
		   while ((DSA_Delay<WAITE_ACK_DELAY_TIME)&&(GET_STB)){
			  DSA_Delay++; 
			  DSA_Delay_us(2);							 
		   }
   	          if (GET_STB) break;	                	          
                  if (!GET_DATA) 
           	          DSA_Sdata=DSA_Sdata_backup;
	          SET_ACK_HIGH;
		   DSA_Delay_us(6);
			  
	          DSA_Timer=0;
	          DSAState++; 
	          goto DSA_Loop2;
	          break;
	    case DSA_Ack2_Send: 
#ifdef DSA_DEBUG_SEND
		   sys_printf(" DSA_Ack2_Send ");
#endif			
	    	  if (DSA_Timer>3) 
	         {
	         	DSAState=DSA_Ideal;
	              break;
	          }
	          //for (DSA_Delay=0;DSA_Delay<200;DSA_Delay++);          
 	           DSA_Delay_us(200);

	           SET_DATA_READ;
 	           SET_STB_READ;
 	           SET_ACK_READ;
 	           DSA_Delay_us(6);

	          DSAState=DSA_Ideal;
	          break;	         
        default:
               DSAState=DSA_Ideal;
               break; 	          	     
        }	
}	
void UI_2_DSA(void)
{
	if (DSA_Sdata==0)
	{	
		DSA_flag=0;

#ifdef DSA_ID3_FUNC
		
		if ((UI2DSA_STATE>=0xA0)&&(UI2DSA_STATE<=0xEF)&&(id3_tag_len>0)){

			if(DSA_id3_frame){

				switch(DSA_id3){
					case 0:
						DSA_flag=0xA0<<8;
						DSA_flag |=id3_artist_len;
						DSA_Sdata = DSA_flag;       
						DSA_id3=1;
						break;
					case 1:
						DSA_flag=0xA1<<8;
						DSA_flag |=id3_alb_len;
						DSA_Sdata = DSA_flag;       
						DSA_id3=2;
						break;
					case 2:
						DSA_flag=0xA2<<8;
						DSA_flag |=id3_title_len;
						DSA_Sdata = DSA_flag;       
						DSA_id3=3;
						
						UI2DSA_STATE =0xA3;
						//DSA_id3_frame=0;
						
						break;	
					case 3:
						
						DSA_flag=id3_tag_buf[UI2DSA_STATE-0xA3];
						DSA_flag|=UI2DSA_STATE<<8;
						DSA_Sdata=DSA_flag;					

#ifdef DSA_DEBUG_SEND_ID3
						printf(" -UI_2_DSA--->%x \r\n",(u16)DSA_Sdata);
#endif

						UI2DSA_STATE++;

						if((UI2DSA_STATE-0xA3)>id3_tag_len){

							DSA_id3=0;
							DSA_id3_frame=0;
							UI2DSA_STATE=0;
						}
						break;
					default:

						UI2DSA_STATE=0;
						DSA_id3_frame=0;
						break;
				}

#ifdef DSA_DEBUG_SEND_ID3
		printf(" -UI_2_DSA--->%x \r\n",(u16)DSA_Sdata);
#endif
				
			}
			else{				

#if 0
				DSA_flag=id3_tag_buf[UI2DSA_STATE-0xA3];
				DSA_flag|=UI2DSA_STATE<<8;
				DSA_Sdata=DSA_flag;					

#ifdef DSA_DEBUG_SEND_ID3
		printf(" -UI_2_DSA--->%x \r\n",(u16)DSA_Sdata);
#endif

				UI2DSA_STATE++;

				if((UI2DSA_STATE-0xA3)>id3_tag_len){

					UI2DSA_STATE=0;
				}
#endif			
				DSA_id3=0;
				DSA_id3_frame=0;
				UI2DSA_STATE=0;
			}	
		}
		else
#endif			
		{

			switch(UI2DSA_STATE)	
			{
				case 0xFA:
					DSA_flag|=0xFA<<8;

					if(device_online==0){					
						//DSA_flag |= 0x04;
					}
					else{

#if 1
						DSA_flag |= 0x04;

						if((device_online&BIT(0))>0){		
							DSA_flag |= 0x40;
						}
						
						if((device_online&BIT(1))>0){		

							DSA_flag |= 0x80;
						}
#else
						if(DSA_SEL_DEV == DEVICE_SDMMC0){
							
							if((device_online&0x01)==0){
									DSA_flag |= 0x04;
							}
						}
						else if(DSA_SEL_DEV == DEVICE_UDISK){

							if((device_online&0x02)==0){
									DSA_flag |= 0x04;
							}
						}
#endif						

					}
					
					if(DSA_SEL_DEV == DEVICE_SDMMC0){
							
						DSA_flag |= 0x01;
					}
					else if (DSA_SEL_DEV == DEVICE_UDISK){
							
						DSA_flag |= 0x02;
					}					
					
					if(play_status == MAD_PLAY){
						DSA_flag |=0x08;
						
					}
					else if(play_status == MAD_STOP){
						DSA_flag |=0x20;
					}
#if 0
					if(play_mode == REPEAT_ONE){
						DSA_flag |=0x40;
					}
					else if(play_mode == REPEAT_FOLDER){
						DSA_flag |=0x80;
					}
					else if(play_mode == REPEAT_ALL){
						DSA_flag |=0xC0;
					}
#endif
					if(DSA_DATA[0] != DSA_flag)
					DSA_Sdata =	DSA_flag;       
					DSA_DATA[0] = DSA_flag;
					UI2DSA_STATE=0xFB;
					break;
					
				case 0xFB:
					DSA_flag|=0xFB<<8;

					if(disk_toc_ok)
						DSA_flag |=0x01;
					if(music_type == IS_WMA){
						DSA_flag |=0x02;
					}


					if(play_mode == REPEAT_ONE){
						DSA_flag |=0x08;
					}
					else if(play_mode == REPEAT_FOLDER){
						DSA_flag |=0x10;
					}
					else if(play_mode == REPEAT_ALL){
						DSA_flag |=0x20;
					}
					else if(play_mode == REPEAT_OFF){
						DSA_flag |=0x40;
					}					
					else if(play_mode == REPEAT_OFF){
						DSA_flag |=0x80;
					}	
					
					if(DSA_DATA[1] != DSA_flag)
					DSA_Sdata=DSA_flag;
					DSA_DATA[1] = DSA_flag;
					UI2DSA_STATE=0x10;
					break;
				
				case 0xF9:
					DSA_flag|=0xF9<<8;				

	    				file_play_time =dec_msg->play_time;
						
	     				min = (u8)(file_play_time/60);
						
					DSA_flag |= min;
					
					if(DSA_DATA[2] != DSA_flag)
					DSA_Sdata=DSA_flag;  
					DSA_DATA[2] = DSA_flag;
					
					UI2DSA_STATE=0xF7;
					break;

				case 0xF7:
					DSA_flag|=0xF7<<8;
					
	    				file_play_time =dec_msg->play_time;
						
	    				sec = (u8)(file_play_time%60);
					DSA_flag |= sec;

					if(DSA_DATA[3]!= DSA_flag)
					DSA_Sdata=	 DSA_flag;    		
					DSA_DATA[3] = DSA_flag;
					UI2DSA_STATE=0xFA;
					break;
					
				case 0x10:
					DSA_flag|=0x10<<8;
					
					DSA_flag |= (given_file_number&0x0FFF);

					if(DSA_DATA[4]!= DSA_flag)
					DSA_Sdata=	 DSA_flag;    		
					DSA_DATA[4] = DSA_flag;
					UI2DSA_STATE=0x20;
					break;

				case 0x20:
					DSA_flag|=0x20<<8;
					
					DSA_flag |= (fs_msg.fileTotal)&0x0FFF;

					if(DSA_DATA[5]!= DSA_flag)
					DSA_Sdata=	 DSA_flag;    		
					DSA_DATA[5] = DSA_flag;
#ifdef DSA_ID3_FUNC
					if(DSA_id3_frame){
						DSA_id3 = 0;
						//DSA_id3_frame=1;
						UI2DSA_STATE=0xA0;
					}
					else{					

						UI2DSA_STATE=0xF9;
					}
#else
						UI2DSA_STATE=0x30;
#endif
					break;

				case 0x30:
					DSA_flag|=0x30<<8;
					
					DSA_flag |= (fs_msg.dirNum)&0x0FFF;

					if(DSA_DATA[6]!= DSA_flag)
					DSA_Sdata=	 DSA_flag;    		
					DSA_DATA[6] = DSA_flag;
					UI2DSA_STATE=0x40;
					break;	

				case 0x40:
					DSA_flag|=0x40<<8;

					DSA_flag |= (fs_info.dirTotal)&0x0FFF;;

					if(DSA_DATA[7]!= DSA_flag)
					DSA_Sdata=	 DSA_flag;    		
					DSA_DATA[7] = DSA_flag;
					
					UI2DSA_STATE=0xF9;
					
					break;					
				default:
					UI2DSA_STATE=0xFA;
					break;
				}
			}	

#ifdef DSA_DEBUG
		printf(" -UI_2_DSA--->%x \r\n",(u16)DSA_flag);
#endif
		
		}	

}
void DSA_if_hdlr(void)
{
	xd_u8 dsa_key=0;
	DSA_Detect();

	if(DSA_REV_OK){

		DSA_REV_OK =0;
#if 1		  
#ifdef DSA_DEBUG_REV_KEY			  
			    printf(" dsa -DSA_Rdata--->%x \r\n",DSA_Rdata);
#endif
			   if(((DSA_Rdata&0xFF00)==0x5500))
			   {
				 for (DSA_Delay=0;DSA_Delay<DSA_KEYNUM;DSA_Delay++)
				 {
					if ((u8)(DSA_Rdata&0x00ff)==DSA_Key[DSA_Delay][1]){
						dsa_key=DSA_Key[DSA_Delay][2];
#ifdef DSA_DEBUG_REV_KEY
						  printf(" dsa -DSA_Rdata  key--->%x \r\n",(u16)dsa_key);
#endif
						  put_msg_lifo(dsa_key);			  
			   		}
				 }
			   }
#endif
	}
	
	if ((DSA_Sdata)&&(DSAState==0))
	{
		DSAState=10;
		DSA_Send();
	}
	else
	{
		DSA_Send();
	}	

	//EA =1;
	if(gether_info_timer++>5){
		gether_info_timer =0;

		//if(work_mode <SYS_FMREV)
			UI_2_DSA();
	}
}
#endif
