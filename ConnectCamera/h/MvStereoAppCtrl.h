/***************************************************************************************************
*
* ��Ȩ��Ϣ����Ȩ���� (c) 2019, ���ݺ��������˼������޹�˾, ��������Ȩ��
*
* �ļ����ƣ�MvStereoAppCtrl.h
* ժ    Ҫ: �������SDK���ӿڶ���
*
* ��ǰ�汾��2.1.0
* ��    ��: �����Ӿ�SDK�Ŷ�
* ��    �ڣ�2019.12.1
* ��    ע���½�
****************************************************************************************************/

#ifndef _MV_STEREOAPP_CTRL_H_
#define _MV_STEREOAPP_CTRL_H_

#include "MvStereoAppDefine.h"

/**
*  @brief  ��̬�⵼�뵼������
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
 *  @brief  ��ȡSDK�汾��
 *  @param  
 *  @return ʼ�շ���4�ֽڰ汾�� |��    |��    |����  |  ����|
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
 *  @brief  ��ȡ��ҵ���SDK�汾��
 *  @param  
 *  @return ʼ�շ���4�ֽڰ汾�� |��    |��    |����  |  ����|
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
 *  @brief  ö���������(����������3D���������
 *  @param  pstCamList                 [OUT]          �豸�б�
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_EnumStereoCam()
 *  @brief  enum stereo camera device
 *  @param  pstCamList                 [OUT]          device list
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_EnumStereoCam(IN OUT MV_STEREOCAM_NET_INFO_LIST* pstCamList);

/************************************************************************
 *  @fn     MV_STA_EnumStereoCamEx()
 *  @brief  ö���豸 (�������������������
 *  @param  nTLayerType                [IN]           ö�ٴ����,����: MV_STA_GIGE_DEVICE | MV_STA_USB_DEVICE
 *  @param  pstCamList                 [OUT]          �豸�б�
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_EnumStereoCamEx()
 *  @brief  enum camera device
 *  @param  nTLayerType                 [IN]          Enumerate TLs,e.g.: MV_STA_GIGE_DEVICE | MV_STA_USB_DEVICE
 *  @param  pstCamList                  [OUT]         device list
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_EnumStereoCamEx(IN unsigned int nTLayerType, IN OUT MV_STA_DEVICE_INFO_LIST* pstCamList);


/************************************************************************
*  @fn     MV_STA_CreateHandleByCameraInfo()
*  @brief  ͨ���豸��Ϣ�������
*  @param  handle                 [OUT]          �����ַ
*  @param  pDeviceInfo            [IN]           �豸��Ϣ
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_CreateHandleByCameraInfo()
*  @brief  create handle by serial number
*  @param  handle                 [OUT]          handle address
*  @param  pDeviceInfo            [IN]           Device Info
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_CreateHandleByCameraInfo(IN OUT void ** handle, IN MV_STEREOCAM_NET_INFO*  pDeviceInfo);


/************************************************************************
 *  @fn     MV_STA_CreateHandleBySerialNumber()
 *  @brief  ͨ�����кŴ������
 *  @param  handle                 [OUT]          �����ַ
 *  @param  chSerialNumber         [IN]           ���к�
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

 *  @fn     MV_STA_CreateHandleBySerialNumber()
 *  @brief  create handle by serial number
 *  @param  handle                 [OUT]          handle address
 *  @param  chSerialNumber         [IN]           serial number
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_CreateHandleBySerialNumber(IN OUT void ** handle, IN const char* chSerialNumber);


/************************************************************************
 *  @fn     MV_STA_CreateHandleByMacAddr()
 *  @brief  ͨ��Mac��ַ�������
 *  @param  handle                 [IN]          �����ַ
 *  @param  nMacHigh               [IN]          MAC��ַ�������ֽ�
 *  @param  nMacLow                [IN]          MAC��ַ���ĸ��ֽ�
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
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
 *  @brief  ���豸
 *  @param  handle                 [IN]          �����ַ
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_OpenDevice()
 *  @brief  open device
 *  @param  handle                 [OUT]          handle address
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_OpenDevice(IN void* handle);

/***********************************************************************
 *  @fn         MV_STA_RegisterDataCallBack()
 *  @brief      ע��ͼ�����ݻص�
 *  @param       handle                 [IN]          ���
 *  @param       cbOutput               [IN]          �ص�����ָ��
 *  @param       pUser                  [IN]          �û��Զ������
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش�����

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
 *  @brief  ע���쳣��Ϣ�ص����ڴ��豸֮�����
 *  @param  handle���豸���
 *  @param  cbException       [IN]      �쳣�ص�����ָ��
 *  @param  pUser             [IN]      �û��Զ������
 *  @return �����ش�����

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
 *  @brief      ��ʼȡ��
 *  @param      handle                 [IN]          ���
 *  @return     �ɹ�������MV_STA_OK�����󣬷��ش�����
 
 *  @fn         MV_STA_Start()
 *  @brief      Start Grabbing
 *  @param      handle                 [IN]          Handle
 *  @return     Success, return MV_STA_OK. Failure, return error code
 ***********************************************************************/
