#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace nn;
using namespace la;

int main(){
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
  return 0;
}
