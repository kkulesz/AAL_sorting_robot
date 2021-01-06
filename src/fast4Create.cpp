//
// Created by demongo on 06.01.2021.
//

#include "../include/fast4Create.h"
#include "../include/creatingGroupsWithLast.h"
#include "../include/utilities.h"
#include <set>
#include <queue>
#include <map>
#include <iostream>
#include <unordered_map>


int heuristicLossF4C(std::vector<int> data){

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

bool worthSearching(std::vector<int> data) {

	static int attempts = 0;
	static int prevLoss = 0;
	static int loss = 0;
	static bool somethingWrong = false;
	static std::vector<std::vector<int>> buffer;

	prevLoss = loss;
	loss = heuristicLossF4C(data);

//	if( loss >= prevLoss ){
//		attempts++;
//		somethingWrong = true;
//		buffer.push_back(data);
//	} else if(somethingWrong){
//		attempts++;
//	}
//
//	if(attempts > 20){
//		somethingWrong = false;
//
//		bool same5Found= false;
//		std::map<std::string, int> map;
//
//		for(auto b: buffer){
//			if( map.find(vToStr(b)) != map.end())
//				map.emplace(std::make_pair(vToStr(b),1));
//			else
//				(*map.find(vToStr(b))).second++;
//		}
//
//		for(auto x: map){
//			if( x.second >= 2){
//				same5Found = true;
//			}
//		}
//
////		std::set<std::vector<int>> s(buffer.begin(), buffer.end());
////		bool sameFound = (s.size() != buffer.size());
//
//		if(same5Found){
//			return false;
//		}else{
//			attempts = 0;
//			somethingWrong=false;
//		}
//	}

		if( loss >= prevLoss ){
			attempts++;
			somethingWrong = true;
			buffer.push_back(data);
		} else if(somethingWrong){
			attempts++;
		}

		if(attempts > 10) {
			somethingWrong = false;

			std::set<std::vector<int>> s(buffer.begin(), buffer.end());
			bool sameFound = (s.size() != buffer.size());

			if (sameFound) {
				return false;
			} else {
				attempts = 0;
				somethingWrong = false;
				buffer.clear();
			}


		}


	return true;
}

std::pair<int,int> searchForSmallGroupRight(std::vector<int> current4){


	int color = current4[3];
	int counter = 1;
	for(int i=2; i>=0; i--){
		if(current4[i] != color){
			break;
		}
		counter++;
	}

	return std::make_pair(color, counter);;
}

std::pair<int,int> searchForSmallGroupLeft(std::vector<int> current4){

	int color = current4[0];
	int counter = 1;
	for(int i=1; i<4; i++){
		if(current4[i] != color){
			break;
		}
		counter++;
	}

	return std::make_pair(color, counter);;
}

void addIndexToVector(int index, std::pair<int,int> colorAndGroupSize,
		std::vector<std::vector<std::vector<int>>>& vector,
		const std::vector<int>& groups){


	for(int i=index; i<index+4; i++){
		if( groups[i] != -1 ){
			// collision with group
			return;
		}
	}

	int color = colorAndGroupSize.first;
	int size = colorAndGroupSize.second;



	vector[color][size].push_back(index);

}

int searchBest4ToMergeRight(const std::vector<int>& data, const std::vector<int>& groups){
	size_t size = data.size();

	std::vector<int> current4;
	current4.push_back(data[0]);
	current4.push_back(data[1]);
	current4.push_back(data[2]);
	current4.push_back(data[3]);


	std::vector<std::vector<std::vector<int>>> indexesOfGroupRight;
	for(int i=0; i<4; i++){
		indexesOfGroupRight.push_back(std::vector<std::vector<int>>());
	}

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			indexesOfGroupRight[i].push_back(std::vector<int>());
		}
	}



	std::pair<int,int> colorAndGroupSizeRight = searchForSmallGroupRight(current4);

	int skip = 0;
	if(colorAndGroupSizeRight.second != 4){

		addIndexToVector(0, colorAndGroupSizeRight, indexesOfGroupRight, groups);
	}else{
		skip = 3;
	}

	for(int i=1+skip; i<size-4; i++){
		int k = 0;
		for(int j=i; j<i+4; j++, k++){
			current4[k] = data[j];
		}

		colorAndGroupSizeRight = searchForSmallGroupRight(current4);

		if(colorAndGroupSizeRight.second != 4){

			addIndexToVector(i, colorAndGroupSizeRight, indexesOfGroupRight, groups);
		}else{
			i+= 3;
		}
	}


	for( int groupSize=3; groupSize>0; groupSize--){
		for(int color=0; color<4; color++){
			if( !indexesOfGroupRight[color][groupSize].empty() ){
				return indexesOfGroupRight[color][groupSize][0];
			}
		}
	}

	return -1;
}

