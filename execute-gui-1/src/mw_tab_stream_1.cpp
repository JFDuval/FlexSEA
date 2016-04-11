//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Stream 1 (Basic)
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <string>

void MainWindow::on_streamONbutton_clicked()
{
    ui->streamONbutton->setDisabled(1);
    ui->streamOFFbutton->setEnabled(1);

    ui->streamONbutton->repaint();
    ui->streamOFFbutton->repaint();

    stream_status = 1;
}

void MainWindow::on_streamOFFbutton_clicked()
{
    ui->streamONbutton->setEnabled(1);
    ui->streamOFFbutton->setDisabled(1);

    ui->streamONbutton->repaint();
    ui->streamOFFbutton->repaint();

    stream_status = 0;
}

void MainWindow::timerStreamEvent(void)
{
    if(stream_status)
    {
        //==========
        //Test: call Stream 1

        int numb = 0;

        /*
        //Special1 command to test the ShuoBot Exo

        numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
                                        KEEP, 0, KEEP, 0, 0, exp_pwm);
        */
        numb = tx_cmd_data_read_all(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN); //New Read All function

        numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;

        //flexsea_serial_transmit(numb, comm_str_spi, 0); //DIY driver
        USBSerialPort_Write(numb, comm_str_usb);        //QSerialPort

        //Can we decode what we received?
        USBSerialPort_Read(usb_rx);
        decode_usb_rx(usb_rx);

        //Raw values:

        ui->disp_accx->setText(QString::number(exec1.accel.x));
        ui->disp_accy->setText(QString::number(exec1.accel.y));
        ui->disp_accz->setText(QString::number(exec1.accel.z));
        ui->disp_gyrox->setText(QString::number(exec1.gyro.x));
        ui->disp_gyroy->setText(QString::number(exec1.gyro.y));
        ui->disp_gyroz->setText(QString::number(exec1.gyro.z));

        ui->disp_enc->setText(QString::number(exec1.encoder));
        ui->disp_strain->setText(QString::number(exec1.strain));
        ui->disp_ana->setText(QString::number(exec1.analog[0]));

        ui->disp_current->setText(QString::number(exec1.current));

        ui->disp_vb->setText(QString::number(exec1.volt_batt));
        ui->disp_vg->setText(QString::number(exec1.volt_int));
        ui->disp_temp->setText(QString::number(exec1.temp));

        ui->disp_stat1->setText(QString::number(exec1.status1));
        ui->disp_stat2->setText(QString::number(exec1.status2));

        //Decode some of them:
        ui->disp_current_d->setText(QString::number((float)exec1.current*12.2));

        ui->tabWidget->repaint();

        //==========
    }
}
