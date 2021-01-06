#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath> // log
#include <queue> //fifo
#include <vector>

#include "../include/utilities.h"
#include "../include/bruteForce.h"
#include "../include/creatingGroupsWithLast.h"
#include "../include/startFromBeg.h"
#include "../include/fast4Create.h"

int main() {
    srand(time(nullptr)) ;

    std::vector<int> data;
    generateData(data, DATA_SIZE, CHANCE_OF_DUPLICATION);

	std::vector<int> dataForCGWL = data;
	std::vector<int> dataForF4C = data;
    std::cout<<"Rozmiar danych: "<< DATA_SIZE<<std::endl;
    std::cout<<"Prawdopodobienstwo powtorzenia: "<< CHANCE_OF_DUPLICATION<<"%"<<std::endl;


//    bruteForce(data);
//    std::cout<< vToStr(data) << "\n" <<std::endl;
	std::cout<< vToStr(dataForCGWL) <<std::endl;
	std::cout << "Number of moves: " << creatingGroupsWithLast(dataForCGWL, true) <<std::endl;
	std::cout<< vToStr(dataForCGWL) << "\n" <<std::endl;

	std::cout<< vToStr(dataForF4C) <<std::endl;
	std::cout << "Number of moves: " << fast4Create(dataForF4C, true) <<std::endl;
	std::cout<< vToStr(dataForF4C) <<std::endl;


//    const char* arr = "CCCCC";
//    data = convertToData(arr, strlen(arr));
//    startFromBeg(data);
//    std::cout<< vToStr(data) <<std::endl;
    return 0;
}
