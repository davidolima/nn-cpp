#include <iostream>
#include "../nn.h"

using namespace nn;
using namespace la;

bool submat(){
  printf("%s:", __func__);
  Matrix A = Matrix(3, 2);

  *A.at(0,0) = 1;
  *A.at(0,1) = 2;
  *A.at(1,0) = 3;
  *A.at(1,1) = 4;
  *A.at(2,0) = 5;
  *A.at(2,1) = 6;

  Matrix B = Matrix(2,1);
  *B.at(0,0) = 4;
  *B.at(1,0) = 6;

  Matrix C = A.submat(2,2,
                      3,2);

  Matrix D = A.submat(0,0);

  if (C != B || D != B){
    if (C != B){
      printf("[!] C not equal to B.\n");
      printf("C = ");
      C.print();
      printf("B = ");
      B.print();
    }
    if (D != B){
      printf("[!] D not equal to B.\n");
      printf("D = ");
      D.print();
      printf("B = ");
      B.print();
    }
    return false;
  }
  return true;
}

bool determinant(){
  printf("%s:", __func__);
  Matrix A = Matrix(3,3);
  // 6 1 1
  // 4 -2 5
  // 2 8 7

  *A.at(0,0) = 6;
  *A.at(0,1) = 1;
  *A.at(0,2) = 1;

  *A.at(1,0) = 4;
  *A.at(1,1) = -2;
  *A.at(1,2) = 5;

  *A.at(2,0) = 2;
  *A.at(2,1) = 8;
  *A.at(2,2) = 7;

  //printf("det(A) = %f\n", A.det());

  if (A.det() != -306){
    return false;
  }

  A = Matrix(5,5);

  *A.at(0,0) = 1;
  *A.at(0,1) = 4;
  *A.at(0,2) = 5;
  *A.at(0,3) = 5;
  *A.at(0,4) = 4;

  *A.at(1,0) = 2;
  *A.at(1,1) = 3;
  *A.at(1,2) = 5;
  *A.at(1,3) = 5;
  *A.at(1,4) = 3;

  *A.at(2,0) = 3;
  *A.at(2,1) = 2;
  *A.at(2,2) = 4;
  *A.at(2,3) = 4;
  *A.at(2,4) = 2;

  *A.at(3,0) = 4;
  *A.at(3,1) = 1;
  *A.at(3,2) = 2;
  *A.at(3,3) = 3;
  *A.at(3,4) = 1;

  *A.at(4,0) = 5;
  *A.at(4,1) = 5;
  *A.at(4,2) = 4;
  *A.at(4,3) = 3;
  *A.at(4,4) = 2;

  //printf("det(A) = %f\n", A.det());
  if (A.det() != -15){
    return false;
  }

  return true;
}

bool matrixMultiplication(){
  printf("%s:", __func__);
  int rows_a = rand() % 10;
  int cols_a = rand() % 10;
  int cols_b = rand() % 10;

  Matrix A(rows_a, cols_a);
  Matrix B(cols_a, cols_b);

  // fill A with random floats
  for (int j = 0; j < cols_a; j++){
    for (int i = 0; i < rows_a; i++){
      *A.at(i,j) = nn::randf()*10;
    }
  }
  // fill B with random floats
  for (int j = 0; j < cols_b; j++){
    for (int i = 0; i < cols_a; i++){
      *B.at(i,j) = nn::randf()*10;
    }
  }

  Matrix C(rows_a,cols_b);
  C = A.mm(B);
  return true;
}

int main(){
  bool (*tests[])() = {
    matrixMultiplication,
    submat,
    determinant
  };

  uint passed = 0;
  uint total = (uint) sizeof(tests)/sizeof(bool*);

  for (uint i = 0; i < total; i++){
    if (tests[i]()){
      printf(" PASSED\n");
      passed++;
    } else {
      printf(" FAILED\n");
    }
  }

  printf("[!] TEST RESULTS: PASSED %d/%d", passed, total);
  return 0;
}
