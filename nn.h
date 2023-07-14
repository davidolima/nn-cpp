#ifndef NETWORK_H_
#define NETWORK_H_
#include <math.h>

namespace nn {
}

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
#endif // NETWORK_H_
