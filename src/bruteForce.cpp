//
// Created by demongo on 03.01.2021.
//

#include "../include/bruteForce.h"

#include <cstring>
#include <queue> //fifo

int bruteForce(std::vector<int>& data){
	size_t size = data.size();

	if(size <=4){
		throw;
	}

	std::queue<std::vector<int>> fifo;
	const size_t num_of_children = size-4;
	fifo.push(data);

	int iterations = 0;
	std::vector<int> tmp;
	while(true){
		tmp = fifo.front();
		fifo.pop();

		if(isSorted(tmp)){
			data = tmp;
			while(!fifo.empty()){
				fifo.pop();
			}
			return iterations;
			/*TODO:jeszze wypisać w ilu ruchach się to udało zrobić;
			wystarczy zlogarytmowac liczbe iteracji logarytmem o podstawie "num_of_children"*/
		}

		for(int i=0; i<num_of_children; ++i) {
			std::vector<int> child;
			child = tmp;
			move4chars(child, i);
			fifo.push(child);
		}
		++iterations;
	}


}