MV_STA_API int __stdcall MV_STA_Start(IN void* handle);

/***********************************************************************
 *  @fn         MV_STA_Stop()
 *  @brief      ֹͣȡ��
 *  @param       handle                 [IN]          ���
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش�����
 
 *  @fn         MV_STA_Stop()
 *  @brief      Stop Grabbing
 *  @param      handle                 [IN]          Handle
 *  @return     Success, return MV_STA_OK. Failure, return error code
 ***********************************************************************/
MV_STA_API int __stdcall MV_STA_Stop(IN void* handle);

/************************************************************************
 *  @fn     MV_STA_DestroyHandle()
 *  @brief  �����豸���
 *  @param  handle                 [IN]          ���
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

 *  @fn     MV_STA_DestroyHandle()
 *  @brief  Destroy Device Handle
 *  @param  handle                 [IN]          Handle
 *  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_DestroyHandle(IN void * handle);


/************************************************************************
 *  @fn     MV_STA_ReceiveDataTimeout()
 *  @brief  ��ѯ��ʽ��ȡ���ݼ�
 *  @param  handle                 [IN]          �����ַ
 *  @param  pDataSet               [IN]          ���ݼ�ָ��
 *  @param  nTimeOut               [IN]          ��ʱʱ��
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
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
 *  @brief  �������ݼ� ����MV_STA_ReceiveDataTimeout ����ʹ�ã���ע�����ص�ʱ������Ҫ���ô˺�����
 *  @param  DataSet                [IN]          ���ݼ�
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_DestroyData()
 *  @brief  destroy data set
 *  @param  DataSet                [IN]          data set
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_DestroyData(IN STC_DataSet DataSet);


/************************************************************************
 *  @fn     MV_STA_DataSetCount()
 *  @brief  ��ȡ���ݼ��еķ������ݸ���
 *  @param  DataSet                 [IN]          ���ݼ�
 *  @return �ɹ����������ݸ��������󣬷���0 
 
 *  @fn     MV_STA_DataSetCount()
 *  @brief  get the count of data set
 *  @param  DataSet                 [IN]          data set
 *  @return Success, return data count. Failure, return 0
 ************************************************************************/
MV_STA_API unsigned int __stdcall MV_STA_DataSetCount(IN STC_DataSet DataSet);

/************************************************************************
 *  @fn     MV_STA_DataSetAt()
 *  @brief  ������Ż�ȡ���ݶ���
 *  @param  DataSet                 [OUT]          ���ݼ�
 *  @param  nIndex                  [IN]           ���ݼ��е����
 *  @return �ɹ������������ݶ���ָ�룻���󣬷���NULL 
 
 *  @fn     MV_STA_DataSetAt()
 *  @brief  get data object by index
 *  @param  DataSet                 [OUT]          data set
 *  @param  nIndex                  [IN]           index in data set
 *  @return Success, return obeject point. Failure, return NULL
 ************************************************************************/
