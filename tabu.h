//
// Created by kacpe on 09.12.2023.
//

#ifndef PEA_2_TABU_H
#define PEA_2_TABU_H
#include <iostream>
#include <limits>
#include <random>

using namespace std;
class tabu {
private:
    const int INF = std::numeric_limits<int>::max();
    static const int MAX_CITIES = 100;
    int numCities;
    int distanceMatrix[MAX_CITIES][MAX_CITIES];
    int bestSolution[MAX_CITIES];
    int bestCost;
    std::pair<int, int> tabuList[MAX_CITIES];
public:
    tabu(int n);
    tabu(string filename);

    void copyArray(const int *source, int *destination, int size);

    void applyMove(int *solution, const pair<int, int> &move);

    pair<int, int> findBestMove(const int *solution, const pair<int, int> *tabuList);

    void generateCandidateList(const int *solution, pair<int, int> *tabuList, int tabuListSize);

    int calculateTotalCost(const int *solution);

    void randomPermutation(int *arr, int size);

    void initializeSolution(int *solution);

    void printSolution();

    void runTabuSearch(int iterations, int tabuListSize);
};


#endif //PEA_2_TABU_H
