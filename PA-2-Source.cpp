#include <iostream>
#include <chrono>
#include <fstream>
#include <array>
#include <cmath>

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

void merge (array<array<int,9>, 9000>& array_i, int i,
 			const int low, const int mid, const int length)
{
	// Variables declaration. 
	int b [length + 1];
	int h, l, j, k;
	h = low;
	l = 0;
	j = mid + 1;
	// Merges the two array's into b[] until the first one is finish
	while ((h <= mid) && (j <= length))
	{
		if (array_i[h][i] <= array_i[j][i])
		{
			b[l] = array_i[h][i];
			h++;
		}
		else
		{
			b[l] = array_i[j][i];
			j++;
		}
		l++;
	}
	// Completes the array filling in it the missing values
	if (h>mid)
	{
		for (k = j; k <= length; k++)
		{
			b[l] = array_i[k][i];
			l++;
		}
	}
	else
	{
		for (k = h; k <= mid; k++)
		{
			b[l] = array_i[k][i];
			l++;
		}
	}
	// Prints into the original array
	for (k = 0; k <= length - low; k++)
	{
		array_i[k + low][i] = b[k];
	}
}

void mergesort(array<array<int,9>, 9000>& array_i, int i, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = (l+r)/2;
 
        // Sort first and second halves
        mergesort(array_i, i, l, m);
        mergesort(array_i, i, m+1, r);
 
        merge(array_i, i, l, m, r);
    }
}

double mergesortTimed(array<array<int,9>, 9000>& array_i, int i) {
	// start chrono timer
	auto start = std::chrono::high_resolution_clock::now();
	
	// perform the mergesort!
	mergesort(array_i, (i - 1), 0, (i*1000) - 1);
	
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
void toFile(ofstream &ms_times, array<double, 9>& times) {
	// input size of the array, nlogn, time spent,
	// nlogn/time using scientific notation.
	// output this straight to file with \t inbetween each
	ms_times << "Input size of n for Array_i\tValue of n*logn\t\t"
			 <<	"Time Spent(ms)\t\tValue of n*logn/time \n";
	for(int i = 0; i < 9; i++) {
		if (times[i] != 0) {
			ms_times << (i+1)*1000 << "\t\t\t\t";
			ms_times << ((i+1) * 1000)*log((i+1) * 1000) << "\t\t\t";
			ms_times << times[i] << "\t\t\t";
			ms_times << ((i+1) * 1000)*log((i+1) * 1000)/times[i] << "\t\t";
			ms_times << "\n";
		}
	}
}

// This method was for testing something...
/*
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
}*/


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
	//test(array_i);
	
	//loop for menu
	while(1) {
	cout << "___________________________________________\n"
		<< "| Hello! Welcome to the mergesort program! |\n"
		<< "|__________________________________________|\n\n"
		<< "Input 1 to see the first array:\n\n"
		<< "Input 2 to see the second array:\n\n"
		<< "Input 3 to see the third array:\n\n"
		<< "Input 4 to see the fourth array:\n\n"
		<< "Input 5 to see the fifth array:\n\n"
		<< "Input 6 to see the sixth array:\n\n"
		<< "Input 7 to see the seventh array:\n\n"
		<< "Input 8 to see the eighth array:\n\n"
		<< "Input 9 to see the ninth array:\n\n"
		<< "Input q to quit"<< endl;	
		cin >> input;
    	if (cin.get() != '\n')  {
        	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input stream
        	cout << "Unknown command '" << input << "'! Ignoring...\n";
        	system("PAUSE");
    	} else if(input == 'q' || input == 'Q') {
			break;
		} else if((input - 48) < 10 && (input - 48) > 0) {
			// Show the unsorted array
			cout << "First we will show the unsorted Array_" << input << '\n';
			system("PAUSE");
			printArray(array_i, input - 48);
			cout << endl;
			
			// Perform the mergesort, which will also print the
			// sorted array and record time
			times[input - 49] = mergesortTimed(array_i, input - 48);
			cout << "Now for the sorted Array_" << input << '\n';
			system("PAUSE");
			printArray(array_i, input - 48);
			cout << endl;
		} else if(input != '\n') {
			cout << "Unknown command '" << input << "'! Ignoring...\n";
			system("PAUSE");
		}
	}
	
	toFile(ms_times, times);
	ms_times.close();
	return 0;
}
