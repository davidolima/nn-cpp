#include "nn.h"
#include <iostream>

using namespace nn;

float nn::randf() { return rand() / (RAND_MAX + 1.); }

Network::Network(int input_dim, int hidden_dim, int output_dim){
  this->input_dim = input_dim;
  this->hidden_dim = hidden_dim;
  this->output_dim = output_dim;
  this->weights = new la::Matrix(hidden_dim, hidden_dim);
  this->bias = new la::Matrix(hidden_dim, 1);
  this->initialize_params();
}

void Network::print(){
  printf("weights = ");
  this->weights->print();
  printf("\nbias = ");
  this->bias->print();
}

void Network::initialize_params(){
  // initialize random weights
  for (int i = 0; i < this->hidden_dim; i++){
    for (int j = 0; j < this->hidden_dim; j++){
      *(this->weights->at(i,j)) = nn::randf()*10;
    }
  }
  for (int i = 0; i < this->hidden_dim; i++){
    *(this->bias->at(i,0)) = nn::randf()*10;
  }
}


la::Matrix Network::feedforward(la::Matrix x){
  la::Matrix r = (*this->weights)*x + *this->bias;
  return r;
}
