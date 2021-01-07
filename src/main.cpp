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

int main() {
    srand(time(nullptr)) ;

    std::vector<int> data;
    generateData(data, DATA_SIZE, CHANCE_OF_DUPLICATION);
    std::cout<< vToStr(data) <<std::endl;

//    std::vector<int> dataForCGWL = data;
    std::cout<<"Rozmiar danych: "<< data.size()<<std::endl;
    std::cout<<"Prawdopodobienstwo powtorzenia: "<< CHANCE_OF_DUPLICATION<<"%"<<std::endl;


//    bruteForce(data);
//    std::cout<< vToStr(data) << "\n" <<std::endl;
//	std::cout<< vToStr(dataForCGWL) <<std::endl;
//	std::cout << "Number of moves: " << creatingGroupsWithLast(dataForCGWL) <<std::endl;
//	std::cout<< vToStr(dataForCGWL) <<std::endl;




    //const char* arr = "KKKMMMMMCCMMMMCC";
    //data = convertToData(arr, strlen(arr));
    std::cout<< vToStr(data) <<std::endl;
    startFromBeg(data);
    //std::cout<< vToStr(data) <<std::endl;
    std::cout<<"Rozmiar danych: "<< DATA_SIZE<<std::endl;
    std::cout<<"Prawdopodobienstwo powtorzenia: "<< CHANCE_OF_DUPLICATION<<"%"<<std::endl;
    return 0;
}
