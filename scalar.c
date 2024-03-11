#include "scalar.h"

#include <assert.h>
#include <math.h>

bool FEqualApprox(float a, float b) {
  return fabsf(a - b) < XMATH_EPSILON;
}

float FMax(float a, float b) {
  return a > b ? a : b;
}

float FMin(float a, float b) {
  return a < b ? a : b;
}

float FLerp(float first, float second, float factor) {
  assert(factor >= 0.0f && factor <= 1.0f && "invalid arg: factor must be between 0.0 and 1.0");
  return (1 - factor) * first + factor * second;
}

float FRemap(float value, float minSrc, float maxSrc, float minDst, float maxDst) {
  return minDst + (value - minSrc) * (maxDst - maxSrc) / (maxSrc - minSrc);
}

float FRad2Deg(float rad) {
  return 57.29578f * rad;
}

float FDeg2Rad(float deg) {
  return 0.01745329f * deg;
}