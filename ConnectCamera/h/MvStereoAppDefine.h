/***************************************************************************************************
*
* ��Ȩ��Ϣ����Ȩ���� (c) 2019, ���ݺ��������˼������޹�˾, ��������Ȩ��
*
* �ļ����ƣ�MvStereoAppDefine.h
* ժ    Ҫ: �������SDK���ṹ�嶨��
*
* ��ǰ�汾��2.1.0
* ��    ��: �����Ӿ�SDK�Ŷ�
* ��    �ڣ�2019.12.1
* ��    ע���½�
****************************************************************************************************/

#ifndef _MV_STA_DEFINE_H_
#define _MV_STA_DEFINE_H_

//��ƽ̨����
//Cross Platform Definition
#ifdef WIN32
    typedef __int64 int64_t;
    typedef unsigned __int64 uint64_t;
#else
    #include <stdint.h>
#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

// ch:�豸���Ͷ��� | en:Device Type Definition
#define MV_STA_UNKNOW_DEVICE                         0x00000000  // ch:δ֪�豸���ͣ��������� | en:Unknown Device Type, Reserved 
#define MV_STA_GIGE_DEVICE                           0x00000001  // ch:GigE�豸 | en:GigE Device
#define MV_STA_1394_DEVICE                           0x00000002  // ch:1394-a/b �豸 | en:1394-a/b Device �ݲ�֧��
#define MV_STA_USB_DEVICE                            0x00000004  // ch:USB3.0 �豸 | en:USB3.0 Device
#define MV_STA_CAMERALINK_DEVICE                     0x00000008  // ch:CameraLink�豸 | en:CameraLink Device



// ch:�豸�ķ���ģʽ | en:Device Access Mode
// ch:��ռȨ�ޣ�����APPֻ�����CCP�Ĵ��� | en:Exclusive authority, other APP is only allowed to read the CCP register
#define MV_STA_ACCESS_Exclusive                                         1
// ch:���Դ�5ģʽ����ռȨ�ޣ�Ȼ���Զ�ռȨ�޴� | en:You can seize the authority from the 5 mode, and then open with exclusive authority
#define MV_STA_ACCESS_ExclusiveWithSwitch                               2
// ch:����Ȩ�ޣ�����APP��������мĴ��� | en:Control authority, allows other APP reading all registers
#define MV_STA_ACCESS_Control                                           3
// ch:���Դ�5��ģʽ����ռȨ�ޣ�Ȼ���Կ���Ȩ�޴� | en:You can seize the authority from the 5 mode, and then open with control authority
#define MV_STA_ACCESS_ControlWithSwitch                                 4
// ch:�Կɱ���ռ�Ŀ���Ȩ�޴� | en:Open with seized control authority
#define MV_STA_ACCESS_ControlSwitchEnable                               5
// ch:���Դ�5��ģʽ����ռȨ�ޣ�Ȼ���Կɱ���ռ�Ŀ���Ȩ�޴� | en:You can seize the authority from the 5 mode, and then open with seized control authority
#define MV_STA_ACCESS_ControlSwitchEnableWithKey                        6
// ch:��ģʽ���豸�������ڿ���Ȩ���� | en:Open with read mode and is available under control authority
#define MV_STA_ACCESS_Monitor                                           7




// ch:��ȷ�붨��
#define MV_STA_OK                                    0x00000000  ///< �ɹ����޴���

//ͨ�ô����붨��:��Χ0x80010000-0x800100FF
#define MV_STA_E_HANDLE                              0x80010000  ///< �������Ч�ľ��
#define MV_STA_E_SUPPORT                             0x80010001  ///< ��֧�ֵĹ���
#define MV_STA_E_BUFOVER                             0x80010002  ///< ��������
#define MV_STA_E_CALLORDER                           0x80010003  ///< ��������˳�����
#define MV_STA_E_PARAMETER                           0x80010004  ///< ����Ĳ���
#define MV_STA_E_RESOURCE                            0x80010005  ///< ��Դ����ʧ��
#define MV_STA_E_NODATA                              0x80010006  ///< ������
#define MV_STA_E_PRECONDITION                        0x80010007  ///< ǰ���������󣬻����л����ѷ����仯
#define MV_STA_E_VERSION                             0x80010008  ///< �汾��ƥ��
#define MV_STA_E_NOENOUGH_BUF                        0x80010009  ///< ������ڴ�ռ䲻��
#define MV_STA_E_ABNORMAL_IMAGE                      0x8001000A  ///< �쳣ͼ�񣬿����Ƕ�������ͼ������
#define MV_STA_E_LOAD_LIBRARY                        0x8001000B  ///< ��̬����DLLʧ��
#define MV_STA_E_ALGORITHM                           0x8001000C  ///< �㷨����
#define MV_STA_E_DeviceNotExist                      0x8001000D  ///< �豸������  ���豸���ߣ����� �ͺŹ��˵��ˣ�

#define MV_STA_E_UNKNOW                              0x800100FF  ///< δ֪�Ĵ���

// GenICamϵ�д���
#define MV_STA_E_GC_GENERIC                          0x80010100  ///< ͨ�ô��� | en:General error
#define MV_STA_E_GC_ARGUMENT                         0x80010101  ///< �����Ƿ� | en:Illegal parameters
#define MV_STA_E_GC_RANGE                            0x80010102  ///< ֵ������Χ | en:The value is out of range
#define MV_STA_E_GC_PROPERTY                         0x80010103  ///< ���� | en:Property
#define MV_STA_E_GC_RUNTIME                          0x80010104  ///< ���л��������� | en:Running environment error
#define MV_STA_E_GC_LOGICAL                          0x80010105  ///< �߼����� | en:Logical error
#define MV_STA_E_GC_ACCESS                           0x80010106  ///< �ڵ������������ | en:Node accessing condition error
#define MV_STA_E_GC_TIMEOUT                          0x80010107  ///< ��ʱ | en:Timeout
#define MV_STA_E_GC_DYNAMICCAST                      0x80010108  ///< ת���쳣 | en:Transformation exception
#define MV_STA_E_GC_UNKNOW                           0x800101FF  ///< GenICamδ֪���� | en:GenICam unknown error

