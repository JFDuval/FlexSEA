#include "main.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTimer>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //MainWindow::makePlot();

    //Default settings:
    //=================

    //System:
    ui->tabWidget->setCurrentIndex(0);  //Start at first tab

    //COM port:
    ui->comPortTxt->setText("/dev/ttyACM0");
    ui->comStatusTxt->setText("Type COM port and click 'Open COM'.");
    ui->closeComButton->setDisabled(1); //Not programmed yet.

    //Stream/log:
    ui->streamONbutton->setDisabled(1);
    ui->streamOFFbutton->setDisabled(1);
    ui->openLogButton->setDisabled(1);
    ui->logFileTxt->setText("Not programmed... do not use yet.");

    //=================

    //Timer:
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::makePlot()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();
}
*/

//ToDo this should move to a different file!
void MainWindow::on_openComButton_clicked()
{
    QString str, comport;
    char *comport_char;
    int com_open = 0, tries = 50;

    //Opening statement, and name saving:

    qDebug("Open COM button clicked.");
    comport = ui->comPortTxt->text();
    QByteArray ba = comport.toLatin1();
    comport_char = ba.data();
    str = QString("Opening '") + comport + QString("'...");


    ui->comStatusTxt->setText(str);
    ui->comStatusTxt->repaint();
    ui->openComButton->setDisabled(1);
    ui->openComButton->repaint();

    //Open USB (serial) port:
//ToDo save/use com str
    com_open = flexsea_serial_open_2(comport_char, tries, 50000);
    if(!com_open)
    {
        qDebug("Successfully opened COM port.");
        str += QString(" Success!");

        //Activate Stream button:
        ui->streamONbutton->setEnabled(1);
    }
    else if(com_open == 1)
    {
        qDebug("Tried n times, failed.");
        str += QString(" Tried ") + QString::number(tries) + QString(" times, failed. Right port? Check your permissions.");

        //Reactivate button:
        ui->openComButton->setEnabled(1);
        ui->openComButton->repaint();
    }
    else
    {
        qDebug("Some other error...");
        str += QString(" Unknown error...");

        //Reactivate button:
        ui->openComButton->setEnabled(1);
        ui->openComButton->repaint();
    }

    //Closing statement:
    ui->comStatusTxt->setText(str);
    ui->comStatusTxt->repaint();
}

void MainWindow::on_comPortTxt_textChanged(const QString &arg1)
{
    //com_port_text();
}

void MainWindow::com_port_text()
{
}

void MainWindow::on_streamONbutton_clicked()
{
    ui->streamONbutton->setDisabled(1);
    ui->streamOFFbutton->setEnabled(1);

    ui->streamONbutton->repaint();
    ui->streamOFFbutton->repaint();

    stream_status = 1;
}

void MainWindow::on_streamOFFbutton_clicked()
{
    ui->streamONbutton->setEnabled(1);
    ui->streamOFFbutton->setDisabled(1);

    ui->streamONbutton->repaint();
    ui->streamOFFbutton->repaint();

    stream_status = 0;
}

void MainWindow::stream_1_refresh(QString val1)
{
    ui->disp_accx->setText(val1);
}

void MainWindow::timerEvent(void)
{
    if(stream_status)
    {
        //==========
        //Test: call Stream 1

        int numb = 0;

        //Special1 command to test the ShuoBot Exo

        numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
                                        KEEP, 0, KEEP, 0, 0, 0);
        numb = comm_gen_str(payload_str, comm_str_spi, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;

        flexsea_serial_transmit(numb, comm_str_spi, 0);

        //Can we decode what we received?
        int val = decode_usb_rx();

        if(val == 1)
        {
            qDebug("[Received a valid comm_str!]");
        }
        else if(val == 0)
        {
            qDebug("[No intelligent data received]");
        }
        else
        {
            qDebug("Some other error...");
        }

        //==========
    }
}