MV_STA_API STC_Object  __stdcall MV_STA_DataSetAt(IN STC_DataSet DataSet, IN unsigned int nIndex);

/************************************************************************
 *  @fn     MV_STA_DataMsgType()
 *  @brief  ���ݶ����ȡ��Ϣ����
 *  @param  DataObject                 [IN]           ���ݶ���
 *  @return �ɹ����������ݶ������ͣ����󣬷���STC_DATA_MSG_TYPE_UNKNOWN
 
 *  @fn     MV_STA_DataMsgType()
 *  @brief   Get the type of message
 *  @param  DataObject                 [IN]           data object
 *  @return Success, return object type. Failure, return  STC_DATA_MSG_TYPE_UNKNOWN
 ************************************************************************/
MV_STA_API unsigned int __stdcall MV_STA_DataMsgType(IN STC_Object DataObject);

/************************************************************************
 *  @fn     MV_STA_GetDeviceFrameID()
 *  @brief  ��ȡ�����֡�ţ���ͼ��֡�ţ�ʵΪ֡ͳ��ֵ��
 *  @param  DataObject                 [IN]           ���ݶ���
 *  @param  pnImageID                  [OUT]          ֡��
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 *..@remark ���߼������MV-DL2040-04B-H �̼�V1.1.0֮��֧��
 
 *  @fn     MV_STA_GetDeviceFrameID()
 *  @brief   Get camera frameID(not image frameID)
 *  @param  DataObject                 [IN]           data object
 *  @param  pnImageID                  [Out]          freameID
 *  @return Success, return MV_STA_OK. Failure, return error code
 *  @remark only Line laser camera MV-DL2040-04B-H,  firmwareVersion V1.1.0 or new support
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_GetDeviceFrameID( IN STC_Object DataObject, IN OUT unsigned int * pnImageID);

/**********������Ϣ���ͣ���ȡ��ϸ����**************/
// �������ԭʼͼ��Mono8��Depth16��PointCloud16�ȣ���Ӧ���� STC_DATA_MSG_TYPE_IMG_RAWʱ���Ե��ô˺���
/************************************************************************
 *  @fn     MV_STA_GetImage()
 *  @brief  ��ȡͼ����Ϣ
 *  @param  DataObject                 [IN]          ���ݶ���
 *  @param  pImg                       [IN OUT]      ͼ������
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_GetImage()
 *  @brief  get image info
 *  @param  DataObject                 [IN]          data object
 *  @param  pImg                       [IN OUT]      image data
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_GetImage(IN STC_Object DataObject, IN OUT STC_DATA_IMAGE* pImg);


/************************************************************************
*  @fn     MV_STA_GetProfileCount()
*  @brief   ��ȡ3D���������ͼ�߶�       ��Ӧ���� STC_3D_Profile_Countʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnProfileCount            [IN OUT]        ����
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetProfileCount()
*  @brief  getProfile Count
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileCount             [IN OUT]       Profile count
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetProfileCount(IN STC_Object DataObject, IN OUT unsigned int * pnProfileCount);

/************************************************************************
*  @fn     MV_STA_GetProfileLinePntNum()
*  @brief   ��ȡ3D���������ͼ���      ��Ӧ���� STC_3D_Profile_LinePntNumʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnProfileLineNum           [IN OUT]      �е���
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetProfileLinePntNum()
*  @brief  get Profile Line Pnt Num
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileLineNum           [IN OUT]       line point count
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetProfileLinePntNum( IN STC_Object DataObject, IN OUT unsigned int * pnProfileLineNum);

/************************************************************************
*  @fn     MV_STA_GetProfileIntensity()
*  @brief   ��ȡ3D������ ����ͼ         ��Ӧ���� STC_3D_Profile_Intensityʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnProfileIntensity         [IN OUT]      ����ͼ
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetProfileIntensity()
*  @brief  get Intensity
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileIntensity         [IN OUT]       Intensity
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetProfileIntensity(IN STC_Object DataObject, IN OUT STC_PROFILE_INTENSITY * pnProfileIntensity);

/************************************************************************
*  @fn     MV_STA_GetProfileThickness()
*  @brief   ��ȡ3D������ ���ͼ        ��Ӧ���� STC_3D_Profile_Thicknessʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnProfileThickness         [IN OUT]      ���ͼ
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetProfileThickness()
*  @brief  get Thickness
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileThickness         [IN OUT]       ProfileThickness
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall  MV_STA_GetProfileThickness( IN STC_Object DataObject, IN OUT STC_PROFILE_THICKNESS * pnProfileThickness);

/************************************************************************
*  @fn     MV_STA_GetProfileRunDir()
*  @brief   ��ȡ3D������ ǰ������     ��Ӧ���� STC_3D_Profile_RunDirʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnProfileRunDir           [IN OUT]      ǰ������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetProfileRunDir()
*  @brief  get Profile Run Dir
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileRunDir            [IN OUT]       Profile Run Dir
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetProfileRunDir(IN STC_Object DataObject, IN OUT STC_PROFILE_RUNDIR * pnProfileRunDir);

/************************************************************************
*  @fn     MV_STA_GetProfileFirstFrmID()
*  @brief   ��ȡ3D������ ��һ��������֡��     ��Ӧ���� STC_3D_Profile_FirstFrmIDʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnProfileFirstFrmID           [IN OUT]      ��һ��������֡��
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetProfileFirstFrmID()
*  @brief  Profile First Frm ID
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileFirstFrmID        [IN OUT]       Profile First Frm ID
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetProfileFirstFrmID( IN STC_Object DataObject, IN OUT unsigned int  * pnProfileFirstFrmID);

/************************************************************************
*  @fn     MV_STA_GetProfileCoordScale()
*  @brief   ��ȡ3D������ �������        ��Ӧ���� STC_3D_Profile_CoordScaleʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnProfileCoordScale       [IN OUT]     �������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetProfileCoordScale()
*  @brief  Get Profile  Coord Scale
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileCoordScale        [IN OUT]       Profile  Coord Scale
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetProfileCoordScale( IN STC_Object DataObject, IN OUT STC_PROFILE_COORDSCALE  * pnProfileCoordScale);

/************************************************************************
*  @fn     MV_STA_GetProfileCoordOffset()
*  @brief   ��ȡ3D������ ������ʼ���ƫ��     ��Ӧ���� STC_3D_Profile_CoordOffsetʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnProfileCoordOffset       [IN OUT]      ������ʼ��ƫ��
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetProfileCoordOffset()
*  @brief  Get Profile  Coord Offset
*  @param  DataObject                 [IN]           data object
*  @param  pnProfileCoordOffset       [IN OUT]       Profile  Coord Offset
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetProfileCoordOffset( IN STC_Object DataObject, IN OUT STC_PROFILE_COORDOFFSET  * pnProfileCoordOffset);

/************************************************************************
*  @fn     MV_STA_GetDwsVolumeInfo()
*  @brief   ��ȡ�߼���������������      ��Ӧ���� STC_DATA_MSG_TYPE_DWS_VOLUMEʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pVolumInfo                 [IN OUT]      �������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetDwsVolumeInfo()
*  @brief  get volum  info
*  @param  DataObject                 [IN]          data object
*  @param  pVolumInfo                 [IN OUT]      volum data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetDwsVolumeInfo(IN STC_Object DataObject, IN OUT STC_DWS_VOLUME_INFO* pVolumInfo);


/************************************************************************
*  @fn     MV_STA_GetStereoVolumeInfo()
*  @brief   ��ȡ˫Ŀ������������         ��Ӧ���� STC_DATA_MSG_TYPE_STEREO_VOLUME ʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pVolumInfo                 [IN OUT]      �������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetStereoVolumeInfo()
*  @brief  get volum  info
*  @param  DataObject                 [IN]          data object
*  @param  pVolumInfo                 [IN OUT]      volum data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_GetStereoVolumeInfo(IN STC_Object DataObject, IN OUT STC_STEREO_VOLUME_INFO* pVolumInfo);


/************************************************************************
*  @fn     MV_STA_NormalizedDepthImage()
*  @brief    �Ѷ������ͼ��ʽͳһ��Mono16      [��ǰ��֧�� STC_PixelType_Gvsp_Coord3D_C32 STC_PixelType_Gvsp_Coord3D_C16  ת STC_PixelType_Gvsp_Mono16]
*  @param  handle                 [IN]          �����ַ
*  @param  pstImage               [IN OUT]      ͼ������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_NormalizedDepthImage()
*  @brief   Image conversion to Mono16 format 
*  @param  handle                 [IN]          handle address
*  @param   pstImage               [IN OUT]     Image Data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_NormalizedDepthImage(IN void* handle, IN OUT STC_NORMALIZE_IMAGE* pstImage);

/************************************************************************
*  @fn     MV_STA_NormalizedPointCloudImage()
*  @brief   �Ѷ��ֵ���ͼת��Ϊ ABC16 �� ABC32)         [��ǰ��֧�� STC_PixelType_Gvsp_Coord3D_ABC32f_Planar  STC_PixelType_Gvsp_Coord3D_ABC32]
*  @param  handle                 [IN]          �����ַ
*  @param  pstImage               [IN OUT]      ͼ������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_NormalizedPointCloudImage()
*  @brief   Converting multiple point clouds to ABC16 or ABC32
*  @param  handle                 [IN]          handle address
*  @param   pstImage              [IN OUT]     Image Data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_NormalizedPointCloudImage(IN void* handle, IN OUT STC_NORMALIZE_IMAGE* pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveTiff()
 *  @brief  ����16λ���ͼΪTIFF��ʽ      [��ǰ��֧��STC_PixelType_Gvsp_Mono16 ����ΪTIFF]
 *  @param  handle                 [IN]          �����ַ
 *  @param  pstImage               [IN]          ���ͼ����
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_SaveTiff()
 *  @brief  save Mono16 depth image to tiff
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          depth imagebuf 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveTiff(IN void* handle, IN STC_IMG_SAVE_MONO16_TO_TIFF_PARAM* pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveJpg()
 *  @brief  ����16λ���ͼΪjpg��ʽ      [��ǰ��֧��STC_PixelType_Gvsp_Mono16 ����Ϊjpg]
 *  @param  handle                 [IN]          �����ַ
 *  @param  pstImage               [IN]          ���ͼ����
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_SaveJpg()
 *  @brief  save Mono16 depth image to jpg
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          depth imagebuf 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveJpg(IN void* handle, IN STC_IMG_SAVE_MONO16_TO_JPG_PARAM* pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveBmp()
 *  @brief  ����16λ���ͼΪBmp��ʽ      [��ǰ��֧��STC_PixelType_Gvsp_Mono16 ����Ϊbmp]
 *  @param  handle                 [IN]          �����ַ
 *  @param  pstImage               [IN]          ���ͼ����
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_SaveBmp()
 *  @brief  save Mono16 depth image to bmp
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          depth imagebuf 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveBmp(IN void* handle, IN STC_IMG_SAVE_MONO16_TO_BMP_PARAM* pstImage);

/************************************************************************
 *  @fn     MV_STA_SavePly()
 *  @brief ����ABC16 �� ABC32��ʽ����ͼΪPLY��ʽ
 *  @param  handle             [IN]          �����ַ
 *  @param  pstImage          [IN]           ����
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_SavePly()
 *  @brief  save ABC16 or ABC32 image to ply
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          data 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SavePly(IN void* handle,  IN OUT STC_IMG_SAVE_ABC16_TO_PLY_PARAM * pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveObj()
 *  @brief ����ABC16 �� ABC32 ��ʽ����ͼΪObj��ʽ
 *  @param  handle             [IN]          �����ַ
 *  @param  pstImage           [IN]          ����
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_SaveObj()
 *  @brief  save ABC16 image to obj
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          data 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveObj(IN void* handle,  IN OUT STC_IMG_SAVE_ABC16_TO_OBJ_PARAM * pstImage);

/************************************************************************
 *  @fn     MV_STA_SaveCsv()
 *  @brief ����ABC16 �� ABC32��ʽ����ͼΪcsv��ʽ
 *  @param  handle             [IN]          �����ַ
 *  @param  pstImage           [IN]          ����
 *  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 
 
 *  @fn     MV_STA_SaveObj()
 *  @brief  save ABC16 image to csv
 *  @param  handle                 [IN]          handle address
 *  @param  pstImage               [IN]          data 
 *  @return Success, return MV_STA_OK. Failure, return error code
 ************************************************************************/