//GigE_STATUS��Ӧ�Ĵ�����
#define MV_STA_E_NOT_IMPLEMENTED                     0x80010200  ///< ������豸֧�� | en:The command is not supported by device
#define MV_STA_E_INVALID_ADDRESS                     0x80010201  ///< ���ʵ�Ŀ���ַ������ | en:The target address being accessed does not exist
#define MV_STA_E_WRITE_PROTECT                       0x80010202  ///< Ŀ���ַ����д | en:The target address is not writable
#define MV_STA_E_ACCESS_DENIED                       0x80010203  ///< �豸�޷���Ȩ�� | en:No permission
#define MV_STA_E_BUSY                                0x80010204  ///< �豸æ��������Ͽ� | en:Device is busy, or network disconnected
#define MV_STA_E_PACKET                              0x80010205  ///< ��������ݴ��� | en:Network data packet error
#define MV_STA_E_NETER                               0x80010206  ///< ������ش��� | en:Network error
// GigE������еĴ�����
#define MV_STA_E_IP_CONFLICT                         0x80010221  ///< �豸IP��ͻ | en:Device IP conflict


//����ʱ��Ӧ�Ĵ�����:
#define MV_STA_E_UPG_FILE_MISMATCH                   0x80010400 ///< �����̼���ƥ�� | en:Firmware mismatches
#define MV_STA_E_UPG_LANGUSGE_MISMATCH               0x80010401 ///< �����̼����Բ�ƥ�� | en:Firmware language mismatches
#define MV_STA_E_UPG_CONFLICT                        0x80010402 ///< ������ͻ���豸�Ѿ����������ٴ��������������ش˴��� | en:Upgrading conflicted (repeated upgrading requests during device upgrade)
#define MV_STA_E_UPG_INNER_ERR                       0x80010403 ///< ����ʱ����ڲ����ִ��� | en:Camera internal error during upgrade
#define MV_STA_E_UPG_UNKNOW                          0x800104FF ///< ����ʱδ֪���� | en:Unknown error during upgrade


//�������
enum MV_STA_CAMERA_TYPE
{
    MV_STA_CAMERA_3D                         = 3, //3D���
    MV_STA_CAMERA_2D                         = 2, //2D���
};

enum MvStereoAppTriggerMode
{
    MV_STA_TRIGGER_MODE_OFF                  = 0,
    MV_STA_TRIGGER_MODE_ON                   = 1,
};

enum MV_STA_TRIGGER_SOURCE
{
    MV_STA_TRIGGER_SOURCE_LINE0              = 0,
    MV_STA_TRIGGER_SOURCE_LINE1              = 1,
    MV_STA_TRIGGER_SOURCE_LINE2              = 2,
    MV_STA_TRIGGER_SOURCE_LINE3              = 3,
    MV_STA_TRIGGER_SOURCE_COUNTER0           = 4,

    MV_STA_TRIGGER_SOURCE_SOFTWARE           = 7,
    MV_STA_TRIGGER_SOURCE_FrequencyConverter = 8,
};

enum MvSTAIpCfgMode
{
    MV_STA_IP_CFG_STATIC  = 0x05000000,
    MV_STA_IP_CFG_DHCP    = 0x06000000,
    MV_STA_IP_CFG_LLA     = 0x04000000,
};

enum MvSTADevException
{
    MV_STA_EXCEPTION_DEV_DISCONNECT = 0x00008001,                   // �豸�Ͽ�����
};


typedef struct _MV_STEREOCAM_NET_INFO_
{
    unsigned int            nIpCfgOption;                           // �豸֧�ֵ�IP����
    unsigned int            nIpCfgCurrent;                          // �豸��ǰIP����
    unsigned int            nCurrentIp;                             // �豸��ǰIP
    unsigned int            nCurrentSubNetMask;                     // �豸��ǰ��������
    unsigned int            nDefultGateWay;                         // �豸Ĭ������
    unsigned char           chManufacturerName[32];                 // �豸����
    unsigned char           chModelName[32];                        // �豸�ͺ�
    unsigned char           chDeviceVersion[32];                    // �豸�汾
    unsigned char           chManufacturerSpecificInfo[48];         // �豸����������Ϣ
    unsigned char           chSerialNumber[16];                     // �豸���к�
    unsigned char           chUserDefinedName[16];                  // �豸�û��Զ�������
    unsigned int            nNetExport;                             // ��������IP��ַ

    unsigned int            nReserved[4];                           // �����ֽڣ����� 0��Mac�ߣ�1��Mac�ͣ�

}MV_STEREOCAM_NET_INFO;

