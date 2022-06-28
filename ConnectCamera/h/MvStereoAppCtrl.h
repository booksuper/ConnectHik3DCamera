/***************************************************************************************************
*
* 版权信息：版权所有 (c) 2019, 杭州海康机器人技术有限公司, 保留所有权利
*
* 文件名称：MvStereoAppCtrl.h
* 摘    要: 立体相机SDK，接口定义
*
* 当前版本：2.1.0
* 作    者: 机器视觉SDK团队
* 日    期：2019.12.1
* 备    注：新建
****************************************************************************************************/

#ifndef _MV_STEREOAPP_CTRL_H_
#define _MV_STEREOAPP_CTRL_H_

#include "MvStereoAppDefine.h"

/**
*  @brief  动态库导入导出定义
*  @brief  Import and export definition of the dynamic library 
*/
#ifndef MV_STA_API

    #if (defined (_WIN32) || defined(WIN64))
        #if defined(MV_STEREOAPPCTRL_EXPORTS)
            #define MV_STA_API __declspec(dllexport)
        #else
            #define MV_STA_API __declspec(dllimport)
        #endif
    #else
        #ifndef __stdcall
            #define __stdcall
        #endif

        #ifndef MV_STA_API
            #define  MV_STA_API
        #endif
    #endif

#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/************************************************************************
 *  @fn     MV_STA_GetSDKVersion()
 *  @brief  获取SDK版本号
 *  @param  
 *  @return 始终返回4字节版本号 |主    |次    |修正  |  测试|
                                 8bits  8bits  8bits  8bits 
                                 
 *  @fn     MV_STA_GetSDKVersion()
 *  @brief  Get SDK Version
 *  @param  
 *  @return Always return 4 Bytes of version number |Main    |Sub    |Rev  |  Test|
                                                     8bits  8bits  8bits  8bits 
 ************************************************************************/
MV_STA_API unsigned int __stdcall MV_STA_GetSDKVersion();

/************************************************************************
 *  @fn     MV_STA_GetMvCameraSDKVersion()
 *  @brief  获取工业相机SDK版本号
 *  @param  
 *  @return 始终返回4字节版本号 |主    |次    |修正  |  测试|
                                 8bits  8bits  8bits  8bits 
                                 
 *  @fn     MV_STA_GetMvCameraSDKVersion()
 *  @brief  Get SDK MvCamera Version
 *  @param  
 *  @return Always return 4 Bytes of version number |Main    |Sub    |Rev  |  Test|
                                                     8bits  8bits  8bits  8bits 
 ************************************************************************/
MV_STA_API unsigned int __stdcall MV_STA_GetMvCameraSDKVersion();

