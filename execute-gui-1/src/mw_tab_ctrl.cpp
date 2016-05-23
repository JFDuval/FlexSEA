//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 04/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Control
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

#define CONTROLLERS 6
#define GAIN_FIELDS 6

void MainWindow::init_ctrl_gains(void)
{
    int i = 0, j = 0;
    for(i = 0; i < CONTROLLERS; i++)
    {
        for(j = 0; j < GAIN_FIELDS; j++)
        {
            //All gains = 0:
            ctrl_gains[i][j] = 0;
        }
    }
}

void MainWindow::save_ctrl_gains(int controller, int16_t *gains)
{
    int i = 0;
    for(i = 0; i < GAIN_FIELDS; i++)
    {
        ctrl_gains[controller][i] = gains[i];
    }
}

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
    tx_cmd_ctrl_mode(active_slave_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, ctrl);
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

    ctrl_setpoint = ui->control_setp_a->text().toInt();
    trap_posi = exec1.enc_display;
    trap_posf = ui->control_setp_a->text().toInt();
    trap_pos = ctrl_setpoint;

    trap_spd = ui->control_trapeze_spd->text().toInt();
    trap_acc = ui->control_trapeze_acc->text().toInt();

    controller_setpoint(val);
}

void MainWindow::on_pushButton_setp_b_go_clicked()
{
    int val = 0;
    val = ui->control_setp_b->text().toInt();

    ctrl_setpoint = ui->control_setp_b->text().toInt();
    trap_posi = exec1.enc_display;
    trap_posf = ui->control_setp_b->text().toInt();
    trap_pos = ctrl_setpoint;

    trap_spd = ui->control_trapeze_spd->text().toInt();
    trap_acc = ui->control_trapeze_acc->text().toInt();

    controller_setpoint(val);
}

