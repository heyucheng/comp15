
#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
  Matrix m1(3, 3);
  cin >> m1;
  cout << "m1: " << endl;
  cout << m1 << endl;

  Matrix m2(3, 3);
  cin >> m2;
  cout << "m2: " << endl;
  cout << m2 << endl;

  Matrix m3(m1 + m2);

  cout << "m3: " << endl;
  cout << m3 << endl;

  Matrix m4;
  cin >> m4;
  cout << "m4: " << endl;
  cout << m4 << endl;

  Matrix m5(m3 * m4);
  cout << "m5: " << endl;
  cout << m5 << endl;
  
  // Comment out the following lines 
  // if you have not done the bonus question
  // In order to comment out, simply change 
  // "#if 1" to "#if 0"

#if 1
  IdentityMatrix i1(3);
  cout << "i1: " << endl;
  cout << i1 << endl;

  Matrix m6(m5 * i1);
  cout << "m6: " << endl;
  cout << m6 << endl;
#endif

  return 0;
}
