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
#include <QSerialPort>
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
#define STREAM_DEFAULT_FREQ     25

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
#define VAR_NUM                 6

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
    int plot_buf_accx[1000], plot_buf_accy[1000], plot_buf_accz[1000];
    int plot_buf_gyrx[1000], plot_buf_gyry[1000], plot_buf_gyrz[1000];
    unsigned char usb_rx[256];
    int exp_pwm;

    QTimer *timer_stream, *timer_log, *timer_plot;
    QSerialPort USBSerialPort;

    //Plot:

    void makePlot(void);
    //void refreshPlot(QVector<double> x, QVector<double> y);
    void refreshPlot(int *x, int *y, int len, uint8_t plot_index);
    void genTestData(uint8_t graph);
    QCustomPlot customPlot;
    int plot_xmin, plot_ymin, plot_xmax, plot_ymax, plot_len;

    void update_plot_buf(int new_data);
    void update_plot_buf_single(int *buf, int *idx, int new_data);

    void update_plot_buf_accx(int new_data);
    void update_plot_buf_accy(int new_data);
    void update_plot_buf_accz(int new_data);
    void update_plot_buf_gyrx(int new_data);
    void update_plot_buf_gyry(int new_data);
    void update_plot_buf_gyrz(int new_data);

    void plotEncoder(uint8_t graph);
    void plotAccX(uint8_t graph);
    void plotAccY(uint8_t graph);
    void plotAccZ(uint8_t graph);
    void plotGyrX(uint8_t graph);
    void plotGyrY(uint8_t graph);
    void plotGyrZ(uint8_t graph);


    int OpenUSBSerialPort(QString name, int tries, int delay);
    void CloseUSBSerialPort(void);
    int USBSerialPort_Write(char bytes_to_send, unsigned char *serial_tx_data);
    int USBSerialPort_Read(unsigned char *buf);

private slots:

    void on_openComButton_clicked();

    void on_streamONbutton_clicked();

    void on_streamOFFbutton_clicked();

    void timerStreamEvent();

    void timerPlotEvent();

    void on_updateRefreshButton_clicked();

    void on_UpdatePlotpushButton_clicked();

    void on_closeComButton_clicked();

    void on_hSlider_PWM_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