#define INFO_MAX_BUFFER_SIZE 64    //�¶���256
typedef struct _MV_STA_USB3_DEVICE_INFO_
{
    unsigned char           CrtlInEndPoint;                          // ch:��������˵� | en:Control input endpoint
    unsigned char           CrtlOutEndPoint;                         // ch:��������˵� | en:Control output endpoint
    unsigned char           StreamEndPoint;                          // ch:���˵� | en:Flow endpoint
    unsigned char           EventEndPoint;                           // ch:�¼��˵� | en:Event endpoint
    unsigned short          idVendor;                                // ch:��Ӧ��ID�� | en:Vendor ID Number
    unsigned short          idProduct;                               // ch:��ƷID�� | en:Device ID Number
    unsigned int            nDeviceNumber;                           // ch:�豸���к�  | en:Device Serial Number
    unsigned char           chDeviceGUID[INFO_MAX_BUFFER_SIZE];      // ch:�豸GUID�� | en:Device GUID Number
    unsigned char           chVendorName[INFO_MAX_BUFFER_SIZE];      // ch:��Ӧ������ | en:Vendor Name
    unsigned char           chModelName[INFO_MAX_BUFFER_SIZE];       // ch:�ͺ����� | en:Model Name
    unsigned char           chFamilyName[INFO_MAX_BUFFER_SIZE];      // ch:�������� | en:Family Name
    unsigned char           chDeviceVersion[INFO_MAX_BUFFER_SIZE];   // ch:�豸�汾�� | en:Device Version
    unsigned char           chManufacturerName[INFO_MAX_BUFFER_SIZE];// ch:���������� | en:Manufacturer Name
    unsigned char           chSerialNumber[INFO_MAX_BUFFER_SIZE];    // ch:���к� | en:Serial Number
    unsigned char           chUserDefinedName[INFO_MAX_BUFFER_SIZE]; // ch:�û��Զ������� | en:User Defined Name
    unsigned int            nbcdUSB;                                 // ch:֧�ֵ�USBЭ�� | en:Support USB Protocol
    unsigned int            nDeviceAddress;                          // ch:�豸��ַ | en:Device Address
    unsigned int            nReserved[2];                            // ch:�����ֽ� | en:Reserved bytes
}MV_STA_USB3_DEVICE_INFO;

typedef struct _MV_STA_CamL_DEV_INFO_
{
    unsigned char           chPortID[INFO_MAX_BUFFER_SIZE];
    unsigned char           chModelName[INFO_MAX_BUFFER_SIZE];
    unsigned char           chFamilyName[INFO_MAX_BUFFER_SIZE];
    unsigned char           chDeviceVersion[INFO_MAX_BUFFER_SIZE];
    unsigned char           chManufacturerName[INFO_MAX_BUFFER_SIZE];
    unsigned char           chSerialNumber[INFO_MAX_BUFFER_SIZE];
    unsigned int            nReserved[38];
}MV_STA_CamL_DEV_INFO;

// ���֧�ֵ��豸����
#define MV_STEREOCAM_MAX_NUM      256
// �豸��Ϣ�б�
typedef struct _MV_STEREOCAM_NET_INFO_LIST_
{
    unsigned int                nDeviceNum;                            // �豸����
    MV_STEREOCAM_NET_INFO*      pDeviceInfo[MV_STEREOCAM_MAX_NUM];     // �豸��Ϣ
}MV_STEREOCAM_NET_INFO_LIST;


// ch:�豸��Ϣ | en:Device Infomation
typedef struct _MV_STA_DEVICE_INFO_
{
    // ch:common info | en:common info 
    unsigned short      nMajorVer;
    unsigned short      nMinorVer;
    unsigned int        nMacAddrHigh;               //  Mac�ߵ�ַ
    unsigned int        nMacAddrLow;                //  Mac�͵�ַ
    unsigned int        nTLayerType;                //  ch:�豸�����Э�����ͣ�e.g. MV_STA_GIGE_DEVICE | MV_STA_USB_DEVICE
    unsigned int        nReserved[4];               //  ���У�nReserved[0]��MV_STA_CAMERA_3D(3)��ʾ3D�����MV_STA_CAMERA_2D(2)��ʾ2D���

    union
    {
        MV_STEREOCAM_NET_INFO     stGigEInfo;
        MV_STA_USB3_DEVICE_INFO   stUsb3VInfo; 
        MV_STA_CamL_DEV_INFO      stCamLInfo;
        // more ...
    }SpecialInfo;

}MV_STA_DEVICE_INFO;

typedef struct _MV_STA_DEVICE_INFO_LIST_
{
    unsigned int             nDeviceNum;                            // ch:�����豸���� | en:Online Device Number
    MV_STA_DEVICE_INFO*      pDeviceInfo[MV_STEREOCAM_MAX_NUM];     // ch:֧�����256���豸 | en:Support up to 256 devices

}MV_STA_DEVICE_INFO_LIST;

typedef struct _MV_STA_ALL_MATCH_INFO_
{
    unsigned int    nType;          // ch:��Ҫ�������Ϣ���ͣ�e.g. MV_STA_MATCH_TYPE_NET_DETECT
    void*           pInfo;          // ch:�������Ϣ���棬�ɵ����߷���
    unsigned int    nInfoSize;      // ch:��Ϣ����Ĵ�С

}MV_STA_ALL_MATCH_INFO;


// ch:��Ϣ���� | en:Information Type
#define MV_STA_MATCH_TYPE_NET_DETECT             0x00000001      // ch:���������Ͷ�����Ϣ | en:Network traffic and packet loss information
#define MV_STA_MATCH_TYPE_USB_DETECT             0x00000002      // ch:host���յ�����U3V�豸���ֽ����� | en:The total number of bytes host received from U3V device


// ch:���������Ͷ�����Ϣ�����ṹ�壬��Ӧ����Ϊ MV_STA_MATCH_TYPE_NET_DETECT
// en:Network traffic and packet loss feedback structure, the corresponding type is MV_STA_MATCH_TYPE_NET_DETECT
typedef struct _MV_STA_MATCH_INFO_NET_DETECT_
{
    int64_t         nReceiveDataSize;            // ch:�ѽ������ݴ�С  [ͳ��StartGrabbing��StopGrabbing֮���������] | en:Received data size 
    int64_t         nLostPacketCount;            // ch:��ʧ�İ����� | en:Number of packets lost
    unsigned int    nLostFrameCount;             // ch:��֡���� | en:Number of frames lost
    unsigned int    nNetRecvFrameCount;          // ch:���� | en:Reserved
    __int64         nRequestResendPacketCount;   // �����ط�����
    __int64         nResendPacketCount;          // �ط�����
}MV_STA_MATCH_INFO_NET_DETECT;

