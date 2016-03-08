//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// MainWindow: Qt GUI Main file
//****************************************************************************

//This is the principal GUI file. Each tab has it's own .cpp file.
//Naming convention: mw_tab_NAMEOFTAB.cpp

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QtSerialPort/QtSerialPort>
#include <string>
#include "qcustomplot.h"

//****************************************************************************
// Function(s)
//****************************************************************************

//MainWindow constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    

    //Default settings:
    //=================

    //System:
    ui->tabWidget->setCurrentIndex(0);  //Start at first tab

    //COM port:
    ui->comPortTxt->setText("/dev/ttyACM0");
    ui->comStatusTxt->setText("Type COM port and click 'Open COM'.");
    ui->closeComButton->setDisabled(1); //Will be enabled when COM is open

    //Stream/log:
    stream_status = 0;
    fake_data = 0;
    ui->streamONbutton->setDisabled(1);
    ui->streamOFFbutton->setDisabled(1);
    ui->openLogButton->setDisabled(1);
    ui->logFileTxt->setText("Not programmed... do not use yet.");
    ui->streamRefreshTxt->setText(QString::number(STREAM_DEFAULT_FREQ));
    ui->streamRefreshStatusTxt->setText("Default setting.");
    ui->logRefreshTxt->setText(QString::number(LOG_DEFAULT_FREQ));
    ui->logRefreshStatusTxt->setText("Default setting.");

    //Plot:
    plot_len = INIT_PLOT_LEN;
    plot_xmin = INIT_PLOT_XMIN;
    plot_xmax = INIT_PLOT_XMAX;
    plot_ymin = INIT_PLOT_YMIN;
    plot_ymax = INIT_PLOT_YMAX;
    ui->radioButtonXAuto->setChecked(1);
    ui->radioButtonXManual->setChecked(0);
    ui->radioButtonYAuto->setChecked(1);
    ui->radioButtonYManual->setChecked(0);
    ui->plot_xmin_lineEdit->setText(QString::number(plot_xmin));
    ui->plot_xmax_lineEdit->setText(QString::number(plot_xmax));
    ui->plot_ymin_lineEdit->setText(QString::number(plot_ymin));
    ui->plot_ymax_lineEdit->setText(QString::number(plot_ymax));
    makePlot();

    //Experiments:
    exp_pwm = 0;
    ui->disp_MotPWM->setText(QString::number(ui->hSlider_PWM->value()));

    //=================
    //Timers:
    //=================

    //Stream:
    timer_stream = new QTimer(this);
    connect(timer_stream, SIGNAL(timeout()), this, SLOT(timerStreamEvent()));
    timer_stream->start(TIM_FREQ_TO_P(STREAM_DEFAULT_FREQ));

    //Plot:
    timer_plot = new QTimer(this);
    connect(timer_plot, SIGNAL(timeout()), this, SLOT(timerPlotEvent()));
    timer_plot->start(TIM_FREQ_TO_P(PLOT_DEFAULT_FREQ));
}

//MainWindow destructor
MainWindow::~MainWindow()
{
    //Close Serial port and delete object:
    qDebug("Closing serial port...");
    CloseUSBSerialPort();

    qDebug("Closing main program...");
    delete ui;
}
