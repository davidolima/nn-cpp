#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace nn;
using namespace la;

int main(){
  Matrix A(5,3);
  Matrix B(3,5);

  int c = 1;
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 3; j++){
      *A.at(i,j) = c;
      *B.at(j,i) = *A.at(i,j);
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
    return 1;
  }
  return 0;
}
