#include "../strassen.h"
#include "../nn.h"
#include <cassert>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

const float epsilon = 1e-4;

float randfloat(const float a, const float b){
  float x = ((float)rand()) / ((float)(RAND_MAX)); // float in [0,1]

  return (b - a) * x + a;
}

int randint(const int a, const int b){
  /**
      Generate random integer in [a, b] */
  assert(b > a);
  return (rand() % (b + 1 - a)) + a;
}

la::Matrix random_matrix(const float min, const float max,
                         const int rows, const int cols){
  la::Matrix m = la::Matrix{rows, cols};

  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      *m.at(i, j) = randfloat(min, max);
    }
  }
  return m;
}

float L1Norm(la::Matrix m1, la::Matrix m2){
  float s = 0.0;
  assert(m1.rows == m2.rows && m1.cols == m2.cols);

  for (int i = 0; i < m1.rows; i++){
    for (int j = 0; j < m1.cols; j++){
      s += fabs(*m1.at(i, j) - *m2.at(i, j));
    }
  }
  return s;
}

void test_strassen(const int num_samples,
                   const float min_v, const float max_v,
                   const int min_r, const int max_r,
                   const int min_c, const int max_c){
  int failed = 0;
  float max_avg_err = 0.0;
  double time_standard_sec = 0.0;
  double time_strassen_sec = 0.0;

  la::Matrix samples1[num_samples];
  la::Matrix samples2[num_samples];

  for (int i = 0; i < num_samples; i++){
    int rows1 = randint(min_r, max_r + 1);
    int common_dim = randint(min_c, max_c + 1);
    int cols2 = randint(min_c, max_c + 1);

    samples1[i] = random_matrix(min_v, max_v, rows1, common_dim);
    samples2[i] = random_matrix(min_v, max_v, common_dim, cols2);
  }

  for (int i = 0; i < num_samples; i++){
    la::Matrix m1 = samples1[i];
    la::Matrix m2 = samples2[i];

    la::Matrix prod = m1.mm(m2);
    la::Matrix prod_strassen = strassen::mm(m1, m2);

    // per entry
    float avg_err = L1Norm(prod, prod_strassen) / ((float)(prod.rows * prod.cols));
    if (avg_err > epsilon){
      ++failed;
    }
    if (avg_err > max_avg_err){
      max_avg_err = avg_err;
    }

    // destruct matrix objects on heap
    // m1.la::Matrix::~Matrix();
    // m2.la::Matrix::~Matrix();
    // prod.la::Matrix::~Matrix();
    // prod_strassen.la::Matrix::~Matrix();
  }
  if (failed > 0){
    printf("Failed %d test cases, with maximum average error %.6f\n", failed, max_avg_err);
  } else {
    printf("All test cases passed, with maximum average error %.6f\n", max_avg_err);
  }

  // for timing purposes only

  // time standard algorithm
  time_t start, end;
  start = time(NULL) * 1000; // in ms
  for (int i = 0; i < num_samples; i++){
    la::Matrix m1 = samples1[i];
    la::Matrix m2 = samples2[i];

    la::Matrix prod = m1.mm(m2);
  }
  end = time(NULL) * 1000; // in ms
  time_standard_sec += difftime(end, start);

  // time standard algorithm
  start = time(NULL) * 1000; // in ms
  for (int i = 0; i < num_samples; i++){
    la::Matrix m1 = samples1[i];
    la::Matrix m2 = samples2[i];

    la::Matrix prod = strassen::mm(m1, m2);
  }
  end = time(NULL) * 1000; // in ms
  time_strassen_sec += difftime(end, start);

  printf("Total elapsed time for %d testcases (with standard algorithm): %.6f\n", num_samples, time_standard_sec);
  printf("Total elapsed time for %d testcases (with Strassen algorithm): %.6f\n", num_samples, time_strassen_sec);
}

int main(int argc, char** argv){
  int num_samples = std::stoi(argv[1]);
  int max_r = std::stoi(argv[2]);
  int max_c = std::stoi(argv[3]);
  float min_v = -1e6; float max_v = +1e6;

  if (argc > 4){
    max_v = std::stof(argv[4]);
    min_v = -max_v;
  }
  if (argc > 5){
    min_v = std::stof(argv[5]);
  }

  test_strassen(num_samples, min_v, max_v, 1, max_r, 1, max_c);
}
