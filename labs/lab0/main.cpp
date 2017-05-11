// main.cpp

#include <iostream>
#include "Array.h"

using namespace std;

int main()
{
  Array a1(-1); // Non-default constructor
  
  Array a2; // constructor

  cout << "a2: " 
       << a2  // Overloaded << operator
       << endl; 
  
  Array a3(10); // Non-default constructor

  for (int i = 0; i < a3.length(); i++) {
    a3[i] = i + 1; // overloaded [] operator
  }
    
  Array a4(a3); // Copy constructor

  cout << "a4: " 
       << a4 
       << "; a3: " 
       << a3 
       << endl;
  
  Array a5; // Default constructor
  
  a5 = a4; // Assignment operator

  cout << "a5: " 
       << a5 
       << endl;
  
  // overloaded == operator
  if (a4 == a5) { 
    cout << "a4 is equal to a5" << endl;
  } else {
    cout << "a4 is not equal to a5" << endl;
  }
  
  cin >> a5; // Overloaded >> operator
  cout << "a5: " 
       << a5 // Overloaded << operator 
       << endl;
  
  Array a6; // Default constructor
  a6 = a5 + 3; // Overloaded + operator
  cout << "a6: " 
       << a6  // Overloaded << operator
       << endl;

  Array a7 = a4 + a6; // Overloaded + operator; Overloaded assignment operator
  cout << "a7: " 
       << a7  // Overloaded << operator
       << endl;

  return 0;
}
