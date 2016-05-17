//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Stream 4 (RIC/NU Knee)
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

void MainWindow::on_stream_RICNU_ONbutton_clicked()
{
    ui->stream_RICNU_ONbutton->setDisabled(1);
    ui->stream_RICNU_OFFbutton->setEnabled(1);

    ui->stream_RICNU_ONbutton->repaint();
    ui->stream_RICNU_OFFbutton->repaint();

	//Can't have 2 stream at the same time
	stream_status = 0;
	stream_ricnu_status = 1;
	stream_sa_status = 0;
}

void MainWindow::on_stream_RICNU_OFFbutton_clicked()
{
	ui->stream_RICNU_ONbutton->setEnabled(1);
	ui->stream_RICNU_OFFbutton->setDisabled(1);

	ui->stream_RICNU_ONbutton->repaint();
	ui->stream_RICNU_OFFbutton->repaint();

	//Can't have 2 stream at the same time
	stream_status = 0;
	stream_ricnu_status = 0;
	stream_sa_status = 0;
}

void MainWindow::timerStream_RICNU_Event(void)
{
    if(stream_ricnu_status)
    {
        //==========
        //Test: call Stream 1

        int numb = 0;

        numb = tx_cmd_data_read_all_ricnu(active_slave_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN); //New Read All function
        numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;

        //flexsea_serial_transmit(numb, comm_str_spi, 0); //DIY driver
        USBSerialPort_Write(numb, comm_str_usb);        //QSerialPort

        //Can we decode what we received?
        USBSerialPort_Read(usb_rx);
        decode_usb_rx(usb_rx);

        //Raw values:

        //*** Work in progress ***
        ui->ricnu_accx->setText(QString::number(ricnu_1.ex.accel.x));
        ui->ricnu_accy->setText(QString::number(ricnu_1.ex.accel.y));
        ui->ricnu_accz->setText(QString::number(ricnu_1.ex.accel.z));
        ui->ricnu_gyrox->setText(QString::number(ricnu_1.ex.gyro.x));
        ui->ricnu_gyroy->setText(QString::number(ricnu_1.ex.gyro.y));
        ui->ricnu_gyroz->setText(QString::number(ricnu_1.ex.gyro.z));

        ui->ricnu_enc_mot->setText(QString::number(ricnu_1.enc_mot));
        ui->ricnu_enc_joint->setText(QString::number(ricnu_1.enc_joint));

        ui->ricnu_current->setText(QString::number(ricnu_1.ex.current));

        ui->ricnu_vb->setText(QString::number(ricnu_1.ex.volt_batt));

        //Decode some of them:
        //===================

        ui->ricnu_current_d->setText(QString::number((float)(ricnu_1.ex.current- ui->horizontalSlider_current_zero->value())*18.5, 'i',0));
        ui->ricnu_vb_d->setText(QString::number(P4_ADC_SUPPLY*((16*(float)ricnu_1.ex.volt_batt/3 + 302 )/P4_ADC_MAX) / 0.0738, 'f',2));

        ui->ricnu_accx_d->setText(QString::number((double)ricnu_1.ex.accel.x/8192, 'f', 2));
        ui->ricnu_accy_d->setText(QString::number((double)ricnu_1.ex.accel.y/8192, 'f', 2));
        ui->ricnu_accz_d->setText(QString::number((double)ricnu_1.ex.accel.z/8192, 'f', 2));
        ui->ricnu_gyrox_d->setText(QString::number((double)ricnu_1.ex.gyro.x/16.4, 'i', 0));
        ui->ricnu_gyroy_d->setText(QString::number((double)ricnu_1.ex.gyro.y/16.4, 'i', 0));
        ui->ricnu_gyroz_d->setText(QString::number((double)ricnu_1.ex.gyro.z/16.4, 'i', 0));

        ui->tabWidget->repaint();

        //==========
    }
}
