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
int find_4th_1(std::vector<int>& data, int howManySorted, int next){
    for(int i = 0; i<data.size()/4; ++i){
        if( next == data[howManySorted + 4*i]){
            return i;//how many moves we need to make to get this element to the sorted position
        }
    }
    return -1;//we cannot find such element
}
int manipulateEnd(std::vector<int>& data, int indexOfNext){
    int howManySorted = getHowManySorted(data, 0);
    int next = getNext(data, howManySorted);

    howManySorted = getHowManySorted(data, 0);
    next = getNext(data, howManySorted);
    int neededMoves = find_4th_1(data, howManySorted, next);
    if(neededMoves > 0){
        return neededMoves;
    }


    int size = data.size();

    while( size-4 < indexOfNext ){
        if(size -1 == indexOfNext){
            move4chars(data, indexOfNext-4);
            indexOfNext = size;
        }else if(size == indexOfNext){
            move4chars(data, indexOfNext-3);
            indexOfNext = size;
        }else if(size == indexOfNext){
            move4chars(data, indexOfNext-2);
            indexOfNext = size;
        }else if(size -4 == indexOfNext){
            move4chars(data, indexOfNext-1);
            indexOfNext = size;
        }

        //in each iteration, it is possible that we will get to correct position
        howManySorted = getHowManySorted(data, 0);
        next = getNext(data, howManySorted);
        int neededMoves = find_4th_1(data, howManySorted, next);
        if(neededMoves > 0){
            return neededMoves;
        }
    }
    return -1;
}
int manipulateUntil_4th_1(std::vector<int>& data, int howManySorted, int next){
    if(data.size() - howManySorted <= 6){
        return -1;//impossible to sort(so far)
    }

    int offsetEnd = (data.size()-howManySorted)%4;

    int indexOfNext = -1;
    for(int i = howManySorted+1; i<data.size(); ++i){
        if(data[i] == next){
            indexOfNext = i;
            break;
        }
    }

    //if it as the end, then we need to manipulate the end
    int neededMoves = manipulateEnd(data,indexOfNext);
    if (neededMoves>0) return neededMoves;

    int offsetStart = indexOfNext - howManySorted;

    //we cannot move it without breaking sorted so far, we need to move it to the end and manipulate it there
    if(offsetEnd == 1 && offsetStart < 3){
        move4chars(data, indexOfNext);
        return manipulateEnd(data, indexOfNext);
    }else if(offsetEnd == 2 && offsetStart< 2){
        move4chars(data, indexOfNext);
        return manipulateEnd(data, indexOfNext);
    }


    //we are somewhere in the middle, move data to the end in that we that it is in the 4th+1 position
    if(offsetEnd == 0){
        move4chars(data, indexOfNext);
        indexOfNext = data.size()-4;
    }else if(offsetEnd == 1){
        move4chars(data, indexOfNext-3);
        indexOfNext = data.size()-1;
    }else if(offsetEnd == 2){
        move4chars(data, indexOfNext-2);
        indexOfNext = data.size()-2;
    }else{
        move4chars(data, indexOfNext-1);
        indexOfNext = data.size()-3;
    }

    //howManySorted = getHowManySorted(data, 0);
    return (indexOfNext-howManySorted)/4;
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
    //std::cout<<howManySorted<<std::endl;
    int old_value = howManySorted;
    int number_of_old_val = 0;

    int maxNumOfIterations = pow(data.size(), 1);
    while(--maxNumOfIterations){
        //look for LookingFor(should be on (4n+1)th place after howManySorted)
        int neededMoves = find_4th_1(data, howManySorted, lookingFor);

        //if he isn't on (4n+1)th place, then think of how to make him be there
        if(neededMoves < 0){
            neededMoves = manipulateUntil_4th_1(data, howManySorted, lookingFor);
        }

        //if he is, then move him to the beginning
        for(int i = 0; i<neededMoves; ++i){
            move4chars(data, howManySorted);
        }

        if(isSorted(data)){
            return 1;
        }


        howManySorted = getHowManySorted(data, 0);
        lookingFor = getNext(data, howManySorted);

//        if(howManySorted == old_value){
//            ++number_of_old_val;
//            if(number_of_old_val >= 2)
//                std::cout<<"STOP"<<std::endl;
//                std::cin>>number_of_old_val;
//        }else{
//            old_value = howManySorted;
//            number_of_old_val = 0;
//        }

    }
    std::cout<<"Too long, probably inf loop"<<std::endl;
    return -1;
}

