//
// Created by kacpe on 09.12.2023.
//

#include <fstream>
#include "tabu.h"
using namespace std;
tabu::tabu(int n) {
    srand(time(nullptr));
    bestCost = INF;
    numCities = n;

    this->bestSolution = new int [numCities];

    this->distanceMatrix = new int * [numCities];
    for (int i = 0; i < numCities; ++i) {
        this->distanceMatrix[i] = new int [numCities];
    }


    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numCities; ++j) {
            if (i == j) distanceMatrix[i][j] = INT_MAX/2;
            else distanceMatrix[i][j] = rand()%(INT_MAX/2);
        }
    }
}

tabu::tabu(string filename) {
    std::string path = "../input_files/"+filename;
    bestCost = INF;
    std::fstream f;
    f.open(path);

    if (f.is_open()){
        f >> this->numCities;

        this->bestSolution = new int [numCities];

        this->distanceMatrix = new int * [numCities];
        for (int i = 0; i < numCities; ++i) {
            this->distanceMatrix[i] = new int [numCities];
        }

        for (int i = 0; i < numCities; ++i) {
            for (int j = 0; j < numCities; ++j) {
                f >> distanceMatrix[i][j];
                if (i == j){
                    distanceMatrix[i][j] = INT_MAX/2;
                }
            }
        }
    }
}

void tabu::runTabuSearch(int iterations) {

    int* currentSolution = new int [numCities];

    initializeSolution(currentSolution);
    copyArray(currentSolution, bestSolution, numCities);
    bestCost = calculateTotalCost(currentSolution);

    for (int iter = 0; iter < iterations; ++iter) {
        generateCandidateList(currentSolution);
        //printTabuList();
        int* bestMove = findBestMove(currentSolution);

        applyMove(currentSolution, bestMove);

        tabuList[iter % tabuListSize] = bestMove;

        int currentCost = calculateTotalCost(currentSolution);
        if (currentCost < bestCost) {
            copyArray(currentSolution, bestSolution, numCities);
            bestCost = currentCost;
        }
    }
}

void tabu::printSolution() {
    cout << "Best TSP Solution: ";
    for (int i = 0; i < numCities; ++i) {
        cout << bestSolution[i] << " ";
    }
    cout << bestSolution[0] << " ";
    cout << endl;

    cout << "Cost of the best solution: " << bestCost << endl;
}

void tabu::initializeSolution(int* solution) {
    for (int i = 0; i < numCities; ++i) {
        solution[i] = i;
    }
    randomPermutation(solution, numCities);
}

void tabu::randomPermutation(int* arr, int size) {
    random_device rd;
    mt19937 g(rd());

    for (int i = size - 1; i > 0; --i) {
        uniform_int_distribution<int> distribution(0, i);
        int j = distribution(g);
        swap(arr[i], arr[j]);
    }
}

int tabu::calculateTotalCost(int* solution) {
    int cost = 0;
    for (int i = 0; i < numCities - 1; ++i) {
        cost += distanceMatrix[solution[i]][solution[i + 1]];
    }
    cost += distanceMatrix[solution[numCities - 1]][solution[0]]; // Return to the starting city
    return cost;
}

void tabu::generateCandidateList(int* solution) {
    int k = 0;
    for (int i = 1; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            bool isTabu = false;

            for (int m = 0; m < tabuListSize; ++m) {
                if (tabuList[m][0] == i and tabuList[m][1] == j){ //make_pair(i, j)) {
                    isTabu = true;
                    break;
                }
            }

            if (!isTabu) {
                //tabuList[k++] = make_pair(i, j);
                tabuList[k][0] = i;
                tabuList[k][1] = j;
                k++;
                if (k >= tabuListSize) {
                    return;
                }
            }
        }
    }
}

int* tabu::findBestMove(int* solution) {
    int* bestMove = new int[2];
    bestMove[0] = 0;
    bestMove[1] = 0;
    int bestCost = INF;

    for (int i = 1; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            bool isTabu = false;

            for (int m = 0; m < tabuListSize; ++m) {
                if (tabuList[m][0] == i and tabuList[m][1] == j) {
                    isTabu = true;
                    break;
                }
            }

            if (!isTabu) {
                int* newSolution = new int[numCities];
                copyArray(solution, newSolution, numCities);
                swap(newSolution[i], newSolution[j]);

                int newCost = calculateTotalCost(newSolution);
                if (newCost < bestCost) {
                    bestCost = newCost;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }

    return bestMove;
}

void tabu::applyMove(int* solution, int* move) {
    swap(solution[move[0]], solution[move[1]]);
}

void tabu::copyArray( int* source, int* destination, int size) {
    for (int i = 0; i < size; ++i) {
        destination[i] = source[i];
    }
}

void tabu::setTabuList(int tabuListSize) {
    this->tabuListSize = tabuListSize;
    this->tabuList = new int * [tabuListSize];
    for (int i = 0; i < tabuListSize; ++i) {
        this->tabuList[i] = new int [2];
        tabuList[i][0] = -1;
        tabuList[i][1] = -1;
    }
}

void tabu::printTabuList() {
    for (int i = 0; i < tabuListSize; ++i) {
        cout << "{" << tabuList[i][0] << ", " << tabuList[i][1] << "}" << endl;
    }
}

tabu::~tabu() {
    for (int i = 0; i < numCities; ++i) {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
    for (int i = 0; i < tabuListSize; ++i) {
        delete[] tabuList[i];
    }
    delete[] tabuList;
    delete[] bestSolution;
}



