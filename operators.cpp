#include "nn.h"
using namespace la;

void Matrix::operator+=(Matrix other){
  this->add_(other);
}

Matrix Matrix::operator+(){
  Matrix result(this->rows, this->cols);

  for (int i = 0; i < this->rows; i++){
    for (int j = 0; j < this->cols; j++){
      *result.at(i, j) = *this->at(i, j);
    }
  }
  return result;
}

Matrix Matrix::operator+(Matrix other){
  return this->add(other);
}

Matrix Matrix::operator-(){
  Matrix result(this->rows, this->cols);

  for (int i = 0; i < this->rows; i++){
    for (int j = 0; j < this->cols; j++){
      *result.at(i, j) = - (*this->at(i, j));
    }
  }
  return result;
}

Matrix Matrix::operator-(Matrix other){
  return this->add(-other);
}

Matrix Matrix::operator*(Matrix other){
  return this->mm(other); // FIXME: change to fast multiplication
}

bool Matrix::operator!=(Matrix other){
  return !(*this == other);
}

bool Matrix::operator==(Matrix other){
  // same size
  bool eq = (this->rows == other.rows) && (this->cols == other.cols);

  // same elements
  for (int i = 0; i < this->rows; i++){
    for (int j = 0; j < this->cols; j++){
      eq = eq && (*(this->at(i, j)) == *(other.at(i, j)));
    }
  }
  return eq;
}