/************************************************************************
 *  @fn     MV_STA_EnumStereoCam()
 *  @brief  枚举立体相机(返回网络中3D立体相机）
 *  @param  pstCamList                 [OUT]          设备列表
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_EnumStereoCam()
 *  @brief  enum stereo camera device
 *  @param  pstCamList                 [OUT]          device list
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_EnumStereoCam(IN OUT MV_STEREOCAM_NET_INFO_LIST* pstCamList);

/************************************************************************
 *  @fn     MV_STA_EnumStereoCamEx()
 *  @brief  枚举设备 (返回网络中所有相机）
 *  @param  nTLayerType                [IN]           枚举传输层,例如: MV_STA_GIGE_DEVICE | MV_STA_USB_DEVICE
 *  @param  pstCamList                 [OUT]          设备列表
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_EnumStereoCamEx()
 *  @brief  enum camera device
 *  @param  nTLayerType                 [IN]          Enumerate TLs,e.g.: MV_STA_GIGE_DEVICE | MV_STA_USB_DEVICE
 *  @param  pstCamList                  [OUT]         device list
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_EnumStereoCamEx(IN unsigned int nTLayerType, IN OUT MV_STA_DEVICE_INFO_LIST* pstCamList);


/************************************************************************
*  @fn     MV_STA_CreateHandleByCameraInfo()
*  @brief  通过设备信息创建句柄
*  @param  handle                 [OUT]          句柄地址
*  @param  pDeviceInfo            [IN]           设备信息
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_CreateHandleByCameraInfo()
*  @brief  create handle by serial number
*  @param  handle                 [OUT]          handle address
*  @param  pDeviceInfo            [IN]           Device Info
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_CreateHandleByCameraInfo(IN OUT void ** handle, IN MV_STEREOCAM_NET_INFO*  pDeviceInfo);


/************************************************************************
 *  @fn     MV_STA_CreateHandleBySerialNumber()
 *  @brief  通过序列号创建句柄
 *  @param  handle                 [OUT]          句柄地址
 *  @param  chSerialNumber         [IN]           序列号
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 

 *  @fn     MV_STA_CreateHandleBySerialNumber()
 *  @brief  create handle by serial number
 *  @param  handle                 [OUT]          handle address
 *  @param  chSerialNumber         [IN]           serial number
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_CreateHandleBySerialNumber(IN OUT void ** handle, IN const char* chSerialNumber);


/************************************************************************
 *  @fn     MV_STA_CreateHandleByMacAddr()
 *  @brief  通过Mac地址创建句柄
 *  @param  handle                 [IN]          句柄地址
 *  @param  nMacHigh               [IN]          MAC地址高两个字节
 *  @param  nMacLow                [IN]          MAC地址低四个字节
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_CreateHandleByMacAddr()
 *  @brief  create handle by serial device mac
 *  @param  handle                 [OUT]          handle address
 *  @param  nMacHigh               [IN]          MAC high 2 byte
 *  @param  nMacLow                [IN]          MAC low 4 byte
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_CreateHandleByMacAddr(IN OUT void** handle,
                                                      IN unsigned int nMacHigh,
                                                      IN unsigned int nMacLow);

/************************************************************************
 *  @fn     MV_STA_OpenDevice()
 *  @brief  打开设备
 *  @param  handle                 [IN]          句柄地址
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_OpenDevice()
 *  @brief  open device
 *  @param  handle                 [OUT]          handle address
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_OpenDevice(IN void* handle);

/***********************************************************************
 *  @fn         MV_STA_RegisterDataCallBack()
 *  @brief      注册图像数据回调
 *  @param       handle                 [IN]          句柄
 *  @param       cbOutput               [IN]          回调函数指针
 *  @param       pUser                  [IN]          用户自定义变量
 *  @return 成功，返回MV_STA_OK；错误，返回错误码

 *  @fn         MV_STA_RegisterDataCallBack()
 *  @brief      register image data callback
 *  @param       handle                 [IN]          Handle
 *  @param       cbOutput               [IN]          Callback function pointer
 *  @param       pUser                  [IN]          User defined variable
 *  @return      Success, return MV_STA_OK. Failure, return error code
***********************************************************************/
MV_STA_API int __stdcall MV_STA_RegisterDataCallBack(IN void* handle, IN STC_DataSetCallBack cbOutput, IN void* pUser);

/************************************************************************
 *  @fn     MV_STA_RegisterExceptionCallBack()
 *  @brief  注册异常消息回调，在打开设备之后调用
 *  @param  handle：设备句柄
 *  @param  cbException       [IN]      异常回调函数指针
 *  @param  pUser             [IN]      用户自定义变量
 *  @return 见返回错误码

 *  @fn     MV_STA_RegisterExceptionCallBack()
 *  @brief  Register Exception Message CallBack, call after open device
 *  @param  handle: Device handle
 *  @param  cbException       [IN]       Exception Message CallBack Function Pointer
 *  @param  pUser             [IN]       User defined variable
 *  @return Refer to error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_RegisterExceptionCallBack(IN void* handle, IN STC_ExceptionCallBack cbException, IN void* pUser);

/***********************************************************************
 *  @fn         MV_STA_Start()
 *  @brief      开始取流
 *  @param      handle                 [IN]          句柄
 *  @return     成功，返回MV_STA_OK；错误，返回错误码
 
 *  @fn         MV_STA_Start()
 *  @brief      Start Grabbing
 *  @param      handle                 [IN]          Handle
 *  @return     Success, return MV_STA_OK. Failure, return error code
 ***********************************************************************/
MV_STA_API int __stdcall MV_STA_Start(IN void* handle);

/***********************************************************************
 *  @fn         MV_STA_Stop()
 *  @brief      停止取流
 *  @param       handle                 [IN]          句柄
 *  @return 成功，返回MV_STA_OK；错误，返回错误码
 
 *  @fn         MV_STA_Stop()
 *  @brief      Stop Grabbing
 *  @param      handle                 [IN]          Handle
 *  @return     Success, return MV_STA_OK. Failure, return error code
 ***********************************************************************/
MV_STA_API int __stdcall MV_STA_Stop(IN void* handle);

