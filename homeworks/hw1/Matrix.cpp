// Array.cpp

#include <iostream>
#include <cstdlib>
#include "Matrix.h"

// Default Constructor
Matrix::Matrix()
  : mRowLen(0), mColumnLen(0), mM(NULL)
{
}

// Non-default constructor
Matrix::Matrix(int aRowLen, int aColumnLen)
{
  allocate(aRowLen, aColumnLen);

  for(int i = 0; i < aRowLen; i++) {
    for (int j = 0; j < aColumnLen; j++) {
      mM[i][j] = 0;    
    }
  } 
}

// Copy constructor
Matrix::Matrix(const Matrix& other)
{
  copy(other);
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other)
{
  if (this != &other) {
    cleanup();
    copy(other);
  }
  return (*this);
}

// Overload ()
int Matrix::getValue(const int i, const int j) const
{
  if (i < 0 or i >= mRowLen) {
    std::cout << "The row length is invalid" << std::endl;
  }
  if (j < 0 or j >= mColumnLen) {
    std::cout << "The column length is invalid" << std::endl;
  }
  return mM[i][j];
}

// Set the value of mM[i][j] to value
void Matrix::setValue(const int i, const int j, const int value)
{
  if (i < 0 or i >= mRowLen) {
    std::cout << "The row length is invalid" << std::endl;
  }
  if (j < 0 or j >= mColumnLen) {
    std::cout << "The column length is invalid" << std::endl;
  }
  mM[i][j] = value;    
}

// Destructor
Matrix::~Matrix()
{
  cleanup();
}

void Matrix::input(std::istream & s)
{
  if(mRowLen == 0 and mColumnLen == 0) {

    std::cout << "Enter the number of rows: ";
    s >> mRowLen;
    std::cout << "Enter the number of columns: ";
    s >> mColumnLen;
    allocate(mRowLen, mColumnLen);
  }

  std::cout << "Enter the matrix:" << std::endl;

  for (int i = 0; i < mRowLen; i++) {
    for(int j = 0; j < mColumnLen; j++){
      std::cout << "Matrix[" << i << "][" << j << "] =" ;
      s >> mM[i][j];
    }
  }
}
void Matrix::output(std::ostream & s) const
{
  for (int i = 0; i < mRowLen; i++) {
    for (int j = 0; j < mColumnLen; j++) {
      s << mM[i][j] << " ";
    }
    s << std::endl;
  }
}

int Matrix::columnLen() const
{
  return mColumnLen;
}

int Matrix::rowLen() const
{
  return mRowLen;
}

void Matrix::allocate(int aRowLen, int aColumnLen)
{
  if (aRowLen < 0 || aColumnLen < 0) {
    std::cout << "Negative index." << std::endl;
    mRowLen = 0;
    mColumnLen = 0;
    mM = nullptr;
    return;
  }

  setLength(aRowLen, aColumnLen);
  mM = new int *[aRowLen];
  for(int i = 0; i < aRowLen; i++) {
    mM[i] = new int[aColumnLen]; 
  }
}

void Matrix::setLength(int aRowLen, int aColumnLen)
{
  mRowLen = aRowLen;
  mColumnLen = aColumnLen;
}

void Matrix::copy(const Matrix & other)
{
  allocate(other.rowLen(), other.columnLen());

  for(int i = 0; i < rowLen(); i++) {
    for (int j = 0; j < columnLen(); j++) {
      mM[i][j] = other.mM[i][j];    
    }
  }
}

void Matrix::cleanup()
{
  for (int i = 0; i < mRowLen; i++){
    delete[] mM[i];
  }
  delete[] mM;
}
//Overload operator >>
std::istream& operator>>(std::istream& s, Matrix& m)
{
  m.input(s);
  return s;
}
//Overload operator <<
std::ostream& operator<<(std::ostream& s, const Matrix& m)
{
  m.output(s);
  return s;
}
//Overload operator ==
bool operator==(const Matrix & m1, const Matrix & m2)
{
  if ((m1.rowLen() != m2.rowLen()) || (m1.columnLen() != m2.columnLen())) {
    return false;
  }
  for (int i = 0; i < m1.rowLen(); i++) {
    for (int j = 0; j < m1.columnLen(); j++) {
      if(m1.getValue(i,j) != m2.getValue(i,j))
        return false;
    }
  }
  return true;
}
// Overload operator +
Matrix operator+(const Matrix & m1, const Matrix & m2)
{
  if (m1.rowLen() != m2.rowLen()) {
    std::cout << "Inconsistent row lengths of matrixes." << std::endl;
    exit(1);
  }
  if (m1.columnLen() != m2.columnLen()) {
    std::cout << "Inconsistent column lengths of matrixes." << std::endl;
    exit(1);
  }

  Matrix m3(m1);

  for (int i = 0; i < m3.rowLen(); i++) {
    for (int j = 0; j < m3.columnLen(); j++) {
    int sum = m3.getValue(i,j) + m2.getValue(i,j);
    m3.setValue(i, j, sum);
    }
  }
  return m3;
}
// Overload operator *
Matrix operator*(const Matrix  & m1, const Matrix & m2)
{
  if (m1.columnLen() != m2.rowLen()) {
    std::cout << "Inconsistent size of matrixes." << std::endl;
    exit(1);
  }

  Matrix m3(m1.rowLen(), m2.columnLen());

  for (int i = 0; i < m1.rowLen(); i++) {
    int sum = 0;
    int mul = 0;
    for (int j = 0; j < m2.columnLen(); j++) {
      for (int k = 0; k < m1.columnLen(); k++) {
        mul = m1.getValue(i,k) * m2.getValue(k,j);
        sum = sum + mul;
      } 
      m3.setValue(i, j, sum);
      sum = 0;
      mul = 0;
    }
  }
  return m3;
}