void MainWindow::on_pushButton_SetGains_clicked()
{
    QString str;
    int16_t gains[6] = {0,0,0,0,0,0};
    int numb = 0, valid = 0;

    //Save gains in temp variables:
    gains[0] = ui->control_g0->text().toInt();
    gains[1] = ui->control_g1->text().toInt();
    gains[2] = ui->control_g2->text().toInt();
    gains[3] = ui->control_g3->text().toInt();
    gains[4] = ui->control_g4->text().toInt();
    gains[5] = ui->control_g5->text().toInt();

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
            save_ctrl_gains(selected_controller, gains);
            str.sprintf("Position gains = {%i,%i,%i,%i,%i,%i}", gains[0],gains[1],gains[2], \
                                                        gains[3],gains[4],gains[5]);
            ui->textLabel_Gains_p->setText(str);
            tx_cmd_ctrl_p_g(active_slave_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, \
                                    gains[0], gains[1], gains[2]);
             break;
        case 3: //Current
            valid = 1;
            save_ctrl_gains(selected_controller, gains);
            str.sprintf("Current gains = {%i,%i,%i,%i,%i,%i}", gains[0],gains[1],gains[2], \
                                                        gains[3],gains[4],gains[5]);
            ui->textLabel_Gains_i->setText(str);
            numb = tx_cmd_ctrl_i_g(active_slave_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, \
                                gains[0], gains[1], gains[2]);
            break;
        case 4: //Impedance
            valid = 1;
            save_ctrl_gains(selected_controller, gains);
            str.sprintf("Impedance gains = {%i,%i,%i,%i,%i,%i}", gains[0],gains[1],gains[2], \
                                                        gains[3],gains[4],gains[5]);
            ui->textLabel_Gains_z->setText(str);
            tx_cmd_ctrl_z_g(active_slave_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, \
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
    ctrl_setpoint = val;

    //When we move the slider we do not use trapeze, we just "slip" the setpoint
    trap_pos = val;
    trap_posi = val;
    trap_posf = val;
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
            numb = tx_cmd_ctrl_o(active_slave_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, val);
            break;
        case 2: //Position
        case 4: //Impedance
            valid = 1;
            numb = tx_cmd_ctrl_p(active_slave_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, trap_pos, trap_posi, trap_posf, trap_spd, trap_acc);
            qDebug() << "posi = " << trap_posi << ", posf = " << trap_posf << ", spd = " << trap_spd << ", trap_acc = " << trap_acc;
             break;
        case 3: //Current
            valid = 1;
            numb = tx_cmd_ctrl_i(active_slave_1, CMD_WRITE, payload_str, PAYLOAD_BUF_LEN, val, 0);
            break;
        //case 4: //Impedance
            //valid = 0;
            //break;
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

void MainWindow::on_pushButton_toggle_clicked()
{
    //Toggle:
    ctrl_toggle_state ^= 1;

    if(!ctrl_toggle_state)
    {
        //We are in Toggle OFF Mode.
        ui->pushButton_toggle->setText("Toggle ON");
        //Enable GO A & B:
        ui->pushButton_setp_a_go->setEnabled(true);
        ui->pushButton_setp_b_go->setEnabled(true);
        ui->control_setp_a->setEnabled(true);
        ui->control_setp_b->setEnabled(true);

        //Stop timer:
        timer_ctrl->stop();
    }
    else
    {
        //We are in Toggle ON Mode.
        ui->pushButton_toggle->setText("Toggle OFF");
        //Enable GO A & B:
        ui->pushButton_setp_a_go->setEnabled(false);
        ui->pushButton_setp_b_go->setEnabled(false);
        ui->control_setp_a->setEnabled(false);
        ui->control_setp_b->setEnabled(false);

        //Start timer:
        timer_ctrl->start(ui->control_toggle_delayA->text().toInt());
    }
}

void MainWindow::timerCtrlEvent(void)
{
    static uint8_t toggle_output_state = 0;

    toggle_output_state ^= 1;

    //qDebug() << "Control Toggle Timer Event, output = " << toggle_output_state;

    if(toggle_output_state)
    {
        ctrl_setpoint = ui->control_setp_a->text().toInt();
        trap_posi = ui->control_setp_b->text().toInt();
        trap_posf = ui->control_setp_a->text().toInt();
        trap_pos = ctrl_setpoint;

        timer_ctrl->setInterval(ui->control_toggle_delayA->text().toInt());
    }
    else
    {
        ctrl_setpoint = ui->control_setp_b->text().toInt();
        trap_posi = ui->control_setp_a->text().toInt();
        trap_posf = ui->control_setp_b->text().toInt();
        trap_pos = ctrl_setpoint;

        timer_ctrl->setInterval(ui->control_toggle_delayB->text().toInt());
    }

    trap_spd = ui->control_trapeze_spd->text().toInt();
    trap_acc = ui->control_trapeze_acc->text().toInt();

    controller_setpoint(ctrl_setpoint);
}

//Selected controller was changed
void MainWindow::on_comboBox_ctrl_list_currentIndexChanged(int index)
{
    selected_controller = ui->comboBox_ctrl_list->currentIndex();

    switch(selected_controller)
    {
        case 0: //Null
            ui->control_g0->setText("0");
            ui->control_g1->setText("0");
            ui->control_g2->setText("0");
            ui->control_g3->setText("0");
            ui->control_g4->setText("0");
            ui->control_g5->setText("0");
            ui->control_g0->setDisabled(1);
            ui->control_g1->setDisabled(1);
            ui->control_g2->setDisabled(1);
            ui->control_g3->setDisabled(1);
            ui->control_g4->setDisabled(1);
            ui->control_g5->setDisabled(1);
            break;
        case 1: //Open
            ui->control_g0->setText("0");
            ui->control_g1->setText("0");
            ui->control_g2->setText("0");
            ui->control_g3->setText("0");
            ui->control_g4->setText("0");
            ui->control_g5->setText("0");
            ui->control_g0->setDisabled(1);
            ui->control_g1->setDisabled(1);
            ui->control_g2->setDisabled(1);
            ui->control_g3->setDisabled(1);
            ui->control_g4->setDisabled(1);
            ui->control_g5->setDisabled(1);
            break;
        case 2: //Position
            ui->control_g0->setText(QString::number(ctrl_gains[selected_controller][0]));
            ui->control_g1->setText(QString::number(ctrl_gains[selected_controller][1]));
            ui->control_g2->setText(QString::number(ctrl_gains[selected_controller][2]));
            ui->control_g3->setText(QString::number(ctrl_gains[selected_controller][3]));
            ui->control_g4->setText(QString::number(ctrl_gains[selected_controller][4]));
            ui->control_g5->setText(QString::number(ctrl_gains[selected_controller][5]));
            ui->control_g0->setEnabled(1);
            ui->control_g1->setEnabled(1);
            ui->control_g2->setEnabled(1);
            ui->control_g3->setDisabled(1);
            ui->control_g4->setDisabled(1);
            ui->control_g5->setDisabled(1);
            break;

        case 3: //Current
            ui->control_g0->setText(QString::number(ctrl_gains[selected_controller][0]));
            ui->control_g1->setText(QString::number(ctrl_gains[selected_controller][1]));
            ui->control_g2->setText(QString::number(ctrl_gains[selected_controller][2]));
            ui->control_g3->setText(QString::number(ctrl_gains[selected_controller][3]));
            ui->control_g4->setText(QString::number(ctrl_gains[selected_controller][4]));
            ui->control_g5->setText(QString::number(ctrl_gains[selected_controller][5]));
            ui->control_g0->setEnabled(1);
            ui->control_g1->setEnabled(1);
            ui->control_g2->setEnabled(1);
            ui->control_g3->setDisabled(1);
            ui->control_g4->setDisabled(1);
            ui->control_g5->setDisabled(1);
            break;
        case 4: //Impedance
            ui->control_g0->setText(QString::number(ctrl_gains[selected_controller][0]));
            ui->control_g1->setText(QString::number(ctrl_gains[selected_controller][1]));
            ui->control_g2->setText(QString::number(ctrl_gains[selected_controller][2]));
            ui->control_g3->setText(QString::number(ctrl_gains[selected_controller][3]));
            ui->control_g4->setText(QString::number(ctrl_gains[selected_controller][4]));
            ui->control_g5->setText(QString::number(ctrl_gains[selected_controller][5]));
            ui->control_g0->setEnabled(1);
            ui->control_g1->setEnabled(1);
            ui->control_g2->setEnabled(1);
            ui->control_g3->setDisabled(1);
            ui->control_g4->setDisabled(1);
            ui->control_g5->setDisabled(1);
            break;
        case 5: //Custom/other
            ui->control_g0->setText("0");
            ui->control_g1->setText("0");
            ui->control_g2->setText("0");
            ui->control_g3->setText("0");
            ui->control_g4->setText("0");
            ui->control_g5->setText("0");
            ui->control_g0->setDisabled(1);
            ui->control_g1->setDisabled(1);
            ui->control_g2->setDisabled(1);
            ui->control_g3->setDisabled(1);
            ui->control_g4->setDisabled(1);
            ui->control_g5->setDisabled(1);
            break;
        default:
            ui->control_g0->setText("0");
            ui->control_g1->setText("0");
            ui->control_g2->setText("0");
            ui->control_g3->setText("0");
            ui->control_g4->setText("0");
            ui->control_g5->setText("0");
            ui->control_g0->setDisabled(1);
            ui->control_g1->setDisabled(1);
            ui->control_g2->setDisabled(1);
            ui->control_g3->setDisabled(1);
            ui->control_g4->setDisabled(1);
            ui->control_g5->setDisabled(1);
            break;
    }
}

void MainWindow::timerCtrlDispRefreshEvent(void)
{
    if(stream_status)
    {
        ui->disp_meas_val->setText(QString::number(exec1.enc_display));
    }

    if(stream_ricnu_status)
    {
        ui->disp_meas_val->setText(QString::number(ricnu_1.ex.enc_control));
    }
}

