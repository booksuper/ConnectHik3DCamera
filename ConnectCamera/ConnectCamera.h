#pragma once
#include <vtkAutoInit.h>//������ͷ�ļ���Ϊ�˰�ͼ����ʾ��qvtkqidget��
#include <vtkRenderWindow.h>
#include <QtWidgets/QMainWindow>
#include "ui_ConnectCamera.h"
#include <qmessagebox.h>
//#include<Windows.h>
#include <afx.h>//ʹ��cstring����
#include <MvStereoAppCtrl.h>
#include <MvStereoAppCtrlEx.h>
#include <MvStereoAppDefine.h>
#include <MvStereoAppDefineEx.h>
#include <MvStereoAppPixelType.h>
#include <string.h>
#include <synchapi.h>//�첽�߳�
#include <handleapi.h>//���
#include <atltime.h>//ϵͳʱ��
#include <afxmt.h>//mfc�й��ڶ��̵߳�ͷ�ļ�������������CCriticalSection,�����������window.h,����������ע�͵�����Ȼ����
#include<pcl/common/common.h>
//�����������max�Ķ����ͻ����pclio�ж�����max��c++������һ��ȫ��max���壬��ͻ����
//�����������Ԥ���������������NOMINMAX
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
	//���ڴ洢ͼ����Զ���ṹ��
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
	//�������
	void connectCam();
	//��ȡ�������
	void getParameter();
	//�����������
	void setParameter();
	//��ʼ�ɼ�,������Ⱦ�߳�ProcessThread
	void startGrab();
	//��Ⱦ�̣߳�������display
	static void * __stdcall ProcessThread(void* pUser);
	//ֹͣ�ɼ�
	void stopGrab();
	//��ʾͼ��,������draw��ConvertRGB8Planner2RGB8Packed,������ʾͼ�񣬻������˺������������ply�ļ��������ļ�
	int Display(void* handle, void* hWnd, STC_DATA_IMAGE* pstDisplayImage);
	//��ȡ�ؼ����ݵĺ�������һ��
	int getData(void* handle, STC_DATA_IMAGE* pstDisplayImage);
	//����ͼ��
	//int Draw(MV_CODEREADER_DRAW_PARAM* pstParam);
	//ת��rgb
	bool ConvertRGB8Planner2RGB8Packed(const unsigned char* pSrcData,int nWidth,int nHeight,unsigned char* pDstData);

	//��ʼ����Դ
	int InitResources();
	//����ʼ����Դ
	void DeInitResources();
	//����Ϊply��������display
	void savePly();
	//�ر��豸
	void closeDevice();
	//��ȡ�ַ���Ϊ���ƶ���,һ��ֻ�ܶ�һ������
    static void txt2pc(string txt,pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_);
	//��ʾ����ͼ
	void showPc();
	//txtת���ƣ����Ե��Ӷ�������
	static void txt2MutiPc(string txt,float step,pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_);
	
	//
	void showPcThread();
	//�رյ���ͼ
	void closePc();
	//����pcd�ļ�
	void savePcd();
	//ִ��һ��
	void doOnce();
	//�Զ�ִ��
	void autoDo();
	//�Զ�ִ�а�ť�����ִ�еĺ���
	void autoDo_button();
	//��ѡ��״̬�ı亯��,����checkBoxState�������ֵ�븴ѡ��״̬ͬ��
	void checkbox_autodo();
	//�̺߳�����һֱ���Ͳɼ��ź�
	void autoDo_CallBack();
	//�л��ڴ���ģʽ
	void switchInside();
	//�л�Ϊ����ģʽ
	void switchSoft();
private:
	Ui::ConnectCameraClass ui;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	MV_STEREOCAM_NET_INFO_LIST  m_stDeviceInfoList;                 // �豸��Ϣ�б�
	MV_STEREOCAM_NET_INFO       m_stDeviceInfo;                     // �豸��Ϣ
	void*                   m_handle;                           // �豸���
	void*                   m_hWndDisplay;                      // ��ʾ���ھ��
	bool                    m_bConnect;                         // �Ƿ��豸������
	bool                    m_bStartJob;                        // �Ƿ����߳��ѿ���
    #define IGNORE              0       // Ignore signal
    #define INFINITE            0xFFFFFFFF  // Infinite timeout




    #define BYTE_ALIGN              4                 // 4�ֽڶ���
    #define EXPOSURE_TIME           "ExposureTime"
    #define GAIN                    "Gain"
    #define ACQUISITION_FRAME_RATE  "AcquisitionFrameRate"

    #define Camera_Width             "Width"
    #define Camera_Height            "Height"

    #define IMAGE_NAME_LEN          64

    #define  PLY_IMAG_MAX_LEN  1024*1020*20

	void* hProcessThread = NULL;  //��Ⱦ�߳�,ָ���ʼ������Ȼ����
	STC_DATA_IMAGE          m_stImageInfo;        //ͼƬ������Ϣ
	int                     m_MaxImageSize;                     // ͼ�����ߴ�
	unsigned char*          m_pcDataBuf;                        // �洢ͼ������

	// ply �洢ͼƬ�ռ�
	int                     m_MaxPlyImageSize;                     // plyͼ�����ߴ�
	unsigned char*          m_pcPlyDataBuf;                        // ply�洢ͼ������
	unsigned char*          m_pcRGBDataBuf;                     //RGBͼ��ͼ������
	CCriticalSection        m_criSection;                       // �ٽ���
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
	static int pc_num;//������¼�ǵڼ������ƣ���txt2MutiPc�������õ�,���������ʼ��
	static int checkBoxState;//������¼��ѡ���״̬
	static int autodo_thread_over;//�ɼ����ݵ��߳̽�����־
};
