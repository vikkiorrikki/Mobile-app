#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->drawWidget->setStyleSheet("background-color: rgb(0,0,0);");

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
    on_pushButton_3_clicked();
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_7_clicked()
{
    this->close();
}
//sandbox
void Widget::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
//play
void Widget::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
