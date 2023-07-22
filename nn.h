#ifndef NETWORK_H_
#define NETWORK_H_
#include <math.h>
#include <iostream>

namespace la {
  class Matrix {
    public:
    Matrix(int rows, int cols){
      this->elements = (float*) calloc((rows+1)*(cols+1), sizeof(float));
      if (this->elements == NULL) {
        printf("Error allocating memory for matrix. Tried to allocate %zu bytes.\n", (rows*cols*sizeof(float)));
        exit (EXIT_FAILURE);
      }
      this->rows = rows;
      this->cols = cols;
    }
    
    // operations
    Matrix mm(Matrix other);
    void add(Matrix other);
    void add_(Matrix other);
    Matrix operator+(void); // unary plus
    Matrix operator+(Matrix other); // binary plus
    Matrix operator-(void); // unary minus
    Matrix operator-(Matrix other); // binary plus
    Matrix operator*(Matrix other); // multiplication operator
    void operator+=(Matrix other);
    bool operator==(Matrix other);
    
    float* at(int i, int j);
    void print(void);
    int rows;
    int cols;
    float* elements;
    float det();
    Matrix submat(int x0, int x1, int y0, int y1);
  private:
    float* allocMat();
  };

}

namespace nn {
  // Returns a number between 1 and 0.
  extern float randf();

  // TODO: Support for multiple layers
  class Network{
    public:
    Network(int num_neurons, bool zeroed);
    Network(int num_neurons);
    void print();
    la::Matrix* weights;
    la::Matrix* biases;
    private:
    int num_neurons;
    float accuracy(la::Matrix training_set);
  };
}

#endif // NETWORK_H_
