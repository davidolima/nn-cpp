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
  assert(i <= this->rows && j <= this->cols);
  return &this->elements[i*this->rows+j];
 }

Matrix Matrix::submat(int x0, int y0, int x1, int y1) {
  /*
   *   Submatrix given by a region of a given matrix.
   */

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

Matrix Matrix::submat(int p, int q){
  /*
   * The submatrix created by removing
   * row p and col q from a given matrix.
   */

  Matrix M = Matrix(this->rows-1,this->cols-1);

  for (int j = 0; j < this->cols; j++){
    int c_j = j > q ? 1 : 0; // maps j to correct col at M
    if (j != q){ // skip col q
      for (int i = 0; i < this->rows; i++){
        if (i != p){ // skip row p
          int c_i = i > p ? 1 : 0; // maps i to correct row at M
          *M.at(i-c_i,j-c_j) = *this->at(i, j);
        }
      }
    }
  }

  return M;
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

  float r = 0;
  for (int j = 0; j < this->cols; j++){
    // (-1)^(i+j)b_{ij}m_{ij}
    r += pow(-1,0+j)**this->at(0,j)*this->submat(0,j).det();
  }
  return r;
}
