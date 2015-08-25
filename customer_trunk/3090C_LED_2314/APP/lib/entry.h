/*--------------------------------------------------------------------------*/
/**@file   entry.h
   @brief  接口函数头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef _ENTRY_
#define _ENTRY_

#include "typedef.h"
#include "tff.h"
#include "music.h"

#ifdef __C51__

/*----------------------------------------------------------------------------*/
/**@brief   数据初始化
   @param   s:数据地址，必须为XDATA地址
   @param   volume:初始化的设定值
   @param   len:初始化数据的长度
   @note    无
*/
/*----------------------------------------------------------------------------*/
void my_memset(u8 _xdata *s, u8 volume, u16 len);
/*----------------------------------------------------------------------------*/
/**@brief   数据转换
   @param   ptr:数据地址，必须为XDATA地址
   @note    无
*/
/*----------------------------------------------------------------------------*/
u16 int2(u8 _xdata *ptr);
u32 int3(u8 _xdata *ptr);
u32 int4(u8 _xdata *ptr);

u16 int2_l(u8 _xdata *ptr);
u32 int3_l(u8 _xdata *ptr);
u32 int4_l(u8 _xdata *ptr);

/*----------------------------------------------------------------------------*/
/**@brief   数据拷贝
   @param   s1:目标数据地址，必须为XDATA地地址
   @param   s2:源数据地址，必须为XDATA地地址
   @param   len:拷贝的数据长度
   @note    无
*/
/*----------------------------------------------------------------------------*/
void my_memcpy(u8 _xdata *s1, u8 _xdata *s2, u16 len);
/*----------------------------------------------------------------------------*/
/**@brief   SD 在线检测
   @param   无
   @note    void sd_online_check(void)
*/
/*----------------------------------------------------------------------------*/
void sd_online_check(void);
/*----------------------------------------------------------------------------*/
/**@brief   USB在线检测
   @param   无
   @note    void usb_polling(void)
*/
/*----------------------------------------------------------------------------*/
void usb_polling(void);
/*----------------------------------------------------------------------------*/
/**@brief    设置SD卡的速度参数
   @param    high : SD 卡高速的BAUD; low : SD 卡低速的BAUD;
   @return   无
   @note     void sd_speed_init(u8 high,u8 low)
*/
/*----------------------------------------------------------------------------*/
void sd_speed_init(u8 high, u8 low);
/*----------------------------------------------------------------------------*/
/**@brief   SD模块初始化，初始化参数已经寄存器
   @param   无
   @return  无
   @note    void init_port_sd(void)
*/
/*----------------------------------------------------------------------------*/
void init_port_sd(void);
/*----------------------------------------------------------------------------*/
/**@brief   获取设备在线状态
   @param   无
   @return  bit0:SDMMC; bit1:USB disk;  bit4:PC;
   @note    u8 get_device_online_status(void)
*/
/*----------------------------------------------------------------------------*/
u8 get_device_online_status(void);
/*----------------------------------------------------------------------------*/
/**@brief    配置USB从机模式下，枚举成哪些设备
   @param    BIT1：USB_SPEAKER， BIT2：USB_HID， BIT3：USB_MASS， 可以同时配置枚举多个设备
   @return	 无
   @note	 void usb_config(u8)
*/
/*----------------------------------------------------------------------------*/
void usb_config(u8);
/*----------------------------------------------------------------------------*/
/**@brief    设置SDMMC的写保护
   @param    1：写保护已打开，0：写保护未打开
   @return	 无
   @note	 void write_protect_set(u8)
*/
/*----------------------------------------------------------------------------*/
void write_protect_set(u8);
/*----------------------------------------------------------------------------*/
/**@brief  初始化USB PHY到从机状态
   @param  无
   @return 无
   @note   void init_usb_device_hardware(void)
*/
/*----------------------------------------------------------------------------*/
void init_usb_device_hardware(void);
/*----------------------------------------------------------------------------*/
/**@brief   USB UFI massstorage 处理
   @param   无
   @return  1:massstorage正在传送数据， 0：massstorage处于空闲
   @note     void UFI_massstorage(void)
*/
/*----------------------------------------------------------------------------*/
bool UFI_massstorage (void);
/*----------------------------------------------------------------------------*/
/**@brief   SD鉴定
   @param
   @return  1:成功；0：失败
   @note    bool init_sd(void)
*/
/*----------------------------------------------------------------------------*/
bool init_sd(void);
/*----------------------------------------------------------------------------*/
/**@brief    解码控制
   @param    cmd  : 解码控制命令
   @param    para : 解码控制参数
   @return
   @note    bool mad_control(u8 cmd, s16 para)
*/
/*----------------------------------------------------------------------------*/
void mad_control(u8, u8);
/*----------------------------------------------------------------------------*/
/**@brief    部分中断服务程序初始化，软中断、USB中断、SD卡中断、解码中断和ADSP中断
   @param    无
   @return	 无
   @note    void bsp_init(void)
*/
/*----------------------------------------------------------------------------*/
void bsp_init(void);
/*----------------------------------------------------------------------------*/
/**@brief    检测是否有事件发生
   @param    无
   @return	 1：有事件；0xff：没有事件
   @note    u8 check_event(u8 event)
*/
/*----------------------------------------------------------------------------*/
u8 check_event(u8 event);
/*----------------------------------------------------------------------------*/
/**@brief    写入事件
   @param    event：事件
   @return	 无
   @note    void put_event(u8 event)
*/
/*----------------------------------------------------------------------------*/
void put_event(u8 event);
/*----------------------------------------------------------------------------*/
/**@brief    清除指定的一个事件
   @param    event：事件
   @return	 无
   @note    void clear_one_event(u8 event)
*/
/*----------------------------------------------------------------------------*/
void clear_one_event(u8 event);
/*----------------------------------------------------------------------------*/
/**@brief    清除所有事件
   @param    无
   @return	 无
   @note    void clear_all_event(void)
*/
/*----------------------------------------------------------------------------*/
void clear_all_event(void);
/*----------------------------------------------------------------------------*/
/**@brief    获取已有事件
   @param    无
   @return	 已有的事件
   @note    void clear_all_event(void)
*/
/*----------------------------------------------------------------------------*/
u8 get_event(void);
/*----------------------------------------------------------------------------*/
/**@brief    开始并初始化
   @param    channel：AMUX通道
   @param	 buf：存储缓存
   @return	 已有的事件
   @note    void recording_start(u8 channel, u8 _xdata *buf)
*/
/*----------------------------------------------------------------------------*/
void recording_start(u8 channel, u8 _xdata *buf);
/*----------------------------------------------------------------------------*/
/**@brief    结束
   @param    channel：AMUX通道
   @param    buf：存储缓存
   @return	 已有的事件
   @note    void recording_end(void)
*/
/*----------------------------------------------------------------------------*/
void recording_end(void);
/*----------------------------------------------------------------------------*/
/**@brief    突然掉电下的记忆函数
   @param    无
   @return	 无
   @note    void burst_out_break_point_save(void)
*/
/*----------------------------------------------------------------------------*/
void burst_out_break_point_save(void);


