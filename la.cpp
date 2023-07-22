#include <iostream>
#include <stdlib.h>
#include <cassert>

#include "nn.h"

using namespace la;

Matrix Matrix::mm(Matrix other){
  // Matrix multiplication. Returns the result of the operation.
  Matrix c (this->rows, other.cols);
  for (int i = 0; i < this->rows; i++){
    for (int j = 0; j < other.cols; j++){
      for (int k = 0; k < this->cols; k++){
        *c.at(i,j) += *this->at(i,k) * *other.at(k,j);
      }
    }
  }
  return c;
}

void Matrix::add(Matrix other){
  // In-place addition the elements of matrix "other" to the given matrix.
  for (int i = 0; i < this->rows; i++){
    for (int j = 0; j < this->cols; j++){
      printf("%f + %f = %f\n", *this->at(i,j), *other.at(i,j), *other.at(i,j)+*this->at(i,j));
      *this->at(i,j) += *(other.at(i,j));
    }
  }
}

void Matrix::print(){
  // Prints the matrix.
  printf("%dx%d matrix\n", this->rows, this->cols);
  for (int i = 0; i < this->rows; i++){
    printf("| ");
    for (int j = 0; j < this->cols; j++){
      printf("%f ", *this->at(i,j));
    }
    printf("|\n");
  }
  return;
}

float* Matrix::at(int i, int j){
  // Returns a pointer to the element (i,j) of the given matrix.
  // Made this way so it's easy to modify the element.
  return &this->elements[i*this->rows+j];
}

Matrix Matrix::submat(int x0, int y0, int x1, int y1) {
  // adding two to compensate starting at index 0.
  assert(x0<=x1 && y0<=y1);

  int sub_rows = (x1-x0)+1;
  int sub_cols = (y1-y0)+1;
  Matrix sub = Matrix(sub_rows, sub_cols);

  for (int j = 0; j < sub_cols; j++){
    for (int i = 0; i < sub_rows; i++){
      *sub.at(i,j) = *this->at(x0+i-1,y0+j-1);
    }
  }

  return sub;
}

float Matrix::det(){
  // Laplace Expansion
  if (this->rows == 2 && this->cols == 2){
    // | a b |
    // | c d |
    // -> a*d - b*c
    // -> (0,0)*(1,1)-(1,0)*(0,1)
    return *this->at(0,0)**this->at(1,1)-*this->at(0,1)**this->at(1,0);
  }


  return 0.f;
}
