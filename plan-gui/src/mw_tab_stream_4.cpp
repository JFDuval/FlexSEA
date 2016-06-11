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

void MainWindow::init_tab_stream_ricnu_knee(void)
{
}

void MainWindow::stream_ricnu_knee(void)
{
    int numb = 0;

    numb = tx_cmd_data_read_all_ricnu(active_slave_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN); //New Read All function
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
    numb = COMM_STR_BUF_LEN;

    USBSerialPort_Write(numb, comm_str_usb);        //QSerialPort

    //Can we decode what we received?
    USBSerialPort_Read(usb_rx);
    decode_usb_rx(usb_rx);

    //Raw values:

    ui->ricnu_accx->setText(QString::number(ricnu_1.ex.accel.x));
    ui->ricnu_accy->setText(QString::number(ricnu_1.ex.accel.y));
    ui->ricnu_accz->setText(QString::number(ricnu_1.ex.accel.z));
    ui->ricnu_gyrox->setText(QString::number(ricnu_1.ex.gyro.x));
    ui->ricnu_gyroy->setText(QString::number(ricnu_1.ex.gyro.y));
    ui->ricnu_gyroz->setText(QString::number(ricnu_1.ex.gyro.z));

    ui->ricnu_enc_mot->setText(QString::number(ricnu_1.ex.enc_commut));
    ui->ricnu_enc_joint->setText(QString::number(ricnu_1.ex.enc_control));

    ui->ricnu_current->setText(QString::number(ricnu_1.ex.current));
    ui->ricnu_vb->setText(QString::number(ricnu_1.ex.volt_batt));

    ui->ricnu_strain_ch1->setText(QString::number(ricnu_1.ext_strain[0]));
    ui->ricnu_strain_ch2->setText(QString::number(ricnu_1.ext_strain[1]));
    ui->ricnu_strain_ch3->setText(QString::number(ricnu_1.ext_strain[2]));
    ui->ricnu_strain_ch4->setText(QString::number(ricnu_1.ext_strain[3]));
    ui->ricnu_strain_ch5->setText(QString::number(ricnu_1.ext_strain[4]));
    ui->ricnu_strain_ch6->setText(QString::number(ricnu_1.ext_strain[5]));

    //To plot strain, we store in other structure:
    strain[0].strain_filtered = ricnu_1.ext_strain[0];
    strain[1].strain_filtered = ricnu_1.ext_strain[1];
    strain[2].strain_filtered = ricnu_1.ext_strain[2];
    strain[3].strain_filtered = ricnu_1.ext_strain[3];
    strain[4].strain_filtered = ricnu_1.ext_strain[4];
    strain[5].strain_filtered = ricnu_1.ext_strain[5];

    //Decode some of them:
    //===================

    ui->ricnu_current_d->setText(QString::number((float)ricnu_1.ex.current*18.5, 'i',0));
    ui->ricnu_vb_d->setText(QString::number(P4_ADC_SUPPLY*((16*(float)ricnu_1.ex.volt_batt/3 + 302 )/P4_ADC_MAX) / 0.0738, 'f',2));

    ui->ricnu_accx_d->setText(QString::number((double)ricnu_1.ex.accel.x/8192, 'f', 2));
    ui->ricnu_accy_d->setText(QString::number((double)ricnu_1.ex.accel.y/8192, 'f', 2));
    ui->ricnu_accz_d->setText(QString::number((double)ricnu_1.ex.accel.z/8192, 'f', 2));
    ui->ricnu_gyrox_d->setText(QString::number((double)ricnu_1.ex.gyro.x/16.4, 'i', 0));
    ui->ricnu_gyroy_d->setText(QString::number((double)ricnu_1.ex.gyro.y/16.4, 'i', 0));
    ui->ricnu_gyroz_d->setText(QString::number((double)ricnu_1.ex.gyro.z/16.4, 'i', 0));

    ui->ricnu_strain_ch1_d->setText(QString::number(((double)(ricnu_1.ext_strain[0]-32768)/32768)*100, 'i', 0));
    ui->ricnu_strain_ch2_d->setText(QString::number(((double)(ricnu_1.ext_strain[1]-32768)/32768)*100, 'i', 0));
    ui->ricnu_strain_ch3_d->setText(QString::number(((double)(ricnu_1.ext_strain[2]-32768)/32768)*100, 'i', 0));
    ui->ricnu_strain_ch4_d->setText(QString::number(((double)(ricnu_1.ext_strain[3]-32768)/32768)*100, 'i', 0));
    ui->ricnu_strain_ch5_d->setText(QString::number(((double)(ricnu_1.ext_strain[4]-32768)/32768)*100, 'i', 0));
    ui->ricnu_strain_ch6_d->setText(QString::number(((double)(ricnu_1.ext_strain[5]-32768)/32768)*100, 'i', 0));

    ui->tabWidget->repaint();

    //ToDo: this is a hack***
    //To be able to plot RIC/NU values we copy them in the exec & strain structures
    exec1.accel.x = ricnu_1.ex.accel.x;
    exec1.accel.y = ricnu_1.ex.accel.y;
    exec1.accel.z = ricnu_1.ex.accel.z;

    exec1.gyro.x = ricnu_1.ex.gyro.x;
    exec1.gyro.y = ricnu_1.ex.gyro.y;
    exec1.gyro.z = ricnu_1.ex.gyro.z;

    exec1.current = ricnu_1.ex.current;
    exec1.volt_batt = ricnu_1.ex.volt_batt;

    strain[0].strain_filtered = ricnu_1.ext_strain[0];
    strain[1].strain_filtered = ricnu_1.ext_strain[1];
    strain[2].strain_filtered = ricnu_1.ext_strain[2];
    strain[3].strain_filtered = ricnu_1.ext_strain[3];
    strain[4].strain_filtered = ricnu_1.ext_strain[4];
    strain[5].strain_filtered = ricnu_1.ext_strain[5];
}
