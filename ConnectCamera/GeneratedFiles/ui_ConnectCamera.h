/********************************************************************************
** Form generated from reading UI file 'ConnectCamera.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTCAMERA_H
#define UI_CONNECTCAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ConnectCameraClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit_CamInfo;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton_close;
    QPushButton *pushButton_findCam;
    QPushButton *pushButton_connect;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_start;
    QPushButton *pushButton_stop;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_savePly;
    QPushButton *pushButton_savePcd;
    QCheckBox *checkBox_isBinary;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_expo;
    QLabel *label_2;
    QLineEdit *lineEdit_gain;
    QLabel *label_3;
    QLineEdit *lineEdit_frame;
    QLabel *label_4;
    QLineEdit *lineEdit_autotriggertime;
    QLabel *label_5;
    QLineEdit *lineEdit_frame_pcNumber;
    QPushButton *pushButton_getPara;
    QPushButton *pushButton_setPara;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_switch;
    QPushButton *pushButton_switch_soft;
    QPushButton *pushButton_doOnce;
    QPushButton *pushButton_autodo;
    QCheckBox *checkBox_autoDo;
    QVTKWidget *qvtkWidget;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_showImg;
    QPushButton *pushButton_closeImg;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ConnectCameraClass)
    {
        if (ConnectCameraClass->objectName().isEmpty())
            ConnectCameraClass->setObjectName(QStringLiteral("ConnectCameraClass"));
        ConnectCameraClass->resize(979, 737);
        centralWidget = new QWidget(ConnectCameraClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit_CamInfo = new QLineEdit(centralWidget);
        lineEdit_CamInfo->setObjectName(QStringLiteral("lineEdit_CamInfo"));
        lineEdit_CamInfo->setGeometry(QRect(20, 40, 601, 31));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(640, 10, 217, 102));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_close = new QPushButton(groupBox);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        pushButton_close->setFont(font);

        gridLayout->addWidget(pushButton_close, 1, 1, 1, 1);

        pushButton_findCam = new QPushButton(groupBox);
        pushButton_findCam->setObjectName(QStringLiteral("pushButton_findCam"));
        pushButton_findCam->setFont(font);

        gridLayout->addWidget(pushButton_findCam, 0, 0, 1, 2);

        pushButton_connect = new QPushButton(groupBox);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setFont(font);

        gridLayout->addWidget(pushButton_connect, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(640, 130, 217, 67));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_start = new QPushButton(groupBox_2);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setFont(font);

        horizontalLayout->addWidget(pushButton_start);

        pushButton_stop = new QPushButton(groupBox_2);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        pushButton_stop->setFont(font);

        horizontalLayout->addWidget(pushButton_stop);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(640, 280, 326, 67));
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_savePly = new QPushButton(groupBox_3);
        pushButton_savePly->setObjectName(QStringLiteral("pushButton_savePly"));
        pushButton_savePly->setFont(font);

        horizontalLayout_2->addWidget(pushButton_savePly);

        pushButton_savePcd = new QPushButton(groupBox_3);
        pushButton_savePcd->setObjectName(QStringLiteral("pushButton_savePcd"));
        pushButton_savePcd->setFont(font);

        horizontalLayout_2->addWidget(pushButton_savePcd);

        checkBox_isBinary = new QCheckBox(groupBox_3);
        checkBox_isBinary->setObjectName(QStringLiteral("checkBox_isBinary"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(8);
        checkBox_isBinary->setFont(font1);

        horizontalLayout_2->addWidget(checkBox_isBinary);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(640, 350, 328, 207));
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit_expo = new QLineEdit(groupBox_4);
        lineEdit_expo->setObjectName(QStringLiteral("lineEdit_expo"));

        gridLayout_2->addWidget(lineEdit_expo, 0, 1, 1, 2);

        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_gain = new QLineEdit(groupBox_4);
        lineEdit_gain->setObjectName(QStringLiteral("lineEdit_gain"));

        gridLayout_2->addWidget(lineEdit_gain, 1, 1, 1, 2);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_frame = new QLineEdit(groupBox_4);
        lineEdit_frame->setObjectName(QStringLiteral("lineEdit_frame"));

        gridLayout_2->addWidget(lineEdit_frame, 2, 1, 1, 2);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        gridLayout_2->addWidget(label_4, 3, 0, 1, 2);

        lineEdit_autotriggertime = new QLineEdit(groupBox_4);
        lineEdit_autotriggertime->setObjectName(QStringLiteral("lineEdit_autotriggertime"));

        gridLayout_2->addWidget(lineEdit_autotriggertime, 3, 2, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        gridLayout_2->addWidget(label_5, 4, 0, 1, 2);

        lineEdit_frame_pcNumber = new QLineEdit(groupBox_4);
        lineEdit_frame_pcNumber->setObjectName(QStringLiteral("lineEdit_frame_pcNumber"));

        gridLayout_2->addWidget(lineEdit_frame_pcNumber, 4, 2, 1, 1);

        pushButton_getPara = new QPushButton(groupBox_4);
        pushButton_getPara->setObjectName(QStringLiteral("pushButton_getPara"));
        pushButton_getPara->setFont(font);

        gridLayout_2->addWidget(pushButton_getPara, 5, 0, 1, 2);

        pushButton_setPara = new QPushButton(groupBox_4);
        pushButton_setPara->setObjectName(QStringLiteral("pushButton_setPara"));
        pushButton_setPara->setFont(font);

        gridLayout_2->addWidget(pushButton_setPara, 5, 2, 1, 1);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(640, 570, 331, 102));
        gridLayout_3 = new QGridLayout(groupBox_5);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton_switch = new QPushButton(groupBox_5);
        pushButton_switch->setObjectName(QStringLiteral("pushButton_switch"));
        pushButton_switch->setFont(font);

        gridLayout_3->addWidget(pushButton_switch, 0, 0, 1, 1);

        pushButton_switch_soft = new QPushButton(groupBox_5);
        pushButton_switch_soft->setObjectName(QStringLiteral("pushButton_switch_soft"));
        pushButton_switch_soft->setFont(font);

        gridLayout_3->addWidget(pushButton_switch_soft, 0, 1, 1, 2);

        pushButton_doOnce = new QPushButton(groupBox_5);
        pushButton_doOnce->setObjectName(QStringLiteral("pushButton_doOnce"));
        pushButton_doOnce->setFont(font);

        gridLayout_3->addWidget(pushButton_doOnce, 1, 0, 1, 1);

        pushButton_autodo = new QPushButton(groupBox_5);
        pushButton_autodo->setObjectName(QStringLiteral("pushButton_autodo"));
        pushButton_autodo->setFont(font);

        gridLayout_3->addWidget(pushButton_autodo, 1, 1, 1, 1);

        checkBox_autoDo = new QCheckBox(groupBox_5);
        checkBox_autoDo->setObjectName(QStringLiteral("checkBox_autoDo"));
        checkBox_autoDo->setFont(font1);

        gridLayout_3->addWidget(checkBox_autoDo, 1, 2, 1, 1);

        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(20, 90, 601, 561));
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(640, 200, 217, 67));
        horizontalLayout_4 = new QHBoxLayout(groupBox_6);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_showImg = new QPushButton(groupBox_6);
        pushButton_showImg->setObjectName(QStringLiteral("pushButton_showImg"));
        pushButton_showImg->setFont(font);

        horizontalLayout_4->addWidget(pushButton_showImg);

        pushButton_closeImg = new QPushButton(groupBox_6);
        pushButton_closeImg->setObjectName(QStringLiteral("pushButton_closeImg"));
        pushButton_closeImg->setFont(font);

        horizontalLayout_4->addWidget(pushButton_closeImg);

        ConnectCameraClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ConnectCameraClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 979, 26));
        ConnectCameraClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ConnectCameraClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ConnectCameraClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ConnectCameraClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ConnectCameraClass->setStatusBar(statusBar);

        retranslateUi(ConnectCameraClass);

        QMetaObject::connectSlotsByName(ConnectCameraClass);
    } // setupUi

    void retranslateUi(QMainWindow *ConnectCameraClass)
    {
        ConnectCameraClass->setWindowTitle(QApplication::translate("ConnectCameraClass", "ConnectCamera", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ConnectCameraClass", "\347\233\270\346\234\272\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_close->setText(QApplication::translate("ConnectCameraClass", "\345\205\263\351\227\255\350\256\276\345\244\207", Q_NULLPTR));
        pushButton_findCam->setText(QApplication::translate("ConnectCameraClass", "\346\237\245\346\211\276\350\256\276\345\244\207", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("ConnectCameraClass", "\350\277\236\346\216\245\350\256\276\345\244\207", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("ConnectCameraClass", "\345\233\276\345\203\217\351\207\207\351\233\206", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("ConnectCameraClass", "\345\274\200\345\247\213\351\207\207\351\233\206", Q_NULLPTR));
        pushButton_stop->setText(QApplication::translate("ConnectCameraClass", "\345\201\234\346\255\242\351\207\207\351\233\206", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("ConnectCameraClass", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButton_savePly->setText(QApplication::translate("ConnectCameraClass", "\344\277\235\345\255\230ply", Q_NULLPTR));
        pushButton_savePcd->setText(QApplication::translate("ConnectCameraClass", "\344\277\235\345\255\230pcd", Q_NULLPTR));
        checkBox_isBinary->setText(QApplication::translate("ConnectCameraClass", "\344\272\214\350\277\233\345\210\266\345\275\242\345\274\217", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("ConnectCameraClass", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("ConnectCameraClass", "\346\233\235\345\205\211\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("ConnectCameraClass", "\345\242\236\347\233\212\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("ConnectCameraClass", "\345\270\247\347\216\207\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("ConnectCameraClass", "\350\207\252\345\212\250\350\247\246\345\217\221\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("ConnectCameraClass", "\347\202\271\344\272\221\350\275\256\345\273\223\346\225\260\351\207\217\357\274\232", Q_NULLPTR));
        pushButton_getPara->setText(QApplication::translate("ConnectCameraClass", "\345\217\202\346\225\260\350\216\267\345\217\226", Q_NULLPTR));
        pushButton_setPara->setText(QApplication::translate("ConnectCameraClass", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("ConnectCameraClass", "\350\247\246\345\217\221\346\250\241\345\274\217", Q_NULLPTR));
        pushButton_switch->setText(QApplication::translate("ConnectCameraClass", "\345\210\207\346\215\242\344\270\272\345\206\205\350\247\246\345\217\221", Q_NULLPTR));
        pushButton_switch_soft->setText(QApplication::translate("ConnectCameraClass", "\345\210\207\346\215\242\344\270\272\350\275\257\350\247\246\345\217\221", Q_NULLPTR));
        pushButton_doOnce->setText(QApplication::translate("ConnectCameraClass", "\345\215\225\346\254\241\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_autodo->setText(QApplication::translate("ConnectCameraClass", "\350\207\252\345\212\250\346\211\247\350\241\214", Q_NULLPTR));
        checkBox_autoDo->setText(QApplication::translate("ConnectCameraClass", "\350\207\252\345\212\250\346\211\247\350\241\214", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("ConnectCameraClass", "\345\233\276\345\203\217\346\230\276\347\244\272", Q_NULLPTR));
        pushButton_showImg->setText(QApplication::translate("ConnectCameraClass", "\346\230\276\347\244\272\345\233\276\345\203\217", Q_NULLPTR));
        pushButton_closeImg->setText(QApplication::translate("ConnectCameraClass", "\345\205\263\351\227\255\345\233\276\345\203\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConnectCameraClass: public Ui_ConnectCameraClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTCAMERA_H
