#include "widgetdraw.h"
#include <QMouseEvent>
#include <qmath.h>
widgetDraw::widgetDraw(QWidget *parent) : QWidget(parent)
{
    rows = 40;
    cols = 28;
    cells = new bool*[rows];
    for(int r = 0; r < rows; r++)
    {
        cells[r] = new bool[cols];
    }

    for(int r = 0; r< rows; r++)
        for(int c = 0; c<cols; c++)
            cells[r][c] = false;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(solve()));
}
void widgetDraw::start()
{
    timer->setInterval(500);
    timer->start();
    generation = levels.at(current_level)->getGeneration();
}

void widgetDraw::deleteCells()
{
    for (int i = 0; i<rows; i++)
            delete [] cells[i];
    delete [] cells;
}
void widgetDraw::setTempl(const QVector<QString> &_templ)
{

}

void widgetDraw::generateRandomCells()
{
    deleteCells();
    cells = new bool*[rows];
    for(int r = 0; r < rows; r++)
    {
        cells[r] = new bool[cols];
    }

    for(int r = 0; r< rows; r++)
        for(int c = 0; c<cols; c++)
            cells[r][c] = false;

    int n = rand()%(rows*cols);
    for(int i = 0; i < n; i++)
    {
        cells[rand()%rows][rand()%cols] = !cells[rand()%rows][rand()%cols];
    }
    update();
}
void widgetDraw::setCurrentLevel(int val)
{   reCells();
    current_level = val;
    stock = levels.at(val)->getStart();
    if(!isSandbox)
    {
        for(int i = 0; i < levels.at(val)->getCells().size(); i = i+2)
        {
            int k, l;
            k = levels.at(val)->getCells().at(i).toInt();
            l = levels.at(val)->getCells().at(i+1).toInt();
            cells[k][l] = true;
        }
    }

    emit changedLevel(levels.at(val)->getId(), levels.at(val)->getPopulation(), levels.at(val)->getGeneration(), levels.at(val)->getStart());
    update();
}

void widgetDraw::reCells()
{
   deleteCells();
   cells = new bool*[rows];

   for(int r = 0; r < rows; r++)
   {
       cells[r] = new bool[cols];
   }

   for(int r = 0; r< rows; r++)
       for(int c = 0; c<cols; c++)
           cells[r][c] = false;

}

void widgetDraw::mousePressEvent(QMouseEvent *press)
{
    QPoint pos;
    pos = press->pos();

    int width, height, a, b, i, j;
    QRect rect;

    rect = this->rect();
    width = rect.width();
    height = rect.height();
    b = width/cols;
    a = height/rows;

    i = pos.y()/a;
    j = pos.x()/b;

    if(!isSandbox)
    {
            for(int ii = 0; ii < levels.at(current_level)->getCells().size(); ii = ii+2)
            {
                int k, l;
                k = levels.at(current_level)->getCells().at(ii).toInt();
                l = levels.at(current_level)->getCells().at(ii+1).toInt();
                qDebug()<<i<<" "<<j<<" "<<k<<" "<<l;
                if( i == k && j == l )
                    return;
            }

        if(stock > 0 )
        {
            if(!cells[i][j])
                emit changedStock(--stock);
            else
                emit changedStock(++stock);

            cells[i][j] = !cells[i][j];
        }
        else if(stock == 0 && cells[i][j])
        {
            emit changedStock(++stock);
            cells[i][j] = !cells[i][j];
        }
        this->update();
     }
    else
    {
       cells[i][j] = !cells[i][j];
       this->update();
    }
}


void widgetDraw::paintEvent(QPaintEvent *)
{
    QPainter *paint;
    int width, height, a, b;
    QRect rect;
    int count = 0;

    rect = this->rect();
    paint = new QPainter(this);
    width = rect.width();
    height = rect.height();

    a = width/cols;
    b = height/rows;

    paint->setPen(QPen(QColor(Qt::white)));
    paint->setBrush(QBrush(Qt::black));
    for(int y = 0, i = 0; i < rows; y += b, i++)
    {
        for(int x =0, j = 0; j < cols; x += a, j++)
        {
            if(!cells[i][j])
                paint->setBrush(QBrush(Qt::black));
            else{
               paint->setBrush(QBrush(Qt::red));
                count++;
            }
            paint->drawRect(x, y, a, b);

        }
    }
    popul = count;
    delete paint;
}
void widgetDraw::result()
{
    int count = 0;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            if(cells[i][j]) count++;
    if (count == levels.at(current_level)->getPopulation())
        emit succes();
    else
    {
        emit unsucces();
    }
}

void widgetDraw::solve()
{
    if(!isSandbox)
    {
        --generation;
        int count = 0;
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                if(cells[i][j]) count++;
        emit changedCells(count, generation);

        if(generation < 0 || count == 0)
        {
            timer->stop();
            result();
            return;
        }

    }
    bool** tmp;
    tmp = new bool*[rows];
    int changed = 0;

    for(int r = 0; r < rows; r++)
    {
        tmp[r] = new bool[cols];
    }

    for(int r = 0; r< rows; r++)
        for(int c = 0; c<cols; c++)
        {
            tmp[r][c] = isAlive(r, c);
            if(tmp[r][c] != cells[r][c])
                changed++;
        }

    deleteCells();
    cells = tmp;
    update();
}
bool widgetDraw::isAlive(int i, int j)
{
    int count = 0;
    int i_minus = i-1, i_plus = i+1;
    int j_minus = j-1, j_plus = j+1;

    if(i == 0)
        i_minus = rows-1;
    if(i == rows-1)
        i_plus = 0;

    if(j == 0)
        j_minus = cols-1;
    if(j == cols-1)
        j_plus = 0;

    if(cells[i][j])
    {
        if(cells[i_minus][j_minus])
            count++;
        if(cells[i_minus][j])
            count++;
        if(cells[i_minus][j_plus])
            count++;
        if(cells[i][j_minus])
            count++;
        if(cells[i][j_plus])
            count++;
        if(cells[i_plus][j_minus])
            count++;
        if(cells[i_plus][j])
            count++;
        if(cells[i_plus][j_plus])
            count++;

        switch (count) {
        case 2:
        case 3:
            return true;
        default:
            return false;
        }
    }
    else
    {
        if(cells[i_minus][j_minus])
            count++;
        if(cells[i_minus][j])
            count++;
        if(cells[i_minus][j_plus])
            count++;
        if(cells[i][j_minus])
            count++;
        if(cells[i][j_plus])
            count++;
        if(cells[i_plus][j_minus])
            count++;
        if(cells[i_plus][j])
            count++;
        if(cells[i_plus][j_plus])
            count++;

        if( count == 3)
            return true;
        else
            return false;
    }

}

widgetDraw::~widgetDraw()
{
    deleteCells();
}
