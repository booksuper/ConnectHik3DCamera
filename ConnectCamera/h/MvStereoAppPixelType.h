/***************************************************************************************************
*
* ��Ȩ��Ϣ����Ȩ���� (c) 2019, ���ݺ��������˼������޹�˾, ��������Ȩ��
*
* �ļ����ƣ�MvStereoAppPixelType.h
* ժ    Ҫ: �������SDK�����ظ�ʽ����
*
* ��ǰ�汾��2.1.0
* ��    ��: �����Ӿ�SDK�Ŷ�
* ��    �ڣ�2019.12.1
* ��    ע���½�
****************************************************************************************************/

#ifndef _MV_STEREOAPP_PIXEL_TYPE_H_
#define _MV_STEREOAPP_PIXEL_TYPE_H_

/************************************************************************/
/*     GigE Vision (2.0.03) PIXEL FORMATS                               */
/************************************************************************/

// Indicate if pixel is monochrome or RGB
#define MV_GVSP_PIX_MONO                                0x01000000
#define MV_GVSP_PIX_RGB                                 0x02000000 // deprecated in version 1.1
#define MV_GVSP_PIX_COLOR                               0x02000000
#define MV_GVSP_PIX_CUSTOM                              0x80000000
#define MV_GVSP_PIX_COLOR_MASK                          0xFF000000

// Indicate effective number of bits occupied by the pixel (including padding).
// This can be used to compute amount of memory required to store an image.
#define MV_PIXEL_BIT_COUNT(n)                           ((n) << 16)

#define MV_GVSP_PIX_EFFECTIVE_PIXEL_SIZE_MASK           0x00FF0000
#define MV_GVSP_PIX_EFFECTIVE_PIXEL_SIZE_SHIFT          16

// Pixel ID: lower 16-bit of the pixel formats
#define MV_GVSP_PIX_ID_MASK                             0x0000FFFF
#define MV_GVSP_PIX_COUNT                               0x46 // next Pixel ID available


enum MvStereoAppGvspPixelType
{
    // Undefined pixel type
    STC_PixelType_Gvsp_Undefined                =   0xFFFFFFFF, 

