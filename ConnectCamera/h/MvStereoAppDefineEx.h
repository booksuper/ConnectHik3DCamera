/***************************************************************************************************
*
* 版权信息：版权所有 (c) 2019, 杭州海康机器人技术有限公司, 保留所有权利
*
* 文件名称：MvStereoAppDefineEx.h
* 摘    要: 立体相机SDK，拓展结构体定义
*
* 当前版本：2.1.0
* 作    者: 机器视觉SDK团队
* 日    期：2019.12.1
* 备    注：新建
****************************************************************************************************/

#ifndef _MV_STA_ERROR_DEFINE_EX_H_
#define _MV_STA_ERROR_DEFINE_EX_H_

#include "MvStereoAppDefine.h"

// 最大类型个数(适用于枚举类型)
#define MV_STA_MAX_XML_SYMBOLIC_NUM          64
// Enum类型值
typedef struct _MV_STA_ENUMVALUE_T
{
    unsigned int    nCurValue;                                          // 当前值
    unsigned int    nSupportedNum;                                      // 有效数据个数
    unsigned int    nSupportValue[MV_STA_MAX_XML_SYMBOLIC_NUM];  // 支持的枚举类型

    unsigned int    nReserved[4];                                       // 保留字节
}MV_STA_ENUMVALUE;

// Int类型值
typedef struct _MV_STA_INTVALUE_T
{
    int64_t    nCurValue;                               // 当前值
    int64_t    nMax;                                    // 最大值
    int64_t    nMin;                                    // 最小值
    int64_t    nInc;                                    // 增量值

    unsigned int    nReserved[16];                      // 保留字节
}MV_STA_INTVALUE;


// Float类型值
typedef struct _MV_STA_FLOATVALUE_T
{
    float           fCurValue;                          // 当前值
    float           fMax;                               // 最大值
    float           fMin;                               // 最小值

    unsigned int    nReserved[4];                       // 保留字节
}MV_STA_FLOATVALUE;

// String类型值
typedef struct _MV_STA_STRINGVALUE_T
{
    char            chCurValue[256];                    // 当前值

    int64_t         nMaxLength;                         // 最大长度
    unsigned int    nReserved[2];                       // 保留字节
}MV_STA_STRINGVALUE;



// 节点访问模式
enum MV_STA_XML_AccessMode
{
    MV_STA_AM_NI,                                // 节点未实现
    MV_STA_AM_NA,                                // 节点不可达
    MV_STA_AM_WO,                                // 节点只写
    MV_STA_AM_RO,                                // 节点只读
    MV_STA_AM_RW,                                // 节点可读可写
    MV_STA_AM_Undefined,                         // 节点未定义
    MV_STA_AM_CycleDetect,                       // 节点需周期检测
};

// 文件存取
typedef struct _MV_STA_FILE_ACCESS_T
{
    const char * pUserFileName;                         // 用户文件名
    const char * pDevFileName;                          // 设备文件名

    unsigned int    nReserved[32];                      // 预留字节
}MV_STA_FILE_ACCESS;

// 文件存取进度
typedef struct _MV_STA_FILE_ACCESS_PROGRESS_T
{
    int64_t nCompleted;                                 // 已完成的长度
    int64_t nTotal;                                     // 总长度

    unsigned int    nReserved[8];                       // 预留字节
}MV_STA_FILE_ACCESS_PROGRESS;


#endif //_MV_STA_ERROR_DEFINE_EX_H_
