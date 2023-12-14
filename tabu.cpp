//
// Created by kacpe on 09.12.2023.
//

#include <fstream>
#include "tabu.h"


tabu::tabu(int n) {
    srand(time(nullptr));
    bestCost = INT_MAX/2;
    this->n = n;
    this->bestSolution = new int [n];

    this->graph = new map(n);

}

tabu::tabu(string filename) {
    this->graph = new  map(filename);
    this->n = graph->get_size();
    bestCost = INT_MAX/2;
    this->bestSolution = new int [n];
}

int tabu::solve(int iterations) {
    if (bestSolution){
        delete[] bestSolution;
        this->bestSolution = new int [n];
    }

    int* currentSolution = new int [n];
    int* bestMove;
    int currentCost;
    init(currentSolution);
    copyArray(currentSolution, bestSolution, n);
    bestCost = calculate_cost(currentSolution);
    for (int iter = 0; iter < iterations; ++iter) {
        bestMove= find_best_move(currentSolution);

        applyMove(currentSolution, bestMove);

        tabuList[iter % tabu_len] = bestMove;

        currentCost = calculate_cost(currentSolution);
        if (currentCost < bestCost) {
            copyArray(currentSolution, bestSolution, n);
            bestCost = currentCost;
        }
    }
    return bestCost;
}

void tabu::print_solution() {
    std::cout << "Best TSP Solution: ";
    for (int i = 0; i < n; ++i) {
        std::cout << bestSolution[i] << " ";
    }
    std::cout << bestSolution[0] << " "<< std::endl;

    std::cout << "Cost of the best solution: " << bestCost << std::endl;
}

void tabu::init(int* solution) {
    for (int i = 0; i < n; ++i) {
        solution[i] = i;
    }
    permutation(solution, n);
}

void tabu::permutation(int* arr, int size) {
    random_device rd;
    mt19937 g(rd());

    for (int i = size - 1; i > 0; --i) {
        uniform_int_distribution<int> distribution(0, i);
        int j = distribution(g);
        swap(arr[i], arr[j]);
    }
}


int* tabu::find_best_move(int* solution) {
    int* bestMove = new int[2];
    bestMove[0] = 0;
    bestMove[1] = 0;
    int bestCost = INT_MAX/2;

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            bool isTabu = false;

            for (int m = 0; m < tabu_len; ++m) {
                if ((tabuList[m][0] == i and tabuList[m][1] == j) or i == j) {
                    isTabu = true;
                    break;
                }
            }

            if (!isTabu) {
                int* newSolution = new int[n];
                copyArray(solution, newSolution, n);
                swap(newSolution[i], newSolution[j]);

                int newCost = calculate_cost(newSolution);
                if (newCost < bestCost) {
                    bestCost = newCost;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
                delete[] newSolution;
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
    this->tabu_len = tabuListSize;
    if (tabuList){
        for (int i = 0; i < this->tabu_len; ++i) {
            delete[] tabuList[i];
        }
        delete[] tabuList;
    }

    this->tabuList = new int * [tabuListSize];
    for (int i = 0; i < tabuListSize; ++i) {
        this->tabuList[i] = new int [2];
        tabuList[i][0] = -1;
        tabuList[i][1] = -1;
    }
}

int tabu::calculate_cost(int* solution) {
    int cost = 0;
    for (int i = 0; i < n - 1; ++i) {
        cost += graph->get_weight(solution[i],solution[i + 1]);
    }
    cost += graph->get_weight(solution[n - 1], solution[0]);
    return cost;
}


tabu::~tabu() {
    delete graph;
    for (int i = 0; i < tabu_len; ++i) {
        delete[] tabuList[i];
    }
    delete[] tabuList;
    delete[] bestSolution;
}

void tabu::show() {
    this->graph->show();
}

int tabu::get_size() {
    return graph->get_size();
}



