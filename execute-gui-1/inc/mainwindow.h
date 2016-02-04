//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// MainWindow: Qt GUI Main file
//****************************************************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <QMainWindow>
#include "qcustomplot.h"

//****************************************************************************
// Definition(s):
//****************************************************************************

//Timers:
//======

#define TIM_FREQ_TO_P(f)        (1000/f)    //f in Hz, return in ms

//Stream:
//======

#define STREAM_MIN_FREQ         1
#define STREAM_MAX_FREQ         1000
#define STREAM_DEFAULT_FREQ     100

//Log:
//======

#define LOG_MIN_FREQ         1
#define LOG_MAX_FREQ         1000
#define LOG_DEFAULT_FREQ     100

//Plot:
//=====

//Axis:
#define INIT_PLOT_LEN           101
#define INIT_PLOT_XMIN          0
#define INIT_PLOT_XMAX          100
#define INIT_PLOT_YMIN          0
#define INIT_PLOT_YMAX          200

//Refresh:
#define PLOT_DEFAULT_FREQ       25

//****************************************************************************
// Class(es)
//****************************************************************************

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void array_minmax(int *arr, int len, int *min, int *max);

private:
    int stream_status, fake_data;
    int plot_buf[1000]; //ToDo!

    QTimer *timer_stream, *timer_log, *timer_plot;

    //Plot:

    void makePlot(void);
    //void refreshPlot(QVector<double> x, QVector<double> y);
    void refreshPlot(int *x, int *y, int len);
    void genTestData(void);
    QCustomPlot customPlot;
    int plot_xmin, plot_ymin, plot_xmax, plot_ymax, plot_len;

    void update_plot_buf(int new_data);
    void update_plot_buf_single(int *buf, int *idx, int new_data);
    void plotEncoder(void);

private slots:

    void on_openComButton_clicked();

    void on_streamONbutton_clicked();

    void on_streamOFFbutton_clicked();

    void timerStreamEvent();

    void timerPlotEvent();

    void on_updateRefreshButton_clicked();

    void on_UpdatePlotpushButton_clicked();

    void on_checkBoxFakeData_clicked();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
