/***************************************************************************************************
*
* 版权信息：版权所有 (c) 2019, 杭州海康机器人技术有限公司, 保留所有权利
*
* 文件名称：MvStereoAppCtrlEx.h
* 摘    要: 立体相机SDK，拓展接口定义
*
* 当前版本：2.1.0
* 作    者: 机器视觉SDK团队
* 日    期：2019.12.1
* 备    注：新建
****************************************************************************************************/

#ifndef _MV_STEREOCAM_CTRL_EX_H_
#define _MV_STEREOCAM_CTRL_EX_H_

#include "MvStereoAppCtrl.h"
#include "MvStereoAppDefineEx.h"


#ifdef __cplusplus
extern "C" {
#endif 


/************************************************************************
*  @fn         MV_STA_API int __stdcall MV_STA_CamIsAccessible(IN MV_STEREOCAM_NET_INFO* pstDevInfo, IN unsigned int nAccessMode)
*  @brief      判断相机的访问权限
*  @param      MV_STEREOCAM_NET_INFO* pstDevInfo                [IN]        相机信息
*  @param      unsigned int * nAccessMode                       [IN]        相机的访问权限      //Eg: MV_STA_ACCESS_Exclusive
*  @return    可达，返回true；不可达，返回false 

*  @fn         MV_STA_API int __stdcall MV_STA_CamIsAccessible(IN MV_STEREOCAM_NET_INFO* pstDevInfo, IN unsigned int nAccessMode)
*  @brief      Get camera's Access privileges
*  @param      MV_STEREOCAM_NET_INFO* pstDevInfo                [IN]        camera info 
*  @param       unsigned int * nAccessMode                      [IN]        camera's Access privileges    //Eg: MV_STA_ACCESS_Exclusive
*  @return     Success, return true. Failure, false
************************************************************************/    
MV_STA_API int __stdcall  MV_STA_CamIsAccessible(IN MV_STEREOCAM_NET_INFO* pstDevInfo, IN unsigned int nAccessMode);


/************************************************************************
*  @fn     MV_STA_GetDeviceInfo
*  @brief  获取设备信息
*  @param  handle                      [IN]            设备句柄
*  @param  pstDevInfo                  [IN][OUT]       返回给调用者有关相机设备信息结构体指针
*  @return 成功,返回MV_STA_OK,失败,返回错误码

*  @fn     MV_STA_GetDeviceInfo
*  @brief  Get device information
*  @param  handle                      [IN]            Device handle
*  @param  pstDevInfo                  [IN][OUT]       Structure pointer of device information
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetDeviceInfo(IN void * handle, IN OUT MV_STEREOCAM_NET_INFO* pstDevInfo);

 
/************************************************************************
*  @fn     MV_STA_GetDevicePropertyConfiguration
*  @brief  获取设备GIGE属性配置
*  @param  handle                      [IN]            设备句柄
*  @param  pData                       [IN][OUT]       返回给调用者有关相机设备信息结构体指针
*  @param  nDataSize                   [IN]            分配数据长度
*  @param  pnDataLen                   [IN][OUT]       实际返回数据的长度
*  @return 成功,返回MV_STA_OK,失败,返回错误码

*  @fn     MV_STA_GetDevicePropertyConfiguration
*  @brief  Get device GIGE Config information
*  @param  handle                      [IN]            Device handle
*  @param  pData                       [IN][OUT]       Structure pointer of device information
*  @param  nDataSize                   [IN]            Data Len
*  @param  pnDataLen                   [IN][OUT]       Real Date Len
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetDevicePropertyConfiguration(IN void * handle, IN OUT unsigned char* pData, IN unsigned int nDataSize, IN OUT unsigned int* pnDataLen);


/************************************************************************
*  @fn         MV_STA_API int __stdcall MV_STA_SetIntValue(IN void* handle,
IN const char* strKey,
IN int64_t nValue);
*  @brief      设置相机Integer型属性值
*  @param      void* handle                [IN]        相机句柄
*  @param      char* strKey                [IN]        属性键值，如获取宽度信息则为"Width"
*              const int64_t nValue        [IN]        想要设置的相机的属性值
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_API int __stdcall MV_STA_SetIntValue(IN void* handle,
IN const char* strKey,
IN int64_t nValue);
*  @brief      Set Camera Integer value
*  @param      void* handle                [IN]        Handle
*  @param      char* strKey                [IN]        Key value, for example, using "Width" to set width
*              const int64_t nValue        [IN]        Feature value to set
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_SetIntValue(IN void* handle, IN const char* strKey, IN int64_t nValue);

/************************************************************************
*  @fn         MV_STA_API int __stdcall MV_STA_GetIntValue(IN void* handle, IN const char* strKey, OUT MV_STA_INTVALUE *pIntValue);
*  @brief      获取Integer属性值
*  @param      void* handle                [IN]        相机句柄
*  @param      char* strKey                [IN]        属性键值，如获取宽度信息则为"Width"
*  @param      MV_STA_INTVALUE* pIntValue  [IN][OUT]   返回给调用者有关相机属性结构体指针
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_GetIntValue(IN void* handle, IN const char* strKey, OUT MV_STA_INTVALUE *pIntValue);
*  @brief      Get Integer value
*  @param      void* handle                [IN]        Handle
*  @param      char* strKey                [IN]        Key value, for example, using "Width" to get width
*  @param      MV_STA_INTVALUE* pIntValue  [IN][OUT]   Structure pointer of camera features
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_GetIntValue(IN void* handle, IN const char* strKey, IN OUT MV_STA_INTVALUE *pIntValue);

/************************************************************************
*  @fn         MV_STA_SetEnumValue(IN void* handle, IN const char* strKey, IN unsigned int nValue);
*  @brief      设置相机Enum型属性值
*  @param      void* handle                [IN]        相机句柄
*  @param      char* strKey                [IN]        属性键值，如获取像素格式信息则为"PixelFormat"
*              const unsigned int nValue   [IN]        想要设置的相机的属性值
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_SetEnumValue(IN void* handle, IN const char* strKey, IN unsigned int nValue);
*  @brief      Set Camera Enum value
*  @param      void* handle                [IN]        Handle
*  @param      char* strKey                [IN]        Key value, for example, using "PixelFormat" to set pixel format
*              const unsigned int nValue   [IN]        Feature value to set
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_SetEnumValue(IN void* handle, IN const char* strKey, IN unsigned int nValue);

/************************************************************************
*  @fn         MV_STA_SetEnumValueByString(IN void* handle, IN const char* strKey, IN const char* sValue);
*  @brief      设置相机Enum型属性值
*  @param      void* handle                [IN]        相机句柄
*  @param      char* strKey                [IN]        属性键值，如获取像素格式信息则为"PixelFormat"
*              char* sValue                [IN]        想要设置的相机的属性字符串
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_SetEnumValueByString(IN void* handle, IN const char* strKey, IN const char* sValue);
*  @brief      Set Camera Enum value
*  @param      void* handle                [IN]        Handle
*  @param      char* strKey                [IN]        Key value, for example, using "PixelFormat" to set pixel format
*              char* sValue                [IN]        Feature String to set
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_SetEnumValueByString(IN void* handle, IN const char* strKey, IN const char* sValue);

/************************************************************************
*  @fn         MV_STA_GetEnumValue(IN void* handle, IN const char* strKey, OUT MV_STA_ENUMVALUE *pEnumValue);
*  @brief      获取相机Enum属性值
*  @param      void* handle                   [IN]        相机句柄
*  @param      char* strKey                   [IN]        属性键值，如获取像素格式信息则为"PixelFormat"
*  @param      MV_STA_ENUMVALUE* pEnumValue [IN][OUT]   返回给调用者有关相机属性结构体指针
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_GetEnumValue(IN void* handle, IN const char* strKey, OUT MV_STA_ENUMVALUE *pEnumValue);
*  @brief      Get Camera Enum value
*  @param      void* handle                   [IN]        Handle
*  @param      char* strKey                   [IN]        Key value, for example, using "PixelFormat" to get pixel format
*  @param      MV_STA_ENUMVALUE* pEnumValue [IN][OUT]   Structure pointer of camera features
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_GetEnumValue(IN void* handle, IN const char* strKey, IN OUT MV_STA_ENUMVALUE *pEnumValue);

/************************************************************************
*  @fn         MV_STA_SetFloatValue(IN void* handle, IN const char* strKey, IN float fValue);
*  @brief      设置相机Float型属性值
*  @param      void* handle                [IN]        相机句柄
*  @param      char* strKey                [IN]        属性键值
*              float fValue                [IN]        想要设置的相机的属性值
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_SetFloatValue(IN void* handle, IN const char* strKey, IN float fValue);
*  @brief      Set Camera Float value
*  @param      void* handle                [IN]        Handle
*  @param      char* strKey                [IN]        Key value
*              float fValue                [IN]        Feature value to set
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_SetFloatValue(IN void* handle, IN const char* strKey, IN float fValue);

/************************************************************************
*  @fn         MV_STA_GetFloatValue(IN void* handle, IN const char* strKey, OUT MV_STA_FLOATVALUE *pFloatValue);
*  @brief      获取相机Float属性值
*  @param      void* handle                     [IN]        相机句柄
*  @param      char* strKey                     [IN]        属性键值
*  @param      MV_STA_FLOATVALUE *pFloatValue [IN][OUT]   返回给调用者有关相机属性结构体指针
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_GetFloatValue(IN void* handle, IN const char* strKey, OUT MV_STA_FLOATVALUE *pFloatValue);
*  @brief      Get Cmera Float value
*  @param      void* handle                     [IN]        Handle
*  @param      char* strKey                     [IN]        Key value
*  @param      MV_STA_FLOATVALUE *pFloatValue [IN][OUT]   Structure pointer of camera features
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_GetFloatValue(IN void* handle, IN const char* strKey, IN OUT MV_STA_FLOATVALUE *pFloatValue);

/************************************************************************
*  @fn         MV_STA_SetStringValue(IN void* handle, IN const char* strKey, IN const char * sValue);
*  @brief      设置相机String型属性值
*  @param      void* handle                  [IN]        相机句柄
*  @param      char* strKey                  [IN]        属性键值
*              char * sValue                 [IN]        想要设置的相机的属性值
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_SetStringValue(IN void* handle, IN const char* strKey, IN const char * sValue);
*  @brief      Set Camera String value
*  @param      void* handle                  [IN]        Handle
*  @param      char* strKey                  [IN]        Key value
*              char * sValue                 [IN]        Feature value to set
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_SetStringValue(IN void* handle, IN const char* strKey, IN const char * sValue);

/************************************************************************
*  @fn         MV_STA_GetStringValue(IN void* handle, IN const char* strKey, OUT MV_STA_STRINGVALUE *pStringValue);
*  @brief      获取相机String属性值
*  @param      void* handle                       [IN]        相机句柄
*  @param      char* strKey                       [IN]        属性键值
*  @param      MV_STA_CAM_GetStringValue [IN][OUT]   返回给调用者有关相机属性结构体指针
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_GetStringValue(IN void* handle, IN const char* strKey, OUT MV_STA_STRINGVALUE *pStringValue);
*  @brief      Get Camera String value
*  @param      void* handle                       [IN]        Handle
*  @param      char* strKey                       [IN]        Key value
*  @param      MV_STA_STRINGVALUE *pStringValue [IN][OUT]   Structure pointer of camera features
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_GetStringValue(IN void* handle, IN const char* strKey, IN OUT MV_STA_STRINGVALUE *pStringValue);

/************************************************************************
*  @fn         MV_STA_SetBoolValue(IN void* handle, IN const char* strKey, IN bool bValue);
*  @brief      设置相机Boolean型属性值
*  @param      void* handle                [IN]        相机句柄
*  @param      char* strKey                [IN]        属性键值
*              bool bValue                 [IN]        想要设置的相机的属性值
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_SetBoolValue(IN void* handle, IN const char* strKey, IN bool bValue);
*  @brief      Set Camera Boolean value
*  @param      void* handle                [IN]        Handle
*  @param      char* strKey                [IN]        Key value
*              bool bValue                 [IN]        Feature value to set
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_SetBoolValue(IN void* handle, IN const char* strKey, IN bool bValue);

/************************************************************************
*  @fn         MV_STA_GetBoolValue(IN void* handle, IN const char* strKey, OUT bool *pBoolValue);
*  @brief      获取相机Boolean属性值
*  @param      void* handle                     [IN]        相机句柄
*  @param      char* strKey                     [IN]        属性键值
*  @param      bool *pBoolValue                 [IN][OUT]   返回给调用者有关相机属性值
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_GetBoolValue(IN void* handle, IN const char* strKey, OUT bool *pBoolValue);
*  @brief      Get Camera Boolean value
*  @param      void* handle                     [IN]        Handle
*  @param      char* strKey                     [IN]        Key value
*  @param      bool *pBoolValue                 [IN][OUT]   Structure pointer of camera features
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_GetBoolValue(IN void* handle, IN const char* strKey, IN OUT bool *pBoolValue);

/************************************************************************
*  @fn         MV_STA_SetCommandValue(IN void* handle, IN const char* strKey);
*  @brief      设置相机Command型属性值
*  @param      void* handle                  [IN]        相机句柄
*  @param      char* strKey                  [IN]        属性键值
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn         MV_STA_SetCommandValue(IN void* handle, IN const char* strKey);
*  @brief      Set Camera Command value
*  @param      void* handle                  [IN]        Handle
*  @param      char* strKey                  [IN]        Key value
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_SetCommandValue(IN void* handle, IN const char* strKey);


/************************************************************************
*  @fn        MV_STA_SetAddressValue(IN void* handle,IN unsigned int nRegAddress,IN unsigned int nValue);
*  @brief      设置相机对应寄存器的值
*  @param      void* handle                  [IN]        相机句柄
*  @param      unsigned int nRegAddress      [IN]        寄存器地址
*  @param      unsigned int nValue           [IN]        值
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn        MV_STA_SetAddressValue
*  @brief      Set  address value
*  @param      void* handle                  [IN]        Handle
*  @param      unsigned int nRegAddress      [IN]        address
*  @param      unsigned int nValue           [IN]        value
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_SetAddressValue(IN void* handle,IN unsigned int nRegAddress,IN unsigned int nValue);

/************************************************************************
*  @fn        MV_STA_ReadAddressValue(IN void * handle, IN unsigned int nRegAddress,OUT unsigned int *pnValue);
*  @brief      读取相机对应寄存器的值
*  @param      void* handle                  [IN]        相机句柄
*  @param      nRegAddress                   [IN]        寄存器地址
*  @param      unsigned int *pnValue          [OUT]       值
*  @return     成功,返回MV_STA_OK,失败,返回错误码

*  @fn     MV_STA_ReadAddressValue(IN void * handle, IN unsigned int nRegAddress,OUT unsigned int *pnValue);
*  @brief  Read  address value
*  @param  void* handle                      [IN]        Handle
*  @param  unsigned int nRegAddress          [IN]        address
*  @param  unsigned int *pnValue             [OUT]        pnValue
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_ReadAddressValue(IN void * handle, IN unsigned int nRegAddress,OUT unsigned int *pnValue);


/************************************************************************
*  @fn     MV_STA_ForceIp()
*  @brief  强制IP
*  @param  handle：设备句柄
*  @param  nIP               [IN]      设置的IP
*  @param  nSubNetMask       [IN]      子网掩码
*  @param  nDefaultGateWay   [IN]      默认网关
*  @return 见返回错误码

*  @fn     MV_STA_ForceIp()
*  @brief  Force IP
*  @param  handle: Device handle
*  @param  nIP               [IN]      IP to set
*  @param  nSubNetMask       [IN]      Subnet mask
*  @param  nDefaultGateWay   [IN]      Default gateway
*  @return Refer to error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_ForceIp(IN void* handle, IN unsigned int nIP, IN unsigned int nSubNetMask, IN unsigned int nDefaultGateWay);

/************************************************************************
*  @fn     MV_STA_SetIpConfig
*  @brief  配置IP方式
*  @param  handle                      [IN]            设备句柄
*  @param  nType                       [IN]            IP类型，见MvSTAIpCfgMode
*  @return 见返回错误码

*  @fn     MV_STA_SetIpConfig
*  @brief  IP configuration method
*  @param  handle                      [IN]            Device handle
*  @param  nType                       [IN]            IP type, refer to MvSTAIpCfgMode
*  @return Refer to error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_SetIpConfig(IN void* handle, IN unsigned int nType);


/************************************************************************
*  @fn     MV_STA_FileAccessRead()
*  @brief  从相机读取文件
*  @param  handle                [IN]           句柄地址
*  @param  pstFileAccess         [IN]           文件存取结构体
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_FileAccessRead()
*  @brief  Read the file from the camera
*  @param  handle                [IN]           Handle
*  @param  pstFileAccess         [IN]           File access structure
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_FileAccessRead(IN void* handle, IN MV_STA_FILE_ACCESS * pstFileAccess);

/************************************************************************
*  @fn     MV_STA_FileAccessWrite()
*  @brief  将文件写入相机
*  @param  handle                [IN]           句柄地址
*  @param  pstFileAccess         [IN]           文件存取结构体
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_FileAccessWrite()
*  @brief  Write the file to camera
*  @param  handle                [IN]           Handle
*  @param  pstFileAccess         [IN]           File access structure
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_FileAccessWrite(IN void* handle, IN MV_STA_FILE_ACCESS * pstFileAccess);

/************************************************************************
 *  @fn     MV_STA_GetOptimalPacketSize
 *  @brief  获取最佳的packet size，该接口目前只支持GigE相机
 *  @param  handle                      [IN]            设备句柄
 *  @return 最佳packetsize
 
 *  @fn     MV_STA_GetOptimalPacketSize
 *  @brief  Get the optimal Packet Size, Only support GigE Camera
 *  @param  handle                      [IN]            Device handle
 *  @return Optimal packetsize
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_GetOptimalPacketSize(IN void* handle);

/************************************************************************
 *  @fn     MV_STA_GetAllMatchInfo
 *  @brief  获取各种类型的信息
 *  @param  handle                      [IN]            设备句柄
 *  @param  pstInfo                     [IN][OUT]       返回给调用者有关相机各种类型的信息结构体指针
 *  @return 成功,返回MV_STA_OK,失败,返回错误码
 
 *  @fn     MV_STA_GetAllMatchInfo
 *  @brief  Get various type of information
 *  @param  handle                      [IN]            Device handle
 *  @param  pstInfo                     [IN][OUT]       Structure pointer of various type of information
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_GetAllMatchInfo(IN void* handle, IN OUT MV_STA_ALL_MATCH_INFO* pstInfo);

/************************************************************************
 *  @fn     MV_STA_GIGE_SetResend
 *  @brief  设置是否打开重发包支持，及重发包设置
 *  @param  handle                      [IN]            设备句柄
 *  @param  bEnable                     [IN]            是否支持重发包
 *  @param  nMaxResendPercent           [IN]            最大重发比
 *  @param  nResendTimeout              [IN]            重发超时时间
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_GIGE_SetResend
 *  @brief  Set whethe to enable resend, and set resend
 *  @param  handle                      [IN]            Device handle
 *  @param  bEnable                     [IN]            enable resend
 *  @param  nMaxResendPercent           [IN]            Max resend persent
 *  @param  nResendTimeout              [IN]            Resend timeout
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_GIGE_SetResend(IN void* handle, IN unsigned int bEnable, unsigned int nMaxResendPercent = 10, unsigned int nResendTimeout = 50);

/************************************************************************
 *  @fn     MV_STA_FeatureLoad
 *  @brief  导入相机属性
 *  @param  handle                      [IN]            设备句柄
 *  @param  pFileName                   [IN]            属性文件名
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_FeatureLoad
 *  @brief  Load camera feature
 *  @param  handle                      [IN]            Device handle
 *  @param  pFileName                   [IN]            File name
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_FeatureLoad(IN void* handle, IN const char* pFileName);

/************************************************************************
 *  @fn     MV_STA_FeatureSave
 *  @brief  保存相机属性
 *  @param  handle                      [IN]            设备句柄
 *  @param  pFileName                   [IN]            属性文件名
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 
 
 *  @fn     MV_STA_FeatureSave
 *  @brief  Save camera feature
 *  @param  handle                      [IN]            Device handle
 *  @param  pFileName                   [IN]            File name
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_FeatureSave(IN void* handle, IN const char* pFileName);

/************************************************************************
 *  @fn     MV_STA_InvalidateNodes
 *  @brief  清除GenICam节点缓存
 *  @param  handle                      [IN]            设备句柄
 *  @return 成功，返回MV_STA_OK；错误，返回错误码
 
 *  @fn     MV_STA_InvalidateNodes
 *  @brief  Invalidate GenICam Nodes
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_InvalidateNodes(IN void* handle);

/************************************************************************
 *  @fn     MV_STA_SetGvcpTimeout
 *  @brief  设置GVCP命令超时时间
 *  @param  handle                      [IN]            设备句柄
 *  @param  nMillisec                   [IN]            超时时间，以毫秒位单位，范围：0-10000
 *  @return 成功，返回MV_STA_OK；错误，返回错误码 

 *  @fn     MV_GIGE_SetGvcpTimeout
 *  @brief  Set GVCP cammand timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            Timeout, ms as unit, range: 0-10000
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SetGvcpTimeout(IN void* handle, unsigned int nMillisec);

/************************************************************************
*  @fn     MV_STA_GetGvcpTimeout
*  @brief  获取GVCP命令超时时间
*  @param  handle                      [IN]            设备句柄
*  @param  pMillisec                   [IN]            超时时间指针，以毫秒位单位
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_GIGE_GetGvcpTimeout
*  @brief  Get GVCP cammand timeout
*  @param  handle                      [IN]            Device handle
*  @param  pMillisec                   [IN]            Timeout, ms as unit
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
 /************************************************************************/
MV_STA_API int __stdcall MV_STA_GetGvcpTimeout(IN void* handle, unsigned int* pMillisec);

/***********************************************************************
 *  @fn     MV_STA_XML_GetNodeAccessMode
 *  @brief  获得当前节点的访问模式
 *  @param  handle                      [IN]            设备句柄
 *  @param  pstrName                    [IN]            节点名称
 *  @param  pAccessMode                 [OUT]           节点的访问模式
 *  @return 成功，返回MV_STA_OK；错误，返回错误码

 *  @fn     MV_STA_XML_GetNodeAccessMode
 *  @brief  Get Access mode of cur node
 *  @param  handle                      [IN]            Device handle
 *  @param  pstrName                    [IN]            Name of node
 *  @param  pAccessMode                 [OUT]           Access mode of the node
 *  @return Success, return MV_STA_OK. Failure, return error code
 ***********************************************************************/
MV_STA_API int __stdcall MV_STA_XML_GetNodeAccessMode(IN void* handle, IN const char * pstrName, OUT MV_STA_XML_AccessMode *pAccessMode);

/***********************************************************************
 *  @fn     MV_STA_SetImageNodeNum
 *  @brief  设置SDK内部图像缓存节点个数，大于等于1，在抓图前调用
 *  @param  handle                      [IN]            设备句柄
 *  @param  nNum                        [IN]            缓存节点个数
 *  @return 成功，返回MV_STA_OK；错误，返回错误码
 
 *  @fn     MV_STA_SetImageNodeNum
 *  @brief  Set the number of the internal image cache nodes in SDK, Greater than or equal to 1, to be called before the capture
 *  @param  handle                      [IN]            Device handle
 *  @param  nNum                        [IN]            Image Node Number
 *  @return Success, return MV_STA_OK. Failure, return error code
 ***********************************************************************/
MV_STA_API int __stdcall MV_STA_SetImageNodeNum(IN void* handle,  IN unsigned int nNodeCount);

/************************************************************************
*  @fn     MV_STA_SetAlgorithmNodeCount()
*  @brief  高帧率模式下，设置算法输出缓存节点数量,阈值[3,...]，小于3会返回失败，超过3可能会导致内存不足，启动失败，在MV_STA_START()前调用
*  @param  handle                 [IN]          句柄地址
*  @param  nNodeCount             [IN]          算法输出节点数量
*  @return 成功，返回MV_STA_OK；错误，返回错误码 

*  @fn     MV_STA_SetAlgorithmNodeCount()
*  @brief  In high frame rate mode, setting the number of output cache nodes and the threshold [3,...],less than 3 will return a failure 
*  exceeding 3 may result in insufficient memory and startup failure,MV_STA_START() before calling 
*  @param  handle                 [IN]          handle address
*  @param  nNodeCount             [IN]          node count 
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_SetAlgorithmNodeCount(IN void* handle, IN int nNodeCount);

/************************************************************************
*  @fn     MV_STA_GetFileAccessProgress
*  @brief  获取文件存取的进度
*  @param  handle                      [IN]            设备句柄
*  @param  pstFileAccessProgress       [IN]            进度内容
*  @return 成功，返回MV_STA_OK；错误，返回错误码 （当前文件存取的状态）

*  @fn     MV_STA_GetFileAccessProgress
*  @brief  Get File Access Progress 
*  @param  handle                      [IN]            Device handle
*  @param  pstFileAccessProgress       [IN]            File access Progress
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetFileAccessProgress(IN void* handle, IN OUT MV_STA_FILE_ACCESS_PROGRESS * pstFileAccessProgress);


/************************************************************************
*  @fn     MV_STA_LocalUpgrade
*  @brief  设备本地升级
*  @param  handle                      [IN]            设备句柄
*  @param  pFilePathName               [IN]            文件名
*  @return 成功,返回MV_STA_OK,失败,返回错误码

*  @fn     MV_STA_LocalUpgrade
*  @brief  Device Local Upgrade
*  @param  handle                      [IN]            Device handle
*  @param  pFilePathName               [IN]            File name
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_LocalUpgrade(IN void* handle, IN const void *pFilePathName);

/************************************************************************
*  @fn     MV_STA_GetUpgradeProcess
*  @brief  获取升级进度
*  @param  handle                      [IN]            设备句柄
*  @param  pnProcess                   [OUT]           进度接收地址
*  @return 成功,返回MV_STA_OK,失败,返回错误码

*  @fn     MV_STA_GetUpgradeProcess
*  @brief  Get Upgrade Progress
*  @param  handle                      [IN]            Device handle
*  @param  pnProcess                   [OUT]           Progress receiving address
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_GetUpgradeProcess(IN void* handle,  IN OUT unsigned int* pnProcess);

/************************************************************************
*  @fn     MV_STA_ReadAddressMem
*  @brief  读内存
*  @param  handle                      [IN]            设备句柄
*  @param  pBuffer                     [IN][OUT]       作为返回值使用，保存读到的内存值（内存值是按照大端模式存储的）
*  @param  nRegAddress                 [IN]            待读取的内存地址，该地址可以从设备的Camera.xml文件中获取，形如xxx_RegAddr的xml节点值
                                                       （设备的Camera.xml文件会在设备打开之后自动生成在应用程序的当前目录中）
*  @param  nLength                     [IN]            待读取的内存长度
*  @return 成功,返回MV_STA_OK,失败,返回错误码

*  @fn     MV_STA_ReadAddressMem
*  @brief  Read Memory
*  @param  handle                      [IN]            Device Handle
*  @param  pBuffer                     [IN][OUT]       Used as a return value, save the read-in memory value ( Memory value is stored in accordance with the big end model)
*  @param  nRegAddress                 [IN]            Memory address to be read, which can be obtained from the Camera.xml file of the device, the form xml node value of xxx_RegAddr
                                                       (Camera.xml file of device is automatically generated in the application's current directory after the device is opened)
*  @param  nLength                     [IN]            Length of the memory to be read
*  @return Success, return MV_STA_OK. Failure, return error code 
************************************************************************/
MV_STA_API int __stdcall MV_STA_ReadAddressMem(IN void * handle,IN OUT void *pBuffer, IN int64_t nRegAddress, IN int64_t nLength);

/************************************************************************
*  @fn     MV_STA_WriteAddressMem
*  @brief  写内存
*  @param  handle                      [IN]            设备句柄
*  @param  pBuffer                     [IN]            待写入的内存值（注意内存值要按照大端模式存储）
*  @param  nRegAddress                 [IN]            待写入的内存地址，该地址可以从设备的Camera.xml文件中获取，形如xxx_RegAddr的xml节点值
                                                       （设备的Camera.xml文件会在设备打开之后自动生成在应用程序的当前目录中）
*  @param  nLength                     [IN]            待写入的内存长度
*  @return 成功,返回MV_STA_OK,失败,返回错误码

*  @fn     MV_STA_WriteAddressMem
*  @brief  Write Memory
*  @param  handle                      [IN]            Device Handle
*  @param  pBuffer                     [IN]            Memory value to be written ( Note the memory value to be stored in accordance with the big end model)
*  @param  nRegAddress                 [IN]            Memory address to be written, which can be obtained from the Camera.xml file of the device, the form xml node value of xxx_RegAddr
                                                       (Camera.xml file of device is automatically generated in the application's current directory after the device is opened)
*  @param  nLength                     [IN]            Length of the memory to be written
*  @return Success, return MV_STA_OK. Failure, return error code 
************************************************************************/
MV_STA_API int __stdcall MV_STA_WriteAddressMem(IN void * handle,IN OUT void *pBuffer, IN int64_t nRegAddress, IN int64_t nLength);

/************************************************************************
*  @fn     MV_STA_GetCameraXML
*  @brief  获取相机xml
*  @param  handle                      [IN]            设备句柄
*  @param  pData                       [IN OUT]        接收xml缓存
*  @param  nDataSize                   [IN]............缓存长度
*  @param  pnDataLen                   [OUT]...........数据实际长度
*  @return 成功,返回MV_STA_OK,失败,返回错误码

*  @fn     MV_STA_GetCameraXML
*  @brief  Get Camera XML
*  @param  handle                      [IN]            Device handle
*  @param  pData                       [IN OUT]        recieve xml buf point
*  @param  nDataSize                   [IN]............buffer size
*  @param  pnDataLen                   [OUT]...........get data len
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetCameraXML(IN void * handle,IN OUT unsigned char* pData, IN unsigned int nDataSize, OUT unsigned int* pnDataLen);



#ifdef __cplusplus
}
#endif 

#endif //_MV_STEREOCAM_CTRL_EX_H_