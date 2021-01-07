#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cmath> // log
#include <queue> //fifo
#include <vector>
#include <chrono>

#include "../include/utilities.h"
#include "../include/bruteForce.h"
#include "../include/creatingGroupsWithLast.h"
#include "../include/startFromBeg.h"
#include "../include/fast4Create.h"
#include "../include/popl.hpp"

using namespace std;
using namespace popl;

void runMode1(int algorithm){

	string input;
	getline(cin, input);

	//TODO:Comment out
//	cout << input << "\n";

	std::vector<int> data = convertToData( input.c_str(), input.size() );

//	cout << vToStr(data) << "\n";


	int numberOfMoves = 0;
	auto begin = chrono::high_resolution_clock::now();
	auto end = chrono::high_resolution_clock::now();
	switch (algorithm) {
		case 1:
			begin = chrono::high_resolution_clock::now();
			numberOfMoves = creatingGroupsWithLast(data, true);
			end = chrono::high_resolution_clock::now();
			break;
		case 2:
			begin = chrono::high_resolution_clock::now();
			numberOfMoves = fast4Create(data, true);
			end = chrono::high_resolution_clock::now();
			break;
		default:
			cout << "Wrong algorithm! Try -a{1,2}\n";
			return;
	}

	auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

	cout << "Number of moves: " << numberOfMoves << "\n";
	cout << "Time taken by algorithm: " << timeTaken << "[ms]\n";
	cout << vToStr(data) << "\n";
}

void runMode2(int algorithm, int problemSize, float generatorParam){

	std::vector<int> data;
	generateData(data, problemSize, (int)(generatorParam*100));

	//TODO:Comment out
	cout << "Generated input: \n" << vToStr(data) << "\n";

	int numberOfMoves = 0;
	auto begin = chrono::high_resolution_clock::now();
	auto end = chrono::high_resolution_clock::now();
	switch (algorithm){
		case 1:
			begin = chrono::high_resolution_clock::now();
			numberOfMoves =  creatingGroupsWithLast(data, true);
			end = chrono::high_resolution_clock::now();
			break;
		case 2:
			begin = chrono::high_resolution_clock::now();
			numberOfMoves = fast4Create(data, true);
			end = chrono::high_resolution_clock::now();
			break;
		default:
			cout << "Wrong algorithm! Try -a{1,2}\n";
			return;
	}

	auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

	cout << "Number of moves: " << numberOfMoves << "\n";
	cout << "Time taken by algorithm: " << timeTaken << "[ms]\n";
	cout << vToStr(data) << "\n";
}

void runMode3(int algorithm, int problemSize, int numberOfStepIterations, int step, int numberOfRuns, float generatorParam){

	std::vector<int> data;

	int maxSize = problemSize + step*numberOfStepIterations + 1;
	for(int size = problemSize; size < maxSize; size+=step){

		for(int run=0; run<numberOfRuns; run++){
			data.clear();
			generateData(data, size, (int)(generatorParam*100));

			int numberOfMoves = 0;
			auto begin = chrono::high_resolution_clock::now();
			auto end = chrono::high_resolution_clock::now();
			cout << "Size: " << size << "\n";
			switch (algorithm){
				case 1:
					begin = chrono::high_resolution_clock::now();
					numberOfMoves = creatingGroupsWithLast(data, true);
					end = chrono::high_resolution_clock::now();
					break;
				case 2:
					begin = chrono::high_resolution_clock::now();
					numberOfMoves = fast4Create(data, true);
					end = chrono::high_resolution_clock::now();
					break;
				default:
					cout << "Wrong algorithm! Try -a{1,2}\n";
					return;
			}

			auto timeTaken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

			//TODO: comment
			cout << "Number of moves: " << numberOfMoves << "\n";
			cout << "Time taken by algorithm: " << timeTaken << "[ms]\n";
			cout << vToStr(data) << "\n\n";
		}
	}
}

