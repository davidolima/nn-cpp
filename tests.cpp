#include <iostream>
#include "nn.h"
#include <vector>

using namespace nn;
using namespace la;

bool matrix_creation(){
  printf("%s:", __func__);
  std::vector<std::vector<float>> elements = {{1,2,3},{4,5,6}, {7,8,9}};
  Matrix A = la::fromVector(elements);
  Matrix B = la::generic(3,3);

  if (A != B){
    printf("[!] Matrix from vector diverged from construction\n");
    printf("From vector = ");
    A.print();
    printf("Construction = ");
    B.print();
    return false;
  }

  A = {{1,2,3}, {4,5,6}, {7,8,9}};
  if (A != B){
    printf("[!] Matrix from initializer_list diverged from construction\n");
    printf("From vector = ");
    A.print();
    printf("Construction = ");
    B.print();
    return false;
  }

  return true;
}

bool trace(){
  printf("%s:", __func__);
  Matrix A = la::identity(3);
  Matrix B = la::ones(3,3);

  if (A.trace() != B.trace()){
    printf("[!] Trace of identity and ones() diverge.\n");
    return false;
  }

  *A.at(0,0) = 1;
  *A.at(1,1) = 5;
  *A.at(2,2) = 9;

  B = la::generic(3,3);

  if (A.trace() != B.trace()){
    printf("[!] Trace of the following matrices diverge.\n");

    printf("A = ");
    A.print();
    printf("B = ");
    B.print();
    printf("tr(A) = %f\ntr(B) = %f", A.trace(), B.trace());
    return false;
  }

  return true;
}

bool transpose(){
  printf("%s:", __func__);
  Matrix A(5,3);
  Matrix B(3,5);

  int c = 1;
  for (int j = 0; j < 3; j++){
    for (int i = 0; i < 5; i++){
      *A.at(i,j) = c;
      *B.at(j,i) = c;
      c++;
    }
  }

  Matrix C = A.transpose();
  if(B != C){
    printf("[!] Tranpose function differs from construction\n");
    printf("A = ");
    A.print();
    printf("B = ");
    B.print();
    printf("A.transpose() = ");
    C.print();
    return false;
  }
  return true;
}

bool fill_and_identity(){
  printf("%s:", __func__);
  Matrix A = ones(2,2);
  Matrix B(2,2);
  B.fill(1.f);

  if (A != B){
    printf("[!] ones() not equal to fill(1.f).\n");
    printf("ones (A) = ");
    A.print();
    printf("fill (B) = ");
    B.print();
    return false;
  }

  A = la::generic(3,3);
  B = la::identity(3);

  if (A*B != A) {
    printf("[!] Multiplication with identity returns a different matrix.\n");
    printf("A = ");
    A.print();
    printf("Identity = ");
    B.print();
    printf("Multiplication result = ");
    (A*B).print();
    return false;
  }

  return true;
}

bool submat(){
  printf("%s:", __func__);
  Matrix A = la::generic(3, 2);
  Matrix B = {
    {4},
    {6}
  };

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
  Matrix A = {
    {6,  1, 1},
    {4, -2, 5},
    {2,  8, 7}
  };

  //printf("det(A) = %f\n", A.det());

  if (A.det() != -306){
    return false;
  }

  A = Matrix(5,5);

  A = {
    {1,4,5,5,4},
    {2,3,5,5,3},
    {3,2,4,4,2},
    {4,1,2,3,1},
    {5,5,4,3,2}
  };

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
    determinant,
    matrixMultiplication,
    submat,
    fill_and_identity,
    transpose,
    trace,
    matrix_creation,
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
