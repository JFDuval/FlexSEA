#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>

namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = 0);
    ~TabWidget();

private:
    Ui::TabWidget *ui;
};

#endif // TABWIDGET_H
