#include <iostream>
#include <vector>
#include "../nn.h"

using namespace std;
using namespace la;

int test_add(){
    Matrix A = generic(5,5);

    vector<vector<float>> t_vector = {
      {2,   4,  6,  8, 10},
      {12, 14, 16, 18, 20},
      {22, 24, 26, 28, 30},
      {32, 34, 36, 38, 40},
      {42, 44, 46, 48, 50}
    };
    Matrix B = fromVector(t_vector);

    Matrix C = A.add(A);
    A.add_(A);

    if (A != B){
        printf("Matrix.add_() not working correctly.");
        printf("A = "); A.print();
        printf("B = "); B.print();
        printf("C = "); C.print();
        return 1;
    }
    if (C != B){
        printf("Matrix.add() not working correctly.");
        printf("A = "); A.print();
        printf("B = "); B.print();
        printf("C = "); C.print();
        return 1;
    }

    return 0;
}

int test_mul(){
    Matrix A = generic(5,5);
    Matrix I = identity(5).multiply(2);

    vector<vector<float>> t_vector = {
      {2,   4,  6,  8, 10},
      {12, 14, 16, 18, 20},
      {22, 24, 26, 28, 30},
      {32, 34, 36, 38, 40},
      {42, 44, 46, 48, 50}
    };
    Matrix B = fromVector(t_vector);

    Matrix C = A.mm(I);

    if (B != C){
        printf("Matrix multiplication not working correctly.");
        printf("A = "); A.print();
        printf("I = "); I.print();
        printf("B = "); B.print();
        printf("C = "); C.print();
        return 1;
    }
    return 0;
}

int main(){
    return test_add() || test_mul();
}
