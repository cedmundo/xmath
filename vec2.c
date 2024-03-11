//
// Created on 3/10/24.
//
#include <math.h>

#include "scalar.h"
#include "vec2.h"

float* Vec2Floats(Vec2* vec) {
  return &vec->x;
}

bool Vec2EqualApprox(Vec2 a, Vec2 b) {
  return FEqualApprox(a.x, b.x) && FEqualApprox(a.y, b.y);
}

Vec2 Vec2Add(Vec2 a, Vec2 b) {
  return (Vec2){a.x + b.x, a.y + b.y};
}

Vec2 Vec2Sub(Vec2 a, Vec2 b) {
  return (Vec2){a.x - b.x, a.y - b.y};
}

Vec2 Vec2Scale(Vec2 v, float f) {
  return (Vec2){v.x * f, v.y * f};
}

float Vec2SqrLen(Vec2 v) {
  return v.x * v.x + v.y * v.y;
}

float Vec2Len(Vec2 v) {
  return sqrtf(v.x * v.x + v.y * v.y);
}

Vec2 Vec2Norm(Vec2 v) {
  float k = 1.0f / Vec2Len(v);
  return Vec2Scale(v, k);
}

Vec2 Vec2Max(Vec2 a, Vec2 b) {
  Vec2 r;
  r.x = FMax(a.x, b.x);
  r.y = FMax(a.y, b.y);
  return r;
}

Vec2 Vec2Min(Vec2 a, Vec2 b) {
  Vec2 r;
  r.x = FMin(a.x, b.x);
  r.y = FMin(a.y, b.y);
  return r;
}
