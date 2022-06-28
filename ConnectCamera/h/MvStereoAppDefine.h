/***************************************************************************************************
*
* 版权信息：版权所有 (c) 2019, 杭州海康机器人技术有限公司, 保留所有权利
*
* 文件名称：MvStereoAppDefine.h
* 摘    要: 立体相机SDK，结构体定义
*
* 当前版本：2.1.0
* 作    者: 机器视觉SDK团队
* 日    期：2019.12.1
* 备    注：新建
****************************************************************************************************/

#ifndef _MV_STA_DEFINE_H_
#define _MV_STA_DEFINE_H_

//跨平台定义
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

// ch:设备类型定义 | en:Device Type Definition
#define MV_STA_UNKNOW_DEVICE                         0x00000000  // ch:未知设备类型，保留意义 | en:Unknown Device Type, Reserved 
#define MV_STA_GIGE_DEVICE                           0x00000001  // ch:GigE设备 | en:GigE Device
#define MV_STA_1394_DEVICE                           0x00000002  // ch:1394-a/b 设备 | en:1394-a/b Device 暂不支持
#define MV_STA_USB_DEVICE                            0x00000004  // ch:USB3.0 设备 | en:USB3.0 Device
#define MV_STA_CAMERALINK_DEVICE                     0x00000008  // ch:CameraLink设备 | en:CameraLink Device



// ch:设备的访问模式 | en:Device Access Mode
// ch:独占权限，其他APP只允许读CCP寄存器 | en:Exclusive authority, other APP is only allowed to read the CCP register
#define MV_STA_ACCESS_Exclusive                                         1
// ch:可以从5模式下抢占权限，然后以独占权限打开 | en:You can seize the authority from the 5 mode, and then open with exclusive authority
#define MV_STA_ACCESS_ExclusiveWithSwitch                               2
// ch:控制权限，其他APP允许读所有寄存器 | en:Control authority, allows other APP reading all registers
#define MV_STA_ACCESS_Control                                           3
// ch:可以从5的模式下抢占权限，然后以控制权限打开 | en:You can seize the authority from the 5 mode, and then open with control authority
#define MV_STA_ACCESS_ControlWithSwitch                                 4
// ch:以可被抢占的控制权限打开 | en:Open with seized control authority
#define MV_STA_ACCESS_ControlSwitchEnable                               5
// ch:可以从5的模式下抢占权限，然后以可被抢占的控制权限打开 | en:You can seize the authority from the 5 mode, and then open with seized control authority
#define MV_STA_ACCESS_ControlSwitchEnableWithKey                        6
// ch:读模式打开设备，适用于控制权限下 | en:Open with read mode and is available under control authority
#define MV_STA_ACCESS_Monitor                                           7




// ch:正确码定义
#define MV_STA_OK                                    0x00000000  ///< 成功，无错误

//通用错误码定义:范围0x80010000-0x800100FF
#define MV_STA_E_HANDLE                              0x80010000  ///< 错误或无效的句柄
#define MV_STA_E_SUPPORT                             0x80010001  ///< 不支持的功能
#define MV_STA_E_BUFOVER                             0x80010002  ///< 缓存已满
#define MV_STA_E_CALLORDER                           0x80010003  ///< 函数调用顺序错误
#define MV_STA_E_PARAMETER                           0x80010004  ///< 错误的参数
#define MV_STA_E_RESOURCE                            0x80010005  ///< 资源申请失败
#define MV_STA_E_NODATA                              0x80010006  ///< 无数据
#define MV_STA_E_PRECONDITION                        0x80010007  ///< 前置条件有误，或运行环境已发生变化
#define MV_STA_E_VERSION                             0x80010008  ///< 版本不匹配
#define MV_STA_E_NOENOUGH_BUF                        0x80010009  ///< 传入的内存空间不足
#define MV_STA_E_ABNORMAL_IMAGE                      0x8001000A  ///< 异常图像，可能是丢包导致图像不完整
#define MV_STA_E_LOAD_LIBRARY                        0x8001000B  ///< 动态导入DLL失败
#define MV_STA_E_ALGORITHM                           0x8001000C  ///< 算法错误
#define MV_STA_E_DeviceNotExist                      0x8001000D  ///< 设备不存在  （设备离线，或者 型号过滤掉了）

#define MV_STA_E_UNKNOW                              0x800100FF  ///< 未知的错误

// GenICam系列错误
#define MV_STA_E_GC_GENERIC                          0x80010100  ///< 通用错误 | en:General error
#define MV_STA_E_GC_ARGUMENT                         0x80010101  ///< 参数非法 | en:Illegal parameters
#define MV_STA_E_GC_RANGE                            0x80010102  ///< 值超出范围 | en:The value is out of range
#define MV_STA_E_GC_PROPERTY                         0x80010103  ///< 属性 | en:Property
#define MV_STA_E_GC_RUNTIME                          0x80010104  ///< 运行环境有问题 | en:Running environment error
#define MV_STA_E_GC_LOGICAL                          0x80010105  ///< 逻辑错误 | en:Logical error
#define MV_STA_E_GC_ACCESS                           0x80010106  ///< 节点访问条件有误 | en:Node accessing condition error
#define MV_STA_E_GC_TIMEOUT                          0x80010107  ///< 超时 | en:Timeout
#define MV_STA_E_GC_DYNAMICCAST                      0x80010108  ///< 转换异常 | en:Transformation exception
#define MV_STA_E_GC_UNKNOW                           0x800101FF  ///< GenICam未知错误 | en:GenICam unknown error

