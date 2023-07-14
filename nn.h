#ifndef NETWORK_H_
#define NETWORK_H_
#include <math.h>

namespace nn {
}

namespace la {
  class Matrix {
    public:
      // Note:
      // The class should have default constructor, otherwise assignments like
      // Matrix a = b will not work, since this call the default constructor
      // for a first, then the copy operation
      Matrix(){
        this->elements = nullptr;
        this->rows = 0;
        this->cols = 0;
      }

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
      static Matrix zeroes(int rows, int cols);
      static Matrix ones(int rows, int cols);
      int rows;
      int cols;
      float* elements;
  };
}
#endif // NETWORK_H_
