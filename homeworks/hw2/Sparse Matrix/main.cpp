
#include <iostream>
#include "SparseMatrix.h"

using namespace std;

int main()
{
  // Square matrix test
  SparseMatrix sm1(3,3);
  cout << "Enter sm1" << endl;
  cin >> sm1;
  cout << "sm1: " << endl;
  cout << sm1;

  SparseMatrix sm2(3,3);
  cout << "Enter sm2" << endl;
  cin >> sm2;
  cout << "sm2: " << endl;
  cout << sm2;

  SparseMatrix result(3,3);
  result = sm1 * sm2; // Assignment operator

  cout << "Output (sm1 * sm2): ";
  cout << result;
  
  // Non-square matrix test
  SparseMatrix sm3(10,20);
  cout << "Enter sm3" << endl;
  cin >> sm3;
  cout << "sm3: " << endl;
  cout << sm3;

  SparseMatrix sm4(20,6);
  cout << "Enter sm4" << endl;
  cin >> sm4;
  cout << "sm4: " << endl;
  cout << sm4;

  SparseMatrix result2(10,6);
  result2 = sm3 * sm4; // Assignment operator

  cout << "Output (sm3 * sm4): ";
  cout << result2;
  
  return 0;
}
