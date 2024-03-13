#include "vec4.h"
#include "scalar.h"

#include <math.h>

float* Vec4Floats(Vec4* vec) {
  return &vec->x;
}

bool Vec4EqualApprox(Vec4 a, Vec4 b) {
  Vec4 diff = Vec4Sub(a, b);
  return Vec4Len(diff) <= XMATH_EPSILON;
}

Vec4 Vec4Add(Vec4 a, Vec4 b) {
  return (Vec4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

Vec4 Vec4Sub(Vec4 a, Vec4 b) {
  return (Vec4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

Vec4 Vec4Scale(Vec4 v, float s) {
  return (Vec4){v.x * s, v.y * s, v.z * s, v.w * s};
}

float Vec4SqrLen(Vec4 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

float Vec4Len(Vec4 v) {
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

Vec4 Vec4Norm(Vec4 v) {
  float vl = Vec4Len(v);
  if (vl < XMATH_EPSILON) {
    return v;
  }

  float k = 1.0f / vl;
  return Vec4Scale(v, k);
}

Vec4 Vec4Max(Vec4 a, Vec4 b) {
  Vec4 r = {0};
  r.x = FMax(a.x, b.x);
  r.y = FMax(a.y, b.y);
  r.z = FMax(a.z, b.z);
  r.w = FMax(a.w, b.w);
  return r;
}

Vec4 Vec4Min(Vec4 a, Vec4 b) {
  Vec4 r = {0};
  r.x = FMin(a.x, b.x);
  r.y = FMin(a.y, b.y);
  r.z = FMin(a.z, b.z);
  r.w = FMin(a.w, b.w);
  return r;
}

float Vec4Angle(Vec4 a, Vec4 b) {
  float aSqrLen = Vec4SqrLen(a);
  float bSqrLen = Vec4SqrLen(b);
  if (aSqrLen < XMATH_EPSILON || bSqrLen < XMATH_EPSILON) {
    return 0.0f;
  }

  float dot = Vec4Dot(a, b);
  return acosf(dot / (sqrtf(aSqrLen) * sqrtf(bSqrLen)));
}

float Vec4Dot(Vec4 a, Vec4 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vec4 Vec4Project(Vec4 a, Vec4 b) {
  float bSqrLen = Vec4SqrLen(b);
  if (bSqrLen < XMATH_EPSILON) {
    return Vec4Zero;
  }

  float scale = Vec4Dot(a, b) / bSqrLen;
  return Vec4Scale(b, scale);
}

Vec4 Vec4Reject(Vec4 a, Vec4 b) {
  Vec4 p = Vec4Project(a, b);
  return Vec4Sub(a, p);
}

Vec4 Vec4Reflect(Vec4 a, Vec4 b) {
  Vec4 n = Vec4Norm(b);
  Vec4 r = Vec4Sub(a, Vec4Scale(n, 2 * Vec4Dot(a, n)));
  return r;
}

Vec4 Vec4Lerp(Vec4 a, Vec4 b, float f) {
  // TODO: handle imprecision
  return (Vec4){
      a.x + (b.x - a.x) * f,
      a.y + (b.y - a.y) * f,
      a.z + (b.z - a.z) * f,
      a.w + (b.w - a.w) * f,
  };
}

Vec4 Vec4Slerp(Vec4 a, Vec4 b, float f) {
  if (f < 0.01f) {
    return Vec4Lerp(a, b, f);
  }

  Vec4 from = Vec4Norm(a);
  Vec4 to = Vec4Norm(b);

  float theta = Vec4Angle(from, to);
  float sin_theta = sinf(theta);

  float fa = sinf((1.0f - f) * theta) / sin_theta;
  float fb = sinf(f * theta) / sin_theta;
  return Vec4Add(Vec4Scale(from, fa), Vec4Scale(to, fb));
}

Vec4 Vec4Nlerp(Vec4 a, Vec4 b, float f) {
  Vec4 r = (Vec4){
      a.x + (b.x - a.x) * f,
      a.y + (b.y - a.y) * f,
      a.z + (b.z - a.z) * f,
      a.w + (b.w - a.w) * f,
  };
  return Vec4Norm(r);
}
