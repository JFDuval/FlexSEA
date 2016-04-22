//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Conterol
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

void MainWindow::on_pushButton_SetController_clicked()
{
    int numb = 0;
    int16_t ctrl = CTRL_NONE;

    selected_controller = ui->comboBox_ctrl_list->currentIndex();
    wanted_controller = selected_controller;

    switch(wanted_controller)
    {
        case 0: //Null
            ctrl = CTRL_NONE;
            break;
        case 1: //Open
            ctrl = CTRL_OPEN;
            break;
        case 2: //Position
            ctrl = CTRL_POSITION;
             break;
        case 3: //Current
            ctrl = CTRL_CURRENT;
            break;
        case 4: //Impedance
            ctrl = CTRL_IMPEDANCE;
            break;
        case 5: //Custom/other
            ctrl = CTRL_NONE;
            break;
        default:
            ctrl = CTRL_NONE;
            break;
    }

    //Prepare and send command:
    tx_cmd_ctrl_mode(FLEXSEA_EXECUTE_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, ctrl);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
    numb = COMM_STR_BUF_LEN;
    USBSerialPort_Write(numb, comm_str_usb);

    //Can we decode what we received?
    //USBSerialPort_Read(usb_rx);
    //decode_usb_rx(usb_rx);
}

void MainWindow::on_pushButton_setp_a_go_clicked()
{
    int val = 0;
    val = ui->control_setp_a->text().toInt();
    controller_setpoint(val);
}

void MainWindow::on_pushButton_setp_b_go_clicked()
{
    int val = 0;
    val = ui->control_setp_b->text().toInt();
    controller_setpoint(val);
}

void MainWindow::on_pushButton_SetGains_clicked()
{
    QString str;
    int16_t gains[6] = {0,0,0,0,0,0};
    int numb = 0, valid = 0;

    //Save gains in variables:
    gains[0] = ui->control_g0->text().toInt();
    gains[1] = ui->control_g1->text().toInt();
    gains[2] = ui->control_g2->text().toInt();
    gains[3] = ui->control_g3->text().toInt();
    gains[4] = ui->control_g4->text().toInt();
    gains[5] = ui->control_g5->text().toInt();

    //Update display:
    str.sprintf("Gains = {%i,%i,%i,%i,%i,%i}", gains[0],gains[1],gains[2], \
                                                gains[3],gains[4],gains[5]);
    ui->textLabel_Gains->setText(str);

    //Send command to hardware:

    //Different controllers have different gain functions:
    selected_controller = ui->comboBox_ctrl_list->currentIndex();
    switch(selected_controller)
    {
        case 0: //Null
            valid = 0;
            break;
        case 1: //Open
            valid = 0;
            break;
        case 2: //Position
            valid = 1;
            tx_cmd_ctrl_p_g(FLEXSEA_EXECUTE_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, \
                                    gains[0], gains[1], gains[2]);
             break;
        case 3: //Current
            valid = 1;
            numb = tx_cmd_ctrl_i_g(FLEXSEA_EXECUTE_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, \
                                gains[0], gains[1], gains[2]);
            break;
        case 4: //Impedance
            valid = 1;
            tx_cmd_ctrl_z_g(FLEXSEA_EXECUTE_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, \
                                    gains[0], gains[1], gains[2]);
            break;
        case 5: //Custom/other
            valid = 0;
            break;
        default:
            valid = 0;
            break;
    }

    if(valid)
    {
        //Common for all gain functions:
        numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;
        USBSerialPort_Write(numb, comm_str_usb);

        //Can we decode what we received?
        //USBSerialPort_Read(usb_rx);
        //decode_usb_rx(usb_rx);
    }
}

void MainWindow::on_pushButton_CtrlMinMax_clicked()
{
    //Get min & max, update slider limits:
    ui->hSlider_Ctrl->setMinimum(ui->control_slider_min->text().toInt());
    ui->hSlider_Ctrl->setMaximum(ui->control_slider_max->text().toInt());
    //Set slider to min:
    ui->hSlider_Ctrl->setValue(ui->control_slider_min->text().toInt());
}

void MainWindow::on_hSlider_Ctrl_valueChanged(int value)
{
    uint val = 0;
    val = ui->hSlider_Ctrl->value();

    controller_setpoint(val);

    //Wait 2ms to avoid sending a million packets when we move the slider
    usleep(2000);
}

void MainWindow::controller_setpoint(int val)
{
    uint numb = 0, valid = 0;

    switch(wanted_controller)
    {
        case 0: //Null
            valid = 0;
            break;
        case 1: //Open
            valid = 1;
            numb = tx_cmd_ctrl_o(FLEXSEA_EXECUTE_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, val);
            break;
        case 2: //Position
            valid = 0;
             break;
        case 3: //Current
            valid = 1;
            numb = tx_cmd_ctrl_i(FLEXSEA_EXECUTE_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, val, 0);
            break;
        case 4: //Impedance
            valid = 0;
            break;
        case 5: //Custom/other
            valid = 0;
            break;
        default:
            valid = 0;
            break;
    }

    if(valid)
    {
        //Common for all gain functions:
        numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;
        USBSerialPort_Write(numb, comm_str_usb);

        //Can we decode what we received?
        //USBSerialPort_Read(usb_rx);
        //decode_usb_rx(usb_rx);
    }
}
