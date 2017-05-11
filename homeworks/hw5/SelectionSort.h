// SelectionSort.h

#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"

class SelectionSort : public SortingAlgorithm {
 public:
  virtual void sort(Array& A)
  {
    // Your selection sort algorithm goes here
    for (int i = 0; i < A.length(); i++) {
    	int min = A[i];
    	int index = i;
    	for (int j = i; j < A.length(); j++){
    		if (min > A[j]) {
    			min = A[j];
    			index = j;
    		}
    	}

    	A[index] = A[i];
    	A[i] = min;
    }
  }
};

#endif

