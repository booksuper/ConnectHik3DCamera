#include "ConnectCamera.h"
//这三行是对vtk初始化，不然在显示的时候会报错
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

int ConnectCamera::pc_num = 0;//点云数量
int ConnectCamera::checkBoxState = 0;//复选框状态标志
int ConnectCamera::autodo_thread_over = 1;//采集数据线程结束标志
ConnectCamera::ConnectCamera(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
	viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	
	ui.pushButton_close->setEnabled(false);
	ui.pushButton_start->setEnabled(false);
	ui.pushButton_stop->setEnabled(false);
	ui.pushButton_savePly->setEnabled(false);
	ui.pushButton_savePcd->setEnabled(false);
	ui.pushButton_connect->setEnabled(false);
	//查找设备
	connect(ui.pushButton_findCam, &QPushButton::clicked, this, &ConnectCamera::findCam);
	//连接相机
	connect(ui.pushButton_connect, &QPushButton::clicked, this, &ConnectCamera::connectCam);
	//关闭设备
	connect(ui.pushButton_close, &QPushButton::clicked, this, &ConnectCamera::closeDevice);
	//获取参数
	connect(ui.pushButton_getPara, &QPushButton::clicked, this, &ConnectCamera::getParameter);
	//设置参数
	connect(ui.pushButton_setPara, &QPushButton::clicked, this, &ConnectCamera::setParameter);
	//开始采集
	connect(ui.pushButton_start, &QPushButton::clicked, this, &ConnectCamera::startGrab);
	//停止采集
	connect(ui.pushButton_stop, &QPushButton::clicked, this, &ConnectCamera::stopGrab);
	//保存为ply
	connect(ui.pushButton_savePly, &QPushButton::clicked, this, &ConnectCamera::savePly);
	//显示点云图
	connect(ui.pushButton_showImg, &QPushButton::clicked, this, &ConnectCamera::showPc);
	//关闭点云图
	connect(ui.pushButton_closeImg, &QPushButton::clicked, this, &ConnectCamera::closePc);
	//保存pcd文件
	connect(ui.pushButton_savePcd, &QPushButton::clicked, this, &ConnectCamera::savePcd);
	//切换为内触发模式
	connect(ui.pushButton_switch, &QPushButton::clicked, this, &ConnectCamera::switchInside);
	//软触发模式下执行一次
	connect(ui.pushButton_doOnce, &QPushButton::clicked, this, &ConnectCamera::doOnce);
	//软触发模式下自动执行
	//clicked信号是你只要点击了复选框就会发送信号，这意味着当你取消勾选的时候也会发送信号
	//所以另外设置一个按钮，通过点击这个按钮来实现启动采集的线程
	connect(ui.pushButton_autodo, &QPushButton::clicked, this, &ConnectCamera::autoDo_button);
	//复选框状态
	connect(ui.checkBox_autoDo, &QCheckBox::clicked, this, &ConnectCamera::checkbox_autodo);
	//切换为软触发模式
	connect(ui.pushButton_switch_soft, &QPushButton::clicked, this, &ConnectCamera::switchSoft);


}



//查询设备
void ConnectCamera::findCam()
{
	int nRet = MV_STA_OK;
	
	string cstrInfo;

	// 将存储设备的结构体初始化，全都赋予0。
	//memset功能一般用来将申请的内存初始化，第一个参数是要初始化的变量，第二个是用什么值进行初始化，一般是0，第三个是初始化的大小
	memset(&m_stDeviceInfoList, 0, sizeof(MV_STEREOCAM_NET_INFO_LIST));
	//枚举设备信息
	nRet = MV_STA_EnumStereoCam(&m_stDeviceInfoList);//枚举立体相机
	if (MV_STA_OK != nRet)
	{
		//cstrInfo.Format(_T("Enum Device failed! err code:%#x"), nRet);
		//MessageBox(cstrInfo);
		QMessageBox::about(this, "Error!", "Enum Device failed!");
		return;
	}
	
	// 显示查找到的设备信息,暂时只有一台设备，可以不用循环
	//设备的ID信息，总共有四段，ip4代表最左边的
		int nIp1 = m_stDeviceInfoList.pDeviceInfo[0]->nCurrentIp & 0xff;
		int nIp2 = (m_stDeviceInfoList.pDeviceInfo[0]->nCurrentIp & 0xff00) >> 8;
		int nIp3 = (m_stDeviceInfoList.pDeviceInfo[0]->nCurrentIp & 0xff0000) >> 16;
		int nIp4 = (m_stDeviceInfoList.pDeviceInfo[0]->nCurrentIp & 0xff000000) >> 24;
		QString info = "ID:" + QString::number(nIp4) + "." + QString::number(nIp3) + "." + QString::number(nIp2) + "." + QString::number(nIp1);
		ui.lineEdit_CamInfo->setText(info);
		ui.pushButton_connect->setEnabled(true);
		ui.pushButton_findCam->setEnabled(false);

	
}

void ConnectCamera::connectCam()
{
	int nRet = MV_STA_OK;
	string cstrInfo;

	//UpdateData(TRUE);//暂时找不到这个函数的定义

	if (true == m_bConnect)
	{
		QMessageBox::about(this, "warning!", "The camera is already connect");
		
		return;
	}

	if (0 == m_stDeviceInfoList.nDeviceNum)
	{
		QMessageBox::about(this, "warning!", "Please discovery device first");
		return;
	}

	if (m_handle)
	{
		MV_STA_DestroyHandle(m_handle);
		m_handle = NULL;
	}

	// 获取当前选择的设备信息,只有一台设备，所以不需要选择，索引就是0
	
	memcpy(&m_stDeviceInfo, m_stDeviceInfoList.pDeviceInfo[0], sizeof(MV_STEREOCAM_NET_INFO));


	// 创建设备句柄
	nRet = MV_STA_CreateHandleByCameraInfo(&m_handle, m_stDeviceInfoList.pDeviceInfo[0]);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Create handle failed! err code:" + QString::number(nRet));
		
		return;
	}

	//开启设备，将获得的相机地址给m_handle
	nRet = MV_STA_OpenDevice(m_handle);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Open device failed! err code:" + QString::number(nRet));
		
		return;
	}

	// 获取参数,暂时没有实现
	getParameter();
	m_bConnect = true;

	// 初始化必要的资源
	InitResources();
	//连接上之后，连接按钮应该别禁用
	ui.pushButton_connect->setEnabled(false);
	ui.pushButton_close->setEnabled(true);
	ui.pushButton_start->setEnabled(true);
	ui.pushButton_stop->setEnabled(false);
	ui.pushButton_savePly->setEnabled(false);
	ui.pushButton_savePcd->setEnabled(false);
	

	
}
//获取参数
void ConnectCamera::getParameter()
{
	int nRet = MV_STA_OK;
	//CString cstrInfo;

	// 获取曝光时间
	float fExposureTime = 0.0f;
	MV_STA_FLOATVALUE stParam;
	memset(&stParam, 0, sizeof(MV_STA_FLOATVALUE));
	//获取相机的曝光参数，这个值是你在相机的软件中设置的，第二个参数指定获取曝光
	nRet = MV_STA_GetFloatValue(m_handle, EXPOSURE_TIME, &stParam);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Set exposure time failed! err code:" + QString::number(nRet));
		
		
	}
	else
	{
		fExposureTime = stParam.fCurValue;
		//将曝光值赋予文本控件
		ui.lineEdit_expo->setText(QString::number(fExposureTime));
		
	}

	// 获取增益
	float fGain = 0.0f;
	memset(&stParam, 0, sizeof(MV_STA_FLOATVALUE));
	nRet = MV_STA_GetFloatValue(m_handle, GAIN, &stParam);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Get gain failed! err code:" + QString::number(nRet));
		
	}
	else
	{
		fGain = stParam.fCurValue;
		ui.lineEdit_gain->setText(QString::number(fGain));
	}

	// 获取帧率
	float fFrameRate = 0.0f;
	memset(&stParam, 0, sizeof(MV_STA_FLOATVALUE));
	nRet = MV_STA_GetFloatValue(m_handle, ACQUISITION_FRAME_RATE, &stParam);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Get acquisition rate failed! err code:" + QString::number(nRet));
		
	}
	else
	{
		fFrameRate = stParam.fCurValue;
		ui.lineEdit_frame->setText(QString::number(fFrameRate));
	}

	
}
//设置参数
void ConnectCamera::setParameter()
{
	
	bool bHasError = false;

	// TODO: Add your control notification handler code here
	int nRet = MV_STA_OK;
	

	// 设置曝光时间
	float fExposureTime = 0.0f;
	fExposureTime = ui.lineEdit_expo->text().toFloat();
	
	nRet = MV_STA_SetFloatValue(m_handle, EXPOSURE_TIME, fExposureTime);
	if (MV_STA_OK != nRet)
	{
		bHasError = true;
		QMessageBox::about(this, "warning!", "Set exposure time failed! err code:" + QString::number(nRet));
		
	}

	// 设置增益
	float fGain = 0.0f;
	fGain = ui.lineEdit_gain->text().toFloat();
	
	nRet = MV_STA_SetFloatValue(m_handle, GAIN, fGain);
	if (MV_STA_OK != nRet)
	{
		bHasError = true;
		QMessageBox::about(this, "warning!", "Set gain failed! err code:" + QString::number(nRet));
		
	}

	// 设置帧率
	float fFrameRate = 0.0f;
	fFrameRate = ui.lineEdit_frame->text().toFloat();
	
	nRet = MV_STA_SetFloatValue(m_handle, ACQUISITION_FRAME_RATE, fFrameRate);
	if (MV_STA_OK != nRet)
	{
		bHasError = true;
		QMessageBox::about(this, "warning!", "Set acquisition rate failed! err code:" + QString::number(nRet));
		
	}

	if (false == bHasError)
	{
		QMessageBox::about(this, "warning!", "Set Para Success!" );
		
	}

}
#if 1
//开始采集
void ConnectCamera::startGrab()
{
	int nRet = MV_STA_OK;
	

	if (NULL != hProcessThread)
	{
		m_bStartJob = false;
		// 等待线程完成，如果是多线程的，需要调用 WaitForMultipleObjects
		WaitForSingleObject(hProcessThread, INFINITE);
		//CloseHandle是关闭线程句柄,用来释放线程资源的,不是终止线程的
		// 做完一次记得释放一次线程资源
		CloseHandle(hProcessThread);
		hProcessThread = NULL;
	}


	m_bStartJob = true;
	// 创建接收 处理线程
	/*CreateThread是c++中创建线程的函数，其中第一个参数安全设置，第二个：堆栈大小，第三个，入口函数
	第四个，入口函数的参数，这个是类内成员函数，本身函数有一个void*指针，这里相当于把当前窗口的主线程
	地址当做参数传递进去了。第五个启动选项。
	ProcessThread其实是回调函数，负责采集数据和
	将最原始的数据转为ply、pcd等各种标准格式数据*/
	hProcessThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProcessThread, this, 0, NULL);
	if (NULL == hProcessThread)
	{
		QMessageBox::about(this, "warning!", "Create proccess Thread failed" );
		
	}


	// 开始工作流程
	nRet = MV_STA_Start(m_handle);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Start grabbing failed! err code:" + QString::number(nRet));
		
		return;
	}

	ui.pushButton_close->setEnabled(false);
	ui.pushButton_start->setEnabled(false);
	ui.pushButton_stop->setEnabled(true);
	ui.pushButton_savePly->setEnabled(true);
	ui.pushButton_savePcd->setEnabled(true);
	ui.pushButton_connect->setEnabled(false);
	ui.pushButton_showImg->setEnabled(true);
	ui.pushButton_closeImg->setEnabled(false);

}
//渲染线程，__stdcall是参数调用约定，这种约定意味着参数从右向左压入堆栈，等
//这里拿到关键数据stImg
//回调函数，负责采集原始数据，并且把原始数据转成ply、pcd等标准数据。里面有个while循环，会一直采集

