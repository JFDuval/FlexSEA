//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Plot 1 (Encoder test)
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

void MainWindow::makePlot()
{
    // create graph and assign data to it:
    ui->customPlot->addGraph();
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

        ui->customPlot->yAxis->setRange(plot_ymin-10, plot_ymax+10);
        ui->plot_ymin_lineEdit->setText(QString::number(plot_ymin));
        ui->plot_ymax_lineEdit->setText(QString::number(plot_ymax));
    }

    ui->customPlot->replot();
}

//Returns the min and max of an array. Used for the auto axis
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

//Test data, to showcase Plot when no COM port is available
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

//Plot the encoder value
void MainWindow::plotEncoder(void)
{
    int x[plot_len], y[plot_len];

    //Generate x index - ToDo optimize
    for (int i=0; i<plot_len; ++i)
    {
      x[i] = i; // x goes from 0 to 1
    }

    //Get new datapoint from Stream:
    update_plot_buf(exec1.encoder);
    qCopy(plot_buf, plot_buf+plot_len, y);

    refreshPlot(x, y, plot_len);
}

void MainWindow::update_plot_buf(int new_data)
{
    static int idx_plot = 0;

    //Updating buffer with one new data point
    update_plot_buf_single(plot_buf, &idx_plot, new_data);

}

//Add one byte to the FIFO buffer
//Do not call that function directly
void MainWindow::update_plot_buf_single(int *buf, int *idx, int new_data)
{
    uint32_t i = 0;

    if((*idx) < plot_len)
    {
        //Buffer isn't full yet, no need to discard "old" bytes
        buf[(*idx)] = new_data;
        (*idx)++;
    }
    else
    {
        //Shift buffer to clear one spot
        for(i = 1; i < plot_len; i++)
        {
            buf[i-1] = buf[i];
        }
        //Add last byte to the buffer
        buf[plot_len-1] = new_data;
    }

    //buf[] is now up to date
}

//Manual axis change requested
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

void MainWindow::timerPlotEvent(void)
{
    //Update plot
    if(fake_data)
    {
        genTestData();  //Test data
    }
    else
    {
        plotEncoder();
    }
}

void MainWindow::on_checkBoxFakeData_clicked()
{
    if(ui->checkBoxFakeData->isChecked())
        fake_data = 1;
    else
        fake_data = 0;
}
