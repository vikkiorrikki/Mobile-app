#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->drawWidget->setStyleSheet("background-color: rgb(0,0,0);");
    connect(ui->widget, SIGNAL(changedLevel(int,int,int,int)), this, SLOT(changedLevel(int,int,int,int)));
    connect(ui->widget, SIGNAL(changedStock(int)), this, SLOT(changedStok(int)));
    connect(ui->widget, SIGNAL(changedCells(int,int)), this, SLOT(changedCells(int,int)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
           ui->drawWidget, SLOT(solve()));
    connect(ui->widget, SIGNAL(succes()), this, SLOT(succes()));
    connect(ui->widget, SIGNAL(unsucces()), this, SLOT(unsucces()));
    isTimer = false;

    parseXml();

    ui->widget->isSandbox = false;
    ui->drawWidget->isSandbox = true;
}

void Widget::succes()
{
    ui->label_goal->setText("Well done!");
    ui->label_gener->clear();
    ui->label_pop->clear();
    ui->label_stock->clear();
    ui->label_current_gen->clear();
    ui->label_current_pop->clear();
    qDebug()<<ui->list_levels->count();
    qDebug()<<ui->widget->current_level;
    if(ui->list_levels->count() > ui->widget->current_level+1)
        ui->pushButton_game->setText("Next");
    else
        ui->pushButton_game->setText("To levels list");
}
void Widget::unsucces()
{
    ui->pushButton_game->setText("Repeat");
    ui->label_goal->setText("Try again...");
    ui->label_gener->clear();
    ui->label_pop->clear();
    ui->label_stock->clear();
    ui->label_current_gen->clear();
    ui->label_current_pop->clear();
}

void Widget::parseXml()
{
    QDomDocument domDoc;
    QFile        file(":/lvl/levels");

    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            parseLevel(domElement);
        }
        file.close();
    }
}
void Widget::parseLevel(const QDomNode &node)
{
    int id, pop, gen, start;
    bool res;
    QString tmpCells;
    QStringList list;
    QVector<QString> vec;
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "level") {
                   id = domElement.attribute("id").toInt();
                   pop = domElement.attribute("population").toInt();
                   gen = domElement.attribute("generation").toInt();
                   start = domElement.attribute("start").toInt();
                   res = domElement.attribute("result").toInt();

                   tmpCells = domElement.attribute("cells");
                   list = tmpCells.split(" ");
                   vec = list.toVector();

                   int **cells;
                   cells = new int*[vec.size()/2];
                   for(int i = 0, j = 0; i < vec.size()/2; j = j+2, i++ )
                   {
                       cells[i] = new int[2];
                       cells[i][0] = vec.at(j).toInt();
                       cells[i][1] = vec.at(j+1).toInt();
                   }
                   qDebug()<< "Level "<<id<<" pop "<<pop<<" gen "<< gen;
                   ui->widget->levels.append(new Levels(id, pop, gen, tmpCells, res, start));
                   ui->list_levels->addItem("Level "+QString::number(id));
               }
           }
        }
        parseLevel(domNode);
        domNode = domNode.nextSibling();
     }
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

    ui->stackedWidget->setCurrentIndex(3);
}
//play
void Widget::on_pushButton_5_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
}
void Widget::changedCells(int pop, int gen)
{
    ui->label_current_pop->setText(QString::number(pop)+" population");
    ui->label_current_gen->setText(QString::number(gen)+" generation left");
}

void Widget::changedStok(int val)
{
    ui->label_stock->setText("for "+QString::number(val)+" cells");
}
void Widget::changedLevel(int id, int pop, int gen, int start)
{
    ui->label_goal->setText("Level #"+QString::number(id)+" Goal: ");
    ui->label_pop->setText(QString::number(pop)+" population");
    ui->label_gener->setText("after "+QString::number(gen)+" generation");
    ui->label_stock->setText("of "+QString::number(start)+" cells");
}

void Widget::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_game_clicked()
{
    if(ui->pushButton_game->text() == "Start")
        ui->widget->start();
    if(ui->pushButton_game->text() == "Repeat")
    {
        ui->widget->setCurrentLevel(ui->widget->current_level);
        ui->pushButton_game->setText("Start");
    }
    if(ui->pushButton_game->text() == "Next")
    {
        ui->pushButton_game->setText("Start");
        ui->widget->setCurrentLevel(ui->widget->current_level+1);
    }
     if(ui->pushButton_game->text() == "To levels list")
         ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_list_levels_itemDoubleClicked(QListWidgetItem *item)
{
    ui->pushButton_game->setText("Start");
    int tmp;
    tmp = ui->list_levels->currentIndex().row();
    ui->widget->setCurrentLevel(tmp);
    ui->stackedWidget->setCurrentIndex(2);
}
