//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 06/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Stream 6 (Ankle 2DOF)
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

void MainWindow::init_tab_stream_ankle_2dof(void)
{
    //All at 0 at start:
    ui->a2dof_w0->setText("0");
    ui->a2dof_w1->setText("0");
    ui->a2dof_w2->setText("0");
    ui->a2dof_w3->setText("0");
    ui->a2dof_r0->setText("0");
    ui->a2dof_r1->setText("0");
    ui->a2dof_r2->setText("0");
    ui->a2dof_r3->setText("0");
}

//We sample 2 different Execute
void MainWindow::stream_ankle_2dof(void)
{
    int numb = 0;
    static uint8_t sel_slave = 0;
    //sel_slave = active_slave_1;

    numb = tx_cmd_ctrl_special_5(active_slave_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, sel_slave, 0, 0, 0);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
    numb = COMM_STR_BUF_LEN;

    USBSerialPort_Write(numb, comm_str_usb);        //QSerialPort

    //Can we decode what we received?
    USBSerialPort_Read(usb_rx);
    decode_usb_rx(usb_rx);

    //Refresh display & change slave for next cycle
    if(sel_slave == 0)
    {
        disp_execute(&exec1, 0);
        sel_slave = 1;
    }
    else
    {
        disp_execute(&exec2, 1);
        sel_slave = 0;
    }
}

void MainWindow::on_pushButton_a2dof_w0_clicked()
{
    user_data_1.w[0] = (int16_t)ui->a2dof_w0->text().toInt();
    a2dof_write_user_data(0);
}

void MainWindow::on_pushButton_a2dof_w1_clicked()
{
    user_data_1.w[1] = (int16_t)ui->a2dof_w1->text().toInt();
    a2dof_write_user_data(1);
}

void MainWindow::on_pushButton_a2dof_w2_clicked()
{
    user_data_1.w[2] = (int16_t)ui->a2dof_w2->text().toInt();
    a2dof_write_user_data(2);
}

void MainWindow::on_pushButton_a2dof_w3_clicked()
{
    user_data_1.w[3] = (int16_t)ui->a2dof_w3->text().toInt();
    a2dof_write_user_data(3);
}

void MainWindow::on_pushButton_a2dof_refresh_clicked()
{
    int numb = 0;

    numb = tx_cmd_data_user(active_slave_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, 0);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
    numb = COMM_STR_BUF_LEN;

    USBSerialPort_Write(numb, comm_str_usb);        //QSerialPort

    //Can we decode what we received?
    USBSerialPort_Read(usb_rx);
    decode_usb_rx(usb_rx);

    //Refresh display:
    ui->a2dof_r0->setText(QString::number(user_data_1.r[0]));
    ui->a2dof_r1->setText(QString::number(user_data_1.r[1]));
    ui->a2dof_r2->setText(QString::number(user_data_1.r[2]));
    ui->a2dof_r3->setText(QString::number(user_data_1.r[3]));
}

void MainWindow::a2dof_write_user_data(uint8_t sel_w)
{
    int numb = 0;

    numb = tx_cmd_data_user(active_slave_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, sel_w);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
    numb = COMM_STR_BUF_LEN;

    USBSerialPort_Write(numb, comm_str_usb);        //QSerialPort

    qDebug() << "Writing" << user_data_1.w[sel_w] << "to field" << sel_w;

    //Can we decode what we received?
    //USBSerialPort_Read(usb_rx);
    //decode_usb_rx(usb_rx);
}
