#include "levels.h"

Levels::Levels()
{

}
Levels::Levels(int new_id, int new_population, int new_generation, QString new_cells, bool new_result, int new_start)
{
    id = new_id;
    population = new_population;
    generation = new_generation;
    result = new_result;
    start = new_start;
    QStringList list = new_cells.split(" ");
    cells = list.toVector();

}

const QVector<QString> &Levels::getCells()
{
    return cells;
}
int Levels::getGeneration()
{
    return generation;
}
int Levels::getId()
{
    return id;
}
int Levels::getPopulation()
{
    return population;
}
bool Levels::getResult()
{
    return result;
}
int Levels::getStart()
{
    return start;
}
