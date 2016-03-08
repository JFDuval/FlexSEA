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

//Open COM port
void MainWindow::on_openComButton_clicked()
{
    QString str, comport;
    char *comport_char;
    int com_open = 0, tries = 150;

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
    //com_open = flexsea_serial_open_2(comport_char, tries, 50000);   //DIY driver
    com_open = OpenUSBSerialPort(comport, tries, 100000);             //QSerialDriver
    if(!com_open)
    {
        qDebug("Successfully opened COM port.");
        str += QString(" Success!");

        //Activate Stream & Clsoe COM buttons:
        ui->streamONbutton->setEnabled(1);
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
}

//Change refresh rate for Stream & Log
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
        //Valid frequency: compute priod, modify timer.

        period = (1000/freq);   //in ms
        //qDebug() << "Frequency in textbox is: " << freq << "Hz. Associated period (integer): " << period << "ms.";

        status = "f = " + QString::number(freq) + "Hz, integer period = " + QString::number(period) + "ms.";
        ui->streamRefreshStatusTxt->setText(status);
        timer_stream->setInterval(period);
    }
}
