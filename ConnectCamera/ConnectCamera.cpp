#include "ConnectCamera.h"
//�������Ƕ�vtk��ʼ������Ȼ����ʾ��ʱ��ᱨ��
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

int ConnectCamera::pc_num = 0;//��������
int ConnectCamera::checkBoxState = 0;//��ѡ��״̬��־
int ConnectCamera::autodo_thread_over = 1;//�ɼ������߳̽�����־
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
	//�����豸
	connect(ui.pushButton_findCam, &QPushButton::clicked, this, &ConnectCamera::findCam);
	//�������
	connect(ui.pushButton_connect, &QPushButton::clicked, this, &ConnectCamera::connectCam);
	//�ر��豸
	connect(ui.pushButton_close, &QPushButton::clicked, this, &ConnectCamera::closeDevice);
	//��ȡ����
	connect(ui.pushButton_getPara, &QPushButton::clicked, this, &ConnectCamera::getParameter);
	//���ò���
	connect(ui.pushButton_setPara, &QPushButton::clicked, this, &ConnectCamera::setParameter);
	//��ʼ�ɼ�
	connect(ui.pushButton_start, &QPushButton::clicked, this, &ConnectCamera::startGrab);
	//ֹͣ�ɼ�
	connect(ui.pushButton_stop, &QPushButton::clicked, this, &ConnectCamera::stopGrab);
	//����Ϊply
	connect(ui.pushButton_savePly, &QPushButton::clicked, this, &ConnectCamera::savePly);
	//��ʾ����ͼ
	connect(ui.pushButton_showImg, &QPushButton::clicked, this, &ConnectCamera::showPc);
	//�رյ���ͼ
	connect(ui.pushButton_closeImg, &QPushButton::clicked, this, &ConnectCamera::closePc);
	//����pcd�ļ�
	connect(ui.pushButton_savePcd, &QPushButton::clicked, this, &ConnectCamera::savePcd);
	//�л�Ϊ�ڴ���ģʽ
	connect(ui.pushButton_switch, &QPushButton::clicked, this, &ConnectCamera::switchInside);
	//����ģʽ��ִ��һ��
	connect(ui.pushButton_doOnce, &QPushButton::clicked, this, &ConnectCamera::doOnce);
	//����ģʽ���Զ�ִ��
	//clicked�ź�����ֻҪ����˸�ѡ��ͻᷢ���źţ�����ζ�ŵ���ȡ����ѡ��ʱ��Ҳ�ᷢ���ź�
	//������������һ����ť��ͨ����������ť��ʵ�������ɼ����߳�
	connect(ui.pushButton_autodo, &QPushButton::clicked, this, &ConnectCamera::autoDo_button);
	//��ѡ��״̬
	connect(ui.checkBox_autoDo, &QCheckBox::clicked, this, &ConnectCamera::checkbox_autodo);
	//�л�Ϊ����ģʽ
	connect(ui.pushButton_switch_soft, &QPushButton::clicked, this, &ConnectCamera::switchSoft);


}



