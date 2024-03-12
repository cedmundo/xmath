#include "vec3.h"
#include "scalar.h"

#include <math.h>

float* Vec3Floats(Vec3* vec) {
  return &vec->x;
}

bool Vec3EqualApprox(Vec3 a, Vec3 b) {
  Vec3 diff = Vec3Sub(a, b);
  return Vec3Len(diff) <= XMATH_EPSILON;
}

Vec3 Vec3Add(Vec3 a, Vec3 b) {
  return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 Vec3Sub(Vec3 a, Vec3 b) {
  return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 Vec3Scale(Vec3 v, float s) {
  return (Vec3){v.x * s, v.y * s, v.z * s};
}

float Vec3SqrLen(Vec3 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

float Vec3Len(Vec3 v) {
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 Vec3Norm(Vec3 v) {
  float vl = Vec3Len(v);
  if (vl < XMATH_EPSILON) {
    return v;
  }

  float k = 1.0f / vl;
  return Vec3Scale(v, k);
}

Vec3 Vec3Max(Vec3 a, Vec3 b) {
  Vec3 r = {0};
  r.x = FMax(a.x, b.x);
  r.y = FMax(a.y, b.y);
  r.z = FMax(a.z, b.z);
  return r;
}

Vec3 Vec3Min(Vec3 a, Vec3 b) {
  Vec3 r = {0};
  r.x = FMin(a.x, b.x);
  r.y = FMin(a.y, b.y);
  r.z = FMin(a.z, b.z);
  return r;
}

float Vec3Angle(Vec3 a, Vec3 b) {
  float aSqrLen = Vec3SqrLen(a);
  float bSqrLen = Vec3SqrLen(b);
  if (aSqrLen < XMATH_EPSILON || bSqrLen < XMATH_EPSILON) {
    return 0.0f;
  }

  float dot = Vec3Dot(a, b);
  return acosf(dot / (sqrtf(aSqrLen) * sqrtf(bSqrLen)));
}

float Vec3Dot(Vec3 a, Vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3Cross(Vec3 l, Vec3 r) {
  return (Vec3){
      l.y * r.z - l.z * r.y,
      l.z * r.x - l.x * r.z,
      l.x * r.y - l.y * r.x,
  };
}

Vec3 Vec3Project(Vec3 a, Vec3 b) {
  float bSqrLen = Vec3SqrLen(b);
  if (bSqrLen < XMATH_EPSILON) {
    return Vec3Zero;
  }

  float scale = Vec3Dot(a, b) / bSqrLen;
  return Vec3Scale(b, scale);
}

Vec3 Vec3Reject(Vec3 a, Vec3 b) {
  Vec3 p = Vec3Project(a, b);
  return Vec3Sub(a, p);
}

Vec3 Vec3Reflect(Vec3 a, Vec3 b) {
  Vec3 n = Vec3Norm(b);
  Vec3 r = Vec3Sub(a, Vec3Scale(n, 2 * Vec3Dot(a, n)));
  return r;
}

Vec3 Vec3Lerp(Vec3 a, Vec3 b, float f) {
  return (Vec3){
      a.x + (b.x - a.x) * f,
      a.y + (b.y - a.y) * f,
      a.z + (b.z - a.z) * f,
  };
}

Vec3 Vec3Slerp(Vec3 a, Vec3 b, float f) {
  if (f < 0.01f) {
    return Vec3Lerp(a, b, f);
  }

  Vec3 from = Vec3Norm(a);
  Vec3 to = Vec3Norm(b);

  float theta = Vec3Angle(from, to);
  float sin_theta = sinf(theta);

  float fa = sinf((1.0f - f) * theta) / sin_theta;
  float fb = sinf(f * theta) / sin_theta;
  return Vec3Add(Vec3Scale(from, fa), Vec3Scale(to, fb));
}

Vec3 Vec3Nlerp(Vec3 a, Vec3 b, float f) {
  Vec3 r = (Vec3){
      a.x + (b.x - a.x) * f,
      a.y + (b.y - a.y) * f,
      a.z + (b.z - a.z) * f,
  };
  return Vec3Norm(r);
}
