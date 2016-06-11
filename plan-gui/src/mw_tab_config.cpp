//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Configuration
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QByteArray>
#include <string>

//****************************************************************************
// Function(s)
//****************************************************************************

void MainWindow::init_tab_config(void)
{
    //Menus:
    //===========

    //Slaves:
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

    //Experiment (stream tab):
    var_list_stream << "Barebone Execute" << "Barebone Manage" << "In Control" << "Strain Amp" << "RIC/NU Knee" << "CSEA Knee" << "2DOF Ankle" << "[Your project]";
    for(int index = 0; index < var_list_stream.count(); index++)
    {
        ui->StreamSelectComboBox->addItem(var_list_stream.at(index));
    }
    //By default we start with Execute stream:
    selected_experiment = 0;
    stream_fct_ptr = &MainWindow::stream_execute;
    //No streaming before COM is open:
    ui->streamON_master_button->setDisabled(1);
    //Only enable Slave A:
    disp_slave_a(true);
    disp_slave_b(false);

    //COM port:
    //=================
    ui->comPortTxt->setText("/dev/ttyACM0");
    ui->comStatusTxt->setText("Type COM port and click 'Open COM'.");
    ui->closeComButton->setDisabled(1); //Will be enabled when COM is open

    //Log, refresh rates:
    //======================
    ui->logFileTxt->setText("Not programmed... do not use yet.");
    ui->streamRefreshTxt->setText(QString::number(STREAM_DEFAULT_FREQ));
    ui->streamRefreshStatusTxt->setText("Default setting.");
    ui->logRefreshTxt->setText(QString::number(LOG_DEFAULT_FREQ));
    ui->logRefreshStatusTxt->setText("Default setting.");

    //Stream status:
    //==============
    ui->label_stream_status->setText(" ");
    stream_status_disp(-1); //Start Black
}

void MainWindow::init_tab_about(void)
{
    QString str;

    str.sprintf("Last full build: %s %s.\n", __DATE__, __TIME__);
    ui->text_last_build->setText(str);
    ui->text_last_build->repaint();
}

//Open COM port
void MainWindow::on_openComButton_clicked()
{
    QString str, comport;
    char *comport_char;
    int com_open = 0, tries = 50;

    //Opening statement, and name saving:

    qDebug("Open COM button clicked.");
    comport = ui->comPortTxt->text();
    QByteArray ba = comport.toLatin1();
    comport_char = ba.data();
    str = QString("Opening '") + comport + QString("'...");

    ui->comStatusTxt->setText(str);
    ui->comStatusTxt->repaint();
    ui->openComButton->setDisabled(1);
    ui->openComButton->repaint();

    //Open USB (serial) port:
    com_open = OpenUSBSerialPort(comport, tries, 100000);             //QSerialDriver
    if(!com_open)
    {
        qDebug("Successfully opened COM port.");
        str += QString(" Success!");

        //Activate Stream & Close COM buttons:
        ui->streamON_master_button->setEnabled(1);
        ui->closeComButton->setEnabled(1);
    }
    else if(com_open == 1)
    {
        qDebug("Tried n times, failed.");
        str += QString(" Tried ") + QString::number(tries) + QString(" times, failed. Right port? Check your permissions.");

        //Reactivate button:
        ui->openComButton->setEnabled(1);
        ui->openComButton->repaint();
    }
    else
    {
        qDebug("Some other error...");
        str += QString(" Unknown error...");

        //Reactivate button:
        ui->openComButton->setEnabled(1);
        ui->openComButton->repaint();
    }

    //Closing statement:
    ui->comStatusTxt->setText(str);
    ui->comStatusTxt->repaint();
}

//Close COM port
void MainWindow::on_closeComButton_clicked()
{
    //Close the port:
    CloseUSBSerialPort();

    //Enable Open COM button:
    ui->openComButton->setEnabled(1);
    ui->openComButton->repaint();

    //Disable Close COM button:
    ui->closeComButton->setDisabled(1);
    ui->closeComButton->repaint();

    ui->comStatusTxt->setText("COM Port closed.");
}

//Change refresh rate for Stream, Log and Plot
void MainWindow::on_updateRefreshButton_clicked()
{
    QString freq_txt, status;
    int period = 0, freq = 0;

    //Get frequency from text box, check limits
    freq_txt = ui->streamRefreshTxt->text();
    freq = freq_txt.toInt();
    if(freq < STREAM_MIN_FREQ)
    {
        status = "Invalid, minimum of " + QString::number(STREAM_MIN_FREQ) + "Hz.";
        ui->streamRefreshStatusTxt->setText(status);
        return;
    }
    else if(freq > STREAM_MAX_FREQ)
    {
        status = "Invalid, maximum of " + QString::number(STREAM_MAX_FREQ) + "Hz.";
        ui->streamRefreshStatusTxt->setText(status);
        return;
    }
    else
    {
        //Valid frequency: compute period, modify timer.

        period = (1000/freq);   //in ms
        //qDebug() << "Frequency in textbox is: " << freq << "Hz. Associated period (integer): " << period << "ms.";

        status = "f = " + QString::number(freq) + "Hz, integer period = " + QString::number(period) + "ms.";
        ui->streamRefreshStatusTxt->setText(status);
        timer_stream->setInterval(period);

        //Plot:
        //timer_plot->setInterval(period);  //Disabled, bugs at 50+Hz
    }
}

