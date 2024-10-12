#include <iostream>
#include <stdlib.h>
#include <cassert>

#include "nn.h"

using namespace la;

void Matrix::multiply_(int scalar){
  for (int i = 0; i < this->rows; i++){
    for (int j = 0; j < this->cols; j++){
      *this->at(i,j) *= scalar;
    }
  }
}

Matrix Matrix::multiply(int scalar){
  Matrix result(this->rows, this->cols);
  result.multiply_(scalar);
  return result;

}

void Matrix::add_(int scalar){
  for (int i = 0; i < this->rows; i++){
    for (int j = 0; j < this->cols; j++){
      *this->at(i,j) += scalar;
    }
  }
}

Matrix Matrix::add(int scalar){
  // Not-in-place addition
  Matrix result(this->rows, this->cols);
  result.add_(scalar);
  return result;
}


Matrix Matrix::mm(Matrix other){
  // Matrix multiplication. Returns the result of the operation.
  return la::mm(*this, other);
}

void Matrix::add_(Matrix other){
  // In-place addition the elements of matrix "other" to the given matrix.
  for (int i = 0; i < this->rows; i++){
    for (int j = 0; j < this->cols; j++){
      *this->at(i,j) += *(other.at(i,j));
    }
  }
}

Matrix Matrix::add(Matrix other){
  // Not-in-place addition
  Matrix result(this->rows, this->cols);
  result.add_(other);
  return result;
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
  assert(i < this->rows && j < this->cols);
  return &this->elements[i*this->cols + j];
 }


