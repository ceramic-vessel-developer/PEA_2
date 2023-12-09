//
// Created by kacpe on 09.10.2023.
//

#ifndef PEA_1_MAP_H
#define PEA_1_MAP_H


#include <string>

class map {
private:
    int n;
    int** matrix;
public:
    map(int n);
    map(std::string file);
    ~map();

    int get_weight(int start, int end);
    int get_size();
    void show();
};


#endif //PEA_1_MAP_H