// ch:host�յ���u3v�豸�˵����ֽ�������Ӧ����Ϊ MV_STA_MATCH_TYPE_USB_DETECT | en:The total number of bytes host received from the u3v device side, the corresponding type is MV_STA_MATCH_TYPE_USB_DETECT
typedef struct _MV_STA_MATCH_INFO_USB_DETECT_
{
    int64_t         nReceiveDataSize;           // ch:�ѽ������ݴ�С    [ͳ��OpenDevicce��CloseDevice֮���������] | en:Received data size
    unsigned int    nReceivedFrameCount;        // ch:���յ���֡�� | en:Number of frames received
    unsigned int    nErrorFrameCount;           // ch:����֡�� | en:Number of error frames
    unsigned int    nReserved[2];               // ch:���� | en:Reserved
}MV_STA_MATCH_INFO_USB_DETECT;


//����������
#define STC_DATA_MSG_TYPE_UNKNOWN                   0
#define STC_DATA_MSG_TYPE_IMG_RAW                   1

// �߼��������ϱ��������
#define STC_DATA_MSG_TYPE_DWS_VOLUME                4

// ˫Ŀ��������ϱ��������
#define STC_DATA_MSG_TYPE_STEREO_VOLUME             5

// ��ǰ֡�ţ�������������㣩
// �߼������MV-DL2040-04B-H �̼�V1.1.0֮��֧��
// �߼������MV-DL2025-04H-H �̼����ְ汾֧��
#define STC_3D_Camera_Current_Frame_ID              0xa5a50105


 
// 3D �����߳��ýڵ�
// �е���(���ͼ���)
#define STC_3D_Profile_LinePntNum                   0xa5a53d01
//����  (���ͼ�߶�)
#define STC_3D_Profile_Count                        0xa5a53d02
//����ͼ
#define STC_3D_Profile_Intensity                    0xa5a53d03
//���ͼ
#define STC_3D_Profile_Thickness                    0xa5a53d04
//ǰ������
#define STC_3D_Profile_RunDir                       0xa5a53d05
//��һ��������֡��
#define STC_3D_Profile_FirstFrmID                   0xa5a53d06
//�������
#define STC_3D_Profile_CoordScale                   0xa5a53d07
//������ʼ���ƫ��
#define STC_3D_Profile_CoordOffset                  0xa5a53d08
//���ĵ�������Ϣ
#define STC_3D_Profile_CenterCoordinate             0xa5a53d09
//RGBDʱ�����Ϣ
#define STC_3D_Profile_TimeStamp                    0xa5a53d10
//Ϊ1 ʱ��ʾ��ʾ���δ����Ӵ����߳�ʱ����Ҫ���һ֡���ͼ
#define STC_3D_Profile_TriggerEnd                   0xa5a53d0A
//RGBͼ��
#define STC_3D_Profile_ExtendImg                    0xa5a53d0B
//RGBD�������������Ϣ
#define STC_3D_Profile_SingulatePkginfo             0xa5a53d0C
//ʵ���ָ���
#define STC_3D_Profile_InstanceSegInfo              0xa5a53d0D
//Ŀ����
#define STC_3D_Profile_DetectInfo                   0xa5a53d0E
//ץȡ��Ϣ
#define STC_3D_Profile_GraspInfo                    0xa5a53d0F

// 3Dλ��(F32)
typedef struct _STC_POINT_XYZ_F32
{
    float  x;              // �ռ�x����
    float  y;              // �ռ�y����
    float  z;              // �ռ�z����
}STC_POINT_XYZ_F32;

//���͵�ṹ�� 
typedef struct _STC_POINT_I
{
    signed int x;          // x����
    signed int y;          // y����
}STC_POINT_I;

//�����͵�ṹ��
typedef struct _STC_POINT_F
{
    float x;               // x����
    float y;               // y����
}STC_POINT_F;

//���Ͷ���νṹ��
typedef struct __STC_POLYGON_I
{
    bool bSupport ;           //�Ƿ�֧��
    STC_POINT_I   point[4];   //����
}_STC_POLYGON_I;

//�����Ͷ���νṹ��
typedef struct _STC_POLYGON_F
{
    bool bSupport ;           // �Ƿ�֧��
    STC_POINT_F   point[4];   //����
}STC_POLYGON_F;

// ���ԭʼͼ������ͼ�����ͼ�����ô˽ṹ��
typedef struct _STC_DATA_IMAGE_
{
    unsigned short      nWidth;                             // ͼ���
    unsigned short      nHeight;                            // ͼ���
    enum MvStereoAppGvspPixelType     enPixelType;          // ���ظ�ʽ
    unsigned char*      pData;                              // ���ԭʼͼ���ʽ
    unsigned int        nFrameLen;                          // ͼ�񳤶�

    unsigned int        nFrameNum;                          // ֡��
    unsigned int        nDevTimeStampHigh;                  // ʱ�����32λ
    unsigned int        nDevTimeStampLow;                   // ʱ�����32λ
    unsigned int        nReserved0;                         // ������8�ֽڶ���
    int64_t             nHostTimeStamp;                     // �������ɵ�ʱ���

    unsigned int        nReserved[8];                       //�����ֽ� nReserved[0] MV_STA_GetImage�ӿڵ���ʱΪ��֡ͼ�񶪰���

}STC_DATA_IMAGE;

// �������ͼ Intensity
typedef struct _STC_PROFILE_INTENSITYE_
{
    unsigned int        nDataLen;                          // ���ݳ���
    unsigned char*      pData;                             // ����

    unsigned int        nReserved[8];                     // �����ֽ�

}STC_PROFILE_INTENSITY;

// �������ͼ Intensity
typedef struct _STC_PROFILE_THICKNESS_
{
    unsigned int        nDataLen;                          // ���ݳ���
    unsigned char*      pData;                             // ����

    unsigned int        nReserved[8];                      // �����ֽ�

}STC_PROFILE_THICKNESS;