/*----------------------------------------------------------------------------*/
/**@brief   SD 卡读接口函数
   @param   lbaL: LBA的低16位
   @param   lbaH: LBA的高16位
   @param   *buf 读BUFF
   @return  0：成功读取；其他读取失败
   @note    u8 sdmmc_read(u16 lbal, u16 lbah, u8 _xdata *buf)
*/
/*----------------------------------------------------------------------------*/
u8 sdmmc_read(u16 lbal, u16 lbah, u8 _xdata *buf);
/*----------------------------------------------------------------------------*/
/**@brief    设置查找文件的类型
   @param    * str 指向一个放在CODE区的数组，数组中存放文件格式的字符串
   @return   无
   @note     void fs_ext_setting(u8 _code * str)
*/
/*----------------------------------------------------------------------------*/
void fs_ext_setting(u8 _code * str);
/*----------------------------------------------------------------------------*/
/**@brief   全设备查找文件
   @param   无
   @return  无
   @note    void fs_scan_disk(void)
*/
/*----------------------------------------------------------------------------*/
u16 fs_scan_disk(u16 break_point);
/*----------------------------------------------------------------------------*/
/**@brief   根据文件序号找文件
   @param   fileNumber ： 查找的文件的文件序号
   @return  无
   @note    bool fs_getfile_bynumber(u16 fileNumber)
*/
/*----------------------------------------------------------------------------*/
u8 fs_getfile_bynumber(u8 file_index, FIL _xdata* ptr, u16 fileNumber);
/*----------------------------------------------------------------------------*/
/**@brief   获取当前文件的长文件名
   @param   *buffer ：存放长文件名的BUFE的指针
   @return  1:成功获取长文件名； 0:没有长文件名
   @note    bool fs_getfile_longname(u8 _xdata *buffer)
*/
/*----------------------------------------------------------------------------*/
bool fs_getfile_longname(u8 _xdata *buffer);
/*----------------------------------------------------------------------------*/
/**@brief   USB disk 枚举
   @param   *buf 枚举试读的buffer指针
   @return  0：失败；1：成功；
   @note    bool usb_host_emuerate_devcie(u8 _xdata *buf, u8 android_delay)
*/
/*----------------------------------------------------------------------------*/
bool usb_host_emuerate_devcie(u8 _xdata *buf, u8 android_delay);
/*----------------------------------------------------------------------------*/
/**@brief   USB mass storage 读接口函数： 此函数编译后的结果绝对不能用到 DATA GROUP,所以不能随便修改
   @param   *buf 读BUFF
   @param   lbaH: LBA的高16位
   @param   lbaL: LBA的低16位
   @return  0：成功读取；其他读取失败
   @note     u8 io_read_usb(u8 _xdata *buf, u16 lbah, u16 lbal)
*/
/*----------------------------------------------------------------------------*/
u8 read_usb(u16 lbaL, u16 lbaH, u8 _xdata * buffer);
/*----------------------------------------------------------------------------*/
/**@brief   获取U盘单个扇区的大小
   @param   无
   @return  单个扇区大小/512
   @note    u8 get_usb_device_pkt_size(void)
*/
/*----------------------------------------------------------------------------*/
u8 get_usb_device_pkt_size(void);
/*----------------------------------------------------------------------------*/
/**@brief   解码EQ开关函数
   @param   on_off：开关
   @return  无
   @note     void decode_eq_switch(u8 on_off)
*/
/*----------------------------------------------------------------------------*/
void decode_eq_switch(u8 on_off);
/*----------------------------------------------------------------------------*/
/**@brief   提供文件信息给断点使用
   @param   文件指针
   @return  ido
   @note    u16 read_file_id(FIL _xdata * file_ptr)
*/
/*----------------------------------------------------------------------------*/
u16 read_file_id(FIL _xdata * file_ptr);