//回调函数整个步骤：首先从设备中采集最原始的数据ori，
//然后使用getData函数将其转为标准图像数据stImg
//接着使用MV_STA_SavePly函数将stImg转为stPlyImage,因为stPlyImage的数据实际上是unsigned char类型的
//所以将其强转成字符串，最后再自己写一个字符串转点云的函数txt2pc

void * __stdcall ConnectCamera::ProcessThread(void * pUser)
{
	int nRet = MV_STA_OK;
	//这里应该把当前的类指针传递进来
	ConnectCamera* pThis = (ConnectCamera*)pUser;
	if (NULL == pThis)
	{
		return NULL;
	}


	STC_DataSet DataSet = NULL;
	STC_Object DataObj;
	unsigned int nResultCount = 0;
	unsigned int nMsgType;
	int outnum = 1;
	//只要不停止采集，这个循环就会一直采
	while (pThis->m_bStartJob)
	{
		// 获取图像数据

		nRet = MV_STA_ReceiveDataTimeout(pThis->m_handle, &DataSet, 100);
		if ((MV_STA_OK == nRet) &&
			(NULL != DataSet) && pThis->m_bStartJob)  //避免帧率过高，即使停流也在处理数据
		{

			try
			{
				nResultCount = MV_STA_DataSetCount(DataSet);

				int index = 0;
				for (index = 0; index < nResultCount; index++)
				{
					DataObj = MV_STA_DataSetAt(DataSet, index);

					nMsgType = MV_STA_DataMsgType(DataObj);
					if (0 != nRet)
					{
						printf("MV_STA_DataMsgType failed, errcode (%#x)!\r\n", nRet);
						throw nRet;
					}
					else
					{
						printf("MV_STA_DataMsgType  value (%d) success: 0_raw 1_death !\r\n", nMsgType);
					}
					//这一段拿到重要数据stImg
					if (STC_DATA_MSG_TYPE_IMG_RAW == nMsgType)
					{
						STC_DATA_IMAGE stImg = { 0 };
						//拿到三维相机取流的数据stImg
						nRet = MV_STA_GetImage(DataObj, &stImg);
						if (0 != nRet)
						{
							printf("MV_STA_GetImage failed, errcode (%#x)!\r\n", nRet);
							throw nRet;
						}
						else
						{
							printf("MV_STA_GetImage success: framenum (%d) hight(%d) width(%d)  len (%d)!\r\n", stImg.nFrameNum, stImg.nHeight, stImg.nWidth, stImg.nFrameLen);


							//不仅用来显示图像，同时还为后面保存图像提前保存m_stImageInfo和m_pcDataBuf，不能注释
							//传进来的stImg是原始数据，可以自己写个函数，只获取用于保存点云的数据，不使用这里面的显示功能
							//尽量精简代码
							//用getData这个函数代替display，将显示点云和提取数据分离开
							//假如成功，就可以不用display函数以及与其相关联的draw函数和convert函数，可以极大精简代码
							//还可以删除hdc显示图像的代码，然后再用pcl的库对拿到的点云进行显示
							//2022.1.6，测试成功
							//先从设备中取得最原始的数据，并将其转成标准图片数据
							nRet = pThis->getData(pThis->m_handle, &stImg);
							//nRet = pThis->Display(pThis->m_handle, pThis->m_hWndDisplay, &stImg);
							
							//将源数据转为点云对象
							int nRet = MV_STA_OK;
							QString  cstrInfo = "";

							// 判断是否开始取流
							if (!pThis->m_bConnect)
							{
								QMessageBox::about(pThis, "warning!", "No camera Connected!");

							}

							if (!pThis->m_bStartJob)
							{
								QMessageBox::about(pThis, "warning!", "The camera is not startJob!");

							}

							// 判断是否有有效数据
							//这里的m_stImageInfo是在display函数中缓存的，所以display函数不能完全注释，但是可以把显示部分进行改造
							//原始的数据保存在m_pcDataBuf，以字节形式
							if (NULL == pThis->m_pcDataBuf)
							{
								QMessageBox::about(pThis, "warning!", "No data，Save PLY failed!");

							}

							if (0 == pThis->m_stImageInfo.nFrameLen)
							{
								QMessageBox::about(pThis, "warning!", "No Data, save nothing !");

							}

							//本例用的三维激光扫描仪的格式是Gvsp_Coord3D_ABC16或者Gvsp_Coord3D_ABC32
							if ((STC_PixelType_Gvsp_Coord3D_ABC16 == pThis->m_stImageInfo.enPixelType) ||
								(STC_PixelType_Gvsp_Coord3D_ABC32 == pThis->m_stImageInfo.enPixelType))
							{
								pThis->m_criSection.Lock();

								try
								{


									// 直接save
									STC_IMG_SAVE_ABC16_TO_PLY_PARAM  stPlyImage = { 0 };
									stPlyImage.nLinePntNum = pThis->m_stImageInfo.nWidth;
									stPlyImage.nLineNum = pThis->m_stImageInfo.nHeight;

									stPlyImage.pSrcData = pThis->m_stImageInfo.pData;
									stPlyImage.nSrcDataLen = pThis->m_stImageInfo.nFrameLen;
									stPlyImage.enSrcPixelType = pThis->m_stImageInfo.enPixelType;


									int nLenTmp = (stPlyImage.nLinePntNum *  stPlyImage.nLineNum *(16 * 3 + 4)) + 2048;

									if (pThis->m_MaxPlyImageSize < nLenTmp)
									{
										if (pThis->m_pcPlyDataBuf)
										{
											free(pThis->m_pcPlyDataBuf);
										}

										pThis->m_pcPlyDataBuf = (unsigned char*)malloc(nLenTmp);
										if (NULL == pThis->m_pcDataBuf)
										{
											QMessageBox::about(pThis, "warning!", "malloc failed");

											nRet = MV_STA_E_RESOURCE;
											throw nRet;
										}

										pThis->m_MaxPlyImageSize = nLenTmp;
										memset(pThis->m_pcPlyDataBuf, 0, pThis->m_MaxPlyImageSize);
									}


									stPlyImage.pDstBuf = pThis->m_pcPlyDataBuf;//(nLinePntNum * nLineNum * (16*3 + 4) + 2048)
									stPlyImage.nDstBufSize = pThis->m_MaxPlyImageSize;
									//这一句进行数据封装，将各种格式3D图转为ply格式
									//关键！将stImg数据封装成标准ply数据
									nRet = MV_STA_SavePly(pThis->m_handle, &stPlyImage);
									if (MV_STA_OK != nRet)
									{
										QMessageBox::about(pThis, "warning!", "MV_STA_SavePly failed");

										throw nRet;
									}
									//用pcl的函数保存ply文件
									//pcl::PointCloud<pcl::PointXYZ> * cloud (new pcl::PointCloud<pcl::PointXYZ>());
									/*pcl::PointCloud<pcl::PointXYZ> * cloud = NULL;
									cloud = (pcl::PointCloud<pcl::PointXYZ> *) malloc(stPlyImage.nDstBufLen);
									memset(cloud, 0, stPlyImage.nDstBufLen);
									memcpy(cloud, stPlyImage.pDstBuf, stPlyImage.nDstBufLen);
									pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_share = cloud->makeShared();
									pcl::io::savePLYFile("text.ply",*cloud_share);*/
									//更安全的一种方式,无效，因为点云指针不是pod类型，无法强制转换
									//虽然转换成功，但是数据是无法读取的，失败
									//pcl::PointCloud<pcl::PointXYZ> * pThing = static_cast<pcl::PointCloud<pcl::PointXYZ> *> (stPlyImage.pDstBuf);
									//pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
									/*这个方法成功,从源码上解析发现pDstBuf是unsigned char*类型的数据
									将这种类型的数据转为字符串比较容易*/
									//首先把void *强转为unsigned char *
									unsigned char * str = (unsigned char *)stPlyImage.pDstBuf;
									string res = "";
									//这一步关键，将unsigned char *转为字符串
									res.append(reinterpret_cast<const char*>(str));
									QString r = QString::fromStdString(res);
									//后续要自己写一个读取txt为点云对象的函数
									//ConnectCamera::txt2pc(res, pThis->cloud);
									//叠加多条点云
									ConnectCamera::txt2MutiPc(res, 100,pThis->cloud);

									//这个线程会不断执行，将可视化放在这试一试，测试之后会报错
									//还是另外开辟一个线程执行可视化
									//pThis->viewer->setBackgroundColor(0, 0, 0);
									//pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> render_color(pThis->cloud, "z");
									////pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color(pThis->cloud, 1, 0, 0);
									//pThis->viewer->addPointCloud(pThis->cloud, render_color, "cloud");
									//pThis->viewer->updatePointCloud(pThis->cloud, render_color, "cloud");
									//
									//pThis->ui.qvtkWidget->SetRenderWindow(pThis->viewer->getRenderWindow());
									//pThis->viewer->setupInteractor(pThis->ui.qvtkWidget->GetInteractor(), pThis->ui.qvtkWidget->GetRenderWindow());
									//pThis->ui.qvtkWidget->update();
									//pThis->viewer->removePointCloud("cloud");

								}
								catch (...)
								{
									pThis->m_criSection.Unlock();
									//MessageBox(cstrInfo);
									return NULL;
								}

								pThis->m_criSection.Unlock();
							}
							//else if ((STC_PixelType_Gvsp_Coord3D_ABC32f == m_stImageInfo.enPixelType) ||
							//	(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == m_stImageInfo.enPixelType) ||
							//	(STC_PixelType_Gvsp_Coord3D_AC32 == m_stImageInfo.enPixelType))
							//{

							//	m_criSection.Lock();

							//	try
							//	{
							//		// 点云图，转换为标准图
							//		STC_NORMALIZE_IMAGE stImage = { 0 };
							//		stImage.nWidth = m_stImageInfo.nWidth;
							//		stImage.nHeight = m_stImageInfo.nHeight;
							//		stImage.enSrcPixelType = m_stImageInfo.enPixelType;
							//		stImage.pData = m_pcDataBuf;
							//		stImage.nLen = m_stImageInfo.nFrameLen;

							//		stImage.enDstPixelType = STC_PixelType_Gvsp_Coord3D_ABC32;

							//		nRet = MV_STA_NormalizedPointCloudImage(m_handle, &stImage);
							//		if (MV_STA_OK != nRet)
							//		{

							//			cstrInfo = "MV_STA_NormalizedPointCloudImage failed";
							//			throw nRet;
							//		}

							//		// save it 
							//		STC_IMG_SAVE_ABC16_TO_PLY_PARAM  stPlyImage = { 0 };
							//		stPlyImage.nLinePntNum = stImage.nWidth;
							//		stPlyImage.nLineNum = stImage.nHeight;

							//		stPlyImage.pSrcData = stImage.pNormalizedData;
							//		stPlyImage.nSrcDataLen = stImage.nNormalizedLen;
							//		stPlyImage.enSrcPixelType = STC_PixelType_Gvsp_Coord3D_ABC32;
							//		int nLenTmp = (stPlyImage.nLinePntNum *  stPlyImage.nLineNum *(16 * 3 + 4)) + 2048;
							//		if (m_MaxPlyImageSize < nLenTmp)
							//		{
							//			if (m_pcPlyDataBuf)
							//			{
							//				free(m_pcPlyDataBuf);
							//			}
							//			m_pcPlyDataBuf = (unsigned char*)malloc(nLenTmp);
							//			if (NULL == m_pcDataBuf)
							//			{
							//				nRet = MV_STA_E_RESOURCE;
							//				cstrInfo = "malloc failed";
							//				throw nRet;
							//			}
							//			m_MaxPlyImageSize = nLenTmp;
							//			memset(m_pcPlyDataBuf, 0, m_MaxPlyImageSize);
							//		}
							//		stPlyImage.pDstBuf = m_pcPlyDataBuf;//(nLinePntNum * nLineNum * (16*3 + 4) + 2048)
							//		stPlyImage.nDstBufSize = m_MaxPlyImageSize;
							//		nRet = MV_STA_SavePly(m_handle, &stPlyImage);
							//		if (MV_STA_OK != nRet)
							//		{
							//			cstrInfo = "MV_STA_SavePly failed";
							//			throw nRet;
							//		}
							//		pfile = fopen(filename, "wb");
							//		if (pfile == NULL)
							//		{
							//			cstrInfo = "Open file failed";
							//			throw nRet;
							//		}
							//		fwrite(stPlyImage.pDstBuf, 1, stPlyImage.nDstBufLen, pfile);
							//		fclose(pfile);
							//		pfile = NULL;
							//	}
							//	catch (...)
							//	{
							//		m_criSection.Unlock();
							//		QMessageBox::about(this, "Warning", cstrInfo);
							//		return;
							//	}
							//	m_criSection.Unlock();
							//}
							/*else
							{
								cstrInfo = "Not support save ply file!";
								QMessageBox::about(this, "Warning", cstrInfo);
								return;
							}*/

							if (MV_STA_OK != nRet)
							{
								throw nRet;
							}
						}


					}
					//下面几段不是本相机需要使用的代码，可忽略
					else if (STC_3D_Profile_ExtendImg == nMsgType)
					{
						STC_EXTEND_IMAGE stExtendImage = { 0 };
						nRet = MV_STA_GetExtendImage(DataObj, &stExtendImage);
						if (0 != nRet)
						{
							printf("MV_STA_GetExtendImage failed, errcode (%#x)!\r\n", nRet);
							throw nRet;
						}
						else
						{
							printf("MV_STA_GetExtendImage success, nPixelFormat[%d] nWidth[%d] nHeight[%d]!\r\n", stExtendImage.nPixelFormat, stExtendImage.nWidth, stExtendImage.nHeight);
						}

						
					}
					else if (STC_3D_Profile_Count == nMsgType)
					{
						unsigned int  nProfileCount = 0;
						nRet = MV_STA_GetProfileCount(DataObj, &nProfileCount);
						if (0 != nRet)
						{
							printf("MV_STA_GetProfileCount failed, errcode (%#x)!\r\n", nRet);
							throw nRet;
						}
					}
					else if (STC_3D_Profile_LinePntNum == nMsgType)
					{
						unsigned int  nProfileLineNum = 0;
						nRet = MV_STA_GetProfileLinePntNum(DataObj, &nProfileLineNum);
						if (0 != nRet)
						{
							printf("MV_STA_GetProfileLinePntNum failed, errcode (%#x)!\r\n", nRet);
							throw nRet;
						}
					}
					else if (STC_3D_Profile_Intensity == nMsgType)
					{
						STC_PROFILE_INTENSITY nProfileLineNum = { 0 };
						nRet = MV_STA_GetProfileIntensity(DataObj, &nProfileLineNum);
						if (0 != nRet)
						{
							printf("MV_STA_GetProfileIntensity failed, errcode (%#x)!\r\n", nRet);
							throw nRet;
						}
					}
					else if (STC_DATA_MSG_TYPE_DWS_VOLUME == nMsgType)
					{
						//   need support
					}
					else if (STC_3D_Profile_Thickness == nMsgType)
					{
						// need support
					}
					else if (STC_3D_Profile_RunDir == nMsgType)
					{
						//  need support
					}
					else if (STC_3D_Profile_FirstFrmID == nMsgType)
					{
						//  need support
					}
					else if (STC_3D_Profile_CoordScale == nMsgType)
					{
						//  need support
					}
					else if (STC_3D_Profile_CoordOffset == nMsgType)
					{
						//  need support
					}
					else
					{
						printf("not support !\r\n");
					}
				}

			}
			catch (...)
			{
				printf("ERROR  !\r\n");
			}


			nRet = MV_STA_DestroyData(DataSet);
			if (0 != nRet)
			{
				printf("MV_STA_DestroyData failed, errcode (%#x)!\r\n", nRet);
			}
			else
			{
				printf("MV_STA_DestroyData  value (%d) success !\r\n", nMsgType);
			}

		}
		else
		{
			Sleep(1);
			continue;
		}
		outnum++;
	}
	printf("stop recv  !\r\n");
}
#endif
//停止采集
void ConnectCamera::stopGrab()
{
	int nRet = MV_STA_OK;
	

	m_bStartJob = false;
	// 停止工作流程
	nRet = MV_STA_Stop(m_handle);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Stop grabbing failed! err code:" + QString::number(nRet));
		
		m_bStartJob = false;
		return;
	}
	ui.pushButton_close->setEnabled(true);
	ui.pushButton_start->setEnabled(true);
	ui.pushButton_stop->setEnabled(false);
	ui.pushButton_savePly->setEnabled(false);
	ui.pushButton_savePcd->setEnabled(false);
	ui.pushButton_connect->setEnabled(false);
	ui.pushButton_showImg->setEnabled(false);
	ui.pushButton_closeImg->setEnabled(false);
	ui.pushButton_doOnce->setEnabled(false);
	//ui.pushButton_autoDo->setEnabled(false);
	
}

