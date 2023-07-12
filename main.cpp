#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef struct {
 float w;
 float b;
} neuron;

int train_set[][2] = {
    {0,1},
    {1,2},
    {2,3},
    {3,4},
    {4,5},
    {5,6},
    {6,7},
    {7,8},
    {8,9},
};
int train_size = sizeof(train_set)/sizeof(train_set[0]);

float sigmoid(float x){
    return 1.f/(1.f+expf(-x)); // sigmoid
}

float binaryStep(float x){
    return (x >= 0) ? 1 : 0; // sigmoid
}

float criterion(float w, float b){
  float mse = 0.f;
  for (int i = 0; i < train_size; i++){
    float y_pred = w*i+b;
    mse += pow((train_set[i][1] - y_pred),2); // MSE
  }
  return mse/train_size;
}

float accuracy(neuron n){
  float r = 0.f;
  for (int i = 0; i < train_size; i++){
    float y = n.w*train_set[i][0]+n.b;
    r += (y == train_set[i][1]) ? 1 : 0;
  }
  return r/train_size;
}

double randf()
{
  return rand() / (RAND_MAX + 1.);
}

int main() {
  srand(time(0));
  float epsilon = 1e-3;
  float lr = 1e-3;
  int epochs = 1000;

  // inicializar neurônios com peso e bias aleatório
  neuron n;
  n.w = randf();
  n.b = randf();

  // treinamento
  for (int i = 0; i < epochs; i++){
    // calcular gradiente
    float dw = (criterion(n.w + epsilon, n.b)-criterion(n.w,n.b))/epsilon;
    float db = (criterion(n.w, n.b + epsilon)-criterion(n.w,n.b))/epsilon;

    // atualizar peso e bias do modelo
    n.w -= dw*lr;
    n.b -= db*lr;

    float loss = criterion(n.w, n.b);
    float acc = accuracy(n);
    printf("[%d/%d] loss = %f, accuracy = %f", i+1, epochs, loss, acc);
    printf("    -> w = %f, b = %f\n", n.w, n.b);
  }

  // testando modelo
  for (int i = 0; i < 5; i++){
    int x = randf()*50;
    printf("x = %d -> y_pred = %f\n", x, n.w*x+n.b);
  }
  return 0;
}
