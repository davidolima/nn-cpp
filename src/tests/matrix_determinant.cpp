#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace nn;
using namespace la;

int main(){
    Matrix A = {
    {6,  1, 1},
    {4, -2, 5},
    {2,  8, 7}
  };

  //printf("det(A) = %f\n", A.det());

  if (A.det() != -306){
    return 1;
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
    return 1;
  }

  return 0;
}
