#include "nn.h"
#include <math.h>

using namespace la;

namespace strassen{
  const int min_size = 16; // FIXME arbitrary value, for now 
  Matrix fill_to_power2(Matrix);

  class BlockMatrix{
    public: 
      Matrix topleft, topright, bottomleft, bottomright;

      BlockMatrix(Matrix topleft, Matrix topright, Matrix bottomleft, Matrix bottomright);

      BlockMatrix(Matrix m);

      Matrix join();
  };

  Matrix strassen_mm(Matrix, Matrix);
}
