#ifndef LEVELS_H
#define LEVELS_H


class Levels
{
private:
    int     id;
    int**   cells;
    int     population;
    int     generation;
    int     start;
    bool    result;
public:
    Levels();
    Levels(int new_id, int new_population, int new_generation, int** new_cells, bool new_result, int new_start);
    int**   getCells();
    int     getPopulation();
    int     getGeneration();
    int     getId();
    int     getStart();
    bool    getResult();
};
#endif // LEVELS_H
