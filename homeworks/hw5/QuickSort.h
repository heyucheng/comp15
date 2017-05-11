// QuickSort.h

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"
#include <cstdlib>

class QuickSort : public SortingAlgorithm {
 
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
    int pivotIndex = pickPivot(A, low, high); // pivot is the 3-midian pick
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

  int pickPivot(Array& A, int low, int high) 
  {
    if (low == high - 1) {
      return low;
    }
    int mid = (low+high)/2;
    if (low > high) {
      if (mid > high) {
        if (low > mid) {
          return mid;
        } else {
          return low;
        }
      } else {
        return high;
      }
    } else {
      if (mid > high) {
        return high;
      } else {
        if (low > mid) {
          return low;
        } else {
          return mid;
        }
      }
    }

  }

  void swap(int i, int j) {
  	int temp = i;
  	i = j;
  	j = temp;
  	return;
  } 
};

#endif

