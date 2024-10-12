#include <stdlib.h>

#include "../src/nn.h"

using namespace std;
using namespace la;

int main() {
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

  printf("A = ");
  A.print();
  printf("B = ");
  B.print();
  printf("C = ");
  C.print();
  printf("D = ");
  D.print();
  printf("I = ");
  I.print();

  printf("det(A) = %f, det(B) = %f, det(C) = %f, det(D) = %f\n", A.det(), B.det(), C.det(), D.det());
  printf("tr(A) = %f, tr(B) = %f, tr(C) = %f, tr(D) = %f\n", A.trace(), B.trace(), C.trace(), D.trace());

  Matrix E = la::generic(2,2);
  printf("A = E? ");
  if (A == E){
    printf("true\n");
  } else {
    printf("false\n");
  }
  return 0;
}