    // Mono buffer format defines
    STC_PixelType_Gvsp_Mono1p                   =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(1) | 0x0037),
    STC_PixelType_Gvsp_Mono2p                   =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(2) | 0x0038),
    STC_PixelType_Gvsp_Mono4p                   =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(4) | 0x0039),
    STC_PixelType_Gvsp_Mono8                    =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(8) | 0x0001),
    STC_PixelType_Gvsp_Mono8_Signed             =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(8)  | 0x0002),
    STC_PixelType_Gvsp_Mono10                   =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0003),
    STC_PixelType_Gvsp_Mono10_Packed            =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x0004),
    STC_PixelType_Gvsp_Mono12                   =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0005),
    STC_PixelType_Gvsp_Mono12_Packed            =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x0006),
    STC_PixelType_Gvsp_Mono14                   =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0025),
    STC_PixelType_Gvsp_Mono16                   =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0007),

    // Bayer buffer format defines 
    STC_PixelType_Gvsp_BayerGR8                 =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(8) | 0x0008),
    STC_PixelType_Gvsp_BayerRG8                 =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(8) | 0x0009),
    STC_PixelType_Gvsp_BayerGB8                 =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(8) | 0x000A),
    STC_PixelType_Gvsp_BayerBG8                 =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(8) | 0x000B),
    STC_PixelType_Gvsp_BayerGR10                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x000C),
    STC_PixelType_Gvsp_BayerRG10                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x000D),
    STC_PixelType_Gvsp_BayerGB10                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x000E),
    STC_PixelType_Gvsp_BayerBG10                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x000F),
    STC_PixelType_Gvsp_BayerGR12                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0010),
    STC_PixelType_Gvsp_BayerRG12                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0011),
    STC_PixelType_Gvsp_BayerGB12                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0012),
    STC_PixelType_Gvsp_BayerBG12                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0013),
    STC_PixelType_Gvsp_BayerGR10_Packed         =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x0026),
    STC_PixelType_Gvsp_BayerRG10_Packed         =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x0027),
    STC_PixelType_Gvsp_BayerGB10_Packed         =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x0028),
    STC_PixelType_Gvsp_BayerBG10_Packed         =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x0029),
    STC_PixelType_Gvsp_BayerGR12_Packed         =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x002A),
    STC_PixelType_Gvsp_BayerRG12_Packed         =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x002B),
    STC_PixelType_Gvsp_BayerGB12_Packed         =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x002C),
    STC_PixelType_Gvsp_BayerBG12_Packed         =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(12) | 0x002D),
    STC_PixelType_Gvsp_BayerGR16                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x002E),
    STC_PixelType_Gvsp_BayerRG16                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x002F),
    STC_PixelType_Gvsp_BayerGB16                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0030),
    STC_PixelType_Gvsp_BayerBG16                =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x0031),

    // RGB Packed buffer format defines 
    STC_PixelType_Gvsp_RGB8_Packed              =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(24) | 0x0014),
    STC_PixelType_Gvsp_BGR8_Packed              =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(24) | 0x0015),
    STC_PixelType_Gvsp_RGBA8_Packed             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(32) | 0x0016),
    STC_PixelType_Gvsp_BGRA8_Packed             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(32) | 0x0017),
    STC_PixelType_Gvsp_RGB10_Packed             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(48) | 0x0018),
    STC_PixelType_Gvsp_BGR10_Packed             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(48) | 0x0019),
    STC_PixelType_Gvsp_RGB12_Packed             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(48) | 0x001A),
    STC_PixelType_Gvsp_BGR12_Packed             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(48) | 0x001B),
    STC_PixelType_Gvsp_RGB16_Packed             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(48) | 0x0033),
    STC_PixelType_Gvsp_RGB10V1_Packed           =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(32) | 0x001C),
    STC_PixelType_Gvsp_RGB10V2_Packed           =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(32) | 0x001D),
    STC_PixelType_Gvsp_RGB12V1_Packed           =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(36) | 0X0034),
    STC_PixelType_Gvsp_RGB565_Packed            =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0x0035),
    STC_PixelType_Gvsp_BGR565_Packed            =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0X0036),

    // YUV Packed buffer format defines 
    STC_PixelType_Gvsp_YUV411_Packed            =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(12) | 0x001E),
    STC_PixelType_Gvsp_YUV422_Packed            =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0x001F),
    STC_PixelType_Gvsp_YUV422_YUYV_Packed       =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0x0032),
    STC_PixelType_Gvsp_YUV444_Packed            =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(24) | 0x0020),
    STC_PixelType_Gvsp_YCBCR8_CBYCR             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(24) | 0x003A),
    STC_PixelType_Gvsp_YCBCR422_8               =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0x003B),
    STC_PixelType_Gvsp_YCBCR422_8_CBYCRY        =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0x0043),
    STC_PixelType_Gvsp_YCBCR411_8_CBYYCRYY      =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(12) | 0x003C),
    STC_PixelType_Gvsp_YCBCR601_8_CBYCR         =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(24) | 0x003D),
    STC_PixelType_Gvsp_YCBCR601_422_8           =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0x003E),
    STC_PixelType_Gvsp_YCBCR601_422_8_CBYCRY    =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0x0044),
    STC_PixelType_Gvsp_YCBCR601_411_8_CBYYCRYY  =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(12) | 0x003F),
    STC_PixelType_Gvsp_YCBCR709_8_CBYCR         =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(24) | 0x0040),
    STC_PixelType_Gvsp_YCBCR709_422_8           =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0x0041),
    STC_PixelType_Gvsp_YCBCR709_422_8_CBYCRY    =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(16) | 0x0045),
    STC_PixelType_Gvsp_YCBCR709_411_8_CBYYCRYY  =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(12) | 0x0042),

    // RGB Planar buffer format defines 
    STC_PixelType_Gvsp_RGB8_Planar              =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(24) | 0x0021),
    STC_PixelType_Gvsp_RGB10_Planar             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(48) | 0x0022),
    STC_PixelType_Gvsp_RGB12_Planar             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(48) | 0x0023),
    STC_PixelType_Gvsp_RGB16_Planar             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(48) | 0x0024),

    // �Զ����ͼƬ��ʽ
    STC_PixelType_Gvsp_Jpeg                     =   (MV_GVSP_PIX_CUSTOM | MV_PIXEL_BIT_COUNT(24) | 0x0001),

    STC_PixelType_Gvsp_Coord3D_ABC32f           =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(96) | 0x00C0),//0x026000C0
    STC_PixelType_Gvsp_Coord3D_ABC32f_Planar    =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(96) | 0x00C1),//0x026000C1

    // ��ֵ����������ο�STC_PixelType_Gvsp_Coord3D_AC32f_64; the value is discarded
    STC_PixelType_Gvsp_Coord3D_AC32f            =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(40) | 0x00C2),
    // ��ֵ������; the value is discarded    (�ѷ���Chunkdata)
    STC_PixelType_Gvsp_COORD3D_DEPTH_PLUS_MASK  =   (MV_GVSP_PIX_CUSTOM | MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(28) | 0x0001),

    STC_PixelType_Gvsp_Coord3D_ABC32            =   (MV_GVSP_PIX_CUSTOM | MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(96) | 0x3001),//0x82603001
    STC_PixelType_Gvsp_Coord3D_AB32f            =   (MV_GVSP_PIX_CUSTOM | MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(64) | 0x3002),//0x82403002
    STC_PixelType_Gvsp_Coord3D_AB32             =   (MV_GVSP_PIX_CUSTOM | MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(64) | 0x3003),//0x82403003
    STC_PixelType_Gvsp_Coord3D_AC32f_64         =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(64) | 0x00C2),//0x024000C2
    STC_PixelType_Gvsp_Coord3D_AC32f_Planar     =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(64) | 0x00C3),//0x024000C3
    STC_PixelType_Gvsp_Coord3D_AC32             =   (MV_GVSP_PIX_CUSTOM | MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(64) | 0x3004),//0x82403004
    STC_PixelType_Gvsp_Coord3D_A32f             =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(32) | 0x00BD),//0x012000BD
    STC_PixelType_Gvsp_Coord3D_A32              =   (MV_GVSP_PIX_CUSTOM | MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(32) | 0x3005),//0x81203005
    STC_PixelType_Gvsp_Coord3D_C32f             =   (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(32) | 0x00BF),//0x012000BF
    STC_PixelType_Gvsp_Coord3D_C32              =   (MV_GVSP_PIX_CUSTOM | MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(32) | 0x3006),//0x81203006


    STC_PixelType_Gvsp_Coord3D_ABC16            =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(48) | 0x00B9),//0x023000B9

    STC_PixelType_Gvsp_Coord3D_C16              =    (MV_GVSP_PIX_MONO | MV_PIXEL_BIT_COUNT(16) | 0x00B8),//0x011000B8 

    STC_PixelType_Gvsp_Coord3D_AC16             =   (MV_GVSP_PIX_COLOR | MV_PIXEL_BIT_COUNT(32) | 0x00BB),//0x022000BB

    //RGBD���ظ�ʽ
    STC_PixelType_Gvsp_Rgbd_C16                 =  0x82283007 
};



//��ƽ̨����
//Cross Platform Definition
#ifdef WIN32
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif


#endif /* _MV_STEREOAPP_PIXEL_TYPE_H_ */
