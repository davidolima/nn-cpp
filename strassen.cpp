#include "nn.h"
#include "strassen.h"
#include <math.h>
#include <cassert>

using namespace la;
// using namespace strassen;

Matrix strassen::fill_to_power2(Matrix m){
  int new_rows = (int)(ceil(log2(m.rows)));
  int new_cols = (int)(ceil(log2(m.cols)));

  Matrix fill_matrix(new_rows, new_cols);

  for (int i = 0; i < new_rows; i++){
    for (int j = 0; j < new_cols; j++){
      if (i < m.rows && j < m.cols){
        *fill_matrix.at(i, j) = *m.at(i, j);
      } else {
        *fill_matrix.at(i, j) = 0.0;
      }
    }
  }
  return fill_matrix;
}

strassen::BlockMatrix::BlockMatrix(Matrix topleft, Matrix topright, Matrix bottomleft, Matrix bottomright){
  assert(topleft.rows == topright.rows);
  assert(bottomleft.rows == bottomright.rows);
  assert(topleft.cols == bottomleft.cols);
  assert(topright.cols == bottomright.cols);
  this->topleft = topleft;
  this->topright = topright;
  this->bottomleft = bottomleft;
  this->bottomright = bottomright;
}

strassen::BlockMatrix::BlockMatrix(Matrix m){
  Matrix filled_m = fill_to_power2(m);
  int r = filled_m.rows, c = filled_m.cols;
  this->topleft = Matrix::zeroes(r / 2, c / 2);
  this->topright = Matrix::zeroes(r / 2, c / 2);
  this->bottomleft = Matrix::zeroes(r / 2, c / 2);
  this->bottomright = Matrix::zeroes(r / 2, c / 2);

  for (int i = 0; i < r / 2; i++){
    for (int j = 0; j < c / 2; j++){
      *(this->topleft.at(i, j)) = *filled_m.at(i, j);
    }
    for (int j = c / 2; j < c; j++){
      *(this->topright.at(i, j)) = *filled_m.at(i, j);
    }
  }
  for (int i = r / 2; i < r; i++){
    for (int j = 0; j < c / 2; j++){
      *(this->bottomleft.at(i, j)) = *filled_m.at(i, j);
    }
    for (int j = c / 2; j < c; j++){
      *(this->bottomright.at(i, j)) = *filled_m.at(i, j);
    }
  }
}

Matrix strassen::BlockMatrix::join(){
  Matrix m(this->topleft.rows + this->bottomleft.rows,
            this->topleft.cols + this->topright.cols);

  for (int i = 0; i < this->topleft.rows; i++){
    for (int j = 0; j < this->topleft.cols; i++){
      *m.at(i, j) = *(this->topleft.at(i, j));
    }
    for (int j = 0; j < this->topright.cols; j++){
      *m.at(i, j) = *(this->topright.at(i, j));
    }
  }

  for (int i = 0; i < this->bottomleft.rows; i++){
    for (int j = 0; j < this->bottomleft.cols; j++){
      *m.at(i + this->topleft.rows, j) = *(this->bottomleft.at(i, j));
    }
    for (int j = 0; j < this->bottomright.cols; j++){
      *m.at(i + this->topleft.rows, j + this->bottomleft.cols) = *(this->bottomright.at(i, j));
    }
  }
  return m;
}


Matrix strassen::strassen_mm(Matrix A, Matrix B){
  if (A.rows < min_size && A.cols < min_size && B.rows < min_size && B.cols < min_size){
    return A * B;
  }

  BlockMatrix BlockA = BlockMatrix(A); 
  BlockMatrix BlockB = BlockMatrix(B);

  Matrix A11 = BlockA.topleft; 
  Matrix A12 = BlockA.topright; 
  Matrix A21 = BlockA.bottomleft; 
  Matrix A22 = BlockA.bottomright;
  Matrix B11 = BlockB.topleft; 
  Matrix B12 = BlockB.topright; 
  Matrix B21 = BlockB.bottomleft; 
  Matrix B22 = BlockB.bottomright;

  Matrix M1 = strassen_mm((A11 + A22), (B11 + B22));
  Matrix M2 = strassen_mm((A21 + A22), B11);
  Matrix M3 = strassen_mm(A11, (B12 - B22));
  Matrix M4 = strassen_mm(A22, (B21 - B11));
  Matrix M5 = strassen_mm((A11 + A22),  B22);
  Matrix M6 = strassen_mm((A21 - A11),  (B11 + B12));
  Matrix M7 = strassen_mm((A12 - A22), (B21 + B22));

  BlockMatrix BlockC = BlockMatrix(M1 + M4 - M5 + M7,
                                  M3 + M5,
                                  M2 + M4,
                                  M1 - M2 + M3 + M6);
  return BlockC.join();
}

