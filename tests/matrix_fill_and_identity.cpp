#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace nn;
using namespace la;

int main(){
  Matrix A = ones(2,2);
  Matrix B(2,2);
  B.fill(1.f);

  if (A != B){
    printf("[!] ones() not equal to fill(1.f).\n");
    printf("ones (A) = ");
    A.print();
    printf("fill (B) = ");
    B.print();
    return 1;
  }

  A = la::generic(3,3);
  B = la::identity(3);

  if (A*B != A) {
    printf("[!] Multiplication with identity returns a different matrix.\n");
    printf("A = "); A.print();
    printf("Identity = "); B.print();
    printf("Multiplication result = "); (A*B).print();
    return 1;
  }

  return 0;
}
