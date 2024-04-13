#ifndef NETWORK_H_
#define NETWORK_H_
#include <math.h>
#include <iostream>
#include <vector>

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
      this->elements = (float*) malloc((rows+2)*(cols+2)*sizeof(float));
      if (this->elements == NULL) {
        printf("Error allocating memory for matrix. Tried to allocate %zu bytes.\n", (rows*cols*sizeof(float)));
        exit (EXIT_FAILURE);
      }
      this->rows = rows;
      this->cols = cols;
      this->fill(0.f);
    }

    Matrix(std::initializer_list<std::initializer_list<float>> elements){
      std::initializer_list<std::initializer_list<float>>::iterator row_it = elements.begin();
      *this = Matrix(elements.size(), (*row_it).size());

      for (int i = 0; i != this->rows; row_it++, i++){
        int j = 0;
        for (std::initializer_list<float>::iterator col_it = row_it->begin(); col_it != row_it->end(); col_it++, j++){
          *this->at(i,j) = *col_it;
        }
      }
    }

    // operations
    Matrix mm(Matrix other);
    Matrix add(Matrix other);
    void add_(Matrix other);
    Matrix operator+(void); // unary plus
    Matrix operator+(Matrix other); // binary plus
    Matrix operator-(void); // unary minus
    Matrix operator-(Matrix other); // binary plus
    Matrix operator*(Matrix other); // multiplication operator
    void operator+=(Matrix other);
    void operator-=(Matrix other);
    bool operator==(Matrix other);
    bool operator!=(Matrix other);
    
    float* at(int i, int j);
    void print(void);
    int rows;
    int cols;
    float* elements;
    float det();
    Matrix transpose();
    void transpose_();
    float trace();
    void fill(float value);
    Matrix submat(int x0, int x1, int y0, int y1);
    Matrix submat(int p, int q);
  private:
  };
  Matrix identity(int size);
  Matrix ones(int rows, int cols);
  Matrix generic(int rows, int cols);
  Matrix fromVector(std::vector<std::vector<float>> elements);
}

namespace nn {
  // Returns a number between 1 and 0.
  extern float randf();
  float* at(int i, int j);
  void print(void);
  static Matrix zeroes(int rows, int cols);
  static Matrix ones(int rows, int cols);
  int rows;
  int cols;
  float* elements;

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
