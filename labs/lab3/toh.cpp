
#include <iostream>

using namespace std;

void move(int n, char A, char B, char C);

int main()
{
  int n;
  cout << "Number of discs: ";
  cin >> n;
  cout << endl;
  // Disc ids
  const char A = 'A';
  const char B = 'B';
  const char C = 'C';
  cout << "Steps to move " 
       << n 
       << " discs from " 
       << A 
       << " to " 
       << B 
       << endl;
  // Recursively print the steps
  move(n, A, B, C);
  // Your code goes here

  return 0;
}

void move(int n, char A, char B, char C)
{
  if ( n == 1) {
    cout << "Move disc from " << A << " to " << B << endl;
  } else {
    n = n - 1;
    move(n, A, C, B);
    move(1, A, B, C);
    move(n, C, B, A);
  }
  return;
}