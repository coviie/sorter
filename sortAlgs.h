/*
 *  sortAlgs.h
 *  Sort Declarations
 *  	   Written by : Jia Wen Goh
 *                 On : 01-04-2017
 * 
 *  Declarations of the 3 sorts, insertionSort, mergeSort and quickSort.
 *  Helper functions are excluded to preserve functional abstraction.
 */

#ifndef SORTALGS_H_
#define SORTALGS_H_

#include <iostream>
#include <vector>

void		insertionSort(std::vector<int>&); // Insertion Sort
void		mergeSort(std::vector<int>&);	  // Merge Sort
void		quickSort(std::vector<int>&);	  // Quick Sort

#endif

