#include "main.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <string>
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    

    //Default settings:
    //=================

    //System:
    ui->tabWidget->setCurrentIndex(0);  //Start at first tab

    //COM port:
    ui->comPortTxt->setText("/dev/ttyACM0");
    ui->comStatusTxt->setText("Type COM port and click 'Open COM'.");
    ui->closeComButton->setDisabled(1); //Not programmed yet.

    //Stream/log:
    stream_status = 0;
    ui->streamONbutton->setDisabled(1);
    ui->streamOFFbutton->setDisabled(1);
    ui->openLogButton->setDisabled(1);
    ui->logFileTxt->setText("Not programmed... do not use yet.");
    ui->streamRefreshTxt->setText("10");
    ui->streamRefreshStatusTxt->setText("Default setting, 10Hz.");
    ui->logRefreshTxt->setText("10");
    ui->logRefreshStatusTxt->setText("Default setting, 10Hz.");

    //Plot:
    plot_len = 101;
    plot_xmin = 0;
    plot_xmax = 100;
    plot_ymin = 0;
    plot_ymax = 200;
    ui->radioButtonXAuto->setChecked(1);
    ui->radioButtonXManual->setChecked(0);
    ui->radioButtonYAuto->setChecked(1);
    ui->radioButtonYManual->setChecked(0);
    ui->plot_xmin_lineEdit->setText(QString::number(plot_xmin));
    ui->plot_xmax_lineEdit->setText(QString::number(plot_xmax));
    ui->plot_ymin_lineEdit->setText(QString::number(plot_ymin));
    ui->plot_ymax_lineEdit->setText(QString::number(plot_ymax));
    makePlot();

    //=================
    //Timers:
    //=================

    //Stream:
    timer_stream = new QTimer(this);
    connect(timer_stream, SIGNAL(timeout()), this, SLOT(timerStreamEvent()));
    timer_stream->start(100);

    //Plot:
    timer_plot = new QTimer(this);
    connect(timer_plot, SIGNAL(timeout()), this, SLOT(timerPlotEvent()));
    timer_plot->start(40);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot()
{
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    //ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(plot_xmin, plot_xmax);
    ui->customPlot->yAxis->setRange(plot_ymin, plot_ymax);
    ui->customPlot->replot();
}

//makePlot created a plot. We now update its data.
void MainWindow::refreshPlot(int *x, int *y, int len)
{
    //From array to QVector:
    QVector<double> xdata(len), ydata(len);
    qCopy(x, x+len, xdata.begin());
    qCopy(y, y+len, ydata.begin());

    ui->customPlot->graph(0)->setData(xdata, ydata);

    //In Automatic mode we constantly adjust the axis:
    if(ui->radioButtonXAuto->isChecked())
    {
        array_minmax(x, len, &plot_xmin, &plot_xmax);

        ui->customPlot->xAxis->setRange(plot_xmin, plot_xmax);
        ui->plot_xmin_lineEdit->setText(QString::number(plot_xmin));
        ui->plot_xmax_lineEdit->setText(QString::number(plot_xmax));
    }

    if(ui->radioButtonYAuto->isChecked())
    {
        array_minmax(y, len, &plot_ymin, &plot_ymax);

        ui->customPlot->yAxis->setRange(plot_ymin, plot_ymax);
        ui->plot_ymin_lineEdit->setText(QString::number(plot_ymin));
        ui->plot_ymax_lineEdit->setText(QString::number(plot_ymax));
    }

    ui->customPlot->replot();
}

void MainWindow::array_minmax(int *arr, int len, int *min, int *max)
{
    (*min) = arr[0];
    (*max) = arr[0];

    for(int i = 0; i < len; i++)
    {
        if(arr[i] < (*min))
            (*min) = arr[i];
        if(arr[i] > (*max))
            (*max) = arr[i];
    }
}

void MainWindow::genTestData(void)
{
    int x[plot_len], y[plot_len];
    static int offset = 0;
    offset+=1;
    if(offset > 100)
        offset = 0;

    for (int i=0; i<plot_len; ++i)
    {
      x[i] = i; // x goes from 0 to 1
      y[i] = i + (offset); // let's plot a quadratic function
    }

    refreshPlot(x, y, plot_len);
}

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

void MainWindow::timerStreamEvent(void)
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

        //Display return status:
        //qDebug() << "decode_usb_rx(): " << val;

        ui->disp_enc->setText(QString::number(exec1.encoder));
        ui->disp_gyrox->setText(QString::number(exec1.imu.x));
        ui->disp_gyroy->setText(QString::number(exec1.imu.y));
        ui->disp_gyroz->setText(QString::number(exec1.imu.z));
        ui->disp_strain->setText(QString::number(exec1.strain));
        ui->disp_ana->setText(QString::number(exec1.analog[0]));
        ui->disp_current->setText(QString::number(exec1.current));
        ui->disp_stat1->setText(QString::number(exec1.status1));
        ui->disp_stat2->setText(QString::number(exec1.status2));

        ui->tabWidget->repaint();

        //==========
    }
}

void MainWindow::timerPlotEvent(void)
{
    //Update plot
    genTestData();  //Test data
}

#define STREAM_MIN_FREQ     1
#define STREAM_MAX_FREQ     1000

void MainWindow::on_updateRefreshButton_clicked()
{
    QString freq_txt, status;
    int period = 0, freq = 0;

    //Get frequency from text box, check limits
    freq_txt = ui->streamRefreshTxt->text();
    freq = freq_txt.toInt();
    if(freq < STREAM_MIN_FREQ)
    {
        status = "Invalid, minimum of " + QString::number(STREAM_MIN_FREQ) + "Hz.";
        ui->streamRefreshStatusTxt->setText(status);
        return;
    }
    else if(freq > STREAM_MAX_FREQ)
    {
        status = "Invalid, maximum of " + QString::number(STREAM_MAX_FREQ) + "Hz.";
        ui->streamRefreshStatusTxt->setText(status);
        return;
    }
    else
    {
        //Valid frequency: compute priod, modify timer.

        period = (1000/freq);   //in ms
        //qDebug() << "Frequency in textbox is: " << freq << "Hz. Associated period (integer): " << period << "ms.";

        status = "f = " + QString::number(freq) + "Hz, integer period = " + QString::number(period) + "ms.";
        ui->streamRefreshStatusTxt->setText(status);
        timer_stream->setInterval(period);
    }
}

void MainWindow::on_UpdatePlotpushButton_clicked()
{
    //X:
    if(ui->radioButtonXManual->isChecked())
    {
        //Manual
        plot_xmin = ui->plot_xmin_lineEdit->text().toInt();
        plot_xmax = ui->plot_xmax_lineEdit->text().toInt();
    }

    //Y:
    if(ui->radioButtonYManual->isChecked())
    {
        //Manual
        plot_ymin = ui->plot_ymin_lineEdit->text().toInt();
        plot_ymax = ui->plot_ymax_lineEdit->text().toInt();
    }

    //Update axis:
    ui->customPlot->xAxis->setRange(plot_xmin, plot_xmax);
    ui->customPlot->yAxis->setRange(plot_ymin, plot_ymax);
}
