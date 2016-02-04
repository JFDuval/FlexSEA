//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// FlexSEA-Execute GUI 0.1
//****************************************************************************

/*
//Note: this project started as 'plan', a CLI C program for the BeagleBone
        Black. It was only using the SPI port. At some point it was modified
        to support 'Native' mode (ie run on a normal computer). The uart/serial
        driver was added at this time. We are now at the 3rd stage: adding
        this Qt Graphical User Interface (GUI), in C++. To make it quick,
        whenever possible the old code was kept: as an example, that's why
        I'm using plan_serial.c/h for the COM port and not Qt's functions.
        There is no doubt that this code is messier than it should; hopefully,
        dear reader, it will motivate you to re-write it! - JF, 2016
*/

//****************************************************************************
// Include(s)
//****************************************************************************

#include "mainwindow.h"
#include <QApplication>
#include <QTime>
#include <QDebug>

//****************************************************************************
// Public Function(s)
//****************************************************************************

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
