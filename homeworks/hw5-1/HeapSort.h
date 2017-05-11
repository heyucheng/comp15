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
  }

 private:
  Array hA;
  int mLen;
};

#endif

