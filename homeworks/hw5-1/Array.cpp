// Array.cpp

#include <iostream>
#include "Array.h"
#include "SortingAlgorithm.h"

// Default Constructor
Array::Array()
  : mLen(0), mA(NULL), mSortingAlgorithm(NULL)
{
}

// Non-default constructor
Array::Array(int aLen)
  : mSortingAlgorithm(NULL)
{
  allocate(aLen);
  
  for (int i = 0; i < length(); i++) {
    (*this)[i] = 0;
  }
}

// Copy constructor
Array::Array(const Array& other)
{
  copy(other);
}

// Assignment operator
Array& Array::operator=(const Array& other)
{
  if (this != &other) {
    // cleanup();
    copy(other);
  }
  return *this;
}

// Destructor
Array::~Array()
{
  cleanup();
}

void Array::input(std::istream & s)
{
  int len = 0;
  std::cout << "Length of array: ";
  s >> len;
  allocate(len);

  for (int i = 0; i < length(); i++) {
    std::cout << "A[" << i << "] = ";
    s >> (*this)[i];
  }
}

void Array::output(std::ostream & s) const
{
  s << "{";
  for (int i = 0; i < mLen; i++) {
    if (i % 20 == 0) {
      s << std::endl;
    }
    s << " " << (*this)[i];
  }
  s << " }";
  s << std::endl;
}

const int & Array::operator[](int i) const
{
  if (i < 0 || i >= mLen) {
    std::cout << "Invalid array index." << std::endl;
    exit(1);
  }
  return mA[i];
}

int & Array::operator[](int i)
{
  if (i < 0 || i >= mLen) {
    std::cout << "Invalid array index." << std::endl;
    exit(1);
  }
  return mA[i];
} 

int Array::length() const
{
  return mLen;
}

void Array::allocate(int aLen)
{
  if (aLen < 0) {
    std::cout << "Negative index." << std::endl;
    mLen = 0;
    mA = NULL;
    return;
  }
  setLength(aLen);
  mA = new int[aLen];
}

void Array::setLength(int aLen)
{
  mLen = aLen;
}

void Array::copy(const Array & other)
{
  allocate(other.length());
  setSortingAlgorithm(other.sortingAlgorithm());

  for (int i = 0; i < length(); i++) {
    (*this)[i] = other[i];
  }
}

void Array::cleanup()
{
  delete [] mA;
}

void Array::setSortingAlgorithm(SortingAlgorithm* algo) 
{ 
  mSortingAlgorithm = algo; 
}

SortingAlgorithm* Array::sortingAlgorithm() const
{ 
  return mSortingAlgorithm; 
}

// Sorting using a chosen algorithm
void Array::sort()
{ 
  if (sortingAlgorithm() == NULL) {
    std::cerr << "Sorting algorithm is unknown." << std::endl;
    return;
  }
  sortingAlgorithm()->sort(*this);
}

//////////////////////////////////////////////////////
std::istream& operator>>(std::istream& s, Array& a)
{
  a.input(s);
  return s;
}

std::ostream& operator<<(std::ostream& s, const Array& a)
{
  a.output(s);
  return s;
}

bool operator==(const Array& a1, const Array& a2)
{
  if (a1.length() != a2.length()) {
    return false;
  }
  for (int i = 0; i < a1.length(); ++i) {
    if (a1[i] != a2[i]) {
	return false;
    }
  }
  return true;
}

Array operator+(const Array & a1, const Array & a2)
{
  if (a1.length() != a2.length()) {
    std::cout << "Inconsistent lengths of arrays." << std::endl;
    exit(1);
  }

  Array result(a1.length());

  for (int i = 0; i < result.length(); i++) {
    result[i] = a1[i] + a2[i];
  }

  return result;
}

Array operator+(const Array& a1, int x)
{
  Array result(a1);
  
  for (int i = 0; i < result.length(); i++) {
    result[i] += x;
  }
  return result;
}

Array operator+(int x, const Array& a2)
{
  return (a2 + x);
}


