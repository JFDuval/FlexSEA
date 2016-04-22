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
        //===================

        ui->disp_current_d->setText(QString::number((float)exec1.current*18.5, 'i',0));
        ui->disp_vb_d->setText(QString::number(P4_ADC_SUPPLY*((16*(float)exec1.volt_batt/3 + 302 )/P4_ADC_MAX) / 0.0738, 'f',2));
        ui->disp_vg_d->setText(QString::number(P4_ADC_SUPPLY*((26*(float)exec1.volt_int/3 + 440 )/P4_ADC_MAX) / 0.43, 'f',2));
        ui->disp_temp_d->setText(QString::number(((((2.625*(float)exec1.temp + 41)/P4_ADC_MAX)*P4_ADC_SUPPLY) - P4_T0) / P4_TC,'f',1));
        ui->disp_ana_d->setText(QString::number(((float)exec1.analog[0]/P4_ADC_MAX)*P4_ADC_SUPPLY,'f',2));

        ui->disp_accx_d->setText(QString::number((double)exec1.accel.x/8192, 'f', 2));
        ui->disp_accy_d->setText(QString::number((double)exec1.accel.y/8192, 'f', 2));
        ui->disp_accz_d->setText(QString::number((double)exec1.accel.z/8192, 'f', 2));
        ui->disp_gyrox_d->setText(QString::number((double)exec1.gyro.x/16.4, 'i', 0));
        ui->disp_gyroy_d->setText(QString::number((double)exec1.gyro.y/16.4, 'i', 0));
        ui->disp_gyroz_d->setText(QString::number((double)exec1.gyro.z/16.4, 'i', 0));

        ui->disp_strain_d->setText(QString::number(((double)(exec1.strain-32768)/32768)*100, 'i', 0));

        ui->tabWidget->repaint();

        //==========
    }
}
