#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

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
    int stream_status;

    QTimer *timer_stream, *timer_log, *timer_plot;

    //Plot:

    void makePlot(void);
    //void refreshPlot(QVector<double> x, QVector<double> y);
    void refreshPlot(int *x, int *y, int len);
    void genTestData(void);
    QCustomPlot customPlot;
    int plot_xmin, plot_ymin, plot_xmax, plot_ymax, plot_len;

private slots:

    void on_openComButton_clicked();

    void on_streamONbutton_clicked();

    void on_streamOFFbutton_clicked();

    void timerStreamEvent();

    void timerPlotEvent();

    void on_updateRefreshButton_clicked();

    void on_UpdatePlotpushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
