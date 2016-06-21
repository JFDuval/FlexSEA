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

void MainWindow::init_tab_plot_1(void)
{
    //Axis, limits, etc.:
    //=====================

    plot_len = INIT_PLOT_LEN;
    plot_xmin = INIT_PLOT_XMIN;
    plot_xmax = INIT_PLOT_XMAX;
    plot_ymin = INIT_PLOT_YMIN;
    plot_ymax = INIT_PLOT_YMAX;
    ui->radioButtonXAuto->setChecked(1);
    ui->radioButtonXManual->setChecked(0);
    ui->radioButtonYAuto->setChecked(1);
    ui->radioButtonYManual->setChecked(0);
    ui->plot_xmin_lineEdit->setText(QString::number(plot_xmin));
    ui->plot_xmax_lineEdit->setText(QString::number(plot_xmax));
    ui->plot_ymin_lineEdit->setText(QString::number(plot_ymin));
    ui->plot_ymax_lineEdit->setText(QString::number(plot_ymax));
    for(int h = 0; h < VAR_NUM; h++)
    {
        data_to_plot[h] = 0;
    }

    //Data fields and variables:
    //==========================

    gen_graph_xarray();
    init_yarrays();
    makePlot();
    //Variable option lists:
    QStringList var_list;
    var_list << "**Unused**" << "Accel X" << "Accel Y" << "Accel Z" << "Gyro X" << "Gyro Y" << "Gyro Z" << "Encoder" \
            << "Motor current" << "Analog[0]" << "Strain" << "+VB" << "+VG" << "Temperature" << "Fake Data" << "Setpoint (square)" \
            << "Setpoint (trapezoidal)" << "Strain ch1" << "Strain ch2" << "Strain ch3" << "Strain ch4" << "Strain ch5" << "Strain ch6" \
            << "AS5047 (Mot.)" << "AS5048B (Joint)";
    for(int index = 0; index < var_list.count(); index++)
    {
        //All boxes have the same list:
        ui->cBoxvar1->addItem(var_list.at(index));
        ui->cBoxvar2->addItem(var_list.at(index));
        ui->cBoxvar3->addItem(var_list.at(index));
        ui->cBoxvar4->addItem(var_list.at(index));
        ui->cBoxvar5->addItem(var_list.at(index));
        ui->cBoxvar6->addItem(var_list.at(index));
    }
    //Color coded labels:
    ui->label_t1->setStyleSheet("QLabel { background-color: red; color: black;}");
    ui->label_t2->setStyleSheet("QLabel { background-color: magenta; color: black;}");
    ui->label_t3->setStyleSheet("QLabel { background-color: blue; color: white;}");
    ui->label_t4->setStyleSheet("QLabel { background-color: cyan; color: black;}");
    ui->label_t5->setStyleSheet("QLabel { background-color: lime; color: black;}");
    ui->label_t6->setStyleSheet("QLabel { background-color: black; color: white;}");

    //Slaves:
    QStringList slave_list;
    slave_list << "Exec1" << "Exec2";
    for(int index = 0; index < slave_list.count(); index++)
    {
        //All boxes have the same list:
        ui->cBoxvar1slave->addItem(slave_list.at(index));
        ui->cBoxvar2slave->addItem(slave_list.at(index));
        ui->cBoxvar3slave->addItem(slave_list.at(index));
        ui->cBoxvar4slave->addItem(slave_list.at(index));
        ui->cBoxvar5slave->addItem(slave_list.at(index));
        ui->cBoxvar6slave->addItem(slave_list.at(index));
    }
}

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
        //Unusued channels (index == 0) aren't used for the automatic gain
        if(data_to_plot[plot_index] == 0)
        {
            //qDebug() << "Ch[" << plot_index << "] is Unused.";

            //Unused channel. We take the min & max from used channels.
            int u = 0;
            for(int k= 0; k < VAR_NUM; k++)
            {
                //Grab min & max from any used channel
                if(data_to_plot[k] != 0)
                {
                    plot_ymin = graph_ylim[k];
                    plot_ymax = graph_ylim[k+VAR_NUM];
                }
                else
                {
                    u++;
                }
            }

            if(u == VAR_NUM)
            {
                //All unused, force to 0:
                plot_ymin = -10;
                plot_ymax = 10;
            }
            //qDebug() << "Min/Max =" << plot_ymin << "," << plot_ymax;
        }
        else
        {
            //Limits for this graph:
            array_minmax(y, len, &plot_ymin, &plot_ymax);
            //qDebug() << "Ch[" << plot_index << "] is used.";
        }

        //Compare to all others and get max(max(())
        graph_ylim[plot_index] = plot_ymin;
        graph_ylim[plot_index+VAR_NUM] = plot_ymax;

        //qDebug() << "Min/Max =" << plot_ymin << "," << plot_ymax;

        array_minmax(graph_ylim, 2*VAR_NUM, &plot_ymin, &plot_ymax);

        //Add 5%:
        plot_ymin = (plot_ymin-(abs(plot_ymin)/20));
        plot_ymax = (plot_ymax+(abs(plot_ymax)/20));

        //Set axis 5% above minimum
        ui->customPlot->yAxis->setRange(plot_ymin, plot_ymax);
        ui->plot_ymin_lineEdit->setText(QString::number(plot_ymin));
        ui->plot_ymax_lineEdit->setText(QString::number(plot_ymax));
    }
    //qDebug() << "Final Min/Max =" << plot_ymin << "," << plot_ymax;
    //qDebug() << "";

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
    uint8_t index = 0;
    int y[PLOT_BUF_LEN];
    struct execute_s *execute_ptr;

    //We go through the list and we update the appropriate data:

    data_to_plot[0] = ui->cBoxvar1->currentIndex();
    data_to_plot[1] = ui->cBoxvar2->currentIndex();
    data_to_plot[2] = ui->cBoxvar3->currentIndex();
    data_to_plot[3] = ui->cBoxvar4->currentIndex();
    data_to_plot[4] = ui->cBoxvar5->currentIndex();
    data_to_plot[5] = ui->cBoxvar6->currentIndex();

    for(index = 0; index < VAR_NUM; index++)
    {
        //Point to the selected slave:
        assign_execute_ptr(&execute_ptr, select_plot_slave(index));

        //Update buffers with latest results:
        switch(data_to_plot[index])
        {
            case 0: //"**Unused**"
                update_graph_array(index, 0);
                break;
            case 1: //"Accel X"
                update_graph_array(index, execute_ptr->accel.x);
                break;
            case 2: //"Accel Y"
                update_graph_array(index, execute_ptr->accel.y);
                break;
            case 3: //"Accel Z"
                update_graph_array(index, execute_ptr->accel.z);
                break;
            case 4: //"Gyro X"
                update_graph_array(index, execute_ptr->gyro.x);
                break;
            case 5: //"Gyro Y"
                update_graph_array(index, execute_ptr->gyro.y);
                break;
            case 6: //"Gyro Z"
                update_graph_array(index, execute_ptr->gyro.z);
                break;
            case 7: //"Encoder"
                update_graph_array(index, execute_ptr->enc_display);
                break;
            case 8: //"Motor current"
                update_graph_array(index, execute_ptr->current);
                break;
            case 9: //"Analog[0]"
                update_graph_array(index, (int) execute_ptr->analog[0]);
                break;
            case 10: //"Strain"
                update_graph_array(index, execute_ptr->strain);
                break;
            case 11: //"+VB"
                update_graph_array(index, execute_ptr->volt_batt);
                break;
            case 12: //"+VG"
                update_graph_array(index, execute_ptr->volt_int);
                break;
            case 13: //"Temp"
                update_graph_array(index, execute_ptr->temp);
                break;
            case 14: //"Fake Data"
                update_graph_array(index, gen_test_data());
                break;
            case 15: //"Setpoint (square)"
                update_graph_array(index, ctrl_setpoint);
                break;
            case 16: //"Setpoint (trap)"
                update_graph_array(index, ctrl_setpoint_trap);
                break;
            case 17: //"Strain ch1"
                update_graph_array(index, strain[0].strain_filtered);
                break;
            case 18: //"Strain ch2"
                update_graph_array(index, strain[1].strain_filtered);
                break;
            case 19: //"Strain ch3"
                update_graph_array(index, strain[2].strain_filtered);
                break;
            case 20: //"Strain ch4"
                update_graph_array(index, strain[3].strain_filtered);
                break;
            case 21: //"Strain ch5"
                update_graph_array(index, strain[4].strain_filtered);
                break;
            case 22: //"Strain ch6"
                update_graph_array(index, strain[5].strain_filtered);
                break;
            case 23: //"AS5047 (Mot.)"
                update_graph_array(index, ricnu_1.ex.enc_commut);
                break;
            case 24: //"AS5048 (Joint)"
                update_graph_array(index, ricnu_1.ex.enc_control);
                break;
        }

        //Copy buffers and plot:
        qCopy(graph_yarray[index], graph_yarray[index] + plot_len, y);
        refreshPlot(graph_xarray, y, plot_len, index);
    }
}

//What slave are we plotting for this variable?
uint8_t MainWindow::select_plot_slave(uint8_t index)
{
    uint8_t retval = 0;

    switch(index)
    {
        case 0:
            retval = ui->cBoxvar1slave->currentIndex();
            break;
        case 1:
            retval = ui->cBoxvar2slave->currentIndex();
            break;
        case 2:
            retval = ui->cBoxvar3slave->currentIndex();
            break;
        case 3:
            retval = ui->cBoxvar4slave->currentIndex();
            break;
        case 4:
            retval = ui->cBoxvar5slave->currentIndex();
            break;
        case 5:
            retval = ui->cBoxvar6slave->currentIndex();
            break;
    }

    return retval;
}
