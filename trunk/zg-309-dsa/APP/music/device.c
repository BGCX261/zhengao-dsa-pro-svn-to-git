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

u8 _bdata device_online=0;			    ///<�豸���߱��
sbit sdmmc_connect = device_online^0;   ///<SD������״̬��ǼĴ�����1:���� 0��������
sbit udisk_connect = device_online^1;   ///<USB MASS storage����״̬��ǼĴ�����1:���� 0��������
sbit pc_connect = device_online^4;      ///<PC����״̬��ǼĴ�����1:���� 0��������
u8 device_active=0;                       ///<��ǰ���߻�豸
u8 const _code file_type[] = "MP1MP2MP3WMAWAVSMP";  ///<�����ļ���ʽ


/*----------------------------------------------------------------------------*/
/**@brief   ��⵱ǰ����豸
   @param   ��
   @return  0����ǰ����豸�����ߣ���������ǰ����豸
   @note    u8 device_check(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_check(void)
{
    device_online = get_device_online_status();
    return device_active & device_online;
}


/*----------------------------------------------------------------------------*/
/**@brief   �豸��ʼ��
   @param   ��
   @return  0���ҵ���Ч˭����������û���ҵ���Ч�豸
   @note    u8 device_init(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_init(void)
{
    u8 sector_sizeof512 = 1;
    cipher_ctl(0);
    if (device_active & device_online)  ///<��ǰ��Ҫ����豸����
    {
        disp_port(MENU_SCAN_DISK);

        stop_decode();
        fs_fun_init();

        if (device_active == DEVICE_SDMMC0)
        {
			usb_suspend();
            if (init_sd())                  ///<sd ������
            {

                f_init(win_buffer, (u16)sdmmc_read, 1);//get_usb_device_pkt_size());    ///<�����ɹ��� ��ʼ���ļ�ϵͳ����
            }
            else
            {
                return 0xff;                       ///<����ʧ��
            }
        }

        else if (device_active == DEVICE_UDISK)
        {
            if (usb_host_emuerate_devcie(win_buffer))     ///<USB MASS STORAGE ö��
            {
                sector_sizeof512 = get_usb_device_pkt_size();
                f_init(win_buffer, (u16)read_usb, sector_sizeof512);      ///<ö�ٳɹ��� ��ʼ���ļ�ϵͳ����
            }
            else
            {
                return 0xff;             ///<ö��ʧ��
            }
        }

    }


    //if (!f_mount())                                      ///<�ļ�ϵͳ��ʼ��
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
        return 0xff;	//����Ч�豸
    }
}
/*----------------------------------------------------------------------------*/
/**@brief    ����ָ�����豸���Զ�������һ����Ч�豸
   @param    select : 1������SD�豸��2������USB mass storage�豸; 0x81:������һ���豸��0x82:������һ���豸;��������Ч
   @return   0���ɹ����ҵ�һ���豸��1:ָ�����豸û���ҵ���2��ֻ��һ���豸��������һ���豸����һ���豸��Ч;3:�ҵ��豸������ʼ�����ɹ�;4���������豸
   @note     u8 find_device(u8 select)
*/
/*----------------------------------------------------------------------------*/
u8 find_device(u8 select)
{
    u8 i;

    device_check();

    i = one_table[device_online & 0x0f];

    if (i == 0)				//���豸
    {
        device_active = 0;
        return NO_DEV_ONLINE;
    }
    if (select == DEVICE_AUTO_PREV)		//������һ���豸
    {
        if ((i == 1) && (device_active & device_online))			//��ǰ�豸�Ѿ�ѡ��
            return ONLY_ONE_DEVICE;

#if 0
        for (i = 0;i < MAX_DEVICE;i++)
        {
            device_active <<= 1;

            if ((device_active > MAX_PLAY_DEVICE) || (device_active == 0))
                device_active = DEVICE_SDMMC0;

            if ((device_active & device_online) == 0)
                continue;

            if (!device_init())             //�ҵ���Ч�豸
                return FIND_DEV_OK;
        }
#endif		
        device_active = 0;
        return NO_EFFECTIVE_DEV;				//����Ч����ʹ�õ��豸

    }
    else if (select == DEVICE_AUTO_NEXT)    //������һ���豸
    {
#if 0
        for (i = 0;i < MAX_DEVICE;i++)
        {
            device_active >>= 1;
            if ((device_active > MAX_PLAY_DEVICE) || (device_active == 0))
                device_active = DEVICE_UDISK;

            if ((device_active & device_online) == 0)
                continue;

            if (!device_init())             //�ҵ���Ч�豸
                return FIND_DEV_OK;
        }
#endif
        device_active = 0;
        return NO_EFFECTIVE_DEV;							//����Ч����ʹ�õ��豸
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
/**@brief   ��¼�ļ�ID0��ID1��Ϣ��EEPROM
   @param   ��
   @return  ��
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
