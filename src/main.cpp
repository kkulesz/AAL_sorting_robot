#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath> // log
#include <queue> //fifo
#include <vector>

#include "../include/utilities.h"
#include "../include/bruteForce.h"

int main() {
    srand(time(nullptr)) ;

    std::vector<int> data;
    generateData(data, DATA_SIZE, CHANCE_OF_DUPLICATION);

    std::cout<<"Rozmiar danych: "<< DATA_SIZE<<std::endl;
    std::cout<<"Prawdopodobienstwo powtorzenia: "<< CHANCE_OF_DUPLICATION<<"%"<<std::endl;
    std::cout<< vToStr(data) <<std::endl;
    bruteForce(data);
    std::cout<< vToStr(data) <<std::endl;
    return 0;
}