int main(int argc, char **argv) {

	int mode;
	int problemSize;
	int numberOfRuns;
	int step;
	int numberOfStepIterations;
	float generatorParam;
	int algorithm;

	OptionParser op("Allowed options");
	auto help_option = op.add<Switch>("h", "help", "produce help message");
	auto mode_option = op.add<Value<int>>("m", "mode", "program mode", 1, &mode);
	auto problemSize_option = op.add<Value<int>>("n", "size", "problem size", 100, &problemSize);
	auto numberOfStepIterations_option = op.add<Value<int>>("k", "iterations", "number of step iterations", 5, &numberOfStepIterations);
	auto step_option = op.add<Value<int>>("s", "step", "step size, increasing problem size", 100, &step);
	auto numberOfRuns_option = op.add<Value<int>>("r", "runs", "number of problem runs", 25, &numberOfRuns);
	auto generatorParam_option    = op.add<Value<float>>("d", "generator", "generator param", 0.5f, &generatorParam);
	auto algorithm_option = op.add<Value<int>>("a", "algorithm", "1 - creatingGroupsWithLast, "
															  "2 - fast4Create", 1, &algorithm);

	op.parse(argc, argv);

	if (help_option->count() == 1)
		cout << op << "\n\n";

	if(!algorithm_option->is_set()){
		cout << "This program needs option: -a. Defaulting to -a1\n";
	}


	//TODO: add mode 4, where next swap candidates are shown
	switch (mode){
		case 1:

			cout << "\n";
			runMode1(algorithm);
			break;

		case 2:
			if(!problemSize_option->is_set()){
				cout << "This mode needs options: -n. Defaulting to -n100\n";
			}
			if(!generatorParam_option->is_set()){
				cout << "This mode needs options: -d. Defaulting to -d0.5\n";
			}

			cout << "\n";
			runMode2(algorithm, problemSize, generatorParam);
			break;

		case 3:
			if(!problemSize_option->is_set()){
				cout << "This mode needs options: -n. Defaulting to -n100\n";
			}
			if(!numberOfStepIterations_option->is_set()){
				cout << "This mode needs options: -k. Defaulting to -k5\n";
			}
			if(!step_option->is_set()){
				cout << "This mode needs options: -step. Defaulting to -step100\n";
			}
			if(!numberOfRuns_option->is_set()){
				cout << "This mode needs options: -r. Defaulting to -r25\n";
			}
			if(!generatorParam_option->is_set()){
				cout << "This mode needs options: -d. Defaulting to -d0.5\n";
			}

			cout << "\n";
			runMode3(algorithm, problemSize, numberOfStepIterations, step, numberOfRuns, generatorParam);
			break;

		default:
			cout << "Wrong mode! Try -m{1,2,3}\n";
			return 1;
	}


//
//    srand(time(nullptr)) ;
//
//    std::vector<int> data;
//    generateData(data, DATA_SIZE, CHANCE_OF_DUPLICATION);
//
//	std::vector<int> dataForCGWL = data;
//	std::vector<int> dataForF4C = data;
//    std::cout<<"Rozmiar danych: "<< DATA_SIZE<<std::endl;
//    std::cout<<"Prawdopodobienstwo powtorzenia: "<< CHANCE_OF_DUPLICATION<<"%"<<std::endl;
//
//
////    bruteForce(data);
////    std::cout<< vToStr(data) << "\n" <<std::endl;
//	std::cout<< vToStr(dataForCGWL) <<std::endl;
//	std::cout << "Number of moves: " << creatingGroupsWithLast(dataForCGWL, true) <<std::endl;
//	std::cout<< vToStr(dataForCGWL) << "\n" <<std::endl;
//
//	std::cout<< vToStr(dataForF4C) <<std::endl;
//	std::cout << "Number of moves: " << fast4Create(dataForF4C, true) <<std::endl;
//	std::cout<< vToStr(dataForF4C) <<std::endl;


//    const char* arr = "CCCCC";
//    data = convertToData(arr, strlen(arr));
//    startFromBeg(data);
//    std::cout<< vToStr(data) <<std::endl;
    return 0;
}
