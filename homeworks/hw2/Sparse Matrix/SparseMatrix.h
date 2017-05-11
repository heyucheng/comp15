
#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <iostream>
using namespace std;


/// A node representing the non-zero sparse matrix entry
class NonZeroEntryNode {

  // Your code goes here

 private:
  /// a non-zero entry in the matrix
  int mVal;
  /// Row number
  int mRowNum;
  /// Col number
  int mColNum;
  
  /// Pointers to the next row and col
  NonZeroEntryNode* mNextRowNode;
  NonZeroEntryNode* mNextColNode;

};

/// A pointer to an entry node
class PointerListNode{
  
  // Your code goes here

 private:
  /// Pointer to the first entry node in a particular row/col
  NonZeroEntryNode* mFirstEntryNode;
  /// Next row/col
  PointerListNode* mNext;

};


/// List of pointers to the nodes
class PointerList {

  // Your code goes here

 private:
  /// First pointer list node (either in row/col)
  PointerListNode* mFirstPointerListNode;
  /// Size of row/col
  int mSize;
};

/// Row Pointer list used for inserting the entry node in an appropriate row
class RowPointerList : public PointerList {

  // Your code goes here
};

/// Col Pointer list used for inserting the entry node in an appropriate column
class ColPointerList : public PointerList {

  // Your code goes here

};

class SparseMatrix {


 public:

  // Constructor
  explicit SparseMatrix(int aNumRows, int aNumCols)
    : mRowPointerList(aNumRows), mColPointerList(aNumCols)
  {
    for (int i = 0; i < aNumRows; ++i) {
      mRowPointerList.addNode();
    }
    for (int i = 0; i < aNumCols; ++i) {
      mColPointerList.addNode();
    }
  }

  // Copy constructor
  SparseMatrix(const SparseMatrix& other)
    : mRowPointerList(other.nrows()), mColPointerList(other.ncols())
  {
    for (int i = 0; i < mRowPointerList.size(); ++i) {
      mRowPointerList.addNode();
    }
    for (int i = 0; i < mColPointerList.size(); ++i) {
      mColPointerList.addNode();
    }
    for (int i = 0; i < mRowPointerList.size(); ++i) {
      for (int j = 0; j < mColPointerList.size(); ++j) {
	int otherVal = other(i, j);
	if (otherVal != 0) {
	  set(i, j, otherVal);
	}
      }
    }
  }

  // Assignment operator
  SparseMatrix& operator=(const SparseMatrix& other)
  {
    // Discard the self-assignment scenario
    if (this != &other) {
      // Clean up existing entries for this
      mRowPointerList.cleanup();

      // copy from other
      for (int i = 0; i < mRowPointerList.size(); ++i) {
	for (int j = 0; j < mColPointerList.size(); ++j) {
	  int otherVal = other(i, j);
	  if (otherVal != 0) {
	    set(i, j, otherVal);
	  }
	}
      }
    }
    return *this;
  }

  int nrows() const { return mRowPointerList.size(); }
  int ncols() const { return mColPointerList.size(); }

  // Functor for fetching an entry
  int operator()(int aRow, int aCol) const
  {
    // Your code goes here
  }

  /// Set the entry
  void set(int aRow, int aCol, int aValue)
  {
    // Your code goes here
  }
  
  /// Input
  void input(istream& s)
  {
    cout << "Enter the non-zero elements with row and col specification" 
	 << endl;
    int row, col, entry;
    bool isMoreEntry;
    while (1) {
      cout << "Row: ";
      s >> row;
      if (row >= nrows()) {
	cout << "Illegal entry: Row number is out of range. Try again." << endl;
	continue;
      }
      cout << "Col: ";
      s >> col;
      if (col >= ncols()) {
	cout << "Illegal entry: Col number is out of range. Try again." << endl;
	continue;
      }
      cout << "Entry (" << row << "," << col << ") = ";
      s >> entry;
      if (entry == 0) {
	cout << "No point in entering zero entries. Try again." << endl;
	continue;
      }
      // Set the entry
      set(row, col, entry);
      cout << "More? (1/0) ";
      cin >> isMoreEntry;
      if (!isMoreEntry) {
	break;
      }
    }
  }

  /// Output
  void output(ostream& s) const
  {
    s << endl;
    for (int i = 0; i < nrows(); ++i) {
      for (int j = 0; j < ncols(); ++j) {
	s << (*this)(i, j) << " ";
      }
      s << endl;
    }
    s << endl;
  }

 private:

  /// List of pointers to the rows
  RowPointerList mRowPointerList;
  /// List of pointers to the cols
  ColPointerList mColPointerList;
};

/// Matrix multiplication for sparse matrices
SparseMatrix operator*(const SparseMatrix& sm1, const SparseMatrix& sm2)
{
  // Your code goes here
}

/// Taking sparse matrix as input
istream& operator>>(istream& s, SparseMatrix& sm)
{
  sm.input(s);
  return s;
}

/// Outputting sparse matrix
ostream& operator<<(ostream& s, const SparseMatrix& sm)
{
  sm.output(s);
  return s;
}

#endif