/************************************************************************
 *  @fn     MV_STA_DestroyHandle()
 *  @brief  销毁设备句柄
 *  @param  handle                 [IN]          句柄
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 

 *  @fn     MV_STA_DestroyHandle()
 *  @brief  Destroy Device Handle
 *  @param  handle                 [IN]          Handle
 *  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_DestroyHandle(IN void * handle);


/************************************************************************
 *  @fn     MV_STA_ReceiveDataTimeout()
 *  @brief  轮询方式获取数据集
 *  @param  handle                 [IN]          句柄地址
 *  @param  pDataSet               [IN]          数据集指针
 *  @param  nTimeOut               [IN]          超时时间
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_ReceiveDataTimeout()
 *  @brief  recv data set
 *  @param  handle                 [IN]          handle address
 *  @param  pDataSet               [IN]          data set pointer
 *  @param  nTimeOut               [IN]          timeout value
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_ReceiveDataTimeout(IN void* handle, IN OUT STC_DataSet* pDataSet, IN unsigned int nTimeOut);

/************************************************************************
 *  @fn     MV_STA_DestroyData()
 *  @brief  销毁数据集 （和MV_STA_ReceiveDataTimeout 配套使用，在注册结果回调时，不需要调用此函数）
 *  @param  DataSet                [IN]          数据集
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_DestroyData()
 *  @brief  destroy data set
 *  @param  DataSet                [IN]          data set
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_DestroyData(IN STC_DataSet DataSet);


/************************************************************************
 *  @fn     MV_STA_DataSetCount()
 *  @brief  获取数据集中的分类数据个数
 *  @param  DataSet                 [IN]          数据集
 *  @return 成功，返回数据个数；错误，返回0 
 
 *  @fn     MV_STA_DataSetCount()
 *  @brief  get the count of data set
 *  @param  DataSet                 [IN]          data set
 *  @return Success, return data count. Failure, return 0
 ************************************************************************/
MV_STA_API unsigned int __stdcall MV_STA_DataSetCount(IN STC_DataSet DataSet);

/************************************************************************
 *  @fn     MV_STA_DataSetAt()
 *  @brief  根据序号获取数据对象
 *  @param  DataSet                 [OUT]          数据集
 *  @param  nIndex                  [IN]           数据集中的序号
 *  @return 成功，返回子数据对象指针；错误，返回NULL 
 
 *  @fn     MV_STA_DataSetAt()
 *  @brief  get data object by index
 *  @param  DataSet                 [OUT]          data set
 *  @param  nIndex                  [IN]           index in data set
 *  @return Success, return obeject point. Failure, return NULL
 ************************************************************************/
MV_STA_API STC_Object  __stdcall MV_STA_DataSetAt(IN STC_DataSet DataSet, IN unsigned int nIndex);

/************************************************************************
 *  @fn     MV_STA_DataMsgType()
 *  @brief  根据对象获取信息类型
 *  @param  DataObject                 [IN]           数据对象
 *  @return 成功，返回数据对象类型；错误，返回STC_DATA_MSG_TYPE_UNKNOWN
 
 *  @fn     MV_STA_DataMsgType()
 *  @brief   Get the type of message
 *  @param  DataObject                 [IN]           data object
 *  @return Success, return object type. Failure, return  STC_DATA_MSG_TYPE_UNKNOWN
 ************************************************************************/
MV_STA_API unsigned int __stdcall MV_STA_DataMsgType(IN STC_Object DataObject);

