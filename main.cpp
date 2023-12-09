#include <iostream>
#include <limits>
#include <random>
#include "tabu.h"

using namespace std;

const int INF = numeric_limits<int>::max();
const int MAX_CITIES = 100;

int main() {

    tabu* test = new tabu("test_4.txt");

    // Number of iterations and tabu list s
    test->runTabuSearch(100, 5);
    test->printSolution();

    return 0;
}