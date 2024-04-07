//
// Created on 4/7/24.
//
#include <math.h>

#include "quat.h"
#include "scalar.h"
#include "vec3.h"

float* QuatFloats(Quat* quat) {
  return &quat->x;
}

Quat QuatMakeAngleAxis(float angle, Vec3 axis) {
  Vec3 norm = Vec3Norm(axis);
  float s = sinf(angle * 0.5f);
  return (Quat){
      .x = norm.x * s,
      .y = norm.y * s,
      .z = norm.z * s,
      cosf(angle * 0.5f),
  };
}

Quat QuatMakeFromTo(Vec3 from, Vec3 to) {
  Vec3 fromNorm = Vec3Norm(from);
  Vec3 toNorm = Vec3Norm(to);
  float fromToDot = Vec3Dot(fromNorm, toNorm);
  if (fromToDot == 1.0f) {
    return QuatIdentity;
  } else if (fromToDot == -1.0f) {
    Vec3 ortho = {1.0f, 0.0f, 0.0f};
    if (fabsf(fromNorm.y) < fabsf(fromNorm.x)) {
      ortho = (Vec3){0.0f, 1.0f, 0.0f};
    }
    if (fabsf(fromNorm.z) < fabsf(fromNorm.y) &&
        fabsf(fromNorm.z) < fabsf(fromNorm.x)) {
      ortho = (Vec3){0.0f, 0.0f, 1.0f};
    }

    Vec3 axis = Vec3Norm(Vec3Cross(fromNorm, ortho));
    return (Quat){axis.x, axis.y, axis.z, 0};
  }

  Vec3 half = Vec3Norm(Vec3Add(fromNorm, toNorm));
  Vec3 axis = Vec3Cross(fromNorm, half);
  return (Quat){axis.x, axis.y, axis.z, Vec3Dot(fromNorm, half)};
}

Vec3 QuatGetAxis(Quat quat) {
  return Vec3Norm((Vec3){quat.x, quat.y, quat.z});
}

float QuatGetAngle(Quat quat) {
  return 2.0f * acosf(quat.w);
}

bool QuatEqualApprox(Quat a, Quat b) {
  return FEqualApprox(a.x, b.x) && FEqualApprox(a.y, b.y) &&
         FEqualApprox(a.z, b.z) && FEqualApprox(a.w, b.w);
}

Quat QuatAdd(Quat a, Quat b) {
  return (Quat){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

Quat QuatSub(Quat a, Quat b) {
  return (Quat){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

Quat QuatScale(Quat q, float s) {
  return (Quat){q.x * s, q.y * s, q.z * s, q.w * s};
}

Quat QuatNeg(Quat q) {
  return QuatScale(q, -1);
}

bool QuatSameOrientation(Quat a, Quat b) {
  return (fabsf(a.x - b.x) <= XMATH_EPSILON &&
          fabsf(a.y - b.y) <= XMATH_EPSILON &&
          fabsf(a.z - b.z) <= XMATH_EPSILON &&
          fabsf(a.w - b.w) <= XMATH_EPSILON) ||
         (fabsf(a.x + b.x) <= XMATH_EPSILON &&
          fabsf(a.y + b.y) <= XMATH_EPSILON &&
          fabsf(a.z + b.z) <= XMATH_EPSILON &&
          fabsf(a.w + b.w) <= XMATH_EPSILON);
}

float QuatDot(Quat a, Quat b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}