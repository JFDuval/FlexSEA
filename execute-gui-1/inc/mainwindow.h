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
#define STREAM_DEFAULT_FREQ     35

//PSoC 4 ADC conversions:
#define P4_ADC_SUPPLY           5.0
#define P4_ADC_MAX              2048
#define P4_T0                   0.5
#define P4_TC                   0.01

//Log:
//======

#define LOG_MIN_FREQ            1
#define LOG_MAX_FREQ            1000
#define LOG_DEFAULT_FREQ        100

//Plot:
//=====

//Axis:
#define INIT_PLOT_LEN           101
#define INIT_PLOT_XMIN          0
#define INIT_PLOT_XMAX          100
#define INIT_PLOT_YMIN          0
#define INIT_PLOT_YMAX          200
#define VAR_NUM                 6
#define PLOT_BUF_LEN            1000

//Refresh:
#define PLOT_DEFAULT_FREQ       35

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
    int stream_status, stream_sa_status, fake_data;

    int plot_buf[PLOT_BUF_LEN]; //ToDo!

    unsigned char usb_rx[256];
    int exp_pwm;

    QTimer *timer_stream, *timer_stream_sa, *timer_log, *timer_plot, *timer_ctrl;
    QSerialPort USBSerialPort;

    int active_slave_1, active_slave_1_index;
    //Lookup from list to actual slave number (FlexSEA convention):
    uint8_t list_to_slave[10];
    QStringList var_list_slaves;

    //Plot:

    //X array never changes after initialization
    int graph_xarray[PLOT_BUF_LEN];
    //We store the graph Y arrays in that variable. 1x 1D array per trace (NUM_VAR)
    int graph_yarray[VAR_NUM][PLOT_BUF_LEN];

    void makePlot(void);
    void refreshPlot(int *x, int *y, int len, uint8_t plot_index);
    int gen_test_data(void);
    QCustomPlot customPlot;
    int plot_xmin, plot_ymin, plot_xmax, plot_ymax, plot_len;

    void gen_graph_xarray(void);
    void init_yarrays(void);
    void update_graph_array(int graph, int new_data);

    void update_plot_buf(int new_data);
    void update_plot_buf_single(int *buf, int *idx, int new_data);

    //Control:
    int wanted_controller = 0, selected_controller = 0, active_controller = 0;
    int trap_pos = 0, trap_posi = 0, trap_posf = 0, trap_spd = 0, trap_acc = 0;
    int ctrl_setpoint = 0;
    int ctrl_toggle_state = 0;
    void controller_setpoint(int val);

    //Stream SA:
    uint8_t bound_number(int num, int min, int max);

    //Serial driver:

    int OpenUSBSerialPort(QString name, int tries, int delay);
    void CloseUSBSerialPort(void);
    int USBSerialPort_Write(char bytes_to_send, unsigned char *serial_tx_data);
    int USBSerialPort_Read(unsigned char *buf);

private slots:

    void on_openComButton_clicked();

    void on_streamONbutton_clicked();

    void on_streamOFFbutton_clicked();

    void timerStreamEvent();

    void timerStream_SA_Event();

    void timerPlotEvent();

    void timerCtrlEvent(void);

    void on_updateRefreshButton_clicked();

    void on_UpdatePlotpushButton_clicked();

    void on_closeComButton_clicked();

    void on_hSlider_PWM_valueChanged(int value);

    void on_pushButton_SetController_clicked();

    void on_pushButton_setp_a_go_clicked();

    void on_pushButton_setp_b_go_clicked();


    void on_pushButton_SetGains_clicked();

    void on_pushButton_CtrlMinMax_clicked();

    void on_hSlider_Ctrl_valueChanged(int value);

    void on_pushButton_toggle_clicked();

    void on_pushButton_ext_pwro_clicked();

    void on_ctrl_encoder_zero_clicked();

    void on_SlaveSelectComboBox_currentIndexChanged(int index);

    void on_stream_SA_ONbutto_clicked();

    void on_stream_SA_OFFbutton_clicked();

    void on_stream_SA_RefreshOffset_clicked();

    void on_comboBox_minm_rgb_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};

//Experimental: TabWidget class
class MainWindowTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    MainWindowTabWidget(QWidget *parent = 0);


public slots:


signals:

private:

};


#endif // MAINWINDOW_H
