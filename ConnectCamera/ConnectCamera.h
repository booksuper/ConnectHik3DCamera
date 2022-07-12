#pragma once
#include <vtkAutoInit.h>//这两个头文件是为了把图像显示在qvtkqidget中
#include <vtkRenderWindow.h>
#include <QtWidgets/QMainWindow>
#include "ui_ConnectCamera.h"
#include <qmessagebox.h>
//#include<Windows.h>
#include <afx.h>//使用cstring必须
#include <MvStereoAppCtrl.h>
#include <MvStereoAppCtrlEx.h>
#include <MvStereoAppDefine.h>
#include <MvStereoAppDefineEx.h>
#include <MvStereoAppPixelType.h>
#include <string.h>
#include <synchapi.h>//异步线程
#include <handleapi.h>//句柄
#include <atltime.h>//系统时间
#include <afxmt.h>//mfc中关于多线程的头文件，本例中用了CCriticalSection,这里面包含了window.h,所以在上面注释掉，不然报错
#include<pcl/common/common.h>
//在这里出现了max的定义冲突错误（pclio中定义了max，c++本身有一个全局max定义，冲突报错）
//解决方法是在预处理器定义中添加NOMINMAX
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <sstream>
#include <vector>
#include <thread>


using namespace std;

class ConnectCamera : public QMainWindow
{
	Q_OBJECT

public:
	ConnectCamera(QWidget *parent = Q_NULLPTR);
	//用于存储图像的自定义结构体
	typedef struct _MV_CODEREADER_DRAW_PARAM_
	{
		HDC hDC;
		unsigned char *pData;

		int nImageWidth;
		int nImageHeight;

		int nWndRectWidth;
		int nWndRectHeight;
		int nDstX;
		int nDstY;

	}MV_CODEREADER_DRAW_PARAM;
	void findCam();
	//连接相机
	void connectCam();
	//获取相机参数
	void getParameter();
	//设置相机参数
	void setParameter();
	//开始采集,依赖渲染线程ProcessThread
	void startGrab();
	//渲染线程，依赖于display
	static void * __stdcall ProcessThread(void* pUser);
	//停止采集
	void stopGrab();
	//显示图像,依赖于draw，ConvertRGB8Planner2RGB8Packed,除了显示图像，还缓存了后续用来保存的ply文件和其他文件
	int Display(void* handle, void* hWnd, STC_DATA_IMAGE* pstDisplayImage);
	//获取关键数据的函数，试一试
	int getData(void* handle, STC_DATA_IMAGE* pstDisplayImage);
	//绘制图像
	//int Draw(MV_CODEREADER_DRAW_PARAM* pstParam);
	//转换rgb
	bool ConvertRGB8Planner2RGB8Packed(const unsigned char* pSrcData,int nWidth,int nHeight,unsigned char* pDstData);

	//初始化资源
	int InitResources();
	//反初始化资源
	void DeInitResources();
	//保存为ply，依赖于display
	void savePly();
	//关闭设备
	void closeDevice();
	//读取字符串为点云对象,一次只能读一条点云
    static void txt2pc(string txt,pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_);
	//显示点云图
	void showPc();
	//txt转点云，可以叠加多条点云
	static void txt2MutiPc(string txt,float step,pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_);
	
	//
	void showPcThread();
	//关闭点云图
	void closePc();
	//保存pcd文件
	void savePcd();
	//执行一次
	void doOnce();
	//自动执行
	void autoDo();
	//自动执行按钮点击后执行的函数
	void autoDo_button();
	//复选框状态改变函数,控制checkBoxState这个变量值与复选框状态同步
	void checkbox_autodo();
	//线程函数，一直发送采集信号
	void autoDo_CallBack();
	//切换内触发模式
	void switchInside();
	//切换为软触发模式
	void switchSoft();
private:
	Ui::ConnectCameraClass ui;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	MV_STEREOCAM_NET_INFO_LIST  m_stDeviceInfoList;                 // 设备信息列表
	MV_STEREOCAM_NET_INFO       m_stDeviceInfo;                     // 设备信息
	void*                   m_handle;                           // 设备句柄
	void*                   m_hWndDisplay;                      // 显示窗口句柄
	bool                    m_bConnect;                         // 是否设备已连接
	bool                    m_bStartJob;                        // 是否工作线程已开启
    #define IGNORE              0       // Ignore signal
    #define INFINITE            0xFFFFFFFF  // Infinite timeout




    #define BYTE_ALIGN              4                 // 4字节对齐
    #define EXPOSURE_TIME           "ExposureTime"
    #define GAIN                    "Gain"
    #define ACQUISITION_FRAME_RATE  "AcquisitionFrameRate"

    #define Camera_Width             "Width"
    #define Camera_Height            "Height"

    #define IMAGE_NAME_LEN          64

    #define  PLY_IMAG_MAX_LEN  1024*1020*20

	void* hProcessThread = NULL;  //渲染线程,指针初始化，不然报错
	STC_DATA_IMAGE          m_stImageInfo;        //图片参数信息
	int                     m_MaxImageSize;                     // 图像最大尺寸
	unsigned char*          m_pcDataBuf;                        // 存储图像数据

	// ply 存储图片空间
	int                     m_MaxPlyImageSize;                     // ply图像最大尺寸
	unsigned char*          m_pcPlyDataBuf;                        // ply存储图像数据
	unsigned char*          m_pcRGBDataBuf;                     //RGB图像图像数据
	CCriticalSection        m_criSection;                       // 临界区
	BITMAPINFO*             m_bBitmapInfo;
	

	typedef int                 INT;
	typedef unsigned int        UINT;
	typedef unsigned int        *PUINT;

	//  Code Page Default Values.
	//  Please Use Unicode, either UTF-16 (as in WCHAR) or UTF-8 (code page CP_ACP)
	//
    #define CP_ACP                    0           // default to ANSI code page
    #define CP_OEMCP                  1           // default to OEM  code page
    #define CP_MACCP                  2           // default to MAC  code page
    #define CP_THREAD_ACP             3           // current thread's ANSI code page
    #define CP_SYMBOL                 42          // SYMBOL translations

    #define CP_UTF7                   65000       // UTF-7 translation
    #define CP_UTF8                   65001       // UTF-8 translation
	static int pc_num;//用来记录是第几个点云，在txt2MutiPc函数中用到,得在类外初始化
	static int checkBoxState;//用来记录复选框的状态
	static int autodo_thread_over;//采集数据的线程结束标志
};