int searchBest4ToMergeLeft(const std::vector<int>& data, const std::vector<int>& groups){
	size_t size = data.size();

	std::vector<int> current4;
	current4.push_back(data[0]);
	current4.push_back(data[1]);
	current4.push_back(data[2]);
	current4.push_back(data[3]);


	std::vector<std::vector<std::vector<int>>> indexesOfGroupLeft;
	for(int i=0; i<4; i++){
		indexesOfGroupLeft.push_back(std::vector<std::vector<int>>());
	}

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			indexesOfGroupLeft[i].push_back(std::vector<int>());
		}
	}


	std::pair<int,int> colorAndGroupSizeLeft = searchForSmallGroupLeft(current4);


	int skip = 0;
	if(colorAndGroupSizeLeft.second != 4){
		addIndexToVector(0, colorAndGroupSizeLeft, indexesOfGroupLeft, groups);
	}else{
		skip = 3;
	}

	for(int i=1+skip; i<size-4; i++){

		int k = 0;
		for(int j=i; j<i+4; j++, k++){
			current4[k] = data[j];
		}

		colorAndGroupSizeLeft = searchForSmallGroupLeft(current4);


		if(colorAndGroupSizeLeft.second != 4){
			addIndexToVector(i, colorAndGroupSizeLeft, indexesOfGroupLeft, groups);
		}else{
			i+= 3;
		}
	}


	int color = data[size-1];
	for( int groupSize=3; groupSize>0; groupSize--){
		if( !indexesOfGroupLeft[color][groupSize].empty() ){
			return indexesOfGroupLeft[color][groupSize][0];
		}
	}

	return -1;
}

bool checkIfIsAll4(std::vector<int> current4){

	int color = current4[0];
	for(int i=1; i<4; i++){
		if(current4[i] != color){
			return false;
		}
	}

	return true;
}

void setGroup(std::vector<int>& groups, int startIndex, int groupNumber){
	for(int i=startIndex; i<startIndex+4; i++){
		groups[i] = groupNumber;
	}
}

void makeGroups(const std::vector<int>& data, std::vector<int>& groups){

	size_t size = data.size();

	std::vector<int> current4;
	current4.push_back(data[0]);
	current4.push_back(data[1]);
	current4.push_back(data[2]);
	current4.push_back(data[3]);

	bool oneColor = checkIfIsAll4(current4);
	int skip = 0;
	int groupNumber = 0;
	if( oneColor ){
		// has one colors
		setGroup(groups, 0, groupNumber);
		groupNumber++;
		skip = 3;
	}

	for(int i=1+skip; i<size-3; i++){

		if( i+3 >= size){
			// end of search
			return;
		}

		int k = 0;
		for(int j=i; j<i+4; j++, k++){
			current4[k] = data[j];
		}

		oneColor = checkIfIsAll4(current4);
		if( oneColor ){
			// has one colors
			setGroup(groups, i, groupNumber);
			groupNumber++;
			i+= 3;
		}

	}

}


int findGroupInLast8(const std::vector<int>& data, const std::vector<int>& groups){
	size_t size = data.size();
	int counter = 0;

	int group = groups[size-8];
	for(int i=size-7; i<size; i++){
		if( groups[i] != -1 ) {
			return i;
		}
	}
	return -1;
}


int fast4Create(std::vector<int>& data, bool versionWithSortFinish){
	size_t size = data.size();

	std::vector<int> groups;
	groups.resize(size);
	std::fill(groups.begin(), groups.end(), -1);

	makeGroups(data, groups);

	int numberOfMoves = 0;
	while (!isSorted(data) && worthSearching(data)){



		int index = searchBest4ToMergeRight(data, groups);

		if(index == -1){
//			 try order
			putAll4ToOrder(data, numberOfMoves);
			makeGroups(data, groups);

			index = searchBest4ToMergeRight(data, groups);
			if( index == -1){
				break;
			}

//			break;

		}

		move4chars(data, index);
		move4chars(groups, index);

		++numberOfMoves;

		if(numberOfMoves == 100){
			std::cout << "w";
		}

		makeGroups(data, groups);
		index = searchBest4ToMergeLeft(data, groups);


		if(index == -1){
			// cant swap
			continue;
		}

		move4chars(data, index);
		move4chars(groups, index);

		++numberOfMoves;

		if(numberOfMoves == 100){
			std::cout << "w";
		}

		makeGroups(data, groups);

		index = findGroupInLast8(data, groups);

		if(index == -1){
			// cant swap
			continue;
		}

		move4chars(data, index);
		move4chars(groups, index);

		++numberOfMoves;

		if(numberOfMoves == 100){
			std::cout << "w";
		}

		makeGroups(data, groups);
	}

	// activate this if
	if(versionWithSortFinish)
		putAll4ToOrder(data, numberOfMoves);

	return numberOfMoves;

}