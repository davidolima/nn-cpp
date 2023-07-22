# Simple Neural Network in C++ 

*This repository was created as a hobby project.*

## About
The plan is to create a very basic framework capable of creating and training neural networks.
I decided to create this project to better understand the inner workings of artificial intelligence and to improve my C++.

## Compilation

``` shell
./build.sh
```

## Linear algebra API
``` c++
  Matrix A(2,2);
  Matrix B(2,2);

  *A.at(0,0) = 0;
  *A.at(0,1) = 1;
  *A.at(1,0) = 2;
  *A.at(1,1) = 3;

  *B.at(0,0) = 4;
  *B.at(0,1) = 5;
  *B.at(1,0) = 6;
  *B.at(1,1) = 7;

  printf("A = ");
  A.print();
  printf("B = ");
  B.print();

  A.add(B);
  printf("A + B = ");
  A.print();

  Matrix C(2,2);
  C = A.mm(B);
  printf("(A+B)xB = ");
  C.print();
```