//显示图像，同时将原始数据缓存起来，便于后面保存成各种格式的文件
//代码不适合本例，因为这是用mfc显示的图像，而本例是直接利用PCL显示点云对象
//所以写了getData函数用来代替display

#if 0
int ConnectCamera::Display(void * handle, void * hWnd, STC_DATA_IMAGE * pstDisplayImage)
{
	int nRet = MV_STA_OK;

	if (NULL == pstDisplayImage)
	{
		return MV_STA_E_PARAMETER;
	}

	if (pstDisplayImage->nWidth == 0 || pstDisplayImage->nHeight == 0 || NULL == hWnd)
	{
		return MV_STA_E_PARAMETER;
	}


	// 显示图像，这一段可以注释，将显示图像的功能放在qvtkwidget中
	//使用hdc显示必须要在release模式下才可以，由于不知名原因，在本例中，显示由于opengl错误导致不能正常显示
	HDC hDC = ::GetDC((HWND)hWnd);
	SetStretchBltMode(hDC, COLORONCOLOR);
	RECT wndRect;
	::GetClientRect((HWND)hWnd, &wndRect);


	//当前部分双目相机显示是Mono12 实际是 Mono16
	//双目相机有MV-DB和MV-DS两种
	if (STC_PixelType_Gvsp_Mono12 == pstDisplayImage->enPixelType && ((0 == memcmp(m_stDeviceInfo.chModelName, "MV-DB", 5)) ||
		(0 == memcmp(m_stDeviceInfo.chModelName, "MV-DS", 5))))
	{
		pstDisplayImage->enPixelType = STC_PixelType_Gvsp_Mono16;
	}


	{
		// 缓存下来，后期保存图片
		m_criSection.Lock();
		if (m_MaxImageSize < pstDisplayImage->nFrameLen)
		{
			if (NULL != m_pcDataBuf)
			{
				free(m_pcDataBuf);
				m_pcDataBuf = NULL;
			}

			m_MaxImageSize = pstDisplayImage->nFrameLen;
			m_pcDataBuf = (unsigned char*)malloc(m_MaxImageSize);
			if (NULL == m_pcDataBuf)
			{
				nRet = MV_STA_E_RESOURCE;
				return nRet;
			}
			memset(m_pcDataBuf, 0, m_MaxImageSize);
		}

		memset(m_pcDataBuf, 0, m_MaxImageSize);
		memset((void *)&m_stImageInfo, 0, sizeof(STC_DATA_IMAGE));

		// 保存图片信息 & 图片，//把传进来的原始数据pstDisplayImage复制给自定义的m_stImageInfo结构体
		//m_stImageInfo和m_pcDataBuf是后面save用的信息
		memcpy((void *)&m_stImageInfo, pstDisplayImage, sizeof(STC_DATA_IMAGE));
		if (NULL != pstDisplayImage->pData)
		{
			//把传进来的原始数据pstDisplayImage复制给自定义的m_pcDataBuf（这是字节数据）
			memcpy(m_pcDataBuf, pstDisplayImage->pData, pstDisplayImage->nFrameLen);
		}
		m_criSection.Unlock();
	}



	//这是对mono8数据的操作,一般是二维相机的数据
	if (STC_PixelType_Gvsp_Mono8 == pstDisplayImage->enPixelType)
	{
		// mono8 直接渲染
		MV_CODEREADER_DRAW_PARAM stParam;    // 自己构建的结构体

		int nWndRectWidth = wndRect.right - wndRect.left;
		int nWndRectHeight = wndRect.bottom - wndRect.top;
		int nDstWidth = (int)(nWndRectWidth);
		int nDstHeight = (int)(nWndRectHeight);
		int nDstX = wndRect.left;
		int nDstY = wndRect.top;

		int nImageWidth = pstDisplayImage->nWidth;
		int nImageHeight = pstDisplayImage->nHeight;
		int nSrcX = 0;
		int nSrcY = 0;
		int nSrcWidth = (int)(nImageWidth);
		int nSrcHeight = (int)(nImageHeight);

		// 给结构体赋值
		stParam.hDC = hDC;
		stParam.nDstX = nDstX;
		stParam.nDstY = nDstY;
		stParam.nImageHeight = nImageHeight;
		stParam.nImageWidth = nImageWidth;
		stParam.nWndRectHeight = nWndRectHeight;
		stParam.nWndRectWidth = nWndRectWidth;

		stParam.pData = pstDisplayImage->pData;
		//drawd的使用，不涉及mono8数据，直接注释
		//nRet = Draw(&stParam);
		if (MV_STA_OK != nRet)
		{
			return MV_STA_E_PARAMETER;
		}

	}
	//对mono16和3D数据，这是本例重点改造的，因为用的是三维线结构光扫描仪
	//这里是把深度度转成标准图
	else if ((STC_PixelType_Gvsp_Mono16 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_C32 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_C16 == pstDisplayImage->enPixelType))
	{
		STC_DEPTH_MAP_DISPLAY_EX  stDisplayExInfo = { 0 };
		if ((STC_PixelType_Gvsp_Coord3D_C32 == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_C16 == pstDisplayImage->enPixelType))
		{

			// 深度图，转换为标准图，渲染
			STC_NORMALIZE_IMAGE stImage = { 0 };
			stImage.nWidth = pstDisplayImage->nWidth;
			stImage.nHeight = pstDisplayImage->nHeight;
			stImage.pData = pstDisplayImage->pData;
			stImage.nLen = pstDisplayImage->nFrameLen;
			stImage.enSrcPixelType = pstDisplayImage->enPixelType;

			stImage.enDstPixelType = STC_PixelType_Gvsp_Mono16;

			nRet = MV_STA_NormalizedDepthImage(handle, &stImage);
			if (0 != nRet)
			{
				printf("MV_STA_NormalizedDepthImage failed, errcode (%#x)!\r\n", nRet);
				return nRet;
			}


			STC_DATA_IMAGE  stDataTmp;
			stDataTmp.nWidth = pstDisplayImage->nWidth;
			stDataTmp.nHeight = pstDisplayImage->nHeight;
			stDataTmp.enPixelType = STC_PixelType_Gvsp_Mono16;

			stDataTmp.pData = stImage.pNormalizedData;
			stDataTmp.nFrameLen = stImage.nNormalizedLen;
			stDataTmp.nFrameNum = pstDisplayImage->nFrameNum;

			nRet = MV_STA_DisplayStandardDepthMap(handle, &stDataTmp, &stDisplayExInfo, hWnd);
			if (0 != nRet)
			{
				printf("MV_STA_DisplayStandardDepthMap failed, errcode (%#x)!\r\n", nRet);
				return nRet;
			}
		}
		else
		{

			// 支持左上角显示水印
#if 0
			memcpy(stDisplayExInfo.szImageWatermark, "HKVISION", sizeof("HKVISION"));

			// 支持显示包裹的位置  （实际坐标）
			stDisplayExInfo.szPackageRoi.bSupport = true;
			stDisplayExInfo.szPackageRoi.point[0].x = 100;
			stDisplayExInfo.szPackageRoi.point[0].y = 100;
			stDisplayExInfo.szPackageRoi.point[1].x = 500;
			stDisplayExInfo.szPackageRoi.point[1].y = 500;
			stDisplayExInfo.szPackageRoi.point[2].x = 500;
			stDisplayExInfo.szPackageRoi.point[2].y = 800;
			stDisplayExInfo.szPackageRoi.point[3].x = 100;
			stDisplayExInfo.szPackageRoi.point[3].y = 800;

			// 支持显示测量区域的位置  (整幅图是1，此处是比例）
			stDisplayExInfo.szMeasureRoi.bSupport = true;
			stDisplayExInfo.szMeasureRoi.point[0].x = 0.4;
			stDisplayExInfo.szMeasureRoi.point[0].y = 0.4;
			stDisplayExInfo.szMeasureRoi.point[1].x = 0.4;
			stDisplayExInfo.szMeasureRoi.point[1].y = 0.6;
			stDisplayExInfo.szMeasureRoi.point[2].x = 0.6;
			stDisplayExInfo.szMeasureRoi.point[2].y = 0.6;
			stDisplayExInfo.szMeasureRoi.point[3].x = 0.6;
			stDisplayExInfo.szMeasureRoi.point[3].y = 0.4;
#endif

			nRet = MV_STA_DisplayStandardDepthMap(handle, pstDisplayImage, &stDisplayExInfo, hWnd);
			if (0 != nRet)
			{
				printf("MV_STA_DisplayStandardDepthMap failed, errcode (%#x)!\r\n", nRet);
				return nRet;
			}
		}
	}
	//对mono16和3D数据，这是本例重点改造的，因为用的是三维线结构光扫描仪，本例的格式是Coord3D_ABC16或32，所以执行在这一段
	//这里是把点云图转标准图
	else if ((STC_PixelType_Gvsp_Coord3D_ABC32f == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_AC32 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC16 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32 == pstDisplayImage->enPixelType))
	{
		// 点云图，转换为标准图，渲染

		if ((STC_PixelType_Gvsp_Coord3D_AC32 == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32f == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32 == pstDisplayImage->enPixelType))
		{
			// 点云图，转换为标准图，渲染
			STC_NORMALIZE_IMAGE stImage = { 0 };
			stImage.nWidth = pstDisplayImage->nWidth;
			stImage.nHeight = pstDisplayImage->nHeight;
			stImage.pData = pstDisplayImage->pData;
			stImage.nLen = pstDisplayImage->nFrameLen;
			stImage.enSrcPixelType = pstDisplayImage->enPixelType;

			stImage.enDstPixelType = STC_PixelType_Gvsp_Coord3D_ABC32;

			nRet = MV_STA_NormalizedPointCloudImage(handle, &stImage);
			if (0 != nRet)
			{
				printf("MV_STA_NormalizedPointCloudImage failed, errcode (%#x)!\r\n", nRet);
				return nRet;
			}


			printf("zzzz  get image (%d): from len  (%d) -->(%d)!\r\n", pstDisplayImage->nFrameNum, pstDisplayImage->nFrameLen, stImage.nNormalizedLen);

			STC_DATA_IMAGE  stDataTmp;
			stDataTmp.nWidth = pstDisplayImage->nWidth;
			stDataTmp.nHeight = pstDisplayImage->nHeight;
			stDataTmp.enPixelType = STC_PixelType_Gvsp_Coord3D_ABC32;

			stDataTmp.pData = stImage.pNormalizedData;
			stDataTmp.nFrameLen = stImage.nNormalizedLen;
			stDataTmp.nFrameNum = pstDisplayImage->nFrameNum;

			//这里是直接显示在窗口中
			nRet = MV_STA_DisplayStandardPointCloud(handle, &stDataTmp, hWnd, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top);
			if (0 != nRet)
			{
				printf("MV_STA_DisplayStandardPointCloud failed, errcode (%#x)!\r\n", nRet);
				return nRet;
			}

		}
		else
		{
			MV_STA_DisplayStandardPointCloud(handle, pstDisplayImage, hWnd, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top);
		}

	}
	else if (STC_PixelType_Gvsp_Rgbd_C16 == pstDisplayImage->enPixelType)
	{
		STC_DEPTH_MAP_DISPLAY_EX  stDisplayExInfo = { 0 };
		nRet = MV_STA_DisplayRgbdMap(handle, pstDisplayImage, &stDisplayExInfo, hWnd);
		if (0 != nRet)
		{
			printf("MV_STA_DisplayStandardDepthMap failed, errcode (%#x)!\r\n", nRet);
			return nRet;
		}
	}
	else if (STC_PixelType_Gvsp_RGB8_Planar == pstDisplayImage->enPixelType)
	{
		nRet = ConvertRGB8Planner2RGB8Packed(pstDisplayImage->pData,
			pstDisplayImage->nWidth,
			pstDisplayImage->nHeight,
			m_pcRGBDataBuf);

		if (1 != nRet)
		{
			printf("MV_STA_DisplayStandardDepthMap ConvertRGB8Planner2RGB8Packed failed, errcode (%#x)!\r\n", nRet);
			return nRet;
		}
		pstDisplayImage->pData = m_pcRGBDataBuf;
		pstDisplayImage->enPixelType = STC_PixelType_Gvsp_RGB8_Packed;
		STC_DEPTH_MAP_DISPLAY_EX  stDisplayExInfo = { 0 };
		nRet = MV_STA_DisplayRgbdMap(handle, pstDisplayImage, &stDisplayExInfo, hWnd);
		if (0 != nRet)
		{
			printf("MV_STA_DisplayStandardDepthMap failed, errcode (%#x)!\r\n", nRet);
			return nRet;
		}
	}
	else
	{
		// 不支持

	}


	::ReleaseDC((HWND)hWnd, hDC);
	return nRet;
}
#endif

