#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "mat4.h"
#include "quat.h"
#include "scalar.h"
#include "vec3.h"

float* QuatFloats(Quat* quat) {
  return &quat->x;
}

Quat QuatMakeAngleAxis(float angle, Vec3 axis) {
  Vec3 norm = Vec3Norm(axis);
  float l = Vec3Len(axis);
  if (l == 0) {
    return (Quat) {0};
  }

  float sin_angle = sinf(angle * 0.5f);
  float cos_angle = cosf(angle * 0.5f);
  float s = sin_angle / l;
  return (Quat){
      .x = norm.x * s,
      .y = norm.y * s,
      .z = norm.z * s,
      .w = cos_angle,
  };
}

Quat QuatMakeFromTo(Vec3 from, Vec3 to) {
  Vec3 c = Vec3Cross(from, to);
  float d = Vec3Dot(from, to);

  if (d < -1.0f + XMATH_EPSILON) {
    return (Quat) {0.0f, 1.0f, 0.0f, 0.0f};
  }

  float s = sqrtf((1.0f + d) * 2.0f);
  float rs = 1.0f / s;
  return (Quat) {
      .x = c.x * rs,
      .y = c.y * rs,
      .z = c.z * rs,
      .w = s * 0.5f,
  };
}

Vec3 QuatGetAxis(Quat q) {
  Vec3 v = {q.x, q.y, q.z};
  return Vec3Norm(v);
}

float QuatGetAngle(Quat q) {
  return 2.0f * acosf(q.w);
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
  if (d < 0.0f) {
    target = QuatNeg(to);
    d = -d;
  }

  // Perform linear interpolation when cosTheta is close to 1
  if (d > 1.0f - XMATH_EPSILON) {
    return QuatLerp(from, target, t);
  }

  float theta = acosf(d);
  Quat a = QuatScale(from, sinf((1.0f - t) * theta));
  Quat b = QuatScale(target, sinf(t * theta));
  Quat c = QuatAdd(a, b);
  return QuatScale(c, 1.0f / sinf(theta));
}

Quat QuatLookRotation(Vec3 dir, Vec3 up) {
  Vec3 d = Vec3Scale(dir, -1);
  Vec3 r = Vec3Cross(up, d);
  Vec3 a = Vec3Scale(r, 1.0f / sqrtf(FMax(0.00001f, Vec3Dot(r, r))));
  Vec3 b = Vec3Cross(d, a);

  // clang-format off
  Mat4 m = {
     a.x,  a.y,  a.z, 0.0f,
     b.x,  b.y,  b.z, 0.0f,
     d.x,  d.y,  d.z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  // clang-format on
  return Mat4ToQuat(m);
}

Mat4 QuatToMat4(Quat q) {
  Vec3 r = QuatTransformVec3(q, Vec3Right);
  Vec3 u = QuatTransformVec3(q, Vec3Up);
  Vec3 f = QuatTransformVec3(q, Vec3Back);
  // clang-format off
  return (Mat4){
     r.x,  r.y,  r.z, 0.0f,
     u.x,  u.y,  u.z, 0.0f,
     f.x,  f.y,  f.z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  };
  // clang-format on
}

Quat Mat4ToQuat(Mat4 m) {
  float fx = m.xx - m.yy - m.zz;
  float fy = m.yy - m.xx - m.zz;
  float fz = m.zz - m.xx - m.yy;
  float fw = m.xx + m.yy + m.zz;

  unsigned bi = 0;
  float fb = fw;
  if (fx > fb) {
    fb = fx;
    bi = 1;
  }

  if (fy > fb) {
    fb = fy;
    bi = 2;
  }

  if (fz > fb) {
    fb = fz;
    bi = 3;
  }

  float bv = sqrtf(fb + 1.0f) * 0.5f;
  float fm = 0.25f / bv;
  switch (bi) {
    case 0:
      return (Quat){
          (m.yz - m.zy) * fm,
          (m.zx - m.xz) * fm,
          (m.xy - m.yx) * fm,
          bv,
      };
    case 1:
      return (Quat){
          bv,
          (m.xy + m.yx) * fm,
          (m.zx + m.xz) * fm,
          (m.yz - m.zy) * fm,
      };
    case 2:
      return (Quat){
          (m.xy + m.yx) * fm,
          bv,
          (m.yz + m.zy) * fm,
          (m.zx - m.xz) * fm,
      };
    case 3:
      return (Quat){
          (m.zx + m.xz) * fm,
          (m.yz + m.zy) * fm,
          bv,
          (m.xy - m.yx) * fm,
      };
    default:
      assert(false && "unreachable code: undefined biggest index");
      return QuatIdentity;
  }
}
