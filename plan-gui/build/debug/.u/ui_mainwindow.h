/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *config;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *comStatusTxt;
    QPushButton *openComButton;
    QPushButton *streamOFF_master_button;
    QLabel *stdelaytxt;
    QLabel *label_18;
    QPushButton *closeComButton;
    QComboBox *StreamSelectComboBox;
    QComboBox *SlaveSelectComboBox;
    QPushButton *updateRefreshButton;
    QLabel *stdelaytxt_2;
    QLineEdit *comPortTxt;
    QLabel *comport_2;
    QLabel *comport_3;
    QPushButton *logOFF_master_button;
    QLabel *label_3;
    QLineEdit *logRefreshTxt;
    QLabel *streamRefreshStatusTxt;
    QLabel *comport;
    QPushButton *logON_master_button;
    QLineEdit *logFileTxt;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *streamON_master_button;
    QLabel *label_20;
    QLineEdit *streamRefreshTxt;
    QLabel *logRefreshStatusTxt;
    QLabel *label_stream_status;
    QWidget *stream_ex;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_21;
    QLabel *label_imu_g_x;
    QLabel *label_imu_a_y;
    QLabel *label_39;
    QLabel *label_38;
    QLabel *label_40;
    QLabel *label_44;
    QLabel *disp_gyroy_d;
    QLabel *label_strain;
    QLabel *disp_temp_d;
    QLabel *disp_vg;
    QLabel *label_imu_a_z;
    QLabel *label_imu_g_y;
    QLabel *label_16;
    QLabel *label_37;
    QLabel *label_imu_g_z;
    QLabel *disp_stat1;
    QLabel *disp_accy_d;
    QLabel *label_29;
    QLabel *label_28;
    QLabel *label_30;
    QLabel *disp_strain_d;
    QLabel *label_43;
    QLabel *disp_gyroz_d;
    QLabel *disp_gyrox_d;
    QLabel *disp_vb;
    QLabel *disp_vb_d;
    QLabel *disp_vg_d;
    QLabel *label_41;
    QLabel *label_8;
    QLabel *disp_accx_d;
    QLabel *disp_accz_d;
    QLabel *disp_temp;
    QSlider *horizontalSlider_current_zero;
    QLabel *label_17;
    QLabel *label;
    QLabel *disp_accx;
    QLabel *label_14;
    QLabel *disp_accy;
    QLabel *disp_current;
    QLabel *disp_strain;
    QLabel *disp_ana;
    QLabel *disp_stat2;
    QLabel *label_6;
    QLabel *disp_enc;
    QLabel *label_4;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *disp_current_d;
    QLabel *disp_ana_d;
    QLabel *disp_accz;
    QLabel *label_15;
    QLabel *disp_gyrox;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_42;
    QLabel *label_imu_a_x;
    QLabel *label_2;
    QLabel *disp_gyroy;
    QLabel *label_10;
    QLabel *disp_gyroz;
    QLabel *label_107;
    QLabel *label_12;
    QLabel *disp_ana1;
    QLabel *disp_ana1_d;
    QLabel *label_108;
    QLabel *label_status1;
    QLabel *label_status2;
    QWidget *stream_manage;
    QWidget *stream_strain;
    QWidget *gridLayoutWidget_9;
    QGridLayout *gridLayout_10;
    QLineEdit *strain_offs_ch6;
    QLineEdit *strain_offs_ch5;
    QLabel *label_67;
    QLabel *label_32;
    QLabel *disp_strain_ch6;
    QLabel *disp_strain_ch1;
    QLabel *disp_strain_ch5_d;
    QLabel *disp_strain_ch6_d;
    QLabel *label_33;
    QLabel *disp_strain_ch1_d;
    QLabel *label_35;
    QLabel *label_68;
    QLabel *label_70;
    QLabel *disp_strain_ch5;
    QLabel *label_36;
    QLabel *label_69;
    QLabel *label_31;
    QLabel *label_34;
    QLabel *disp_strain_ch2;
    QLabel *disp_strain_ch3;
    QLabel *disp_strain_ch3_d;
    QLabel *disp_strain_ch2_d;
    QLabel *disp_strain_ch4_d;
    QLabel *disp_strain_ch4;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *stream_SA_RefreshOffset;
    QLineEdit *strain_offs_ch3;
    QLineEdit *strain_offs_ch1;
    QLineEdit *strain_offs_ch2;
    QLineEdit *strain_offs_ch4;
    QWidget *stream_ricnu;
    QWidget *gridLayoutWidget_10;
    QGridLayout *gridLayout_11;
    QLabel *label_84;
    QLabel *label_imu_a_y_2;
    QLabel *label_93;
    QLabel *label_imu_a_x_2;
    QLabel *label_74;
    QLabel *ricnu_current_d;
    QLabel *label_76;
    QLabel *label_imu_g_y_2;
    QLabel *label_81;
    QLabel *label_80;
    QLabel *label_82;
    QLabel *label_83;
    QLabel *label_85;
    QLabel *label_87;
    QLabel *label_89;
    QLabel *label_88;
    QLabel *ricnu_enc_mot;
    QLabel *ricnu_accx;
    QLabel *ricnu_accy;
    QLabel *ricnu_accz;
    QLabel *ricnu_enc_joint;
    QLabel *ricnu_gyrox;
    QLabel *ricnu_gyroy;
    QLabel *ricnu_current;
    QLabel *ricnu_gyroz;
    QLabel *ricnu_gyroz_d;
    QLabel *ricnu_accy_d;
    QLabel *label_91;
    QLabel *ricnu_accx_d;
    QLabel *ricnu_gyrox_d;
    QLabel *label_imu_g_x_2;
    QLabel *label_imu_g_z_2;
    QLabel *ricnu_accz_d;
    QLabel *ricnu_gyroy_d;
    QLabel *label_92;
    QLabel *label_imu_a_z_2;
    QLabel *label_94;
    QLabel *ricnu_vb;
    QLabel *ricnu_vb_d;
    QSlider *horizontalSlider_current_zero_2;
    QLabel *label_99;
    QLabel *label_100;
    QLabel *label_95;
    QLabel *label_96;
    QLabel *label_78;
    QLabel *label_77;
    QLabel *label_75;
    QLabel *label_86;
    QLabel *label_79;
    QLabel *label_73;
    QLabel *ricnu_strain_ch1;
    QLabel *label_97;
    QLabel *ricnu_strain_ch1_d;
    QLabel *ricnu_strain_ch2;
    QLabel *ricnu_strain_ch2_d;
    QLabel *ricnu_strain_ch3;
    QLabel *ricnu_strain_ch4;
    QLabel *ricnu_strain_ch3_d;
    QLabel *ricnu_strain_ch4_d;
    QLabel *ricnu_strain_ch5;
    QLabel *ricnu_strain_ch6_d;
    QLabel *ricnu_strain_ch5_d;
    QLabel *label_90;
    QLabel *ricnu_strain_ch6;
    QLabel *label_98;
    QLabel *label_101;
    QLabel *label_102;
    QLabel *label_103;
    QLabel *label_104;
    QWidget *plot;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QCustomPlot *customPlot;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxXaxisLim;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_4;
    QLineEdit *plot_xmin_lineEdit;
    QRadioButton *radioButtonXManual;
    QLabel *label_22;
    QLineEdit *plot_xmax_lineEdit;
    QRadioButton *radioButtonXAuto;
    QLabel *label_23;
    QPushButton *UpdatePlotpushButton;
    QGroupBox *groupBoxYaxisLim;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_5;
    QRadioButton *radioButtonYManual;
    QLineEdit *plot_ymax_lineEdit;
    QRadioButton *radioButtonYAuto;
    QLineEdit *plot_ymin_lineEdit;
    QLabel *label_24;
    QLabel *label_25;
    QGridLayout *gridLayout_7;
    QLabel *label_t1;
    QComboBox *cBoxvar1;
    QComboBox *cBoxvar4;
    QComboBox *cBoxvar6;
    QComboBox *cBoxvar5;
    QComboBox *cBoxvar2;
    QComboBox *cBoxvar3;
    QLabel *label_t2;
    QLabel *label_t3;
    QLabel *label_t4;
    QLabel *label_t5;
    QLabel *label_t6;
    QWidget *exp;
    QWidget *control;
    QWidget *gridLayoutWidget_7;
    QGridLayout *gridLayout_8;
    QLabel *label_66;
    QLineEdit *control_trapeze_spd;
    QLabel *label_65;
    QLabel *label_59;
    QLabel *textLabel_Gains_2;
    QLabel *label_62;
    QLineEdit *control_toggle_delayB;
    QLineEdit *control_g3;
    QLineEdit *control_slider_max;
    QLineEdit *control_setp_b;
    QPushButton *pushButton_SetGains;
    QLabel *label_60;
    QSlider *hSlider_Ctrl;
    QLineEdit *control_g2;
    QLineEdit *control_g5;
    QPushButton *pushButton_CtrlMinMax;
    QLabel *disp_active_controller;
    QLabel *label_51;
    QLabel *label_47;
    QLabel *label_56;
    QLabel *label_53;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_48;
    QLabel *label_58;
    QLabel *label_49;
    QLineEdit *control_g4;
    QLabel *label_52;
    QLabel *label_46;
    QLineEdit *control_setp_a;
    QComboBox *comboBox_ctrl_list;
    QLabel *label_54;
    QLineEdit *control_g1;
    QLabel *disp_slider;
    QPushButton *pushButton_setp_a_go;
    QLabel *label_50;
    QLabel *label_55;
    QLabel *label_45;
    QPushButton *pushButton_setp_b_go;
    QLineEdit *control_g0;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_SetController;
    QLineEdit *control_slider_min;
    QLabel *label_61;
    QPushButton *pushButton_toggle;
    QLineEdit *control_toggle_delayA;
    QLabel *label_57;
    QLabel *disp_meas_val;
    QLineEdit *control_trapeze_acc;
    QLabel *textLabel_Gains_i;
    QLabel *textLabel_Gains_p;
    QLabel *textLabel_Gains_z;
    QWidget *in_control;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_6;
    QLabel *label_109;
    QLabel *disp_inctrl_current_d;
    QLabel *label_26;
    QLabel *disp_inctrl_current;
    QLabel *label_117;
    QLabel *label_113;
    QLabel *label_19;
    QLabel *label_27;
    QLabel *label_111;
    QLabel *label_115;
    QLabel *label_114;
    QLabel *label_112;
    QLabel *label_110;
    QLabel *label_116;
    QLabel *label_118;
    QLabel *disp_inctrl_active_controller;
    QLabel *disp_inctrl_setp;
    QLabel *disp_inctrl_actual_val;
    QLabel *disp_inctrl_error;
    QLabel *disp_inctrl_output;
    QLabel *disp_inctrl_dir;
    QLabel *disp_inctrl_1;
    QLabel *disp_inctrl_pwm;
    QLabel *disp_inctrl_0;
    QLabel *label_124;
    QLabel *label_123;
    QLabel *label_122;
    QLabel *label_125;
    QLineEdit *inctrl_w0;
    QLineEdit *inctrl_w1;
    QLineEdit *inctrl_w2;
    QLineEdit *inctrl_w3;
    QPushButton *pushButton_inctrl_w0;
    QPushButton *pushButton_inctrl_w1;
    QPushButton *pushButton_inctrl_w2;
    QPushButton *pushButton_inctrl_w3;
    QWidget *external;
    QWidget *gridLayoutWidget_8;
    QGridLayout *gridLayout_9;
    QLineEdit *ext_pwro_pwm;
    QLabel *label_63;
    QLabel *label_64;
    QPushButton *pushButton_ext_pwro;
    QLabel *label_71;
    QLabel *label_105;
    QLabel *label_72;
    QComboBox *comboBox_minm_rgb;
    QPushButton *quadrature_write;
    QLineEdit *quad_write_val;
    QLabel *label_106;
    QWidget *about;
    QTextBrowser *textBrowser;
    QLabel *text_last_build;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1024, 768));
        MainWindow->setMaximumSize(QSize(1024, 768));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 10, 1031, 731));
        config = new QWidget();
        config->setObjectName(QStringLiteral("config"));
        gridLayoutWidget = new QWidget(config);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 1001, 368));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        comStatusTxt = new QLabel(gridLayoutWidget);
        comStatusTxt->setObjectName(QStringLiteral("comStatusTxt"));
        comStatusTxt->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(comStatusTxt, 3, 0, 1, 4);

        openComButton = new QPushButton(gridLayoutWidget);
        openComButton->setObjectName(QStringLiteral("openComButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openComButton->sizePolicy().hasHeightForWidth());
        openComButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(openComButton, 2, 2, 1, 1);

        streamOFF_master_button = new QPushButton(gridLayoutWidget);
        streamOFF_master_button->setObjectName(QStringLiteral("streamOFF_master_button"));

        gridLayout->addWidget(streamOFF_master_button, 4, 3, 1, 1);

        stdelaytxt = new QLabel(gridLayoutWidget);
        stdelaytxt->setObjectName(QStringLiteral("stdelaytxt"));

        gridLayout->addWidget(stdelaytxt, 11, 0, 1, 1);

        label_18 = new QLabel(gridLayoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy2);
        label_18->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(label_18, 0, 0, 1, 2);

        closeComButton = new QPushButton(gridLayoutWidget);
        closeComButton->setObjectName(QStringLiteral("closeComButton"));
        sizePolicy1.setHeightForWidth(closeComButton->sizePolicy().hasHeightForWidth());
        closeComButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(closeComButton, 2, 3, 1, 1);

        StreamSelectComboBox = new QComboBox(gridLayoutWidget);
        StreamSelectComboBox->setObjectName(QStringLiteral("StreamSelectComboBox"));

        gridLayout->addWidget(StreamSelectComboBox, 4, 1, 1, 1);

        SlaveSelectComboBox = new QComboBox(gridLayoutWidget);
        SlaveSelectComboBox->setObjectName(QStringLiteral("SlaveSelectComboBox"));

        gridLayout->addWidget(SlaveSelectComboBox, 1, 1, 1, 1);

        updateRefreshButton = new QPushButton(gridLayoutWidget);
        updateRefreshButton->setObjectName(QStringLiteral("updateRefreshButton"));

        gridLayout->addWidget(updateRefreshButton, 15, 0, 1, 1);

        stdelaytxt_2 = new QLabel(gridLayoutWidget);
        stdelaytxt_2->setObjectName(QStringLiteral("stdelaytxt_2"));

        gridLayout->addWidget(stdelaytxt_2, 13, 0, 1, 1);

        comPortTxt = new QLineEdit(gridLayoutWidget);
        comPortTxt->setObjectName(QStringLiteral("comPortTxt"));
        sizePolicy.setHeightForWidth(comPortTxt->sizePolicy().hasHeightForWidth());
        comPortTxt->setSizePolicy(sizePolicy);
        comPortTxt->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(comPortTxt, 2, 1, 1, 1);

        comport_2 = new QLabel(gridLayoutWidget);
        comport_2->setObjectName(QStringLiteral("comport_2"));

        gridLayout->addWidget(comport_2, 1, 0, 1, 1);

        comport_3 = new QLabel(gridLayoutWidget);
        comport_3->setObjectName(QStringLiteral("comport_3"));

        gridLayout->addWidget(comport_3, 4, 0, 1, 1);

        logOFF_master_button = new QPushButton(gridLayoutWidget);
        logOFF_master_button->setObjectName(QStringLiteral("logOFF_master_button"));

        gridLayout->addWidget(logOFF_master_button, 6, 3, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 6, 0, 1, 1);

        logRefreshTxt = new QLineEdit(gridLayoutWidget);
        logRefreshTxt->setObjectName(QStringLiteral("logRefreshTxt"));
        sizePolicy.setHeightForWidth(logRefreshTxt->sizePolicy().hasHeightForWidth());
        logRefreshTxt->setSizePolicy(sizePolicy);
        logRefreshTxt->setMinimumSize(QSize(100, 0));
        logRefreshTxt->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(logRefreshTxt, 13, 1, 1, 1);

        streamRefreshStatusTxt = new QLabel(gridLayoutWidget);
        streamRefreshStatusTxt->setObjectName(QStringLiteral("streamRefreshStatusTxt"));
        streamRefreshStatusTxt->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(streamRefreshStatusTxt, 12, 0, 1, 3);

        comport = new QLabel(gridLayoutWidget);
        comport->setObjectName(QStringLiteral("comport"));

        gridLayout->addWidget(comport, 2, 0, 1, 1);

        logON_master_button = new QPushButton(gridLayoutWidget);
        logON_master_button->setObjectName(QStringLiteral("logON_master_button"));

        gridLayout->addWidget(logON_master_button, 6, 2, 1, 1);

        logFileTxt = new QLineEdit(gridLayoutWidget);
        logFileTxt->setObjectName(QStringLiteral("logFileTxt"));
        sizePolicy.setHeightForWidth(logFileTxt->sizePolicy().hasHeightForWidth());
        logFileTxt->setSizePolicy(sizePolicy);
        logFileTxt->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(logFileTxt, 6, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(275, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 15, 4, 1, 1);

        streamON_master_button = new QPushButton(gridLayoutWidget);
        streamON_master_button->setObjectName(QStringLiteral("streamON_master_button"));

        gridLayout->addWidget(streamON_master_button, 4, 2, 1, 1);

        label_20 = new QLabel(gridLayoutWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        sizePolicy2.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy2);
        label_20->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(label_20, 9, 0, 1, 2);

        streamRefreshTxt = new QLineEdit(gridLayoutWidget);
        streamRefreshTxt->setObjectName(QStringLiteral("streamRefreshTxt"));
        sizePolicy.setHeightForWidth(streamRefreshTxt->sizePolicy().hasHeightForWidth());
        streamRefreshTxt->setSizePolicy(sizePolicy);
        streamRefreshTxt->setMinimumSize(QSize(100, 0));
        streamRefreshTxt->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(streamRefreshTxt, 11, 1, 1, 1);

        logRefreshStatusTxt = new QLabel(gridLayoutWidget);
        logRefreshStatusTxt->setObjectName(QStringLiteral("logRefreshStatusTxt"));
        logRefreshStatusTxt->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(logRefreshStatusTxt, 14, 0, 1, 3);

        label_stream_status = new QLabel(gridLayoutWidget);
        label_stream_status->setObjectName(QStringLiteral("label_stream_status"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_stream_status->sizePolicy().hasHeightForWidth());
        label_stream_status->setSizePolicy(sizePolicy3);
        label_stream_status->setMinimumSize(QSize(20, 0));
        label_stream_status->setBaseSize(QSize(30, 0));
        label_stream_status->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_stream_status, 4, 4, 1, 1);

        tabWidget->addTab(config, QString());
        stream_ex = new QWidget();
        stream_ex->setObjectName(QStringLiteral("stream_ex"));
        gridLayoutWidget_2 = new QWidget(stream_ex);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 10, 721, 621));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(gridLayoutWidget_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_21, 0, 2, 1, 1);

        label_imu_g_x = new QLabel(gridLayoutWidget_2);
        label_imu_g_x->setObjectName(QStringLiteral("label_imu_g_x"));

        gridLayout_2->addWidget(label_imu_g_x, 4, 4, 1, 1);

        label_imu_a_y = new QLabel(gridLayoutWidget_2);
        label_imu_a_y->setObjectName(QStringLiteral("label_imu_a_y"));

        gridLayout_2->addWidget(label_imu_a_y, 2, 4, 1, 1);

        label_39 = new QLabel(gridLayoutWidget_2);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setLayoutDirection(Qt::LeftToRight);
        label_39->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_39, 12, 1, 1, 1);

        label_38 = new QLabel(gridLayoutWidget_2);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setLayoutDirection(Qt::LeftToRight);
        label_38->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_38, 12, 0, 2, 1);

        label_40 = new QLabel(gridLayoutWidget_2);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setLayoutDirection(Qt::LeftToRight);
        label_40->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_40, 13, 1, 1, 1);

        label_44 = new QLabel(gridLayoutWidget_2);
        label_44->setObjectName(QStringLiteral("label_44"));

        gridLayout_2->addWidget(label_44, 14, 4, 1, 1);

        disp_gyroy_d = new QLabel(gridLayoutWidget_2);
        disp_gyroy_d->setObjectName(QStringLiteral("disp_gyroy_d"));
        disp_gyroy_d->setAutoFillBackground(false);
        disp_gyroy_d->setFrameShape(QFrame::Box);
        disp_gyroy_d->setFrameShadow(QFrame::Raised);
        disp_gyroy_d->setLineWidth(1);
        disp_gyroy_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_gyroy_d, 5, 3, 1, 1);

        label_strain = new QLabel(gridLayoutWidget_2);
        label_strain->setObjectName(QStringLiteral("label_strain"));

        gridLayout_2->addWidget(label_strain, 7, 4, 1, 1);

        disp_temp_d = new QLabel(gridLayoutWidget_2);
        disp_temp_d->setObjectName(QStringLiteral("disp_temp_d"));
        disp_temp_d->setAutoFillBackground(false);
        disp_temp_d->setFrameShape(QFrame::Box);
        disp_temp_d->setFrameShadow(QFrame::Raised);
        disp_temp_d->setLineWidth(1);
        disp_temp_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_temp_d, 14, 3, 1, 1);

        disp_vg = new QLabel(gridLayoutWidget_2);
        disp_vg->setObjectName(QStringLiteral("disp_vg"));
        disp_vg->setAutoFillBackground(false);
        disp_vg->setFrameShape(QFrame::Box);
        disp_vg->setFrameShadow(QFrame::Raised);
        disp_vg->setLineWidth(1);
        disp_vg->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_vg, 13, 2, 1, 1);

        label_imu_a_z = new QLabel(gridLayoutWidget_2);
        label_imu_a_z->setObjectName(QStringLiteral("label_imu_a_z"));

        gridLayout_2->addWidget(label_imu_a_z, 3, 4, 1, 1);

        label_imu_g_y = new QLabel(gridLayoutWidget_2);
        label_imu_g_y->setObjectName(QStringLiteral("label_imu_g_y"));

        gridLayout_2->addWidget(label_imu_g_y, 5, 4, 1, 1);

        label_16 = new QLabel(gridLayoutWidget_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_16, 15, 1, 1, 1);

        label_37 = new QLabel(gridLayoutWidget_2);
        label_37->setObjectName(QStringLiteral("label_37"));

        gridLayout_2->addWidget(label_37, 8, 4, 1, 1);

        label_imu_g_z = new QLabel(gridLayoutWidget_2);
        label_imu_g_z->setObjectName(QStringLiteral("label_imu_g_z"));

        gridLayout_2->addWidget(label_imu_g_z, 6, 4, 1, 1);

        disp_stat1 = new QLabel(gridLayoutWidget_2);
        disp_stat1->setObjectName(QStringLiteral("disp_stat1"));
        disp_stat1->setAutoFillBackground(false);
        disp_stat1->setFrameShape(QFrame::Box);
        disp_stat1->setFrameShadow(QFrame::Raised);
        disp_stat1->setLineWidth(1);
        disp_stat1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_stat1, 15, 2, 1, 1);

        disp_accy_d = new QLabel(gridLayoutWidget_2);
        disp_accy_d->setObjectName(QStringLiteral("disp_accy_d"));
        disp_accy_d->setAutoFillBackground(false);
        disp_accy_d->setFrameShape(QFrame::Box);
        disp_accy_d->setFrameShadow(QFrame::Raised);
        disp_accy_d->setLineWidth(1);
        disp_accy_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_accy_d, 2, 3, 1, 1);

        label_29 = new QLabel(gridLayoutWidget_2);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setLayoutDirection(Qt::LeftToRight);
        label_29->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_29, 8, 1, 1, 1);

        label_28 = new QLabel(gridLayoutWidget_2);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_28, 0, 3, 1, 1);

        label_30 = new QLabel(gridLayoutWidget_2);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_30, 0, 5, 1, 1);

        disp_strain_d = new QLabel(gridLayoutWidget_2);
        disp_strain_d->setObjectName(QStringLiteral("disp_strain_d"));
        disp_strain_d->setAutoFillBackground(false);
        disp_strain_d->setFrameShape(QFrame::Box);
        disp_strain_d->setFrameShadow(QFrame::Raised);
        disp_strain_d->setLineWidth(1);
        disp_strain_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_strain_d, 7, 3, 1, 1);

        label_43 = new QLabel(gridLayoutWidget_2);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setLayoutDirection(Qt::LeftToRight);
        label_43->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_43, 14, 0, 1, 1);

        disp_gyroz_d = new QLabel(gridLayoutWidget_2);
        disp_gyroz_d->setObjectName(QStringLiteral("disp_gyroz_d"));
        disp_gyroz_d->setAutoFillBackground(false);
        disp_gyroz_d->setFrameShape(QFrame::Box);
        disp_gyroz_d->setFrameShadow(QFrame::Raised);
        disp_gyroz_d->setLineWidth(1);
        disp_gyroz_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_gyroz_d, 6, 3, 1, 1);

        disp_gyrox_d = new QLabel(gridLayoutWidget_2);
        disp_gyrox_d->setObjectName(QStringLiteral("disp_gyrox_d"));
        disp_gyrox_d->setAutoFillBackground(false);
        disp_gyrox_d->setFrameShape(QFrame::Box);
        disp_gyrox_d->setFrameShadow(QFrame::Raised);
        disp_gyrox_d->setLineWidth(1);
        disp_gyrox_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_gyrox_d, 4, 3, 1, 1);

        disp_vb = new QLabel(gridLayoutWidget_2);
        disp_vb->setObjectName(QStringLiteral("disp_vb"));
        disp_vb->setAutoFillBackground(false);
        disp_vb->setFrameShape(QFrame::Box);
        disp_vb->setFrameShadow(QFrame::Raised);
        disp_vb->setLineWidth(1);
        disp_vb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_vb, 12, 2, 1, 1);

        disp_vb_d = new QLabel(gridLayoutWidget_2);
        disp_vb_d->setObjectName(QStringLiteral("disp_vb_d"));
        disp_vb_d->setAutoFillBackground(false);
        disp_vb_d->setFrameShape(QFrame::Box);
        disp_vb_d->setFrameShadow(QFrame::Raised);
        disp_vb_d->setLineWidth(1);
        disp_vb_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_vb_d, 12, 3, 1, 1);

        disp_vg_d = new QLabel(gridLayoutWidget_2);
        disp_vg_d->setObjectName(QStringLiteral("disp_vg_d"));
        disp_vg_d->setAutoFillBackground(false);
        disp_vg_d->setFrameShape(QFrame::Box);
        disp_vg_d->setFrameShadow(QFrame::Raised);
        disp_vg_d->setLineWidth(1);
        disp_vg_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_vg_d, 13, 3, 1, 1);

        label_41 = new QLabel(gridLayoutWidget_2);
        label_41->setObjectName(QStringLiteral("label_41"));

        gridLayout_2->addWidget(label_41, 12, 4, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_8, 4, 1, 1, 1);

        disp_accx_d = new QLabel(gridLayoutWidget_2);
        disp_accx_d->setObjectName(QStringLiteral("disp_accx_d"));
        disp_accx_d->setAutoFillBackground(false);
        disp_accx_d->setFrameShape(QFrame::Box);
        disp_accx_d->setFrameShadow(QFrame::Raised);
        disp_accx_d->setLineWidth(1);
        disp_accx_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_accx_d, 1, 3, 1, 1);

        disp_accz_d = new QLabel(gridLayoutWidget_2);
        disp_accz_d->setObjectName(QStringLiteral("disp_accz_d"));
        disp_accz_d->setAutoFillBackground(false);
        disp_accz_d->setFrameShape(QFrame::Box);
        disp_accz_d->setFrameShadow(QFrame::Raised);
        disp_accz_d->setLineWidth(1);
        disp_accz_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_accz_d, 3, 3, 1, 1);

        disp_temp = new QLabel(gridLayoutWidget_2);
        disp_temp->setObjectName(QStringLiteral("disp_temp"));
        disp_temp->setAutoFillBackground(false);
        disp_temp->setFrameShape(QFrame::Box);
        disp_temp->setFrameShadow(QFrame::Raised);
        disp_temp->setLineWidth(1);
        disp_temp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_temp, 14, 2, 1, 1);

        horizontalSlider_current_zero = new QSlider(gridLayoutWidget_2);
        horizontalSlider_current_zero->setObjectName(QStringLiteral("horizontalSlider_current_zero"));
        sizePolicy.setHeightForWidth(horizontalSlider_current_zero->sizePolicy().hasHeightForWidth());
        horizontalSlider_current_zero->setSizePolicy(sizePolicy);
        horizontalSlider_current_zero->setMinimumSize(QSize(150, 0));
        horizontalSlider_current_zero->setMinimum(-125);
        horizontalSlider_current_zero->setMaximum(125);
        horizontalSlider_current_zero->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider_current_zero, 10, 5, 1, 1);

        label_17 = new QLabel(gridLayoutWidget_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_17, 16, 1, 1, 1);

        label = new QLabel(gridLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 1, 0, 3, 1);

        disp_accx = new QLabel(gridLayoutWidget_2);
        disp_accx->setObjectName(QStringLiteral("disp_accx"));
        disp_accx->setAutoFillBackground(false);
        disp_accx->setFrameShape(QFrame::Box);
        disp_accx->setFrameShadow(QFrame::Raised);
        disp_accx->setLineWidth(1);
        disp_accx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_accx, 1, 2, 1, 1);

        label_14 = new QLabel(gridLayoutWidget_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setLayoutDirection(Qt::LeftToRight);
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_14, 11, 0, 1, 1);

        disp_accy = new QLabel(gridLayoutWidget_2);
        disp_accy->setObjectName(QStringLiteral("disp_accy"));
        disp_accy->setAutoFillBackground(false);
        disp_accy->setFrameShape(QFrame::Box);
        disp_accy->setFrameShadow(QFrame::Raised);
        disp_accy->setLineWidth(1);
        disp_accy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_accy, 2, 2, 1, 1);

        disp_current = new QLabel(gridLayoutWidget_2);
        disp_current->setObjectName(QStringLiteral("disp_current"));
        disp_current->setAutoFillBackground(false);
        disp_current->setFrameShape(QFrame::Box);
        disp_current->setFrameShadow(QFrame::Raised);
        disp_current->setLineWidth(1);
        disp_current->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_current, 10, 2, 1, 1);

        disp_strain = new QLabel(gridLayoutWidget_2);
        disp_strain->setObjectName(QStringLiteral("disp_strain"));
        disp_strain->setAutoFillBackground(false);
        disp_strain->setFrameShape(QFrame::Box);
        disp_strain->setFrameShadow(QFrame::Raised);
        disp_strain->setLineWidth(1);
        disp_strain->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_strain, 7, 2, 1, 1);

        disp_ana = new QLabel(gridLayoutWidget_2);
        disp_ana->setObjectName(QStringLiteral("disp_ana"));
        disp_ana->setAutoFillBackground(false);
        disp_ana->setFrameShape(QFrame::Box);
        disp_ana->setFrameShadow(QFrame::Raised);
        disp_ana->setLineWidth(1);
        disp_ana->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_ana, 8, 2, 1, 1);

        disp_stat2 = new QLabel(gridLayoutWidget_2);
        disp_stat2->setObjectName(QStringLiteral("disp_stat2"));
        disp_stat2->setAutoFillBackground(false);
        disp_stat2->setFrameShape(QFrame::Box);
        disp_stat2->setFrameShadow(QFrame::Raised);
        disp_stat2->setLineWidth(1);
        disp_stat2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_stat2, 16, 2, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 3, 1, 1, 1);

        disp_enc = new QLabel(gridLayoutWidget_2);
        disp_enc->setObjectName(QStringLiteral("disp_enc"));
        disp_enc->setAutoFillBackground(false);
        disp_enc->setFrameShape(QFrame::Box);
        disp_enc->setFrameShadow(QFrame::Raised);
        disp_enc->setLineWidth(1);
        disp_enc->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_enc, 11, 2, 1, 1);

        label_4 = new QLabel(gridLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 10, 4, 1, 1);

        label_11 = new QLabel(gridLayoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setLayoutDirection(Qt::LeftToRight);
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_11, 7, 0, 1, 1);

        label_13 = new QLabel(gridLayoutWidget_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setLayoutDirection(Qt::LeftToRight);
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_13, 10, 0, 1, 1);

        disp_current_d = new QLabel(gridLayoutWidget_2);
        disp_current_d->setObjectName(QStringLiteral("disp_current_d"));
        disp_current_d->setAutoFillBackground(false);
        disp_current_d->setFrameShape(QFrame::Box);
        disp_current_d->setFrameShadow(QFrame::Raised);
        disp_current_d->setLineWidth(1);
        disp_current_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_current_d, 10, 3, 1, 1);

        disp_ana_d = new QLabel(gridLayoutWidget_2);
        disp_ana_d->setObjectName(QStringLiteral("disp_ana_d"));
        disp_ana_d->setAutoFillBackground(false);
        disp_ana_d->setFrameShape(QFrame::Box);
        disp_ana_d->setFrameShadow(QFrame::Raised);
        disp_ana_d->setLineWidth(1);
        disp_ana_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_ana_d, 8, 3, 1, 1);

        disp_accz = new QLabel(gridLayoutWidget_2);
        disp_accz->setObjectName(QStringLiteral("disp_accz"));
        disp_accz->setAutoFillBackground(false);
        disp_accz->setFrameShape(QFrame::Box);
        disp_accz->setFrameShadow(QFrame::Raised);
        disp_accz->setLineWidth(1);
        disp_accz->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_accz, 3, 2, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setLayoutDirection(Qt::LeftToRight);
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_15, 15, 0, 2, 1);

        disp_gyrox = new QLabel(gridLayoutWidget_2);
        disp_gyrox->setObjectName(QStringLiteral("disp_gyrox"));
        disp_gyrox->setAutoFillBackground(false);
        disp_gyrox->setFrameShape(QFrame::Box);
        disp_gyrox->setFrameShadow(QFrame::Raised);
        disp_gyrox->setLineWidth(1);
        disp_gyrox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_gyrox, 4, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 2, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 6, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_9, 5, 1, 1, 1);

        label_42 = new QLabel(gridLayoutWidget_2);
        label_42->setObjectName(QStringLiteral("label_42"));

        gridLayout_2->addWidget(label_42, 13, 4, 1, 1);

        label_imu_a_x = new QLabel(gridLayoutWidget_2);
        label_imu_a_x->setObjectName(QStringLiteral("label_imu_a_x"));

        gridLayout_2->addWidget(label_imu_a_x, 1, 4, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 1, 1, 1, 1);

        disp_gyroy = new QLabel(gridLayoutWidget_2);
        disp_gyroy->setObjectName(QStringLiteral("disp_gyroy"));
        disp_gyroy->setAutoFillBackground(false);
        disp_gyroy->setFrameShape(QFrame::Box);
        disp_gyroy->setFrameShadow(QFrame::Raised);
        disp_gyroy->setLineWidth(1);
        disp_gyroy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_gyroy, 5, 2, 1, 1);

        label_10 = new QLabel(gridLayoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setLayoutDirection(Qt::LeftToRight);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 4, 0, 3, 1);

        disp_gyroz = new QLabel(gridLayoutWidget_2);
        disp_gyroz->setObjectName(QStringLiteral("disp_gyroz"));
        disp_gyroz->setAutoFillBackground(false);
        disp_gyroz->setFrameShape(QFrame::Box);
        disp_gyroz->setFrameShadow(QFrame::Raised);
        disp_gyroz->setLineWidth(1);
        disp_gyroz->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_gyroz, 6, 2, 1, 1);

        label_107 = new QLabel(gridLayoutWidget_2);
        label_107->setObjectName(QStringLiteral("label_107"));
        label_107->setLayoutDirection(Qt::LeftToRight);
        label_107->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_107, 9, 1, 1, 1);

        label_12 = new QLabel(gridLayoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setLayoutDirection(Qt::LeftToRight);
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_12, 8, 0, 2, 1);

        disp_ana1 = new QLabel(gridLayoutWidget_2);
        disp_ana1->setObjectName(QStringLiteral("disp_ana1"));
        disp_ana1->setAutoFillBackground(false);
        disp_ana1->setFrameShape(QFrame::Box);
        disp_ana1->setFrameShadow(QFrame::Raised);
        disp_ana1->setLineWidth(1);
        disp_ana1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_ana1, 9, 2, 1, 1);

        disp_ana1_d = new QLabel(gridLayoutWidget_2);
        disp_ana1_d->setObjectName(QStringLiteral("disp_ana1_d"));
        disp_ana1_d->setAutoFillBackground(false);
        disp_ana1_d->setFrameShape(QFrame::Box);
        disp_ana1_d->setFrameShadow(QFrame::Raised);
        disp_ana1_d->setLineWidth(1);
        disp_ana1_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(disp_ana1_d, 9, 3, 1, 1);

        label_108 = new QLabel(gridLayoutWidget_2);
        label_108->setObjectName(QStringLiteral("label_108"));

        gridLayout_2->addWidget(label_108, 9, 4, 1, 1);

        label_status1 = new QLabel(gridLayoutWidget_2);
        label_status1->setObjectName(QStringLiteral("label_status1"));

        gridLayout_2->addWidget(label_status1, 15, 3, 1, 3);

        label_status2 = new QLabel(gridLayoutWidget_2);
        label_status2->setObjectName(QStringLiteral("label_status2"));

        gridLayout_2->addWidget(label_status2, 16, 3, 1, 3);

        tabWidget->addTab(stream_ex, QString());
        stream_manage = new QWidget();
        stream_manage->setObjectName(QStringLiteral("stream_manage"));
        tabWidget->addTab(stream_manage, QString());
        stream_strain = new QWidget();
        stream_strain->setObjectName(QStringLiteral("stream_strain"));
        gridLayoutWidget_9 = new QWidget(stream_strain);
        gridLayoutWidget_9->setObjectName(QStringLiteral("gridLayoutWidget_9"));
        gridLayoutWidget_9->setGeometry(QRect(9, 9, 551, 341));
        gridLayout_10 = new QGridLayout(gridLayoutWidget_9);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        strain_offs_ch6 = new QLineEdit(gridLayoutWidget_9);
        strain_offs_ch6->setObjectName(QStringLiteral("strain_offs_ch6"));
        sizePolicy.setHeightForWidth(strain_offs_ch6->sizePolicy().hasHeightForWidth());
        strain_offs_ch6->setSizePolicy(sizePolicy);
        strain_offs_ch6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(strain_offs_ch6, 6, 4, 1, 1);

        strain_offs_ch5 = new QLineEdit(gridLayoutWidget_9);
        strain_offs_ch5->setObjectName(QStringLiteral("strain_offs_ch5"));
        sizePolicy.setHeightForWidth(strain_offs_ch5->sizePolicy().hasHeightForWidth());
        strain_offs_ch5->setSizePolicy(sizePolicy);
        strain_offs_ch5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(strain_offs_ch5, 5, 4, 1, 1);

        label_67 = new QLabel(gridLayoutWidget_9);
        label_67->setObjectName(QStringLiteral("label_67"));
        label_67->setLayoutDirection(Qt::LeftToRight);
        label_67->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_67, 5, 0, 1, 1);

        label_32 = new QLabel(gridLayoutWidget_9);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_32, 0, 1, 1, 1);

        disp_strain_ch6 = new QLabel(gridLayoutWidget_9);
        disp_strain_ch6->setObjectName(QStringLiteral("disp_strain_ch6"));
        disp_strain_ch6->setAutoFillBackground(false);
        disp_strain_ch6->setFrameShape(QFrame::Box);
        disp_strain_ch6->setFrameShadow(QFrame::Raised);
        disp_strain_ch6->setLineWidth(1);
        disp_strain_ch6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch6, 6, 1, 1, 1);

        disp_strain_ch1 = new QLabel(gridLayoutWidget_9);
        disp_strain_ch1->setObjectName(QStringLiteral("disp_strain_ch1"));
        disp_strain_ch1->setAutoFillBackground(false);
        disp_strain_ch1->setFrameShape(QFrame::Box);
        disp_strain_ch1->setFrameShadow(QFrame::Raised);
        disp_strain_ch1->setLineWidth(1);
        disp_strain_ch1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch1, 1, 1, 1, 1);

        disp_strain_ch5_d = new QLabel(gridLayoutWidget_9);
        disp_strain_ch5_d->setObjectName(QStringLiteral("disp_strain_ch5_d"));
        disp_strain_ch5_d->setAutoFillBackground(false);
        disp_strain_ch5_d->setFrameShape(QFrame::Box);
        disp_strain_ch5_d->setFrameShadow(QFrame::Raised);
        disp_strain_ch5_d->setLineWidth(1);
        disp_strain_ch5_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch5_d, 5, 2, 1, 1);

        disp_strain_ch6_d = new QLabel(gridLayoutWidget_9);
        disp_strain_ch6_d->setObjectName(QStringLiteral("disp_strain_ch6_d"));
        disp_strain_ch6_d->setAutoFillBackground(false);
        disp_strain_ch6_d->setFrameShape(QFrame::Box);
        disp_strain_ch6_d->setFrameShadow(QFrame::Raised);
        disp_strain_ch6_d->setLineWidth(1);
        disp_strain_ch6_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch6_d, 6, 2, 1, 1);

        label_33 = new QLabel(gridLayoutWidget_9);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_33, 0, 0, 1, 1);

        disp_strain_ch1_d = new QLabel(gridLayoutWidget_9);
        disp_strain_ch1_d->setObjectName(QStringLiteral("disp_strain_ch1_d"));
        disp_strain_ch1_d->setAutoFillBackground(false);
        disp_strain_ch1_d->setFrameShape(QFrame::Box);
        disp_strain_ch1_d->setFrameShadow(QFrame::Raised);
        disp_strain_ch1_d->setLineWidth(1);
        disp_strain_ch1_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch1_d, 1, 2, 1, 1);

        label_35 = new QLabel(gridLayoutWidget_9);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setLayoutDirection(Qt::LeftToRight);
        label_35->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_35, 2, 0, 1, 1);

        label_68 = new QLabel(gridLayoutWidget_9);
        label_68->setObjectName(QStringLiteral("label_68"));
        label_68->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_68, 0, 4, 1, 1);

        label_70 = new QLabel(gridLayoutWidget_9);
        label_70->setObjectName(QStringLiteral("label_70"));
        label_70->setLayoutDirection(Qt::LeftToRight);
        label_70->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_70, 4, 0, 1, 1);

        disp_strain_ch5 = new QLabel(gridLayoutWidget_9);
        disp_strain_ch5->setObjectName(QStringLiteral("disp_strain_ch5"));
        disp_strain_ch5->setAutoFillBackground(false);
        disp_strain_ch5->setFrameShape(QFrame::Box);
        disp_strain_ch5->setFrameShadow(QFrame::Raised);
        disp_strain_ch5->setLineWidth(1);
        disp_strain_ch5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch5, 5, 1, 1, 1);

        label_36 = new QLabel(gridLayoutWidget_9);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setLayoutDirection(Qt::LeftToRight);
        label_36->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_36, 3, 0, 1, 1);

        label_69 = new QLabel(gridLayoutWidget_9);
        label_69->setObjectName(QStringLiteral("label_69"));
        label_69->setLayoutDirection(Qt::LeftToRight);
        label_69->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_69, 6, 0, 1, 1);

        label_31 = new QLabel(gridLayoutWidget_9);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_31, 0, 2, 1, 1);

        label_34 = new QLabel(gridLayoutWidget_9);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setLayoutDirection(Qt::LeftToRight);
        label_34->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_34, 1, 0, 1, 1);

        disp_strain_ch2 = new QLabel(gridLayoutWidget_9);
        disp_strain_ch2->setObjectName(QStringLiteral("disp_strain_ch2"));
        disp_strain_ch2->setAutoFillBackground(false);
        disp_strain_ch2->setFrameShape(QFrame::Box);
        disp_strain_ch2->setFrameShadow(QFrame::Raised);
        disp_strain_ch2->setLineWidth(1);
        disp_strain_ch2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch2, 2, 1, 1, 1);

        disp_strain_ch3 = new QLabel(gridLayoutWidget_9);
        disp_strain_ch3->setObjectName(QStringLiteral("disp_strain_ch3"));
        disp_strain_ch3->setAutoFillBackground(false);
        disp_strain_ch3->setFrameShape(QFrame::Box);
        disp_strain_ch3->setFrameShadow(QFrame::Raised);
        disp_strain_ch3->setLineWidth(1);
        disp_strain_ch3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch3, 3, 1, 1, 1);

        disp_strain_ch3_d = new QLabel(gridLayoutWidget_9);
        disp_strain_ch3_d->setObjectName(QStringLiteral("disp_strain_ch3_d"));
        disp_strain_ch3_d->setAutoFillBackground(false);
        disp_strain_ch3_d->setFrameShape(QFrame::Box);
        disp_strain_ch3_d->setFrameShadow(QFrame::Raised);
        disp_strain_ch3_d->setLineWidth(1);
        disp_strain_ch3_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch3_d, 3, 2, 1, 1);

        disp_strain_ch2_d = new QLabel(gridLayoutWidget_9);
        disp_strain_ch2_d->setObjectName(QStringLiteral("disp_strain_ch2_d"));
        disp_strain_ch2_d->setAutoFillBackground(false);
        disp_strain_ch2_d->setFrameShape(QFrame::Box);
        disp_strain_ch2_d->setFrameShadow(QFrame::Raised);
        disp_strain_ch2_d->setLineWidth(1);
        disp_strain_ch2_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch2_d, 2, 2, 1, 1);

        disp_strain_ch4_d = new QLabel(gridLayoutWidget_9);
        disp_strain_ch4_d->setObjectName(QStringLiteral("disp_strain_ch4_d"));
        disp_strain_ch4_d->setAutoFillBackground(false);
        disp_strain_ch4_d->setFrameShape(QFrame::Box);
        disp_strain_ch4_d->setFrameShadow(QFrame::Raised);
        disp_strain_ch4_d->setLineWidth(1);
        disp_strain_ch4_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch4_d, 4, 2, 1, 1);

        disp_strain_ch4 = new QLabel(gridLayoutWidget_9);
        disp_strain_ch4->setObjectName(QStringLiteral("disp_strain_ch4"));
        disp_strain_ch4->setAutoFillBackground(false);
        disp_strain_ch4->setFrameShape(QFrame::Box);
        disp_strain_ch4->setFrameShadow(QFrame::Raised);
        disp_strain_ch4->setLineWidth(1);
        disp_strain_ch4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(disp_strain_ch4, 4, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(120, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_7, 8, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(120, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_5, 8, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(120, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_4, 8, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_6, 8, 3, 1, 1);

        stream_SA_RefreshOffset = new QPushButton(gridLayoutWidget_9);
        stream_SA_RefreshOffset->setObjectName(QStringLiteral("stream_SA_RefreshOffset"));

        gridLayout_10->addWidget(stream_SA_RefreshOffset, 7, 4, 1, 1);

        strain_offs_ch3 = new QLineEdit(gridLayoutWidget_9);
        strain_offs_ch3->setObjectName(QStringLiteral("strain_offs_ch3"));
        sizePolicy.setHeightForWidth(strain_offs_ch3->sizePolicy().hasHeightForWidth());
        strain_offs_ch3->setSizePolicy(sizePolicy);
        strain_offs_ch3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(strain_offs_ch3, 3, 4, 1, 1);

        strain_offs_ch1 = new QLineEdit(gridLayoutWidget_9);
        strain_offs_ch1->setObjectName(QStringLiteral("strain_offs_ch1"));
        sizePolicy2.setHeightForWidth(strain_offs_ch1->sizePolicy().hasHeightForWidth());
        strain_offs_ch1->setSizePolicy(sizePolicy2);
        strain_offs_ch1->setMinimumSize(QSize(0, 0));
        strain_offs_ch1->setSizeIncrement(QSize(100, 0));
        strain_offs_ch1->setBaseSize(QSize(100, 0));
        strain_offs_ch1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(strain_offs_ch1, 1, 4, 1, 1);

        strain_offs_ch2 = new QLineEdit(gridLayoutWidget_9);
        strain_offs_ch2->setObjectName(QStringLiteral("strain_offs_ch2"));
        sizePolicy.setHeightForWidth(strain_offs_ch2->sizePolicy().hasHeightForWidth());
        strain_offs_ch2->setSizePolicy(sizePolicy);
        strain_offs_ch2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(strain_offs_ch2, 2, 4, 1, 1);

        strain_offs_ch4 = new QLineEdit(gridLayoutWidget_9);
        strain_offs_ch4->setObjectName(QStringLiteral("strain_offs_ch4"));
        sizePolicy.setHeightForWidth(strain_offs_ch4->sizePolicy().hasHeightForWidth());
        strain_offs_ch4->setSizePolicy(sizePolicy);
        strain_offs_ch4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_10->addWidget(strain_offs_ch4, 4, 4, 1, 1);

        tabWidget->addTab(stream_strain, QString());
        stream_ricnu = new QWidget();
        stream_ricnu->setObjectName(QStringLiteral("stream_ricnu"));
        gridLayoutWidget_10 = new QWidget(stream_ricnu);
        gridLayoutWidget_10->setObjectName(QStringLiteral("gridLayoutWidget_10"));
        gridLayoutWidget_10->setGeometry(QRect(10, 10, 721, 581));
        gridLayout_11 = new QGridLayout(gridLayoutWidget_10);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        label_84 = new QLabel(gridLayoutWidget_10);
        label_84->setObjectName(QStringLiteral("label_84"));
        label_84->setLayoutDirection(Qt::LeftToRight);
        label_84->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_84, 11, 1, 1, 1);

        label_imu_a_y_2 = new QLabel(gridLayoutWidget_10);
        label_imu_a_y_2->setObjectName(QStringLiteral("label_imu_a_y_2"));

        gridLayout_11->addWidget(label_imu_a_y_2, 2, 4, 1, 1);

        label_93 = new QLabel(gridLayoutWidget_10);
        label_93->setObjectName(QStringLiteral("label_93"));
        label_93->setLayoutDirection(Qt::LeftToRight);
        label_93->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_93, 10, 0, 1, 1);

        label_imu_a_x_2 = new QLabel(gridLayoutWidget_10);
        label_imu_a_x_2->setObjectName(QStringLiteral("label_imu_a_x_2"));

        gridLayout_11->addWidget(label_imu_a_x_2, 1, 4, 1, 1);

        label_74 = new QLabel(gridLayoutWidget_10);
        label_74->setObjectName(QStringLiteral("label_74"));

        gridLayout_11->addWidget(label_74, 7, 4, 1, 1);

        ricnu_current_d = new QLabel(gridLayoutWidget_10);
        ricnu_current_d->setObjectName(QStringLiteral("ricnu_current_d"));
        ricnu_current_d->setAutoFillBackground(false);
        ricnu_current_d->setFrameShape(QFrame::Box);
        ricnu_current_d->setFrameShadow(QFrame::Raised);
        ricnu_current_d->setLineWidth(1);
        ricnu_current_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_current_d, 7, 3, 1, 1);

        label_76 = new QLabel(gridLayoutWidget_10);
        label_76->setObjectName(QStringLiteral("label_76"));
        label_76->setLayoutDirection(Qt::LeftToRight);
        label_76->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_76, 1, 0, 3, 1);

        label_imu_g_y_2 = new QLabel(gridLayoutWidget_10);
        label_imu_g_y_2->setObjectName(QStringLiteral("label_imu_g_y_2"));

        gridLayout_11->addWidget(label_imu_g_y_2, 5, 4, 1, 1);

        label_81 = new QLabel(gridLayoutWidget_10);
        label_81->setObjectName(QStringLiteral("label_81"));
        label_81->setLayoutDirection(Qt::LeftToRight);
        label_81->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_81, 4, 0, 3, 1);

        label_80 = new QLabel(gridLayoutWidget_10);
        label_80->setObjectName(QStringLiteral("label_80"));
        label_80->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_80, 4, 1, 1, 1);

        label_82 = new QLabel(gridLayoutWidget_10);
        label_82->setObjectName(QStringLiteral("label_82"));
        label_82->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_82, 1, 1, 1, 1);

        label_83 = new QLabel(gridLayoutWidget_10);
        label_83->setObjectName(QStringLiteral("label_83"));
        label_83->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_83, 2, 1, 1, 1);

        label_85 = new QLabel(gridLayoutWidget_10);
        label_85->setObjectName(QStringLiteral("label_85"));
        label_85->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_85, 6, 1, 1, 1);

        label_87 = new QLabel(gridLayoutWidget_10);
        label_87->setObjectName(QStringLiteral("label_87"));
        label_87->setLayoutDirection(Qt::LeftToRight);
        label_87->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_87, 7, 0, 1, 1);

        label_89 = new QLabel(gridLayoutWidget_10);
        label_89->setObjectName(QStringLiteral("label_89"));
        label_89->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_89, 3, 1, 1, 1);

        label_88 = new QLabel(gridLayoutWidget_10);
        label_88->setObjectName(QStringLiteral("label_88"));
        label_88->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_88, 5, 1, 1, 1);

        ricnu_enc_mot = new QLabel(gridLayoutWidget_10);
        ricnu_enc_mot->setObjectName(QStringLiteral("ricnu_enc_mot"));
        ricnu_enc_mot->setAutoFillBackground(false);
        ricnu_enc_mot->setFrameShape(QFrame::Box);
        ricnu_enc_mot->setFrameShadow(QFrame::Raised);
        ricnu_enc_mot->setLineWidth(1);
        ricnu_enc_mot->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_enc_mot, 8, 2, 1, 1);

        ricnu_accx = new QLabel(gridLayoutWidget_10);
        ricnu_accx->setObjectName(QStringLiteral("ricnu_accx"));
        ricnu_accx->setAutoFillBackground(false);
        ricnu_accx->setFrameShape(QFrame::Box);
        ricnu_accx->setFrameShadow(QFrame::Raised);
        ricnu_accx->setLineWidth(1);
        ricnu_accx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_accx, 1, 2, 1, 1);

        ricnu_accy = new QLabel(gridLayoutWidget_10);
        ricnu_accy->setObjectName(QStringLiteral("ricnu_accy"));
        ricnu_accy->setAutoFillBackground(false);
        ricnu_accy->setFrameShape(QFrame::Box);
        ricnu_accy->setFrameShadow(QFrame::Raised);
        ricnu_accy->setLineWidth(1);
        ricnu_accy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_accy, 2, 2, 1, 1);

        ricnu_accz = new QLabel(gridLayoutWidget_10);
        ricnu_accz->setObjectName(QStringLiteral("ricnu_accz"));
        ricnu_accz->setAutoFillBackground(false);
        ricnu_accz->setFrameShape(QFrame::Box);
        ricnu_accz->setFrameShadow(QFrame::Raised);
        ricnu_accz->setLineWidth(1);
        ricnu_accz->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_accz, 3, 2, 1, 1);

        ricnu_enc_joint = new QLabel(gridLayoutWidget_10);
        ricnu_enc_joint->setObjectName(QStringLiteral("ricnu_enc_joint"));
        ricnu_enc_joint->setAutoFillBackground(false);
        ricnu_enc_joint->setFrameShape(QFrame::Box);
        ricnu_enc_joint->setFrameShadow(QFrame::Raised);
        ricnu_enc_joint->setLineWidth(1);
        ricnu_enc_joint->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_enc_joint, 9, 2, 1, 1);

        ricnu_gyrox = new QLabel(gridLayoutWidget_10);
        ricnu_gyrox->setObjectName(QStringLiteral("ricnu_gyrox"));
        ricnu_gyrox->setAutoFillBackground(false);
        ricnu_gyrox->setFrameShape(QFrame::Box);
        ricnu_gyrox->setFrameShadow(QFrame::Raised);
        ricnu_gyrox->setLineWidth(1);
        ricnu_gyrox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_gyrox, 4, 2, 1, 1);

        ricnu_gyroy = new QLabel(gridLayoutWidget_10);
        ricnu_gyroy->setObjectName(QStringLiteral("ricnu_gyroy"));
        ricnu_gyroy->setAutoFillBackground(false);
        ricnu_gyroy->setFrameShape(QFrame::Box);
        ricnu_gyroy->setFrameShadow(QFrame::Raised);
        ricnu_gyroy->setLineWidth(1);
        ricnu_gyroy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_gyroy, 5, 2, 1, 1);

        ricnu_current = new QLabel(gridLayoutWidget_10);
        ricnu_current->setObjectName(QStringLiteral("ricnu_current"));
        ricnu_current->setAutoFillBackground(false);
        ricnu_current->setFrameShape(QFrame::Box);
        ricnu_current->setFrameShadow(QFrame::Raised);
        ricnu_current->setLineWidth(1);
        ricnu_current->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_current, 7, 2, 1, 1);

        ricnu_gyroz = new QLabel(gridLayoutWidget_10);
        ricnu_gyroz->setObjectName(QStringLiteral("ricnu_gyroz"));
        ricnu_gyroz->setAutoFillBackground(false);
        ricnu_gyroz->setFrameShape(QFrame::Box);
        ricnu_gyroz->setFrameShadow(QFrame::Raised);
        ricnu_gyroz->setLineWidth(1);
        ricnu_gyroz->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_gyroz, 6, 2, 1, 1);

        ricnu_gyroz_d = new QLabel(gridLayoutWidget_10);
        ricnu_gyroz_d->setObjectName(QStringLiteral("ricnu_gyroz_d"));
        ricnu_gyroz_d->setAutoFillBackground(false);
        ricnu_gyroz_d->setFrameShape(QFrame::Box);
        ricnu_gyroz_d->setFrameShadow(QFrame::Raised);
        ricnu_gyroz_d->setLineWidth(1);
        ricnu_gyroz_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_gyroz_d, 6, 3, 1, 1);

        ricnu_accy_d = new QLabel(gridLayoutWidget_10);
        ricnu_accy_d->setObjectName(QStringLiteral("ricnu_accy_d"));
        ricnu_accy_d->setAutoFillBackground(false);
        ricnu_accy_d->setFrameShape(QFrame::Box);
        ricnu_accy_d->setFrameShadow(QFrame::Raised);
        ricnu_accy_d->setLineWidth(1);
        ricnu_accy_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_accy_d, 2, 3, 1, 1);

        label_91 = new QLabel(gridLayoutWidget_10);
        label_91->setObjectName(QStringLiteral("label_91"));

        gridLayout_11->addWidget(label_91, 10, 4, 1, 1);

        ricnu_accx_d = new QLabel(gridLayoutWidget_10);
        ricnu_accx_d->setObjectName(QStringLiteral("ricnu_accx_d"));
        ricnu_accx_d->setAutoFillBackground(false);
        ricnu_accx_d->setFrameShape(QFrame::Box);
        ricnu_accx_d->setFrameShadow(QFrame::Raised);
        ricnu_accx_d->setLineWidth(1);
        ricnu_accx_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_accx_d, 1, 3, 1, 1);

        ricnu_gyrox_d = new QLabel(gridLayoutWidget_10);
        ricnu_gyrox_d->setObjectName(QStringLiteral("ricnu_gyrox_d"));
        ricnu_gyrox_d->setAutoFillBackground(false);
        ricnu_gyrox_d->setFrameShape(QFrame::Box);
        ricnu_gyrox_d->setFrameShadow(QFrame::Raised);
        ricnu_gyrox_d->setLineWidth(1);
        ricnu_gyrox_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_gyrox_d, 4, 3, 1, 1);

        label_imu_g_x_2 = new QLabel(gridLayoutWidget_10);
        label_imu_g_x_2->setObjectName(QStringLiteral("label_imu_g_x_2"));

        gridLayout_11->addWidget(label_imu_g_x_2, 4, 4, 1, 1);

        label_imu_g_z_2 = new QLabel(gridLayoutWidget_10);
        label_imu_g_z_2->setObjectName(QStringLiteral("label_imu_g_z_2"));

        gridLayout_11->addWidget(label_imu_g_z_2, 6, 4, 1, 1);

        ricnu_accz_d = new QLabel(gridLayoutWidget_10);
        ricnu_accz_d->setObjectName(QStringLiteral("ricnu_accz_d"));
        ricnu_accz_d->setAutoFillBackground(false);
        ricnu_accz_d->setFrameShape(QFrame::Box);
        ricnu_accz_d->setFrameShadow(QFrame::Raised);
        ricnu_accz_d->setLineWidth(1);
        ricnu_accz_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_accz_d, 3, 3, 1, 1);

        ricnu_gyroy_d = new QLabel(gridLayoutWidget_10);
        ricnu_gyroy_d->setObjectName(QStringLiteral("ricnu_gyroy_d"));
        ricnu_gyroy_d->setAutoFillBackground(false);
        ricnu_gyroy_d->setFrameShape(QFrame::Box);
        ricnu_gyroy_d->setFrameShadow(QFrame::Raised);
        ricnu_gyroy_d->setLineWidth(1);
        ricnu_gyroy_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_gyroy_d, 5, 3, 1, 1);

        label_92 = new QLabel(gridLayoutWidget_10);
        label_92->setObjectName(QStringLiteral("label_92"));
        label_92->setLayoutDirection(Qt::LeftToRight);
        label_92->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_92, 10, 1, 1, 1);

        label_imu_a_z_2 = new QLabel(gridLayoutWidget_10);
        label_imu_a_z_2->setObjectName(QStringLiteral("label_imu_a_z_2"));

        gridLayout_11->addWidget(label_imu_a_z_2, 3, 4, 1, 1);

        label_94 = new QLabel(gridLayoutWidget_10);
        label_94->setObjectName(QStringLiteral("label_94"));
        label_94->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_94, 0, 2, 1, 1);

        ricnu_vb = new QLabel(gridLayoutWidget_10);
        ricnu_vb->setObjectName(QStringLiteral("ricnu_vb"));
        ricnu_vb->setAutoFillBackground(false);
        ricnu_vb->setFrameShape(QFrame::Box);
        ricnu_vb->setFrameShadow(QFrame::Raised);
        ricnu_vb->setLineWidth(1);
        ricnu_vb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_vb, 10, 2, 1, 1);

        ricnu_vb_d = new QLabel(gridLayoutWidget_10);
        ricnu_vb_d->setObjectName(QStringLiteral("ricnu_vb_d"));
        ricnu_vb_d->setAutoFillBackground(false);
        ricnu_vb_d->setFrameShape(QFrame::Box);
        ricnu_vb_d->setFrameShadow(QFrame::Raised);
        ricnu_vb_d->setLineWidth(1);
        ricnu_vb_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_vb_d, 10, 3, 1, 1);

        horizontalSlider_current_zero_2 = new QSlider(gridLayoutWidget_10);
        horizontalSlider_current_zero_2->setObjectName(QStringLiteral("horizontalSlider_current_zero_2"));
        sizePolicy.setHeightForWidth(horizontalSlider_current_zero_2->sizePolicy().hasHeightForWidth());
        horizontalSlider_current_zero_2->setSizePolicy(sizePolicy);
        horizontalSlider_current_zero_2->setMinimumSize(QSize(150, 0));
        horizontalSlider_current_zero_2->setMinimum(-125);
        horizontalSlider_current_zero_2->setMaximum(125);
        horizontalSlider_current_zero_2->setOrientation(Qt::Horizontal);

        gridLayout_11->addWidget(horizontalSlider_current_zero_2, 7, 5, 1, 1);

        label_99 = new QLabel(gridLayoutWidget_10);
        label_99->setObjectName(QStringLiteral("label_99"));
        label_99->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_99, 0, 3, 1, 1);

        label_100 = new QLabel(gridLayoutWidget_10);
        label_100->setObjectName(QStringLiteral("label_100"));
        label_100->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_100, 0, 5, 1, 1);

        label_95 = new QLabel(gridLayoutWidget_10);
        label_95->setObjectName(QStringLiteral("label_95"));
        label_95->setLayoutDirection(Qt::LeftToRight);
        label_95->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_95, 8, 1, 1, 1);

        label_96 = new QLabel(gridLayoutWidget_10);
        label_96->setObjectName(QStringLiteral("label_96"));
        label_96->setLayoutDirection(Qt::LeftToRight);
        label_96->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_96, 9, 1, 1, 1);

        label_78 = new QLabel(gridLayoutWidget_10);
        label_78->setObjectName(QStringLiteral("label_78"));
        label_78->setLayoutDirection(Qt::LeftToRight);
        label_78->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_78, 8, 0, 2, 1);

        label_77 = new QLabel(gridLayoutWidget_10);
        label_77->setObjectName(QStringLiteral("label_77"));
        label_77->setLayoutDirection(Qt::LeftToRight);
        label_77->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_77, 14, 1, 1, 1);

        label_75 = new QLabel(gridLayoutWidget_10);
        label_75->setObjectName(QStringLiteral("label_75"));
        label_75->setLayoutDirection(Qt::LeftToRight);
        label_75->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_75, 12, 1, 1, 1);

        label_86 = new QLabel(gridLayoutWidget_10);
        label_86->setObjectName(QStringLiteral("label_86"));
        label_86->setLayoutDirection(Qt::LeftToRight);
        label_86->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_86, 13, 1, 1, 1);

        label_79 = new QLabel(gridLayoutWidget_10);
        label_79->setObjectName(QStringLiteral("label_79"));
        label_79->setLayoutDirection(Qt::LeftToRight);
        label_79->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_79, 15, 1, 1, 1);

        label_73 = new QLabel(gridLayoutWidget_10);
        label_73->setObjectName(QStringLiteral("label_73"));
        label_73->setLayoutDirection(Qt::LeftToRight);
        label_73->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_73, 16, 1, 1, 1);

        ricnu_strain_ch1 = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch1->setObjectName(QStringLiteral("ricnu_strain_ch1"));
        ricnu_strain_ch1->setAutoFillBackground(false);
        ricnu_strain_ch1->setFrameShape(QFrame::Box);
        ricnu_strain_ch1->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch1->setLineWidth(1);
        ricnu_strain_ch1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch1, 11, 2, 1, 1);

        label_97 = new QLabel(gridLayoutWidget_10);
        label_97->setObjectName(QStringLiteral("label_97"));
        label_97->setLayoutDirection(Qt::LeftToRight);
        label_97->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(label_97, 11, 0, 6, 1);

        ricnu_strain_ch1_d = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch1_d->setObjectName(QStringLiteral("ricnu_strain_ch1_d"));
        ricnu_strain_ch1_d->setAutoFillBackground(false);
        ricnu_strain_ch1_d->setFrameShape(QFrame::Box);
        ricnu_strain_ch1_d->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch1_d->setLineWidth(1);
        ricnu_strain_ch1_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch1_d, 11, 3, 1, 1);

        ricnu_strain_ch2 = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch2->setObjectName(QStringLiteral("ricnu_strain_ch2"));
        ricnu_strain_ch2->setAutoFillBackground(false);
        ricnu_strain_ch2->setFrameShape(QFrame::Box);
        ricnu_strain_ch2->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch2->setLineWidth(1);
        ricnu_strain_ch2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch2, 12, 2, 1, 1);

        ricnu_strain_ch2_d = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch2_d->setObjectName(QStringLiteral("ricnu_strain_ch2_d"));
        ricnu_strain_ch2_d->setAutoFillBackground(false);
        ricnu_strain_ch2_d->setFrameShape(QFrame::Box);
        ricnu_strain_ch2_d->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch2_d->setLineWidth(1);
        ricnu_strain_ch2_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch2_d, 12, 3, 1, 1);

        ricnu_strain_ch3 = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch3->setObjectName(QStringLiteral("ricnu_strain_ch3"));
        ricnu_strain_ch3->setAutoFillBackground(false);
        ricnu_strain_ch3->setFrameShape(QFrame::Box);
        ricnu_strain_ch3->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch3->setLineWidth(1);
        ricnu_strain_ch3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch3, 13, 2, 1, 1);

        ricnu_strain_ch4 = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch4->setObjectName(QStringLiteral("ricnu_strain_ch4"));
        ricnu_strain_ch4->setAutoFillBackground(false);
        ricnu_strain_ch4->setFrameShape(QFrame::Box);
        ricnu_strain_ch4->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch4->setLineWidth(1);
        ricnu_strain_ch4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch4, 14, 2, 1, 1);

        ricnu_strain_ch3_d = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch3_d->setObjectName(QStringLiteral("ricnu_strain_ch3_d"));
        ricnu_strain_ch3_d->setAutoFillBackground(false);
        ricnu_strain_ch3_d->setFrameShape(QFrame::Box);
        ricnu_strain_ch3_d->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch3_d->setLineWidth(1);
        ricnu_strain_ch3_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch3_d, 13, 3, 1, 1);

        ricnu_strain_ch4_d = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch4_d->setObjectName(QStringLiteral("ricnu_strain_ch4_d"));
        ricnu_strain_ch4_d->setAutoFillBackground(false);
        ricnu_strain_ch4_d->setFrameShape(QFrame::Box);
        ricnu_strain_ch4_d->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch4_d->setLineWidth(1);
        ricnu_strain_ch4_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch4_d, 14, 3, 1, 1);

        ricnu_strain_ch5 = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch5->setObjectName(QStringLiteral("ricnu_strain_ch5"));
        ricnu_strain_ch5->setAutoFillBackground(false);
        ricnu_strain_ch5->setFrameShape(QFrame::Box);
        ricnu_strain_ch5->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch5->setLineWidth(1);
        ricnu_strain_ch5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch5, 15, 2, 1, 1);

        ricnu_strain_ch6_d = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch6_d->setObjectName(QStringLiteral("ricnu_strain_ch6_d"));
        ricnu_strain_ch6_d->setAutoFillBackground(false);
        ricnu_strain_ch6_d->setFrameShape(QFrame::Box);
        ricnu_strain_ch6_d->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch6_d->setLineWidth(1);
        ricnu_strain_ch6_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch6_d, 16, 3, 1, 1);

        ricnu_strain_ch5_d = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch5_d->setObjectName(QStringLiteral("ricnu_strain_ch5_d"));
        ricnu_strain_ch5_d->setAutoFillBackground(false);
        ricnu_strain_ch5_d->setFrameShape(QFrame::Box);
        ricnu_strain_ch5_d->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch5_d->setLineWidth(1);
        ricnu_strain_ch5_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch5_d, 15, 3, 1, 1);

        label_90 = new QLabel(gridLayoutWidget_10);
        label_90->setObjectName(QStringLiteral("label_90"));

        gridLayout_11->addWidget(label_90, 11, 4, 1, 1);

        ricnu_strain_ch6 = new QLabel(gridLayoutWidget_10);
        ricnu_strain_ch6->setObjectName(QStringLiteral("ricnu_strain_ch6"));
        ricnu_strain_ch6->setAutoFillBackground(false);
        ricnu_strain_ch6->setFrameShape(QFrame::Box);
        ricnu_strain_ch6->setFrameShadow(QFrame::Raised);
        ricnu_strain_ch6->setLineWidth(1);
        ricnu_strain_ch6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(ricnu_strain_ch6, 16, 2, 1, 1);

        label_98 = new QLabel(gridLayoutWidget_10);
        label_98->setObjectName(QStringLiteral("label_98"));

        gridLayout_11->addWidget(label_98, 12, 4, 1, 1);

        label_101 = new QLabel(gridLayoutWidget_10);
        label_101->setObjectName(QStringLiteral("label_101"));

        gridLayout_11->addWidget(label_101, 13, 4, 1, 1);

        label_102 = new QLabel(gridLayoutWidget_10);
        label_102->setObjectName(QStringLiteral("label_102"));

        gridLayout_11->addWidget(label_102, 14, 4, 1, 1);

        label_103 = new QLabel(gridLayoutWidget_10);
        label_103->setObjectName(QStringLiteral("label_103"));

        gridLayout_11->addWidget(label_103, 15, 4, 1, 1);

        label_104 = new QLabel(gridLayoutWidget_10);
        label_104->setObjectName(QStringLiteral("label_104"));

        gridLayout_11->addWidget(label_104, 16, 4, 1, 1);

        tabWidget->addTab(stream_ricnu, QString());
        plot = new QWidget();
        plot->setObjectName(QStringLiteral("plot"));
        gridLayoutWidget_3 = new QWidget(plot);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 10, 1001, 502));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        customPlot = new QCustomPlot(gridLayoutWidget_3);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setMinimumSize(QSize(100, 500));

        gridLayout_3->addWidget(customPlot, 0, 0, 2, 1, Qt::AlignTop);

        horizontalLayoutWidget = new QWidget(plot);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 520, 1001, 151));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        groupBoxXaxisLim = new QGroupBox(horizontalLayoutWidget);
        groupBoxXaxisLim->setObjectName(QStringLiteral("groupBoxXaxisLim"));
        groupBoxXaxisLim->setAutoFillBackground(false);
        gridLayoutWidget_4 = new QWidget(groupBoxXaxisLim);
        gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(0, 20, 294, 95));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        plot_xmin_lineEdit = new QLineEdit(gridLayoutWidget_4);
        plot_xmin_lineEdit->setObjectName(QStringLiteral("plot_xmin_lineEdit"));
        sizePolicy.setHeightForWidth(plot_xmin_lineEdit->sizePolicy().hasHeightForWidth());
        plot_xmin_lineEdit->setSizePolicy(sizePolicy);
        plot_xmin_lineEdit->setMinimumSize(QSize(100, 0));
        plot_xmin_lineEdit->setBaseSize(QSize(100, 0));
        plot_xmin_lineEdit->setReadOnly(true);

        gridLayout_4->addWidget(plot_xmin_lineEdit, 0, 2, 1, 1);

        radioButtonXManual = new QRadioButton(gridLayoutWidget_4);
        radioButtonXManual->setObjectName(QStringLiteral("radioButtonXManual"));

        gridLayout_4->addWidget(radioButtonXManual, 0, 0, 1, 1);

        label_22 = new QLabel(gridLayoutWidget_4);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_4->addWidget(label_22, 0, 1, 1, 1);

        plot_xmax_lineEdit = new QLineEdit(gridLayoutWidget_4);
        plot_xmax_lineEdit->setObjectName(QStringLiteral("plot_xmax_lineEdit"));
        sizePolicy.setHeightForWidth(plot_xmax_lineEdit->sizePolicy().hasHeightForWidth());
        plot_xmax_lineEdit->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(plot_xmax_lineEdit, 1, 2, 1, 1);

        radioButtonXAuto = new QRadioButton(gridLayoutWidget_4);
        radioButtonXAuto->setObjectName(QStringLiteral("radioButtonXAuto"));

        gridLayout_4->addWidget(radioButtonXAuto, 1, 0, 1, 1);

        label_23 = new QLabel(gridLayoutWidget_4);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_4->addWidget(label_23, 1, 1, 1, 1);

        UpdatePlotpushButton = new QPushButton(gridLayoutWidget_4);
        UpdatePlotpushButton->setObjectName(QStringLiteral("UpdatePlotpushButton"));
        sizePolicy.setHeightForWidth(UpdatePlotpushButton->sizePolicy().hasHeightForWidth());
        UpdatePlotpushButton->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(UpdatePlotpushButton, 2, 1, 1, 2);


        horizontalLayout->addWidget(groupBoxXaxisLim);

        groupBoxYaxisLim = new QGroupBox(horizontalLayoutWidget);
        groupBoxYaxisLim->setObjectName(QStringLiteral("groupBoxYaxisLim"));
        gridLayoutWidget_5 = new QWidget(groupBoxYaxisLim);
        gridLayoutWidget_5->setObjectName(QStringLiteral("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(0, 20, 294, 71));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        radioButtonYManual = new QRadioButton(gridLayoutWidget_5);
        radioButtonYManual->setObjectName(QStringLiteral("radioButtonYManual"));

        gridLayout_5->addWidget(radioButtonYManual, 0, 0, 1, 1);

        plot_ymax_lineEdit = new QLineEdit(gridLayoutWidget_5);
        plot_ymax_lineEdit->setObjectName(QStringLiteral("plot_ymax_lineEdit"));

        gridLayout_5->addWidget(plot_ymax_lineEdit, 1, 2, 1, 1);

        radioButtonYAuto = new QRadioButton(gridLayoutWidget_5);
        radioButtonYAuto->setObjectName(QStringLiteral("radioButtonYAuto"));

        gridLayout_5->addWidget(radioButtonYAuto, 1, 0, 1, 1);

        plot_ymin_lineEdit = new QLineEdit(gridLayoutWidget_5);
        plot_ymin_lineEdit->setObjectName(QStringLiteral("plot_ymin_lineEdit"));

        gridLayout_5->addWidget(plot_ymin_lineEdit, 0, 2, 1, 1);

        label_24 = new QLabel(gridLayoutWidget_5);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_5->addWidget(label_24, 0, 1, 1, 1);

        label_25 = new QLabel(gridLayoutWidget_5);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_5->addWidget(label_25, 1, 1, 1, 1);


        horizontalLayout->addWidget(groupBoxYaxisLim);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_t1 = new QLabel(horizontalLayoutWidget);
        label_t1->setObjectName(QStringLiteral("label_t1"));
        sizePolicy3.setHeightForWidth(label_t1->sizePolicy().hasHeightForWidth());
        label_t1->setSizePolicy(sizePolicy3);
        label_t1->setBaseSize(QSize(30, 0));

        gridLayout_7->addWidget(label_t1, 0, 0, 1, 1);

        cBoxvar1 = new QComboBox(horizontalLayoutWidget);
        cBoxvar1->setObjectName(QStringLiteral("cBoxvar1"));

        gridLayout_7->addWidget(cBoxvar1, 0, 1, 1, 1);

        cBoxvar4 = new QComboBox(horizontalLayoutWidget);
        cBoxvar4->setObjectName(QStringLiteral("cBoxvar4"));

        gridLayout_7->addWidget(cBoxvar4, 1, 3, 1, 1);

        cBoxvar6 = new QComboBox(horizontalLayoutWidget);
        cBoxvar6->setObjectName(QStringLiteral("cBoxvar6"));

        gridLayout_7->addWidget(cBoxvar6, 2, 3, 1, 1);

        cBoxvar5 = new QComboBox(horizontalLayoutWidget);
        cBoxvar5->setObjectName(QStringLiteral("cBoxvar5"));

        gridLayout_7->addWidget(cBoxvar5, 2, 1, 1, 1);

        cBoxvar2 = new QComboBox(horizontalLayoutWidget);
        cBoxvar2->setObjectName(QStringLiteral("cBoxvar2"));

        gridLayout_7->addWidget(cBoxvar2, 0, 3, 1, 1);

        cBoxvar3 = new QComboBox(horizontalLayoutWidget);
        cBoxvar3->setObjectName(QStringLiteral("cBoxvar3"));

        gridLayout_7->addWidget(cBoxvar3, 1, 1, 1, 1);

        label_t2 = new QLabel(horizontalLayoutWidget);
        label_t2->setObjectName(QStringLiteral("label_t2"));
        sizePolicy3.setHeightForWidth(label_t2->sizePolicy().hasHeightForWidth());
        label_t2->setSizePolicy(sizePolicy3);
        label_t2->setBaseSize(QSize(30, 0));

        gridLayout_7->addWidget(label_t2, 0, 2, 1, 1);

        label_t3 = new QLabel(horizontalLayoutWidget);
        label_t3->setObjectName(QStringLiteral("label_t3"));
        sizePolicy3.setHeightForWidth(label_t3->sizePolicy().hasHeightForWidth());
        label_t3->setSizePolicy(sizePolicy3);
        label_t3->setBaseSize(QSize(30, 0));

        gridLayout_7->addWidget(label_t3, 1, 0, 1, 1);

        label_t4 = new QLabel(horizontalLayoutWidget);
        label_t4->setObjectName(QStringLiteral("label_t4"));
        sizePolicy3.setHeightForWidth(label_t4->sizePolicy().hasHeightForWidth());
        label_t4->setSizePolicy(sizePolicy3);
        label_t4->setBaseSize(QSize(30, 0));

        gridLayout_7->addWidget(label_t4, 1, 2, 1, 1);

        label_t5 = new QLabel(horizontalLayoutWidget);
        label_t5->setObjectName(QStringLiteral("label_t5"));
        sizePolicy3.setHeightForWidth(label_t5->sizePolicy().hasHeightForWidth());
        label_t5->setSizePolicy(sizePolicy3);
        label_t5->setBaseSize(QSize(30, 0));

        gridLayout_7->addWidget(label_t5, 2, 0, 1, 1);

        label_t6 = new QLabel(horizontalLayoutWidget);
        label_t6->setObjectName(QStringLiteral("label_t6"));
        sizePolicy3.setHeightForWidth(label_t6->sizePolicy().hasHeightForWidth());
        label_t6->setSizePolicy(sizePolicy3);
        label_t6->setBaseSize(QSize(30, 0));

        gridLayout_7->addWidget(label_t6, 2, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout_7);

        tabWidget->addTab(plot, QString());
        exp = new QWidget();
        exp->setObjectName(QStringLiteral("exp"));
        tabWidget->addTab(exp, QString());
        control = new QWidget();
        control->setObjectName(QStringLiteral("control"));
        gridLayoutWidget_7 = new QWidget(control);
        gridLayoutWidget_7->setObjectName(QStringLiteral("gridLayoutWidget_7"));
        gridLayoutWidget_7->setGeometry(QRect(9, 9, 844, 655));
        gridLayout_8 = new QGridLayout(gridLayoutWidget_7);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        label_66 = new QLabel(gridLayoutWidget_7);
        label_66->setObjectName(QStringLiteral("label_66"));

        gridLayout_8->addWidget(label_66, 13, 3, 1, 1);

        control_trapeze_spd = new QLineEdit(gridLayoutWidget_7);
        control_trapeze_spd->setObjectName(QStringLiteral("control_trapeze_spd"));
        sizePolicy.setHeightForWidth(control_trapeze_spd->sizePolicy().hasHeightForWidth());
        control_trapeze_spd->setSizePolicy(sizePolicy);
        control_trapeze_spd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_trapeze_spd, 12, 4, 1, 1);

        label_65 = new QLabel(gridLayoutWidget_7);
        label_65->setObjectName(QStringLiteral("label_65"));

        gridLayout_8->addWidget(label_65, 12, 3, 1, 1);

        label_59 = new QLabel(gridLayoutWidget_7);
        label_59->setObjectName(QStringLiteral("label_59"));

        gridLayout_8->addWidget(label_59, 18, 0, 1, 1);

        textLabel_Gains_2 = new QLabel(gridLayoutWidget_7);
        textLabel_Gains_2->setObjectName(QStringLiteral("textLabel_Gains_2"));

        gridLayout_8->addWidget(textLabel_Gains_2, 2, 2, 1, 2);

        label_62 = new QLabel(gridLayoutWidget_7);
        label_62->setObjectName(QStringLiteral("label_62"));

        gridLayout_8->addWidget(label_62, 15, 0, 1, 1);

        control_toggle_delayB = new QLineEdit(gridLayoutWidget_7);
        control_toggle_delayB->setObjectName(QStringLiteral("control_toggle_delayB"));
        sizePolicy.setHeightForWidth(control_toggle_delayB->sizePolicy().hasHeightForWidth());
        control_toggle_delayB->setSizePolicy(sizePolicy);
        control_toggle_delayB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_toggle_delayB, 15, 1, 1, 1);

        control_g3 = new QLineEdit(gridLayoutWidget_7);
        control_g3->setObjectName(QStringLiteral("control_g3"));
        sizePolicy.setHeightForWidth(control_g3->sizePolicy().hasHeightForWidth());
        control_g3->setSizePolicy(sizePolicy);
        control_g3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_g3, 7, 1, 1, 1);

        control_slider_max = new QLineEdit(gridLayoutWidget_7);
        control_slider_max->setObjectName(QStringLiteral("control_slider_max"));
        sizePolicy.setHeightForWidth(control_slider_max->sizePolicy().hasHeightForWidth());
        control_slider_max->setSizePolicy(sizePolicy);
        control_slider_max->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_slider_max, 19, 1, 1, 1);

        control_setp_b = new QLineEdit(gridLayoutWidget_7);
        control_setp_b->setObjectName(QStringLiteral("control_setp_b"));
        sizePolicy.setHeightForWidth(control_setp_b->sizePolicy().hasHeightForWidth());
        control_setp_b->setSizePolicy(sizePolicy);
        control_setp_b->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_setp_b, 13, 1, 1, 1);

        pushButton_SetGains = new QPushButton(gridLayoutWidget_7);
        pushButton_SetGains->setObjectName(QStringLiteral("pushButton_SetGains"));

        gridLayout_8->addWidget(pushButton_SetGains, 9, 2, 1, 1);

        label_60 = new QLabel(gridLayoutWidget_7);
        label_60->setObjectName(QStringLiteral("label_60"));

        gridLayout_8->addWidget(label_60, 19, 0, 1, 1);

        hSlider_Ctrl = new QSlider(gridLayoutWidget_7);
        hSlider_Ctrl->setObjectName(QStringLiteral("hSlider_Ctrl"));
        hSlider_Ctrl->setMinimum(55);
        hSlider_Ctrl->setMaximum(155);
        hSlider_Ctrl->setOrientation(Qt::Horizontal);

        gridLayout_8->addWidget(hSlider_Ctrl, 20, 0, 1, 2);

        control_g2 = new QLineEdit(gridLayoutWidget_7);
        control_g2->setObjectName(QStringLiteral("control_g2"));
        sizePolicy.setHeightForWidth(control_g2->sizePolicy().hasHeightForWidth());
        control_g2->setSizePolicy(sizePolicy);
        control_g2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_g2, 6, 1, 1, 1);

        control_g5 = new QLineEdit(gridLayoutWidget_7);
        control_g5->setObjectName(QStringLiteral("control_g5"));
        sizePolicy.setHeightForWidth(control_g5->sizePolicy().hasHeightForWidth());
        control_g5->setSizePolicy(sizePolicy);
        control_g5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_g5, 9, 1, 1, 1);

        pushButton_CtrlMinMax = new QPushButton(gridLayoutWidget_7);
        pushButton_CtrlMinMax->setObjectName(QStringLiteral("pushButton_CtrlMinMax"));

        gridLayout_8->addWidget(pushButton_CtrlMinMax, 19, 2, 1, 1);

        disp_active_controller = new QLabel(gridLayoutWidget_7);
        disp_active_controller->setObjectName(QStringLiteral("disp_active_controller"));
        disp_active_controller->setAutoFillBackground(false);
        disp_active_controller->setFrameShape(QFrame::Box);
        disp_active_controller->setFrameShadow(QFrame::Raised);
        disp_active_controller->setLineWidth(1);
        disp_active_controller->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(disp_active_controller, 2, 1, 1, 1);

        label_51 = new QLabel(gridLayoutWidget_7);
        label_51->setObjectName(QStringLiteral("label_51"));

        gridLayout_8->addWidget(label_51, 7, 0, 1, 1);

        label_47 = new QLabel(gridLayoutWidget_7);
        label_47->setObjectName(QStringLiteral("label_47"));

        gridLayout_8->addWidget(label_47, 3, 0, 1, 1);

        label_56 = new QLabel(gridLayoutWidget_7);
        label_56->setObjectName(QStringLiteral("label_56"));

        gridLayout_8->addWidget(label_56, 13, 0, 1, 1);

        label_53 = new QLabel(gridLayoutWidget_7);
        label_53->setObjectName(QStringLiteral("label_53"));

        gridLayout_8->addWidget(label_53, 9, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_2, 22, 2, 1, 1);

        label_48 = new QLabel(gridLayoutWidget_7);
        label_48->setObjectName(QStringLiteral("label_48"));

        gridLayout_8->addWidget(label_48, 4, 0, 1, 1);

        label_58 = new QLabel(gridLayoutWidget_7);
        label_58->setObjectName(QStringLiteral("label_58"));

        gridLayout_8->addWidget(label_58, 17, 0, 1, 2);

        label_49 = new QLabel(gridLayoutWidget_7);
        label_49->setObjectName(QStringLiteral("label_49"));

        gridLayout_8->addWidget(label_49, 5, 0, 1, 1);

        control_g4 = new QLineEdit(gridLayoutWidget_7);
        control_g4->setObjectName(QStringLiteral("control_g4"));
        sizePolicy.setHeightForWidth(control_g4->sizePolicy().hasHeightForWidth());
        control_g4->setSizePolicy(sizePolicy);
        control_g4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_g4, 8, 1, 1, 1);

        label_52 = new QLabel(gridLayoutWidget_7);
        label_52->setObjectName(QStringLiteral("label_52"));

        gridLayout_8->addWidget(label_52, 8, 0, 1, 1);

        label_46 = new QLabel(gridLayoutWidget_7);
        label_46->setObjectName(QStringLiteral("label_46"));

        gridLayout_8->addWidget(label_46, 0, 0, 1, 1);

        control_setp_a = new QLineEdit(gridLayoutWidget_7);
        control_setp_a->setObjectName(QStringLiteral("control_setp_a"));
        sizePolicy.setHeightForWidth(control_setp_a->sizePolicy().hasHeightForWidth());
        control_setp_a->setSizePolicy(sizePolicy);
        control_setp_a->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_setp_a, 12, 1, 1, 1);

        comboBox_ctrl_list = new QComboBox(gridLayoutWidget_7);
        comboBox_ctrl_list->setObjectName(QStringLiteral("comboBox_ctrl_list"));

        gridLayout_8->addWidget(comboBox_ctrl_list, 1, 0, 1, 1);

        label_54 = new QLabel(gridLayoutWidget_7);
        label_54->setObjectName(QStringLiteral("label_54"));

        gridLayout_8->addWidget(label_54, 11, 0, 1, 2);

        control_g1 = new QLineEdit(gridLayoutWidget_7);
        control_g1->setObjectName(QStringLiteral("control_g1"));
        sizePolicy.setHeightForWidth(control_g1->sizePolicy().hasHeightForWidth());
        control_g1->setSizePolicy(sizePolicy);
        control_g1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_g1, 5, 1, 1, 1);

        disp_slider = new QLabel(gridLayoutWidget_7);
        disp_slider->setObjectName(QStringLiteral("disp_slider"));
        disp_slider->setAutoFillBackground(false);
        disp_slider->setFrameShape(QFrame::Box);
        disp_slider->setFrameShadow(QFrame::Raised);
        disp_slider->setLineWidth(1);
        disp_slider->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(disp_slider, 20, 2, 1, 1);

        pushButton_setp_a_go = new QPushButton(gridLayoutWidget_7);
        pushButton_setp_a_go->setObjectName(QStringLiteral("pushButton_setp_a_go"));

        gridLayout_8->addWidget(pushButton_setp_a_go, 12, 2, 1, 1);

        label_50 = new QLabel(gridLayoutWidget_7);
        label_50->setObjectName(QStringLiteral("label_50"));

        gridLayout_8->addWidget(label_50, 6, 0, 1, 1);

        label_55 = new QLabel(gridLayoutWidget_7);
        label_55->setObjectName(QStringLiteral("label_55"));

        gridLayout_8->addWidget(label_55, 12, 0, 1, 1);

        label_45 = new QLabel(gridLayoutWidget_7);
        label_45->setObjectName(QStringLiteral("label_45"));

        gridLayout_8->addWidget(label_45, 2, 0, 1, 1);

        pushButton_setp_b_go = new QPushButton(gridLayoutWidget_7);
        pushButton_setp_b_go->setObjectName(QStringLiteral("pushButton_setp_b_go"));

        gridLayout_8->addWidget(pushButton_setp_b_go, 13, 2, 1, 1);

        control_g0 = new QLineEdit(gridLayoutWidget_7);
        control_g0->setObjectName(QStringLiteral("control_g0"));
        sizePolicy.setHeightForWidth(control_g0->sizePolicy().hasHeightForWidth());
        control_g0->setSizePolicy(sizePolicy);
        control_g0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_g0, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer, 22, 0, 1, 1);

        pushButton_SetController = new QPushButton(gridLayoutWidget_7);
        pushButton_SetController->setObjectName(QStringLiteral("pushButton_SetController"));

        gridLayout_8->addWidget(pushButton_SetController, 1, 2, 1, 1);

        control_slider_min = new QLineEdit(gridLayoutWidget_7);
        control_slider_min->setObjectName(QStringLiteral("control_slider_min"));
        sizePolicy.setHeightForWidth(control_slider_min->sizePolicy().hasHeightForWidth());
        control_slider_min->setSizePolicy(sizePolicy);
        control_slider_min->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_slider_min, 18, 1, 1, 1);

        label_61 = new QLabel(gridLayoutWidget_7);
        label_61->setObjectName(QStringLiteral("label_61"));

        gridLayout_8->addWidget(label_61, 14, 0, 1, 1);

        pushButton_toggle = new QPushButton(gridLayoutWidget_7);
        pushButton_toggle->setObjectName(QStringLiteral("pushButton_toggle"));

        gridLayout_8->addWidget(pushButton_toggle, 15, 2, 1, 1);

        control_toggle_delayA = new QLineEdit(gridLayoutWidget_7);
        control_toggle_delayA->setObjectName(QStringLiteral("control_toggle_delayA"));
        sizePolicy.setHeightForWidth(control_toggle_delayA->sizePolicy().hasHeightForWidth());
        control_toggle_delayA->setSizePolicy(sizePolicy);
        control_toggle_delayA->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_toggle_delayA, 14, 1, 1, 1);

        label_57 = new QLabel(gridLayoutWidget_7);
        label_57->setObjectName(QStringLiteral("label_57"));

        gridLayout_8->addWidget(label_57, 21, 0, 1, 1);

        disp_meas_val = new QLabel(gridLayoutWidget_7);
        disp_meas_val->setObjectName(QStringLiteral("disp_meas_val"));
        disp_meas_val->setAutoFillBackground(false);
        disp_meas_val->setFrameShape(QFrame::Box);
        disp_meas_val->setFrameShadow(QFrame::Raised);
        disp_meas_val->setLineWidth(1);
        disp_meas_val->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(disp_meas_val, 21, 1, 1, 1);

        control_trapeze_acc = new QLineEdit(gridLayoutWidget_7);
        control_trapeze_acc->setObjectName(QStringLiteral("control_trapeze_acc"));
        sizePolicy.setHeightForWidth(control_trapeze_acc->sizePolicy().hasHeightForWidth());
        control_trapeze_acc->setSizePolicy(sizePolicy);
        control_trapeze_acc->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(control_trapeze_acc, 13, 4, 1, 1);

        textLabel_Gains_i = new QLabel(gridLayoutWidget_7);
        textLabel_Gains_i->setObjectName(QStringLiteral("textLabel_Gains_i"));

        gridLayout_8->addWidget(textLabel_Gains_i, 4, 3, 1, 2);

        textLabel_Gains_p = new QLabel(gridLayoutWidget_7);
        textLabel_Gains_p->setObjectName(QStringLiteral("textLabel_Gains_p"));

        gridLayout_8->addWidget(textLabel_Gains_p, 5, 3, 1, 2);

        textLabel_Gains_z = new QLabel(gridLayoutWidget_7);
        textLabel_Gains_z->setObjectName(QStringLiteral("textLabel_Gains_z"));

        gridLayout_8->addWidget(textLabel_Gains_z, 6, 3, 1, 2);

        tabWidget->addTab(control, QString());
        in_control = new QWidget();
        in_control->setObjectName(QStringLiteral("in_control"));
        gridLayoutWidget_6 = new QWidget(in_control);
        gridLayoutWidget_6->setObjectName(QStringLiteral("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(9, 9, 601, 621));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        label_109 = new QLabel(gridLayoutWidget_6);
        label_109->setObjectName(QStringLiteral("label_109"));

        gridLayout_6->addWidget(label_109, 0, 0, 1, 1);

        disp_inctrl_current_d = new QLabel(gridLayoutWidget_6);
        disp_inctrl_current_d->setObjectName(QStringLiteral("disp_inctrl_current_d"));
        disp_inctrl_current_d->setAutoFillBackground(false);
        disp_inctrl_current_d->setFrameShape(QFrame::Box);
        disp_inctrl_current_d->setFrameShadow(QFrame::Raised);
        disp_inctrl_current_d->setLineWidth(1);
        disp_inctrl_current_d->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_current_d, 8, 2, 1, 1);

        label_26 = new QLabel(gridLayoutWidget_6);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setLayoutDirection(Qt::LeftToRight);
        label_26->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_26, 8, 0, 1, 1);

        disp_inctrl_current = new QLabel(gridLayoutWidget_6);
        disp_inctrl_current->setObjectName(QStringLiteral("disp_inctrl_current"));
        disp_inctrl_current->setAutoFillBackground(false);
        disp_inctrl_current->setFrameShape(QFrame::Box);
        disp_inctrl_current->setFrameShadow(QFrame::Raised);
        disp_inctrl_current->setLineWidth(1);
        disp_inctrl_current->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_current, 8, 1, 1, 1);

        label_117 = new QLabel(gridLayoutWidget_6);
        label_117->setObjectName(QStringLiteral("label_117"));
        label_117->setLayoutDirection(Qt::LeftToRight);
        label_117->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_117, 10, 0, 1, 1);

        label_113 = new QLabel(gridLayoutWidget_6);
        label_113->setObjectName(QStringLiteral("label_113"));
        label_113->setLayoutDirection(Qt::LeftToRight);
        label_113->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_113, 6, 0, 1, 1);

        label_19 = new QLabel(gridLayoutWidget_6);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_6->addWidget(label_19, 8, 3, 1, 1);

        label_27 = new QLabel(gridLayoutWidget_6);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setLayoutDirection(Qt::LeftToRight);
        label_27->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_27, 1, 0, 1, 1);

        label_111 = new QLabel(gridLayoutWidget_6);
        label_111->setObjectName(QStringLiteral("label_111"));
        label_111->setLayoutDirection(Qt::LeftToRight);
        label_111->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_111, 3, 0, 1, 1);

        label_115 = new QLabel(gridLayoutWidget_6);
        label_115->setObjectName(QStringLiteral("label_115"));
        label_115->setLayoutDirection(Qt::LeftToRight);
        label_115->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_115, 5, 0, 1, 1);

        label_114 = new QLabel(gridLayoutWidget_6);
        label_114->setObjectName(QStringLiteral("label_114"));
        label_114->setLayoutDirection(Qt::LeftToRight);
        label_114->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_114, 7, 0, 1, 1);

        label_112 = new QLabel(gridLayoutWidget_6);
        label_112->setObjectName(QStringLiteral("label_112"));
        label_112->setLayoutDirection(Qt::LeftToRight);
        label_112->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_112, 4, 0, 1, 1);

        label_110 = new QLabel(gridLayoutWidget_6);
        label_110->setObjectName(QStringLiteral("label_110"));
        label_110->setLayoutDirection(Qt::LeftToRight);
        label_110->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_110, 2, 0, 1, 1);

        label_116 = new QLabel(gridLayoutWidget_6);
        label_116->setObjectName(QStringLiteral("label_116"));

        gridLayout_6->addWidget(label_116, 9, 0, 1, 1);

        label_118 = new QLabel(gridLayoutWidget_6);
        label_118->setObjectName(QStringLiteral("label_118"));
        label_118->setLayoutDirection(Qt::LeftToRight);
        label_118->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_118, 11, 0, 1, 1);

        disp_inctrl_active_controller = new QLabel(gridLayoutWidget_6);
        disp_inctrl_active_controller->setObjectName(QStringLiteral("disp_inctrl_active_controller"));
        disp_inctrl_active_controller->setAutoFillBackground(false);
        disp_inctrl_active_controller->setFrameShape(QFrame::Box);
        disp_inctrl_active_controller->setFrameShadow(QFrame::Raised);
        disp_inctrl_active_controller->setLineWidth(1);
        disp_inctrl_active_controller->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_active_controller, 1, 1, 1, 1);

        disp_inctrl_setp = new QLabel(gridLayoutWidget_6);
        disp_inctrl_setp->setObjectName(QStringLiteral("disp_inctrl_setp"));
        disp_inctrl_setp->setAutoFillBackground(false);
        disp_inctrl_setp->setFrameShape(QFrame::Box);
        disp_inctrl_setp->setFrameShadow(QFrame::Raised);
        disp_inctrl_setp->setLineWidth(1);
        disp_inctrl_setp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_setp, 2, 1, 1, 1);

        disp_inctrl_actual_val = new QLabel(gridLayoutWidget_6);
        disp_inctrl_actual_val->setObjectName(QStringLiteral("disp_inctrl_actual_val"));
        disp_inctrl_actual_val->setAutoFillBackground(false);
        disp_inctrl_actual_val->setFrameShape(QFrame::Box);
        disp_inctrl_actual_val->setFrameShadow(QFrame::Raised);
        disp_inctrl_actual_val->setLineWidth(1);
        disp_inctrl_actual_val->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_actual_val, 3, 1, 1, 1);

        disp_inctrl_error = new QLabel(gridLayoutWidget_6);
        disp_inctrl_error->setObjectName(QStringLiteral("disp_inctrl_error"));
        disp_inctrl_error->setAutoFillBackground(false);
        disp_inctrl_error->setFrameShape(QFrame::Box);
        disp_inctrl_error->setFrameShadow(QFrame::Raised);
        disp_inctrl_error->setLineWidth(1);
        disp_inctrl_error->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_error, 4, 1, 1, 1);

        disp_inctrl_output = new QLabel(gridLayoutWidget_6);
        disp_inctrl_output->setObjectName(QStringLiteral("disp_inctrl_output"));
        disp_inctrl_output->setAutoFillBackground(false);
        disp_inctrl_output->setFrameShape(QFrame::Box);
        disp_inctrl_output->setFrameShadow(QFrame::Raised);
        disp_inctrl_output->setLineWidth(1);
        disp_inctrl_output->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_output, 5, 1, 1, 1);

        disp_inctrl_dir = new QLabel(gridLayoutWidget_6);
        disp_inctrl_dir->setObjectName(QStringLiteral("disp_inctrl_dir"));
        disp_inctrl_dir->setAutoFillBackground(false);
        disp_inctrl_dir->setFrameShape(QFrame::Box);
        disp_inctrl_dir->setFrameShadow(QFrame::Raised);
        disp_inctrl_dir->setLineWidth(1);
        disp_inctrl_dir->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_dir, 7, 1, 1, 1);

        disp_inctrl_1 = new QLabel(gridLayoutWidget_6);
        disp_inctrl_1->setObjectName(QStringLiteral("disp_inctrl_1"));
        disp_inctrl_1->setAutoFillBackground(false);
        disp_inctrl_1->setFrameShape(QFrame::Box);
        disp_inctrl_1->setFrameShadow(QFrame::Raised);
        disp_inctrl_1->setLineWidth(1);
        disp_inctrl_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_1, 11, 1, 1, 1);

        disp_inctrl_pwm = new QLabel(gridLayoutWidget_6);
        disp_inctrl_pwm->setObjectName(QStringLiteral("disp_inctrl_pwm"));
        disp_inctrl_pwm->setAutoFillBackground(false);
        disp_inctrl_pwm->setFrameShape(QFrame::Box);
        disp_inctrl_pwm->setFrameShadow(QFrame::Raised);
        disp_inctrl_pwm->setLineWidth(1);
        disp_inctrl_pwm->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_pwm, 6, 1, 1, 1);

        disp_inctrl_0 = new QLabel(gridLayoutWidget_6);
        disp_inctrl_0->setObjectName(QStringLiteral("disp_inctrl_0"));
        disp_inctrl_0->setAutoFillBackground(false);
        disp_inctrl_0->setFrameShape(QFrame::Box);
        disp_inctrl_0->setFrameShadow(QFrame::Raised);
        disp_inctrl_0->setLineWidth(1);
        disp_inctrl_0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(disp_inctrl_0, 10, 1, 1, 1);

        label_124 = new QLabel(gridLayoutWidget_6);
        label_124->setObjectName(QStringLiteral("label_124"));
        label_124->setLayoutDirection(Qt::LeftToRight);
        label_124->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_124, 12, 0, 1, 1);

        label_123 = new QLabel(gridLayoutWidget_6);
        label_123->setObjectName(QStringLiteral("label_123"));
        label_123->setLayoutDirection(Qt::LeftToRight);
        label_123->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_123, 14, 0, 1, 1);

        label_122 = new QLabel(gridLayoutWidget_6);
        label_122->setObjectName(QStringLiteral("label_122"));
        label_122->setLayoutDirection(Qt::LeftToRight);
        label_122->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_122, 13, 0, 1, 1);

        label_125 = new QLabel(gridLayoutWidget_6);
        label_125->setObjectName(QStringLiteral("label_125"));
        label_125->setLayoutDirection(Qt::LeftToRight);
        label_125->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_125, 15, 0, 1, 1);

        inctrl_w0 = new QLineEdit(gridLayoutWidget_6);
        inctrl_w0->setObjectName(QStringLiteral("inctrl_w0"));
        sizePolicy.setHeightForWidth(inctrl_w0->sizePolicy().hasHeightForWidth());
        inctrl_w0->setSizePolicy(sizePolicy);
        inctrl_w0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(inctrl_w0, 12, 1, 1, 1);

        inctrl_w1 = new QLineEdit(gridLayoutWidget_6);
        inctrl_w1->setObjectName(QStringLiteral("inctrl_w1"));
        sizePolicy.setHeightForWidth(inctrl_w1->sizePolicy().hasHeightForWidth());
        inctrl_w1->setSizePolicy(sizePolicy);
        inctrl_w1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(inctrl_w1, 13, 1, 1, 1);

        inctrl_w2 = new QLineEdit(gridLayoutWidget_6);
        inctrl_w2->setObjectName(QStringLiteral("inctrl_w2"));
        sizePolicy.setHeightForWidth(inctrl_w2->sizePolicy().hasHeightForWidth());
        inctrl_w2->setSizePolicy(sizePolicy);
        inctrl_w2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(inctrl_w2, 14, 1, 1, 1);

        inctrl_w3 = new QLineEdit(gridLayoutWidget_6);
        inctrl_w3->setObjectName(QStringLiteral("inctrl_w3"));
        sizePolicy.setHeightForWidth(inctrl_w3->sizePolicy().hasHeightForWidth());
        inctrl_w3->setSizePolicy(sizePolicy);
        inctrl_w3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(inctrl_w3, 15, 1, 1, 1);

        pushButton_inctrl_w0 = new QPushButton(gridLayoutWidget_6);
        pushButton_inctrl_w0->setObjectName(QStringLiteral("pushButton_inctrl_w0"));

        gridLayout_6->addWidget(pushButton_inctrl_w0, 12, 2, 1, 1);

        pushButton_inctrl_w1 = new QPushButton(gridLayoutWidget_6);
        pushButton_inctrl_w1->setObjectName(QStringLiteral("pushButton_inctrl_w1"));

        gridLayout_6->addWidget(pushButton_inctrl_w1, 13, 2, 1, 1);

        pushButton_inctrl_w2 = new QPushButton(gridLayoutWidget_6);
        pushButton_inctrl_w2->setObjectName(QStringLiteral("pushButton_inctrl_w2"));

        gridLayout_6->addWidget(pushButton_inctrl_w2, 14, 2, 1, 1);

        pushButton_inctrl_w3 = new QPushButton(gridLayoutWidget_6);
        pushButton_inctrl_w3->setObjectName(QStringLiteral("pushButton_inctrl_w3"));

        gridLayout_6->addWidget(pushButton_inctrl_w3, 15, 2, 1, 1);

        tabWidget->addTab(in_control, QString());
        external = new QWidget();
        external->setObjectName(QStringLiteral("external"));
        gridLayoutWidget_8 = new QWidget(external);
        gridLayoutWidget_8->setObjectName(QStringLiteral("gridLayoutWidget_8"));
        gridLayoutWidget_8->setGeometry(QRect(9, 9, 396, 174));
        gridLayout_9 = new QGridLayout(gridLayoutWidget_8);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        ext_pwro_pwm = new QLineEdit(gridLayoutWidget_8);
        ext_pwro_pwm->setObjectName(QStringLiteral("ext_pwro_pwm"));
        sizePolicy.setHeightForWidth(ext_pwro_pwm->sizePolicy().hasHeightForWidth());
        ext_pwro_pwm->setSizePolicy(sizePolicy);
        ext_pwro_pwm->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(ext_pwro_pwm, 1, 1, 1, 1);

        label_63 = new QLabel(gridLayoutWidget_8);
        label_63->setObjectName(QStringLiteral("label_63"));

        gridLayout_9->addWidget(label_63, 0, 0, 1, 1);

        label_64 = new QLabel(gridLayoutWidget_8);
        label_64->setObjectName(QStringLiteral("label_64"));

        gridLayout_9->addWidget(label_64, 1, 0, 1, 1);

        pushButton_ext_pwro = new QPushButton(gridLayoutWidget_8);
        pushButton_ext_pwro->setObjectName(QStringLiteral("pushButton_ext_pwro"));

        gridLayout_9->addWidget(pushButton_ext_pwro, 1, 2, 1, 1);

        label_71 = new QLabel(gridLayoutWidget_8);
        label_71->setObjectName(QStringLiteral("label_71"));

        gridLayout_9->addWidget(label_71, 2, 0, 1, 1);

        label_105 = new QLabel(gridLayoutWidget_8);
        label_105->setObjectName(QStringLiteral("label_105"));

        gridLayout_9->addWidget(label_105, 4, 0, 1, 1);

        label_72 = new QLabel(gridLayoutWidget_8);
        label_72->setObjectName(QStringLiteral("label_72"));

        gridLayout_9->addWidget(label_72, 3, 0, 1, 1);

        comboBox_minm_rgb = new QComboBox(gridLayoutWidget_8);
        comboBox_minm_rgb->setObjectName(QStringLiteral("comboBox_minm_rgb"));

        gridLayout_9->addWidget(comboBox_minm_rgb, 3, 1, 1, 1);

        quadrature_write = new QPushButton(gridLayoutWidget_8);
        quadrature_write->setObjectName(QStringLiteral("quadrature_write"));

        gridLayout_9->addWidget(quadrature_write, 5, 2, 1, 1);

        quad_write_val = new QLineEdit(gridLayoutWidget_8);
        quad_write_val->setObjectName(QStringLiteral("quad_write_val"));
        sizePolicy.setHeightForWidth(quad_write_val->sizePolicy().hasHeightForWidth());
        quad_write_val->setSizePolicy(sizePolicy);
        quad_write_val->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(quad_write_val, 5, 1, 1, 1);

        label_106 = new QLabel(gridLayoutWidget_8);
        label_106->setObjectName(QStringLiteral("label_106"));

        gridLayout_9->addWidget(label_106, 5, 0, 1, 1);

        tabWidget->addTab(external, QString());
        about = new QWidget();
        about->setObjectName(QStringLiteral("about"));
        textBrowser = new QTextBrowser(about);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(382, 244, 260, 140));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        text_last_build = new QLabel(about);
        text_last_build->setObjectName(QStringLiteral("text_last_build"));
        text_last_build->setGeometry(QRect(10, 650, 1001, 17));
        text_last_build->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        tabWidget->addTab(about, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 25));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(control_g0, control_g1);
        QWidget::setTabOrder(control_g1, control_g2);
        QWidget::setTabOrder(control_g2, control_g3);
        QWidget::setTabOrder(control_g3, control_g4);
        QWidget::setTabOrder(control_g4, control_g5);
        QWidget::setTabOrder(control_g5, updateRefreshButton);
        QWidget::setTabOrder(updateRefreshButton, comPortTxt);
        QWidget::setTabOrder(comPortTxt, logOFF_master_button);
        QWidget::setTabOrder(logOFF_master_button, logRefreshTxt);
        QWidget::setTabOrder(logRefreshTxt, logON_master_button);
        QWidget::setTabOrder(logON_master_button, logFileTxt);
        QWidget::setTabOrder(logFileTxt, streamON_master_button);
        QWidget::setTabOrder(streamON_master_button, streamRefreshTxt);
        QWidget::setTabOrder(streamRefreshTxt, horizontalSlider_current_zero);
        QWidget::setTabOrder(horizontalSlider_current_zero, stream_SA_RefreshOffset);
        QWidget::setTabOrder(stream_SA_RefreshOffset, strain_offs_ch1);
        QWidget::setTabOrder(strain_offs_ch1, strain_offs_ch2);
        QWidget::setTabOrder(strain_offs_ch2, strain_offs_ch3);
        QWidget::setTabOrder(strain_offs_ch3, strain_offs_ch4);
        QWidget::setTabOrder(strain_offs_ch4, strain_offs_ch5);
        QWidget::setTabOrder(strain_offs_ch5, strain_offs_ch6);
        QWidget::setTabOrder(strain_offs_ch6, horizontalSlider_current_zero_2);
        QWidget::setTabOrder(horizontalSlider_current_zero_2, plot_xmin_lineEdit);
        QWidget::setTabOrder(plot_xmin_lineEdit, radioButtonXManual);
        QWidget::setTabOrder(radioButtonXManual, plot_xmax_lineEdit);
        QWidget::setTabOrder(plot_xmax_lineEdit, radioButtonXAuto);
        QWidget::setTabOrder(radioButtonXAuto, UpdatePlotpushButton);
        QWidget::setTabOrder(UpdatePlotpushButton, radioButtonYManual);
        QWidget::setTabOrder(radioButtonYManual, plot_ymax_lineEdit);
        QWidget::setTabOrder(plot_ymax_lineEdit, radioButtonYAuto);
        QWidget::setTabOrder(radioButtonYAuto, plot_ymin_lineEdit);
        QWidget::setTabOrder(plot_ymin_lineEdit, cBoxvar1);
        QWidget::setTabOrder(cBoxvar1, cBoxvar4);
        QWidget::setTabOrder(cBoxvar4, cBoxvar6);
        QWidget::setTabOrder(cBoxvar6, cBoxvar5);
        QWidget::setTabOrder(cBoxvar5, cBoxvar2);
        QWidget::setTabOrder(cBoxvar2, cBoxvar3);
        QWidget::setTabOrder(cBoxvar3, control_trapeze_spd);
        QWidget::setTabOrder(control_trapeze_spd, control_toggle_delayB);
        QWidget::setTabOrder(control_toggle_delayB, closeComButton);
        QWidget::setTabOrder(closeComButton, control_slider_max);
        QWidget::setTabOrder(control_slider_max, control_setp_b);
        QWidget::setTabOrder(control_setp_b, pushButton_SetGains);
        QWidget::setTabOrder(pushButton_SetGains, hSlider_Ctrl);
        QWidget::setTabOrder(hSlider_Ctrl, streamOFF_master_button);
        QWidget::setTabOrder(streamOFF_master_button, SlaveSelectComboBox);
        QWidget::setTabOrder(SlaveSelectComboBox, pushButton_CtrlMinMax);
        QWidget::setTabOrder(pushButton_CtrlMinMax, StreamSelectComboBox);
        QWidget::setTabOrder(StreamSelectComboBox, control_setp_a);
        QWidget::setTabOrder(control_setp_a, comboBox_ctrl_list);
        QWidget::setTabOrder(comboBox_ctrl_list, openComButton);
        QWidget::setTabOrder(openComButton, pushButton_setp_a_go);
        QWidget::setTabOrder(pushButton_setp_a_go, pushButton_setp_b_go);
        QWidget::setTabOrder(pushButton_setp_b_go, tabWidget);
        QWidget::setTabOrder(tabWidget, pushButton_SetController);
        QWidget::setTabOrder(pushButton_SetController, control_slider_min);
        QWidget::setTabOrder(control_slider_min, pushButton_toggle);
        QWidget::setTabOrder(pushButton_toggle, control_toggle_delayA);
        QWidget::setTabOrder(control_toggle_delayA, control_trapeze_acc);
        QWidget::setTabOrder(control_trapeze_acc, ext_pwro_pwm);
        QWidget::setTabOrder(ext_pwro_pwm, pushButton_ext_pwro);
        QWidget::setTabOrder(pushButton_ext_pwro, comboBox_minm_rgb);
        QWidget::setTabOrder(comboBox_minm_rgb, quadrature_write);
        QWidget::setTabOrder(quadrature_write, quad_write_val);
        QWidget::setTabOrder(quad_write_val, textBrowser);

        retranslateUi(MainWindow);
        QObject::connect(hSlider_Ctrl, SIGNAL(valueChanged(int)), disp_slider, SLOT(setNum(int)));

        tabWidget->setCurrentIndex(8);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FlexSEA-Plan GUI v0.1", 0));
        comStatusTxt->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#797979;\">ComStatus</span></p></body></html>", 0));
        openComButton->setText(QApplication::translate("MainWindow", "Open COM", 0));
        streamOFF_master_button->setText(QApplication::translate("MainWindow", "Stream OFF", 0));
        stdelaytxt->setText(QApplication::translate("MainWindow", "Stream refresh rate:", 0));
        label_18->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Configuration:</span></p></body></html>", 0));
        closeComButton->setText(QApplication::translate("MainWindow", "Close COM", 0));
        StreamSelectComboBox->setCurrentText(QString());
        SlaveSelectComboBox->setCurrentText(QString());
        updateRefreshButton->setText(QApplication::translate("MainWindow", "Update Refresh", 0));
        stdelaytxt_2->setText(QApplication::translate("MainWindow", "Log refresh rate:", 0));
