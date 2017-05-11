#ifndef JUMBO_H 
#define JUMBO_H

#include <iostream> 

using namespace std; 

class Jumbo { 
  
 private:
  int* mInt;
  int mLen;



  void allocate(int aLen);
  void cleanup();
  void copy(const Jumbo& other);

  /* You decicde what goes here */
  
 public:
  
  // Default constructor

  Jumbo();

  // Destructor

  ~Jumbo();

  // Create from an existing integer value 
  Jumbo( unsigned int value ); 	
  
  // Create from a string representation (e.g. '73287473284237842947328432423789427')
  Jumbo( const string& s); 
		
  // Add the argument Jumbo to `this' one and return the result
  Jumbo add(const Jumbo& other) const;		

  // Convert value to a string for printing 
  string str() const;

  // Assign operator
  Jumbo & operator=(const Jumbo & other);

  // Copy constructor

  Jumbo(const Jumbo & other);

  int length() const;
  void setLength(int aLen);
  int getIntLen(unsigned int n);
  int getStrLen(string s);

};


#endif
