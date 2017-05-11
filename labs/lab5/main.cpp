
#include <iostream>
#include <fstream>
#include "bst.h"

using namespace std;

int main()
{
  BST bst;
  cout << "Enter the number of nodes: ";
  int n;
  cin >> n;
  if (n <= 0) {
    cout << "The number of nodes must be positive." << endl;
    exit(1);
  }
  int* preorder = new int [n];
  int* inorder = new int [n];
  cout << "Enter the preorder sequence: " << endl;
  for (int i = 0; i < n; i++) {
    cout << "preorder[" << i << "] = ";
    cin >> preorder[i];
  }
  cout << "Enter the inorder sequence: " << endl;
  for (int i = 0; i < n; i++) {
    cout << "inorder[" << i << "] = ";
    cin >> inoryesder[i];
  }
  int currIndex = 0;
  (void) bst.constructTreeFromTraversals(preorder, inorder, 0, n-1, currIndex);
  ofstream of;
  of.open("output_tree.dot");
  of << bst;
  delete [] preorder;
  delete [] inorder;


  return 0;
}
