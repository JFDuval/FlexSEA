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

private:
    int stream_status;
    void makePlot(void);
    QCustomPlot customPlot;
    QTimer *timer;

private slots:

    void on_openComButton_clicked();

    void on_streamONbutton_clicked();

    void on_streamOFFbutton_clicked();

    void timerEvent();

    void on_updateRefreshButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