// 3D �����ǵ�ǰ������
typedef struct _STC_PROFILE_RUNDIR_
{
    float       x;
    float       y;
    float       z;
}STC_PROFILE_RUNDIR;

//3D������ �������
typedef struct _STC_PROFILE_COORDSCALE_
{
    float       x;
    float       y;
    float       z;
}STC_PROFILE_COORDSCALE;

//3D������ ������ʼ���ƫ��
typedef struct STC_PROFILE_COORDOFFSET
{
    int        x;
    int        y;
    int        z;
}STC_PROFILE_COORDOFFSET;

//��֡��������  ���ĵ�������Ϣ
typedef struct _STC_CENTERCOORDINATE_
{
    unsigned int        nDataLen;                          // ���ݳ���
    int*                pData;                             // ����
}STC_CENTERCOORDINATE;

//��չͼ����Ϣ
typedef struct _STC_EXTEND_IMAGE_
{
    int nPixelFormat;      /* ���ظ�ʽ������RGB8,BGR8��RGB8_Planar */
    int nWidth;            /* rgb width */
    int nHeight;           /* rgb height */
    unsigned int nDataLen; /*imagesize*/
    int nFlag;             /* ͼ���û���־λ��Ϊ1ʱ�滻image��Ϊ0ʱ����Ҫ�滻 */
    int  nRes[3];          /* rgb �����ֽ� */
    unsigned char* pData;  /* rgbͼ���� */
}STC_EXTEND_IMAGE;

// ����λ�� 3d
#define  STC_PKGTK_SINGULATE_MAX_PKG_NUM               200         // ��������Ŀ
#define  STC_PKGTK_SINGULATE_MAX_PTS_NUM               16          // ����͹����󶥵���

typedef struct _STC_PKGTK_SINGULATE_PKG3D_
{
    STC_POINT_XYZ_F32   rect_vertexes[4];                                       // ���ο򶥵����꣨��Ŀ���⣩
    STC_POINT_XYZ_F32   convex_vertexes[STC_PKGTK_SINGULATE_MAX_PTS_NUM];       // ͹�����������꣨��ʵ���ָ
    signed int          convex_pts_num;                                         // ͹����������Ŀ
    signed int          flag_rect;                                              // ���ο򶥵������Ƿ���Ч��HKA_FALSE: ��Ч, HKA_TRUE: ��Ч��
    signed int          flag_convex;                                            // ͹�������������Ƿ���Ч��HKA_FALSE: ��Ч, HKA_TRUE: ��Ч��

}STC_PKGTK_SINGULATE_PKG3D;

typedef struct _STC_SINGULATE_CALPOSE_
{
    unsigned int nPkgId;                               /**< ����ID�� */
    STC_PKGTK_SINGULATE_PKG3D stPkgs3d;                /**< ������Ϣ */
}STC_SINGULATE_CALPOSE;

//������Ϣ
typedef struct _STC_PACKAGE_INFO_
{
    unsigned int nFrameId;                  /**< ֡�� */
    signed int nPkgsNum;                    /**< �������� */
    //STC_SINGULATE_CALPOSE pstPkgInfo[STC_PKGTK_SINGULATE_MAX_PKG_NUM];      /**< ������Ϣ���� */
    STC_SINGULATE_CALPOSE *pstPkgInfo;      /**< ������Ϣ���� */
}STC_PACKAGE_INFO;

// ���ͼ��Ⱦ��Ϣ
typedef struct _STC_DEPTH_MAP_DISPLAY_EX
{
    // ������λ��  ��ʵ�����꣩
    STC_POLYGON_F     szPackageRoi;
    // ��������     ������ͼ�ı����������1�� 0.5�����м䣬����ʵ�����꣬4�������ǰ���ͼ���������)
    STC_POLYGON_F    szMeasureRoi;
    // ˮӡ������ͼ�����Ͻ���ʾ
    unsigned char szImageWatermark[32];
}STC_DEPTH_MAP_DISPLAY_EX;

// ������Ϣ
typedef struct _STC_DWS_VOLUME_INFO
{
    // ����
    float                  volume;                       // Ŀ�����
    float                  length;                       // Ŀ�곤
    float                  width;                        // Ŀ���
    float                  height;                       // Ŀ���
    // ��Ե��ģ�� 
    float                  rectangularity;               // ���ζ�(ȡֵ��Χ0~1, Խ�ӽ�1���ζ�Խ��)    //���ֶ���ʱ�����֧�֣�
    // ����ģ���ͼ��ģ��
    STC_POINT_XYZ_F32      vertex_pnts[4];               // Ŀ�궥��     //���ֶ���ʱ�����֧�֣�

    signed int             obj_id;                       // Ŀ��ID��
    unsigned short         start_frm_id;                 // ��ʼ֡��
    unsigned short         end_frm_id;                   // ����֡��
}STC_DWS_VOLUME_INFO;


// ���������
#pragma pack(4)
typedef struct _STC_STEREO_VOLUME_INFO
{
    unsigned __int64       nVolume;                      //�������
    unsigned int           nLength;                      //����
    unsigned int           nWidth;                       //���
    unsigned int           nHeight;                      //�߶�
    STC_POINT_I            vertex_pnts[4];               //Ŀ�궥�㣨ͼ������ֵ��
}STC_STEREO_VOLUME_INFO;
#pragma pack()


// ��һ�����ͼ�͵���ͼʱ�������������
typedef struct _STC_NORMALIZE_IMAGE_
{
    IN unsigned short       nWidth;                      // ͼ���
    IN unsigned short       nHeight;                     // ͼ���
    IN enum MvStereoAppGvspPixelType     enSrcPixelType; // ���ظ�ʽ
    IN unsigned char*       pData;                       // ���ԭʼͼ���ʽ
    IN unsigned int         nLen;                        // ͼ�񳤶�

    // ���ظ�ʽ���������������ͼ����ô�����ʽΪMono16�����������ǵ���ͼ����ô�����ʽΪABC16��ABC32��
    IN OUT enum MvStereoAppGvspPixelType   enDstPixelType;
    OUT unsigned char*      pNormalizedData;            // ���ԭʼͼ���ʽ��������SDK�ڲ�����
    OUT unsigned int        nNormalizedLen;             // ͼ�񳤶�

}STC_NORMALIZE_IMAGE;