////////////////////////////////////////////////
/*----------------------------------------------------------------------------*/
/**@brief   在MS中断中调用，为BSP提供一个MS的中断
   @param   无
   @return  无
   @note   void dec_delay_counter(void)
*/
/*----------------------------------------------------------------------------*/
void dec_delay_counter(void);
/*----------------------------------------------------------------------------*/
/**@brief   延时，最小单位为调用 dec_delay_counter()函数所在的timer
   @param   delay：延时参数
   @return  无
   @note    void delay_10ms(u8 delay)
*/
/*----------------------------------------------------------------------------*/
void delay_10ms(u8);
/*----------------------------------------------------------------------------*/
/**@brief   延时
   @param   delay：延时参数
   @return  无
   @note    void delay(u16)
*/
/*----------------------------------------------------------------------------*/
void delay(u16);
/*----------------------------------------------------------------------------*/
/**@brief   推一个先进先出的消息到消息池，低优先级
   @param   msg：低优先级的消息
   @return  无
   @note    void put_msg_fifo(u8 msg)
*/
/*----------------------------------------------------------------------------*/
void put_msg_fifo(u8);
/*----------------------------------------------------------------------------*/
/**@brief   推一个后进先出的消息到消息池，高优先级
   @param   msg：高优先级的消息
   @return
   @note    void put_msg_lifo(u8 msg)
*/
/*----------------------------------------------------------------------------*/
void put_msg_lifo(u8);
/*----------------------------------------------------------------------------*/
/**@brief   获取消息池的消息
   @param   无
   @return  消息
   @note    u8 get_msg(void)
*/
/*----------------------------------------------------------------------------*/
u8 get_msg(void);
/*----------------------------------------------------------------------------*/
/**@brief  清空消息池中的低优先级消息
   @param   无
   @return  无
   @note   void flush_low_msg(void)
*/
/*----------------------------------------------------------------------------*/
void flush_low_msg(void);
/*----------------------------------------------------------------------------*/
/**@brief  清空消息池中的所有消息
   @param   无
   @return  无
   @note   void flush_all_msg(void)
*/
/*----------------------------------------------------------------------------*/
void flush_all_msg(void);
/*----------------------------------------------------------------------------*/
/**@brief   文件系统偏移函数
   @param   offset    type
   @return  0:成功；其他：失败
   @note    u8 f_seek(u8 type, u32 offset)
*/
/*----------------------------------------------------------------------------*/
u8  f_seek (u8 type, u16 offsetl, u16 offseth);
/*----------------------------------------------------------------------------*/
/**@brief   文件系统度函数
   @param   file_index ：文件句柄序号
   @param   buffer ：读取的数据的buffer
   @param   len:需要读取的数据的长度
   @return  0:成功；其他：失败
   @note    u16 f_read (u8 file_index, u8 _xdata *buffer, u16 len)
*/
/*----------------------------------------------------------------------------*/
u16 f_read (u8 file_index, u8 _xdata *buffer, u16 len);
/*----------------------------------------------------------------------------*/
/**@brief   查询文件状态
   @param   file_index ：文件句柄序号
   @return  0:成功；其他：文件错误
   @note    u8 f_tell_status(u8 file_index)
*/
/*----------------------------------------------------------------------------*/
u8 f_tell_status(u8 file_index);
/*----------------------------------------------------------------------------*/
/**@brief    获得文件大小
   @param    无
   @return   u32 以字节为单位的文件大小
   @note     u32 f_tell_fsize(u8 file_index)
*/
/*----------------------------------------------------------------------------*/
u32 f_tell_fsize(u8 file_index);
/*----------------------------------------------------------------------------*/
/**@brief    获取文件读指针
   @param    无
   @return   指针位置
   @note     u32 f_tell_fptr(u8 file_index)
*/
/*----------------------------------------------------------------------------*/
u32 f_tell_fptr(u8 file_index);
/*----------------------------------------------------------------------------*/
/**@brief    获取文件長文件名
   @param    dj ： 文件目录
   @param    dindex ：文件目录项的序号
   @param    buffer	：存放文件名的BUFF 2KB
   @return   指针位置
   @note     bool f_getfilename(u8 _xdata * dj, u16 dindex, u8 _xdata *buffer)
*/
/*----------------------------------------------------------------------------*/
bool f_getfilename(u8 _xdata * dj, u16 dindex, u8 _xdata *buffer);

