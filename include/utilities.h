//
// Created by demongo on 03.01.2021.
//

#ifndef PROJEKT_UTILITIES_H
#define PROJEKT_UTILITIES_H


#include <vector>
#include <string>

typedef enum Color{C, M, Y, K} Color;
const int DATA_SIZE = 40;
const int CHANCE_OF_DUPLICATION = 90;

//void append(std::vector<int>& base, int suffix);
void swapAndAppend(std::vector<int>& data, int& degraded, int& upgraded);
void generateData(std::vector<int>& data, size_t size, const int chance_of_duplication);
void move4chars(std::vector<int>& data, const int index);
bool isSorted(std::vector<int> data);
std::string vToStr(std::vector<int> data);

#endif //PROJEKT_UTILITIES_H
