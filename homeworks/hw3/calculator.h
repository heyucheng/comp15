#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <string>
#include <cmath>
#include "stack.h"
#include <sstream>

using namespace std;

class calculator {

 public:

 calculator()
   : mInfixInput(""), mPostfixOutput("")
    {}

  void readInput();
  void convertInputIntoPostfix();
  void outputPostfix() const;
  void evaluatePostfixIntoResult();
  void outputResult() const;
  bool isStopCondition() const;

 private:

  // Helper functions
  bool hasHigherPrecedenceThan(int aLHS, int aRHS) const;

  bool isOperator(int c) const;
  
 private:
  string mInfixInput;
  string mPostfixOutput;
  int mResult;

};

bool calculator::isStopCondition() const
{
  return (mInfixInput == ".");
}

void calculator::readInput()
{
  mInfixInput.clear();
  mPostfixOutput.clear();
  cin >> mInfixInput;
}

void calculator::outputPostfix() const
{
  cout << "Postfix = "
       << mPostfixOutput 
       << endl;
}

void calculator::outputResult() const
{
  cout << "Result = "
       << mResult
       << endl;
}

// Returns true if aLHS has a higher precedence than aRHS.
// Otherwise, returns false.
bool calculator::hasHigherPrecedenceThan(int aLHS, int aRHS) const
{
  if ((aRHS == '+' || aRHS == '-') &&
      (aLHS == '*' || aLHS == '/' || aLHS == '^')) {
    return true;
  }
  if ((aRHS == '+' || aRHS == '-' || aRHS == '*' || aRHS == '/') &&
      (aLHS == '^')) {
    return true;
  }
  if (aLHS == '^' && aRHS == '^') {
    return true;
  }
  return false;
}

bool calculator::isOperator(int c) const
{
  return ((c == '+') ||
	  (c == '-') ||
	  (c == '*') ||
	  (c == '/') ||
	  (c == '^'));
}

void calculator::convertInputIntoPostfix()
{
  // Your implementation goes here
  stringstream ss;
  stack tempStack;
  for (int i = 0; i < mInfixInput.length(); i++) {
    if (isOperator( mInfixInput[i] ) == true) {
      while (tempStack.isEmpty() == false and hasHigherPrecedenceThan(mInfixInput[i], tempStack.top()) == false ) {
          ss << (char)tempStack.top();
          tempStack.pop();
      }
          tempStack.push(mInfixInput[i]);
    } else {
      ss << mInfixInput[i] - '0';
    }
  }
  while (tempStack.isEmpty() == false) {
    ss << (char)tempStack.top();
    tempStack.pop();
  }
  ss >> mPostfixOutput;
}

void calculator::evaluatePostfixIntoResult()
{
  // Your implementation goes here
  stack tempStack;
  int tempResult = 0;
  int digit1 = 0;
  int digit2 = 0;
  for (int i = 0; i < mPostfixOutput.length(); i++) {
    if (isOperator(mPostfixOutput[i]) == false) {
      tempStack.push(mPostfixOutput[i]);
    } else {
      digit2 = tempStack.top() - '0';
      tempStack.pop();
      digit1 = tempStack.top() - '0';
      tempStack.pop();
      if (mPostfixOutput[i] == '+') {
        tempResult = digit1 + digit2;
      }
      if (mPostfixOutput[i] == '-') {
        tempResult = digit1 - digit2;
      }
      if (mPostfixOutput[i] == '*') {
        tempResult = digit1 * digit2;
       }
      if (mPostfixOutput[i] == '/') {
        tempResult = digit1 / digit2;
      }
      if (mPostfixOutput[i] == '^') {
        tempResult = pow(digit1, digit2);
      }
      tempStack.push(tempResult + '0');
      
    }
  }
  mResult = tempStack.top() - '0';
  tempStack.pop();
  if (tempStack.isEmpty() == false) {
    cout << "Malformed expression" << endl;        
  }
}

#endif
