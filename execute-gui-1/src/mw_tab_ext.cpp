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

