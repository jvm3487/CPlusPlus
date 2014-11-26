#include "IntMatrix.h"

IntMatrix::IntMatrix(){
  numRows = 0;
  numColumns = 0;
  rows = new IntArray*;
  rows[0] = NULL;
}
IntMatrix::IntMatrix(int r, int c) {
  numRows = r;
  numColumns = c;
  rows = new IntArray*[r];
  for (int i=0; i<numRows; i++){
    rows[i] = new IntArray;
    *rows[i] = IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs)  {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray*[numRows];
  for (int i = 0; i < numRows; i++){
    rows[i] = new IntArray;
    *rows[i] = IntArray(rhs[i]);
  } 
}
IntMatrix::~IntMatrix() {
  for (int i=0; i < numRows; i++){
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs){      
    delete rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray*[numRows];
    for (int i = 0; i < numRows; i++){
      rows[i] = new IntArray;
      *rows[i] = IntArray(rhs[i]);
    }
    return *this;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows);
  return **(rows+index);
}
IntArray & IntMatrix::operator[](int index){
  assert(index < numRows);
  return **(rows+index);
}



bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows){ return false; }
  if (numColumns != rhs.numColumns){ return false; }
  for (int i = 0; i < numRows; i++){
    if (*(rows[i]) != *(rhs.rows[i])){ return false; }
  }
  return true;
}


IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  IntMatrix ans(numRows, numColumns);
  for (int i = 0; i < numRows; i++){
    for (int j = 0; j < numColumns; j++){
      (*(ans.rows[i]))[j] = (*(rows[i]))[j] + (*(rhs.rows[i]))[j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++){
    s << rhs[i];
    if (i + 1 != rhs.getRows()){
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
