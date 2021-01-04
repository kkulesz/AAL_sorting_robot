//
// Created by Konrad Kulesza on 1/4/2021.
//

#include <iostream>
#include <cmath> //pow()
#include "../include/startFromBeg.h"
#include "../include/utilities.h"

static int Cs = 0, Ms = 0, Ys = 0, Ks = 0;

int getNext(std::vector<int>& data, int howManySorted) {
    if(howManySorted<0){
        throw;
    }else if(howManySorted < Cs){
        return C;
    }else if(howManySorted < Cs+Ms){
        return M;
    }else if(howManySorted < Cs+Ms+Ys){
        return Y;
    }else if(howManySorted < Cs+Ms+Ys+Ks){
        return K;
    }else if(howManySorted == Cs+Ms+Ys+Ks){
        std::cout<<"already sorted -- getNext()"<<std::endl;
        return -1;
    }else{
        throw;
    }
}
int getHowManySorted(std::vector<int>& data, int howManySorted){

    for(int i = howManySorted; i<data.size(); ++i){
        int expectedNext = getNext(data, i);
        if(expectedNext != data[i]){
            return i;
        }
    }

    std::cout<<"already sorted -- getHowManySorted()"<<std::endl;
    return data.size();
}

int startFromBeg(std::vector<int>& data){
    // count colors
    for(int color: data){
        if(color == C){
            ++Cs;
        }else if(color == M) {
            ++Ms;
        }else if(color == Y){
            ++Ys;
        }else if(color == K){
            ++Ks;
        }else{
            throw;
        }
    }
    int howManySorted = getHowManySorted(data, 0);
    int lookingFor = getNext(data, howManySorted);

    int maxNumOfIterations = pow(data.size(), 3);
    while(--maxNumOfIterations){
        //look for LookingFor(should be on (4n+1)th place after howManySorted)
        //if he isn't on (4n+1)th place, then think of how to make he be there
        //if he is, then move him to the beginning

        
    }






    return -1;
}

