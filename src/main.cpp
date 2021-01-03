#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath> // log
#include <queue> //fifo

#include "../include/utilities.h"
#include "../include/bruteForce.h"

int main() {
    srand(time(nullptr)) ;

    char data[DATA_SIZE+1];
    generateData(data, DATA_SIZE, CHANCE_OF_DUPLICATION);

    std::cout<<"Rozmiar danych: "<< DATA_SIZE<<std::endl;
    std::cout<<"Prawdopodobienstwo powtorzenia: "<< CHANCE_OF_DUPLICATION<<"%"<<std::endl;
    std::cout<<data<<std::endl;
    bruteForce(data, strlen(data));
    std::cout<<data<<std::endl;
    return 0;
}