//用于测试，看能否精简代码拿到数据
//假如成功，就可以不用display函数以及与其相关联的draw函数和convert函数，可以极大精简代码
//2022.1.6,绕过display函数，使用getdata函数成功拿到相机源数据，成功精简代码
int ConnectCamera::getData(void * handle, STC_DATA_IMAGE * pstDisplayImage)
{
	int nRet = MV_STA_OK;

	if (NULL == pstDisplayImage)
	{
		return MV_STA_E_PARAMETER;
	}

	if (pstDisplayImage->nWidth == 0 || pstDisplayImage->nHeight == 0)
	{
		return MV_STA_E_PARAMETER;
	}
	
	//当前部分双目相机显示是Mono12 实际是 Mono16
	//双目相机有MV-DB和MV-DS两种
	if (STC_PixelType_Gvsp_Mono12 == pstDisplayImage->enPixelType && ((0 == memcmp(m_stDeviceInfo.chModelName, "MV-DB", 5)) ||
		(0 == memcmp(m_stDeviceInfo.chModelName, "MV-DS", 5))))
	{
		pstDisplayImage->enPixelType = STC_PixelType_Gvsp_Mono16;
	}


	{
		// 缓存下来，后期保存图片
		//这一段是本例的核心，将扫描仪数据存在pstDisplayImage共享指针中
		//后面一系列的选择判断语句本例都用不上，是支持其他相机的代码
		m_criSection.Lock();
		if (m_MaxImageSize < pstDisplayImage->nFrameLen)
		{
			if (NULL != m_pcDataBuf)
			{
				free(m_pcDataBuf);
				m_pcDataBuf = NULL;
			}

			m_MaxImageSize = pstDisplayImage->nFrameLen;
			m_pcDataBuf = (unsigned char*)malloc(m_MaxImageSize);
			if (NULL == m_pcDataBuf)
			{
				nRet = MV_STA_E_RESOURCE;
				return nRet;
			}
			memset(m_pcDataBuf, 0, m_MaxImageSize);
		}

		memset(m_pcDataBuf, 0, m_MaxImageSize);
		memset((void *)&m_stImageInfo, 0, sizeof(STC_DATA_IMAGE));

		// 保存图片信息 & 图片，//把传进来的原始数据pstDisplayImage复制给自定义的m_stImageInfo结构体
		//m_stImageInfo和m_pcDataBuf是后面save用的信息
		memcpy((void *)&m_stImageInfo, pstDisplayImage, sizeof(STC_DATA_IMAGE));
		if (NULL != pstDisplayImage->pData)
		{
			//把传进来的原始数据pstDisplayImage复制给自定义的m_pcDataBuf（这是字节数据）
			memcpy(m_pcDataBuf, pstDisplayImage->pData, pstDisplayImage->nFrameLen);
		}
		m_criSection.Unlock();
	}

//若使用的相机不是MV-DP2305系列的相机，可以使用下面代码
#if 0
	//这是对mono8数据的操作,一般是二维相机的数据，这里用不到
	if (STC_PixelType_Gvsp_Mono8 == pstDisplayImage->enPixelType)
	{
		// mono8 直接渲染
		//MV_CODEREADER_DRAW_PARAM stParam;    // 自己构建的结构体

		//int nWndRectWidth = wndRect.right - wndRect.left;
		//int nWndRectHeight = wndRect.bottom - wndRect.top;
		//int nDstWidth = (int)(nWndRectWidth);
		//int nDstHeight = (int)(nWndRectHeight);
		//int nDstX = wndRect.left;
		//int nDstY = wndRect.top;

		//int nImageWidth = pstDisplayImage->nWidth;
		//int nImageHeight = pstDisplayImage->nHeight;
		//int nSrcX = 0;
		//int nSrcY = 0;
		//int nSrcWidth = (int)(nImageWidth);
		//int nSrcHeight = (int)(nImageHeight);

		//// 给结构体赋值
		//stParam.hDC = hDC;
		//stParam.nDstX = nDstX;
		//stParam.nDstY = nDstY;
		//stParam.nImageHeight = nImageHeight;
		//stParam.nImageWidth = nImageWidth;
		//stParam.nWndRectHeight = nWndRectHeight;
		//stParam.nWndRectWidth = nWndRectWidth;

		//stParam.pData = pstDisplayImage->pData;
		////drawd的使用，不涉及mono8数据，直接注释
		////nRet = Draw(&stParam);
		//if (MV_STA_OK != nRet)
		//{
		//	return MV_STA_E_PARAMETER;
		//}

	}
	//对mono16和3D数据，这是本例重点改造的，因为用的是三维线结构光扫描仪
	//这里是把深度度转成标准图，这里用不到
	else if ((STC_PixelType_Gvsp_Mono16 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_C32 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_C16 == pstDisplayImage->enPixelType))
	{
		STC_DEPTH_MAP_DISPLAY_EX  stDisplayExInfo = { 0 };
		if ((STC_PixelType_Gvsp_Coord3D_C32 == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_C16 == pstDisplayImage->enPixelType))
		{

			// 深度图，转换为标准图，渲染
			/*STC_NORMALIZE_IMAGE stImage = { 0 };
			stImage.nWidth = pstDisplayImage->nWidth;
			stImage.nHeight = pstDisplayImage->nHeight;
			stImage.pData = pstDisplayImage->pData;
			stImage.nLen = pstDisplayImage->nFrameLen;
			stImage.enSrcPixelType = pstDisplayImage->enPixelType;

			stImage.enDstPixelType = STC_PixelType_Gvsp_Mono16;

			nRet = MV_STA_NormalizedDepthImage(handle, &stImage);
			if (0 != nRet)
			{
				printf("MV_STA_NormalizedDepthImage failed, errcode (%#x)!\r\n", nRet);
				return nRet;
			}


			STC_DATA_IMAGE  stDataTmp;
			stDataTmp.nWidth = pstDisplayImage->nWidth;
			stDataTmp.nHeight = pstDisplayImage->nHeight;
			stDataTmp.enPixelType = STC_PixelType_Gvsp_Mono16;

			stDataTmp.pData = stImage.pNormalizedData;
			stDataTmp.nFrameLen = stImage.nNormalizedLen;
			stDataTmp.nFrameNum = pstDisplayImage->nFrameNum;

			nRet = MV_STA_DisplayStandardDepthMap(handle, &stDataTmp, &stDisplayExInfo, hWnd);
			if (0 != nRet)
			{
				printf("MV_STA_DisplayStandardDepthMap failed, errcode (%#x)!\r\n", nRet);
				return nRet;
			}*/
		}
		else
		{

			

			/*nRet = MV_STA_DisplayStandardDepthMap(handle, pstDisplayImage, &stDisplayExInfo, hWnd);
			if (0 != nRet)
			{
				printf("MV_STA_DisplayStandardDepthMap failed, errcode (%#x)!\r\n", nRet);
				return nRet;
			}*/
		}
	}
	//对mono16和3D数据，这是本例重点改造的，因为用的是三维线结构光扫描仪，本例的格式是Coord3D_ABC16或32，所以执行在这一段
	//这里是把点云图转标准图，本例执行的是这一段
	else if ((STC_PixelType_Gvsp_Coord3D_ABC32f == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_AC32 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC16 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32 == pstDisplayImage->enPixelType))
	{
		// 点云图，转换为标准图，渲染
		//跳到这，但也没有执行这一段，直接跳出这个
		if ((STC_PixelType_Gvsp_Coord3D_AC32 == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32f == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32 == pstDisplayImage->enPixelType))
		{
			// 点云图，转换为标准图，渲染
			//STC_NORMALIZE_IMAGE stImage = { 0 };
			//stImage.nWidth = pstDisplayImage->nWidth;
			//stImage.nHeight = pstDisplayImage->nHeight;
			//stImage.pData = pstDisplayImage->pData;
			//stImage.nLen = pstDisplayImage->nFrameLen;
			//stImage.enSrcPixelType = pstDisplayImage->enPixelType;

			//stImage.enDstPixelType = STC_PixelType_Gvsp_Coord3D_ABC32;

			//nRet = MV_STA_NormalizedPointCloudImage(handle, &stImage);
			//if (0 != nRet)
			//{
			//	printf("MV_STA_NormalizedPointCloudImage failed, errcode (%#x)!\r\n", nRet);
			//	return nRet;
			//}


			//printf("zzzz  get image (%d): from len  (%d) -->(%d)!\r\n", pstDisplayImage->nFrameNum, pstDisplayImage->nFrameLen, stImage.nNormalizedLen);

			//STC_DATA_IMAGE  stDataTmp;
			//stDataTmp.nWidth = pstDisplayImage->nWidth;
			//stDataTmp.nHeight = pstDisplayImage->nHeight;
			//stDataTmp.enPixelType = STC_PixelType_Gvsp_Coord3D_ABC32;

			//stDataTmp.pData = stImage.pNormalizedData;
			//stDataTmp.nFrameLen = stImage.nNormalizedLen;
			//stDataTmp.nFrameNum = pstDisplayImage->nFrameNum;

			////这里是直接显示在窗口中
			////nRet = MV_STA_DisplayStandardPointCloud(handle, &stDataTmp, hWnd, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top);
			//if (0 != nRet)
			//{
			//	printf("MV_STA_DisplayStandardPointCloud failed, errcode (%#x)!\r\n", nRet);
			//	return nRet;
			//}

		}
		else
		{
			//MV_STA_DisplayStandardPointCloud(handle, pstDisplayImage, hWnd, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top);
		}

	}
	else if (STC_PixelType_Gvsp_Rgbd_C16 == pstDisplayImage->enPixelType)
	{
		STC_DEPTH_MAP_DISPLAY_EX  stDisplayExInfo = { 0 };
		//nRet = MV_STA_DisplayRgbdMap(handle, pstDisplayImage, &stDisplayExInfo, hWnd);
		if (0 != nRet)
		{
			printf("MV_STA_DisplayStandardDepthMap failed, errcode (%#x)!\r\n", nRet);
			return nRet;
		}
	}
	else if (STC_PixelType_Gvsp_RGB8_Planar == pstDisplayImage->enPixelType)
	{
	/*	nRet = ConvertRGB8Planner2RGB8Packed(pstDisplayImage->pData,
			pstDisplayImage->nWidth,
			pstDisplayImage->nHeight,
			m_pcRGBDataBuf);

		if (1 != nRet)
		{
			printf("MV_STA_DisplayStandardDepthMap ConvertRGB8Planner2RGB8Packed failed, errcode (%#x)!\r\n", nRet);
			return nRet;
		}
		pstDisplayImage->pData = m_pcRGBDataBuf;
		pstDisplayImage->enPixelType = STC_PixelType_Gvsp_RGB8_Packed;
		STC_DEPTH_MAP_DISPLAY_EX  stDisplayExInfo = { 0 };
		nRet = MV_STA_DisplayRgbdMap(handle, pstDisplayImage, &stDisplayExInfo, hWnd);
		if (0 != nRet)
		{
			printf("MV_STA_DisplayStandardDepthMap failed, errcode (%#x)!\r\n", nRet);
			return nRet;
		}*/
	}
	else
	{
		// 不支持

	}

#endif
	//::ReleaseDC((HWND)hWnd, hDC);
	return nRet;
}

