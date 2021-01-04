//
// Created by demongo on 04.01.2021.
//
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include "../include/creatingGroupsWithLast.h"
#include "../include/utilities.h"


int heuristicLossCGWL(std::vector<int> data){

	int prev = data[0];
	int curr = data[1];

	int counter=0;
	if( prev != curr ){
		counter++;
	}
	for(int i=2; i<data.size(); i++){
		prev = curr;
		curr = data[i];

		if( prev != curr ){
			counter++;
		}
	}

	return counter;
}


bool worthSearching(std::vector<int> data){

	static int attempts = 0;
	static int prevLoss = 0;
	static int loss = 0;
	static bool somethingWrong = false;
	static std::vector<std::vector<int>> buffer;

	prevLoss = loss;
	loss = heuristicLossCGWL(data);

	if( loss > prevLoss ){
		attempts++;
		somethingWrong = true;
		buffer.push_back(data);
	} else if(somethingWrong){
		attempts++;
	}

	if(attempts > 10){
		somethingWrong = false;

//		auto it = std::unique( buffer.begin(), buffer.end() );
//		bool sameFound = !( it == buffer.end() );

		std::set<std::vector<int>> s(buffer.begin(), buffer.end());
		bool sameFound = (s.size() != buffer.size());

		if(sameFound){
			return false;
		}else{
			attempts = 0;
			somethingWrong=false;
		}

	}

	return true;
}

int howManyLastsInCurrent4(std::queue<int> current4, int last){

	int counter=0;
	for(int i=0; i<4; i++){
		if(current4.front() == last){
			counter++;
		}else{
			return counter;
		}
		current4.pop();
	}

	return counter;

}

int searchBest4ToSwap(std::vector<int> data, int last){

	std::queue<int> current4;
	current4.push(data[0]);
	current4.push(data[1]);
	current4.push(data[2]);
	current4.push(data[3]);

	std::map<int, std::vector<int>> indexesForNumberOfLastOccurrences;
	indexesForNumberOfLastOccurrences.emplace(0, std::vector<int>());
	indexesForNumberOfLastOccurrences.emplace(1, std::vector<int>());
	indexesForNumberOfLastOccurrences.emplace(2, std::vector<int>());
	indexesForNumberOfLastOccurrences.emplace(3, std::vector<int>());
	indexesForNumberOfLastOccurrences.emplace(4, std::vector<int>());

	int number = howManyLastsInCurrent4(current4, last);
	indexesForNumberOfLastOccurrences.find(number)->second.push_back(0);

	size_t size = data.size();
	for(int i=1; i<size-3; ++i){
		current4.pop();
		current4.push(data[i+3]);
		bool searchingInLastGroup = true;

		for(int j=size-1; j>i+3; j--){
			if( data[i+3] != data[j] ){
				searchingInLastGroup = false;
				break;
			}
		}

		if( searchingInLastGroup ){
			if( i == 1 ){
				return -1;
			}
			break;
		}

		number = howManyLastsInCurrent4(current4, last);
		indexesForNumberOfLastOccurrences.find(number)->second.push_back(i);
	}

	if(!indexesForNumberOfLastOccurrences.find(4)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(4)->second[0];
	}else if(!indexesForNumberOfLastOccurrences.find(3)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(3)->second[0];
	}else if(!indexesForNumberOfLastOccurrences.find(2)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(2)->second[0];
	}else if(!indexesForNumberOfLastOccurrences.find(1)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(1)->second[0];
	}else{
		return -1;
	}

}

int search4ToSwap(std::vector<int> data, int last){

	std::queue<int> current4;
	current4.push(data[0]);
	current4.push(data[1]);
	current4.push(data[2]);
	current4.push(data[3]);

	std::map<int, std::vector<int>> indexesForNumberOfLastOccurrences;
	indexesForNumberOfLastOccurrences.emplace(0, std::vector<int>());
	indexesForNumberOfLastOccurrences.emplace(1, std::vector<int>());
	indexesForNumberOfLastOccurrences.emplace(2, std::vector<int>());
	indexesForNumberOfLastOccurrences.emplace(3, std::vector<int>());
	indexesForNumberOfLastOccurrences.emplace(4, std::vector<int>());

	int number = howManyLastsInCurrent4(current4, last);
	indexesForNumberOfLastOccurrences.find(number)->second.push_back(0);

	size_t size = data.size();
	for(int i=1; i<size-3; ++i){
		current4.pop();
		current4.push(data[i+3]);
		bool searchingInLastGroup = true;

		for(int j=size-1; j>i+3; j--){
			if( data[i+3] != data[j] ){
				searchingInLastGroup = false;
				break;
			}
		}

		if( searchingInLastGroup ){
			if( i == 1 ){
				return -1;
			}
			break;
		}

		number = howManyLastsInCurrent4(current4, last);
		indexesForNumberOfLastOccurrences.find(number)->second.push_back(i);
	}

	if(!indexesForNumberOfLastOccurrences.find(4)->second.empty()){
		return indexesForNumberOfLastOccurrences.find(4)->second[0];
	}else {
		return -1;
	}

}

void putAll4ToOrder(std::vector<int>& data, int& numberOfMoves){

	while(true){
		int index = search4ToSwap(data, C);

		if(index == -1){
			// cant swap
			break;
		}

		move4chars(data, index);

		++numberOfMoves;
	}

	while(true){
		int index = search4ToSwap(data, M);

		if(index == -1){
			// cant swap
			break;
		}

		move4chars(data, index);

		++numberOfMoves;
	}

	while(true){
		int index = search4ToSwap(data, Y);

		if(index == -1){
			// cant swap
			break;
		}

		move4chars(data, index);

		++numberOfMoves;
	}

	while(true){
		int index = search4ToSwap(data, K);

		if(index == -1){
			// cant swap
			break;
		}

		move4chars(data, index);

		++numberOfMoves;
	}

}

int creatingGroupsWithLast(std::vector<int>& data){

	int last = *(data.end()-1);

	int numberOfMoves = 0;
	while (!isSorted(data) && worthSearching(data)){
		last = *(data.end()-1);

		int index = searchBest4ToSwap(data, last);

		if(index == -1){
			// cant swap
			break;
		}

		move4chars(data, index);

		++numberOfMoves;
	}

	putAll4ToOrder(data, numberOfMoves);

	return numberOfMoves;
}