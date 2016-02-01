#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void stream_1_refresh(QString val1);

private:
    void com_port_text();
    int stream_status = 0;

private slots:

    void on_openComButton_clicked();

    void on_comPortTxt_textChanged(const QString &arg1);

    void on_streamONbutton_clicked();

    void on_streamOFFbutton_clicked();

    void timerEvent();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
