#include <math.h>

#include "mat4.h"
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
      .w = cosf(angle * 0.5f),
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
  Vec3 v = {quat.x, quat.y, quat.z};
  return Vec3Norm(v);
}

float QuatGetAngle(Quat quat) {
  return 2.0f * acosf(quat.w);
}

Vec3 QuatGetImgPart(Quat q) {
  return (Vec3){q.x, q.y, q.z};
}

float QuatGetRealPart(Quat q) {
  return q.w;
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

float QuatSqrLen(Quat v) {
  return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

float QuatLen(Quat v) {
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

Quat QuatNorm(Quat v) {
  float vl = QuatLen(v);
  if (vl < XMATH_EPSILON) {
    return v;
  }

  float k = 1.0f / vl;
  return QuatScale(v, k);
}

Quat QuatConjugate(Quat q) {
  return (Quat){-q.x, -q.y, -q.z, q.w};
}

Quat QuatInvert(Quat q) {
  float lenSq = QuatSqrLen(q);
  if (lenSq < XMATH_EPSILON) {
    return QuatIdentity;
  }

  float recip = 1.0f / lenSq;
  return (Quat){-q.x * recip, -q.y * recip, -q.z * recip, q.w * recip};
}

Quat QuatCross(Quat a, Quat b) {
  return (Quat){
      a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
      a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
      a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
      a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
  };
}

Vec3 QuatTransformVec3(Quat q, Vec3 v) {
  float s = QuatGetRealPart(q);
  Vec3 i = QuatGetImgPart(q);
  Vec3 a = Vec3Scale(i, 2.0f * Vec3Dot(i, v));
  Vec3 b = Vec3Scale(v, s * s - Vec3Dot(i, i));
  Vec3 c = Vec3Scale(Vec3Cross(i, v), 2.0f * s);
  return Vec3Add(Vec3Add(a, b), c);
}

Quat QuatLerp(Quat from, Quat to, float t) {
  return QuatAdd(QuatScale(from, 1.0f - t), QuatScale(to, t));
}

Quat QuatNLerp(Quat from, Quat to, float t) {
  return QuatNorm(QuatLerp(from, to, t));
}

Quat QuatSLerp(Quat from, Quat to, float t) {
  Quat target = to;
  float d = QuatDot(from, to);

  // if theta < 0 the interpolation will take the long way around the sphere
  if (d < 0) {
    target = QuatNeg(to);
    d = -d;
  }

  // Perform linear interpolation when cosTheta is close to 1
  if (d > 1.0f - XMATH_EPSILON) {
    return QuatLerp(from, target, t);
  }

  float theta = acosf(d);
  Quat a = QuatScale(target, sinf((1.0f - t) * theta));
  Quat b = QuatScale(from, sinf(t * theta));
  Quat c = QuatAdd(a, b);
  return QuatScale(c, 1.0f / sinf(theta));
}

Quat LookRotation(Vec3 dir, Vec3 up) {
  Vec3 f = Vec3Norm(dir);
  Vec3 u = Vec3Norm(up);
  Vec3 r = Vec3Cross(u, f);
  u = Vec3Cross(f, r);

  Quat worldToObject = QuatMakeFromTo(Vec3Backward, f);
  Vec3 objectUp = QuatTransformVec3(worldToObject, Vec3Up);
  Quat objectUpToDesiredUp = QuatMakeFromTo(objectUp, u);
  Quat result = QuatCross(worldToObject, objectUpToDesiredUp);
  return QuatNorm(result);
}

Mat4 QuatToMat4(Quat q) {
  Vec3 r = QuatTransformVec3(q, Vec3Right);
  Vec3 u = QuatTransformVec3(q, Vec3Up);
  Vec3 f = QuatTransformVec3(q, Vec3Backward);
  // clang-format off
  return (Mat4){
    r.x, r.y, r.z, 0.0f,
    u.x, u.y, u.z, 0.0f,
    f.x, f.y, f.z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  };
  // clang-format on
}

Quat Mat4ToQuat(Mat4 m) {
  Vec3 up = {m.yx, m.yy, m.yz};
  Vec3 forward = {m.zx, m.zy, m.zz};

  up = Vec3Norm(up);
  forward = Vec3Norm(forward);
  Vec3 right = Vec3Cross(up, forward);
  up = Vec3Cross(forward, right);
  return LookRotation(forward, up);
}
