#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

const char C = 'C', M = 'M', Y = 'Y', K = 'K';
const int DATA_SIZE = 15;
const int CHANCE_OF_DUPLICATION = 70;

void append(char* base, char suffix){
    int len = strlen(base);
    base[len] = suffix;
    base[len+1] = '\0';
}

void swapAndAppend(char* data, char& degraded, char& upgraded){
    std::swap(degraded, upgraded);
    append(data, degraded);
}

void generateData(char* data ,int size, int chance_of_duplication){
    if( chance_of_duplication < 0 || chance_of_duplication > 100 || size<=0){
        throw;
    }
    memset(data, '\0', 1);
    std::cout<<data<<std::endl;
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
    append(data, privileged);

    while(--size){
        random = rand()%100;
        if(random < chance_of_duplication){
            append(data,privileged);
        }else if(random < chance_of_duplication + chance_of_change/3){
            swapAndAppend(data, privileged, rest[0]);
        }else if( random < chance_of_duplication + 2/3*chance_of_change){
            swapAndAppend(data, privileged, rest[1]);
        }else{
            swapAndAppend(data, privileged, rest[2]);
        }
    }
}

void move4chars(char* data, int index){
    if(index < 0 || index > strlen(data)-5){
        throw;
    }
    int size = strlen(data);
    char* mid = new char[4];
    char* end = new char[size-index-4];

    int beg_len = index;
    int mid_len = 4;
    int end_len = size - index-4;

    //copy_to_tmp array
    strncpy(mid, data+index, mid_len);
    strncpy(end, data+index+mid_len, end_len);

    //copy in different_order
    strncpy(data + beg_len, end, end_len);
    strncpy(data+beg_len+end_len, mid, mid_len);
}

int main() {
    srand(time(NULL)) ;

    char data[DATA_SIZE+1];
    generateData(data, DATA_SIZE, CHANCE_OF_DUPLICATION);

    std::cout<<"PRZED: " << data << std::endl;
    move4chars(data, 3);
    std::cout<<"PO:    " << data << std::endl;
    return 0;
}
