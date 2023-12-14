//
// Created by kacpe on 09.12.2023.
//

#ifndef PEA_2_TABU_H
#define PEA_2_TABU_H
#include <iostream>
#include <climits>
#include <random>
#include "map.h"

using namespace std;
class tabu {
private:
    int n;
    int tabu_len;
    map* graph;
    int* bestSolution;
    int bestCost;
    int** tabuList = nullptr;

    int* find_best_move(int *solution);
    int calculate_cost(int *solution);
    void permutation(int *arr, int size);
    void init(int *solution);
    void copyArray( int *source, int *destination, int size);
    void applyMove(int *solution, int *move);
public:
    tabu(int n);
    tabu(string filename);
    ~tabu();

    void setTabuList(int tabuListSize);
    void print_solution();
    int solve(int iterations);




    void show();
    int get_size();
};


#endif //PEA_2_TABU_H
