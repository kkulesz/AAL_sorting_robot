#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath> // log
#include <queue> //fifo

const char C = 'C', M = 'M', Y = 'Y', K = 'K';
const int DATA_SIZE = 40;
const int CHANCE_OF_DUPLICATION = 90;

void append(char* base, char suffix){
    int len = strlen(base);
    base[len] = suffix;
    base[len+1] = '\0';
}

void swapAndAppend(char* data, char& degraded, char& upgraded){
    std::swap(degraded, upgraded);
    append(data, degraded);
}

void generateData(char* data ,int size, const int chance_of_duplication){
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

    while(--size - 1){
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

void move4chars(char* data, const int index){
    int size = strlen(data);
    if(index < 0 || index > size-4){
        throw;
    }
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

bool isSorted(const char* data, const int size){
    if(data == nullptr || size <= 0){
        throw;
    }

    bool notSorted= false;
    int i=1;
    while(i != size) {
        char current = data[i];
        char previous = data[i - 1];

        if (current == C) {
            if (previous == M || previous == Y || previous == K)  {
                notSorted = true;
            }
        }else if( current == M) {
            if (previous == Y || previous == K) {
                notSorted = true;
            }
        }else if( current == Y) {
            if (previous == K) {
                notSorted = true;
            }
        }

        if(notSorted) {
            return false;
        }
        ++i;
    }
    return true;
}

int bruteForce(char* data, const int size){
    if(data == nullptr || size <=4){
        throw;
    }
    std::queue<char*> fifo;
    const int num_of_children = size-4;
    fifo.push(data);
    int iterations = 0;
    char* tmp = new char[size];
    while(true){
        strncpy(tmp, fifo.front(), size);
        delete [] fifo.front();
        fifo.pop();


        if(isSorted(tmp, size)){
            strncpy(data, tmp, size);
            while(!fifo.empty()){
                delete[] fifo.front();
                fifo.pop();
            }
            return iterations;
            /*TODO:jeszze wypisać w ilu ruchach się to udało zrobić;
            wystarczy zlogarytmowac liczbe iteracji logarytmem o podstawie "num_of_children"*/
        }

        for(int i=0; i<num_of_children; ++i) {
            char *child = new char[size];
            strncpy(child, tmp, size);
            move4chars(child, i);
            fifo.push(child);
        }
        ++iterations;
    }


}

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
