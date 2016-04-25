//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 04/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:External
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

//****************************************************************************
// Public Function(s)
//****************************************************************************

void MainWindow::on_pushButton_ext_pwro_clicked()
{
    static uint8_t pwro_button_state = 0;
    uint8_t pwm = 0;
    int numb = 0;

    //Toggle:
    pwro_button_state ^= 1;

    if(!pwro_button_state)
    {
        //We are in Output OFF Mode.
        ui->pushButton_ext_pwro->setText("Turn ON (PWM)");
        pwm = 0;
    }
    else
    {
        //We are in Output ON Mode.
        ui->pushButton_ext_pwro->setText("Turn OFF");
        pwm = ui->ext_pwro_pwm->text().toInt();;
    }

    //Prepare and send command:
    tx_cmd_exp_pwro(FLEXSEA_EXECUTE_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, pwm);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
    numb = COMM_STR_BUF_LEN;
    USBSerialPort_Write(numb, comm_str_usb);
    qDebug() << "Sending PWRO a PWM = " << pwm << " value.";

    //Can we decode what we received?
    //USBSerialPort_Read(usb_rx);
    //decode_usb_rx(usb_rx);

}
