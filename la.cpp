#include <iostream>
#include <stdlib.h>

#include "nn.h"

using namespace la;

Matrix Matrix::mm(Matrix other){
  // Matrix multiplication. Returns the result of the operation.
  Matrix c (this->rows, other.cols);
  for (int i = 0; i < this->rows; i++){
    for (int j = 0; j < this->cols; j++){
      for (int k = 0; k < (int) sizeof(this->cols); k++){
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
      *this->at(i,j) += *other.at(i,j);
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
}

float* Matrix::at(int i, int j){
  // Returns a pointer to the element (i,j) of the given matrix.
  // Made this way so it's easy to modify the element.
  return &this->elements[i*this->cols+j];
}
