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
	std::cout << "{";
	for (int i = 0; i < length(); i++){
      if(i != length() - 1){
        	std::cout << (*this)[i] << " ";
        }else {
          std::cout << (*this)[i];
        }
	}
	std::cout << "}";
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
  // Your implementation will go here
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
   // Your implementation goes here

	Array a3(a1.length());
	if (a1.length() == a2.length()){
		for (int i = 0; i < a1.length(); i++) {
			a3[i] = a1[i] + a2[i];
		}
	}
	return a3;
}

Array operator+(const Array& a1, int x)
{
  // Your implementation goes here
	Array a3(a1.length());
	for (int i = 0; i < a1.length(); i++) {
		a3[i] = a1[i] + x;
	}
  return a3;
   
}

Array operator+(int x, const Array& a2)
{
   // Your implementation goes here
	Array a3(a2.length());
	for (int i = 0; i < a2.length(); i++) {
		a3[i] = a2[i] + x;
	}
  return a3;
}
