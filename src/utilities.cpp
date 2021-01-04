//
// Created by demongo on 03.01.2021.
//


#include "../include/utilities.h"

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <queue> //fifo
#include <algorithm>
#include <sstream>

//void append(std::vector<int> base, int suffix){
//	int len = base.size;
//	base[len] = suffix;
//}

void swapAndAppend(std::vector<int>& data, char& degraded, char& upgraded){
	std::swap(degraded, upgraded);
	data.push_back(degraded);
}

void generateData(std::vector<int>& data, size_t size, const int chance_of_duplication){
	if( chance_of_duplication < 0 || chance_of_duplication > 100 || size<=0){
		throw;
	}

//	std::cout<< vToStr(data) <<std::endl;
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
	data.push_back(privileged);

	while(--size - 1){
		random = rand()%100;
		if(random < chance_of_duplication){
			data.push_back(privileged);
		}else if(random < chance_of_duplication + chance_of_change/3){
			swapAndAppend(data, privileged, rest[0]);
		}else if( random < chance_of_duplication + 2/3*chance_of_change){
			swapAndAppend(data, privileged, rest[1]);
		}else{
			swapAndAppend(data, privileged, rest[2]);
		}
	}
}

void move4chars(std::vector<int>& data, const int index){
	int size = data.size();
	if(index < 0 || index > size-4){
		throw;
	}

	std::vector<int> mid;
	std::vector<int> end;

	mid.resize(size);
	end.resize(size);

	int beg_len = index;
	int mid_len = 4;
	int end_len = size - index-4;

	//copy_to_tmp array
	std::copy_n(data.begin() + index, mid_len, mid.begin());
	std::copy_n(data.begin() + index + mid_len, end_len, end.begin());

	//copy in different_order
	std::copy_n(end.begin(), end_len, data.begin() + beg_len);
	std::copy_n(mid.begin(), mid_len, data.begin() + beg_len + end_len);
}

bool isSorted(std::vector<int> data){
	size_t size = data.size();
	if(size <= 0){
		throw;
	}

	std::vector<int> buff = data;
	std::sort(buff.begin(), buff.end());

	for(int i=0; i<size; i++){
		if( buff[i] != data[i] )
			return false;
	}


	return true;
}

std::string vToStr(std::vector<int> data){
	std::stringstream ss;

	for(auto x: data){
		switch(x){
			case C:
				ss << 'C';
				break;
			case M:
				ss << 'M';
				break;
			case Y:
				ss << 'Y';
				break;
			case K:
				ss << 'K';
				break;
			default:
				throw;
		}
	}

	return ss.str();
}

int heuristicLoss(std::vector<int> data){
	size_t size = data.size();
	if( size <= 0 ){
		throw;
	}

	int loss=0;

	std::vector<int> tmp;
	tmp = data;

	std::sort(tmp.begin(), tmp.end());

	for (int i = 0; i < size; ++i) {
		if( tmp[i] != data[i]){
			++loss;
		}
	}


	return loss;
}
