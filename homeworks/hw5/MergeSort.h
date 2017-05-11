// MergeSort.h

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"

class MergeSort : public SortingAlgorithm {

 public:
  virtual void sort(Array& A)
  {
    // Your merge sort algorithm goes here
  	mergeSort(A, 0, A.length() -1);
  	return;
  }
  void mergeSort(Array& A, int low, int high)
  {
  	int mid;
  	if (low < high) {
  		mid = (low + high)/2;
  		mergeSort(A, low, mid);
  		mergeSort(A, mid+1, high);
  		merge(A, low, high, mid);
  	}
  }
  void merge(Array& A, int low, int high, int mid)
  {
  	int mergeA[high+1];
  	int i = low;
  	int j = mid + 1;
    int index = low;
    while (i <= mid and j <= high) {
      if (A[i] < A[j]) {
        mergeA[index] = A[i];
        i++;
        index++;
      } else {
        mergeA[index] = A[j];
        j++;
        index++;
      }
    }
    while (i <= mid) {
      mergeA[index] = A[i];
      i++;
      index++;
    }
    while (j <= high) {
      mergeA[index] = A[j];
      j++;
      index++;
    }
    for (int k = low; k < index; k++) {
      A[k] = mergeA[k];
    }
  }

};

#endif