//Draw只在mono8中使用了，本例使用的是三维数据，可以直接注释

//int ConnectCamera::Draw(MV_CODEREADER_DRAW_PARAM * pstParam)
//{
//	if (NULL == pstParam)
//	{
//		return MV_STA_E_PARAMETER;
//	}
//
//	int nImageWidth = pstParam->nImageWidth;
//	int nImageHeight = pstParam->nImageHeight;
//	int nDstWidth = (int)(pstParam->nWndRectWidth);
//	int nDstHeight = (int)(pstParam->nWndRectHeight);
//	int nSrcX = 0;
//	int nSrcY = 0;
//	int nSrcWidth = (int)(nImageWidth);
//	int nSrcHeight = (int)(nImageHeight);
//
//	if (NULL == m_bBitmapInfo)
//	{
//		m_bBitmapInfo = (PBITMAPINFO)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
//		memset(m_bBitmapInfo, 0, sizeof(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)));
//	}
//	// 位图信息头
//	m_bBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);             // BITMAPINFOHEADER结构长度
//	m_bBitmapInfo->bmiHeader.biWidth = nImageWidth;                         // 图像宽度
//	m_bBitmapInfo->bmiHeader.biPlanes = 1;                                  // 位面数
//	m_bBitmapInfo->bmiHeader.biBitCount = 8;                                // 比特数/像素的颜色深度,2^8=256
//	m_bBitmapInfo->bmiHeader.biCompression = BI_RGB;                        // 图像数据压缩类型,BI_RGB表示不压缩
//	m_bBitmapInfo->bmiHeader.biSizeImage = nImageWidth * nImageHeight;      // 图像大小
//	m_bBitmapInfo->bmiHeader.biHeight = -nImageHeight;                       // 图像高度
//
//	for (int i = 0; i < 256; i++)
//	{
//		m_bBitmapInfo->bmiColors[i].rgbBlue = m_bBitmapInfo->bmiColors[i].rgbRed = m_bBitmapInfo->bmiColors[i].rgbGreen = i;
//		m_bBitmapInfo->bmiColors[i].rgbReserved = 0;
//	}
//
//	int nRet = StretchDIBits(pstParam->hDC,
//		pstParam->nDstX, pstParam->nDstY, nDstWidth, nDstHeight,
//		nSrcX, nSrcY, nSrcWidth, nSrcHeight, pstParam->pData, m_bBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
//
//	return MV_STA_OK;
//}

