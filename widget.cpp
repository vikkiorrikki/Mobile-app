#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
           ui->drawWidget, SLOT(solve()));
    isTimer = false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_3_clicked()
{
    if(isTimer)
    {
        ui->pushButton->setText("Start");
        isTimer = false;
        timer->stop();
    }
    ui->drawWidget->reCells();
    ui->drawWidget->repaint();
}



void Widget::on_pushButton_clicked()
{
    if(!isTimer)
    {
        ui->pushButton->setText("Pause");
        isTimer = true;
        timer->start(500);
    }
    else
    {
        ui->pushButton->setText("Start");
        isTimer = false;
        timer->stop();
    }
}

void Widget::on_pushButton_2_clicked()
{

    ui->drawWidget->generateRandomCells();
}

void Widget::on_pushButton_4_clicked()
{
    this->close();
}
