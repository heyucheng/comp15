// QuickSort.h

#ifndef POOR_QUICK_SORT_H
#define POOR_QUICK_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"
#include <cstdlib>

class PoorQuickSort : public SortingAlgorithm {
 
 public:
  virtual void sort(Array& A)
  {
    // Your quick sort implementation goes here
    quickSort(A, 0, A.length() - 1);
  }
  void quickSort(Array& A, int low, int high)
  {
    if (low >= high) {
      return;
    }
    int pivotIndex = low; // pivot is the always be the first element
    int pivot = A[pivotIndex];
    A[pivotIndex] = A[high];
    A[high] = pivot;
    int i = low - 1;
    int j = high;
    do {
      do { i++; } while (A[i] < pivot);
      do { j--; } while (A[j] > pivot and j > low);
      if (i < j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
      }
    } while (i < j);
    A[high] = A[i]; 
    A[i] = pivot;      
    quickSort(A, low, i-1);
    quickSort(A, j+1, high);
  }


  void swap(int i, int j) {
  	int temp = i;
  	i = j;
  	j = temp;
  	return;
  } 
};

#endif