// ���ͼMono16תTIFF�ṹ��
typedef struct _STC_IMG_SAVE_MONO16_TO_TIFF_PARAM_
{
    enum MvStereoAppGvspPixelType  enPixelType;        // �����������ظ�ʽ
    unsigned char*                 pData;              // �������ݻ���
    unsigned int                   nDataLen;           // �������ݴ�С
    unsigned short                 nWidth;             // ����ͼ���
    unsigned short                 nHeight;            // ����ͼ���

    char                           pImagePath[256];    // ����ļ�·��, ���������·��ʱ�������ڲ���Ҫת����·������·�����Ȳ��ܳ���windows���ƣ�����ᱨ��������
    int                            iMethodValue;       // ��Ч����������Ĭ��ֵ0����
    unsigned int                   nReserved[8];       // �����ֽ�
}STC_IMG_SAVE_MONO16_TO_TIFF_PARAM;

// ���ͼMono16תBMP�ṹ��
typedef struct _STC_IMG_SAVE_MONO16_TO_BMP_PARAM_
{
    enum MvStereoAppGvspPixelType  enPixelType;        // �����������ظ�ʽ
    unsigned char*                 pData;              // �������ݻ���
    unsigned int                   nDataLen;           // �������ݴ�С
    unsigned short                 nWidth;             // ����ͼ���
    unsigned short                 nHeight;            // ����ͼ���

    char                           pImagePath[256];    // ����ļ�·��, ���������·��ʱ�������ڲ���Ҫת����·������·�����Ȳ��ܳ���windows���ƣ�����ᱨ��������
    unsigned int                   nReserved[8];       // �����ֽ�
}STC_IMG_SAVE_MONO16_TO_BMP_PARAM;


// ���ͼMono16תJPG�ṹ��
typedef struct _STC_IMG_SAVE_MONO16_TO_JPG_PARAM_
{
    enum MvStereoAppGvspPixelType  enPixelType;        // �����������ظ�ʽ
    unsigned char*                 pData;              // �������ݻ���
    unsigned int                   nDataLen;           // �������ݴ�С
    unsigned short                 nWidth;             // ����ͼ���
    unsigned short                 nHeight;            // ����ͼ���

    unsigned int                   nQuality;           // ���JPG��������(0-100]
    char                           pImagePath[256];    // ����ļ�·��,���������·��ʱ�������ڲ���Ҫת����·������·�����Ȳ��ܳ���windows���ƣ�����ᱨ��������
    unsigned int                   nReserved[8];       // �����ֽ�
}STC_IMG_SAVE_MONO16_TO_JPG_PARAM;

// ����ͼABC16תPYL,OBJ,CSV���ýṹ��
typedef struct _STC_IMG_SAVE_ABC16_TO_PLY_PARAM_
{
    unsigned int                   nLinePntNum;        // ÿһ�е������,��Ӧͼ���
    unsigned int                   nLineNum;           // ����,��Ӧͼ���
    enum MvStereoAppGvspPixelType  enSrcPixelType;     // �����������ظ�ʽ
    unsigned char*                 pSrcData;           // �������ݻ���
    unsigned int                   nSrcDataLen;        // �������ݴ�С

    void*                          pDstBuf;            // ������ݻ���
    unsigned int                   nDstBufSize;        // �����������С(nLinePntNum * nLineNum * (16*3 + 4) + 2048)
    unsigned int                   nDstBufLen;         // ������ݳ���
    unsigned int                   nReserved[8];       // �����ֽ�

}STC_IMG_SAVE_ABC16_TO_PLY_PARAM, STC_IMG_SAVE_ABC16_TO_OBJ_PARAM, STC_IMG_SAVE_ABC16_TO_CSV_PARAM;

// ������������嶨λ��Ϣ
typedef struct _STC_DATA_MEASURE_VOLUME_
{
    float          fLength;
    float          fWidth;
    float          fHeight;
    float          fVolume;
    struct POINT_XY
    {
        float       fX;                         // X����
        float       fY;                         // Y����
        float       fZ;                         // Y����
        int         nReserved[8];               // �����ֶ�
    }stVolPos[4];

    int             nReserved[8];
} STC_DATA_MEASURE_VOLUME;


typedef void*   STC_Object;
typedef STC_Object STC_DataSet; 


// �쳣��Ϣ
typedef struct _STC_EXCEPTION_INFO_
{
    unsigned int        nExceptionID;         // �쳣ID    MvSTADevException
    char                strExceptionDes[256]; // �쳣����

    unsigned int        nReserved[16];        // �����ֽ�

}STC_EXCEPTION_INFO;

// ch:���ͼ�����Ϣ | en:Output Frame Information
typedef struct _STC_IMAGE_INFO_
{
    OUT unsigned char*  pImageBuf;            // ԭʼͼ�񻺴棬��SDK�ڲ�����
    OUT unsigned int    nImageLen;            // ԭʼͼ�񳤶�
    OUT enum  MvStereoAppGvspPixelType     enImageType; // ch:ͼ���ʽ | en:Image Type
    OUT unsigned short  nWidth;               // ch:ͼ��� | en:Image Width
    OUT unsigned short  nHeight;              // ch:ͼ��� | en:Image Height

    OUT unsigned int    nFrameNum;            // ch:֡�� | en:Frame Number
    OUT unsigned int    nDevTimeStampHigh;    // ch:ʱ�����32λ | en:Timestamp high 32 bits
    OUT unsigned int    nDevTimeStampLow;     // ch:ʱ�����32λ | en:Timestamp low 32 bits

    unsigned int        nReserved[32];        // �����ֽ�
}STC_IMAGE_INFO;

