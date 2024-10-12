#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace nn;
using namespace la;

int main(){
  vector<vector<float>> elements = {
      {1,2,3},
      {4,5,6},
      {7,8,9}
  };
  Matrix A = fromVector(elements);
  Matrix B = generic(3,3);

  if (A != B){
      printf("[!] Matrix from vector diverged from construction\n");
      printf("From vector = ");
      A.print();
      printf("Construction = ");
      B.print();
      return 1;
  }

  A = {{1,2,3},
       {4,5,6},
       {7,8,9}};

  if (A != B){
      printf("[!] Matrix from initializer_list diverged from construction\n");
      printf("From vector = ");
      A.print();
      printf("Construction = ");
      B.print();
      return 1;
  }

  return 0;
}
