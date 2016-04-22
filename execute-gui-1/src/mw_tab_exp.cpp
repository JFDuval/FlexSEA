//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Experiments
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

//Motor PWM slider:
void MainWindow::on_hSlider_PWM_valueChanged(int value)
{
    //PWM will be used by the stream user 1 command:
    exp_pwm = ui->hSlider_PWM->value();
    ui->disp_MotPWM->setText(QString::number(exp_pwm));
}