/*----------------------------------------------------------------------------*/
/**@brief     打开文件，最多打开四个
   @param  	  file_index ：文件句柄序号
   @param  	  *ptr	：文件BUFF 512B
   @param  	  finfo	：文件信息，用于打开文件
   @return    0：成功；非0：失败
   @note      u8  f_open(u8 file_index, u8 _xdata *ptr, u8 _xdata * finfo)
*/
/*----------------------------------------------------------------------------*/
u8  f_open(u8 file_index, u8 _xdata *ptr, u8 _xdata * finfo);
/*----------------------------------------------------------------------------*/
/**@brief     打开一个目录
   @param     *dj 目录的路径的指针
   @return    无
   @note      void  f_opendir(u8 _xdata * dj)
*/
/*----------------------------------------------------------------------------*/
void  f_opendir(u8 _xdata * dj);
/*----------------------------------------------------------------------------*/
/**@brief     查找文件系统
   @param     无
   @return    0:成功：其他：失败
   @note      u8 f_mount(void)
*/
/*----------------------------------------------------------------------------*/
u8  f_mount(void);

void f_init(u8 _xdata * buf, u16 io_read, u8 sector_sizeof512);
/*----------------------------------------------------------------------------*/
/**@brief   文件系统初始化
   @param   * buf ：为文件系统读提供的BUFF
   @param   io_read ：设备读指针
   @param   sector_sizeof512 ： 512的倍数
   @return  无效
   @note    u8 f_init(u8 _xdata * buf, u16 io_read, u8 sector_sizeof512)
*/
/*----------------------------------------------------------------------------*/
void file_io_init(void);
/*----------------------------------------------------------------------------*/
/**@brief   WAV解码函数
   @param   无
   @return  无
   @note    void WMA_decode(void)
*/
/*----------------------------------------------------------------------------*/
void WMA_decode(void);
/*----------------------------------------------------------------------------*/
/**@brief   音乐文件格式的检测
   @param   解码buffer 2KB
   @return  文件的格式
   @note    u8 music_format_check(u8 _xdata *)
*/
/*----------------------------------------------------------------------------*/
u8 music_format_check(u8 _xdata *);