//��ѯ�豸
void ConnectCamera::findCam()
{
	int nRet = MV_STA_OK;
	
	string cstrInfo;

	// ���洢�豸�Ľṹ���ʼ����ȫ������0��
	//memset����һ��������������ڴ��ʼ������һ��������Ҫ��ʼ���ı������ڶ�������ʲôֵ���г�ʼ����һ����0���������ǳ�ʼ���Ĵ�С
	memset(&m_stDeviceInfoList, 0, sizeof(MV_STEREOCAM_NET_INFO_LIST));
	//ö���豸��Ϣ
	nRet = MV_STA_EnumStereoCam(&m_stDeviceInfoList);//ö���������
	if (MV_STA_OK != nRet)
	{
		//cstrInfo.Format(_T("Enum Device failed! err code:%#x"), nRet);
		//MessageBox(cstrInfo);
		QMessageBox::about(this, "Error!", "Enum Device failed!");
		return;
	}
	
	// ��ʾ���ҵ����豸��Ϣ,��ʱֻ��һ̨�豸�����Բ���ѭ��
	//�豸��ID��Ϣ���ܹ����ĶΣ�ip4��������ߵ�
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

	//UpdateData(TRUE);//��ʱ�Ҳ�����������Ķ���

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

	// ��ȡ��ǰѡ����豸��Ϣ,ֻ��һ̨�豸�����Բ���Ҫѡ����������0
	
	memcpy(&m_stDeviceInfo, m_stDeviceInfoList.pDeviceInfo[0], sizeof(MV_STEREOCAM_NET_INFO));


	// �����豸���
	nRet = MV_STA_CreateHandleByCameraInfo(&m_handle, m_stDeviceInfoList.pDeviceInfo[0]);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Create handle failed! err code:" + QString::number(nRet));
		
		return;
	}

	//�����豸������õ������ַ��m_handle
	nRet = MV_STA_OpenDevice(m_handle);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Open device failed! err code:" + QString::number(nRet));
		
		return;
	}

	// ��ȡ����,��ʱû��ʵ��
	getParameter();
	m_bConnect = true;

	// ��ʼ����Ҫ����Դ
	InitResources();
	//������֮�����Ӱ�ťӦ�ñ����
	ui.pushButton_connect->setEnabled(false);
	ui.pushButton_close->setEnabled(true);
	ui.pushButton_start->setEnabled(true);
	ui.pushButton_stop->setEnabled(false);
	ui.pushButton_savePly->setEnabled(false);
	ui.pushButton_savePcd->setEnabled(false);
	

	
}
//��ȡ����
void ConnectCamera::getParameter()
{
	int nRet = MV_STA_OK;
	//CString cstrInfo;

	// ��ȡ�ع�ʱ��
	float fExposureTime = 0.0f;
	MV_STA_FLOATVALUE stParam;
	memset(&stParam, 0, sizeof(MV_STA_FLOATVALUE));
	//��ȡ������ع���������ֵ�������������������õģ��ڶ�������ָ����ȡ�ع�
	nRet = MV_STA_GetFloatValue(m_handle, EXPOSURE_TIME, &stParam);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Set exposure time failed! err code:" + QString::number(nRet));
		
		
	}
	else
	{
		fExposureTime = stParam.fCurValue;
		//���ع�ֵ�����ı��ؼ�
		ui.lineEdit_expo->setText(QString::number(fExposureTime));
		
	}

	// ��ȡ����
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

	// ��ȡ֡��
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
//���ò���
void ConnectCamera::setParameter()
{
	
	bool bHasError = false;

	// TODO: Add your control notification handler code here
	int nRet = MV_STA_OK;
	

	// �����ع�ʱ��
	float fExposureTime = 0.0f;
	fExposureTime = ui.lineEdit_expo->text().toFloat();
	
	nRet = MV_STA_SetFloatValue(m_handle, EXPOSURE_TIME, fExposureTime);
	if (MV_STA_OK != nRet)
	{
		bHasError = true;
		QMessageBox::about(this, "warning!", "Set exposure time failed! err code:" + QString::number(nRet));
		
	}

	// ��������
	float fGain = 0.0f;
	fGain = ui.lineEdit_gain->text().toFloat();
	
	nRet = MV_STA_SetFloatValue(m_handle, GAIN, fGain);
	if (MV_STA_OK != nRet)
	{
		bHasError = true;
		QMessageBox::about(this, "warning!", "Set gain failed! err code:" + QString::number(nRet));
		
	}

	// ����֡��
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
//��ʼ�ɼ�
void ConnectCamera::startGrab()
{
	int nRet = MV_STA_OK;
	

	if (NULL != hProcessThread)
	{
		m_bStartJob = false;
		// �ȴ��߳���ɣ�����Ƕ��̵߳ģ���Ҫ���� WaitForMultipleObjects
		WaitForSingleObject(hProcessThread, INFINITE);
		//CloseHandle�ǹر��߳̾��,�����ͷ��߳���Դ��,������ֹ�̵߳�
		// ����һ�μǵ��ͷ�һ���߳���Դ
		CloseHandle(hProcessThread);
		hProcessThread = NULL;
	}


	m_bStartJob = true;
	// �������� �����߳�
	/*CreateThread��c++�д����̵߳ĺ��������е�һ��������ȫ���ã��ڶ�������ջ��С������������ں���
	���ĸ�����ں����Ĳ�������������ڳ�Ա��������������һ��void*ָ�룬�����൱�ڰѵ�ǰ���ڵ����߳�
	��ַ�����������ݽ�ȥ�ˡ����������ѡ�
	ProcessThread��ʵ�ǻص�����������ɼ����ݺ�
	����ԭʼ������תΪply��pcd�ȸ��ֱ�׼��ʽ����*/
	hProcessThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProcessThread, this, 0, NULL);
	if (NULL == hProcessThread)
	{
		QMessageBox::about(this, "warning!", "Create proccess Thread failed" );
		
	}


	// ��ʼ��������
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
//��Ⱦ�̣߳�__stdcall�ǲ�������Լ��������Լ����ζ�Ų�����������ѹ���ջ����
//�����õ��ؼ�����stImg
//�ص�����������ɼ�ԭʼ���ݣ����Ұ�ԭʼ����ת��ply��pcd�ȱ�׼���ݡ������и�whileѭ������һֱ�ɼ�

//�ص������������裺���ȴ��豸�вɼ���ԭʼ������ori��
//Ȼ��ʹ��getData��������תΪ��׼ͼ������stImg
//����ʹ��MV_STA_SavePly������stImgתΪstPlyImage,��ΪstPlyImage������ʵ������unsigned char���͵�
//���Խ���ǿת���ַ�����������Լ�дһ���ַ���ת���Ƶĺ���txt2pc

void * __stdcall ConnectCamera::ProcessThread(void * pUser)
{
	int nRet = MV_STA_OK;
	//����Ӧ�ðѵ�ǰ����ָ�봫�ݽ���
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
	//ֻҪ��ֹͣ�ɼ������ѭ���ͻ�һֱ��
	while (pThis->m_bStartJob)
	{
		// ��ȡͼ������

		nRet = MV_STA_ReceiveDataTimeout(pThis->m_handle, &DataSet, 100);
		if ((MV_STA_OK == nRet) &&
			(NULL != DataSet) && pThis->m_bStartJob)  //����֡�ʹ��ߣ���ʹͣ��Ҳ�ڴ�������
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
					//��һ���õ���Ҫ����stImg
					if (STC_DATA_MSG_TYPE_IMG_RAW == nMsgType)
					{
						STC_DATA_IMAGE stImg = { 0 };
						//�õ���ά���ȡ��������stImg
						nRet = MV_STA_GetImage(DataObj, &stImg);
						if (0 != nRet)
						{
							printf("MV_STA_GetImage failed, errcode (%#x)!\r\n", nRet);
							throw nRet;
						}
						else
						{
							printf("MV_STA_GetImage success: framenum (%d) hight(%d) width(%d)  len (%d)!\r\n", stImg.nFrameNum, stImg.nHeight, stImg.nWidth, stImg.nFrameLen);


							//����������ʾͼ��ͬʱ��Ϊ���汣��ͼ����ǰ����m_stImageInfo��m_pcDataBuf������ע��
							//��������stImg��ԭʼ���ݣ������Լ�д��������ֻ��ȡ���ڱ�����Ƶ����ݣ���ʹ�����������ʾ����
							//�����������
							//��getData�����������display������ʾ���ƺ���ȡ���ݷ��뿪
							//����ɹ����Ϳ��Բ���display�����Լ������������draw������convert���������Լ��󾫼����
							//������ɾ��hdc��ʾͼ��Ĵ��룬Ȼ������pcl�Ŀ���õ��ĵ��ƽ�����ʾ
							//2022.1.6�����Գɹ�
							//�ȴ��豸��ȡ����ԭʼ�����ݣ�������ת�ɱ�׼ͼƬ����
							nRet = pThis->getData(pThis->m_handle, &stImg);
							//nRet = pThis->Display(pThis->m_handle, pThis->m_hWndDisplay, &stImg);
							
							//��Դ����תΪ���ƶ���
							int nRet = MV_STA_OK;
							QString  cstrInfo = "";

							// �ж��Ƿ�ʼȡ��
							if (!pThis->m_bConnect)
							{
								QMessageBox::about(pThis, "warning!", "No camera Connected!");

							}

							if (!pThis->m_bStartJob)
							{
								QMessageBox::about(pThis, "warning!", "The camera is not startJob!");

							}

							// �ж��Ƿ�����Ч����
							//�����m_stImageInfo����display�����л���ģ�����display����������ȫע�ͣ����ǿ��԰���ʾ���ֽ��и���
							//ԭʼ�����ݱ�����m_pcDataBuf�����ֽ���ʽ
							if (NULL == pThis->m_pcDataBuf)
							{
								QMessageBox::about(pThis, "warning!", "No data��Save PLY failed!");

							}

							if (0 == pThis->m_stImageInfo.nFrameLen)
							{
								QMessageBox::about(pThis, "warning!", "No Data, save nothing !");

							}

							//�����õ���ά����ɨ���ǵĸ�ʽ��Gvsp_Coord3D_ABC16����Gvsp_Coord3D_ABC32
							if ((STC_PixelType_Gvsp_Coord3D_ABC16 == pThis->m_stImageInfo.enPixelType) ||
								(STC_PixelType_Gvsp_Coord3D_ABC32 == pThis->m_stImageInfo.enPixelType))
							{
								pThis->m_criSection.Lock();

								try
								{


									// ֱ��save
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
									//��һ��������ݷ�װ�������ָ�ʽ3DͼתΪply��ʽ
									//�ؼ�����stImg���ݷ�װ�ɱ�׼ply����
									nRet = MV_STA_SavePly(pThis->m_handle, &stPlyImage);
									if (MV_STA_OK != nRet)
									{
										QMessageBox::about(pThis, "warning!", "MV_STA_SavePly failed");

										throw nRet;
									}
									//��pcl�ĺ�������ply�ļ�
									//pcl::PointCloud<pcl::PointXYZ> * cloud (new pcl::PointCloud<pcl::PointXYZ>());
									/*pcl::PointCloud<pcl::PointXYZ> * cloud = NULL;
									cloud = (pcl::PointCloud<pcl::PointXYZ> *) malloc(stPlyImage.nDstBufLen);
									memset(cloud, 0, stPlyImage.nDstBufLen);
									memcpy(cloud, stPlyImage.pDstBuf, stPlyImage.nDstBufLen);
									pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_share = cloud->makeShared();
									pcl::io::savePLYFile("text.ply",*cloud_share);*/
									//����ȫ��һ�ַ�ʽ,��Ч����Ϊ����ָ�벻��pod���ͣ��޷�ǿ��ת��
									//��Ȼת���ɹ��������������޷���ȡ�ģ�ʧ��
									//pcl::PointCloud<pcl::PointXYZ> * pThing = static_cast<pcl::PointCloud<pcl::PointXYZ> *> (stPlyImage.pDstBuf);
									//pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
									/*��������ɹ�,��Դ���Ͻ�������pDstBuf��unsigned char*���͵�����
									���������͵�����תΪ�ַ����Ƚ�����*/
									//���Ȱ�void *ǿתΪunsigned char *
									unsigned char * str = (unsigned char *)stPlyImage.pDstBuf;
									string res = "";
									//��һ���ؼ�����unsigned char *תΪ�ַ���
									res.append(reinterpret_cast<const char*>(str));
									QString r = QString::fromStdString(res);
									//����Ҫ�Լ�дһ����ȡtxtΪ���ƶ���ĺ���
									//ConnectCamera::txt2pc(res, pThis->cloud);
									//���Ӷ�������
									ConnectCamera::txt2MutiPc(res, 100,pThis->cloud);

									//����̻߳᲻��ִ�У������ӻ���������һ�ԣ�����֮��ᱨ��
									//�������⿪��һ���߳�ִ�п��ӻ�
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
							//		// ����ͼ��ת��Ϊ��׼ͼ
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
					//���漸�β��Ǳ������Ҫʹ�õĴ��룬�ɺ���
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
//ֹͣ�ɼ�
void ConnectCamera::stopGrab()
{
	int nRet = MV_STA_OK;
	

	m_bStartJob = false;
	// ֹͣ��������
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

//��ʾͼ��ͬʱ��ԭʼ���ݻ������������ں��汣��ɸ��ָ�ʽ���ļ�
//���벻�ʺϱ�������Ϊ������mfc��ʾ��ͼ�񣬶�������ֱ������PCL��ʾ���ƶ���
//����д��getData������������display

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


	// ��ʾͼ����һ�ο���ע�ͣ�����ʾͼ��Ĺ��ܷ���qvtkwidget��
	//ʹ��hdc��ʾ����Ҫ��releaseģʽ�²ſ��ԣ����ڲ�֪��ԭ���ڱ����У���ʾ����opengl�����²���������ʾ
	HDC hDC = ::GetDC((HWND)hWnd);
	SetStretchBltMode(hDC, COLORONCOLOR);
	RECT wndRect;
	::GetClientRect((HWND)hWnd, &wndRect);


	//��ǰ����˫Ŀ�����ʾ��Mono12 ʵ���� Mono16
	//˫Ŀ�����MV-DB��MV-DS����
	if (STC_PixelType_Gvsp_Mono12 == pstDisplayImage->enPixelType && ((0 == memcmp(m_stDeviceInfo.chModelName, "MV-DB", 5)) ||
		(0 == memcmp(m_stDeviceInfo.chModelName, "MV-DS", 5))))
	{
		pstDisplayImage->enPixelType = STC_PixelType_Gvsp_Mono16;
	}


	{
		// �������������ڱ���ͼƬ
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

		// ����ͼƬ��Ϣ & ͼƬ��//�Ѵ�������ԭʼ����pstDisplayImage���Ƹ��Զ����m_stImageInfo�ṹ��
		//m_stImageInfo��m_pcDataBuf�Ǻ���save�õ���Ϣ
		memcpy((void *)&m_stImageInfo, pstDisplayImage, sizeof(STC_DATA_IMAGE));
		if (NULL != pstDisplayImage->pData)
		{
			//�Ѵ�������ԭʼ����pstDisplayImage���Ƹ��Զ����m_pcDataBuf�������ֽ����ݣ�
			memcpy(m_pcDataBuf, pstDisplayImage->pData, pstDisplayImage->nFrameLen);
		}
		m_criSection.Unlock();
	}



	//���Ƕ�mono8���ݵĲ���,һ���Ƕ�ά���������
	if (STC_PixelType_Gvsp_Mono8 == pstDisplayImage->enPixelType)
	{
		// mono8 ֱ����Ⱦ
		MV_CODEREADER_DRAW_PARAM stParam;    // �Լ������Ľṹ��

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

		// ���ṹ�帳ֵ
		stParam.hDC = hDC;
		stParam.nDstX = nDstX;
		stParam.nDstY = nDstY;
		stParam.nImageHeight = nImageHeight;
		stParam.nImageWidth = nImageWidth;
		stParam.nWndRectHeight = nWndRectHeight;
		stParam.nWndRectWidth = nWndRectWidth;

		stParam.pData = pstDisplayImage->pData;
		//drawd��ʹ�ã����漰mono8���ݣ�ֱ��ע��
		//nRet = Draw(&stParam);
		if (MV_STA_OK != nRet)
		{
			return MV_STA_E_PARAMETER;
		}

	}
	//��mono16��3D���ݣ����Ǳ����ص����ģ���Ϊ�õ�����ά�߽ṹ��ɨ����
	//�����ǰ���ȶ�ת�ɱ�׼ͼ
	else if ((STC_PixelType_Gvsp_Mono16 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_C32 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_C16 == pstDisplayImage->enPixelType))
	{
		STC_DEPTH_MAP_DISPLAY_EX  stDisplayExInfo = { 0 };
		if ((STC_PixelType_Gvsp_Coord3D_C32 == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_C16 == pstDisplayImage->enPixelType))
		{

			// ���ͼ��ת��Ϊ��׼ͼ����Ⱦ
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

			// ֧�����Ͻ���ʾˮӡ
#if 0
			memcpy(stDisplayExInfo.szImageWatermark, "HKVISION", sizeof("HKVISION"));

			// ֧����ʾ������λ��  ��ʵ�����꣩
			stDisplayExInfo.szPackageRoi.bSupport = true;
			stDisplayExInfo.szPackageRoi.point[0].x = 100;
			stDisplayExInfo.szPackageRoi.point[0].y = 100;
			stDisplayExInfo.szPackageRoi.point[1].x = 500;
			stDisplayExInfo.szPackageRoi.point[1].y = 500;
			stDisplayExInfo.szPackageRoi.point[2].x = 500;
			stDisplayExInfo.szPackageRoi.point[2].y = 800;
			stDisplayExInfo.szPackageRoi.point[3].x = 100;
			stDisplayExInfo.szPackageRoi.point[3].y = 800;

			// ֧����ʾ���������λ��  (����ͼ��1���˴��Ǳ�����
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
	//��mono16��3D���ݣ����Ǳ����ص����ģ���Ϊ�õ�����ά�߽ṹ��ɨ���ǣ������ĸ�ʽ��Coord3D_ABC16��32������ִ������һ��
	//�����ǰѵ���ͼת��׼ͼ
	else if ((STC_PixelType_Gvsp_Coord3D_ABC32f == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_AC32 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC16 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32 == pstDisplayImage->enPixelType))
	{
		// ����ͼ��ת��Ϊ��׼ͼ����Ⱦ

		if ((STC_PixelType_Gvsp_Coord3D_AC32 == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32f == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32 == pstDisplayImage->enPixelType))
		{
			// ����ͼ��ת��Ϊ��׼ͼ����Ⱦ
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

			//������ֱ����ʾ�ڴ�����
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
		// ��֧��

	}


	::ReleaseDC((HWND)hWnd, hDC);
	return nRet;
}
#endif

//���ڲ��ԣ����ܷ񾫼�����õ�����
//����ɹ����Ϳ��Բ���display�����Լ������������draw������convert���������Լ��󾫼����
//2022.1.6,�ƹ�display������ʹ��getdata�����ɹ��õ����Դ���ݣ��ɹ��������
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
	
	//��ǰ����˫Ŀ�����ʾ��Mono12 ʵ���� Mono16
	//˫Ŀ�����MV-DB��MV-DS����
	if (STC_PixelType_Gvsp_Mono12 == pstDisplayImage->enPixelType && ((0 == memcmp(m_stDeviceInfo.chModelName, "MV-DB", 5)) ||
		(0 == memcmp(m_stDeviceInfo.chModelName, "MV-DS", 5))))
	{
		pstDisplayImage->enPixelType = STC_PixelType_Gvsp_Mono16;
	}


	{
		// �������������ڱ���ͼƬ
		//��һ���Ǳ����ĺ��ģ���ɨ�������ݴ���pstDisplayImage����ָ����
		//����һϵ�е�ѡ���ж���䱾�����ò��ϣ���֧����������Ĵ���
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

		// ����ͼƬ��Ϣ & ͼƬ��//�Ѵ�������ԭʼ����pstDisplayImage���Ƹ��Զ����m_stImageInfo�ṹ��
		//m_stImageInfo��m_pcDataBuf�Ǻ���save�õ���Ϣ
		memcpy((void *)&m_stImageInfo, pstDisplayImage, sizeof(STC_DATA_IMAGE));
		if (NULL != pstDisplayImage->pData)
		{
			//�Ѵ�������ԭʼ����pstDisplayImage���Ƹ��Զ����m_pcDataBuf�������ֽ����ݣ�
			memcpy(m_pcDataBuf, pstDisplayImage->pData, pstDisplayImage->nFrameLen);
		}
		m_criSection.Unlock();
	}

//��ʹ�õ��������MV-DP2305ϵ�е����������ʹ���������
#if 0
	//���Ƕ�mono8���ݵĲ���,һ���Ƕ�ά��������ݣ������ò���
	if (STC_PixelType_Gvsp_Mono8 == pstDisplayImage->enPixelType)
	{
		// mono8 ֱ����Ⱦ
		//MV_CODEREADER_DRAW_PARAM stParam;    // �Լ������Ľṹ��

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

		//// ���ṹ�帳ֵ
		//stParam.hDC = hDC;
		//stParam.nDstX = nDstX;
		//stParam.nDstY = nDstY;
		//stParam.nImageHeight = nImageHeight;
		//stParam.nImageWidth = nImageWidth;
		//stParam.nWndRectHeight = nWndRectHeight;
		//stParam.nWndRectWidth = nWndRectWidth;

		//stParam.pData = pstDisplayImage->pData;
		////drawd��ʹ�ã����漰mono8���ݣ�ֱ��ע��
		////nRet = Draw(&stParam);
		//if (MV_STA_OK != nRet)
		//{
		//	return MV_STA_E_PARAMETER;
		//}

	}
	//��mono16��3D���ݣ����Ǳ����ص����ģ���Ϊ�õ�����ά�߽ṹ��ɨ����
	//�����ǰ���ȶ�ת�ɱ�׼ͼ�������ò���
	else if ((STC_PixelType_Gvsp_Mono16 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_C32 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_C16 == pstDisplayImage->enPixelType))
	{
		STC_DEPTH_MAP_DISPLAY_EX  stDisplayExInfo = { 0 };
		if ((STC_PixelType_Gvsp_Coord3D_C32 == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_C16 == pstDisplayImage->enPixelType))
		{

			// ���ͼ��ת��Ϊ��׼ͼ����Ⱦ
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
	//��mono16��3D���ݣ����Ǳ����ص����ģ���Ϊ�õ�����ά�߽ṹ��ɨ���ǣ������ĸ�ʽ��Coord3D_ABC16��32������ִ������һ��
	//�����ǰѵ���ͼת��׼ͼ������ִ�е�����һ��
	else if ((STC_PixelType_Gvsp_Coord3D_ABC32f == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_AC32 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC16 == pstDisplayImage->enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32 == pstDisplayImage->enPixelType))
	{
		// ����ͼ��ת��Ϊ��׼ͼ����Ⱦ
		//�����⣬��Ҳû��ִ����һ�Σ�ֱ���������
		if ((STC_PixelType_Gvsp_Coord3D_AC32 == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32f == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32f_Planar == pstDisplayImage->enPixelType) ||
			(STC_PixelType_Gvsp_Coord3D_ABC32 == pstDisplayImage->enPixelType))
		{
			// ����ͼ��ת��Ϊ��׼ͼ����Ⱦ
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

			////������ֱ����ʾ�ڴ�����
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
		// ��֧��

	}

#endif
	//::ReleaseDC((HWND)hWnd, hDC);
	return nRet;
}

//Drawֻ��mono8��ʹ���ˣ�����ʹ�õ�����ά���ݣ�����ֱ��ע��

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
//	// λͼ��Ϣͷ
//	m_bBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);             // BITMAPINFOHEADER�ṹ����
//	m_bBitmapInfo->bmiHeader.biWidth = nImageWidth;                         // ͼ����
//	m_bBitmapInfo->bmiHeader.biPlanes = 1;                                  // λ����
//	m_bBitmapInfo->bmiHeader.biBitCount = 8;                                // ������/���ص���ɫ���,2^8=256
//	m_bBitmapInfo->bmiHeader.biCompression = BI_RGB;                        // ͼ������ѹ������,BI_RGB��ʾ��ѹ��
//	m_bBitmapInfo->bmiHeader.biSizeImage = nImageWidth * nImageHeight;      // ͼ���С
//	m_bBitmapInfo->bmiHeader.biHeight = -nImageHeight;                       // ͼ��߶�
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

//ConvertRGB8Planner2RGB8Packed��display���ʹ�ã������ò���
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

//��ʼ����Դ
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
//����ʼ����Դ
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
//����ply
void ConnectCamera::savePly()
{
	char filename[256] = { 0 };
	CTime currTime;                                     // ��ȡϵͳʱ����Ϊ����ͼƬ�ļ���
	currTime = CTime::GetCurrentTime();
	sprintf(filename, ("%.4d%.2d%.2d%.2d%.2d%.2d.ply"), currTime.GetYear(), currTime.GetMonth(),
		currTime.GetDay(), currTime.GetHour(), currTime.GetMinute(), currTime.GetSecond());
	pcl::PLYWriter w;
	if (ui.checkBox_isBinary->isChecked())
	{
		if (w.write(filename, *cloud, true) < 0)
		{
			QMessageBox::about(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ʧ��"));
		}
		QMessageBox::about(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����ɹ�"));


	}
	if (w.write(filename, *cloud, false) < 0)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ʧ��"));
	}
	QMessageBox::about(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����ɹ�"));
	//���Դ��룬��ʱ�ò���
#if 0
	int nRet = MV_STA_OK;
	QString  cstrInfo = "";

	// �ж��Ƿ�ʼȡ��
	if (!m_bConnect)
	{
		QMessageBox::about(this, "warning!", "No camera Connected!" );
		
	}

	if (!m_bStartJob)
	{
		QMessageBox::about(this, "warning!", "The camera is not startJob!");
		
	}

	// �ж��Ƿ�����Ч����
	//�����m_stImageInfo����display�����л���ģ�����display����������ȫע�ͣ����ǿ��԰���ʾ���ֽ��и���
	//ԭʼ�����ݱ�����m_pcDataBuf�����ֽ���ʽ
	if (NULL == m_pcDataBuf)
	{
		QMessageBox::about(this, "warning!", "No data��Save PLY failed!");
		
	}

	if (0 == m_stImageInfo.nFrameLen)
	{
		QMessageBox::about(this, "warning!", "No Data, save nothing !");
		
	}



	FILE* pfile;
	char filename[256] = { 0 };
	CTime currTime;                                     // ��ȡϵͳʱ����Ϊ����ͼƬ�ļ���
	currTime = CTime::GetCurrentTime();
	sprintf(filename, ("%.4d%.2d%.2d%.2d%.2d%.2d.ply"), currTime.GetYear(), currTime.GetMonth(),
		currTime.GetDay(), currTime.GetHour(), currTime.GetMinute(), currTime.GetSecond());

	//�����õ���ά����ɨ���ǵĸ�ʽ��Gvsp_Coord3D_ABC16����Gvsp_Coord3D_ABC32
	if ((STC_PixelType_Gvsp_Coord3D_ABC16 == m_stImageInfo.enPixelType) ||
		(STC_PixelType_Gvsp_Coord3D_ABC32 == m_stImageInfo.enPixelType))
	{
		m_criSection.Lock();

		try
		{


			// ֱ��save
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
			//��һ��������ݷ�װ�������ָ�ʽ3DͼתΪply��ʽ
			nRet = MV_STA_SavePly(m_handle, &stPlyImage);
			if (MV_STA_OK != nRet)
			{
				QMessageBox::about(this, "warning!", "MV_STA_SavePly failed");
				
				throw nRet;
			}
			//��pcl�ĺ�������ply�ļ�
			//pcl::PointCloud<pcl::PointXYZ> * cloud (new pcl::PointCloud<pcl::PointXYZ>());
			/*pcl::PointCloud<pcl::PointXYZ> * cloud = NULL;
			cloud = (pcl::PointCloud<pcl::PointXYZ> *) malloc(stPlyImage.nDstBufLen);
			memset(cloud, 0, stPlyImage.nDstBufLen);
			memcpy(cloud, stPlyImage.pDstBuf, stPlyImage.nDstBufLen);
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_share = cloud->makeShared();
			pcl::io::savePLYFile("text.ply",*cloud_share);*/
			//����ȫ��һ�ַ�ʽ,��Ч����Ϊ����ָ�벻��pod���ͣ��޷�ǿ��ת��
			//��Ȼת���ɹ��������������޷���ȡ�ģ�ʧ��
			//pcl::PointCloud<pcl::PointXYZ> * pThing = static_cast<pcl::PointCloud<pcl::PointXYZ> *> (stPlyImage.pDstBuf);
			//pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
			/*��������ɹ�,��Դ���Ͻ�������pDstBuf��unsigned char*���͵�����
			���������͵�����תΪ�ַ����Ƚ�����*/
			//���Ȱ�void *ǿתΪunsigned char *
			//unsigned char * str =(unsigned char *) stPlyImage.pDstBuf;
			//string res = "";
			////��һ���ؼ�����unsigned char *תΪ�ַ���
			//res.append(reinterpret_cast<const char*>(str));
			//QString r = QString::fromStdString(res);
			////����Ҫ�Լ�дһ����ȡtxtΪ���ƶ���ĺ���
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
			// ����ͼ��ת��Ϊ��׼ͼ
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
//�ر��豸�����ܺ���
void ConnectCamera::closeDevice()
{
	// TODO: Add your control notification handler code here
	int nRet = MV_STA_OK;
	

	// �����豸��� 
	if (NULL != m_handle)
	{
		// ֹͣ��������
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

			//�ȴ���Ⱦ�߳���ȫֹͣ
			if (NULL != hProcessThread)
			{
				// �ȴ��߳���ɣ�����Ƕ��̵߳ģ���Ҫ���� WaitForMultipleObjects
				WaitForSingleObject(hProcessThread, INFINITE);
				// ���رվ��
				CloseHandle(hProcessThread);
				hProcessThread = NULL;
			}
		}

		// ��ղ���ͼƬ,��ʱ����Ҫ��仰���������qvtk�ؼ��ٽ������ͼƬ
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

	//������Դ
	DeInitResources();

	// �ر��豸����ո����������,������qt�Ĵ���
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
	//��stringתΪqstring������������������qstring���ṩ�˺ܶ෽��
	QString qtxt = QString::fromStdString(txt);
	//��string���ջ��з����зָ������һ��QStringList�У���ʵ�൱��vector<string>,���������鷽ʽ����
	QStringList qtxtlist = qtxt.split("\n");
	//ply�ļ��е������Ǵ洢Ԫ�ظ�������Ϣ��������ȡ�����������տո�ָ�������ֲ��־��ڸ�list�ĵڶ���������
	QStringList qsizelist = qtxtlist[3].split(" ");
	//��Ԫ�ظ�����ȡ����������ƶ���
	int points_size = qsizelist[2].toInt();
	cloud_->height = 1;
	cloud_->width = points_size;
	cloud_->resize(cloud_->height * cloud_->width);
	
	for (int i = 0; i < cloud_->size(); i++)
	{
		//�����Ǵӵڰ��п�ʼ�ģ����������Ӹ�8
		QStringList datalist = qtxtlist[i+8].split(" ");
		//ÿһ�д���һ�������ά���꣬��ȡ�������浽���ƶ�����
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
	//����ĳ�������ֵ�Ե��ƽ�����Ⱦ����ɫΪ����ֵ����ɫΪ��Сֵ
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> render_color(cloud, "x");
	viewer->addPointCloud(cloud, render_color, "cloud");
	//������ʾ�ĵ���
	viewer->updatePointCloud(cloud, render_color,"cloud");
	
	//viewer->initCameraParameters();
	ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(ui.qvtkWidget->GetInteractor(), ui.qvtkWidget->GetRenderWindow());
	ui.qvtkWidget->update();
	

}
//txtת�������Ƶ���
void ConnectCamera::txt2MutiPc(string txt,float step, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr new_cloud(new pcl::PointCloud<pcl::PointXYZ>());
	//��stringתΪqstring������������������qstring���ṩ�˺ܶ෽��
	QString qtxt = QString::fromStdString(txt);
	//��string���ջ��з����зָ������һ��QStringList�У���ʵ�൱��vector<string>,���������鷽ʽ����
	QStringList qtxtlist = qtxt.split("\n");
	//ply�ļ��е������Ǵ洢Ԫ�ظ�������Ϣ��������ȡ�����������տո�ָ�������ֲ��־��ڸ�list�ĵڶ���������
	QStringList qsizelist = qtxtlist[3].split(" ");
	//��Ԫ�ظ�����ȡ����������ƶ���
	int points_size = qsizelist[2].toInt();
	new_cloud->height = 1;
	new_cloud->width = points_size;
	new_cloud->resize(new_cloud->height * new_cloud->width);

	for (int i = 0; i < new_cloud->size(); i++)
	{
		//�����Ǵӵڰ��п�ʼ�ģ����������Ӹ�8
		QStringList datalist = qtxtlist[i + 8].split(" ");
		//ÿһ�д���һ�������ά���꣬��ȡ�������浽���ƶ�����
		new_cloud->points[i].x = datalist[0].toDouble();
		new_cloud->points[i].y = pc_num * step;//y�᷽�����ۼ�
		new_cloud->points[i].z = datalist[2].toDouble();

	}
	//���ӵ���
	*cloud_ = *cloud_ + *new_cloud;
	pc_num++;
}

void ConnectCamera::showPcThread()
{
	//ui����Ĳ���ֻ�ܷ������߳��У����̲߳��ܰ���ui�������
	//ʹ��qt�Ķ��̣߳���Ҫ�Լ�����һ���߳��ࣨ�̳���qthread�ࣩȻ����д�����е��麯��run�ſ���

}

void ConnectCamera::closePc()
{
	viewer->removeAllPointClouds();
	viewer->removeAllShapes();
	viewer->removeAllCoordinateSystems();
	//ͬʱ���������
	cloud->clear();
	pc_num = 0;
	//viewer->updatePointCloud("cloud");

	//���ǻᱨ����֪��ɶԭ����ʱ��������������ˢ����������
	//ui.qvtkWidget->close();
	//viewer->~PCLVisualizer();
	ui.pushButton_showImg->setEnabled(true);
	ui.pushButton_closeImg->setEnabled(false);
}

void ConnectCamera::savePcd()
{
	char filename[256] = { 0 };
	CTime currTime;                                     // ��ȡϵͳʱ����Ϊ����ͼƬ�ļ���
	currTime = CTime::GetCurrentTime();
	sprintf(filename, ("%.4d%.2d%.2d%.2d%.2d%.2d.pcd"), currTime.GetYear(), currTime.GetMonth(),
		currTime.GetDay(), currTime.GetHour(), currTime.GetMinute(), currTime.GetSecond());
	pcl::PCDWriter w;
	if (ui.checkBox_isBinary->isChecked())
	{
		if (w.write(filename, *cloud, true) < 0)
		{
			QMessageBox::about(this, "warning", QString::fromLocal8Bit("����ʧ��"));
		}
		QMessageBox::about(this, "information", QString::fromLocal8Bit("����ɹ�"));
		

	}
	if (w.write(filename, *cloud, false) < 0)
	{
		QMessageBox::about(this, "warning", QString::fromLocal8Bit("����ʧ��"));
	}
	QMessageBox::about(this, "information", QString::fromLocal8Bit("����ɹ�"));


}
//ִ��һ��
void ConnectCamera::doOnce()
{
	
	//����ģʽ��ִ��һ��
	int nRet = MV_STA_SetCommandValue(m_handle, "TriggerSoftware");
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Execute Once failed! err code:" + QString::number(nRet));
		
	}
	//�ɼ�һ��֮����Ҫ������ʾ�ĵ���
	showPc();

}

void ConnectCamera::autoDo()
{
#if 0
	int nRet;
	if (ui.checkBox_autoDo->isChecked())
	{
		ui.pushButton_doOnce->setEnabled(false);
		//��ʱ�Ҳ��������Զ����Զ�ִ�е����ֻ���Լ�д��ѭ������ִ��
		//��������Ҫ����������һ���̣߳���Ȼ�ٴε����ѡ���û��Ӧ��
		//2022.1.8,������ʾ������֮����Ȼȷʵ�����Զ�ִ�У���ȴ�����������̣߳���Ҫ��һ���߳�
		//2022706,ʹ��count��������count����ָ������֮�󣬾�����ѭ����Ȼ����ִ��һ����ʾ���ƣ������Ͳ��Ῠ����
		//�����ַ�ʽ�޷�ʵ��Ӧ�á��������������ʵ�ֹ����ǣ����û�����Զ�����֮������ͻᰴ��ָ����֡��һֱ�ɼ����ݣ���
		//�ɼ���ָ��������ʱ���ͽ�������Ⱦ����������������У����Ʋ��Ƕ�̬���ӵġ�
		//������Ҫʵ�ֵķ����ǣ����û�����Զ�����֮���������ָ��֡�ʲɼ���ͬʱһ�߲ɼ������ڻ���һ�߶�̬��ʾ
		//��������õ����̱߳�̣����岽�裺�û�����Զ�����֮���½�һ���̣߳�����̻߳�һֱ��������Ͳɼ��ź�
		//�����ź�֮��ǰ��Ĳɼ��̻߳�ɼ����ݡ��������Ҫ��̬��ʾ���ƣ�����ʹ�����߳�����ʾ����Ҫ��̬��ʾ�Ļ�
		//�ͱ���һֱѭ�������������ǻ�ʹ�������濨������ô�죿����ʹ��һ����������������������ﵽָ������������
		//��ʾ�߳�����ѭ��
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
	//����ת����Ч
	/*typedef void  (*CallBack_Pointer) (void *);
	CallBack_Pointer call_pointer = (CallBack_Pointer) (&ConnectCamera::autoDo_CallBack);
	std::thread autoStart(call_pointer);*/
	//���������߼���֪���Բ���

	std::thread autoStart(&ConnectCamera::autoDo_CallBack, this);
	//����join�ķ�ʽ�������̣߳�����ζ���ڲɼ����ݵ�ʱ�����߳̽���ȴ���ֱ���û�ȡ���ɼ�����
	//�������ֵ�����˽����ˣ�ֱ�ӿ��������ǵ��÷����߳�
	//autoStart.join();
	//�������÷����̵߳ķ�ʽ�����ɿأ����׳�bug
	//�����߳�֮�󣬽���û�п��������Ǳ���˵�ؼ������ڲ�ͬ���߳�֮�乲������
	//�õ������ˣ�������û����qvtk�ؼ���ʵʱ��ʾ
	autoStart.detach();
	//QMessageBox::about(this, "warning", "clicked");

}
void ConnectCamera::autoDo_button()
{
	//������ť
	if (ui.checkBox_autoDo->isChecked())
	{
		//�����ظ�����Զ�ִ�а�ť����Ȼ��������̣߳����Ե��һ��֮��Ҫ������Ϊ����ѡ
		ui.pushButton_doOnce->setEnabled(false);
		ui.pushButton_autodo->setEnabled(false);
		autoDo();
	}
	else
	{
		QMessageBox::about(this, "warning", QString::fromLocal8Bit("�빴ѡ�Զ�ִ�и�ѡ��"));
	}
	
}
//��ѡ��״̬�ı亯��,����checkBoxState�������ֵ�븴ѡ��״̬ͬ��
//ʹ������м������������߳����޷������ؼ�������
void ConnectCamera::checkbox_autodo()
{
	if (ui.checkBox_autoDo->isChecked())
	{
		checkBoxState = 1;
	}
	else
	{
		checkBoxState = 0;
		//���߳�Ҫ�����ˣ���ʱ��Ӧ�ðѵ���ִ�к��Զ�ִ�а�ť����Ϊ��ѡ
		
		if (!ui.pushButton_autodo->isEnabled())
		{
			ui.pushButton_autodo->setEnabled(true);
		}
		if (!ui.pushButton_doOnce->isEnabled())
		{
			ui.pushButton_doOnce->setEnabled(true);
		}
		//���ݲɼ����ˣ��ÿ�ʼ��ʾ
		//��ʾ��ʱ��ֻ��ʾ��һ���ֵ��ƣ��ٵ��һ�ε���ִ�У��Ͱ�����ȫ����ʾ�ˣ���֪Ϊɶ
		//����һ�ᣬ�Ȳɼ����ݵ��̰߳����ݲ���,�������ǲ��У�ʹ���߳̽�����־����׼����
		//ֻ���߳̽���֮�󣬲���ʾ����
		//�߳�û�����ͻ�һֱ�������ѭ����
		//����һ�����⣬���ǵ��߳̽���֮�����ʾ���Ƶģ�Ϊʲô��������
		//�п����ǵ��ӵ��Ƶ��߳��ͺ��ڷ��Ͳɼ��źŵ��߳�
		while (autodo_thread_over)
		{

		}
		//���Ͳɼ��źŵ��߳̽���֮���ٵ�4�룬�ȵ��ӵ��Ƶ��̰߳����ݵ�����
		//������֮�����û�����ˣ�������һ��������
		//����ĵ�����ʾ��800�����ߣ�ʵ����ȷʵҲ����ô���У�����ʾ������ֻ��60���������ҵ����е�y���Ҳ��5900
		//���ƻ����ź��̺߳Ͳɼ��̵߳�֮��ͬ��������
		Sleep(4000);
		showPc();

	}
}
//���ڳ�Ա�����޷��� ���ص���������Ҫ���
//ʹ��thread�࣬�ڶ�������ֻ��Ҫ����Ķ�����У�����Ҳ����this
void ConnectCamera::autoDo_CallBack()
{
	//���߳��в�Ӧ�ò����ؼ�
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
	//����ģʽ�����������ô���Դ������Դ��������Ҳ��Ӳ������Ӳ������ʵ����ͨ�����ܱ������Ĳ���źţ��յ�һ���źŲɼ�һ��
	//ʵ��Ӧ���У��������Ȳ��ߣ�һ�㶼����Ӳ���������һ��ƽ��̨������ת̨��ͨ������ƽ��̨�еĵ���������ź����ɼ�ͼ��
	//������Ϊû����ӵ����������ʱʹ����������ʵ��
	int nRet = MV_STA_SetEnumValue(m_handle, "TriggerMode", MV_STA_TRIGGER_MODE_ON);
	if (MV_STA_OK != nRet)
	{
		QMessageBox::about(this, "warning!", "Set TriggerMode On failed! err code:" + QString::number(nRet));

	}
	//���ô���ԴΪ����
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
	//����ģʽ�أ�תΪ�ڴ���ģʽ
	//�ڴ���ģʽ��ʵ�������ͨ�������ڲ����źſ��Ʋɼ�ͼ��
	//�����ַ�ʽ��Ϊ�����������Ƶģ���粻�ܿ��ƣ���������ͻ�һֱ�ɼ���ʵ��Ӧ���л�������������ģʽ
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
