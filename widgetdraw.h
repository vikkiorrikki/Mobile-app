#ifndef WIDGETDRAW_H
#define WIDGETDRAW_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QRect>
#include <levels.h>
#include <QTimer>
class widgetDraw : public QWidget
{
    Q_OBJECT

private:
    QTimer *timer;
    int rows, cols;
    int generation;
    int popul;
    int stock;
    bool **cells;
    void deleteCells();
public:
    int current_level;
    QVector<Levels*> levels;
    explicit widgetDraw(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *press);
    ~widgetDraw();
    void setTempl(const QVector<QString> &_templ);
    bool isAlive(int i, int j);
    bool isSandbox;
    void setCurrentLevel(int val);
    void start();
    void result();
signals:
    void changedCells(int pop, int gen);
    void changedLevel(int id, int pop, int gen, int start);
    void changedStock(int val);
    void succes();
    void unsucces();
public slots:
    void reCells();
    void solve();
    void generateRandomCells();
};

#endif // WIDGETDRAW_H
