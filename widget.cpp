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

    parseXml();
}
void Widget::parseXml()
{
    QDomDocument domDoc;
    QFile        file("addressbook.xml");

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
                   cells = new int*[tmpCells.size()/2];
                   for(int i = 0; i < tmpCells.size()/2; i = i+2 )
                   {
                       cells[i] = new int[2];
                       cells[i][0] = vec.at(i).toInt();
                       cells[i][1] = vec.at(i+1).toInt();
                   }
                   levels.append(new Levels(id, pop, gen, cells, res, start));
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
