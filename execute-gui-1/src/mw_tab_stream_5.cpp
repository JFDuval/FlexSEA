//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Stream 5 (In Control)
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

void MainWindow::init_tab_stream_in_ctrl(void)
{
    ui->inctrl_w0->setText("0");
    ui->inctrl_w1->setText("0");
    ui->inctrl_w2->setText("0");
    ui->inctrl_w3->setText("0");
}

void MainWindow::stream_in_ctrl(void)
{
    int numb = 0;

    numb = tx_cmd_in_control(active_slave_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, 0);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
    numb = COMM_STR_BUF_LEN;

    USBSerialPort_Write(numb, comm_str_usb);        //QSerialPort

    //Can we decode what we received?
    USBSerialPort_Read(usb_rx);
    decode_usb_rx(usb_rx);

    //Raw values:

    ui->disp_inctrl_setp->setText(QString::number(in_control_1.setp));
    ui->disp_inctrl_actual_val->setText(QString::number(in_control_1.actual_val));
    ui->disp_inctrl_error->setText(QString::number(in_control_1.error));
    ui->disp_inctrl_pwm->setText(QString::number(in_control_1.pwm));

    ui->tabWidget->repaint();
}


void MainWindow::on_pushButton_inctrl_w0_clicked()
{

}

void MainWindow::on_pushButton_inctrl_w1_clicked()
{

}

void MainWindow::on_pushButton_inctrl_w2_clicked()
{

}

void MainWindow::on_pushButton_inctrl_w3_clicked()
{

}
