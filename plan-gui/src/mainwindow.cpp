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
//#include <QtSerialPort/QtSerialPort>
#include <QSerialPort>
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

    /*
    //Test code: TODO REMOVE
    uint8_t test_buf1[10] = {1,2,3,4,HEADER,5,6,7,8,9};
    uint8_t test_buf2[10] = {0,0,0,0,0,0,0,0,0,0};
    qDebug() << "test_buf1:";
    for(int i = 0; i < 10; i++)
    {
        qDebug() << test_buf1[i];
    }

    qDebug() << "test_buf2:";
    for(int i = 0; i < 10; i++)
    {
        qDebug() << test_buf2[i];
    }

    unwrap_buffer(test_buf1, test_buf2, 10);
    qDebug() << "test_buf1:";
    for(int i = 0; i < 10; i++)
    {
        qDebug() << test_buf1[i];
    }

    qDebug() << "test_buf2:";
    for(int i = 0; i < 10; i++)
    {
        qDebug() << test_buf2[i];
    }
    */

    //System:
    //=================

    ui->tabWidget->setCurrentIndex(0);  //Start at first tab

    //Config tabs:
    //=================

    init_tab_config();
    init_tab_plot_1();
    init_tab_exp();
    init_tab_ext();
    init_tab_about();
    init_tab_ctrl();
    init_tab_stream_in_ctrl();
    init_tab_stream_execute();
    init_tab_stream_strain();
    init_tab_stream_ricnu_knee();

    //=================
    //Timers:
    //=================

    //Stream:
    timer_stream = new QTimer(this);
    connect(timer_stream, SIGNAL(timeout()), this, SLOT(timerStreamEvent()));
    timer_stream->start(TIM_FREQ_TO_P(STREAM_DEFAULT_FREQ));

    //Log:
    timer_log = new QTimer(this);
    connect(timer_log, SIGNAL(timeout()), this, SLOT(timerLogEvent()));
    timer_log->start(TIM_FREQ_TO_P(LOG_DEFAULT_FREQ));

    //Plot:
    timer_plot = new QTimer(this);
    connect(timer_plot, SIGNAL(timeout()), this, SLOT(timerPlotEvent()));
    timer_plot->start(TIM_FREQ_TO_P(PLOT_DEFAULT_FREQ));

    //Control:
    timer_ctrl = new QTimer(this);
    connect(timer_ctrl, SIGNAL(timeout()), this, SLOT(timerCtrlEvent()));
}

//MainWindow destructor
MainWindow::~MainWindow()
{
    qDebug("Stopping any pending Stream, and 1s delay...");
    //Turn all Stream OFF
    stream_status = 0;
    stream_ricnu_status = 0;
    stream_sa_status = 0;
    sleep(1);

    //Close Serial port and delete object:
    qDebug("Closing serial port...");
    CloseUSBSerialPort();

    qDebug("Closing main program... Done!");
    delete ui;
}
