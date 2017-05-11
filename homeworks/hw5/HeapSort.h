
// HeapSort.h

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "Array.h"
#include "SortingAlgorithm.h"

using namespace std;

class HeapSort : public SortingAlgorithm {
 public:

  HeapSort(Array& A) : hA(A.length()+1), mLen(A.length())
  {}

  virtual void sort(Array& A)
  {
    // Your heap sort implementation goes here
    int n = mLen;

    for (int i = n; i > 0; i--) {
    	hA[i] = A[i-1];
    }   
    bottomUpHeap(hA, n);

    for(int i = 0; i < mLen; i++){
    	A[i] = hA[1];
      hA[1] = hA[n];
    	n--;
    	bubbleDown(hA, 1, n);
    } 
  }

 private:
  Array hA;
  int mLen;
  
  void bottomUpHeap(Array& A, int n)
  {
	  for (int i = n; i > 0; i--){
		  bubbleDown(A, i , n);
	  }

  }

  void bubbleDown(Array& A, int x, int n)
  {

  	int left = 2 * x;
  	int right = (2 * x) + 1;
    int temp = A[x];
    int small;
  	if (right > n) {
      if (left > n) {
        return;
      } else {
        small = left;
      }
  	} else {
      if (A[left] >= A[right]) {
        small = right;
      } else {
        small = left;
      }
    }

  	if (A[x] > A[small]) {
  		A[x] = A[small];
  		A[small] = temp;
  		bubbleDown(A, small, n);
  	} else {
  		return;
  	}
  } 
};


#endif

