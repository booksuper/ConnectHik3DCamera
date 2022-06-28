/***************************************************************************************************
*
* ��Ȩ��Ϣ����Ȩ���� (c) 2019, ���ݺ��������˼������޹�˾, ��������Ȩ��
*
* �ļ����ƣ�MvStereoAppDefineEx.h
* ժ    Ҫ: �������SDK����չ�ṹ�嶨��
*
* ��ǰ�汾��2.1.0
* ��    ��: �����Ӿ�SDK�Ŷ�
* ��    �ڣ�2019.12.1
* ��    ע���½�
****************************************************************************************************/

#ifndef _MV_STA_ERROR_DEFINE_EX_H_
#define _MV_STA_ERROR_DEFINE_EX_H_

#include "MvStereoAppDefine.h"

// ������͸���(������ö������)
#define MV_STA_MAX_XML_SYMBOLIC_NUM          64
// Enum����ֵ
typedef struct _MV_STA_ENUMVALUE_T
{
    unsigned int    nCurValue;                                          // ��ǰֵ
    unsigned int    nSupportedNum;                                      // ��Ч���ݸ���
    unsigned int    nSupportValue[MV_STA_MAX_XML_SYMBOLIC_NUM];  // ֧�ֵ�ö������

    unsigned int    nReserved[4];                                       // �����ֽ�
}MV_STA_ENUMVALUE;

// Int����ֵ
typedef struct _MV_STA_INTVALUE_T
{
    int64_t    nCurValue;                               // ��ǰֵ
    int64_t    nMax;                                    // ���ֵ
    int64_t    nMin;                                    // ��Сֵ
    int64_t    nInc;                                    // ����ֵ

    unsigned int    nReserved[16];                      // �����ֽ�
}MV_STA_INTVALUE;


// Float����ֵ
typedef struct _MV_STA_FLOATVALUE_T
{
    float           fCurValue;                          // ��ǰֵ
    float           fMax;                               // ���ֵ
    float           fMin;                               // ��Сֵ

    unsigned int    nReserved[4];                       // �����ֽ�
}MV_STA_FLOATVALUE;

// String����ֵ
typedef struct _MV_STA_STRINGVALUE_T
{
    char            chCurValue[256];                    // ��ǰֵ

    int64_t         nMaxLength;                         // ��󳤶�
    unsigned int    nReserved[2];                       // �����ֽ�
}MV_STA_STRINGVALUE;



// �ڵ����ģʽ
enum MV_STA_XML_AccessMode
{
    MV_STA_AM_NI,                                // �ڵ�δʵ��
    MV_STA_AM_NA,                                // �ڵ㲻�ɴ�
    MV_STA_AM_WO,                                // �ڵ�ֻд
    MV_STA_AM_RO,                                // �ڵ�ֻ��
    MV_STA_AM_RW,                                // �ڵ�ɶ���д
    MV_STA_AM_Undefined,                         // �ڵ�δ����
    MV_STA_AM_CycleDetect,                       // �ڵ������ڼ��
};

// �ļ���ȡ
typedef struct _MV_STA_FILE_ACCESS_T
{
    const char * pUserFileName;                         // �û��ļ���
    const char * pDevFileName;                          // �豸�ļ���

    unsigned int    nReserved[32];                      // Ԥ���ֽ�
}MV_STA_FILE_ACCESS;

// �ļ���ȡ����
typedef struct _MV_STA_FILE_ACCESS_PROGRESS_T
{
    int64_t nCompleted;                                 // ����ɵĳ���
    int64_t nTotal;                                     // �ܳ���

    unsigned int    nReserved[8];                       // Ԥ���ֽ�
}MV_STA_FILE_ACCESS_PROGRESS;


#endif //_MV_STA_ERROR_DEFINE_EX_H_