//ConvertRGB8Planner2RGB8Packed与display配合使用，本例用不上
#if 0
bool ConnectCamera::ConvertRGB8Planner2RGB8Packed(const unsigned char * pSrcData, int nWidth, int nHeight, unsigned char * pDstData)
{
	if (NULL == pSrcData || NULL == pDstData)
	{
		return false;
	}
	int nImageStep = nWidth * nHeight;
	for (int i = 0; i < nImageStep; ++i)
	{
		pDstData[i * 3 + 0] = pSrcData[i + nImageStep * 0];
		pDstData[i * 3 + 1] = pSrcData[i + nImageStep * 1];
		pDstData[i * 3 + 2] = pSrcData[i + nImageStep * 2];
	}

	return true;
}
#endif

//初始化资源
int ConnectCamera::InitResources()
{
	int nRet = MV_STA_OK;
	

	try
	{
		int nSensorWidth = 0;
		int nSensorHight = 0;

		MV_STA_INTVALUE stParam;
		memset(&stParam, 0, sizeof(MV_STA_INTVALUE));
		nRet = MV_STA_GetIntValue(m_handle, Camera_Width, &stParam);
		if (MV_STA_OK != nRet)
		{
			QMessageBox::about(this, "warning!", "Get width failed! err code:" + QString::number(nRet));
			nRet = MV_STA_E_UNKNOW;
			throw nRet;
		}
		nSensorWidth = stParam.nMax;

		memset(&stParam, 0, sizeof(MV_STA_INTVALUE));
		nRet = MV_STA_GetIntValue(m_handle, Camera_Height, &stParam);
		if (MV_STA_OK != nRet)
		{
			QMessageBox::about(this, "warning!", "Get hight failed! err code:" + QString::number(nRet));
			
			return nRet;
		}
		nSensorHight = stParam.nMax;

		m_MaxImageSize = nSensorWidth * nSensorHight + 4096;

		
		m_pcDataBuf = (unsigned char*)malloc(m_MaxImageSize);
		if (NULL == m_pcDataBuf)
		{
			nRet = MV_STA_E_RESOURCE;
			throw nRet;
		}
		memset(m_pcDataBuf, 0, m_MaxImageSize);
		memset((void *)&m_stImageInfo, 0, sizeof(STC_DATA_IMAGE));

		m_pcRGBDataBuf = (unsigned char*)malloc(2000 * 2000 * 3);
		if (NULL == m_pcRGBDataBuf)
		{
			nRet = MV_STA_E_RESOURCE;
			throw nRet;
		}
		memset(m_pcRGBDataBuf, 0, m_MaxImageSize);


		m_MaxPlyImageSize = PLY_IMAG_MAX_LEN;
		m_pcPlyDataBuf = (unsigned char*)malloc(m_MaxPlyImageSize);
		if (NULL == m_pcDataBuf)
		{
			nRet = MV_STA_E_RESOURCE;
			throw nRet;
		}
		memset((void *)m_pcPlyDataBuf, 0, m_MaxPlyImageSize);


	}
	catch (...)
	{
		DeInitResources();
		return nRet;
	}

	return nRet;
}
//反初始化资源
void ConnectCamera::DeInitResources()
{
	if (NULL != m_pcDataBuf)
	{
		free(m_pcDataBuf);
		m_pcDataBuf = NULL;
	}

	if (NULL != m_pcRGBDataBuf)
	{
		free(m_pcRGBDataBuf);
		m_pcRGBDataBuf = NULL;
	}

	if (NULL != m_pcPlyDataBuf)
	{
		free(m_pcPlyDataBuf);
		m_pcPlyDataBuf = NULL;
	}
}
//保存ply
void ConnectCamera::savePly()
{
	char filename[256] = { 0 };
	CTime currTime;                                     // 获取系统时间作为保存图片文件名
	currTime = CTime::GetCurrentTime();
	sprintf(filename, ("%.4d%.2d%.2d%.2d%.2d%.2d.ply"), currTime.GetYear(), currTime.GetMonth(),
		currTime.GetDay(), currTime.GetHour(), currTime.GetMinute(), currTime.GetSecond());
	pcl::PLYWriter w;
	if (ui.checkBox_isBinary->isChecked())
	{
		if (w.write(filename, *cloud, true) < 0)
		{
			QMessageBox::about(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("保存失败"));
		}
		QMessageBox::about(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("保存成功"));


	}
	if (w.write(filename, *cloud, false) < 0)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("保存失败"));
	}
	QMessageBox::about(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("保存成功"));
	//测试代码，暂时用不上
