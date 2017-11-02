/*
 *  sorter.cpp
 *  End-User Interface
 *  	   Written by : Jia Wen Goh
 *                 On : 01-04-2017
 * 
 *  Sorts given inputs with (a) Insertion Sort, (b) Merge Sort or 
 *  (c) Quick Sort, before saving/printing it.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include "sortAlgs.h"
using namespace std;

//----Function Declarations-----//
/******************************** 
 *         Run Functions        *
 ********************************/
// run that takes in input from the cmd line
void	run(string,string);

// run that takes in input from a file
void	run(string,string,string);

/******************************** 
 *         Read Functions       *
 ********************************/
// Reads in contents from an input stream (cin/infile), and stores in a vector
void	read(istream&,vector<int>&);

// Opens a file and processes the inputs
void	readFile(string,vector<int>&);

// Sorts the input based on the user's desired sorting method
void	sort(string,vector<int>&);

/******************************** 
 *        Print Functions       *
 ********************************/
// Prints the sorted list's inputs
void	print(ostream&,vector<int>);

// Saves the lists inputs into a file
void	save(vector<int>,string,string);
void	saveFile(string,vector<int>);

/******************************** 
 *         Etc Functions        *
 ********************************/
// Prints an error message of the correct input on cerr 
void	errorMessage();

//------------------------------//

//-------------Main-------------//

int main(int argc, char* argv[]) 
{
	if (argc == 3) {
		try {
			run(argv[1], argv[2]);
		} catch (...) {
			errorMessage();
			return 1;
		}
	}
	
	else if (argc == 4) {
		try {
			run(argv[1], argv[2], argv[3]);
		} catch (...) {
			errorMessage();
			return 1;
		}
	}
	
	else {
		errorMessage();
		return 1;
	}
}

//------------------------------//

//-----Function Definitions-----//
/******************************** 
 *         Run Functions        *
 ********************************/
/* [Name]:		run
 * [Purpose]:		Interactive run that takes in ints from the command
 * 			line. If any of the cmdline inputs aren't in the right
 * 			form, throw a runtime error (that is caught by main).
 * 			Sorts, then prints or saves the contents after end of
 * 			input.
 * [Parameters]:	2 strings (sortAlg and outputMode)
 * [Returns]:		void
 */
void run(string sortAlg, string outputMode)
{
	if ((sortAlg != "-s1" and sortAlg != "-s2" and sortAlg != "-s3") or
	    (outputMode != "--print" and outputMode != "--save"))
		throw runtime_error("Invalid input");
	
	vector<int> intList;
	
	read(cin, intList);
	sort(sortAlg, intList);
	
	if (outputMode == "--print")
		print(cout, intList);
	else
		save(intList, "cin", sortAlg);
}

/* [Name]:		run
 * [Purpose]:		Automated run that takes in ints from a given
 * 			file. If any of the cmdline inputs aren't in the right
 * 			form, throw a runtime error (that is caught by main).
 * 			Sorts, then prints or saves the contents after end of
 * 			input.
 * [Parameters]:	3 strings (sortAlg, outputMode and filename)
 * [Returns]:		void
 */
void run(string sortAlg, string outputMode, string filename)
{
	if ((sortAlg != "-s1" and sortAlg != "-s2" and sortAlg != "-s3") or
	    (outputMode != "--print" and outputMode != "--save"))
		throw runtime_error("Invalid input");
	
	vector<int> intList;
		
	readFile(filename, intList);
	sort(sortAlg, intList);
	
	if (outputMode == "--print")
		print(cout, intList);
	else
		save(intList, filename, sortAlg);
}

/* [Name]:		sort
 * [Purpose]:		Determines which sort to use 
 * 			- "-s1" - Insertion Sort
 * 			- "-s2" - Merge Sort
 * 			- "-s3" - Quick Sort
 * [Parameters]:	1 string (sortAlg), 1 int vector & (list to be sorted)
 * [Returns]:		void
 */
void sort(string sortAlg, vector<int> &intList)
{
	if (sortAlg == "-s1")
		insertionSort(intList);
	else if (sortAlg == "-s2")
		mergeSort(intList);
	else
		quickSort(intList);
}

/******************************** 
 *         Read Functions       *
 ********************************/
/* [Name]:		read
 * [Purpose]:		Reads in and stores input from the given istream
 * 			into the int vector.
 * [Parameters]:	1 istream &, 1 int vector & (input stored inside)
 * [Returns]:		void
 */
void read(istream &input, vector<int> &intList)
{
	int intInput;
	input >> intInput;
	while (!input.eof()) {
		intList.push_back(intInput);
		input >> intInput;
	}
}

/* [Name]:		readFile
 * [Purpose]:		Reads in input from the given filename. Throws an
 * 			exception if the file is invalid/nonexistent. Stores
 * 			the input into the given vector.
 * [Parameters]:	1 string (filename), 1 int vector & (input stored 
 * 			inside)
 * [Returns]:		void
 */
void readFile(string filename, vector<int> &intList)
{
	ifstream inf;
	
	inf.open(filename.c_str());
	if (!inf.is_open())
		throw runtime_error("Invalid input");
	
	while (!inf.eof())
		read(inf, intList);
	
	inf.close();
}

/******************************** 
 *        Print Functions       *
 ********************************/
/* [Name]:		print
 * [Purpose]:		Prints all stored inputs onto the given ostream
 * [Parameters]:	1 ostream & (stream to print on), 1 int vector
 * 			(list to be printed)
 * [Returns]:		void
 */
void print(ostream& output, vector<int> intList)
{
	size_t listLength = intList.size();
	for (size_t i = 0; i < listLength; i++)
		output << intList[i] << endl;
}
	
/* [Name]:		save
 * [Purpose]:		Saves all stored inputs into a file with the given
 * 			format:
 * 			  "ListOrigin_SortAlg_NumElements_sorted.txt"
 * [Parameters]:	1 int vector (list to be saved), 2 strings
 * 			(listOrigin and sortAlg)
 * [Returns]:		void
 */
void save(vector<int> intList, string listOrigin, string sortAlg)
{	
	string numElements;
	if (intList.empty())
		numElements = "0";
	else
		numElements = to_string(intList.size());
	
	sortAlg = sortAlg[2];
	
	string filename = listOrigin + "_" + sortAlg + "_" + numElements + 
			  "_sorted.txt";
	saveFile(filename, intList);
}

/* [Name]:		saveFile
 * [Purpose]:		Saves the input from the given intList into the 
 * 			specified filename.
 * [Parameters]:	1 string (filename), 1 int vector (sorted list)
 * [Returns]:		void
 */
void saveFile(string filename, vector<int> intList)
{
	ofstream outf;
	
	outf.open(filename.c_str());
	if (!outf.is_open())
		throw runtime_error("Invalid input");
	
	print(outf, intList);
	
	outf.close();
}

/******************************** 
 *         Etc Functions        *
 ********************************/
/* [Name]:		errorMessage
 * [Purpose]:		Prints an error message on the proper cmd line input
 * 			onto cerr.
 * [Parameters]:	-
 * [Returns]:		void
 */
void errorMessage()
{
	cerr << "Usage:  sorter sortAlg outputMode [fileName]\n"
	     << "            where:  sortAlg is -s1, -s2, or -s3\n"
	     << "            and     outputMode is --print or --save\n";
}

//------------------------------//