#include "nn.h"
#include <iostream>

using namespace nn;

float nn::randf() { return rand() / (RAND_MAX + 1.); }

Network::Network(int num_neurons){
  this->weights = new la::Matrix(1,num_neurons);
  this->biases = new la::Matrix(num_neurons,1);

  // initialize random weights
  for (int i = 0; i < num_neurons; i++){
    *(this->weights->at(0,i)) = nn::randf()*10;
    *(this->biases->at(i,0)) = nn::randf()*10;
  }
}

void Network::print(){
  // FIXME: Support for multiple layers
  printf("weights = ");
  this->weights->print();
  printf("\nbiases = ");
  this->biases->print();
}