#if 0
	int nRet = MV_STA_OK;
	QString  cstrInfo = "";

	// 判断是否开始取流
	if (!m_bConnect)
	{
		QMessageBox::about(this, "warning!", "No camera Connected!" );
		
	}

	if (!m_bStartJob)
	{
		QMessageBox::about(this, "warning!", "The camera is not startJob!");
		
	}

	// 判断是否有有效数据
	//这里的m_stImageInfo是在display函数中缓存的，所以display函数不能完全注释，但是可以把显示部分进行改造
	//原始的数据保存在m_pcDataBuf，以字节形式
	if (NULL == m_pcDataBuf)
	{
		QMessageBox::about(this, "warning!", "No data，Save PLY failed!");
		
	}

	if (0 == m_stImageInfo.nFrameLen)
	{
		QMessageBox::about(this, "warning!", "No Data, save nothing !");
		
	}



	FILE* pfile;
	char filename[256] = { 0 };
	CTime currTime;                                     // 获取系统时间作为保存图片文件名
	currTime = CTime::GetCurrentTime();
	sprintf(filename, ("%.4d%.2d%.2d%.2d%.2d%.2d.ply"), currTime.GetYear(), currTime.GetMonth(),
		currTime.GetDay(), currTime.GetHour(), currTime.GetMinute(), currTime.GetSecond());

	//本例用的三维激光扫描仪的格式是Gvsp_Coord3D_ABC16或者Gvsp_Coord3D_ABC32
	if ((STC_PixelType_Gvsp_Coord3D_ABC16 == m_stImageInfo.enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32 == m_stImageInfo.enPixelType))
	{
		m_criSection.Lock();

		try
		{


			// 直接save
			STC_IMG_SAVE_ABC16_TO_PLY_PARAM  stPlyImage = { 0 };
			stPlyImage.nLinePntNum = m_stImageInfo.nWidth;
			stPlyImage.nLineNum = m_stImageInfo.nHeight;

			stPlyImage.pSrcData = m_stImageInfo.pData;
			stPlyImage.nSrcDataLen = m_stImageInfo.nFrameLen;
			stPlyImage.enSrcPixelType = m_stImageInfo.enPixelType;


			int nLenTmp = (stPlyImage.nLinePntNum *  stPlyImage.nLineNum *(16 * 3 + 4)) + 2048;

			if (m_MaxPlyImageSize < nLenTmp)
			{
				if (m_pcPlyDataBuf)
				{
					free(m_pcPlyDataBuf);
				}

				m_pcPlyDataBuf = (unsigned char*)malloc(nLenTmp);
				if (NULL == m_pcDataBuf)
				{
					QMessageBox::about(this, "warning!", "malloc failed");
					
					nRet = MV_STA_E_RESOURCE;
					throw nRet;
				}

				m_MaxPlyImageSize = nLenTmp;
				memset(m_pcPlyDataBuf, 0, m_MaxPlyImageSize);
			}


			stPlyImage.pDstBuf = m_pcPlyDataBuf;//(nLinePntNum * nLineNum * (16*3 + 4) + 2048)
			stPlyImage.nDstBufSize = m_MaxPlyImageSize;
			//这一句进行数据封装，将各种格式3D图转为ply格式
			nRet = MV_STA_SavePly(m_handle, &stPlyImage);
			if (MV_STA_OK != nRet)
			{
				QMessageBox::about(this, "warning!", "MV_STA_SavePly failed");
				
				throw nRet;
			}
			//用pcl的函数保存ply文件
			//pcl::PointCloud<pcl::PointXYZ> * cloud (new pcl::PointCloud<pcl::PointXYZ>());
			/*pcl::PointCloud<pcl::PointXYZ> * cloud = NULL;
			cloud = (pcl::PointCloud<pcl::PointXYZ> *) malloc(stPlyImage.nDstBufLen);
			memset(cloud, 0, stPlyImage.nDstBufLen);
			memcpy(cloud, stPlyImage.pDstBuf, stPlyImage.nDstBufLen);
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_share = cloud->makeShared();
			pcl::io::savePLYFile("text.ply",*cloud_share);*/
			//更安全的一种方式,无效，因为点云指针不是pod类型，无法强制转换
			//虽然转换成功，但是数据是无法读取的，失败
			//pcl::PointCloud<pcl::PointXYZ> * pThing = static_cast<pcl::PointCloud<pcl::PointXYZ> *> (stPlyImage.pDstBuf);
			//pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
			/*这个方法成功,从源码上解析发现pDstBuf是unsigned char*类型的数据
			将这种类型的数据转为字符串比较容易*/
			//首先把void *强转为unsigned char *
			//unsigned char * str =(unsigned char *) stPlyImage.pDstBuf;
			//string res = "";
			////这一步关键，将unsigned char *转为字符串
			//res.append(reinterpret_cast<const char*>(str));
			//QString r = QString::fromStdString(res);
			////后续要自己写一个读取txt为点云对象的函数
			//ConnectCamera::txt2pc(res, cloud);
			//pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("viewer"));
			//viewer->setBackgroundColor(1, 1, 1);
			//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color(cloud, 1, 0, 0);
			//viewer->addPointCloud(cloud, color, "cloud");
			//viewer->spin();
			//QMessageBox::about(this, "warn", r);
			//pcl::PCDWriter w;
			//w.write("text.pcd", *cloud);
			pfile = fopen(filename, "wb");
			if (pfile == NULL)
			{
				QMessageBox::about(this, "warning!", "Open file failed");
				
				throw nRet;
			}
			
			fwrite(stPlyImage.pDstBuf, 1, stPlyImage.nDstBufLen, pfile);
			fclose(pfile);
			pfile = NULL;

		}
		catch (...)
		{
			m_criSection.Unlock();
			//MessageBox(cstrInfo);
			return;
		}

		m_criSection.Unlock();
	}
	else if ((STC_PixelType_Gvsp_Coord3D_ABC32f == m_stImageInfo.enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == m_stImageInfo.enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_AC32 == m_stImageInfo.enPixelType))
	{

		m_criSection.Lock();

		try
		{
			// 点云图，转换为标准图
			STC_NORMALIZE_IMAGE stImage = { 0 };
			stImage.nWidth = m_stImageInfo.nWidth;
			stImage.nHeight = m_stImageInfo.nHeight;
			stImage.enSrcPixelType = m_stImageInfo.enPixelType;
			stImage.pData = m_pcDataBuf;
			stImage.nLen = m_stImageInfo.nFrameLen;

			stImage.enDstPixelType = STC_PixelType_Gvsp_Coord3D_ABC32;

			nRet = MV_STA_NormalizedPointCloudImage(m_handle, &stImage);
			if (MV_STA_OK != nRet)
			{
				
				cstrInfo = "MV_STA_NormalizedPointCloudImage failed";
				throw nRet;
			}

			// save it 
			STC_IMG_SAVE_ABC16_TO_PLY_PARAM  stPlyImage = { 0 };
			stPlyImage.nLinePntNum = stImage.nWidth;
			stPlyImage.nLineNum = stImage.nHeight;

			stPlyImage.pSrcData = stImage.pNormalizedData;
			stPlyImage.nSrcDataLen = stImage.nNormalizedLen;
			stPlyImage.enSrcPixelType = STC_PixelType_Gvsp_Coord3D_ABC32;


			int nLenTmp = (stPlyImage.nLinePntNum *  stPlyImage.nLineNum *(16 * 3 + 4)) + 2048;

			if (m_MaxPlyImageSize < nLenTmp)
			{
				if (m_pcPlyDataBuf)
				{
					free(m_pcPlyDataBuf);
				}

				m_pcPlyDataBuf = (unsigned char*)malloc(nLenTmp);
				if (NULL == m_pcDataBuf)
				{
					nRet = MV_STA_E_RESOURCE;
					cstrInfo = "malloc failed";
					throw nRet;
				}

				m_MaxPlyImageSize = nLenTmp;
				memset(m_pcPlyDataBuf, 0, m_MaxPlyImageSize);
			}


			stPlyImage.pDstBuf = m_pcPlyDataBuf;//(nLinePntNum * nLineNum * (16*3 + 4) + 2048)
			stPlyImage.nDstBufSize = m_MaxPlyImageSize;

			nRet = MV_STA_SavePly(m_handle, &stPlyImage);
			if (MV_STA_OK != nRet)
			{
				cstrInfo = "MV_STA_SavePly failed";
				throw nRet;
			}

			pfile = fopen(filename, "wb");
			if (pfile == NULL)
			{
				cstrInfo = "Open file failed";
				throw nRet;
			}

			fwrite(stPlyImage.pDstBuf, 1, stPlyImage.nDstBufLen, pfile);
			fclose(pfile);
			pfile = NULL;
		}
		catch (...)
		{
			m_criSection.Unlock();
			QMessageBox::about(this, "Warning", cstrInfo);
			return;
		}

		m_criSection.Unlock();
	}
	else
	{
		cstrInfo = "Not support save ply file!";
		QMessageBox::about(this, "Warning", cstrInfo);
		return;
	}

	cstrInfo = "Save ply image success!";
	QMessageBox::about(this, "Warning", cstrInfo);
#endif
}
//关闭设备，功能函数
void ConnectCamera::closeDevice()
{
	// TODO: Add your control notification handler code here
	int nRet = MV_STA_OK;
	

	// 销毁设备句柄 
	if (NULL != m_handle)
	{
		// 停止工作流程
		if (true == m_bStartJob)
		{
			m_bStartJob = false;
			nRet = MV_STA_Stop(m_handle);
			if (MV_STA_OK != nRet)
			{
				QMessageBox::about(this, "warning!", "Stop grabbing failed! err code:" + QString::number(nRet));
				
				m_bStartJob = false;
				return;
			}

			//等待渲染线程完全停止
			if (NULL != hProcessThread)
			{
				// 等待线程完成，如果是多线程的，需要调用 WaitForMultipleObjects
				WaitForSingleObject(hProcessThread, INFINITE);
				// 最后关闭句柄
				CloseHandle(hProcessThread);
				hProcessThread = NULL;
			}
		}

		// 清空残留图片,暂时不需要这句话，后面加上qvtk控件再进行清除图片
		//GetDlgItem(IDC_DISPLAY_STATIC)->ShowWindow(FALSE);
		//GetDlgItem(IDC_DISPLAY_STATIC)->ShowWindow(TRUE);

		if (NULL != m_handle)
		{
			nRet = MV_STA_DestroyHandle(m_handle);
			if (MV_STA_OK != nRet)
			{
				QMessageBox::about(this, "warning!", "Destroy handle failed! err code:" + QString::number(nRet));
				
				return;
			}
			m_handle = NULL;
		}
	}

	//销毁资源
	DeInitResources();

	// 关闭设备后清空各项参数数据,后面用qt的代替
	/*m_ctrlExposureEdit.SetWindowText(NULL);
	m_ctrlGainEdit.SetWindowText(NULL);
	m_ctrlFrameRateEdit.SetWindowText(NULL);*/

	m_bStartJob = false;
	m_bConnect = false;
	//ui.pushButton_connect->setEnabled(true);
	ui.pushButton_findCam->setEnabled(true);
	
	ui.pushButton_close->setEnabled(false);
	ui.pushButton_start->setEnabled(false);
	ui.pushButton_stop->setEnabled(false);
	ui.pushButton_savePly->setEnabled(false);
	ui.pushButton_savePcd->setEnabled(false);
	ui.pushButton_connect->setEnabled(false);
	ui.pushButton_showImg->setEnabled(false);
	ui.pushButton_closeImg->setEnabled(false);
	
}

void ConnectCamera::txt2pc(string txt, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_)
{
	//将string转为qstring，这样方便后面操作，qstring中提供了很多方法
	QString qtxt = QString::fromStdString(txt);
	//将string按照换行符进行分割，保存在一个QStringList中，其实相当于vector<string>,可以用数组方式索引
	QStringList qtxtlist = qtxt.split("\n");
	//ply文件中第四行是存储元素个数的信息，将其提取出来，并按照空格分割，这样数字部分就在该list的第二个索引中
	QStringList qsizelist = qtxtlist[3].split(" ");
	//讲元素个数提取出来赋予点云对象
	int points_size = qsizelist[2].toInt();
	cloud_->height = 1;
	cloud_->width = points_size;
	cloud_->resize(cloud_->height * cloud_->width);
	
	for (int i = 0; i < cloud_->size(); i++)
	{
		//坐标是从第八行开始的，所以索引加个8
		QStringList datalist = qtxtlist[i+8].split(" ");
		//每一行代表一个点的三维坐标，提取出来并存到点云对象中
		cloud_->points[i].x = datalist[0].toDouble();
		cloud_->points[i].y = datalist[1].toDouble();
		cloud_->points[i].z = datalist[2].toDouble();

	}
	
	

}

void ConnectCamera::showPc()
{
	ui.pushButton_showImg->setEnabled(true);
	ui.pushButton_closeImg->setEnabled(true);

	viewer->setBackgroundColor(0.5, 0.5, 0.5);
	
	//float coeff = getCoordinate(cloud);
	viewer->addCoordinateSystem(4000);
	//按照某个轴的数值对点云进行渲染，蓝色为极大值，红色为极小值
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> render_color(cloud, "x");
	viewer->addPointCloud(cloud, render_color, "cloud");
	//更新显示的点云
	viewer->updatePointCloud(cloud, render_color,"cloud");
	
	//viewer->initCameraParameters();
	ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(ui.qvtkWidget->GetInteractor(), ui.qvtkWidget->GetRenderWindow());
	ui.qvtkWidget->update();
	

}
//txt转多条点云叠加
void ConnectCamera::txt2MutiPc(string txt,float step, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr new_cloud(new pcl::PointCloud<pcl::PointXYZ>());
	//将string转为qstring，这样方便后面操作，qstring中提供了很多方法
	QString qtxt = QString::fromStdString(txt);
	//将string按照换行符进行分割，保存在一个QStringList中，其实相当于vector<string>,可以用数组方式索引
	QStringList qtxtlist = qtxt.split("\n");
	//ply文件中第四行是存储元素个数的信息，将其提取出来，并按照空格分割，这样数字部分就在该list的第二个索引中
	QStringList qsizelist = qtxtlist[3].split(" ");
	//讲元素个数提取出来赋予点云对象
	int points_size = qsizelist[2].toInt();
	new_cloud->height = 1;
	new_cloud->width = points_size;
	new_cloud->resize(new_cloud->height * new_cloud->width);

	for (int i = 0; i < new_cloud->size(); i++)
	{
		//坐标是从第八行开始的，所以索引加个8
		QStringList datalist = qtxtlist[i + 8].split(" ");
		//每一行代表一个点的三维坐标，提取出来并存到点云对象中
		new_cloud->points[i].x = datalist[0].toDouble();
		new_cloud->points[i].y = pc_num * step;//y轴方向上累加
		new_cloud->points[i].z = datalist[2].toDouble();

	}
	//叠加点云
	*cloud_ = *cloud_ + *new_cloud;
	pc_num++;
}

