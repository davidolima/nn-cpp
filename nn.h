#ifndef NETWORK_H_
#define NETWORK_H_
#include <math.h>

namespace la {
  class Matrix {
    public:
      Matrix(int rows, int cols){
        this->elements = (float*) malloc(rows*cols*sizeof(float));
        this->rows = rows;
        this->cols = cols;
      }
      Matrix mm(Matrix other);
      void add_(Matrix other);
      Matrix add(Matrix other);

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
  };
}

#endif // NETWORK_H_