Matrix Matrix::submat(int row_start, int col_start,
                      int row_end, int col_end) {
  /*
   *   Submatrix given by a region of a given matrix.
   */

  // adding two to compensate starting at index 0.
  // FIXME: This is a mess.
  if (row_start == 0 && col_start == 0 &&
      row_end == this->rows && col_end == this->cols){
    return *this;
  } else if (row_start>row_end || col_start>col_end){
    printf("Error: Start point should come before end point.\n");
    printf("Starting point:(%d,%d), End point:(%d,%d)\n", col_start, row_start, col_end, row_end);
    assert(false);
  }

  int s_rows = (row_end-row_start);
  int s_cols = (col_end-col_start);
  s_rows = s_rows < 2? s_rows+1 : s_rows;
  s_cols = s_cols < 2? s_cols+1 : s_cols;
  Matrix sub = Matrix(s_rows, s_cols);

  for (int i = 0; i < s_rows; i++) {
    for (int j = 0; j < s_cols; j++) {
      *sub.at(i,j) = *this->at(row_start+i,col_start+j);
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
  assert(this->rows == this->cols);
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

Matrix Matrix::transpose(){
  Matrix t = *this;
  t.transpose_();
  return t;
}

void Matrix::transpose_(){
  Matrix t(this->cols, this->rows);
  for (int j = 0; j < this->cols; j++){
    for (int i = 0; i < this->rows; i++){
      *t.at(j,i) = *this->at(i,j);
    }
  }
  *this = t;
}

float Matrix::trace(){
  assert(this->cols == this->rows);
  float tr = 0.f;
  for (int i = 0; i < this->cols; i++){
      tr += *this->at(i, i);
  }
  return tr;
}

void Matrix::fill(float value){
  for(int i = 0; i < this->rows*this->cols; i++){
    this->elements[i] = value;
  }
}

Matrix la::identity(int size){
  Matrix A(size, size);
  for (int i = 0; i < size; i++){
    *A.at(i,i) = 1;
  }
  return A;
}

Matrix la::ones(int rows, int cols){
  Matrix A(rows, cols);
  A.fill(1.f);
  return A;
}

Matrix la::zeroes(int rows, int cols){
  Matrix A(rows, cols);
  A.fill(0.f);
  return A;
}

Matrix la::generic(int rows, int cols){
  Matrix A(rows, cols);
  int c = 1;
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      *A.at(i, j) = c;
      c++;
    }
  }
  return A;
}

Matrix la::fromVector(std::vector<std::vector<float>> elements){
  //FIXME: inconsistent.
  Matrix A(elements.size(), elements[0].size());
  for (int i = 0; i < A.rows; i++){
    for (int j = 0; j < A.cols; j++){
      *A.at(i,j) = elements[i][j];
    }
  }
  return A;
}

Matrix la::fill_to_power2(Matrix m){
  auto get_geq_power2 = [](int x){
    if (x <= 1){
      return 2; // always assure dim >= 2, see NOTE
    } else{
      // __builtin_clz = leading 0s in binary representation
      long unsigned int ceil_log2 = sizeof(int) * 8  -__builtin_clz(x - 1);
      return 1 << ceil_log2;
    }
  };

  int new_rows = get_geq_power2(m.rows);
  int new_cols = get_geq_power2(m.cols);

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

BlockMatrix::BlockMatrix(Matrix topleft, Matrix topright, Matrix bottomleft, Matrix bottomright){
  assert(topleft.rows == topright.rows);
  assert(bottomleft.rows == bottomright.rows);
  assert(topleft.cols == bottomleft.cols);
  assert(topright.cols == bottomright.cols);
  this->topleft = topleft;
  this->topright = topright;
  this->bottomleft = bottomleft;
  this->bottomright = bottomright;
}

BlockMatrix::BlockMatrix(Matrix m){
  // NOTE: this division in (r/2, c/2) fails if r or c are odd
  // (ex.: 1)

  Matrix filled_m = fill_to_power2(m);
  int r = filled_m.rows, c = filled_m.cols;
  this->topleft = la::zeroes(r / 2, c / 2);
  this->topright = la::zeroes(r / 2, c / 2);
  this->bottomleft = la::zeroes(r / 2, c / 2);
  this->bottomright = la::zeroes(r / 2, c / 2);

  for (int i = 0; i < r / 2; i++){
    for (int j = 0; j < c / 2; j++){
      *(this->topleft.at(i, j)) = *filled_m.at(i, j);
    }
    for (int j = c / 2; j < c; j++){
      *(this->topright.at(i, j - c/2)) = *filled_m.at(i, j);
    }
  }
  for (int i = r / 2; i < r; i++){
    for (int j = 0; j < c / 2; j++){
      *(this->bottomleft.at(i - r/2, j)) = *filled_m.at(i, j);
    }
    for (int j = c / 2; j < c; j++){
      *(this->bottomright.at(i - r/2, j - c/2)) = *filled_m.at(i, j);
    }
  }
}

Matrix la::BlockMatrix::join(){
  int r1 = this->topleft.rows,
    r2 = this->bottomleft.rows,
    c1 = this->topleft.cols,
    c2 = this->topright.cols;

  Matrix m(r1 + r2, c1 + c2);

  for (int i = 0; i < r1; i++){
    for (int j = 0; j < c1; j++){
      *m.at(i, j) = *(this->topleft.at(i, j));
    }
    for (int j = c1; j < c1 + c2; j++){
      *m.at(i, j) = *(this->topright.at(i, j - c1));
    }
  }

  for (int i = r1; i < r1 + r2; i++){
    for (int j = 0; j < c1; j++){
      *m.at(i, j) = *(this->bottomleft.at(i - r1, j));
    }
    for (int j = c1; j < c1 + c2; j++){
      *m.at(i, j) = *(this->bottomright.at(i - r1, j - c1));
    }
  }
  return m;
}


Matrix la::mm(Matrix A, Matrix B){
  assert(A.cols == B.rows);
  if (A.rows < min_size && A.cols < min_size && B.rows < min_size && B.cols < min_size){
    Matrix c (A.rows, B.cols);
    for (int i = 0; i < A.rows; i++){
      for (int j = 0; j < B.cols; j++){
        for (int k = 0; k < A.cols; k++){
          *c.at(i,j) += *A.at(i,k) * *B.at(k,j);
        }
      }
    }
    return c; // TODO: make it strassen.
  }
  // Another possibility: allow recursion up to base case n=m=1
  // Might be slow (Strassen's algorithm is slower than naive O(n^3) for n small, because of large constant factor and hidden terms)
  // if (A.rows == 1 && A.cols == 1 && B.rows ==  1 && B.cols == 1){
  //   Matrix m(1, 1);
  //   *m.at(0,0) = *A.at(0, 0) * *B.at(0, 0);
  //   return m;
  // }

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


  Matrix M1 = mm((A11 + A22), (B11 + B22));
  Matrix M2 = mm((A21 + A22), B11);
  Matrix M3 = mm(A11, (B12 - B22));
  Matrix M4 = mm(A22, (B21 - B11));
  Matrix M5 = mm((A11 + A12),  B22);
  Matrix M6 = mm((A21 - A11),  (B11 + B12));
  Matrix M7 = mm((A12 - A22), (B21 + B22));

  BlockMatrix BlockC = BlockMatrix(M1 + M4 - M5 + M7,
                                  M3 + M5,
                                  M2 + M4,
                                  M1 - M2 + M3 + M6);
  Matrix filled_ans = BlockC.join();
  Matrix ans(A.rows, B.cols);
  for (int i = 0; i < A.rows; i++){
    for (int j = 0; j < B.cols; j++){
      *(ans.at(i, j)) = *(filled_ans.at(i, j));
    }
  }
  return ans;
}
