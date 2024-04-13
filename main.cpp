#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "nn.h"

using namespace std;
using namespace nn;
using namespace la;

int train_set[][2] = {
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
    {5,10},
    {6,12},
    {7,14},
    {8,16},
};

int train_size = sizeof(train_set)/sizeof(train_set[0]);

float criterion(float w, float b){
  float mse = 0.f;
  for (int i = 0; i < train_size; i++){
    float y_pred = w*i+b;
    mse += pow((train_set[i][1] - y_pred),2);
  }
  return mse/train_size;
}



int main() {
  // srand(time(0));
  // float epsilon = 1e-5;
  // float lr = 1e-3;
  // int epochs = 1000;

  // // inicializar modelo
  // Network net(2);

  // net.print();
  Matrix A = generic(5,1);
  Matrix B = ones(1,5)*2;
  A.print();
  B.print();
  A.mm(B).print();
  return 0;
}
