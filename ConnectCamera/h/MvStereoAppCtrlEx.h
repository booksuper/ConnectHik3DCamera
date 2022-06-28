/***************************************************************************************************
*
* ��Ȩ��Ϣ����Ȩ���� (c) 2019, ���ݺ��������˼������޹�˾, ��������Ȩ��
*
* �ļ����ƣ�MvStereoAppCtrlEx.h
* ժ    Ҫ: �������SDK����չ�ӿڶ���
*
* ��ǰ�汾��2.1.0
* ��    ��: �����Ӿ�SDK�Ŷ�
* ��    �ڣ�2019.12.1
* ��    ע���½�
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
*  @brief      �ж�����ķ���Ȩ��
*  @param      MV_STEREOCAM_NET_INFO* pstDevInfo                [IN]        �����Ϣ
*  @param      unsigned int * nAccessMode                       [IN]        ����ķ���Ȩ��      //Eg: MV_STA_ACCESS_Exclusive
*  @return    �ɴ����true�����ɴ����false 

*  @fn         MV_STA_API int __stdcall MV_STA_CamIsAccessible(IN MV_STEREOCAM_NET_INFO* pstDevInfo, IN unsigned int nAccessMode)
*  @brief      Get camera's Access privileges
*  @param      MV_STEREOCAM_NET_INFO* pstDevInfo                [IN]        camera info 
*  @param       unsigned int * nAccessMode                      [IN]        camera's Access privileges    //Eg: MV_STA_ACCESS_Exclusive
*  @return     Success, return true. Failure, false
************************************************************************/    
MV_STA_API int __stdcall  MV_STA_CamIsAccessible(IN MV_STEREOCAM_NET_INFO* pstDevInfo, IN unsigned int nAccessMode);


