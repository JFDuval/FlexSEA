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
    QString str;

    ui->setupUi(this);    

    //Default settings:
    //=================

    //System:
    //=================
    ui->tabWidget->setCurrentIndex(0);  //Start at first tab

    //Config:
    //=================

    //Variable option lists:
    var_list_slaves << "Execute 1" << "Execute 2" << "Execute 3" << "Execute 4" << "Manage 1" << "Strain Amp 1";
    for(int index = 0; index < var_list_slaves.count(); index++)
    {
        ui->SlaveSelectComboBox->addItem(var_list_slaves.at(index));
    }
    //Lookup from list to actual slave number (FlexSEA convention):
    list_to_slave[0] = FLEXSEA_EXECUTE_1;
    list_to_slave[1] = FLEXSEA_EXECUTE_2;
    list_to_slave[2] = FLEXSEA_EXECUTE_3;
    list_to_slave[3] = FLEXSEA_EXECUTE_4;
    list_to_slave[4] = FLEXSEA_MANAGE_1;
    list_to_slave[5] = FLEXSEA_STRAIN_1;
    active_slave_1_index = ui->SlaveSelectComboBox->currentIndex();
    active_slave_1 = list_to_slave[active_slave_1_index];
    qDebug() << "Selected slave is" << var_list_slaves.at(active_slave_1_index);

    //COM port:
    //=================
    ui->comPortTxt->setText("/dev/ttyACM0");
    ui->comStatusTxt->setText("Type COM port and click 'Open COM'.");
    ui->closeComButton->setDisabled(1); //Will be enabled when COM is open

    //Stream/log:
    //=================
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

    ui->horizontalSlider_current_zero->setValue(0);

    //Plot:
    //=================
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
    for(int h = 0; h < VAR_NUM; h++)
    {
        data_to_plot[h] = 0;
    }
    gen_graph_xarray();
    init_yarrays();
    makePlot();
    //Variable option lists:
    QStringList var_list;
    var_list << "**Unused**" << "Accel X" << "Accel Y" << "Accel Z" << "Gyro X" << "Gyro Y" << "Gyro Z" << "Encoder" \
            << "Motor current" << "Analog[0]" << "Strain" << "+VB" << "+VG" << "Temperature" << "Fake Data" << "Setpoint" \
            << "Strain ch1" << "Strain ch2" << "Strain ch3" << "Strain ch4" << "Strain ch5" << "Strain ch6" \
            << "AS5047 (Mot.)" << "AS5048B (Joint)";
    for(int index = 0; index < var_list.count(); index++)
    {
        //All boxes have the same list:
        ui->cBoxvar1->addItem(var_list.at(index));
        ui->cBoxvar2->addItem(var_list.at(index));
        ui->cBoxvar3->addItem(var_list.at(index));
        ui->cBoxvar4->addItem(var_list.at(index));
        ui->cBoxvar5->addItem(var_list.at(index));
        ui->cBoxvar6->addItem(var_list.at(index));
    }
    //Color coded labels:
    ui->label_t1->setStyleSheet("QLabel { background-color: red; color: black;}");
    ui->label_t2->setStyleSheet("QLabel { background-color: magenta; color: black;}");
    ui->label_t3->setStyleSheet("QLabel { background-color: blue; color: white;}");
    ui->label_t4->setStyleSheet("QLabel { background-color: cyan; color: black;}");
    ui->label_t5->setStyleSheet("QLabel { background-color: lime; color: black;}");
    ui->label_t6->setStyleSheet("QLabel { background-color: black; color: white;}");

    //Experiments:
    //=================
    exp_pwm = 0;
    ui->disp_MotPWM->setText(QString::number(ui->hSlider_PWM->value()));
    ui->tabWidget->setTabEnabled(6, false); //Disabled for now

    //About:
    //=================
    str.sprintf("Last full build: %s %s.\n", __DATE__, __TIME__);
    ui->text_last_build->setText(str);
    ui->text_last_build->repaint();

    //Control:
    //=================

    //Setpoints:
    ui->control_slider_min->setText("0");
    ui->control_slider_max->setText("0");
    ui->hSlider_Ctrl->setMinimum(ui->control_slider_min->text().toInt());
    ui->hSlider_Ctrl->setMaximum(ui->control_slider_max->text().toInt());
    ui->control_setp_a->setText("0");
    ui->control_setp_b->setText("0");
    ui->control_toggle_delayA->setText("1000");
    ui->control_toggle_delayB->setText("1000");
    ui->control_trapeze_spd->setText("10000");
    ui->control_trapeze_acc->setText("10000");

    //Variable option lists:
    QStringList var_list_controllers;
    var_list_controllers << "**Null**" << "Open" << "Position" << "Current" << "Impedance" << "Other/custom";
    for(int index = 0; index < var_list_controllers.count(); index++)
    {
        ui->comboBox_ctrl_list->addItem(var_list_controllers.at(index));
    }

    //Gains:
    init_ctrl_gains();  //All 0 when we start
    ui->control_g0->setText("0");
    ui->control_g1->setText("0");
    ui->control_g2->setText("0");
    ui->control_g3->setText("0");
    ui->control_g4->setText("0");
    ui->control_g5->setText("0");
    str.sprintf("Current gains = {0,0,0,0,0,0}");
    ui->textLabel_Gains_i->setText(str);
    str.sprintf("Position gains = {0,0,0,0,0,0}");
    ui->textLabel_Gains_p->setText(str);
    str.sprintf("Impedance gains = {0,0,0,0,0,0}");
    ui->textLabel_Gains_z->setText(str);

    //Strain:
    //=================
    ui->stream_SA_ONbutto->setDisabled(1);
    ui->stream_SA_OFFbutton->setDisabled(1);

    //External:
    //=================
    ui->pushButton_ext_pwro->setText("Turn ON (PWM)");
    ui->ext_pwro_pwm->setText("0");
    ui->quad_write_val->setText("0");

    //Variable option lists:
    QStringList var_list_colors;
    var_list_colors << "Unchanged" << "Red" << "Green" << "Blue" << "White" << "Black (off)" \
                    << "Cyan" << "Magenta" << "Yellow";
    for(int index = 0; index < var_list_colors.count(); index++)
    {
        ui->comboBox_minm_rgb->addItem(var_list_colors.at(index));
    }

    //=================
    //Timers:
    //=================

    //Stream 1 (Execute):
    timer_stream = new QTimer(this);
    connect(timer_stream, SIGNAL(timeout()), this, SLOT(timerStreamEvent()));
    timer_stream->start(TIM_FREQ_TO_P(STREAM_DEFAULT_FREQ));

    //Stream 3 (Strain):
    timer_stream_sa = new QTimer(this);
    connect(timer_stream_sa, SIGNAL(timeout()), this, SLOT(timerStream_SA_Event()));
    timer_stream_sa->start(TIM_FREQ_TO_P(STREAM_DEFAULT_FREQ));

    //Stream 4 (RIC/NU Knee):
    timer_stream_ricnu = new QTimer(this);
    connect(timer_stream_ricnu, SIGNAL(timeout()), this, SLOT(timerStream_RICNU_Event()));
    timer_stream_ricnu->start(TIM_FREQ_TO_P(STREAM_DEFAULT_FREQ));

    //Plot:
    timer_plot = new QTimer(this);
    connect(timer_plot, SIGNAL(timeout()), this, SLOT(timerPlotEvent()));
    timer_plot->start(TIM_FREQ_TO_P(PLOT_DEFAULT_FREQ));

    //Control:
    timer_ctrl = new QTimer(this);
    connect(timer_ctrl, SIGNAL(timeout()), this, SLOT(timerCtrlEvent()));
    timer_ctrl_disp_refresh = new QTimer(this);
    connect(timer_ctrl_disp_refresh, SIGNAL(timeout()), this, SLOT(timerCtrlDispRefreshEvent()));
    timer_ctrl_disp_refresh->start(TIM_FREQ_TO_P(PLOT_DEFAULT_FREQ));
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
