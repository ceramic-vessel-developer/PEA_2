#include <iostream>
#include <limits>
#include <random>

using namespace std;

const int INF = numeric_limits<int>::max();
const int MAX_CITIES = 100;

class TabuSearchTSP {
private:
    int numCities;
    int distanceMatrix[MAX_CITIES][MAX_CITIES];
    int bestSolution[MAX_CITIES];
    int bestCost;
    pair<int, int> tabuList[MAX_CITIES];

public:
    TabuSearchTSP(int n, int distances[MAX_CITIES][MAX_CITIES]) : numCities(n), bestCost(INF) {
        for (int i = 0; i < numCities; ++i) {
            for (int j = 0; j < numCities; ++j) {
                distanceMatrix[i][j] = distances[i][j];
            }
        }
    }

    void runTabuSearch(int iterations, int tabuListSize) {
        int currentSolution[MAX_CITIES];

        initializeSolution(currentSolution);
        copyArray(currentSolution, bestSolution, numCities);
        bestCost = calculateTotalCost(currentSolution);

        for (int iter = 0; iter < iterations; ++iter) {
            generateCandidateList(currentSolution, tabuList, tabuListSize);
            pair<int, int> bestMove = findBestMove(currentSolution, tabuList);

            applyMove(currentSolution, bestMove);

            tabuList[iter % tabuListSize] = bestMove;

            int currentCost = calculateTotalCost(currentSolution);
            if (currentCost < bestCost) {
                copyArray(currentSolution, bestSolution, numCities);
                bestCost = currentCost;
            }
        }
    }

    void printSolution() {
        cout << "Best TSP Solution: ";
        for (int i = 0; i < numCities; ++i) {
            cout << bestSolution[i] << " ";
        }
        cout << bestSolution[0] << " ";
        cout << endl;

        cout << "Cost of the best solution: " << bestCost << endl;
    }

private:
    void initializeSolution(int solution[MAX_CITIES]) {
        for (int i = 0; i < numCities; ++i) {
            solution[i] = i;
        }
        randomPermutation(solution, numCities);
    }

    void randomPermutation(int arr[MAX_CITIES], int size) {
        random_device rd;
        mt19937 g(rd());

        for (int i = size - 1; i > 0; --i) {
            uniform_int_distribution<int> distribution(0, i);
            int j = distribution(g);
            swap(arr[i], arr[j]);
        }
    }

    int calculateTotalCost(const int solution[MAX_CITIES]) {
        int cost = 0;
        for (int i = 0; i < numCities - 1; ++i) {
            cost += distanceMatrix[solution[i]][solution[i + 1]];
        }
        cost += distanceMatrix[solution[numCities - 1]][solution[0]]; // Return to the starting city
        return cost;
    }

    void generateCandidateList(const int solution[MAX_CITIES], pair<int, int> tabuList[MAX_CITIES], int tabuListSize) {
        int k = 0;
        for (int i = 1; i < numCities; ++i) {
            for (int j = i + 1; j < numCities; ++j) {
                bool isTabu = false;

                for (int m = 0; m < tabuListSize; ++m) {
                    if (tabuList[m] == make_pair(i, j)) {
                        isTabu = true;
                        break;
                    }
                }

                if (!isTabu) {
                    tabuList[k++] = make_pair(i, j);
                    if (k >= tabuListSize) {
                        return;
                    }
                }
            }
        }
    }

    pair<int, int> findBestMove(const int solution[MAX_CITIES], const pair<int, int> tabuList[MAX_CITIES]) {
        pair<int, int> bestMove;
        int bestCost = INF;

        for (int i = 1; i < numCities; ++i) {
            for (int j = i + 1; j < numCities; ++j) {
                bool isTabu = false;

                for (int m = 0; m < numCities; ++m) {
                    if (tabuList[m] == make_pair(i, j)) {
                        isTabu = true;
                        break;
                    }
                }

                if (!isTabu) {
                    int newSolution[MAX_CITIES];
                    copyArray(solution, newSolution, numCities);
                    swap(newSolution[i], newSolution[j]);

                    int newCost = calculateTotalCost(newSolution);
                    if (newCost < bestCost) {
                        bestCost = newCost;
                        bestMove = make_pair(i, j);
                    }
                }
            }
        }

        return bestMove;
    }

    void applyMove(int solution[MAX_CITIES], const pair<int, int>& move) {
        swap(solution[move.first], solution[move.second]);
    }

    void copyArray(const int source[MAX_CITIES], int destination[MAX_CITIES], int size) {
        for (int i = 0; i < size; ++i) {
            destination[i] = source[i];
        }
    }
};

int main() {
    // Example usage
    int numCities = 4;
    int distanceMatrix[MAX_CITIES][MAX_CITIES] = {
            {0,  1, 15, 20},
            {10, 0,  35, 205},
            {15, 35, 0,  300},
            {20, 25, 30, 0}
    };

    TabuSearchTSP tabuSearch(numCities, distanceMatrix);

    // Number of iterations and tabu list s
    tabuSearch.runTabuSearch(100, 5);
    tabuSearch.printSolution();

    return 0;
}