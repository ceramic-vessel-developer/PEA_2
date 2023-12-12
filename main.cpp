#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include "tabu.h"

using namespace std;

void temp();

int main() {
    temp();
    return 0;
}

void temp(){
    string a[] = {"tsp_6_1.txt",
                  "tsp_6_2.txt",
                  "tsp_10.txt",
                  "tsp_12.txt",
                  "tsp_13.txt",
                  "tsp_14.txt",
                  "tsp_15.txt",
                  "tsp_17.txt",
                  "test_4.txt"};
    tabu* test;
    for (int i = 1; i < 9; ++i) {
        test = new tabu(i*100);
        //cout << i << endl;
        // Number of iterations and tabu list s
        test->setTabuList(500);
        test->runTabuSearch(100);
        test->printSolution();
        delete test;
    }
}