MV_STA_API int __stdcall MV_STA_SaveCsv(IN void* handle,  IN OUT STC_IMG_SAVE_ABC16_TO_CSV_PARAM * pstImage);

/************************************************************************
*  @fn     MV_STA_DisplayStandardDepthMap()
*  @brief  ��׼���ͼ��Ⱦ[MONO16]     [��ǰ��֧�� STC_PixelType_Gvsp_Mono16 ��Ⱦ]
*  @param  handle                 [IN]          �����ַ
*  @param  pstImage               [IN]          ���ͼ����
*  @param  pstDisplayExInfo       [IN]          ��Ⱦ��չ��Ϣ
*  @param  hWnd                   [IN]          ��Ⱦ���ھ��
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

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
*  @brief  ��׼����ͼ��Ⱦ[ABC16,��ABC32]
*  @param  handle                 [IN]          �����ַ
*  @param  pstImage               [IN]          ����ͼ����
*  @param  hWnd                   [IN]          ��Ⱦ���ھ��
*  @param  nWndWidth              [IN]          ��Ⱦ���ڿ��
*  @param  nWndHeight              [IN]         ��Ⱦ���ڸ߶�
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

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
// ����ƴ�ӡ������ߣ�ƴ�ӳ�����ͼ����ǰ��֧��STC_PixelType_Gvsp_Coord3D_ABC16 ƴ�ӣ�����ӿڵ���˳�����£�
// 1. ע��ƴ�ӻص�������
// 2. ����ƴ�ӵ�֡���Ͳ�����
// 3. �������������ݣ�
// 4. �������������ݴﵽ֡��ʱ���Զ�ִ��ע��ص�����
/************************************************************************/ 

