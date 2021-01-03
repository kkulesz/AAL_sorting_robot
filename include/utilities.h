//
// Created by demongo on 03.01.2021.
//

#ifndef PROJEKT_UTILITIES_H
#define PROJEKT_UTILITIES_H


typedef enum Color{C = 'C', M = 'M', Y = 'Y', K = 'K'} Color;
const int DATA_SIZE = 40;
const int CHANCE_OF_DUPLICATION = 90;

void append(char* base, char suffix);
void swapAndAppend(char* data, char& degraded, char& upgraded);
void generateData(char* data ,int size, const int chance_of_duplication);
void move4chars(char* data, const int index);
bool isSorted(const char* data, const int size);

#endif //PROJEKT_UTILITIES_H