/*----------------------------------------------------------------------------*/
/**@brief   获取ID3v2信息的长度
   @param   无
   @return  ID3v2信息的长度，字节为单位
   @note    u32 ff_get_id3v2_len(void)
*/
/*----------------------------------------------------------------------------*/
u32 ff_get_id3v2_len(void);

/*----------------------------------------------------------------------------*/
/**@brief   检测MP3文件
   @param   无
   @return  0失败 1成功
   @note    bool get_mp3_total_time(void)
*/
/*----------------------------------------------------------------------------*/
bool get_mp3_total_time(void);

/*----------------------------------------------------------------------------*/
/**@brief   发送HID命令
   @param   KEY:USB HID命令
   @return  无
   @note    void usb_hid_key(u8 key)
*/
/*----------------------------------------------------------------------------*/
void usb_hid_key(u8 key);

/*----------------------------------------------------------------------------*/
/**@brief   启动EQ设置函数
   @param   dsp工作状态
   @return  无
   @note    void dsp_set_eq_mode(unsigned char n)
*/
/*----------------------------------------------------------------------------*/
void dsp_set_eq_mode(unsigned char n);

/*----------------------------------------------------------------------------*/
/**@brief   EQ设置函数
   @param   ppp：EQ表
   @return  无
   @note    void dsp_set_eq_coeff(unsigned short *ppp)
*/
/*----------------------------------------------------------------------------*/
void dsp_set_eq_coeff(unsigned short *ppp);

/*----------------------------------------------------------------------------*/
/**@brief   左右声道反相
   @param   0x0: 右声道不反相；0x1: 右声道反相
   @return  无
   @note    void dsp_set_rinv_mode(unsigned char n)
*/
/*----------------------------------------------------------------------------*/
void dsp_set_rinv_mode(unsigned char n);
/*----------------------------------------------------------------------------*/
/**@brief   设置声道模式(单声道，立体声)
   @param   0x0: Lout=left, Rout=right;0x1: Lout=Rout=(left+right)/2 ;0x2: Lout=Rout=(left-right)/2
   @return  无
   @note    void dsp_set_ch_mode(unsigned char n)
*/
/*----------------------------------------------------------------------------*/
void dsp_set_ch_mode(unsigned char n);
/*----------------------------------------------------------------------------*/
/**@brief   解码函数初始化
   @param   无
   @return  无
   @note    void fs_fun_init(void)
*/
/*----------------------------------------------------------------------------*/
void fs_fun_init(void);

/*----------------------------------------------------------------------------*/
/**@brief   获取频谱运算结果
   @param   para :1~255(建议取值 1~2；取值越大，频谱数据越小)
   @return  无
   @note    void music_spec_cul(u8 para)
*/
/*----------------------------------------------------------------------------*/
//void music_spec_cul(u8 para);
/*----------------------------------------------------------------------------*/
/**@brief   读RTC寄存器
   @param   无
   @return  寄存器值
   @note    u8 read_rtc_reg(void)
*/
/*----------------------------------------------------------------------------*/
u8 read_rtc_reg(void);
/*----------------------------------------------------------------------------*/
/**@brief 写RTC寄存器
   @param 	cmd：寄存器值
   @return  void
   @note  void write_rtc_reg(u8 cmd)
*/
/*----------------------------------------------------------------------------*/
void write_rtc_reg(u8 cmd);
/*----------------------------------------------------------------------------*/
/**@brief 写RTC RAM操作
   @param addr:RAM地址；dat:写入RAM的值0~63
   @return  无
   @note void write_rtc_ram(u8 addr,u8 dat)
*/
/*----------------------------------------------------------------------------*/
void write_rtc_ram(u8 addr,u8 dat);
/*----------------------------------------------------------------------------*/
/**@brief 读RTC RAM操作
   @param addr：RAM地址 0~63
   @return  RAM地址数据
   @note u8 read_rtc_ram(u8 addr)
*/
/*----------------------------------------------------------------------------*/
u8 read_rtc_ram(u8 addr);