/************************************************************************
*  @fn     MV_STA_GetDeviceInfo
*  @brief  ��ȡ�豸��Ϣ
*  @param  handle                      [IN]            �豸���
*  @param  pstDevInfo                  [IN][OUT]       ���ظ��������й�����豸��Ϣ�ṹ��ָ��
*  @return �ɹ�,����MV_STA_OK,ʧ��,���ش�����

*  @fn     MV_STA_GetDeviceInfo
*  @brief  Get device information
*  @param  handle                      [IN]            Device handle
*  @param  pstDevInfo                  [IN][OUT]       Structure pointer of device information
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetDeviceInfo(IN void * handle, IN OUT MV_STEREOCAM_NET_INFO* pstDevInfo);

 
/************************************************************************
*  @fn     MV_STA_GetDevicePropertyConfiguration
*  @brief  ��ȡ�豸GIGE��������
*  @param  handle                      [IN]            �豸���
*  @param  pData                       [IN][OUT]       ���ظ��������й�����豸��Ϣ�ṹ��ָ��
*  @param  nDataSize                   [IN]            �������ݳ���
*  @param  pnDataLen                   [IN][OUT]       ʵ�ʷ������ݵĳ���
*  @return �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      �������Integer������ֵ
*  @param      void* handle                [IN]        ������
*  @param      char* strKey                [IN]        ���Լ�ֵ�����ȡ�����Ϣ��Ϊ"Width"
*              const int64_t nValue        [IN]        ��Ҫ���õ����������ֵ
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      ��ȡInteger����ֵ
*  @param      void* handle                [IN]        ������
*  @param      char* strKey                [IN]        ���Լ�ֵ�����ȡ�����Ϣ��Ϊ"Width"
*  @param      MV_STA_INTVALUE* pIntValue  [IN][OUT]   ���ظ��������й�������Խṹ��ָ��
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      �������Enum������ֵ
*  @param      void* handle                [IN]        ������
*  @param      char* strKey                [IN]        ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
*              const unsigned int nValue   [IN]        ��Ҫ���õ����������ֵ
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      �������Enum������ֵ
*  @param      void* handle                [IN]        ������
*  @param      char* strKey                [IN]        ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
*              char* sValue                [IN]        ��Ҫ���õ�����������ַ���
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      ��ȡ���Enum����ֵ
*  @param      void* handle                   [IN]        ������
*  @param      char* strKey                   [IN]        ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
*  @param      MV_STA_ENUMVALUE* pEnumValue [IN][OUT]   ���ظ��������й�������Խṹ��ָ��
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      �������Float������ֵ
*  @param      void* handle                [IN]        ������
*  @param      char* strKey                [IN]        ���Լ�ֵ
*              float fValue                [IN]        ��Ҫ���õ����������ֵ
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      ��ȡ���Float����ֵ
*  @param      void* handle                     [IN]        ������
*  @param      char* strKey                     [IN]        ���Լ�ֵ
*  @param      MV_STA_FLOATVALUE *pFloatValue [IN][OUT]   ���ظ��������й�������Խṹ��ָ��
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      �������String������ֵ
*  @param      void* handle                  [IN]        ������
*  @param      char* strKey                  [IN]        ���Լ�ֵ
*              char * sValue                 [IN]        ��Ҫ���õ����������ֵ
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      ��ȡ���String����ֵ
*  @param      void* handle                       [IN]        ������
*  @param      char* strKey                       [IN]        ���Լ�ֵ
*  @param      MV_STA_CAM_GetStringValue [IN][OUT]   ���ظ��������й�������Խṹ��ָ��
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      �������Boolean������ֵ
*  @param      void* handle                [IN]        ������
*  @param      char* strKey                [IN]        ���Լ�ֵ
*              bool bValue                 [IN]        ��Ҫ���õ����������ֵ
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      ��ȡ���Boolean����ֵ
*  @param      void* handle                     [IN]        ������
*  @param      char* strKey                     [IN]        ���Լ�ֵ
*  @param      bool *pBoolValue                 [IN][OUT]   ���ظ��������й��������ֵ
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      �������Command������ֵ
*  @param      void* handle                  [IN]        ������
*  @param      char* strKey                  [IN]        ���Լ�ֵ
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

*  @fn         MV_STA_SetCommandValue(IN void* handle, IN const char* strKey);
*  @brief      Set Camera Command value
*  @param      void* handle                  [IN]        Handle
*  @param      char* strKey                  [IN]        Key value
*  @return     Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_SetCommandValue(IN void* handle, IN const char* strKey);


/************************************************************************
*  @fn        MV_STA_SetAddressValue(IN void* handle,IN unsigned int nRegAddress,IN unsigned int nValue);
*  @brief      ���������Ӧ�Ĵ�����ֵ
*  @param      void* handle                  [IN]        ������
*  @param      unsigned int nRegAddress      [IN]        �Ĵ�����ַ
*  @param      unsigned int nValue           [IN]        ֵ
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief      ��ȡ�����Ӧ�Ĵ�����ֵ
*  @param      void* handle                  [IN]        ������
*  @param      nRegAddress                   [IN]        �Ĵ�����ַ
*  @param      unsigned int *pnValue          [OUT]       ֵ
*  @return     �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief  ǿ��IP
*  @param  handle���豸���
*  @param  nIP               [IN]      ���õ�IP
*  @param  nSubNetMask       [IN]      ��������
*  @param  nDefaultGateWay   [IN]      Ĭ������
*  @return �����ش�����

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
*  @brief  ����IP��ʽ
*  @param  handle                      [IN]            �豸���
*  @param  nType                       [IN]            IP���ͣ���MvSTAIpCfgMode
*  @return �����ش�����

*  @fn     MV_STA_SetIpConfig
*  @brief  IP configuration method
*  @param  handle                      [IN]            Device handle
*  @param  nType                       [IN]            IP type, refer to MvSTAIpCfgMode
*  @return Refer to error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_SetIpConfig(IN void* handle, IN unsigned int nType);


/************************************************************************
*  @fn     MV_STA_FileAccessRead()
*  @brief  �������ȡ�ļ�
*  @param  handle                [IN]           �����ַ
*  @param  pstFileAccess         [IN]           �ļ���ȡ�ṹ��
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_FileAccessRead()
*  @brief  Read the file from the camera
*  @param  handle                [IN]           Handle
*  @param  pstFileAccess         [IN]           File access structure
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_FileAccessRead(IN void* handle, IN MV_STA_FILE_ACCESS * pstFileAccess);

/************************************************************************
*  @fn     MV_STA_FileAccessWrite()
*  @brief  ���ļ�д�����
*  @param  handle                [IN]           �����ַ
*  @param  pstFileAccess         [IN]           �ļ���ȡ�ṹ��
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_FileAccessWrite()
*  @brief  Write the file to camera
*  @param  handle                [IN]           Handle
*  @param  pstFileAccess         [IN]           File access structure
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_FileAccessWrite(IN void* handle, IN MV_STA_FILE_ACCESS * pstFileAccess);

/************************************************************************
 *  @fn     MV_STA_GetOptimalPacketSize
 *  @brief  ��ȡ��ѵ�packet size���ýӿ�Ŀǰֻ֧��GigE���
 *  @param  handle                      [IN]            �豸���
 *  @return ���packetsize
 
 *  @fn     MV_STA_GetOptimalPacketSize
 *  @brief  Get the optimal Packet Size, Only support GigE Camera
 *  @param  handle                      [IN]            Device handle
 *  @return Optimal packetsize
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_GetOptimalPacketSize(IN void* handle);

/************************************************************************
 *  @fn     MV_STA_GetAllMatchInfo
 *  @brief  ��ȡ�������͵���Ϣ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstInfo                     [IN][OUT]       ���ظ��������й�����������͵���Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_STA_OK,ʧ��,���ش�����
 
 *  @fn     MV_STA_GetAllMatchInfo
 *  @brief  Get various type of information
 *  @param  handle                      [IN]            Device handle
 *  @param  pstInfo                     [IN][OUT]       Structure pointer of various type of information
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_GetAllMatchInfo(IN void* handle, IN OUT MV_STA_ALL_MATCH_INFO* pstInfo);

/************************************************************************
 *  @fn     MV_STA_GIGE_SetResend
 *  @brief  �����Ƿ���ط���֧�֣����ط�������
 *  @param  handle                      [IN]            �豸���
 *  @param  bEnable                     [IN]            �Ƿ�֧���ط���
 *  @param  nMaxResendPercent           [IN]            ����ط���
 *  @param  nResendTimeout              [IN]            �ط���ʱʱ��
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
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
 *  @brief  �����������
 *  @param  handle                      [IN]            �豸���
 *  @param  pFileName                   [IN]            �����ļ���
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_FeatureLoad
 *  @brief  Load camera feature
 *  @param  handle                      [IN]            Device handle
 *  @param  pFileName                   [IN]            File name
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_FeatureLoad(IN void* handle, IN const char* pFileName);

/************************************************************************
 *  @fn     MV_STA_FeatureSave
 *  @brief  �����������
 *  @param  handle                      [IN]            �豸���
 *  @param  pFileName                   [IN]            �����ļ���
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_FeatureSave
 *  @brief  Save camera feature
 *  @param  handle                      [IN]            Device handle
 *  @param  pFileName                   [IN]            File name
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_FeatureSave(IN void* handle, IN const char* pFileName);

/************************************************************************
 *  @fn     MV_STA_InvalidateNodes
 *  @brief  ���GenICam�ڵ㻺��
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش�����
 
 *  @fn     MV_STA_InvalidateNodes
 *  @brief  Invalidate GenICam Nodes
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_InvalidateNodes(IN void* handle);

/************************************************************************
 *  @fn     MV_STA_SetGvcpTimeout
 *  @brief  ����GVCP���ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  nMillisec                   [IN]            ��ʱʱ�䣬�Ժ���λ��λ����Χ��0-10000
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

 *  @fn     MV_GIGE_SetGvcpTimeout
 *  @brief  Set GVCP cammand timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            Timeout, ms as unit, range: 0-10000
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SetGvcpTimeout(IN void* handle, unsigned int nMillisec);

/************************************************************************
*  @fn     MV_STA_GetGvcpTimeout
*  @brief  ��ȡGVCP���ʱʱ��
*  @param  handle                      [IN]            �豸���
*  @param  pMillisec                   [IN]            ��ʱʱ��ָ�룬�Ժ���λ��λ
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

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
 *  @brief  ��õ�ǰ�ڵ�ķ���ģʽ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstrName                    [IN]            �ڵ�����
 *  @param  pAccessMode                 [OUT]           �ڵ�ķ���ģʽ
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش�����

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
 *  @brief  ����SDK�ڲ�ͼ�񻺴�ڵ���������ڵ���1����ץͼǰ����
 *  @param  handle                      [IN]            �豸���
 *  @param  nNum                        [IN]            ����ڵ����
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش�����
 
 *  @fn     MV_STA_SetImageNodeNum
 *  @brief  Set the number of the internal image cache nodes in SDK, Greater than or equal to 1, to be called before the capture
 *  @param  handle                      [IN]            Device handle
 *  @param  nNum                        [IN]            Image Node Number
 *  @return Success, return MV_STA_OK. Failure, return error code
 ***********************************************************************/