/***********************************************************************
*  @fn         MV_STA_RegisterPointCloudMosaicImageCallBack()
*  @brief      ע���������ƴ�ӻص�
*  @param       handle                 [IN]          ���
*  @param       cbOutputCallback       [IN]          �ص�����ָ��
*  @param       pUser                  [IN]          �û��Զ������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش�����

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
*  @brief  ���õ���ƴ�Ӳ���
*  @param  handle                 [IN]          �����ַ
*  @param  pstConfigInfo          [IN]          ����ͼƴ�Ӳ���
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_SetPointCloudMosaicConfigParam()
*  @brief  Set PointCloud Mosaic Config param
*  @param  handle                 [IN]          handle address
*  @param  pstConfigInfo          [IN]          config param
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_SetPointCloudMosaicConfigParam(IN void* handle,  IN STC_PointCloudMosaicConfigParam * pstConfigInfo);


/************************************************************************
*  @fn     MV_STA_PointCloudMosaicUpdateImage()
*  @brief  �����������    ����֧��STC_PixelType_Gvsp_Coord3D_ABC16��׼���Ƹ�ʽ���紫��Ǳ�׼���Ƹ�ʽ�����ܲ���������ȡ�����������ݣ����ƴ������ݵĿ����ͬ������Ϊ1��
*  @param  handle                 [IN]          �����ַ
*  @param  pstImage               [IN]          ����ͼ����
*  @param  nWidth                 [IN]          ���������߿��
*  @param  nImageSize             [IN]          ����ͼ��С
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

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
*  @brief  �����������    ��֧��STC_PixelType_Gvsp_Coord3D_ABC16��STC_PixelType_Gvsp_Coord3D_ABC32��׼���Ƹ�ʽ�������ƴ������ݵĿ����ͬ������Ϊ1��
*  @param  handle                 [IN]          �����ַ
*  @param  pstImage               [IN]          ����ͼ����
*  @param  nWidth                 [IN]          ���������߿��
*  @param  nImageSize             [IN]          ����ͼ��С
*  @param  nFrameNum              [IN]          ����ͼ֡��
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

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
*  @brief  ��յ�������   
*  @param  handle                 [IN]          �����ַ
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_ReleasePointCloudData()
*  @brief  release PointCloud data
*  @param  handle                 [IN]          handle address
*  @return Success, return MV_STA_OK. Failure,  return error code
************************************************************************/
MV_STA_API int __stdcall MV_STA_ReleasePointCloudData(IN void* handle);