void MainWindow::on_SlaveSelectComboBox_currentIndexChanged(int index)
{
    active_slave_1_index = ui->SlaveSelectComboBox->currentIndex();
    active_slave_1 = list_to_slave[active_slave_1_index];
    qDebug() << "Selected slave is" << var_list_slaves.at(active_slave_1_index);
}

//*** New Config tab - Work in progress ***

void MainWindow::on_StreamSelectComboBox_currentIndexChanged(int index)
{
    selected_experiment = ui->StreamSelectComboBox->currentIndex();

    //All stream tabs OFF:
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);
    ui->tabWidget->setTabEnabled(3, false);
    ui->tabWidget->setTabEnabled(4, false);
    ui->tabWidget->setTabEnabled(8, false);
    ui->tabWidget->setTabEnabled(9, false);

    //By default, do not display Slave B:
    disp_slave_b(false);

    //Based on the experiment we assign a "stream" function pointer.
    //It will them be used by the stream timer event.
    switch(selected_experiment)
    {
        case 0: //Barebone Execute
            stream_fct_ptr = &MainWindow::stream_execute;
            ui->tabWidget->setTabEnabled(1, true);
            break;
        case 1: //Barebone Manage
            //stream_fct_ptr = &MainWindow::stream_manage;
            break;
        case 2: //In Control
            stream_fct_ptr = &MainWindow::stream_in_ctrl;
            ui->tabWidget->setTabEnabled(8, true);
            break;
        case 3: //Strain Amp
            stream_fct_ptr = &MainWindow::stream_strain_amp;
            ui->tabWidget->setTabEnabled(3, true);
            break;
        case 4: //RIC/NU Knee
            stream_fct_ptr = &MainWindow::stream_ricnu_knee;
            ui->tabWidget->setTabEnabled(4, true);
            break;
        case 5: //CSEA_KNEE
            //stream_fct_ptr = &MainWindow::stream_csea_knee;
            stream_fct_ptr = &MainWindow::stream_execute;
            qDebug() << "Not implemented yet! Streaming Execute instead.";
            break;
        case 6: //ANKLE_2DOF
            stream_fct_ptr = &MainWindow::stream_ankle_2dof;
            ui->tabWidget->setTabEnabled(1, true);  //Enable Execute tab
            ui->tabWidget->setTabEnabled(9, true);  //Enable Ankle tab
            disp_slave_b(true);
            qDebug() << "Work In Progress...";
            break;
        //case 6: //ToDo add more experiments...
        //    ctrl = ;
        //    break;
        default:
            stream_fct_ptr = &MainWindow::stream_execute;
            break;
    }
}

void MainWindow::on_streamON_master_button_clicked()
{
    ui->streamON_master_button->setDisabled(1);
    ui->streamOFF_master_button->setEnabled(1);

    ui->streamON_master_button->repaint();
    ui->streamOFF_master_button->repaint();

    stream_status = 1;
}

void MainWindow::on_streamOFF_master_button_clicked()
{
    ui->streamON_master_button->setEnabled(1);
    ui->streamOFF_master_button->setDisabled(1);

    ui->streamON_master_button->repaint();
    ui->streamOFF_master_button->repaint();

    stream_status = 0;

    stream_status_disp(-1); //Indicator = Black
}

void MainWindow::timerStreamEvent(void)
{
    //Stream tabs:
    if(stream_status)
    {
        //Calls the function selected by the user

        //***Important: this should be a function pointer call, but I failed at it... ToDo ***

        //stream_fct_ptr();

        //***So we are usign this for now:

        switch(selected_experiment)
        {
            case 0: //Barebone Execute
                stream_execute();
                break;
            case 1: //Barebone Manage
                //stream_manage();
                break;
            case 2: //In Control
                stream_in_ctrl();
                 break;
            case 3: //Strain Amp
                stream_strain_amp();
                break;
            case 4: //RIC/NU Knee
                stream_ricnu_knee();
                break;
            case 5: //CSEA_KNEE
                //stream_fct_ptr = &MainWindow::stream_csea_knee;
                break;
            case 6: //ToDo add more experiments...
                stream_ankle_2dof();
                break;
            default:
                //stream_execute();
                break;
        }
    }

    //Control & trapeze:
    stream_ctrl();
    control_trapeze();
}

void MainWindow::stream_status_disp(int status)
{

    if(status == 1)
    {
        ui->label_stream_status->setStyleSheet("QLabel { background-color: green; color: black;}");
    }
    else if(status == 0)
    {
        ui->label_stream_status->setStyleSheet("QLabel { background-color: red; color: black;}");
    }
    else
    {
        ui->label_stream_status->setStyleSheet("QLabel { background-color: black; color: black;}");
    }
}

//ToDo:
void MainWindow::on_logON_master_button_clicked()
{

}

void MainWindow::on_logOFF_master_button_clicked()
{

}

void MainWindow::assign_execute_ptr(struct execute_s **ex_ptr, uint8_t slave)
{
    //Based on selected slave, what structure do we use?
    switch(slave)
    {
        case 0:
            *ex_ptr = &exec1;
            break;
        case 1:
            *ex_ptr = &exec2;
            break;
        case 2:
            *ex_ptr = &exec3;
            break;
        case 3:
            *ex_ptr = &exec4;
            break;
        default:
            *ex_ptr = &exec1;
            break;
    }
}
