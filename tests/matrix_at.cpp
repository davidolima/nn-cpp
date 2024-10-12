#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace nn;
using namespace la;

int main(){
  printf("%s:", __func__);
  Matrix A = la::identity(3);
  Matrix B (3,3);

  *B.at(0,0) = 1;
  *B.at(1,1) = 1;
  *B.at(2,2) = 1;

  if (A != B){
    printf("A = "); A.print();
    printf("B = "); B.print();
    return 1;
  }

  A = la::generic(3,3);

  *B.at(0,0) = 1;
  *B.at(0,1) = 2;
  *B.at(0,2) = 3;

  *B.at(1,0) = 4;
  *B.at(1,1) = 5;
  *B.at(1,2) = 6;

  *B.at(2,0) = 7;
  *B.at(2,1) = 8;
  *B.at(2,2) = 9;

  if (A != B){
    printf("A = "); A.print();
    printf("B = "); B.print();
    return 1;
  }

  std::vector<std::vector<float>> elements = {
    {1,2,3},
    {4,5,6},
    {7,8,9}
  };

  A = la::fromVector(elements);
  B = la::generic(3,4);

  if ( A != B ) {
      printf("Generic constructor failed.");
      printf("A = "); A.print();
      printf("B = "); B.print();
      return 1;
  }

  elements = {
    {4, 3, 2, 7},
    {1, 0, 5, 8}
  };

  A = la::fromVector(elements);
  B = Matrix(2,4);
  *B.at(0,0) = 4; *B.at(0,1) = 3; *B.at(0,2) = 2; *B.at(0,3) = 7;
  *B.at(1,0) = 1; *B.at(1,1) = 0; *B.at(1,2) = 5; *B.at(1,3) = 8;

  if (A != B) {
      printf("Manual construction of matrix failed.");
      printf("A = "); A.print();
      printf("B = "); B.print();
      return 1;
  }

  return 0;
}