/************************************************************************
*  @fn     MV_STA_GetCenterCoordinate()
*  @brief   ��ȡ��֡�����������ĵ�����     ��Ӧ���� STC_3D_Profile_CenterCoordinateʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnCenterCoordinate         [IN OUT]      ���ĵ�����
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetCenterCoordinate()
*  @brief  Get Profile  Center Coordinate
*  @param  DataObject                 [IN]           data object
*  @param  pnCenterCoordinate       [IN OUT]       Profile  Center Coordinate
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetCenterCoordinate( IN STC_Object DataObject, IN OUT STC_CENTERCOORDINATE  * pnCenterCoordinate);

/************************************************************************
*  @fn     MV_STA_GetExtendImage()
*  @brief  ��ȡchunkdata����չͼ������     ��Ӧ���� STC_3D_Profile_ExtendImgʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnExtendImage              [IN OUT]      ��չͼ������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetExtendImage()
*  @brief  Getting extended image data in chunkdata  Corresponding type STC_3D_Profile_ExtendImg can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnExtendImage              [IN OUT]       extended image data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetExtendImage( IN STC_Object DataObject, IN OUT STC_EXTEND_IMAGE  * pnExtendImage);

/************************************************************************
*  @fn     MV_STA_GetPackageInfo()
*  @brief  ��ȡchunkdata�а�����Ϣ����     ��Ӧ���� STC_3D_Profile_SingulatePkginfoʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnPackageInfo              [IN OUT]      ������Ϣ����
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetPackageInfo()
*  @brief  Get package information data in chunkdata   Corresponding type STC_3D_Profile_SingulatePkginfo can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnPackageInfo              [IN OUT]       packageinfo data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetPackageInfo( IN STC_Object DataObject, IN OUT STC_PACKAGE_INFO  * pnPackageInfo);

/************************************************************************
*  @fn     MV_STA_GetInstanceSegInfo()
*  @brief  ��ȡchunkdata��ʵ��ָ���Ϣ     ��Ӧ���� STC_3D_Profile_InstanceSegInfo ʱ���Ե��ô˺���
*  @param  DataObject                     [IN]          ���ݶ���
*  @param  pnInstanceSegInfo              [IN OUT]      ʵ��ָ�����
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetInstanceSegInfo()
*  @brief  Getting Instance Segmentation  data in chunkdata  Corresponding type STC_3D_Profile_InstanceSegInfo can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnInstanceSegInfo          [IN OUT]       Instance Segmentation  data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetInstanceSegInfo( IN STC_Object DataObject, IN OUT STC_INSTANCE_SEG_INFO  * pnInstanceSegInfo);

/************************************************************************
*  @fn     MV_STA_GetDetectObjInfo()
*  @brief  ��ȡchunkdata��Ŀ��������     ��Ӧ���� STC_3D_Profile_DetectInfoʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnDetectInfo              [IN OUT]      Ŀ��������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetDetectObjInfo()
*  @brief  Get detect information data in chunkdata   Corresponding type STC_3D_Profile_DetectInfo can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnDetectInfo               [IN OUT]       detectinfo data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetDetectObjInfo( IN STC_Object DataObject, IN OUT STC_DETECT_INFO  * pnDetectInfo);

/************************************************************************
*  @fn     MV_STA_GetTimeStampInfo()
*  @brief  ��ȡchunkdata��ʱ�������     ��Ӧ���� STC_3D_Profile_TimeStampʱ���Ե��ô˺���
*  @param  DataObject                   [IN]          ���ݶ���
*  @param  pnTimeStampInfo              [IN OUT]      ʱ�������
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetTimeStampInfo()
*  @brief  Get timestamp information data in chunkdata   Corresponding type STC_3D_Profile_TimeStamp can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnTimeStampInfo            [IN OUT]       timestamp data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetTimeStampInfo( IN STC_Object DataObject, IN OUT STC_TIME_STAMP_INFO  * pnTimeStampInfo);

/************************************************************************
*  @fn     MV_STA_GetGraspInfo()
*  @brief  ��ȡchunkdata��ץȡ��Ϣ����     ��Ӧ���� STC_3D_Profile_GraspInfoʱ���Ե��ô˺���
*  @param  DataObject                 [IN]          ���ݶ���
*  @param  pnGraspInfo                [IN OUT]      ץȡ��Ϣ����
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

*  @fn     MV_STA_GetGraspInfo()
*  @brief  Get grasp information data in chunkdata   Corresponding type STC_3D_Profile_GraspInfo can be called
*  @param  DataObject                 [IN]           data object
*  @param  pnGraspInfo               [IN OUT]       graspinfo data
*  @return Success, return MV_STA_OK. Failure, return error code
************************************************************************/
MV_STA_API int __stdcall    MV_STA_GetGraspInfo( IN STC_Object DataObject, IN OUT STC_GRASP_INFO  * pnGraspInfo);