MV_STA_API int __stdcall MV_STA_SetImageNodeNum(IN void* handle,  IN unsigned int nNodeCount);

/************************************************************************
*  @fn     MV_STA_SetAlgorithmNodeCount()
*  @brief  ��֡��ģʽ�£������㷨�������ڵ�����,��ֵ[3,...]��С��3�᷵��ʧ�ܣ�����3���ܻᵼ���ڴ治�㣬����ʧ�ܣ���MV_STA_START()ǰ����
*  @param  handle                 [IN]          �����ַ
*  @param  nNodeCount             [IN]          �㷨����ڵ�����
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

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
*  @brief  ��ȡ�ļ���ȡ�Ľ���
*  @param  handle                      [IN]            �豸���
*  @param  pstFileAccessProgress       [IN]            ��������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� ����ǰ�ļ���ȡ��״̬��

*  @fn     MV_STA_GetFileAccessProgress
*  @brief  Get File Access Progress 
*  @param  handle                      [IN]            Device handle
*  @param  pstFileAccessProgress       [IN]            File access Progress
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetFileAccessProgress(IN void* handle, IN OUT MV_STA_FILE_ACCESS_PROGRESS * pstFileAccessProgress);


/************************************************************************
*  @fn     MV_STA_LocalUpgrade
*  @brief  �豸��������
*  @param  handle                      [IN]            �豸���
*  @param  pFilePathName               [IN]            �ļ���
*  @return �ɹ�,����MV_STA_OK,ʧ��,���ش�����

*  @fn     MV_STA_LocalUpgrade
*  @brief  Device Local Upgrade
*  @param  handle                      [IN]            Device handle
*  @param  pFilePathName               [IN]            File name
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_LocalUpgrade(IN void* handle, IN const void *pFilePathName);

/************************************************************************
*  @fn     MV_STA_GetUpgradeProcess
*  @brief  ��ȡ��������
*  @param  handle                      [IN]            �豸���
*  @param  pnProcess                   [OUT]           ���Ƚ��յ�ַ
*  @return �ɹ�,����MV_STA_OK,ʧ��,���ش�����

*  @fn     MV_STA_GetUpgradeProcess
*  @brief  Get Upgrade Progress
*  @param  handle                      [IN]            Device handle
*  @param  pnProcess                   [OUT]           Progress receiving address
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_GetUpgradeProcess(IN void* handle,  IN OUT unsigned int* pnProcess);

/************************************************************************
*  @fn     MV_STA_ReadAddressMem
*  @brief  ���ڴ�
*  @param  handle                      [IN]            �豸���
*  @param  pBuffer                     [IN][OUT]       ��Ϊ����ֵʹ�ã�����������ڴ�ֵ���ڴ�ֵ�ǰ��մ��ģʽ�洢�ģ�
*  @param  nRegAddress                 [IN]            ����ȡ���ڴ��ַ���õ�ַ���Դ��豸��Camera.xml�ļ��л�ȡ������xxx_RegAddr��xml�ڵ�ֵ
                                                       ���豸��Camera.xml�ļ������豸��֮���Զ�������Ӧ�ó���ĵ�ǰĿ¼�У�
*  @param  nLength                     [IN]            ����ȡ���ڴ泤��
*  @return �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief  д�ڴ�
*  @param  handle                      [IN]            �豸���
*  @param  pBuffer                     [IN]            ��д����ڴ�ֵ��ע���ڴ�ֵҪ���մ��ģʽ�洢��
*  @param  nRegAddress                 [IN]            ��д����ڴ��ַ���õ�ַ���Դ��豸��Camera.xml�ļ��л�ȡ������xxx_RegAddr��xml�ڵ�ֵ
                                                       ���豸��Camera.xml�ļ������豸��֮���Զ�������Ӧ�ó���ĵ�ǰĿ¼�У�
*  @param  nLength                     [IN]            ��д����ڴ泤��
*  @return �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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
*  @brief  ��ȡ���xml
*  @param  handle                      [IN]            �豸���
*  @param  pData                       [IN OUT]        ����xml����
*  @param  nDataSize                   [IN]............���泤��
*  @param  pnDataLen                   [OUT]...........����ʵ�ʳ���
*  @return �ɹ�,����MV_STA_OK,ʧ��,���ش�����

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