//GigE_STATUS对应的错误码
#define MV_STA_E_NOT_IMPLEMENTED                     0x80010200  ///< 命令不被设备支持 | en:The command is not supported by device
#define MV_STA_E_INVALID_ADDRESS                     0x80010201  ///< 访问的目标地址不存在 | en:The target address being accessed does not exist
#define MV_STA_E_WRITE_PROTECT                       0x80010202  ///< 目标地址不可写 | en:The target address is not writable
#define MV_STA_E_ACCESS_DENIED                       0x80010203  ///< 设备无访问权限 | en:No permission
#define MV_STA_E_BUSY                                0x80010204  ///< 设备忙，或网络断开 | en:Device is busy, or network disconnected
#define MV_STA_E_PACKET                              0x80010205  ///< 网络包数据错误 | en:Network data packet error
#define MV_STA_E_NETER                               0x80010206  ///< 网络相关错误 | en:Network error
// GigE相机特有的错误码
#define MV_STA_E_IP_CONFLICT                         0x80010221  ///< 设备IP冲突 | en:Device IP conflict


//升级时对应的错误码:
#define MV_STA_E_UPG_FILE_MISMATCH                   0x80010400 ///< 升级固件不匹配 | en:Firmware mismatches
#define MV_STA_E_UPG_LANGUSGE_MISMATCH               0x80010401 ///< 升级固件语言不匹配 | en:Firmware language mismatches
#define MV_STA_E_UPG_CONFLICT                        0x80010402 ///< 升级冲突（设备已经在升级了再次请求升级即返回此错误） | en:Upgrading conflicted (repeated upgrading requests during device upgrade)
#define MV_STA_E_UPG_INNER_ERR                       0x80010403 ///< 升级时相机内部出现错误 | en:Camera internal error during upgrade
#define MV_STA_E_UPG_UNKNOW                          0x800104FF ///< 升级时未知错误 | en:Unknown error during upgrade


//相机类型
enum MV_STA_CAMERA_TYPE
{
    MV_STA_CAMERA_3D                         = 3, //3D相机
    MV_STA_CAMERA_2D                         = 2, //2D相机
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
    MV_STA_EXCEPTION_DEV_DISCONNECT = 0x00008001,                   // 设备断开连接
};


typedef struct _MV_STEREOCAM_NET_INFO_
{
    unsigned int            nIpCfgOption;                           // 设备支持的IP类型
    unsigned int            nIpCfgCurrent;                          // 设备当前IP类型
    unsigned int            nCurrentIp;                             // 设备当前IP
    unsigned int            nCurrentSubNetMask;                     // 设备当前子网掩码
    unsigned int            nDefultGateWay;                         // 设备默认网关
    unsigned char           chManufacturerName[32];                 // 设备厂商
    unsigned char           chModelName[32];                        // 设备型号
    unsigned char           chDeviceVersion[32];                    // 设备版本
    unsigned char           chManufacturerSpecificInfo[48];         // 设备厂商特殊信息
    unsigned char           chSerialNumber[16];                     // 设备序列号
    unsigned char           chUserDefinedName[16];                  // 设备用户自定义名称
    unsigned int            nNetExport;                             // 主机网口IP地址

    unsigned int            nReserved[4];                           // 保留字节，其中 0：Mac高；1：Mac低；

}MV_STEREOCAM_NET_INFO;