void ConnectCamera::showPcThread()
{
	//ui界面的操作只能放在主线程中，子线程不能包含ui界面操作
	//使用qt的多线程，需要自己定义一个线程类（继承于qthread类）然后重写该类中的虚函数run才可以

}

void ConnectCamera::closePc()
{
	viewer->removeAllPointClouds();
	viewer->removeAllShapes();
	viewer->removeAllCoordinateSystems();
	//同时将点云清空
	cloud->clear();
	pc_num = 0;
	//viewer->updatePointCloud("cloud");

	//总是会报错，不知道啥原因，暂时就用上面的语句来刷新整个窗口
	//ui.qvtkWidget->close();
	//viewer->~PCLVisualizer();
	ui.pushButton_showImg->setEnabled(true);
	ui.pushButton_closeImg->setEnabled(false);
}

void ConnectCamera::savePcd()
{
	char filename[256] = { 0 };
	CTime currTime;                                     // 获取系统时间作为保存图片文件名
	currTime = CTime::GetCurrentTime();
	sprintf(filename, ("%.4d%.2d%.2d%.2d%.2d%.2d.pcd"), currTime.GetYear(), currTime.GetMonth(),
		currTime.GetDay(), currTime.GetHour(), currTime.GetMinute(), currTime.GetSecond());
	pcl::PCDWriter w;
	if (ui.checkBox_isBinary->isChecked())
	{
		if (w.write(filename, *cloud, true) < 0)
		{
			QMessageBox::about(this, "warning", QString::fromLocal8Bit("保存失败"));
		}
		QMessageBox::about(this, "information", QString::fromLocal8Bit("保存成功"));
		

	}
	if (w.write(filename, *cloud, false) < 0)
	{
		QMessageBox::about(this, "warning", QString::fromLocal8Bit("保存失败"));
	}
	QMessageBox::about(this, "information", QString::fromLocal8Bit("保存成功"));


}
//执行一次
void ConnectCamera::doOnce()
{
	
	//软触发模式下执行一次
	int nRet = MV_STA_SetCommandValue(m_handle, "TriggerSoftware");
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Execute Once failed! err code:" + QString::number(nRet));
		
	}
	//采集一次之后需要更新显示的点云
	showPc();

}

void ConnectCamera::autoDo()
{
#if 0
	int nRet;
	if (ui.checkBox_autoDo->isChecked())
	{
		ui.pushButton_doOnce->setEnabled(false);
		//暂时找不到海康自动的自动执行的命令，只能自己写个循环不断执行
		//但这里需要把它放在另一个线程，不然再次点击复选框会没反应的
		//2022.1.8,测试显示，开启之后，虽然确实是在自动执行，但却堵塞了其他线程，需要另开一个线程
		//2022706,使用count计数，当count大于指定数字之后，就跳出循环，然后再执行一次显示点云，这样就不会卡死了
		//但这种方式无法实际应用。海康威视软件上实现过程是，当用户点击自动运行之后，相机就会按照指定的帧率一直采集数据，当
		//采集到指定的数量时，就将点云渲染出来，在这个过程中，点云不是动态增加的。
		//我们想要实现的方案是：当用户点击自动运行之后，相机按照指定帧率采集，同时一边采集，窗口还会一边动态显示
		//这里必须用到多线程编程，具体步骤：用户点击自动运行之后，新建一个线程，这个线程会一直给相机发送采集信号
		//发了信号之后，前面的采集线程会采集数据。如果这里要动态显示点云，必须使用主线程来显示，但要动态显示的话
		//就必须一直循环，而这样还是会使整个界面卡死，怎么办？继续使用一个计数变量，如果点云数达到指定数量，就让
		//显示线程跳出循环
		int count = 0;
		while (ui.checkBox_autoDo->isChecked())
		{
			if (count > 100)
			{
				break;
			}
			Sleep(10);
			if (ui.checkBox_autoDo->isChecked())
			{
				nRet = MV_STA_SetCommandValue(m_handle, "TriggerSoftware");
				if (MV_STA_OK != nRet)
				{
					QMessageBox::about(this, "warning!", "Execute Once failed! err code:" + QString::number(nRet));
					break;
				}
				
				count++;
			}
			else
			{
				    break;
			}
			
			
		}
		showPc();

	}
	else
	{
		ui.pushButton_doOnce->setEnabled(true);

	}
#endif
	//类型转换无效
	/*typedef void  (*CallBack_Pointer) (void *);
	CallBack_Pointer call_pointer = (CallBack_Pointer) (&ConnectCamera::autoDo_CallBack);
	std::thread autoStart(call_pointer);*/
	//不报错，但逻辑不知道对不对

	std::thread autoStart(&ConnectCamera::autoDo_CallBack, this);
	//先用join的方式堵塞主线程，这意味着在采集数据的时候，主线程将会等待，直到用户取消采集数据
	//堵塞后发现点击不了界面了，直接卡死，还是得用分离线程
	//autoStart.join();
	//尽量不用分离线程的方式，不可控，容易出bug
	//分离线程之后，界面没有卡死，但是报错说控件不能在不同的线程之间共享数据
	//拿到数据了，但是他没法在qvtk控件中实时显示
	autoStart.detach();
	//QMessageBox::about(this, "warning", "clicked");

}
void ConnectCamera::autoDo_button()
{
	//将本身按钮
	if (ui.checkBox_autoDo->isChecked())
	{
		//不能重复点击自动执行按钮，不然会挂起多个线程，所以点击一次之后要将其置为不可选
		ui.pushButton_doOnce->setEnabled(false);
		ui.pushButton_autodo->setEnabled(false);
		autoDo();
	}
	else
	{
		QMessageBox::about(this, "warning", QString::fromLocal8Bit("请勾选自动执行复选框"));
	}
	
}
//复选框状态改变函数,控制checkBoxState这个变量值与复选框状态同步
//使用这个中间变量来解决子线程中无法操作控件的问题
void ConnectCamera::checkbox_autodo()
{
	if (ui.checkBox_autoDo->isChecked())
	{
		checkBoxState = 1;
	}
	else
	{
		checkBoxState = 0;
		//子线程要结束了，这时候应该把单次执行和自动执行按钮都置为可选
		
		if (!ui.pushButton_autodo->isEnabled())
		{
			ui.pushButton_autodo->setEnabled(true);
		}
		if (!ui.pushButton_doOnce->isEnabled())
		{
			ui.pushButton_doOnce->setEnabled(true);
		}
		//数据采集完了，得开始显示
		//显示的时候，只显示了一部分点云，再点击一次单次执行，就把数据全部显示了，不知为啥
		//休眠一会，等采集数据的线程把数据采完,这样还是不行，使用线程结束标志来精准控制
		//只有线程结束之后，才显示点云
		//线程没结束就会一直卡在这个循环里
		//还是一样问题，我是等线程结束之后才显示点云的，为什么还是这样
		//有可能是叠加点云的线程滞后于发送采集信号的线程
		while (autodo_thread_over)
		{

		}
		//发送采集信号的线程结束之后，再等4秒，等叠加点云的线程把数据叠加完
		//这样做之后基本没问题了，但又有一个新问题
		//保存的点云显示有800多条线，实际上确实也有那么多行，但显示出来就只有60多条，而且点云中的y最大也就5900
		//估计还是信号线程和采集线程的之间同步的问题
		Sleep(4000);
		showPc();

	}
}
//类内成员函数无法当 做回调函数，需要解决
//使用thread类，第二个参数只需要传类的对象就行，这里也就是this
void ConnectCamera::autoDo_CallBack()
{
	//子线程中不应该操作控件
	int nRet;
	while (checkBoxState)
	{
		if (checkBoxState)
		{
			nRet = MV_STA_SetCommandValue(m_handle, "TriggerSoftware");
			if (MV_STA_OK != nRet)
			{
				QMessageBox::about(this, "warning!", "Execute Once failed! err code:" + QString::number(nRet));
				break;
			}

		}
		else
		{
			break;
		}
	}
	autodo_thread_over = 0;
	
}

void ConnectCamera::switchSoft()
{
	//触发模式开，可以设置触发源，触发源有软触发，也有硬触发，硬触发其实就是通过接受编码器的差分信号，收到一个信号采集一张
	//实际应用中，软触发精度不高，一般都是用硬触发，外接一个平移台或者旋转台，通过接收平移台中的电机发出的信号来采集图像
	//本例因为没有外接电机，所以暂时使用软触发进行实验
	int nRet = MV_STA_SetEnumValue(m_handle, "TriggerMode", MV_STA_TRIGGER_MODE_ON);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Set TriggerMode On failed! err code:" + QString::number(nRet));

	}
	//设置触发源为软触发
	nRet = MV_STA_SetEnumValue(m_handle, "TriggerSource", MV_STA_TRIGGER_SOURCE_SOFTWARE);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Set TriggerSource Software failed! err code:" + QString::number(nRet));

	}

	ui.pushButton_doOnce->setEnabled(true);
	//ui.pushButton_autoDo->setEnabled(true);
	ui.pushButton_switch->setEnabled(true);
	ui.checkBox_autoDo->setEnabled(true);
	ui.pushButton_switch_soft->setEnabled(false);
}

void ConnectCamera::switchInside()
{
	//触发模式关，转为内触发模式
	//内触发模式其实就是相机通过自身内部的信号控制采集图像
	//但这种方式因为是相机自身控制的，外界不能控制，所以相机就会一直采集，实际应用中基本不会用这种模式
	int nRet = MV_STA_SetEnumValue(m_handle, "TriggerMode", MV_STA_TRIGGER_MODE_OFF);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Set TriggerMode Off failed! err code:" + QString::number(nRet));

	}
	ui.pushButton_doOnce->setEnabled(false);
	//ui.pushButton_autoDo->setEnabled(false);
	ui.pushButton_switch->setEnabled(false);
	ui.checkBox_autoDo->setEnabled(false);
	ui.pushButton_switch_soft->setEnabled(true);
}
