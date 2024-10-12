#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace nn;
using namespace la;

int main(){
  Matrix A = la::identity(3);
  Matrix B = la::ones(3,3);

  if (A.trace() != B.trace()){
    printf("[!] Trace of identity and ones() diverge.\n");
    return 1;
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
    return 1;
  }

  return 0;
}
