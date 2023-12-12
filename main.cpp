#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <windows.h>
#include <fstream>
#include "tabu.h"

using namespace std;

void temp();
void testing();
void tabu_t();
void research();
void tabu_m();
void menu();

int main() {
    menu();
    //temp();
    return 0;
}

void menu(){
    int choice;
    bool error = true;
    while (error) {
        std::cout << "Wybierz funkcjonalnosc programu:\n1)Badania\n2)Testowanie funkcjonalnosci" << std::endl;

        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                research();
                error = false;
                break;
            case 2:
                testing();
                error = false;
                break;
            default:
                std::cout << "Bledna wartosc" << std::endl;
                break;

        }
    }


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


        test->setTabuList(50);
        test->runTabuSearch(10000);

        test->printSolution();
        delete test;
    }
}


void testing(){
    int choice;
    while (true) {
        std::cout << "Wybierz algorytm:\n1)Tabu search\n2))Wyjscie" << std::endl;

        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                tabu_t();
                break;
            case 2:
                return;
            default:
                std::cout << "Bledna wartosc" << std::endl;
                break;

        }
    }

}

void tabu_t(){
    int choice;
    std::string input;
    int input_n,iterations,size;
    int* result;
    tabu* test = nullptr;

    while (true) {
        std::cout << "1)Wprowadz plik z grafem\n2)Wygeneruj graf losowo\n3)Wyswietl graf\n4)Rozwiaz\n5)Wyjscie1" << std::endl;

        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                std::cout << "Wprowadz nazwe pliku" << std::endl;
                std::cin >> input;
                if (test){
                    delete test;
                }
                test = new tabu(input);
                break;
            case 2:
                if (test){
                    delete test;
                }
                std::cout << "Wprowadz liczbe miast" << std::endl;
                std::cin >> input_n;
                test = new tabu(input_n);
                break;
            case 3:
                if (!test){
                    std::cout << "Nie wprowadzono grafu!" << std::endl;
                    break;
                }
                test->show();
                break;
            case 4:
                if (!test){
                    std::cout << "Nie wprowadzono grafu!" << std::endl;
                    break;
                }
                std::cout << "Wprowadz wielkosc listy tabu" << std::endl;
                std::cin >> size;
                std::cout << "Wprowadz liczbe iteracji" << std::endl;
                std::cin >> iterations;
                test->setTabuList(size);
                test->runTabuSearch(iterations);
                test->printSolution();
                break;
            case 5:
                delete test;
                delete result;
                return;
            default:
                std::cout << "Bledna wartosc" << std::endl;
                break;

        }
    }
}

void research(){
    tabu_m();
}

void tabu_m(){
    const int number_of_tests = 25;
    int sizes []= {10,20,30,40,50,60,70,80};
    int tabu_size = 25;
    int iterations = 1000;
    int size;
    long double time = 0;
    long double elapsed_time_double;
    LARGE_INTEGER start_time, end_time, elapsed_time, frequency;
    std::fstream f;
    std::string path = "../output_files/tabu.txt";
    QueryPerformanceFrequency(&frequency);
    f.open(path,std::ios::out);
    f.close();
    for (int i = 0; i < 8; ++i) {
        size = sizes[i];
        for (int j = 0; j < number_of_tests; ++j) {
            std::cout<< "tabu " << i << ' '<< j << std::endl;

            tabu* test = new tabu(size);
            test->setTabuList(tabu_size);
            QueryPerformanceCounter(&start_time);
            test->runTabuSearch(iterations);
            QueryPerformanceCounter(&end_time);

            elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
            elapsed_time_double = static_cast<long double>(elapsed_time.QuadPart);
            elapsed_time_double *= 1000000; // result in microseconds
            elapsed_time_double /= frequency.QuadPart;
            delete test;
            time += elapsed_time_double;
        }
        time = time/number_of_tests;
        f.open(path,std::ios::app);
        f << size << ' ' << time <<  std::endl;
        f.close();
    }
}


