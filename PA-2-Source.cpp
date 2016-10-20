#include <iostream>
#include <chrono>
#include <fstream>
#include <array>

using namespace std;

void randomizeArray(int array[]) {	
	// Seed random number generator. 
	srand((unsigned)time(NULL));

	// A random number in the range of 1 to 100,000 is assigned.
	for(int i=0;i < 1000;i++) {
		array[i] = rand() % 100000 + 1;
	}
}


int main(int argc, char** argv) {
	char input = 0;
	
	cout << "Hello! This is a console application." << endl;
	cout << "Press q to quit, press a to execute foo." << endl;	
	while(1) {
		cin >> input;
		if(input == 'a') {
			Foo();
		} else if(input == 'q') {
			break;
		} else if(input != '\n') {
			cout << "Unknown command '" << input << "'! Ignoring...\n";
		}
	}

	return 0;
}
