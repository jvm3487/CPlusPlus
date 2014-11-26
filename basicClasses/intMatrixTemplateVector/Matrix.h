#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector< std::vector <T> > rows;
 public:
  Matrix(){
    numRows = 0;
    numColumns = 0;
    rows.push_back(std::vector<T>());
  }
  Matrix(int r, int c){
    numRows = r;
    numColumns = c;
    for (int i=0; i < numRows; i++){
      rows.push_back(std::vector<T>());
      rows[i].resize(numColumns);
    }
  }
  Matrix(const Matrix & rhs){
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    for (int i = 0; i < numRows; i++){
      rows.push_back(std::vector<T>());
      for (int j=0; j < numColumns; j++){
	rows[i].push_back(rhs.rows[i][j]);
      }
    }
  }
  ~Matrix(){}
  Matrix & operator=(const Matrix & rhs){
    if (this != &rhs){      
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      for (int i = 0; i < numRows; i++){
	rows.push_back(std::vector<T>());
	for(int j=0; j < numColumns; j++){
	  rows[i].push_back(rhs.rows[i][j]);
	}
      }
    }
    return *this;
  }
  int getRows() const{
    return numRows;
  }
  int getColumns() const{
    return numColumns;
  }
  const std::vector<T> & operator[](int index) const{
    assert(index < numRows);
    return rows.at(index);
  }
  std::vector<T> & operator[](int index){
    assert(index < numRows);
    return rows.at(index);
  }
  bool operator==(const Matrix & rhs) const{
    if (numRows != rhs.numRows){ return false; }
    if (numColumns != rhs.numColumns){ return false; }
    for (int i = 0; i < numRows; i++){
      for (int j = 0; j < numColumns; j++){
	if (rows[i][j] != rhs.rows[i][j]){	
	  return false; 
	}
      }
    }
    return true;
  }
  Matrix operator+(const Matrix & rhs) const{
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    Matrix ans(numRows, numColumns);
    for (int i = 0; i < numRows; i++){
      for (int j = 0; j < numColumns; j++){
	ans.rows[i][j] = rows[i][j] + rhs.rows[i][j];
      }
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs){
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++){
    s << "{";
    for (int j = 0; j < rhs.getColumns(); j++){
      s << rhs[i][j];
      if (j + 1 != rhs.getColumns()){
	s<< ", ";
      }
    }
    s << "}";
    if (i + 1 != rhs.getRows()){
      s<<",\n";
    }
  }
  s << " ]";
  return s;
}

#endif
