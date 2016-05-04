#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <widgetdraw.h>

#include <QTimer>
#include <QVector>
#include <QFile>
#include <QtXml>
#include <QListWidget>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:

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

    void on_pushButton_menu_clicked();

    void changedStok(int val);
    void changedLevel(int id, int pop, int gen, int start);
    void changedCells(int pop, int gen);
    void succes();
    void unsucces();
    void on_pushButton_game_clicked();

    void on_list_levels_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