// ch:����ƴ��������Ϣ
typedef struct _STC_PointCloudMosaicConfigParam_
{
    unsigned int                        nLineNum;            // ���������������ٸ�����ƴ��Ϊһ������
    unsigned int                        nExpanRatio;         // ������࣬ÿ������������֮��ľ���
    bool                                bByFrame;            //.��֡��ƴ�� Ĭ��false
    enum MvStereoAppGvspPixelType       enPixelType;         //.���ظ�ʽ Ĭ��STC_PixelType_Gvsp_Coord3D_ABC16
    unsigned int                        nReserved[8];        //.�����ֽ�
}STC_PointCloudMosaicConfigParam;



typedef void(__stdcall* STC_DataSetCallBack)(STC_DataSet DataSet, void* pUser);
typedef void(__stdcall* STC_ExceptionCallBack)(STC_EXCEPTION_INFO* pstExcptInfo, void* pUser);
typedef void(__stdcall* STC_PointCloudCallback)(void*pData, int nDataSize, int nStep);


typedef struct _STC_BOX_F
{
    float center_x;           // ���ĵ�������
    float center_y;           // ���ĵ�������
    float width;              // ���ο�ȡ����Ϊ������
    float height;             // ���θ߶ȡ��߶�Ϊ�̰���
    float angle;              // ���νǶȡ�
}STC_BOX_F;

/* ===== ʵ���ָ�����Ϣ  ===== */
typedef struct _STC_INSTANCE_SEG_OBJ_POLYGON
{
    signed int       vertex_num;                                   //������
    STC_POINT_I      point[STC_PKGTK_SINGULATE_MAX_PTS_NUM];       //����
}STC_INSTANCE_SEG_OBJ_POLYGON;

typedef struct _STC_INSTANCE_SEG_OBJ_INFO
{
    signed int     cls_label;                          // ���ֵ
    float          confidence;                         // ���Ŷ�
    STC_BOX_F      obj_box;                            // Ŀ���
    char           label_name[128];                    // ��ǩ����
    STC_INSTANCE_SEG_OBJ_POLYGON polygon;              // �����
}STC_INSTANCE_SEG_OBJ_INFO;

// ʵ���ָ�����ص�
typedef struct _STC_INSTANCE_SEG_INFO
{
    signed int                     nObjNum;          //������
    STC_INSTANCE_SEG_OBJ_INFO      *pstObjInfo;      //ʵ����������obj_num����
}STC_INSTANCE_SEG_INFO;

/* ===== Ŀ��������Ϣ  ===== */
typedef struct _STC_DETECT_OBJ_INFO
{
    signed int     cls_label;            // ���ֵ
    float          confidence;           // ���Ŷ�
    STC_BOX_F      obj_box;              // Ŀ���
    STC_POINT_F    obj_point[4];         // �ĸ���
    char           label_name[128];      // ��ǩ����
}STC_DETECT_OBJ_INFO;

typedef struct _STC_DETECT_INFO
{
    signed int             nObjNum;         //������
    STC_DETECT_OBJ_INFO    *pstObjInfo;     //ʵ����������obj_num����
}STC_DETECT_INFO;

typedef struct _STC_TIME_STAMP_INFO
{
    unsigned int nInTimeHigh;              //��ʼʱ�����λ
    unsigned int nInTimeLow;               //��ʼʱ�����λ
    unsigned int nOutTimeHigh;             //����ʱ�����λ
    unsigned int nOutTimeLow;              //����ʱ�����λ
    unsigned int nReserved[4];
}STC_TIME_STAMP_INFO;

/* ===== ��е��ץȡ��Ϣ  ===== */
// 3Dλ��(F32)
typedef struct _STC_3D_POS_F32
{
    float  x;  // �ռ�x����
    float  y;  // �ռ�y����
    float  z;  // �ռ�z����
    float  rz; // ��Z����ת�Ƕ�
    float  ry; // ��Y����ת�Ƕ�
    float  rx; // ��X����ת�Ƕ�
}STC_3D_POS_F32;

#define  STC_GRASP_MAX_CVX_PNT_NUM                     (16)     // ͹��������
#define  STC_GRASP_MAX_GRIPPER_NUM                     (2)      // ���װִ������Ŀ


// ��е�۰���ץȡλ����Ϣ-������Ϣ
typedef struct _STC_GRASP_ROBOT_CAP_INFO_WORLD
{
    STC_3D_POS_F32                      stPkgPosRobot;                              // ����������ϵ��ץȡλ��
    STC_POINT_XYZ_F32                   stPkgRectRobot[4];                          // ����������ϵ��ץȡ������
    STC_POINT_XYZ_F32                   stPkgCvxRobot[STC_GRASP_MAX_CVX_PNT_NUM];   // ����������ϵ��ץȡ������
    int                                 nChPntNum;                                  // ͹������
    int                                 nReserved[16];                              // �����ֽ�
}STC_GRASP_ROBOT_CAP_INFO_WORLD;

// ��е�۰���ץȡλ����Ϣ-ͼ����Ϣ
typedef struct _STC_GRASP_ROBOT_CAP_INFO_IMG
{
    STC_POINT_F                         stPkgPtRgb;                                 // rgbͼ����ץȡ������
    STC_POINT_F                         stPkgRectRgb[4];                            // rgbͼ����ץȡ������
    STC_POINT_F                         stPkgCvxRgb[STC_GRASP_MAX_CVX_PNT_NUM];     // rgbͼ����ץȡ������
    int                                 nChPntNum;                                  // ͹������
    int                                 nReserved[16];                              // �����ֽ�
}STC_GRASP_ROBOT_CAP_INFO_IMG;

