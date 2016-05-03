#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <widgetdraw.h>
#include <levels.h>
#include <QTimer>
#include <QVector>
#include <QFile>
#include <QtXml>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:
    QVector<Levels*> levels;
    bool isTimer;
    QTimer *timer;
    void parseXml();
    void parseLevel(const QDomNode& node);
public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
