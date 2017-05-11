// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
 public:
  // Default constructor
  Matrix();
  // Non-defualt constructor
  Matrix(int aRowLen, int aColumnLen);
  // Copy constructor
  Matrix(const Matrix & other);
  // Assign operator
  Matrix & operator=(const Matrix & other);
  // Destructor
  ~Matrix();


  void input(std::istream & s = std::cin);
  void output(std::ostream & s = std::cout) const;

  // Get the value of mM[i][j]
  int getValue(const int i, const int j) const; 
  // Set the value of mM[i][j] to value
  void setValue(const int i, const int j, const int value);
  // Get mRowLen
  int rowLen() const;
  // Get mColumnLen
  int columnLen() const;

private:
  int ** mM;
  int mRowLen;
  int mColumnLen;

  void allocate(int aRowLen, int aColumnLen);
  void setLength(int aRowLen, int aColumnLen);
  void copy(const Matrix & other);
  void cleanup();
};

class SquareMatrix: public Matrix
{
public:
  // Constructor
  SquareMatrix(int size)
    :Matrix(size, size)
  {
  }
};

class IdentityMatrix: public SquareMatrix
{
public:
  // Constructor
  IdentityMatrix(int size)
    :SquareMatrix(size)
  {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (i == j) {
          Matrix::setValue(i, j, 1);
        }
      }
    }
  }
}; 



std::istream & operator>>(std::istream & s,       Matrix & a);
std::ostream & operator<<(std::ostream & s, const Matrix & a);

bool operator==(const Matrix & m1, const Matrix & m2);

Matrix operator+(const Matrix & m1, const Matrix & m2);

Matrix operator*(const Matrix & m1, const Matrix & m2);




#endif