#include "scalar.h"

#include <math.h>

bool FEqualApprox(float a, float b) {
  return fabsf(a - b) < XMATH_EPSILON;
}
