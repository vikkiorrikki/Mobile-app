#ifndef WIDGETDRAW_H
#define WIDGETDRAW_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QRect>

class widgetDraw : public QWidget
{
    Q_OBJECT

private:
    bool isSandbox;
    int rows, cols;
    bool **cells;
    void deleteCells();
public:
    explicit widgetDraw(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *press);
    ~widgetDraw();

    bool isAlive(int i, int j);

signals:

public slots:
    void reCells();
    void solve();
    void generateRandomCells();
};

#endif // WIDGETDRAW_H
