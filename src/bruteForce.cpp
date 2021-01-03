//
// Created by demongo on 03.01.2021.
//

#include "../include/bruteForce.h"

#include <cstring>
#include <queue> //fifo

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