/************************************************************************
 *  @fn     MV_STA_GetDeviceFrameID()
 *  @brief  获取相机的帧号（非图像帧号，实为帧统计值）
 *  @param  DataObject                 [IN]           数据对象
 *  @param  pnImageID                  [OUT]          帧号
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 *..@remark 仅线激光相机MV-DL2040-04B-H 固件V1.1.0之后支持
 
 *  @fn     MV_STA_GetDeviceFrameID()
 *  @brief   Get camera frameID(not image frameID)
 *  @param  DataObject                 [IN]           data object
 *  @param  pnImageID                  [Out]          freameID
 *  @return Success, return MV_STA_OK. Failure, return error code
 *  @remark only Line laser camera MV-DL2040-04B-H,  firmwareVersion V1.1.0 or new support
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_GetDeviceFrameID( IN STC_Object DataObject, IN OUT unsigned int * pnImageID);

/**********根据信息类型，获取详细数据**************/
// 相机出的原始图，Mono8、Depth16、PointCloud16等，对应类型 STC_DATA_MSG_TYPE_IMG_RAW时可以调用此函数
/************************************************************************
 *  @fn     MV_STA_GetImage()
 *  @brief  获取图像信息
 *  @param  DataObject                 [IN]          数据对象
 *  @param  pImg                       [IN OUT]      图像数据
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_GetImage()
 *  @brief  get image info
 *  @param  DataObject                 [IN]          data object
 *  @param  pImg                       [IN OUT]      image data
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_GetImage(IN STC_Object DataObject, IN OUT STC_DATA_IMAGE* pImg);


/************************************************************************
*  @fn     MV_STA_GetProfileCount()
*  @brief   获取3D轮廓仪深度图高度       对应类型 STC_3D_Profile_Count时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnProfileCount            [IN OUT]        行数
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetProfileCount()
*  @brief  getProfile Count
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileCount             [IN OUT]       Profile count
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetProfileCount(IN STC_Object DataObject, IN OUT unsigned int * pnProfileCount);

/************************************************************************
*  @fn     MV_STA_GetProfileLinePntNum()
*  @brief   获取3D轮廓仪深度图宽度      对应类型 STC_3D_Profile_LinePntNum时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnProfileLineNum           [IN OUT]      行点数
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetProfileLinePntNum()
*  @brief  get Profile Line Pnt Num
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileLineNum           [IN OUT]       line point count
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetProfileLinePntNum( IN STC_Object DataObject, IN OUT unsigned int * pnProfileLineNum);

/************************************************************************
*  @fn     MV_STA_GetProfileIntensity()
*  @brief   获取3D轮廓仪 亮度图         对应类型 STC_3D_Profile_Intensity时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnProfileIntensity         [IN OUT]      亮度图
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetProfileIntensity()
*  @brief  get Intensity
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileIntensity         [IN OUT]       Intensity
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetProfileIntensity(IN STC_Object DataObject, IN OUT STC_PROFILE_INTENSITY * pnProfileIntensity);

/************************************************************************
*  @fn     MV_STA_GetProfileThickness()
*  @brief   获取3D轮廓仪 宽度图        对应类型 STC_3D_Profile_Thickness时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnProfileThickness         [IN OUT]      宽度图
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetProfileThickness()
*  @brief  get Thickness
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileThickness         [IN OUT]       ProfileThickness
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_GetProfileThickness( IN STC_Object DataObject, IN OUT STC_PROFILE_THICKNESS * pnProfileThickness);

/************************************************************************
*  @fn     MV_STA_GetProfileRunDir()
*  @brief   获取3D轮廓仪 前进方向     对应类型 STC_3D_Profile_RunDir时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnProfileRunDir           [IN OUT]      前进方向
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetProfileRunDir()
*  @brief  get Profile Run Dir
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileRunDir            [IN OUT]       Profile Run Dir
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetProfileRunDir(IN STC_Object DataObject, IN OUT STC_PROFILE_RUNDIR * pnProfileRunDir);

/************************************************************************
*  @fn     MV_STA_GetProfileFirstFrmID()
*  @brief   获取3D轮廓仪 第一个轮廓的帧号     对应类型 STC_3D_Profile_FirstFrmID时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnProfileFirstFrmID           [IN OUT]      第一个轮廓的帧号
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetProfileFirstFrmID()
*  @brief  Profile First Frm ID
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileFirstFrmID        [IN OUT]       Profile First Frm ID
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetProfileFirstFrmID( IN STC_Object DataObject, IN OUT unsigned int  * pnProfileFirstFrmID);

/************************************************************************
*  @fn     MV_STA_GetProfileCoordScale()
*  @brief   获取3D轮廓仪 采样间隔        对应类型 STC_3D_Profile_CoordScale时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnProfileCoordScale       [IN OUT]     采样间隔
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetProfileCoordScale()
*  @brief  Get Profile  Coord Scale
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileCoordScale        [IN OUT]       Profile  Coord Scale
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetProfileCoordScale( IN STC_Object DataObject, IN OUT STC_PROFILE_COORDSCALE  * pnProfileCoordScale);

/************************************************************************
*  @fn     MV_STA_GetProfileCoordOffset()
*  @brief   获取3D轮廓仪 采样起始点的偏移     对应类型 STC_3D_Profile_CoordOffset时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnProfileCoordOffset       [IN OUT]      采样起始点偏移
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetProfileCoordOffset()
*  @brief  Get Profile  Coord Offset
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileCoordOffset       [IN OUT]       Profile  Coord Offset
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetProfileCoordOffset( IN STC_Object DataObject, IN OUT STC_PROFILE_COORDOFFSET  * pnProfileCoordOffset);

/************************************************************************
*  @fn     MV_STA_GetDwsVolumeInfo()
*  @brief   获取线激光相机的体积数据      对应类型 STC_DATA_MSG_TYPE_DWS_VOLUME时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pVolumInfo                 [IN OUT]      体积数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetDwsVolumeInfo()
*  @brief  get volum  info
*  @param  DataObject                 [IN]          data object
*  @param  pVolumInfo                 [IN OUT]      volum data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetDwsVolumeInfo(IN STC_Object DataObject, IN OUT STC_DWS_VOLUME_INFO* pVolumInfo);


/************************************************************************
*  @fn     MV_STA_GetStereoVolumeInfo()
*  @brief   获取双目相机的体积数据         对应类型 STC_DATA_MSG_TYPE_STEREO_VOLUME 时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pVolumInfo                 [IN OUT]      体积数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetStereoVolumeInfo()
*  @brief  get volum  info
*  @param  DataObject                 [IN]          data object
*  @param  pVolumInfo                 [IN OUT]      volum data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetStereoVolumeInfo(IN STC_Object DataObject, IN OUT STC_STEREO_VOLUME_INFO* pVolumInfo);


/************************************************************************
*  @fn     MV_STA_NormalizedDepthImage()
*  @brief    把多种深度图格式统一成Mono16      [当前仅支持 STC_PixelType_Gvsp_Coord3D_C32 STC_PixelType_Gvsp_Coord3D_C16  转 STC_PixelType_Gvsp_Mono16]
*  @param  handle                 [IN]          句柄地址
*  @param  pstImage               [IN OUT]      图像数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_NormalizedDepthImage()
*  @brief   Image conversion to Mono16 format 
*  @param  handle                 [IN]          handle address
*  @param   pstImage               [IN OUT]     Image Data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_NormalizedDepthImage(IN void* handle, IN OUT STC_NORMALIZE_IMAGE* pstImage);

/************************************************************************
*  @fn     MV_STA_NormalizedPointCloudImage()
*  @brief   把多种点云图转换为 ABC16 或 ABC32)         [当前仅支持 STC_PixelType_Gvsp_Coord3D_ABC32f_Planar  STC_PixelType_Gvsp_Coord3D_ABC32]
*  @param  handle                 [IN]          句柄地址
*  @param  pstImage               [IN OUT]      图像数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_NormalizedPointCloudImage()
*  @brief   Converting multiple point clouds to ABC16 or ABC32
*  @param  handle                 [IN]          handle address
*  @param   pstImage              [IN OUT]     Image Data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_NormalizedPointCloudImage(IN void* handle, IN OUT STC_NORMALIZE_IMAGE* pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveTiff()
 *  @brief  保存16位深度图为TIFF格式      [当前仅支持STC_PixelType_Gvsp_Mono16 保存为TIFF]
 *  @param  handle                 [IN]          句柄地址
 *  @param  pstImage               [IN]          深度图数据
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_SaveTiff()
 *  @brief  save Mono16 depth image to tiff
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          depth imagebuf 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveTiff(IN void* handle, IN STC_IMG_SAVE_MONO16_TO_TIFF_PARAM* pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveJpg()
 *  @brief  保存16位深度图为jpg格式      [当前仅支持STC_PixelType_Gvsp_Mono16 保存为jpg]
 *  @param  handle                 [IN]          句柄地址
 *  @param  pstImage               [IN]          深度图数据
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_SaveJpg()
 *  @brief  save Mono16 depth image to jpg
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          depth imagebuf 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveJpg(IN void* handle, IN STC_IMG_SAVE_MONO16_TO_JPG_PARAM* pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveBmp()
 *  @brief  保存16位深度图为Bmp格式      [当前仅支持STC_PixelType_Gvsp_Mono16 保存为bmp]
 *  @param  handle                 [IN]          句柄地址
 *  @param  pstImage               [IN]          深度图数据
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_SaveBmp()
 *  @brief  save Mono16 depth image to bmp
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          depth imagebuf 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveBmp(IN void* handle, IN STC_IMG_SAVE_MONO16_TO_BMP_PARAM* pstImage);

/************************************************************************
 *  @fn     MV_STA_SavePly()
 *  @brief 保存ABC16 或 ABC32格式点云图为PLY格式
 *  @param  handle             [IN]          句柄地址
 *  @param  pstImage          [IN]           数据
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_SavePly()
 *  @brief  save ABC16 or ABC32 image to ply
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          data 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SavePly(IN void* handle,  IN OUT STC_IMG_SAVE_ABC16_TO_PLY_PARAM * pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveObj()
 *  @brief 保存ABC16 或 ABC32 格式点云图为Obj格式
 *  @param  handle             [IN]          句柄地址
 *  @param  pstImage           [IN]          数据
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_SaveObj()
 *  @brief  save ABC16 image to obj
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          data 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveObj(IN void* handle,  IN OUT STC_IMG_SAVE_ABC16_TO_OBJ_PARAM * pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveCsv()
 *  @brief 保存ABC16 或 ABC32格式点云图为csv格式
 *  @param  handle             [IN]          句柄地址
 *  @param  pstImage           [IN]          数据
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_SaveObj()
 *  @brief  save ABC16 image to csv
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          data 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveCsv(IN void* handle,  IN OUT STC_IMG_SAVE_ABC16_TO_CSV_PARAM * pstImage);

/************************************************************************
*  @fn     MV_STA_DisplayStandardDepthMap()
*  @brief  标准深度图渲染[MONO16]     [当前仅支持 STC_PixelType_Gvsp_Mono16 渲染]
*  @param  handle                 [IN]          句柄地址
*  @param  pstImage               [IN]          深度图数据
*  @param  pstDisplayExInfo       [IN]          渲染扩展信息
*  @param  hWnd                   [IN]          渲染窗口句柄
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_DisplayStandardDepthMap()
*  @brief   Display  STC_PixelType_Gvsp_Mono16
*  @param  handle                 [IN]          handle address
*  @param  pstImage               [IN]          Depth Map data 
*  @param  pstDisplayExInfo       [IN]          Ex Display Info
*  @param  hWnd                   [IN]          DisplayHandle
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_DisplayStandardDepthMap(IN void* handle,  IN STC_DATA_IMAGE * pstImage, STC_DEPTH_MAP_DISPLAY_EX *pstDisplayExInfo,  void * hWnd);

/************************************************************************
*  @fn     MV_STA_DisplayStandardPointCloud()
*  @brief  标准点云图渲染[ABC16,或ABC32]
*  @param  handle                 [IN]          句柄地址
*  @param  pstImage               [IN]          点云图数据
*  @param  hWnd                   [IN]          渲染窗口句柄
*  @param  nWndWidth              [IN]          渲染窗口宽度
*  @param  nWndHeight              [IN]         渲染窗口高度
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_DisplayStandardPointCloud()
*  @brief  display  standard point cloud image[ABC16 or ABC32]
*  @param  handle                 [IN]          handle address
*  @param  pstImage               [IN]          Point Cloud data 
*  @param  hWnd                   [IN]          DisplayHandle
*  @param  nWndWidth              [IN]          DisplayWindowWith
*  @param  nWndHeight              [IN]          DisplayWindowHight
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_DisplayStandardPointCloud(IN void* handle,  IN STC_DATA_IMAGE * pstImage, void * hWnd, int nWndWWith , int nWndHight);



/************************************************************************/
// 点云拼接【轮廓线，拼接成轮廓图】当前仅支持STC_PixelType_Gvsp_Coord3D_ABC16 拼接，具体接口调用顺序如下：
// 1. 注册拼接回调函数；
// 2. 设置拼接的帧数和步长；
// 3. 放入轮廓线数据；
// 4. 放入轮廓线数据达到帧数时，自动执行注册回调函数
/************************************************************************/ 

