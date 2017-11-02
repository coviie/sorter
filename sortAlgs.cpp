/*
 *  sortAlgs.cpp
 *  Sort Definitions
 *  	   Written by : Jia Wen Goh
 *                 On : 01-04-2017
 * 
 *  Definition of sorts, with accompanying helper functions.
 */

#include <iostream>
#include <vector>
using namespace std;

//----Function Declarations-----//
/******************************** 
 *       Helper Functions       *
 ********************************/
// 'Merges' 2 int vectors into a sorted one
vector<int>	merge(vector<int>&, vector<int>&);

// Pushes the smallest int into the given vector 
void		pushSmallest(vector<int>&, vector<int>&);

// Appends two vectors
void		append(vector<int>&, vector<int>&);

// Quick sort helper function
void		quickSort(vector<int>&, int, int);

// Swaps 2 elements
void		swap(vector<int>&, int, int);

//------------------------------//

//-----Function Definitions-----//
/******************************** 
 *        Insertion Sort        *
 ********************************/
/* [Name]:		insertionSort
 * [Purpose]:		Sorts the given intList with insertion sort.
 * 
 * 			Algorithm builds the final sorted list one item
 * 			at a time, looking at successive elements and 
 * 			sorting them (if successive elements are out
 * 			of order, function moves it into its correct
 * 			position and shifts subsequent elements 1 place 
 * 			back).
 * [Parameters]:	1 int vector & (list to be sorted)
 * [Returns]:		void
 */
void insertionSort(vector<int> &intList)
{
	size_t listLength = intList.size();
	
	for (size_t i = 0; i < listLength; i++) {
		int currInt = intList[i];
		
		for (size_t k = 0; k < i; k++) {
			if (currInt < intList[k]) {
				for (size_t j = i; j > k; j--)
					intList[j] = intList[j - 1];
				intList[k] = currInt;
				break;
			}
		}
	}
}

/******************************** 
 *          Merge Sort          *
 ********************************/
/* [Name]:		mergeSort
 * [Purpose]:		Sorts the given intList with merge sort.
 * 
 * 			Algorithm recursively splits lists (and subsequent
 * 			sublists) into 2 sublists, each containing half of
 * 			the lists' elements, till sublists are size 1.
 * 			Sublists are then merged into a sorted list 
 * 			(smallest int from both sublists get recursively
 * 			 added into the new, sorted list).
 * [Parameters]:	1 int vector & (list to be sorted)
 * [Returns]:		void
 */
void mergeSort(vector<int> &intList)
{
	if (intList.size() <= 1)
		return;
	
	vector<int> leftList;
	vector<int> rightList;
	size_t middle = intList.size() / 2;
	
	for (size_t i = 0; i < middle; i++)
		leftList.push_back(intList[i]);
	for (size_t i = middle; i < intList.size(); i++)
		rightList.push_back(intList[i]);
	
	mergeSort(leftList);
	mergeSort(rightList); 
	
	intList = merge(leftList, rightList);
}

/* [Name]:		merge
 * [Purpose]:		The ints from the 2 given lists are sorted into
 * 			a new list. Smallest ints from both lists are
 * 			successively added.
 * [Parameters]:	2 int vectors & (lists that will be merged)
 * [Returns]:		1 int vector (sorted list from the 2 given sublists)
 */
vector<int> merge(vector<int> &leftList, vector<int> &rightList)
{
	vector<int> sortedList;
	
	while (leftList.size() > 0 or rightList.size() > 0) {
		if (leftList.size() > 0 and rightList.size() > 0) {
			if (leftList.front() < rightList.front())
				pushSmallest(sortedList, leftList);
			else
				pushSmallest(sortedList, rightList);

		}
		
		else if (leftList.size() > 0) {
			append(sortedList, leftList);
			break;
		}
		
		else { // rightList.size() > 0
			append(sortedList, rightList);
			break;
		}
	}
	
	return sortedList;
}

/* [Name]:		pushSmallest
 * [Purpose]:		Push the front-most element from the sourceList into
 * 			the mainList.
 * [Parameters]:	2 int vectors & (mainList & sourceList)
 * [Returns]:		void
 */
void pushSmallest(vector<int> &mainList, vector<int> &sourceList)
{
	mainList.push_back(sourceList.front());
	sourceList.erase(sourceList.begin());
}

/* [Name]:		append
 * [Purpose]:		Appends the 2 given lists.
 * [Parameters]:	2 int vectors & (2 lists to be appended)
 * [Returns]:		void
 */
void append(vector<int> &mainList, vector<int> &appendedList)
{
	for (size_t i = 0; i < appendedList.size(); i++)
		mainList.push_back(appendedList[i]);
}

/******************************** 
 *          Quick Sort          *
 ********************************/
/* [Name]:		quickSort
 * [Purpose]:		Algorithm that dividies, conquers and combines a list 
 * 			by first partitioning it based on a pivot (ints <
 * 			than the pivot is to the left of the pivot, while ints
 * 			> are to its right). Since partition is within the
 * 			vector, recursively doing this will produce a sorted
 * 			list.
 * [Parameters]:	1 int vector & (list to be sorted)
 * [Returns]:		void
 */
void quickSort(vector<int> &intList)
{
	if (intList.size() > 1)
		quickSort(intList, 0, intList.size() - 1);
}

/* [Name]:		quickSort
 * [Purpose]:		Helper function for quickSort that does all the 
 * 			sorting.
 * [Parameters]:	1 int vector & (list to be sorted), 2 ints (L/R index)
 * [Returns]:		void
 */
void quickSort(vector<int> &intList, int leftIndex, int rightIndex)
{
	if (leftIndex >= rightIndex)
		return;
	
	int leftPtr, rightPtr, pivot;
	leftPtr  = leftIndex;
	rightPtr = rightIndex;
	pivot    = intList[(leftPtr + rightPtr) / 2];
	
	while (leftPtr <= rightPtr) {
		while (intList[leftPtr] < pivot)
			leftPtr++;
		while (intList[rightPtr] > pivot)
			rightPtr--;
		if (leftPtr <= rightPtr) {
			swap(intList, leftPtr, rightPtr);
			leftPtr++;
			rightPtr--;
		}
	}
	
	quickSort(intList, leftIndex, rightPtr);
	quickSort(intList, leftPtr, rightIndex);
}

/* [Name]:		swap
 * [Purpose]:		Swaps the elements at the 2 given indexes in the
 * 			intList.
 * [Parameters]:	1 int vector &, 2 ints (indexes)
 * [Returns]:		void
 */
void swap(vector<int> &intList, int leftIndex, int rightIndex)
{
	int tmp = intList[leftIndex];
	intList[leftIndex]  = intList[rightIndex];
	intList[rightIndex] = tmp;
}

//------------------------------//