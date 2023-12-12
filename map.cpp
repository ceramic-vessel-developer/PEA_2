//
// Created by kacpe on 09.10.2023.
//

#include <iostream>
#include <fstream>
#include "map.h"
#include <climits>

map::map(int n) {
    srand(time(nullptr));
    this->n = n;
    this->matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        this->matrix[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) matrix[i][j] = INT_MAX/2;
            else matrix[i][j] = rand()%(INT_MAX/2);
        }
    }
}

map::map(std::string file) {
    std::string path = "../input_files/"+file;
    std::fstream f;
    f.open(path);

    if (f.is_open()){
        f >> this->n;

        this->matrix = new int*[n];
        for (int i = 0; i < n; ++i) {
            this->matrix[i] = new int[n];
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                f >> matrix[i][j];
                if (i == j){
                    matrix[i][j] = INT_MAX/2;
                }
            }
        }
    }
}

map::~map() {
    for (int i = 0; i < this->n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int map::get_weight(int start, int end) {
    return this->matrix[start][end];
}

void map::show() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int map::get_size() {
    return n;
}