/************************************************************************
*  @fn     MV_STA_DisplayRgbdMap()
*  @brief  RGBDͼ��Ⱦ  ֧��RGBD���STC_PixelType_Gvsp_Rgbd_C16����
*  @param  handle                 [IN]          �����ַ
*  @param  pstImage               [IN]          RGBDͼ����
*  @param  pstDisplayExInfo       [IN]          ��Ⱦ��չ��Ϣ
*  @param  hWnd                   [IN]          ��Ⱦ���ھ��
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

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
// ���ͼת����ͼ ��֧��Mono16/C16/C32���ݡ�������ӿڵ���˳�����£�
// 1. ע�����ͼת����ͼ�ص�����������X/Y������չϵ����
// 2. �������ͼ���ݣ�
// 3. ���е���ͼ�������ʱ���Զ�ִ��ע��ص�����
/************************************************************************/ 

/***********************************************************************
*  @fn          MV_STA_RegisterDepthToPointCloudCallBack()
*  @brief       ע�����ͼת����ͼ�ص�   ֧��Mono16/C16/C32����
*  @param       handle                 [IN]          ���
*  @param       cbOutputCallback       [IN]          �ص�����ָ��
*  @param       pUser                  [IN]          �û��Զ������
*  @param       nXScale                [IN]          X������չϵ��
*  @param       nYScale                [IN]          Y������չϵ��
*  @return �ɹ�������MV_STA_OK�����󣬷��ش�����

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
*  @brief  �������ͼ����  
*  @param  handle                 [IN]          �����ַ
*  @param  pstImage               [IN]          ���ͼ����
*  @return �ɹ�������MV_STA_OK�����󣬷��ش����� 

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