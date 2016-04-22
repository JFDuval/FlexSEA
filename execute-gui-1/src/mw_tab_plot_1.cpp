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
    QPen pen;

    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(plot_xmin, plot_xmax);
    ui->customPlot->yAxis->setRange(plot_ymin, plot_ymax);

    //Add 6 graphs:

    ui->customPlot->addGraph();
    pen.setColor(Qt::red);
    ui->customPlot->graph()->setPen(pen);

    ui->customPlot->addGraph();
    pen.setColor(Qt::magenta);
    ui->customPlot->graph()->setPen(pen);

    ui->customPlot->addGraph();
    pen.setColor(Qt::blue);
    ui->customPlot->graph()->setPen(pen);

    ui->customPlot->addGraph();
    pen.setColor(Qt::cyan);
    ui->customPlot->graph()->setPen(pen);

    ui->customPlot->addGraph();
    pen.setColor(Qt::green);
    ui->customPlot->graph()->setPen(pen);

    ui->customPlot->addGraph();
    pen.setColor(Qt::black);
    ui->customPlot->graph()->setPen(pen);

    ui->customPlot->replot();
}

//makePlot created a plot. We now update its data.
void MainWindow::refreshPlot(int *x, int *y, int len, uint8_t plot_index)
{
    static int graph_ylim[2*VAR_NUM] = {0,0,0,0,0,0,0,0,0,0,0,0};
    //static int graph_ymin[VAR_NUM] = {0,0,0,0,0,0};

    //From array to QVector:
    QVector<double> xdata(len), ydata(len);
    qCopy(x, x+len, xdata.begin());
    qCopy(y, y+len, ydata.begin());

    ui->customPlot->graph(plot_index)->setData(xdata, ydata);

    //ToDo: Modify this code to take the max of all curves!

    //In Automatic mode we constantly adjust the axis:
    if(ui->radioButtonXAuto->isChecked())
    {
        array_minmax(x, len, &plot_xmin, &plot_xmax);

        ui->customPlot->xAxis->setRange(plot_xmin, plot_xmax);
        ui->plot_xmin_lineEdit->setText(QString::number(plot_xmin));
        ui->plot_xmax_lineEdit->setText(QString::number(plot_xmax));
    }
    else
    {
        //X is in manual mode.
    }

    if(ui->radioButtonYAuto->isChecked())
    {
        //Maximum for this graph:
        array_minmax(y, len, &plot_ymin, &plot_ymax);
        //Compare to all others and get max(max(())
        graph_ylim[plot_index] = plot_ymin;
        graph_ylim[plot_index+VAR_NUM] = plot_ymax;
        array_minmax(graph_ylim, 2*VAR_NUM, &plot_ymin, &plot_ymax);
        //Add 5%:
        plot_ymin = (plot_ymin-(abs(plot_ymin)/20));
        plot_ymax = (plot_ymax+(abs(plot_ymax)/20));

        //Set axis 5% above minimum
        ui->customPlot->yAxis->setRange(plot_ymin, plot_ymax);
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

//Returns a new test data point (sine wave)
#define TWO_PI              (2*3.14159)
#define PHASE_INCREMENT     (TWO_PI/75)
#define A_GAIN              1000
int MainWindow::gen_test_data(void)
{
    static double phase = 0.0;
    double res_f = 0;

    phase += PHASE_INCREMENT;
    res_f = A_GAIN * sin(phase);

    return((int)res_f);
}

//All graphs use the same X data. Call this once at startup.
void MainWindow::gen_graph_xarray(void)
{
    for(int i = 0; i < PLOT_BUF_LEN; i++)
    {
        graph_xarray[i] = i; // x goes from 0 to 1
    }
}

//Initialize all the graphs at 0:
void MainWindow::init_yarrays(void)
{
    for(int i = 0; i < VAR_NUM; i++)
    {
        for(int j = 0; j < PLOT_BUF_LEN; j++)
        {
            graph_yarray[i][j] = 0;
        }
    }
}

//Buffer management for the N variables that we can plot.
void MainWindow::update_graph_array(int graph, int new_data)
{
    static int idx_plot[VAR_NUM] = {0,0,0,0,0,0};

    //Updating buffer with one new data point
    update_plot_buf_single(graph_yarray[graph], &idx_plot[graph], new_data);
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
        plot_xmin = ui->plot_xmin_lineEdit->text().toInt(); //Forced to 0, non-editable
        plot_xmax = ui->plot_xmax_lineEdit->text().toInt();
        plot_xmin = 0;  //Just in case.

        //Few safety checks on that number.
        if(plot_xmax >= PLOT_BUF_LEN)
        {
            plot_len = PLOT_BUF_LEN;
            plot_xmax = PLOT_BUF_LEN;
            ui->plot_xmax_lineEdit->setText(QString::number(plot_xmax));;
        }
        else
        {
            plot_len = plot_xmax;
        }
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
    uint8_t data_to_plot[VAR_NUM] = {0,0,0,0,0,0};
    uint8_t index = 0;
    int y[PLOT_BUF_LEN];

    //We go through the list and we update the appropriate data:

    data_to_plot[0] = ui->cBoxvar1->currentIndex();
    data_to_plot[1] = ui->cBoxvar2->currentIndex();
    data_to_plot[2] = ui->cBoxvar3->currentIndex();
    data_to_plot[3] = ui->cBoxvar4->currentIndex();
    data_to_plot[4] = ui->cBoxvar5->currentIndex();
    data_to_plot[5] = ui->cBoxvar6->currentIndex();

    for(index = 0; index < VAR_NUM; index++)
    {
        //Update buffers with latest results:
        switch(data_to_plot[index])
        {
            case 0: //"**Unused**"
                update_graph_array(index, 0);
                break;
            case 1: //"Accel X"
                update_graph_array(index, exec1.accel.x);
                break;
            case 2: //"Accel Y"
                update_graph_array(index, exec1.accel.y);
                break;
            case 3: //"Accel Z"
                update_graph_array(index, exec1.accel.z);
                break;
            case 4: //"Gyro X"
                update_graph_array(index, exec1.gyro.x);
                break;
            case 5: //"Gyro Y"
                update_graph_array(index, exec1.gyro.y);
                break;
            case 6: //"Gyro Z"
                update_graph_array(index, exec1.gyro.z);
                break;
            case 7: //"Encoder"
                update_graph_array(index, exec1.encoder);
                break;
            case 8: //"Motor current"
                update_graph_array(index, exec1.current);
                break;
            case 9: //"Analog[0]"
                update_graph_array(index, (int) exec1.analog[0]);
                break;
            case 10: //"Strain"
                update_graph_array(index, exec1.strain);
                break;
            case 11: //"+VB"
                update_graph_array(index, exec1.volt_batt);
                break;
            case 12: //"+VG"
                update_graph_array(index, exec1.volt_int);
                break;
            case 13: //"Temp"
                update_graph_array(index, exec1.temp);
                break;
            case 14: //"Fake Data"
                update_graph_array(index, gen_test_data());
                break;
            case 15: //"Setpoint"
                update_graph_array(index, ctrl_setpoint);
                break;
        }

        //Copy buffers and plot:
        qCopy(graph_yarray[index], graph_yarray[index] + plot_len, y);
        refreshPlot(graph_xarray, y, plot_len, index);
    }
}