/***********************************************************************
*  @fn         MV_STA_RegisterPointCloudMosaicImageCallBack()
*  @brief      注册点云数据拼接回调
*  @param       handle                 [IN]          句柄
*  @param       cbOutputCallback       [IN]          回调函数指针
*  @param       pUser                  [IN]          用户自定义变量
*  @return 成功，返回MV_STA_OK；错误，返回错误码

*  @fn         MV_STA_RegisterPointCloudMosaicImageCallBack()
*  @brief      register PointCloud Mosaic callback
*  @param       handle                 [IN]          Handle
*  @param       cbOutputCallback       [IN]          Callback function pointer
*  @param       pUser                  [IN]          User defined variable
*  @return      Success, return MV_STA_OK. Failure, return error code
***********************************************************************/
MV_STA_API int __stdcall MV_STA_RegisterPointCloudMosaicImageCallBack(IN void* handle, STC_PointCloudCallback cbOutputCallback, void* pUser);

/************************************************************************
*  @fn     MV_STA_SetPointCloudMosaicConfigParam()
*  @brief  设置点云拼接参数
*  @param  handle                 [IN]          句柄地址
*  @param  pstConfigInfo          [IN]          点云图拼接参数
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_SetPointCloudMosaicConfigParam()
*  @brief  Set PointCloud Mosaic Config param
*  @param  handle                 [IN]          handle address
*  @param  pstConfigInfo          [IN]          config param
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_SetPointCloudMosaicConfigParam(IN void* handle,  IN STC_PointCloudMosaicConfigParam * pstConfigInfo);


/************************************************************************
*  @fn     MV_STA_PointCloudMosaicUpdateImage()
*  @brief  放入点云数据    （仅支持STC_PixelType_Gvsp_Coord3D_ABC16标准点云格式，如传入非标准点云格式，可能不报错，但获取不到轮廓数据，限制传入数据的宽度相同，长度为1）
*  @param  handle                 [IN]          句柄地址
*  @param  pstImage               [IN]          点云图数据
*  @param  nWidth                 [IN]          点云轮廓线宽度
*  @param  nImageSize             [IN]          点云图大小
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_PointCloudMosaicUpdateImage()
*  @brief  put  PointCloud to Algorithms library
*  @param  handle                 [IN]          handle address
*  @param  pstImage               [IN]          Point Cloud data 
*  @param  nWidth                 [IN]          Point Cloud Image Width
*  @param  nImageSize             [IN]          Point Cloud image Size
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_PointCloudMosaicUpdateImage(IN void* handle, IN void*pImageData, IN int nWidth, IN int nImageSize);

/************************************************************************
*  @fn     MV_STA_PointCloudMosaicUpdateImageEx()
*  @brief  放入点云数据    （支持STC_PixelType_Gvsp_Coord3D_ABC16和STC_PixelType_Gvsp_Coord3D_ABC32标准点云格式，，限制传入数据的宽度相同，长度为1）
*  @param  handle                 [IN]          句柄地址
*  @param  pstImage               [IN]          点云图数据
*  @param  nWidth                 [IN]          点云轮廓线宽度
*  @param  nImageSize             [IN]          点云图大小
*  @param  nFrameNum              [IN]          点云图帧号
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_PointCloudMosaicUpdateImageEx()
*  @brief  put  PointCloud to Algorithms library
*  @param  handle                 [IN]          handle address
*  @param  pstImage               [IN]          Point Cloud data 
*  @param  nWidth                 [IN]          Point Cloud Image Width
*  @param  nImageSize             [IN]          Point Cloud image Size
*  @param  nFrameNum              [IN]          Point Cloud Frame number
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_PointCloudMosaicUpdateImageEx(IN void* handle, IN void*pImageData, IN int nWidth, IN int nImageSize, IN int nFrameNum);

/************************************************************************
*  @fn     MV_STA_ReleasePointCloudData()
*  @brief  清空点云数据   
*  @param  handle                 [IN]          句柄地址
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_ReleasePointCloudData()
*  @brief  release PointCloud data
*  @param  handle                 [IN]          handle address
*  @return Success, return MV_STA_OK. Failure,  return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_ReleasePointCloudData(IN void* handle);

/************************************************************************
*  @fn     MV_STA_GetCenterCoordinate()
*  @brief   获取高帧率轮廓仪中心点坐标     对应类型 STC_3D_Profile_CenterCoordinate时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnCenterCoordinate         [IN OUT]      中心点坐标
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetCenterCoordinate()
*  @brief  Get Profile  Center Coordinate
*  @param  DataObject                 [IN]           data object
*  @param  pnCenterCoordinate       [IN OUT]       Profile  Center Coordinate
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetCenterCoordinate( IN STC_Object DataObject, IN OUT STC_CENTERCOORDINATE  * pnCenterCoordinate);

/************************************************************************
*  @fn     MV_STA_GetExtendImage()
*  @brief  获取chunkdata中扩展图像数据     对应类型 STC_3D_Profile_ExtendImg时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnExtendImage              [IN OUT]      扩展图像数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetExtendImage()
*  @brief  Getting extended image data in chunkdata  Corresponding type STC_3D_Profile_ExtendImg can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnExtendImage              [IN OUT]       extended image data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetExtendImage( IN STC_Object DataObject, IN OUT STC_EXTEND_IMAGE  * pnExtendImage);

/************************************************************************
*  @fn     MV_STA_GetPackageInfo()
*  @brief  获取chunkdata中包裹信息数据     对应类型 STC_3D_Profile_SingulatePkginfo时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnPackageInfo              [IN OUT]      包裹信息数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetPackageInfo()
*  @brief  Get package information data in chunkdata   Corresponding type STC_3D_Profile_SingulatePkginfo can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnPackageInfo              [IN OUT]       packageinfo data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetPackageInfo( IN STC_Object DataObject, IN OUT STC_PACKAGE_INFO  * pnPackageInfo);

/************************************************************************
*  @fn     MV_STA_GetInstanceSegInfo()
*  @brief  获取chunkdata中实体分割信息     对应类型 STC_3D_Profile_InstanceSegInfo 时可以调用此函数
*  @param  DataObject                     [IN]          数据对象
*  @param  pnInstanceSegInfo              [IN OUT]      实体分割数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetInstanceSegInfo()
*  @brief  Getting Instance Segmentation  data in chunkdata  Corresponding type STC_3D_Profile_InstanceSegInfo can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnInstanceSegInfo          [IN OUT]       Instance Segmentation  data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetInstanceSegInfo( IN STC_Object DataObject, IN OUT STC_INSTANCE_SEG_INFO  * pnInstanceSegInfo);

/************************************************************************
*  @fn     MV_STA_GetDetectObjInfo()
*  @brief  获取chunkdata中目标检测数据     对应类型 STC_3D_Profile_DetectInfo时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnDetectInfo              [IN OUT]      目标检测数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetDetectObjInfo()
*  @brief  Get detect information data in chunkdata   Corresponding type STC_3D_Profile_DetectInfo can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnDetectInfo               [IN OUT]       detectinfo data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetDetectObjInfo( IN STC_Object DataObject, IN OUT STC_DETECT_INFO  * pnDetectInfo);

/************************************************************************
*  @fn     MV_STA_GetTimeStampInfo()
*  @brief  获取chunkdata中时间戳数据     对应类型 STC_3D_Profile_TimeStamp时可以调用此函数
*  @param  DataObject                   [IN]          数据对象
*  @param  pnTimeStampInfo              [IN OUT]      时间戳数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetTimeStampInfo()
*  @brief  Get timestamp information data in chunkdata   Corresponding type STC_3D_Profile_TimeStamp can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnTimeStampInfo            [IN OUT]       timestamp data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetTimeStampInfo( IN STC_Object DataObject, IN OUT STC_TIME_STAMP_INFO  * pnTimeStampInfo);

/************************************************************************
*  @fn     MV_STA_GetGraspInfo()
*  @brief  获取chunkdata中抓取信息数据     对应类型 STC_3D_Profile_GraspInfo时可以调用此函数
*  @param  DataObject                 [IN]          数据对象
*  @param  pnGraspInfo                [IN OUT]      抓取信息数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_GetGraspInfo()
*  @brief  Get grasp information data in chunkdata   Corresponding type STC_3D_Profile_GraspInfo can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnGraspInfo               [IN OUT]       graspinfo data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetGraspInfo( IN STC_Object DataObject, IN OUT STC_GRASP_INFO  * pnGraspInfo);

/************************************************************************
*  @fn     MV_STA_DisplayRgbdMap()
*  @brief  RGBD图渲染  支持RGBD相机STC_PixelType_Gvsp_Rgbd_C16数据
*  @param  handle                 [IN]          句柄地址
*  @param  pstImage               [IN]          RGBD图数据
*  @param  pstDisplayExInfo       [IN]          渲染扩展信息
*  @param  hWnd                   [IN]          渲染窗口句柄
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_DisplayRgbdMap()                         
*  @brief  Rgbd image rendering  supports rgbd camera STC_PixelType_Gvsp_Rgbd_C16 data 
*  @param  handle                 [IN]          handle address
*  @param  pstImage               [IN]          RGBD Map data
*  @param  pstDisplayExInfo       [IN]          Ex Display Info
*  @param  hWnd                   [IN]          DisplayHandle
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_DisplayRgbdMap(IN void* handle,  IN STC_DATA_IMAGE * pstImage, STC_DEPTH_MAP_DISPLAY_EX *pstDisplayExInfo,  void * hWnd);

/************************************************************************/
// 深度图转点云图 【支持Mono16/C16/C32数据】，具体接口调用顺序如下：
// 1. 注册深度图转点云图回调函数，设置X/Y方向扩展系数；
// 2. 放入深度图数据；
// 3. 当有点云图数据输出时，自动执行注册回调函数
/************************************************************************/ 

