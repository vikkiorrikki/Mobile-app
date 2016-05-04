#ifndef LEVELS_H
#define LEVELS_H
#include<QVector>

class Levels
{
private:
    int     id;
    QVector<QString>    cells;
    int     population;
    int     generation;
    int     start;
    bool    result;
public:
    Levels();
    Levels(int new_id, int new_population, int new_generation, QString new_cells, bool new_result, int new_start);
    const QVector<QString>&   getCells();
    int     getPopulation();
    int     getGeneration();
    int     getId();
    int     getStart();
    bool    getResult();
};
#endif // LEVELS_H
