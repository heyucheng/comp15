#include "TaxiDriver.h"
#include "Array.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readNYCTaxiDrivers(Array<NYCTaxiDriver>& aTaxiDrivers)
{
  ifstream ifs("nyc_taxi_drivers.txt");
  string line;
  // read the heading away
  getline(ifs, line);
  while(getline(ifs, line)) {
    // line contains the relevant portion of each line 
    // read from the file
    string medNumStr = line.substr(0, 7);
    size_t firstCommaPos = line.find(",");
    string lastName = line.substr(8, firstCommaPos - 8);
    string substrStartingComma = line.substr(firstCommaPos);
    size_t secondQuotesPos = substrStartingComma.find("\"");
    string firstName = substrStartingComma.substr(1, secondQuotesPos-1);
    unsigned int medNo = atoi(medNumStr.c_str());
    NYCTaxiDriver taxiDriver(medNo, lastName, firstName);
    aTaxiDrivers.add(taxiDriver);
  }
}

void findAllMatchingLastName(const Array<NYCTaxiDriver>& aTaxiDrivers, 
		     const string aLastName,
		     Array<NYCTaxiDriver>& aMatchedDrivers)
{
  // Your code goes here

  for (int i = 0; i < aTaxiDrivers.getSize(); i++) {
    NYCTaxiDriver driver = aTaxiDrivers[i];
    if (driver.getLastName() == aLastName) {
      aMatchedDrivers.add(driver);
    }
  }

}

int binarySearch(const Array<NYCTaxiDriver>& aSortedList,
		  unsigned int aKey,
		  int aBegin,
		  int aEnd
		  ) 
{
  // Your code goes here
  int mid = (aBegin + aEnd) / 2;
  if (aBegin > aEnd) {
    return -1;
  }
  if (aKey < aSortedList[mid].getMedallionNumber()) {
    return binarySearch(aSortedList, aKey, aBegin, mid -1);
  }
  if (aKey > aSortedList[mid].getMedallionNumber()) {
    return binarySearch(aSortedList, aKey, mid + 1, aEnd);
  }
  return mid;
}

void simpleSortByMedallionNumber(Array<NYCTaxiDriver>& aMatchedDrivers)
{
  // Your code goes here

  for (int i = 0; i < aMatchedDrivers.getSize() - 1; i++) {
    int x = i;
    for(int j = i; j < aMatchedDrivers.getSize() - 1; j++) {
      if (aMatchedDrivers[x].getMedallionNumber() < aMatchedDrivers[j].getMedallionNumber()) {
      } else {
        x = j;
      }
    }

    NYCTaxiDriver temp;
    temp = aMatchedDrivers[x];
    aMatchedDrivers[x] = aMatchedDrivers[i];
    aMatchedDrivers[i] = temp;
  }

}



void getAllManhattanMedallions(Array<unsigned int>& aManhattanMedallions)
{
  ifstream ifs("nyc_medallion_numbers_traveling_in_manhattan.txt");
  string line;
  while(getline(ifs, line)) {
    unsigned int medNo = atoi(line.c_str());
    aManhattanMedallions.add(medNo);
  }
}

void printTheMatchingDrivers(const Array<unsigned int>& aManhattanMedallions,
			    const Array<NYCTaxiDriver>& aMatchedDrivers)
{
  // Your code goes here
  int x = 1;
  for (int i = 0; i < aManhattanMedallions.getSize(); i++) {

    int j = binarySearch(aMatchedDrivers, aManhattanMedallions[i], 0, aMatchedDrivers.getSize() - 1);

    if(j != -1) {

      cout << "Match " << x << ":"<< endl << aMatchedDrivers[j] << endl;
      x = x + 1;
    }
  }
}

int main()
{
  Array<NYCTaxiDriver> allDrivers;
  // Get all drivers
  readNYCTaxiDrivers(allDrivers);
  cout << "Total number of legal taxi drivers = " 
       << allDrivers.getSize() << endl;
  // cout << allDrivers << endl;
  cout << "---------------------" << endl;

  Array<NYCTaxiDriver> matchedDrivers;
  // Match all the drivers with the last name "SINGH"
  // (Complexity: n)
  findAllMatchingLastName(allDrivers, "SINGH", matchedDrivers);
  cout << "Total matching drivers = " 
       << matchedDrivers.getSize() << endl;
  // Sort the matched drivers (complexity: k^2)
  simpleSortByMedallionNumber(matchedDrivers);
  // cout << matchedDrivers << endl;
  cout << "---------------------" << endl;

  Array<unsigned int> manhattanMedallions;
  // Get the medallion numbers of taxis that traveled Manhattan
  // that day (complexity: m)
  getAllManhattanMedallions(manhattanMedallions);
  cout << "Total number of taxis traveling in Manhattan = " 
       << manhattanMedallions.getSize() << endl;
  // cout << manhattanMedallions << endl;
  cout << "---------------------" << endl;

  // Match and print the drivers
  // (Complexity: m * log k)
  printTheMatchingDrivers(manhattanMedallions, matchedDrivers);
  return 0;
}
