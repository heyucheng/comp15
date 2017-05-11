// InsertionSort.h

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"

class InsertionSort : public SortingAlgorithm {
 public:
  virtual void sort(Array& A)
  {
    // Your insertion sort algorithm goes here
    for (int i = 1; i < A.length(); i++) {
    	int temp = A[i];
      int j = i-1;
    	while (j >= 0 and A[j] > temp) {
        A[j+1] = A[j];
        j--;
      }
      A[j+1] = temp;
    } 
  } 
};

#endif

