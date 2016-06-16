//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 06/2016
//****************************************************************************
// Datalogging functions
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
#include <QTextStream>
#include <string>

//****************************************************************************
// Function(s)
//****************************************************************************

void MainWindow::init_datalogger(void)
{
    //Not logging yet, no OFF button.
    log_status = 0;
    log_num = '0';
    ui->logOFF_master_button->setDisabled(1);
    ui->logON_master_button->setDisabled(1);    //Enabled by opening COM

    //For now the filename is not user editable:
    ui->logFileTxt->setDisabled(1);

    //Do we already have a "Logs" directory?
    if(!QDir("../../Logs").exists())
    {
        //No, create it:
        QDir().mkdir("../../Logs");
        qDebug() << "Created /Logs/";
    }
    else
    {
        qDebug() << "Using existing ""Logs"" directory";
    }

    //One directory per date
    filename_date = filename_date.sprintf("../../Logs/%s", __DATE__);
    //Do we already have a "Today's date" directory?
    if(!QDir(filename_date).exists())
    {
        //No, create it:
        QDir().mkdir(filename_date);
        qDebug() << "Created" << filename_date << "/";
    }
    else
    {
        qDebug() << "Using existing" << filename_date << "directory";
    }

    //Last: file name based on time (default)
    filename_time = filename_time.sprintf("%s", __TIME__);

    log_filename = filename_date + "/" + filename_time + + "_";
    ui->logFileTxt->setText(log_filename + log_num + ".txt");
    ui->logRefreshTxt->setText(QString::number(LOG_DEFAULT_FREQ));
    ui->logRefreshStatusTxt->setText("Default setting.");
}

//Note: work in progress! For now we use the Stream function to communicate with slaves and get data
void MainWindow::timerLogEvent(void)
{
    //Stream tabs:
    if(log_status)
    {
        switch(selected_experiment)
        {
            case 0: //Barebone Execute
                log_execute();
                break;
            case 1: //Barebone Manage
                //stream_manage();
                break;
            case 2: //In Control
                //stream_in_ctrl();
                 break;
            case 3: //Strain Amp
                //stream_strain_amp();
                break;
            case 4: //RIC/NU Knee
                //stream_ricnu_knee();
                break;
            case 5: //CSEA_KNEE
                //stream_fct_ptr = &MainWindow::stream_csea_knee;
                break;
            case 6: //ToDo add more experiments...
                //stream_ankle_2dof();
                break;
            default:
                //stream_execute();
                break;
        }
    }
}

void MainWindow::on_logON_master_button_clicked()
{
    //Buttons:
    ui->logOFF_master_button->setEnabled(1);
    ui->logON_master_button->setDisabled(1);
    ui->streamON_master_button->setDisabled(1);

    log_filename = filename_date + "/" + filename_time + + "_" + log_num + ".txt";
    ui->logFileTxt->setText(log_filename);

    //Create new file:
    log_file.close();
    log_file.setFileName(log_filename);
    //log_file.open(log_filename);
    if(log_file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Successfully created and opened" << log_filename;
    }
    else
    {
        qDebug() << "Datalogging file error!";
    }

    //Point stream to file:
    logfile_stream.setDevice(&log_file);

    //Print header:
    logfile_stream << "accel.x," << \
                      "accel.y," << \
                      "accel.z," << \
                      "gyro.x," << \
                      "gyro.y," << \
                      "gyro.z," << \
                      '\n';
    //ToDo make generic!
    //ToDo add more fields

    //Start logging:
    log_status = 1;
    log_num++;
}

void MainWindow::on_logOFF_master_button_clicked()
{
    //Buttons:
    ui->logON_master_button->setEnabled(1);
    ui->logOFF_master_button->setDisabled(1);
    ui->streamON_master_button->setEnabled(1);

    //Stop logging:
    log_status = 0;
}

//ToDo Work In Progress! For now we use the Stream function to communicate with slaves and get data
//Only works with Execute 1
void MainWindow::log_execute(void)
{
    struct execute_s *exec_ptr = &exec1;

    //We use the Stream function for 99% of our needs:
    stream_execute();

    //And we add to he text file:
    logfile_stream << exec_ptr->accel.x << ',' << \
                      exec_ptr->accel.y << ',' << \
                      exec_ptr->accel.z << ',' << \
                      exec_ptr->gyro.x << ',' << \
                      exec_ptr->gyro.y << ',' << \
                      exec_ptr->gyro.z << ',' << \
                      '\n';
    //ToDo complete (follow what stream is doing)
}
