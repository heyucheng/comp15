
#ifndef NYC_TAXI_DRIVER_H
#define NYC_TAXI_DRIVER_H

#include <iostream>

using namespace std;

class NYCTaxiDriver {

public:
  
 NYCTaxiDriver()
   : mMedallionNumber(-1), mLastName(""), mFirstName("")
    {}

 NYCTaxiDriver(unsigned int aLicNo, string aLastName, string aFirstName) 
   : mMedallionNumber(aLicNo), mLastName(aLastName), mFirstName(aFirstName)
  {} 

  // Copy constructor
  NYCTaxiDriver(const NYCTaxiDriver& other)
  {
    mMedallionNumber = other.getMedallionNumber();
    mLastName = other.getLastName();
    mFirstName = other.getFirstName();
  }

  // Assignment operator
  NYCTaxiDriver & operator=(const NYCTaxiDriver& other)
  {
    if (this != &other) {
      mMedallionNumber = other.getMedallionNumber();
      mLastName = other.getLastName();
      mFirstName = other.getFirstName();
    }
    return *this;
  }

  unsigned int getMedallionNumber() const { return mMedallionNumber; }
  string getLastName() const { return mLastName; }
  string getFirstName() const { return mFirstName; }

  void output(ostream & s = cout) const
  {
    s << mMedallionNumber << " "
      << mLastName << ","
      << mFirstName << endl;
  }
  
private:
  unsigned int mMedallionNumber;
  string mLastName;
  string mFirstName;

};


ostream& operator<<(ostream& s, const NYCTaxiDriver& a)
{
  a.output(s);
  return s;
}

#endif
