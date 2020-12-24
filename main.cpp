#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>

const char C = 'C', M = 'M', Y = 'Y', K = 'K';
const int DATA_SIZE = 15;
const int CHANCE_OF_DUPLICATION = 100;


std::string generateData(int size, int chance_of_duplication){
    if( chance_of_duplication < 0 || chance_of_duplication > 100 || size<0){
        throw;
    }
    std::string data = "";
    int chance_of_change = 100 - chance_of_duplication;

    char privileged;
    char rest[3];


    int random = rand()%100;
    if(random <= 25){//choose first privileged and set the rest
        privileged = C;
        rest[0] = M; rest[1] = Y; rest[2] = K;
    }else if(random <= 50){
        privileged = M;
        rest[0] = C; rest[1] = Y; rest[2] = K;
    }else if(random <= 75){
        privileged = Y;
        rest[0] = C; rest[1] = M; rest[2] = K;
    }else{
        privileged = K;
        rest[0] = C; rest[1] = M; rest[2] = Y;
    }

    while(--size){
        int random = rand()%100;
        if(random <= chance_of_duplication){
            data.append(1,privileged);
        }else if(random <= chance_of_duplication + chance_of_change/3){
            data.append(1,rest[0]);
            std::swap(privileged, rest[0]);
        }else if( random <= chance_of_duplication + 2/3*chance_of_change){
            data.append(1,rest[1]);
            std::swap(privileged, rest[1]);
        }else{
            data.append(1,rest[2]);
            std::swap(privileged, rest[2]);
        }
    }
    return std::move(data);
}

int main() {
    srand(time(NULL)) ;

    std::string data = generateData(DATA_SIZE, CHANCE_OF_DUPLICATION);

    std::cout << data << std::endl;
    return 0;
}