// ����λ����Ϣ
typedef struct _STC_GRASP_GRIPPER_POS_INFO
{
    STC_POINT_F                         stGripperRect[4];                           // ץȡ�ľ��ο�
    int                                 nReserved[16];                              // �����ֽ�
}STC_GRASP_GRIPPER_POS_INFO;

// ��е�۰���ץȡλ����Ϣ-������Ϣ
typedef struct _STC_GRASP_ROBOT_CAP_INFO_ASSIST
{
    float                              fPkgHeight;                                 // �����߶�
    int                                nFlagGripperNum;                            // ץȡʹ��ִ��������
    STC_GRASP_GRIPPER_POS_INFO         stGripperPos[STC_GRASP_MAX_GRIPPER_NUM];    // ִ����λ��
	int                                nSegClassId;                                // �ָ�ID��
    int                                nFlagPkgType;                               // �������ͱ�־λ
    int                                nReserved[16];                              // �����ֽ�
}STC_GRASP_ROBOT_CAP_INFO_ASSIST;

// ����������ϵ�°���ץȡλ����Ϣ
typedef struct _STC_GRASP_ROBOT_CAP_INFO
{
    STC_GRASP_ROBOT_CAP_INFO_WORLD    stPkgPosRobot;                               // ����λ����Ϣ
    STC_GRASP_ROBOT_CAP_INFO_IMG      stPkgPosImg;                                 // ͼ��λ����Ϣ
    STC_GRASP_ROBOT_CAP_INFO_ASSIST   stAssistInfo;                                // ������Ϣ
}STC_GRASP_ROBOT_CAP_INFO;


// rgb�����ץȡλ����Ϣ-ͼ����Ϣ
typedef struct _STC_GRASP_CAM_CAP_INFO_IMG
{
    STC_POINT_F                         stRgbImgCenterPt;                            // rgb����µ�ͼ�����ĵ�
    STC_POINT_F                         stRgbImgGraspPt;                             // rgb����µ�ͼ��ץȡ��
    STC_POINT_F                         stRgbImgCvxHull[STC_GRASP_MAX_CVX_PNT_NUM];  // rgb����µ�ͼ��͹��
    int                                 nChPntNum;                                   // ͹������
    int                                 nReserved[16];                               // �����ֽ�
}STC_GRASP_CAM_CAP_INFO_IMG;

// rgb�����ץȡλ����Ϣ-������Ϣ
typedef struct _STC_GRASP_CAM_CAP_INFO_WORLD
{
    STC_POINT_XYZ_F32                  stRgbCamCenterPt;                              // rgb����µĿռ����ĵ�
    STC_POINT_XYZ_F32                  stRgbCamGraspPt;                               // rgb����µĿռ�ץȡ��
    STC_POINT_XYZ_F32                  stRgbCamCvxHull[STC_GRASP_MAX_CVX_PNT_NUM];    // rgb����µĿռ�͹��
    int                                nChPntNum;                                     // ͹������
    int                                nRgbCamNormal[3];                              // rgb����µķ�����
    int                                nReserved[16];                                 // �����ֽ�
}STC_GRASP_CAM_CAP_INFO_WORLD;

// rgb�����ץȡλ����Ϣ-������Ϣ
typedef struct _STC_GRASP_CAM_CAP_INFO_ASSIST
{
    float                              fCapLength;                                     // ���ץȡ����
    float                              fCapWidth;                                      // ���ץȡ���
    float                              fCapAreaRatio;                                  // ץȡ�������
    int                                nSegClassId;                                    // �ָ�����
    int                                nDetectRoiId;                                   // ��������
    int                                nReserved[16];                                  // �����ֽ�
}STC_GRASP_CAM_CAP_INFO_ASSIST;


// rgb�����λ����Ϣ
typedef struct _STC_GRASP_CAM_CAP_POS_INFO
{
    STC_GRASP_CAM_CAP_INFO_WORLD       stPkgPosCam;                                     // ����λ����Ϣ
    STC_GRASP_CAM_CAP_INFO_IMG         stPkgPosImg;                                     // ͼ��λ����Ϣ
    STC_GRASP_CAM_CAP_INFO_ASSIST      stAssistInfo;                                    // ������Ϣ
}STC_GRASP_CAM_CAP_POS_INFO;

typedef struct _STC_grasp_robot_capture
{
    int                                nFrmId;                                          // �ص�Ҫ��֡��
    int                                nValidFlag;                                      // ץȡ��Ϣ�Ƿ���Ч
    int                                nRobotPkgPosNum;                                 // ����������ϵ�°���ץȡλ����Ŀ
	int                                nNoCapPosNum;                                    // ����������ϵ�°�������ץȡλ����Ŀ
    int                                nCameraPkgPosNum;                                // �������ϵ�°���ץȡλ����Ŀ
    STC_GRASP_ROBOT_CAP_INFO*          pstRobot_pkg_pos;                                //����������ϵ�°���ץȡλ����Ϣ, n = robot_pkg_pos_num, ������Ϊrobot_pkg_pos_num * sizeof(STC_GRASP_ROBOT_CAP_INFO)
    STC_GRASP_ROBOT_CAP_INFO*          pstNo_cap_pos;                                   //����������ϵ�°�������ץȡλ����Ϣ,��������ץȡλ����Ϣ�����С��̬�䶯��ʵ�ʴ�С��no_cap_pos_num���嶨
	STC_GRASP_CAM_CAP_POS_INFO*        pstCamera_pkg_pos;                               //�������ϵ�°���ץȡλ����Ϣ,m = camera_pkg_pos_num,������Ϊcamera_pkg_pos_num * sizeof(STC_GRASP_CAM_CAP_POS_INFO)
}STC_GRASP_INFO;

typedef struct _STC_3DPOINT_32_
{
    int nX;
    int nY;
    int nZ;
}STC_3DPOINT_32;

#endif //_MV_STA_DEFINE_H_