/***********************************************************************
*  @fn          MV_STA_RegisterDepthToPointCloudCallBack()
*  @brief       注册深度图转点云图回调   支持Mono16/C16/C32数据
*  @param       handle                 [IN]          句柄
*  @param       cbOutputCallback       [IN]          回调函数指针
*  @param       pUser                  [IN]          用户自定义变量
*  @param       nXScale                [IN]          X方向扩展系数
*  @param       nYScale                [IN]          Y方向扩展系数
*  @return 成功，返回MV_STA_OK；错误，返回错误码

*  @fn         MV_STA_RegisterDepthToPointCloudCallBack()
*  @brief      register Depth to PointCloud callback  support Mono16/C16/C32 data
*  @param       handle                 [IN]          Handle
*  @param       cbOutputCallback       [IN]          Callback function pointer
*  @param       pUser                  [IN]          User defined variable
*  @param       nXScale                [IN]          X direction Expansion coefficient
*  @param       nYScale                [IN]          Y direction Expansion coefficient
*  @return      Success, return MV_STA_OK. Failure, return error code
***********************************************************************/
MV_STA_API int __stdcall MV_STA_RegisterDepthToPointCloudCallBack(IN void* handle, STC_PointCloudCallback cbOutputCallback, void* pUser, int nXScale, int nYScale);

/************************************************************************
*  @fn     MV_STA_DepthToPointCloudUpdateImage()
*  @brief  放入深度图数据  
*  @param  handle                 [IN]          句柄地址
*  @param  pstImage               [IN]          深度图数据
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_DepthToPointCloudUpdateImage()
*  @brief  put Depth Image to Algorithms library
*  @param  handle                 [IN]          handle address
*  @param  pstImage               [IN]          Depth Image data 
*  @return Success, return MV_STA_OK. Failure,  return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_DepthToPointCloudUpdateImage(IN void* handle, IN STC_DATA_IMAGE * pstImage);

#ifdef __cplusplus
}
#endif 

#endif //_MV_STA_CTRL_H_