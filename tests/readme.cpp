#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace nn;
using namespace la;

int main(){
  Matrix A = {
    {1, 2},
    {3, 4}
  };

  Matrix B = A.transpose();

  Matrix C = A + B;
  Matrix D = A * B;

  Matrix I = la::identity(2);

  A = A * I;
  B = B * I;
  C = C * I;
  D = D * I;

  Matrix E = la::generic(2,2);
  if (A != E){
    return 1;
  }

  return 0;
}
