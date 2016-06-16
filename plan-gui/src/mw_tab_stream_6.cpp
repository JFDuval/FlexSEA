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
}

//We sample 2 different Execute
void MainWindow::stream_ankle_2dof(void)
{
    int numb = 0;
    static uint8_t sel_slave = 0;
    //sel_slave = active_slave_1;

    numb = tx_cmd_ctrl_special_5(active_slave_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, sel_slave);	//ToDo change
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

