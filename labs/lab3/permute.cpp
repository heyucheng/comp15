
#include <iostream>

using namespace std;

void permute(char* L, int n, int r, char* P, int m);
void remove(char* L, int j, int n, char* newList);
int main()
{
  cout << "Number of chars (n): ";
  unsigned int n;
  cin >> n;
  char* alphabets = new char [n+1];
  cout << "Alphabets: ";
  cin >> alphabets;
  cout << "Number of alphabets in the permutations (r): ";
  unsigned int r;
  cin >> r;
  if (r > n) {
    cout << "r cannot be greater than n" << endl;
    exit(1);
  }
  cout  << "Permutations of " 
	<< alphabets 
	<< " taking " 
	<< r 
	<< " alphabets at a time." 
	<< endl;

  	char* P = new char [r+1];
  // Print the permutations of n alphabets taken r at a time
  
	permute(alphabets, n, r, P, 0);
  // Your code goes here
  	delete [] alphabets;
  	delete [] P;
  	return 0;
}

void permute(char* L, int n, int r, char* P, int m)
{	
  	if (r == 0) {
		P[m] = '\0';
		cout << P << endl;
  	} else { 
    		for (int j = 0; j < n; j++) {
      			P[m] = L[j];
			char* newList = new char [n-1];
			remove(L, j, n, newList);
			permute(newList, n-1, r-1, P, m+1);
			delete [] newList;
    		}
  	}
}

void remove(char* L, int j, int n, char* newList)
{
	for (int i = 0; i < j; i++){
		newList[i] = L[i];
	}
  	for (int i = j; i < n-1; i++){
		newList[i] = L[i+1];
	}
	return;
}