#define INFO_MAX_BUFFER_SIZE 64    //新定义256
typedef struct _MV_STA_USB3_DEVICE_INFO_
{
    unsigned char           CrtlInEndPoint;                          // ch:控制输入端点 | en:Control input endpoint
    unsigned char           CrtlOutEndPoint;                         // ch:控制输出端点 | en:Control output endpoint
    unsigned char           StreamEndPoint;                          // ch:流端点 | en:Flow endpoint
    unsigned char           EventEndPoint;                           // ch:事件端点 | en:Event endpoint
    unsigned short          idVendor;                                // ch:供应商ID号 | en:Vendor ID Number
    unsigned short          idProduct;                               // ch:产品ID号 | en:Device ID Number
    unsigned int            nDeviceNumber;                           // ch:设备序列号  | en:Device Serial Number
    unsigned char           chDeviceGUID[INFO_MAX_BUFFER_SIZE];      // ch:设备GUID号 | en:Device GUID Number
    unsigned char           chVendorName[INFO_MAX_BUFFER_SIZE];      // ch:供应商名字 | en:Vendor Name
    unsigned char           chModelName[INFO_MAX_BUFFER_SIZE];       // ch:型号名字 | en:Model Name
    unsigned char           chFamilyName[INFO_MAX_BUFFER_SIZE];      // ch:家族名字 | en:Family Name
    unsigned char           chDeviceVersion[INFO_MAX_BUFFER_SIZE];   // ch:设备版本号 | en:Device Version
    unsigned char           chManufacturerName[INFO_MAX_BUFFER_SIZE];// ch:制造商名字 | en:Manufacturer Name
    unsigned char           chSerialNumber[INFO_MAX_BUFFER_SIZE];    // ch:序列号 | en:Serial Number
    unsigned char           chUserDefinedName[INFO_MAX_BUFFER_SIZE]; // ch:用户自定义名字 | en:User Defined Name
    unsigned int            nbcdUSB;                                 // ch:支持的USB协议 | en:Support USB Protocol
    unsigned int            nDeviceAddress;                          // ch:设备地址 | en:Device Address
    unsigned int            nReserved[2];                            // ch:保留字节 | en:Reserved bytes
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

// 最大支持的设备个数
#define MV_STEREOCAM_MAX_NUM      256
// 设备信息列表
typedef struct _MV_STEREOCAM_NET_INFO_LIST_
{
    unsigned int                nDeviceNum;                            // 设备数量
    MV_STEREOCAM_NET_INFO*      pDeviceInfo[MV_STEREOCAM_MAX_NUM];     // 设备信息
}MV_STEREOCAM_NET_INFO_LIST;


// ch:设备信息 | en:Device Infomation
typedef struct _MV_STA_DEVICE_INFO_
{
    // ch:common info | en:common info 
    unsigned short      nMajorVer;
    unsigned short      nMinorVer;
    unsigned int        nMacAddrHigh;               //  Mac高地址
    unsigned int        nMacAddrLow;                //  Mac低地址
    unsigned int        nTLayerType;                //  ch:设备传输层协议类型，e.g. MV_STA_GIGE_DEVICE | MV_STA_USB_DEVICE
    unsigned int        nReserved[4];               //  其中：nReserved[0]，MV_STA_CAMERA_3D(3)表示3D相机；MV_STA_CAMERA_2D(2)表示2D相机

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
    unsigned int             nDeviceNum;                            // ch:在线设备数量 | en:Online Device Number
    MV_STA_DEVICE_INFO*      pDeviceInfo[MV_STEREOCAM_MAX_NUM];     // ch:支持最多256个设备 | en:Support up to 256 devices

}MV_STA_DEVICE_INFO_LIST;

typedef struct _MV_STA_ALL_MATCH_INFO_
{
    unsigned int    nType;          // ch:需要输出的信息类型，e.g. MV_STA_MATCH_TYPE_NET_DETECT
    void*           pInfo;          // ch:输出的信息缓存，由调用者分配
    unsigned int    nInfoSize;      // ch:信息缓存的大小

}MV_STA_ALL_MATCH_INFO;


// ch:信息类型 | en:Information Type
#define MV_STA_MATCH_TYPE_NET_DETECT             0x00000001      // ch:网络流量和丢包信息 | en:Network traffic and packet loss information
#define MV_STA_MATCH_TYPE_USB_DETECT             0x00000002      // ch:host接收到来自U3V设备的字节总数 | en:The total number of bytes host received from U3V device


// ch:网络流量和丢包信息反馈结构体，对应类型为 MV_STA_MATCH_TYPE_NET_DETECT
// en:Network traffic and packet loss feedback structure, the corresponding type is MV_STA_MATCH_TYPE_NET_DETECT
typedef struct _MV_STA_MATCH_INFO_NET_DETECT_
{
    int64_t         nReceiveDataSize;            // ch:已接收数据大小  [统计StartGrabbing和StopGrabbing之间的数据量] | en:Received data size 
    int64_t         nLostPacketCount;            // ch:丢失的包数量 | en:Number of packets lost
    unsigned int    nLostFrameCount;             // ch:丢帧数量 | en:Number of frames lost
    unsigned int    nNetRecvFrameCount;          // ch:保留 | en:Reserved
    __int64         nRequestResendPacketCount;   // 请求重发包数
    __int64         nResendPacketCount;          // 重发包数
}MV_STA_MATCH_INFO_NET_DETECT;

// ch:host收到从u3v设备端的总字节数，对应类型为 MV_STA_MATCH_TYPE_USB_DETECT | en:The total number of bytes host received from the u3v device side, the corresponding type is MV_STA_MATCH_TYPE_USB_DETECT
typedef struct _MV_STA_MATCH_INFO_USB_DETECT_
{
    int64_t         nReceiveDataSize;           // ch:已接收数据大小    [统计OpenDevicce和CloseDevice之间的数据量] | en:Received data size
    unsigned int    nReceivedFrameCount;        // ch:已收到的帧数 | en:Number of frames received
    unsigned int    nErrorFrameCount;           // ch:错误帧数 | en:Number of error frames
    unsigned int    nReserved[2];               // ch:保留 | en:Reserved
}MV_STA_MATCH_INFO_USB_DETECT;


//输出结果类型
#define STC_DATA_MSG_TYPE_UNKNOWN                   0
#define STC_DATA_MSG_TYPE_IMG_RAW                   1

// 线激光主动上报体积数据
#define STC_DATA_MSG_TYPE_DWS_VOLUME                4

// 双目相机主动上报体积数据
#define STC_DATA_MSG_TYPE_STEREO_VOLUME             5

// 当前帧号（从相机开机计算）
// 线激光相机MV-DL2040-04B-H 固件V1.1.0之后支持
// 线激光相机MV-DL2025-04H-H 固件部分版本支持
#define STC_3D_Camera_Current_Frame_ID              0xa5a50105


 
// 3D 轮廓线常用节点
// 行点数(深度图宽度)
#define STC_3D_Profile_LinePntNum                   0xa5a53d01
//行数  (深度图高度)
#define STC_3D_Profile_Count                        0xa5a53d02
//亮度图
#define STC_3D_Profile_Intensity                    0xa5a53d03
//宽度图
#define STC_3D_Profile_Thickness                    0xa5a53d04
//前进方向
#define STC_3D_Profile_RunDir                       0xa5a53d05
//第一个轮廓的帧号
#define STC_3D_Profile_FirstFrmID                   0xa5a53d06
//采样间隔
#define STC_3D_Profile_CoordScale                   0xa5a53d07
//采样起始点的偏移
#define STC_3D_Profile_CoordOffset                  0xa5a53d08
//中心点坐标信息
#define STC_3D_Profile_CenterCoordinate             0xa5a53d09
//RGBD时间戳信息
#define STC_3D_Profile_TimeStamp                    0xa5a53d10
//为1 时表示表示单次触发接触或者超时，需要输出一帧深度图
#define STC_3D_Profile_TriggerEnd                   0xa5a53d0A
//RGB图像
#define STC_3D_Profile_ExtendImg                    0xa5a53d0B
//RGBD单件分离包裹信息
#define STC_3D_Profile_SingulatePkginfo             0xa5a53d0C
//实例分割结果
#define STC_3D_Profile_InstanceSegInfo              0xa5a53d0D
//目标检测
#define STC_3D_Profile_DetectInfo                   0xa5a53d0E
//抓取信息
#define STC_3D_Profile_GraspInfo                    0xa5a53d0F

// 3D位置(F32)
typedef struct _STC_POINT_XYZ_F32
{
    float  x;              // 空间x坐标
    float  y;              // 空间y坐标
    float  z;              // 空间z坐标
}STC_POINT_XYZ_F32;

//整型点结构体 
typedef struct _STC_POINT_I
{
    signed int x;          // x坐标
    signed int y;          // y坐标
}STC_POINT_I;

//浮点型点结构体
typedef struct _STC_POINT_F
{
    float x;               // x坐标
    float y;               // y坐标
}STC_POINT_F;

//整型多边形结构体
typedef struct __STC_POLYGON_I
{
    bool bSupport ;           //是否支持
    STC_POINT_I   point[4];   //顶点
}_STC_POLYGON_I;

//浮点型多边形结构体
typedef struct _STC_POLYGON_F
{
    bool bSupport ;           // 是否支持
    STC_POINT_F   point[4];   //顶点
}STC_POLYGON_F;

// 相机原始图、点云图、深度图，都用此结构体
typedef struct _STC_DATA_IMAGE_
{
    unsigned short      nWidth;                             // 图像宽
    unsigned short      nHeight;                            // 图像高
    enum MvStereoAppGvspPixelType     enPixelType;          // 像素格式
    unsigned char*      pData;                              // 相机原始图像格式
    unsigned int        nFrameLen;                          // 图像长度

    unsigned int        nFrameNum;                          // 帧号
    unsigned int        nDevTimeStampHigh;                  // 时间戳高32位
    unsigned int        nDevTimeStampLow;                   // 时间戳低32位
    unsigned int        nReserved0;                         // 保留，8字节对齐
    int64_t             nHostTimeStamp;                     // 主机生成的时间戳

    unsigned int        nReserved[8];                       //保留字节 nReserved[0] MV_STA_GetImage接口调用时为本帧图像丢包数

}STC_DATA_IMAGE;

// 相机亮度图 Intensity
typedef struct _STC_PROFILE_INTENSITYE_
{
    unsigned int        nDataLen;                          // 数据长度
    unsigned char*      pData;                             // 数据

    unsigned int        nReserved[8];                     // 保留字节

}STC_PROFILE_INTENSITY;

// 相机亮度图 Intensity
typedef struct _STC_PROFILE_THICKNESS_
{
    unsigned int        nDataLen;                          // 数据长度
    unsigned char*      pData;                             // 数据

    unsigned int        nReserved[8];                      // 保留字节

}STC_PROFILE_THICKNESS;

// 3D 轮廓仪的前进方向
typedef struct _STC_PROFILE_RUNDIR_
{
    float       x;
    float       y;
    float       z;
}STC_PROFILE_RUNDIR;

//3D轮廓仪 采样间隔
typedef struct _STC_PROFILE_COORDSCALE_
{
    float       x;
    float       y;
    float       z;
}STC_PROFILE_COORDSCALE;

//3D轮廓仪 采样起始点的偏移
typedef struct STC_PROFILE_COORDOFFSET
{
    int        x;
    int        y;
    int        z;
}STC_PROFILE_COORDOFFSET;

//高帧率轮廓仪  中心点坐标信息
typedef struct _STC_CENTERCOORDINATE_
{
    unsigned int        nDataLen;                          // 数据长度
    int*                pData;                             // 数据
}STC_CENTERCOORDINATE;

//扩展图像信息
typedef struct _STC_EXTEND_IMAGE_
{
    int nPixelFormat;      /* 像素格式：兼容RGB8,BGR8，RGB8_Planar */
    int nWidth;            /* rgb width */
    int nHeight;           /* rgb height */
    unsigned int nDataLen; /*imagesize*/
    int nFlag;             /* 图像置换标志位：为1时替换image，为0时不需要替换 */
    int  nRes[3];          /* rgb 保留字节 */
    unsigned char* pData;  /* rgb图数据 */
}STC_EXTEND_IMAGE;

// 包裹位姿 3d
#define  STC_PKGTK_SINGULATE_MAX_PKG_NUM               200         // 最大包裹数目
#define  STC_PKGTK_SINGULATE_MAX_PTS_NUM               16          // 包裹凸包最大顶点数

typedef struct _STC_PKGTK_SINGULATE_PKG3D_
{
    STC_POINT_XYZ_F32   rect_vertexes[4];                                       // 矩形框顶点坐标（接目标检测）
    STC_POINT_XYZ_F32   convex_vertexes[STC_PKGTK_SINGULATE_MAX_PTS_NUM];       // 凸包集顶点坐标（接实例分割）
    signed int          convex_pts_num;                                         // 凸包集顶点数目
    signed int          flag_rect;                                              // 矩形框顶点坐标是否有效（HKA_FALSE: 无效, HKA_TRUE: 有效）
    signed int          flag_convex;                                            // 凸包集顶点坐标是否有效（HKA_FALSE: 无效, HKA_TRUE: 有效）

}STC_PKGTK_SINGULATE_PKG3D;

typedef struct _STC_SINGULATE_CALPOSE_
{
    unsigned int nPkgId;                               /**< 包裹ID号 */
    STC_PKGTK_SINGULATE_PKG3D stPkgs3d;                /**< 包裹信息 */
}STC_SINGULATE_CALPOSE;

//包裹信息
typedef struct _STC_PACKAGE_INFO_
{
    unsigned int nFrameId;                  /**< 帧号 */
    signed int nPkgsNum;                    /**< 包裹数量 */
    //STC_SINGULATE_CALPOSE pstPkgInfo[STC_PKGTK_SINGULATE_MAX_PKG_NUM];      /**< 包裹信息集合 */
    STC_SINGULATE_CALPOSE *pstPkgInfo;      /**< 包裹信息集合 */
}STC_PACKAGE_INFO;

// 深度图渲染信息
typedef struct _STC_DEPTH_MAP_DISPLAY_EX
{
    // 包裹的位置  （实际坐标）
    STC_POLYGON_F     szPackageRoi;
    // 测量区域     （整幅图的比例，最大是1； 0.5代表中间，不是实际坐标，4个顶点是按照图像比例传的)
    STC_POLYGON_F    szMeasureRoi;
    // 水印，会在图像左上角显示
    unsigned char szImageWatermark[32];
}STC_DEPTH_MAP_DISPLAY_EX;

// 包裹信息
typedef struct _STC_DWS_VOLUME_INFO
{
    // 共用
    float                  volume;                       // 目标体积
    float                  length;                       // 目标长
    float                  width;                        // 目标宽
    float                  height;                       // 目标高
    // 边缘点模块 
    float                  rectangularity;               // 矩形度(取值范围0~1, 越接近1矩形度越高)    //此字段暂时无相机支持；
    // 轮廓模块和图像模块
    STC_POINT_XYZ_F32      vertex_pnts[4];               // 目标顶点     //此字段暂时无相机支持；

    signed int             obj_id;                       // 目标ID号
    unsigned short         start_frm_id;                 // 起始帧号
    unsigned short         end_frm_id;                   // 结束帧号
}STC_DWS_VOLUME_INFO;


// 体积侧数据
#pragma pack(4)
typedef struct _STC_STEREO_VOLUME_INFO
{
    unsigned __int64       nVolume;                      //积分体积
    unsigned int           nLength;                      //长度
    unsigned int           nWidth;                       //宽度
    unsigned int           nHeight;                      //高度
    STC_POINT_I            vertex_pnts[4];               //目标顶点（图像坐标值）
}STC_STEREO_VOLUME_INFO;
#pragma pack()


// 归一化深度图和点云图时的输入参数定义
typedef struct _STC_NORMALIZE_IMAGE_
{
    IN unsigned short       nWidth;                      // 图像宽
    IN unsigned short       nHeight;                     // 图像高
    IN enum MvStereoAppGvspPixelType     enSrcPixelType; // 像素格式
    IN unsigned char*       pData;                       // 相机原始图像格式
    IN unsigned int         nLen;                        // 图像长度

    // 像素格式。如果输入的是深度图，那么输出格式为Mono16；如果输入的是点云图，那么输出格式为ABC16或ABC32；
    IN OUT enum MvStereoAppGvspPixelType   enDstPixelType;
    OUT unsigned char*      pNormalizedData;            // 相机原始图像格式，缓存由SDK内部分配
    OUT unsigned int        nNormalizedLen;             // 图像长度

}STC_NORMALIZE_IMAGE;


// 深度图Mono16转TIFF结构体
typedef struct _STC_IMG_SAVE_MONO16_TO_TIFF_PARAM_
{
    enum MvStereoAppGvspPixelType  enPixelType;        // 输入数据像素格式
    unsigned char*                 pData;              // 输入数据缓存
    unsigned int                   nDataLen;           // 输入数据大小
    unsigned short                 nWidth;             // 输入图像宽
    unsigned short                 nHeight;            // 输入图像高

    char                           pImagePath[256];    // 输出文件路径, 当传入相对路径时，由于内部需要转绝对路径，总路径长度不能超过windows限制，否则会报参数错误
    int                            iMethodValue;       // 无效参数，采用默认值0即可
    unsigned int                   nReserved[8];       // 保留字节
}STC_IMG_SAVE_MONO16_TO_TIFF_PARAM;

// 深度图Mono16转BMP结构体
typedef struct _STC_IMG_SAVE_MONO16_TO_BMP_PARAM_
{
    enum MvStereoAppGvspPixelType  enPixelType;        // 输入数据像素格式
    unsigned char*                 pData;              // 输入数据缓存
    unsigned int                   nDataLen;           // 输入数据大小
    unsigned short                 nWidth;             // 输入图像宽
    unsigned short                 nHeight;            // 输入图像高

    char                           pImagePath[256];    // 输出文件路径, 当传入相对路径时，由于内部需要转绝对路径，总路径长度不能超过windows限制，否则会报参数错误
    unsigned int                   nReserved[8];       // 保留字节
}STC_IMG_SAVE_MONO16_TO_BMP_PARAM;


// 深度图Mono16转JPG结构体
typedef struct _STC_IMG_SAVE_MONO16_TO_JPG_PARAM_
{
    enum MvStereoAppGvspPixelType  enPixelType;        // 输入数据像素格式
    unsigned char*                 pData;              // 输入数据缓存
    unsigned int                   nDataLen;           // 输入数据大小
    unsigned short                 nWidth;             // 输入图像宽
    unsigned short                 nHeight;            // 输入图像高

    unsigned int                   nQuality;           // 输出JPG编码质量(0-100]
    char                           pImagePath[256];    // 输出文件路径,当传入相对路径时，由于内部需要转绝对路径，总路径长度不能超过windows限制，否则会报参数错误
    unsigned int                   nReserved[8];       // 保留字节
}STC_IMG_SAVE_MONO16_TO_JPG_PARAM;

// 点云图ABC16转PYL,OBJ,CSV共用结构体
typedef struct _STC_IMG_SAVE_ABC16_TO_PLY_PARAM_
{
    unsigned int                   nLinePntNum;        // 每一行点的数量,对应图像宽
    unsigned int                   nLineNum;           // 行数,对应图像高
    enum MvStereoAppGvspPixelType  enSrcPixelType;     // 输入数据像素格式
    unsigned char*                 pSrcData;           // 输入数据缓存
    unsigned int                   nSrcDataLen;        // 输入数据大小

    void*                          pDstBuf;            // 输出数据缓存
    unsigned int                   nDstBufSize;        // 输出缓冲区大小(nLinePntNum * nLineNum * (16*3 + 4) + 2048)
    unsigned int                   nDstBufLen;         // 输出数据长度
    unsigned int                   nReserved[8];       // 保留字节

}STC_IMG_SAVE_ABC16_TO_PLY_PARAM, STC_IMG_SAVE_ABC16_TO_OBJ_PARAM, STC_IMG_SAVE_ABC16_TO_CSV_PARAM;

// 体积测量、物体定位信息
typedef struct _STC_DATA_MEASURE_VOLUME_
{
    float          fLength;
    float          fWidth;
    float          fHeight;
    float          fVolume;
    struct POINT_XY
    {
        float       fX;                         // X坐标
        float       fY;                         // Y坐标
        float       fZ;                         // Y坐标
        int         nReserved[8];               // 保留字段
    }stVolPos[4];

    int             nReserved[8];
} STC_DATA_MEASURE_VOLUME;


typedef void*   STC_Object;
typedef STC_Object STC_DataSet; 


// 异常信息
typedef struct _STC_EXCEPTION_INFO_
{
    unsigned int        nExceptionID;         // 异常ID    MvSTADevException
    char                strExceptionDes[256]; // 异常描述

    unsigned int        nReserved[16];        // 保留字节

}STC_EXCEPTION_INFO;

// ch:输出图像的信息 | en:Output Frame Information
typedef struct _STC_IMAGE_INFO_
{
    OUT unsigned char*  pImageBuf;            // 原始图像缓存，由SDK内部分配
    OUT unsigned int    nImageLen;            // 原始图像长度
    OUT enum  MvStereoAppGvspPixelType     enImageType; // ch:图像格式 | en:Image Type
    OUT unsigned short  nWidth;               // ch:图像宽 | en:Image Width
    OUT unsigned short  nHeight;              // ch:图像高 | en:Image Height

    OUT unsigned int    nFrameNum;            // ch:帧号 | en:Frame Number
    OUT unsigned int    nDevTimeStampHigh;    // ch:时间戳高32位 | en:Timestamp high 32 bits
    OUT unsigned int    nDevTimeStampLow;     // ch:时间戳低32位 | en:Timestamp low 32 bits

    unsigned int        nReserved[32];        // 保留字节
}STC_IMAGE_INFO;

// ch:点云拼接配置信息
typedef struct _STC_PointCloudMosaicConfigParam_
{
    unsigned int                        nLineNum;            // 轮廓的数量，多少个轮廓拼接为一个点云
    unsigned int                        nExpanRatio;         // 步进间距，每两个相邻轮廓之间的距离
    bool                                bByFrame;            //.按帧号拼接 默认false
    enum MvStereoAppGvspPixelType       enPixelType;         //.像素格式 默认STC_PixelType_Gvsp_Coord3D_ABC16
    unsigned int                        nReserved[8];        //.保留字节
}STC_PointCloudMosaicConfigParam;



typedef void(__stdcall* STC_DataSetCallBack)(STC_DataSet DataSet, void* pUser);
typedef void(__stdcall* STC_ExceptionCallBack)(STC_EXCEPTION_INFO* pstExcptInfo, void* pUser);
typedef void(__stdcall* STC_PointCloudCallback)(void*pData, int nDataSize, int nStep);


typedef struct _STC_BOX_F
{
    float center_x;           // 中心点列坐标
    float center_y;           // 中心点行坐标
    float width;              // 矩形宽度。宽度为长半轴
    float height;             // 矩形高度。高度为短半轴
    float angle;              // 矩形角度。
}STC_BOX_F;

/* ===== 实例分割结果信息  ===== */
typedef struct _STC_INSTANCE_SEG_OBJ_POLYGON
{
    signed int       vertex_num;                                   //顶点数
    STC_POINT_I      point[STC_PKGTK_SINGULATE_MAX_PTS_NUM];       //顶点
}STC_INSTANCE_SEG_OBJ_POLYGON;

typedef struct _STC_INSTANCE_SEG_OBJ_INFO
{
    signed int     cls_label;                          // 类别值
    float          confidence;                         // 置信度
    STC_BOX_F      obj_box;                            // 目标框
    char           label_name[128];                    // 标签名称
    STC_INSTANCE_SEG_OBJ_POLYGON polygon;              // 多边形
}STC_INSTANCE_SEG_OBJ_INFO;

// 实例分割输出回调
typedef struct _STC_INSTANCE_SEG_INFO
{
    signed int                     nObjNum;          //检测个数
    STC_INSTANCE_SEG_OBJ_INFO      *pstObjInfo;      //实际数量根据obj_num而定
}STC_INSTANCE_SEG_INFO;

/* ===== 目标检测结果信息  ===== */
typedef struct _STC_DETECT_OBJ_INFO
{
    signed int     cls_label;            // 类别值
    float          confidence;           // 置信度
    STC_BOX_F      obj_box;              // 目标框
    STC_POINT_F    obj_point[4];         // 四个点
    char           label_name[128];      // 标签名称
}STC_DETECT_OBJ_INFO;

typedef struct _STC_DETECT_INFO
{
    signed int             nObjNum;         //检测个数
    STC_DETECT_OBJ_INFO    *pstObjInfo;     //实际数量根据obj_num而定
}STC_DETECT_INFO;

typedef struct _STC_TIME_STAMP_INFO
{
    unsigned int nInTimeHigh;              //开始时间戳高位
    unsigned int nInTimeLow;               //开始时间戳低位
    unsigned int nOutTimeHigh;             //结束时间戳高位
    unsigned int nOutTimeLow;              //结束时间戳低位
    unsigned int nReserved[4];
}STC_TIME_STAMP_INFO;

/* ===== 机械臂抓取信息  ===== */
// 3D位姿(F32)
typedef struct _STC_3D_POS_F32
{
    float  x;  // 空间x坐标
    float  y;  // 空间y坐标
    float  z;  // 空间z坐标
    float  rz; // 绕Z轴旋转角度
    float  ry; // 绕Y轴旋转角度
    float  rx; // 绕X轴旋转角度
}STC_3D_POS_F32;

#define  STC_GRASP_MAX_CVX_PNT_NUM                     (16)     // 凸包最大点数
#define  STC_GRASP_MAX_GRIPPER_NUM                     (2)      // 最大安装执行器数目


// 机械臂包裹抓取位姿信息-物理信息
typedef struct _STC_GRASP_ROBOT_CAP_INFO_WORLD
{
    STC_3D_POS_F32                      stPkgPosRobot;                              // 机器人坐标系下抓取位姿
    STC_POINT_XYZ_F32                   stPkgRectRobot[4];                          // 机器人坐标系下抓取面坐标
    STC_POINT_XYZ_F32                   stPkgCvxRobot[STC_GRASP_MAX_CVX_PNT_NUM];   // 机器人坐标系下抓取面坐标
    int                                 nChPntNum;                                  // 凸包点数
    int                                 nReserved[16];                              // 保留字节
}STC_GRASP_ROBOT_CAP_INFO_WORLD;

// 机械臂包裹抓取位姿信息-图像信息
typedef struct _STC_GRASP_ROBOT_CAP_INFO_IMG
{
    STC_POINT_F                         stPkgPtRgb;                                 // rgb图像上抓取点坐标
    STC_POINT_F                         stPkgRectRgb[4];                            // rgb图像上抓取面坐标
    STC_POINT_F                         stPkgCvxRgb[STC_GRASP_MAX_CVX_PNT_NUM];     // rgb图像上抓取面坐标
    int                                 nChPntNum;                                  // 凸包点数
    int                                 nReserved[16];                              // 保留字节
}STC_GRASP_ROBOT_CAP_INFO_IMG;

// 吸嘴位置信息
typedef struct _STC_GRASP_GRIPPER_POS_INFO
{
    STC_POINT_F                         stGripperRect[4];                           // 抓取的矩形框
    int                                 nReserved[16];                              // 保留字节
}STC_GRASP_GRIPPER_POS_INFO;

// 机械臂包裹抓取位姿信息-辅助信息
typedef struct _STC_GRASP_ROBOT_CAP_INFO_ASSIST
{
    float                              fPkgHeight;                                 // 包裹高度
    int                                nFlagGripperNum;                            // 抓取使用执行器数量
    STC_GRASP_GRIPPER_POS_INFO         stGripperPos[STC_GRASP_MAX_GRIPPER_NUM];    // 执行器位置
	int                                nSegClassId;                                // 分割ID号
    int                                nFlagPkgType;                               // 包裹类型标志位
    int                                nReserved[16];                              // 保留字节
}STC_GRASP_ROBOT_CAP_INFO_ASSIST;

// 机器人坐标系下包裹抓取位姿信息
typedef struct _STC_GRASP_ROBOT_CAP_INFO
{
    STC_GRASP_ROBOT_CAP_INFO_WORLD    stPkgPosRobot;                               // 物理位姿信息
    STC_GRASP_ROBOT_CAP_INFO_IMG      stPkgPosImg;                                 // 图像位姿信息
    STC_GRASP_ROBOT_CAP_INFO_ASSIST   stAssistInfo;                                // 辅助信息
}STC_GRASP_ROBOT_CAP_INFO;


// rgb相机下抓取位姿信息-图像信息
typedef struct _STC_GRASP_CAM_CAP_INFO_IMG
{
    STC_POINT_F                         stRgbImgCenterPt;                            // rgb相机下的图像中心点
    STC_POINT_F                         stRgbImgGraspPt;                             // rgb相机下的图像抓取点
    STC_POINT_F                         stRgbImgCvxHull[STC_GRASP_MAX_CVX_PNT_NUM];  // rgb相机下的图像凸包
    int                                 nChPntNum;                                   // 凸包点数
    int                                 nReserved[16];                               // 保留字节
}STC_GRASP_CAM_CAP_INFO_IMG;

// rgb相机下抓取位姿信息-物理信息
typedef struct _STC_GRASP_CAM_CAP_INFO_WORLD
{
    STC_POINT_XYZ_F32                  stRgbCamCenterPt;                              // rgb相机下的空间中心点
    STC_POINT_XYZ_F32                  stRgbCamGraspPt;                               // rgb相机下的空间抓取点
    STC_POINT_XYZ_F32                  stRgbCamCvxHull[STC_GRASP_MAX_CVX_PNT_NUM];    // rgb相机下的空间凸包
    int                                nChPntNum;                                     // 凸包点数
    int                                nRgbCamNormal[3];                              // rgb相机下的法向量
    int                                nReserved[16];                                 // 保留字节
}STC_GRASP_CAM_CAP_INFO_WORLD;

// rgb相机下抓取位姿信息-辅助信息
typedef struct _STC_GRASP_CAM_CAP_INFO_ASSIST
{
    float                              fCapLength;                                     // 类的抓取长度
    float                              fCapWidth;                                      // 类的抓取宽度
    float                              fCapAreaRatio;                                  // 抓取面积比例
    int                                nSegClassId;                                    // 分割结果号
    int                                nDetectRoiId;                                   // 检测区域号
    int                                nReserved[16];                                  // 保留字节
}STC_GRASP_CAM_CAP_INFO_ASSIST;


// rgb相机下位姿信息
typedef struct _STC_GRASP_CAM_CAP_POS_INFO
{
    STC_GRASP_CAM_CAP_INFO_WORLD       stPkgPosCam;                                     // 物理位姿信息
    STC_GRASP_CAM_CAP_INFO_IMG         stPkgPosImg;                                     // 图像位姿信息
    STC_GRASP_CAM_CAP_INFO_ASSIST      stAssistInfo;                                    // 辅助信息
}STC_GRASP_CAM_CAP_POS_INFO;

typedef struct _STC_grasp_robot_capture
{
    int                                nFrmId;                                          // 回调要有帧号
    int                                nValidFlag;                                      // 抓取信息是否有效
    int                                nRobotPkgPosNum;                                 // 机器人坐标系下包裹抓取位姿数目
	int                                nNoCapPosNum;                                    // 机器人坐标系下包裹不可抓取位姿数目
    int                                nCameraPkgPosNum;                                // 相机坐标系下包裹抓取位姿数目
    STC_GRASP_ROBOT_CAP_INFO*          pstRobot_pkg_pos;                                //机器人坐标系下包裹抓取位姿信息, n = robot_pkg_pos_num, 数据量为robot_pkg_pos_num * sizeof(STC_GRASP_ROBOT_CAP_INFO)
    STC_GRASP_ROBOT_CAP_INFO*          pstNo_cap_pos;                                   //机器人坐标系下包裹不可抓取位姿信息,包裹不可抓取位姿信息数组大小动态变动，实际大小由no_cap_pos_num具体定
	STC_GRASP_CAM_CAP_POS_INFO*        pstCamera_pkg_pos;                               //相机坐标系下包裹抓取位姿信息,m = camera_pkg_pos_num,数据量为camera_pkg_pos_num * sizeof(STC_GRASP_CAM_CAP_POS_INFO)
}STC_GRASP_INFO;

typedef struct _STC_3DPOINT_32_
{
    int nX;
    int nY;
    int nZ;
}STC_3DPOINT_32;

#endif //_MV_STA_DEFINE_H_
