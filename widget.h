#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <widgetdraw.h>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:
    bool isTimer;
    QTimer *timer;

public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
