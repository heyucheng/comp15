// Array.cpp

#include <iostream>
#include <cstdlib>
#include "Array.h"

// Default Constructor
Array::Array()
  : mLen(0), mA(NULL)
{
}

// Non-default constructor
Array::Array(int aLen)
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
    cleanup();
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
    s << " " << (*this)[i];
  }
  s << " }";
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
    mA = nullptr;
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

  for (int i = 0; i < length(); i++) {
    (*this)[i] = other[i];
  }
}

void Array::cleanup()
{
  delete [] mA;
}

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

  Array result(a1);

  for (int i = 0; i < result.length(); i++) {
    result[i] += a2[i];
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
// My code is here.

int Array::find(int aData)
{
    for (int i = 0; i < mLen; i++){

        if ((*this)[i] == aData){
            return i;  
        }
    }
    return -1;
}

void Array::insertAfter(int aExistingEntry, int aData)
{
    int targetIndex = find(aExistingEntry); // find the target index for the target data
    int * newPtr = mA; // create a new pointer to array.
    int newLen = mLen + 1; // create a newLen to satify the length of array

    allocate(newLen);   // this updates mLen to newLen, and upadate the mA.

    for(int i = 0; i < mLen - 1; i++) {
        (*this)[i] = newPtr[i]; // copy the old array to new array.

    }
    if(targetIndex != -1) {
        for(int i = newLen - 1; i > targetIndex + 1; i--) {
            (*this)[i] = (*this)[i - 1]; // shift right the data after targetIndex
        }
        (*this)[targetIndex + 1] = aData; // insert the aData after the targetIndex
    } else {
        (*this)[newLen - 1] = aData; // for not found data, just insert to the end of the array
    }
    delete [] newPtr; // release memory
}


void Array::deleteThis(int aData)
{
    int targetIndex = find(aData); // find target index                      

    if (targetIndex != -1){
        int newLen = mLen - 1;
        int * newPtr = mA;
        allocate(newLen); // same as insertAfter function, but the array will be changed when found the data

        for(int i = 0; i < targetIndex; i++) {
            (*this)[i] = newPtr[i]; // copy the data before target index
        }

        for(int i = targetIndex; i < newLen; i++){
            (*this)[i] = newPtr[i + 1]; // copy the data after target index
        }

        delete [] newPtr; // release memory
    }

}

