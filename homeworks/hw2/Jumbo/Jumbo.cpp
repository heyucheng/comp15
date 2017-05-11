#include <iostream>
#include <cmath>
#include <cstring>
#include <sstream>
#include "Jumbo.h"


// Default constructor
Jumbo::Jumbo()
	:mLen(0), mInt(NULL)
{
}


// Destructor
Jumbo::~Jumbo()
{
	cleanup();
}


// Set the length char and int array
void Jumbo::setLength(int aLen)
{
	mLen = aLen;
	return;
}


// Get the length from int input
int Jumbo::getIntLen(unsigned int n)
{	
	unsigned int m = n;
	if (m == 0){
		mLen = 1;
	} else {
		for (mLen = 0; m > 0; mLen++) {
			m = m / 10;
		}
	}
	return mLen;
}


// Get the length from string input
int Jumbo::getStrLen(string s)
{
	mLen = s.length();
	return mLen;
}


// Create from an existing integer value 
Jumbo::Jumbo(unsigned int value)
{
	mLen = getIntLen(value);
	allocate(mLen);
	unsigned int m = value;
	int i = mLen - 1;
	while(m) {
		mInt[i--] = m % 10;
		m /= 10;
	}

} 	
  
// Create from a string representation (e.g. '73287473284237842947328432423789427')
Jumbo::Jumbo(const string& s)
{
	mLen = s.length();
	allocate(mLen);
	char aChar[mLen + 1];
	strcpy (aChar, s.c_str());

	for (int i = 0; i < mLen; i++) {	
		mInt[i] = aChar[i] - '0';
	}

}
  
// Assign operator
Jumbo & Jumbo::operator=(const Jumbo& other)
{
  	if (this != &other) {
    	cleanup();
    	copy(other);
  	}

  return *this;
}

// Copy constructor
Jumbo::Jumbo(const Jumbo & other)
{
	copy(other);
}
		
// Add the argument Jumbo to `this' one and return the result
Jumbo Jumbo::add(const Jumbo & other) const
{
	int newLen;
	if (mLen >= other.length()) {
		newLen = mLen;	

	} else {
		newLen = other.length();

	}
	int otherInt[newLen];
	int Int[newLen];
	if (mLen >= other.length()) {
		for (int i = 0; i < newLen; i++) {
			otherInt[i] = 0;
		}
		for (int i = newLen - 1; i >= newLen - other.length(); i--) {
			otherInt[i] = other.mInt[i - newLen + other.length()];
		}
		for (int i = 0; i < newLen; i++) {
			Int[i] = mInt[i];
		}
	} else {
		for (int i = 0; i < newLen; i++) {
			otherInt[i] = other.mInt[i];
		}
		for (int i = 0; i < newLen; i++) {
			Int[i] = 0;
		}
		for (int i = newLen - 1; i >= newLen - mLen; i--) {
			Int[i] = mInt[i - newLen + mLen];
		}
	}


	int newInt[newLen];
	for (int i = 0; i < newLen; i++) {
		newInt[i] = 0;
	}
	for (int j = newLen - 1; j >= 0; j--) {
		if (j == 0) {
			newInt[j] = Int[j] + otherInt[j] + newInt[j];
		} 
		if (j > 0) {
			int m = Int[j] + otherInt[j] + newInt[j];
			newInt[j] = m % 10;
			newInt[j - 1] = m / 10;
		}
	}
	string s;
	stringstream ss;
	ss.clear();
	ss.str("");
	for (int i = 0; i < newLen; i++) {
		ss << newInt[i];
	}
	ss >> s;
	Jumbo newJumbo(s);

	return newJumbo;
}		

// Convert value to a string for printing 
string Jumbo::str() const
{
	string printStream;
	stringstream ss;
	ss.clear();
	
	for (int i = 0; i < mLen; i++) {
		ss << mInt[i];
	}
	ss >> printStream; 
	return printStream;
}

void Jumbo::cleanup()
{
	delete [] mInt;
}

void Jumbo::allocate(int aLen)
{
	setLength(aLen);
	mInt = new int [aLen];
}

void Jumbo::copy(const Jumbo & other)
{
	allocate(other.mLen);
	for (int i = 0; i < mLen; i++) {
		mInt[i] = other.mInt[i];
	}
}

int Jumbo::length() const
{
	return mLen;
}