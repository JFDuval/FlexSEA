//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 03/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - USB Serial Port Driver
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QByteArray>
//#include <string>

//Open port
int MainWindow::OpenUSBSerialPort(QString name, int tries, int delay)
{
    unsigned int cnt = 0;
    bool fd = false;

    USBSerialPort.setPortName(name);
    USBSerialPort.setBaudRate(USBSerialPort.Baud115200);
    USBSerialPort.setDataBits(QSerialPort::Data8);
    USBSerialPort.setParity(QSerialPort::NoParity);
    USBSerialPort.setStopBits(QSerialPort::OneStop);
    USBSerialPort.setFlowControl(QSerialPort::NoFlowControl);

    do
    {
        fd = USBSerialPort.open(QIODevice::ReadWrite);  //returns true if successful
        cnt++;
        if(cnt >= tries)
            break;

        //When false, print error code:
        if(fd == false)
        {
            qDebug() << "Try #" << cnt << " failed. Error: " << USBSerialPort.errorString() << ".\n";
        }

        usleep(delay);
    }while(fd != true);


    if (fd == false)
    {
        //qDebug() << "Tried " << cnt << " times, couldn't open " << name << ".\n";

        return 1;
    }
    else
    {
        //qDebug() << "Successfully opened " << name << ".\n";

        //Clear any data that was already in the buffers:
        //while(USBSerialPort.waitForReadyRead(100))
        {
            USBSerialPort.clear((QSerialPort::AllDirections));
        }

        return 0;
    }
}

//Close port
void MainWindow::CloseUSBSerialPort(void)
{
    if(stream_status)
    {
        stream_status = 0;
        usleep(50000);
    }

    USBSerialPort.clear((QSerialPort::AllDirections));
    USBSerialPort.close();
}

//Write
int MainWindow::USBSerialPort_Write(char bytes_to_send, unsigned char *serial_tx_data)
{
    qint64 write_ret = 0;
    QByteArray myQBArray;
    myQBArray = QByteArray::fromRawData((const char*)serial_tx_data, bytes_to_send);

    //Check if COM was successfully opened:

    write_ret = USBSerialPort.write(myQBArray);

    return (int) write_ret;
}

//Read
int MainWindow::USBSerialPort_Read(unsigned char *buf)
{
    QByteArray data;
    bool dataReady = false;

    dataReady = USBSerialPort.waitForReadyRead(100);
    if(dataReady == true)
    {
        data = USBSerialPort.readAll();

        //We check to see if we are getting reasonnable packets, or a bunch of crap:
        int len = data.length();
        if(len > 256)
        {
            qDebug() << "Data length over 256 bytes (" << len << "bytes)";
            len = 256;
            USBSerialPort.clear((QSerialPort::AllDirections));
            return 0;
        }

        qDebug() << "Read " << len << " bytes.";

        //Fill the rx buf with our new bytes:
        for(int i = 0; i < len; i++)
        {
            update_rx_buf_byte_usb(data[i]);
            //ToDo use array
        }
    }
    else
    {
        qDebug("No USB bytes available.");
    }
}

