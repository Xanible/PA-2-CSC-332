#include <iostream>
#include <chrono>
#include <fstream>
#include <array>

using namespace std;

void randomizeArrays(array<array<int,9>, 9000>& array_i, int i) {	
	// Seed random number generator. 
	srand((unsigned)time(NULL));

	// A random number in the range of 1 to 100,000 is assigned.
	int bound = i * 1000;
	for(int j=0;j < bound;j++) {
		array_i[j][i - 1] = rand() % 100000 + 1;
	}
}

void mergesort(array<array<int,9>, 9000>& array_i, int i) {
	// I need teh mergesort code herez
	// Get rid of these comments when you do please
}

double mergesortTimed(array<array<int,9>, 9000>& array_i, int i) {
	// start chrono timer
	auto start = std::chrono::high_resolution_clock::now();
	
	// perform the mergesort!
	mergesort(array_i, i);
	
	// stop chrono timer
	auto finish = std::chrono::high_resolution_clock::now();
	
	// make sure enough time has passed for the timer to have registered change
	while(finish == start) {
		finish = std::chrono::high_resolution_clock::now();
	}
	
	// calculate elapsed time and add to array
	std::chrono::duration<double, std::milli> elapsed = finish - start;
	return elapsed.count();
}

// Prints a given array to screen
// NOT DONE YET
void printArray(array<array<int,9>, 9000>& array_i, int i) {
	int bound = i * 1000;
	for(int j=0;j < bound;j++) {
		cout << array_i[j][i - 1] << '\t';
	}
}

// This method will write the text file that will be used
// for the xlsx file
void toFile(ofstream &ms_times) {
	// input size of the array, nlogn, time spent,
	// nlogn/time using scientific notation.
	// output this straight to file with \t inbetween each
}

// This method was for testing something...
void test(array<array<int,9>, 9000>& array_i) {
	string junk = "test.txt";
	ofstream test(junk.c_str());
	for (int i = 0;i < 9000;i++) {
		test << array_i[i][0] << '\t' << array_i[i][1] << '\t'
			 << array_i[i][2] << '\t' << array_i[i][3] << '\t'
			 << array_i[i][4] << '\t' << array_i[i][5] << '\t' 
			 << array_i[i][6] << '\t' << array_i[i][7] << '\t' 
			 << array_i[i][8] << "\n"; 
	}
}


int main(int argc, char** argv) {
	// Declare the 9 arrays
	array<array<int,9>, 9000> array_i = {}; 
	
	// Fill the arrays based on size
	for (int i = 1;i <= 9;i++) {
		randomizeArrays(array_i, i);
	}
	
	// Output file for text
	string junk = "Mergesort_Time.txt";
	ofstream ms_times(junk.c_str());
	
	// Array to hold the times
	array<double, 9> times= {};
	
	// The console loop
	char input = 0;
	
	//a small test
	test(array_i);
	
	cout << "Hello! This is a console application." << endl;
	cout << "Press q to quit, press a to execute foo." << endl;	
	while(1) {
		cin >> input;
    	if (cin.get() != '\n')  {
        	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input stream
        	cout << "Enter a number 1 - 9: \n";
    	} else if(input == 'q') {
			break;
		} else if((input - 48) < 10 && (input - 48) > 0) {
			// Show the unsorted array
			cout << "Here is the unsorted Array_" << input << '\n';
			printArray(array_i, input - 48);
			
			// Perform the mergesort, which will also print the
			// sorted array and record time
			times[input - 48] = mergesortTimed(array_i, input - 48);
		} else if(input != '\n') {
			cout << "Unknown command '" << input << "'! Ignoring...\n";
		}
	}
	
	toFile(ms_times);
	ms_times.close();
	return 0;
}