/*----------------------------------------------------------------------------*/
/**@brief 读写RTC ALM时间寄存器
   @param 读写入的时间参数，
   @return  读出的数据
   @note u8 irtc_sr_byte(u8 x)
*/
/*----------------------------------------------------------------------------*/
u8 irtc_sr_byte(u8 x);
/*----------------------------------------------------------------------------*/
/**@brief 中断初始化
   @param vector：中断向量
   @param *pra：中断服务程序
   @return  无
   @note void interrupt_init(u8 vector, void _code * pra)
*/
/*----------------------------------------------------------------------------*/
void interrupt_init(u8 vector, void _code * pra);

/*----------------------------------------------------------------------------*/
/**@brief 文件系统初始化
   @param ： sector_sizeof512 单个扇区512的倍数
   @return  无
   @note u8 f_mount_bsp(u8 sector_sizeof512)
*/
/*----------------------------------------------------------------------------*/
extern u8  f_mount_bsp(u8 sector_sizeof512);

/*----------------------------------------------------------------------------*/
/**@brief SDMMC进入动态省电模式，在解码任务的循环中调用，可以减小SDMMC卡的功耗，但会增加系统3.3V电源的波动
   @param ： 无
   @return  无
   @note
*/
/*----------------------------------------------------------------------------*/
void suspend_sdmmc(void);
/*----------------------------------------------------------------------------*/
/**@brief 	系统供电保持。如果系统进入掉电模式后，通过wakeup pin唤醒后，需执行此函数来保持系统的电源
   @param	无
   @return  无
   @note   	
*/
/*----------------------------------------------------------------------------*/
void core_power_on(void);

/*----------------------------------------------------------------------------*/
/**@brief 	系统进入掉电模式，必须通过wake up pin或系统重新上电才能重新工作
   @param	无
   @return  无
   @note   	
*/
/*----------------------------------------------------------------------------*/
void core_power_off(void);
/*----------------------------------------------------------------------------*/
/**@brief 	设置USB模块进入Suspend Mode
   @param	mode 0:退出Suspend Mode；1：进入Suspend Mode
   @return  无
   @note   	void usb_suspend_mode(u8 mode)
*/
/*----------------------------------------------------------------------------*/
void usb_suspend(void);

void dsp_set_dcc_flt(u8);

