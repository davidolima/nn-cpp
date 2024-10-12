#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace nn;
using namespace la;

int main(){
  Matrix A = la::generic(3, 2);
  Matrix B = {
    {4},
    {6}
  };

  Matrix C = A.submat(1,1,
                      2,1);

  Matrix D = A.submat(0,0);

  if (C != B || D != B){
    printf("A = ");
    A.print();
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
    return 1;
  }

  Matrix E = la::generic(6,3);
  Matrix E1_gt = {
    {1,   2},
    {4,   5},
    {7,   8},
    {10, 11},
    {13, 14},
    {16, 17},
  };
  Matrix E2_gt = {
  {3},
  {6},
  {9},
  {12},
  {15},
  {18},
  };

  Matrix E1 = E.submat(0     , 0,
                       E.rows, E.cols-1);
  Matrix E2 = E.submat(0     , E.cols-1,
                       E.rows, E.cols-1);

  if (E1_gt != E1 || E2_gt != E2){
    E.print();
    E1.print();
    E2.print();
    return 1;
  }
  return 0;
}
