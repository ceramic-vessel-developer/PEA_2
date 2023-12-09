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
    for (int i = 0; i < 9; ++i) {


        test = new tabu(a[i]);
        cout << a[i] << endl;
        // Number of iterations and tabu list s
        test->setTabuList(10);
        test->runTabuSearch(1000);
        test->printSolution();
        delete test;
    }
}