/*----------------------------------------------------------------------------*/
/**@brief 	录音时设备文件系统初始化
   @param	dev：活动设备
   @return  无
   @note   	u8 f_write_init(u8 dev)
*/
/*----------------------------------------------------------------------------*/
u8 f_write_init(u8 dev);
/*----------------------------------------------------------------------------*/
/**@brief 	录音开始
   @param	
   @return  无
   @note   	u8 bsp_start_encode(u8)
*/
/*----------------------------------------------------------------------------*/
u8 bsp_start_encode(u8 );
/*----------------------------------------------------------------------------*/
/**@brief 	录音结束
   @param	无
   @return  无
   @note   	void stop_encode(void)
*/
/*----------------------------------------------------------------------------*/
void stop_encode(void);
/*----------------------------------------------------------------------------*/
/**@brief 	录音暂停
   @param	无
   @return  无
   @note   	void pause_encode(void)
*/
/*----------------------------------------------------------------------------*/
void pause_encode(void);
/*----------------------------------------------------------------------------*/
/**@brief 	录音暂停后录音继续
   @param	无
   @return  无
   @note   	void continue_encode(void)
*/
/*----------------------------------------------------------------------------*/
void continue_encode(void);
/*----------------------------------------------------------------------------*/
/**@brief 	录音通道设置
   @param	channel： 0：fm   1：linein     2：mic
   @return  无
   @note   	void set_rec_channel(u8 channel)
*/
/*----------------------------------------------------------------------------*/
void set_rec_channel(u8 channel);
/*----------------------------------------------------------------------------*/
/**@brief 	录音音量设置
   @param	vol：录音音量
   @return  无
   @note   	void set_rec_vol(u8 vol)
*/
/*----------------------------------------------------------------------------*/
void set_rec_vol(u8 vol);
/*----------------------------------------------------------------------------*/
/**@brief 	录音声道
   @param	track：
   @return  无
   @note   	void set_rec_track (u8 track)
*/
/*----------------------------------------------------------------------------*/
void set_rec_track (u8 track);
/*----------------------------------------------------------------------------*/
/**@brief 	录音时间
   @param	无
   @return  无
   @note   	u16 encode_time(void)
*/
/*----------------------------------------------------------------------------*/
u16 encode_time(void);
/*----------------------------------------------------------------------------*/
/**@brief 	删除文件
   @param	device：设备  	fat_ptr1：文件信息
   @return  无
   @note   	u8 delete_current_file(u8 device , FIL _xdata *fat_ptr1)
*/
/*----------------------------------------------------------------------------*/
u8 delete_current_file(u8 device , FIL _xdata *fat_ptr1);
/*----------------------------------------------------------------------------*/
/**@brief 	创建文件名
   @param	ptr ：文件名
   @return  无
   @note   	void rec_dirfile_name(u8 _xdata *ptr)
*/
/*----------------------------------------------------------------------------*/
void rec_dirfile_name(u8 _xdata *ptr);

void dsp_set_adc_con(u16 reg);
/*----------------------------------------------------------------------------*/
/**@brief 	录音采样时钟设置   
   @param	0：24M  1：48M
   @return  无
   @note   	void rec_sys_set(u8 clk)
*/
/*----------------------------------------------------------------------------*/
void rec_sys_set(u8 clk);
void dsp_kalaok_channel(void);
/*----------------------------------------------------------------------------*/
/**@brief 	设置开启混响
   @param	channl：混响通道 
   @param	vol：   混响音量0~7
   @return  无
   @note   	void echo_set(channl,vol)
*/
/*----------------------------------------------------------------------------*/
void echo_set(channl,vol);
/*----------------------------------------------------------------------------*/
/**@brief 	关闭混响 
   @param	无
   @return  无
   @note   	void close_echo(void);
*/
/*----------------------------------------------------------------------------*/
void close_echo(void);
/*----------------------------------------------------------------------------*/
/**@brief 	关闭混响 
   @param	ctl 0：无混响功能；1：有混响功能
   @return  ECHO信息结构体的地址
   @note   	u8 _xdata * get_echo_var_ptr(u8 ctl);
*/
/*----------------------------------------------------------------------------*/
u8 _xdata * get_echo_var_ptr(u8 ctl);
/*----------------------------------------------------------------------------*/
/**@brief 	解码 output buf大小
   @param	size
   @return  无
   @note   	void set_obuf_size(u8 size);
*/
/*----------------------------------------------------------------------------*/
extern void set_obuf_size(u8 size);

/*----------------------------------------------------------------------------*/
/**@brief 	获取ENCODE信息 
   @param	无
   @return  encode_msg地址
   @note   	u8 _xdata * get_encode_msg_ptr(void);
*/
/*----------------------------------------------------------------------------*/
u8 _xdata * get_encode_msg_ptr(void);
/*----------------------------------------------------------------------------*/
/**@brief 	解码主音量选择 
   @param	flag 1：模拟音量作为解码主音量; 0：数字量作为解码主音量;
   @return  encode_msg地址
   @note   	u8 _xdata * get_encode_msg_ptr(void);
*/
/*----------------------------------------------------------------------------*/
void dec_analog_vol_sel(u8 flag);

/*----------------------------------------------------------------------------*/
/**@brief  音量表初始化
   @param	anolog_vol_tab 模擬音量表（u8类型）
   @param	digtal_vol_tab 数字音量表（u16类型）
   @return  無
   @note   	u8 _xdata * get_encode_msg_ptr(void);
*/
/*----------------------------------------------------------------------------*/
void set_vol_tab_ptr(u8 _code * anolog_vol, u16 _code * digtal_vol);
#endif

#endif

