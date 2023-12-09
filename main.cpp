#include <iostream>
#include <limits>
#include <random>
#include "tabu.h"

using namespace std;

const int INF = numeric_limits<int>::max();
const int MAX_CITIES = 100;

int main() {
    // Example usage
    int numCities = 4;
    int distanceMatrix[MAX_CITIES][MAX_CITIES] = {
            {0,  1, 15, 20},
            {10, 0,  35, 205},
            {15, 35, 0,  300},
            {20, 25, 30, 0}
    };

    tabu* test = new tabu(numCities,distanceMatrix);

    // Number of iterations and tabu list s
    test->runTabuSearch(100, 5);
    test->printSolution();

    return 0;
}