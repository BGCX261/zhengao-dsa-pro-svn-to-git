/*


*/
#include "device.h"
#include "uart.h"

extern DECODER_MSG _xdata *dec_msg;
extern u8 _xdata decode_buffer[1024*2];
extern u8 given_device;
extern u8 given_file_method;
extern u16 break_point_filenum;
extern u8 _xdata win_buffer[512];
extern u8 _code one_table[];
extern void stop_decode(void);
extern FSAPIMSG _pdata fs_msg;
extern FIL xdata fat_ptr1;

extern DISK_MUSIC_POINT _idata	disk_mus_point[2];

u8 _bdata device_online=0;			    ///<设备在线标记
sbit sdmmc_connect = device_online^0;   ///<SD卡在线状态标记寄存器；1:在线 0：不在线
sbit udisk_connect = device_online^1;   ///<USB MASS storage在线状态标记寄存器；1:在线 0：不在线
sbit pc_connect = device_online^4;      ///<PC在线状态标记寄存器；1:在线 0：不在线
u8 device_active=0;                       ///<当前在线活动设备
u8 const _code file_type[] = "MP1MP2MP3WMAWAVSMP";  ///<解码文件格式


/*----------------------------------------------------------------------------*/
/**@brief   检测当前活动的设备
   @param   无
   @return  0：当前活动的设备不在线：其他：当前活动的设备
   @note    u8 device_check(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_check(void)
{
    device_online = get_device_online_status();
    return device_active & device_online;
}


/*----------------------------------------------------------------------------*/
/**@brief   设备初始化
   @param   无
   @return  0：找到有效谁而；其他：没有找到有效设备
   @note    u8 device_init(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_init(void)
{
    u8 sector_sizeof512 = 1;
    cipher_ctl(0);
    if (device_active & device_online)  ///<当前需要活动的设备在线
    {
        disp_port(MENU_SCAN_DISK);

        stop_decode();
        fs_fun_init();

        if (device_active == DEVICE_SDMMC0)
        {
			usb_suspend();
            if (init_sd())                  ///<sd 卡鉴定
            {

                f_init(win_buffer, (u16)sdmmc_read, 1);//get_usb_device_pkt_size());    ///<鉴定成功后 初始化文件系统参数
            }
            else
            {
                return 0xff;                       ///<鉴定失败
            }
        }

        else if (device_active == DEVICE_UDISK)
        {
            if (usb_host_emuerate_devcie(win_buffer))     ///<USB MASS STORAGE 枚举
            {
                sector_sizeof512 = get_usb_device_pkt_size();
                f_init(win_buffer, (u16)read_usb, sector_sizeof512);      ///<枚举成功后 初始化文件系统参数
            }
            else
            {
                return 0xff;             ///<枚举失败
            }
        }

    }


    //if (!f_mount())                                      ///<文件系统初始化
    if (!f_mount_bsp(sector_sizeof512))
    {
        fs_ext_setting(file_type);
//        printf("scan disk \n");

        {
            u16 break_point;

            if (device_active == DEVICE_SDMMC0)
            {
                break_point = disk_mus_point[0].id0;
            }
            else if (device_active == DEVICE_UDISK)
            {

                break_point = disk_mus_point[1].id0;
            }
            break_point_filenum = fs_scan_disk(break_point);
        }
        if (fs_msg.fileTotal == 0)
        {
            return 0xfe;
        }
        return 0;
    }
    else
    {
        return 0xff;	//无有效设备
    }
}
/*----------------------------------------------------------------------------*/
/**@brief    查找指定的设备或自动查找下一个有效设备
   @param    select : 1：查找SD设备；2：查找USB mass storage设备; 0x81:查找上一个设备；0x82:查找下一个设备;其它：无效
   @return   0：成功查找到一个设备；1:指定的设备没有找到；2：只有一个设备，查找上一个设备或下一个设备无效;3:找到设备，但初始化不成功;4：无在线设备
   @note     u8 find_device(u8 select)
*/
/*----------------------------------------------------------------------------*/
u8 find_device(u8 select)
{
    u8 i;

    device_check();

    i = one_table[device_online & 0x0f];

    if (i == 0)				//无设备
    {
        device_active = 0;
        return NO_DEV_ONLINE;
    }
    if (select == DEVICE_AUTO_PREV)		//查找上一个设备
    {
        if ((i == 1) && (device_active & device_online))			//当前设备已经选中
            return ONLY_ONE_DEVICE;

#if 0
        for (i = 0;i < MAX_DEVICE;i++)
        {
            device_active <<= 1;

            if ((device_active > MAX_PLAY_DEVICE) || (device_active == 0))
                device_active = DEVICE_SDMMC0;

            if ((device_active & device_online) == 0)
                continue;

            if (!device_init())             //找到有效设备
                return FIND_DEV_OK;
        }
#endif		
        device_active = 0;
        return NO_EFFECTIVE_DEV;				//无有效可以使用的设备

    }
    else if (select == DEVICE_AUTO_NEXT)    //查找下一个设备
    {
#if 0
        for (i = 0;i < MAX_DEVICE;i++)
        {
            device_active >>= 1;
            if ((device_active > MAX_PLAY_DEVICE) || (device_active == 0))
                device_active = DEVICE_UDISK;

            if ((device_active & device_online) == 0)
                continue;

            if (!device_init())             //找到有效设备
                return FIND_DEV_OK;
        }
#endif
        device_active = 0;
        return NO_EFFECTIVE_DEV;							//无有效可以使用的设备
    }
    else
    {

        if (select & device_online)
        {

            device_active = select;
            if (!device_init())
                return FIND_DEV_OK;
            else
            {
                device_active = 0;
                return DEV_INIT_ERR;
            }
        }
        else
            return NO_DEFINE_DEV;
    }
}
/*----------------------------------------------------------------------------*/
/**@brief   记录文件ID0，ID1信息到EEPROM
   @param   无
   @return  无
   @note    void write_file_info(void)
*/
/*----------------------------------------------------------------------------*/

void write_file_info(void)
{
    u16 id;
    u8 i;
    id = read_file_id(&fat_ptr1);

    write_info(MEM_ACTIVE_DEV, device_active);
    if (device_active == DEVICE_SDMMC0)
    {
        disk_mus_point[0].id0 = id;
        disk_mus_point[0].id1 = 0;
        disk_mus_point[0].id2 = 0;
        for (i = 9;i != (-1);i--)
        {
            write_info(MEM_SD_PLAYPOINT_ID0+i,((u8 *)(&(disk_mus_point[0].id0)))[i]);
        }




    }
    else if (device_active == DEVICE_UDISK)
    {
        disk_mus_point[1].id0 = id;
        disk_mus_point[1].id1 = 0;
        disk_mus_point[1].id2 = 0;
        for (i = 9;i != (-1);i--)
        {
            write_info(MEM_USB_PLAYPOINT_ID0+i,((u8 *)(&(disk_mus_point[1].id0)))[i]);
        }
    }
}
