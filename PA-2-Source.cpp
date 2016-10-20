#include <iostream>
#include <chrono>
#include <fstream>
#include <array>

using namespace std;

void randomizeArrays(array<array<int,9>, 9000> array_i, int i) {	
	// Seed random number generator. 
	srand((unsigned)time(NULL));

	// A random number in the range of 1 to 100,000 is assigned.
	int bound = (i + 1) * 1000;
	for(int j=0;j < bound;j++) {
		array_i[j][i] = rand() % 100000 + 1;
	}
}


int main(int argc, char** argv) {
	// Declare the 9 arrays
	array<array<int,9>, 9000> array_i = {}; 
	
	// Fill the arrays based on size
	for (int i = 0;i < 9;i++) {
		randomizeArrays(array_i, i);
	}
	
	// The console loop
	char input = 0;
	
	cout << "Hello! This is a console application." << endl;
	cout << "Press q to quit, press a to execute foo." << endl;	
	while(1) {
		cin >> input;
		if(input == 'a') {
			//Foo();
		} else if(input == 'q') {
			break;
		} else if(input != '\n') {
			cout << "Unknown command '" << input << "'! Ignoring...\n";
		}
	}

	return 0;
}
