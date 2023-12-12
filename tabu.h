//
// Created by kacpe on 09.12.2023.
//

#ifndef PEA_2_TABU_H
#define PEA_2_TABU_H
#include <iostream>
#include <limits>
#include <random>
#include "map.h"

using namespace std;
class tabu {
private:
    int INF = INT_MAX/2;
    int numCities;
    int tabuListSize;
    map* graph;
    int* bestSolution;
    int bestCost;
    int** tabuList;
    void printTabuList();

    int* findBestMove(int *solution);

    void generateCandidateList(int *solution);

    int calculateTotalCost(int *solution);

    void randomPermutation(int *arr, int size);

    void initializeSolution(int *solution);

    void copyArray( int *source, int *destination, int size);

    void applyMove(int *solution, int*move);
public:
    tabu(int n);
    tabu(string filename);
    ~tabu();

    void setTabuList(int tabuListSize);

    void printSolution();

    void runTabuSearch(int iterations);
    void show();
};


#endif //PEA_2_TABU_H
