#include "nn.h"
#include "strassen.h"
#include <math.h>
#include <cassert>

using namespace la;
// using namespace strassen;

Matrix strassen::fill_to_power2(Matrix m){
  auto get_geq_power2 = [](int x){
    if (x <= 1){
      return 1;
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

Matrix strassen::BlockMatrix::join(){
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


Matrix strassen::strassen_mm(Matrix A, Matrix B){
  assert(A.cols == B.rows);
  if (A.rows < min_size && A.cols < min_size && B.rows < min_size && B.cols < min_size){
    return A * B;
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


  Matrix M1 = strassen_mm((A11 + A22), (B11 + B22));
  Matrix M2 = strassen_mm((A21 + A22), B11);
  Matrix M3 = strassen_mm(A11, (B12 - B22));
  Matrix M4 = strassen_mm(A22, (B21 - B11));
  Matrix M5 = strassen_mm((A11 + A12),  B22);
  Matrix M6 = strassen_mm((A21 - A11),  (B11 + B12));
  Matrix M7 = strassen_mm((A12 - A22), (B21 + B22));

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

