//
// Created by kacpe on 09.12.2023.
//

#ifndef PEA_2_TABU_H
#define PEA_2_TABU_H
#include <iostream>
#include <climits>
#include <random>

using namespace std;
class tabu {
private:
    int INF = INT_MAX/2;
    int numCities;
    int tabuListSize;
    int** distanceMatrix;
    int* bestSolution;
    int bestCost;
    int** tabuList;
public:
    tabu(int n);
    tabu(string filename);
    ~tabu();

    void copyArray( int *source, int *destination, int size);

    void applyMove(int *solution, int*move);

    void setTabuList(int tabuListSize);
    void printTabuList();

    int* findBestMove(int *solution);

    void generateCandidateList(int *solution);

    int calculateTotalCost(int *solution);

    void randomPermutation(int *arr, int size);

    void initializeSolution(int *solution);

    void printSolution();

    void runTabuSearch(int iterations);
};


#endif //PEA_2_TABU_H
