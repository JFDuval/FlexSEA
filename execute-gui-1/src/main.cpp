#include "mainwindow.h"
#include <QApplication>
#include <QTime>

void test_function(MainWindow &ptr);
void delay();



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    /*
    while(1)
    {
        test_function(w);
    }
    */

    return a.exec();
}

void test_function(MainWindow &ptr)
{
    static unsigned char myvar = 0;
    myvar++;
    delay();

    ptr.stream_1_refresh(QString::number(myvar));

    qDebug("Test message");
}

void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