#ifndef QT_NO_TOOLTIP
        comPortTxt->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        comport_2->setText(QApplication::translate("MainWindow", "Slave:", 0));
        comport_3->setText(QApplication::translate("MainWindow", "Experiment:", 0));
        logOFF_master_button->setText(QApplication::translate("MainWindow", "Log OFF", 0));
        label_3->setText(QApplication::translate("MainWindow", "Log file:", 0));
#ifndef QT_NO_TOOLTIP
        logRefreshTxt->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        streamRefreshStatusTxt->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#797979;\">StreamStatus</span></p></body></html>", 0));
        comport->setText(QApplication::translate("MainWindow", "COM port:", 0));
        logON_master_button->setText(QApplication::translate("MainWindow", "Log ON", 0));
        streamON_master_button->setText(QApplication::translate("MainWindow", "Stream ON", 0));
        label_20->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Optional:</span></p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        streamRefreshTxt->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        logRefreshStatusTxt->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#797979;\">LogStatus</span></p></body></html>", 0));
        label_stream_status->setText(QApplication::translate("MainWindow", "S", 0));
        tabWidget->setTabText(tabWidget->indexOf(config), QApplication::translate("MainWindow", "Config", 0));
        label_21->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Raw</span></p></body></html>", 0));
        label_imu_g_x->setText(QApplication::translate("MainWindow", "degree/s", 0));
        label_imu_a_y->setText(QApplication::translate("MainWindow", "g", 0));
        label_39->setText(QApplication::translate("MainWindow", "+VB", 0));
        label_38->setText(QApplication::translate("MainWindow", "Voltage", 0));
        label_40->setText(QApplication::translate("MainWindow", "+VG", 0));
        label_44->setText(QApplication::translate("MainWindow", "\302\260C", 0));
        disp_gyroy_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_strain->setText(QApplication::translate("MainWindow", "<html><head/><body><p>\302\261100% of full scale</p></body></html>", 0));
        disp_temp_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_vg->setText(QApplication::translate("MainWindow", "Default", 0));
        label_imu_a_z->setText(QApplication::translate("MainWindow", "g", 0));
        label_imu_g_y->setText(QApplication::translate("MainWindow", "degree/s", 0));
        label_16->setText(QApplication::translate("MainWindow", "Byte #1", 0));
        label_37->setText(QApplication::translate("MainWindow", "V", 0));
        label_imu_g_z->setText(QApplication::translate("MainWindow", "degree/s", 0));
        disp_stat1->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_accy_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_29->setText(QApplication::translate("MainWindow", "[0]", 0));
        label_28->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Decoded</span></p></body></html>", 0));
        label_30->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Modifier</span></p></body></html>", 0));
        disp_strain_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_43->setText(QApplication::translate("MainWindow", "Temperature", 0));
        disp_gyroz_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_gyrox_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_vb->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_vb_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_vg_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_41->setText(QApplication::translate("MainWindow", "V", 0));
        label_8->setText(QApplication::translate("MainWindow", "X", 0));
        disp_accx_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_accz_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_temp->setText(QApplication::translate("MainWindow", "Default", 0));
        label_17->setText(QApplication::translate("MainWindow", "Byte #2", 0));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Accelerometer</p><p>(\302\2614g)</p></body></html>", 0));
        disp_accx->setText(QApplication::translate("MainWindow", "Default", 0));
        label_14->setText(QApplication::translate("MainWindow", "Encoder", 0));
        disp_accy->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_current->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_strain->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_ana->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_stat2->setText(QApplication::translate("MainWindow", "Default", 0));
        label_6->setText(QApplication::translate("MainWindow", "Z", 0));
        disp_enc->setText(QApplication::translate("MainWindow", "Default", 0));
        label_4->setText(QApplication::translate("MainWindow", "mA", 0));
        label_11->setText(QApplication::translate("MainWindow", "Strain", 0));
        label_13->setText(QApplication::translate("MainWindow", "Current", 0));
        disp_current_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_ana_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_accz->setText(QApplication::translate("MainWindow", "Default", 0));
        label_15->setText(QApplication::translate("MainWindow", "Status", 0));
        disp_gyrox->setText(QApplication::translate("MainWindow", "Default", 0));
        label_5->setText(QApplication::translate("MainWindow", "Y", 0));
        label_7->setText(QApplication::translate("MainWindow", "Z", 0));
        label_9->setText(QApplication::translate("MainWindow", "Y", 0));
        label_42->setText(QApplication::translate("MainWindow", "V", 0));
        label_imu_a_x->setText(QApplication::translate("MainWindow", "<html><head/><body><p>g</p></body></html>", 0));
        label_2->setText(QApplication::translate("MainWindow", "X", 0));
        disp_gyroy->setText(QApplication::translate("MainWindow", "Default", 0));
        label_10->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Gyroscope </p><p>(\302\2611000DPS)</p></body></html>", 0));
        disp_gyroz->setText(QApplication::translate("MainWindow", "Default", 0));
        label_107->setText(QApplication::translate("MainWindow", "[1]", 0));
        label_12->setText(QApplication::translate("MainWindow", "Analog", 0));
        disp_ana1->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_ana1_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_108->setText(QApplication::translate("MainWindow", "V", 0));
        label_status1->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Status1</p></body></html>", 0));
        label_status2->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Status2</p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(stream_ex), QApplication::translate("MainWindow", "Execute", 0));
        tabWidget->setTabText(tabWidget->indexOf(stream_manage), QApplication::translate("MainWindow", "Manage", 0));
        label_67->setText(QApplication::translate("MainWindow", "5", 0));
        label_32->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Raw</span></p></body></html>", 0));
        disp_strain_ch6->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_strain_ch1->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_strain_ch5_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_strain_ch6_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_33->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Channel</span></p></body></html>", 0));
        disp_strain_ch1_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_35->setText(QApplication::translate("MainWindow", "2", 0));
        label_68->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Offset</span></p></body></html>", 0));
        label_70->setText(QApplication::translate("MainWindow", "4", 0));
        disp_strain_ch5->setText(QApplication::translate("MainWindow", "Default", 0));
        label_36->setText(QApplication::translate("MainWindow", "3", 0));
        label_69->setText(QApplication::translate("MainWindow", "6", 0));
        label_31->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Decoded (\302\261100%)</span></p></body></html>", 0));
        label_34->setText(QApplication::translate("MainWindow", "1", 0));
        disp_strain_ch2->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_strain_ch3->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_strain_ch3_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_strain_ch2_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_strain_ch4_d->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_strain_ch4->setText(QApplication::translate("MainWindow", "Default", 0));
        stream_SA_RefreshOffset->setText(QApplication::translate("MainWindow", "Change Offset", 0));
        tabWidget->setTabText(tabWidget->indexOf(stream_strain), QApplication::translate("MainWindow", "Strain Amp", 0));
        label_84->setText(QApplication::translate("MainWindow", "Ch. 1", 0));
        label_imu_a_y_2->setText(QApplication::translate("MainWindow", "g", 0));
        label_93->setText(QApplication::translate("MainWindow", "Voltage", 0));
        label_imu_a_x_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p>g</p></body></html>", 0));
        label_74->setText(QApplication::translate("MainWindow", "mA", 0));
        ricnu_current_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_76->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Accelerometer</p><p>(\302\2614g)</p></body></html>", 0));
        label_imu_g_y_2->setText(QApplication::translate("MainWindow", "degree/s", 0));
        label_81->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Gyroscope </p><p>(\302\2611000DPS)</p></body></html>", 0));
        label_80->setText(QApplication::translate("MainWindow", "X", 0));
        label_82->setText(QApplication::translate("MainWindow", "X", 0));
        label_83->setText(QApplication::translate("MainWindow", "Y", 0));
        label_85->setText(QApplication::translate("MainWindow", "Z", 0));
        label_87->setText(QApplication::translate("MainWindow", "Current", 0));
        label_89->setText(QApplication::translate("MainWindow", "Z", 0));
        label_88->setText(QApplication::translate("MainWindow", "Y", 0));
        ricnu_enc_mot->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_accx->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_accy->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_accz->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_enc_joint->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_gyrox->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_gyroy->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_current->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_gyroz->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_gyroz_d->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_accy_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_91->setText(QApplication::translate("MainWindow", "V", 0));
        ricnu_accx_d->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_gyrox_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_imu_g_x_2->setText(QApplication::translate("MainWindow", "degree/s", 0));
        label_imu_g_z_2->setText(QApplication::translate("MainWindow", "degree/s", 0));
        ricnu_accz_d->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_gyroy_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_92->setText(QApplication::translate("MainWindow", "+VB", 0));
        label_imu_a_z_2->setText(QApplication::translate("MainWindow", "g", 0));
        label_94->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Raw</span></p></body></html>", 0));
        ricnu_vb->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_vb_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_99->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Decoded</span></p></body></html>", 0));
        label_100->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">Modifier</span></p></body></html>", 0));
        label_95->setText(QApplication::translate("MainWindow", "Motor (AS5047)", 0));
        label_96->setText(QApplication::translate("MainWindow", "Joint (AS5048B)", 0));
        label_78->setText(QApplication::translate("MainWindow", "Encoders", 0));
        label_77->setText(QApplication::translate("MainWindow", "Ch. 4", 0));
        label_75->setText(QApplication::translate("MainWindow", "Ch. 2", 0));
        label_86->setText(QApplication::translate("MainWindow", "Ch. 3", 0));
        label_79->setText(QApplication::translate("MainWindow", "Ch. 5", 0));
        label_73->setText(QApplication::translate("MainWindow", "Ch. 6", 0));
        ricnu_strain_ch1->setText(QApplication::translate("MainWindow", "Default", 0));
        label_97->setText(QApplication::translate("MainWindow", "Strain", 0));
        ricnu_strain_ch1_d->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_strain_ch2->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_strain_ch2_d->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_strain_ch3->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_strain_ch4->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_strain_ch3_d->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_strain_ch4_d->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_strain_ch5->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_strain_ch6_d->setText(QApplication::translate("MainWindow", "Default", 0));
        ricnu_strain_ch5_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_90->setText(QApplication::translate("MainWindow", "\302\261100%", 0));
        ricnu_strain_ch6->setText(QApplication::translate("MainWindow", "Default", 0));
        label_98->setText(QApplication::translate("MainWindow", "\302\261100%", 0));
        label_101->setText(QApplication::translate("MainWindow", "\302\261100%", 0));
        label_102->setText(QApplication::translate("MainWindow", "\302\261100%", 0));
        label_103->setText(QApplication::translate("MainWindow", "\302\261100%", 0));
        label_104->setText(QApplication::translate("MainWindow", "\302\261100%", 0));
        tabWidget->setTabText(tabWidget->indexOf(stream_ricnu), QApplication::translate("MainWindow", "RIC/NU Knee", 0));
        groupBoxXaxisLim->setTitle(QApplication::translate("MainWindow", "X Axis Limits:", 0));
        radioButtonXManual->setText(QApplication::translate("MainWindow", "Manual", 0));
        label_22->setText(QApplication::translate("MainWindow", "Min:", 0));
        radioButtonXAuto->setText(QApplication::translate("MainWindow", "Automatic", 0));
        label_23->setText(QApplication::translate("MainWindow", "Max:", 0));
        UpdatePlotpushButton->setText(QApplication::translate("MainWindow", "Update Manual XY", 0));
        groupBoxYaxisLim->setTitle(QApplication::translate("MainWindow", "Y Axis Limits:", 0));
        radioButtonYManual->setText(QApplication::translate("MainWindow", "Manual", 0));
        radioButtonYAuto->setText(QApplication::translate("MainWindow", "Automatic", 0));
        label_24->setText(QApplication::translate("MainWindow", "Min:", 0));
        label_25->setText(QApplication::translate("MainWindow", "Max:", 0));
        label_t1->setText(QApplication::translate("MainWindow", "1", 0));
        label_t2->setText(QApplication::translate("MainWindow", "2", 0));
        label_t3->setText(QApplication::translate("MainWindow", "3", 0));
        label_t4->setText(QApplication::translate("MainWindow", "4", 0));
        label_t5->setText(QApplication::translate("MainWindow", "5", 0));
        label_t6->setText(QApplication::translate("MainWindow", "6", 0));
        tabWidget->setTabText(tabWidget->indexOf(plot), QApplication::translate("MainWindow", "Plot", 0));
        tabWidget->setTabText(tabWidget->indexOf(exp), QApplication::translate("MainWindow", "Experiments", 0));
        label_66->setText(QApplication::translate("MainWindow", "Acceleration:", 0));
        label_65->setText(QApplication::translate("MainWindow", "Speed:", 0));
        label_59->setText(QApplication::translate("MainWindow", "Min:", 0));
        textLabel_Gains_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic;\">(Value returned from Execute, ToDo)</span></p></body></html>", 0));
        label_62->setText(QApplication::translate("MainWindow", "Time B (ms):", 0));
        pushButton_SetGains->setText(QApplication::translate("MainWindow", "Set Gains", 0));
        label_60->setText(QApplication::translate("MainWindow", "Max:", 0));
        pushButton_CtrlMinMax->setText(QApplication::translate("MainWindow", "Update Min-Max", 0));
        disp_active_controller->setText(QApplication::translate("MainWindow", "Default", 0));
        label_51->setText(QApplication::translate("MainWindow", "Gain 3:", 0));
        label_47->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Gains:</span></p></body></html>", 0));
        label_56->setText(QApplication::translate("MainWindow", "Setpoint B:", 0));
        label_53->setText(QApplication::translate("MainWindow", "Gain 5:", 0));
        label_48->setText(QApplication::translate("MainWindow", "Gain 0 (kp/K/...):", 0));
        label_58->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Setpoint - manual slider:</span></p></body></html>", 0));
        label_49->setText(QApplication::translate("MainWindow", "Gain 1 (ki/B/...):", 0));
        label_52->setText(QApplication::translate("MainWindow", "Gain 4:", 0));
        label_46->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Controller:</span></p></body></html>", 0));
        label_54->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Setpoints - 2 values:</span></p></body></html>", 0));
        disp_slider->setText(QApplication::translate("MainWindow", "Default", 0));
        pushButton_setp_a_go->setText(QApplication::translate("MainWindow", "Go", 0));
        label_50->setText(QApplication::translate("MainWindow", "Gain 2 (kd/I/...):", 0));
        label_55->setText(QApplication::translate("MainWindow", "Setpoint A:", 0));
        label_45->setText(QApplication::translate("MainWindow", "Active controller:", 0));
        pushButton_setp_b_go->setText(QApplication::translate("MainWindow", "Go", 0));
        pushButton_SetController->setText(QApplication::translate("MainWindow", "Set Controller", 0));
        label_61->setText(QApplication::translate("MainWindow", "Time A (ms):", 0));
        pushButton_toggle->setText(QApplication::translate("MainWindow", "Toggle ON", 0));
        label_57->setText(QApplication::translate("MainWindow", "Measured:", 0));
        disp_meas_val->setText(QApplication::translate("MainWindow", "Default", 0));
        textLabel_Gains_i->setText(QApplication::translate("MainWindow", "Current gains", 0));
        textLabel_Gains_p->setText(QApplication::translate("MainWindow", "Current gains", 0));
        textLabel_Gains_z->setText(QApplication::translate("MainWindow", "Current gains", 0));
        tabWidget->setTabText(tabWidget->indexOf(control), QApplication::translate("MainWindow", "Control", 0));
        label_109->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Common:</span></p></body></html>", 0));
        disp_inctrl_current_d->setText(QApplication::translate("MainWindow", "Default", 0));
        label_26->setText(QApplication::translate("MainWindow", "Current", 0));
        disp_inctrl_current->setText(QApplication::translate("MainWindow", "Default", 0));
        label_117->setText(QApplication::translate("MainWindow", "in_control.r[0]:", 0));
        label_113->setText(QApplication::translate("MainWindow", "PWM:", 0));
        label_19->setText(QApplication::translate("MainWindow", "mA", 0));
        label_27->setText(QApplication::translate("MainWindow", "Selected controller:", 0));
        label_111->setText(QApplication::translate("MainWindow", "Actual value:", 0));
        label_115->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Controller output:</p></body></html>", 0));
        label_114->setText(QApplication::translate("MainWindow", "Motor direction:", 0));
        label_112->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Error:</p></body></html>", 0));
        label_110->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Setpoint:</p></body></html>", 0));
        label_116->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">User:</span></p></body></html>", 0));
        label_118->setText(QApplication::translate("MainWindow", "in_control.r[1]:", 0));
        disp_inctrl_active_controller->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_inctrl_setp->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_inctrl_actual_val->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_inctrl_error->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_inctrl_output->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_inctrl_dir->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_inctrl_1->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_inctrl_pwm->setText(QApplication::translate("MainWindow", "Default", 0));
        disp_inctrl_0->setText(QApplication::translate("MainWindow", "Default", 0));
        label_124->setText(QApplication::translate("MainWindow", "Iin_control.w[0]:", 0));
        label_123->setText(QApplication::translate("MainWindow", "in_control.w[2]:", 0));
        label_122->setText(QApplication::translate("MainWindow", "in_control.w[1]:", 0));
        label_125->setText(QApplication::translate("MainWindow", "in_control.w[3]:", 0));
        pushButton_inctrl_w0->setText(QApplication::translate("MainWindow", "Write", 0));
        pushButton_inctrl_w1->setText(QApplication::translate("MainWindow", "Write", 0));
        pushButton_inctrl_w2->setText(QApplication::translate("MainWindow", "Write", 0));
        pushButton_inctrl_w3->setText(QApplication::translate("MainWindow", "Write", 0));
        tabWidget->setTabText(tabWidget->indexOf(in_control), QApplication::translate("MainWindow", "In Control", 0));
        label_63->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Power Output:</span></p></body></html>", 0));
        label_64->setText(QApplication::translate("MainWindow", "PWM (0-255):", 0));
        pushButton_ext_pwro->setText(QApplication::translate("MainWindow", "ON (PWM)", 0));
        label_71->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">MinM RGB:</span></p></body></html>", 0));
        label_105->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Quadrature:</span></p></body></html>", 0));
        label_72->setText(QApplication::translate("MainWindow", "Color:", 0));
        quadrature_write->setText(QApplication::translate("MainWindow", "Write", 0));
        label_106->setText(QApplication::translate("MainWindow", "New value:", 0));
        tabWidget->setTabText(tabWidget->indexOf(external), QApplication::translate("MainWindow", "External", 0));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">FlexSEA-Execute 0.1</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">Advanced Motion Controller</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-"
                        "left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Jean-Francois Duval</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">jfduval@media.mit.edu</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">MIT Media Lab - Biomechatronics</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2016</p></body></html>", 0));
        text_last_build->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(about), QApplication::translate("MainWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
