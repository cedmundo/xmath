#include "transform.h"
#include <math.h>
#include "scalar.h"

bool TransformEqualApprox(Transform a, Transform b) {
  return Vec3EqualApprox(a.position, b.position) &&
         QuatEqualApprox(a.rotation, b.rotation) &&
         Vec3EqualApprox(a.scale, b.scale);
}

Transform TransformCombine(Transform a, Transform b) {
  Transform r = {0};

  r.scale = Vec3Cross(a.scale, b.scale);
  r.rotation = QuatCross(a.rotation, b.rotation);
  r.position = QuatTransformVec3(a.rotation, Vec3Cross(a.scale, b.position));
  r.position = Vec3Add(a.position, r.position);
  return r;
}

Transform TransformInverse(Transform t) {
  Transform r = {0};

  r.rotation = QuatInvert(t.rotation);
  r.scale.x = fabsf(t.scale.x) < XMATH_EPSILON ? 0.0f : 1.0f / t.scale.x;
  r.scale.y = fabsf(t.scale.y) < XMATH_EPSILON ? 0.0f : 1.0f / t.scale.y;
  r.scale.z = fabsf(t.scale.z) < XMATH_EPSILON ? 0.0f : 1.0f / t.scale.z;

  Vec3 it = Vec3Scale(t.position, -1.0f);
  r.position = QuatTransformVec3(r.rotation, Vec3Cross(r.scale, it));
  return r;
}

Transform TransformLerp(Transform a, Transform b, float t) {
  Quat rot = b.rotation;
  if (QuatDot(a.rotation, rot) < 0.0f) {
    rot = QuatNeg(rot);
  }

  return (Transform){
      .position = Vec3Lerp(a.position, b.position, t),
      .rotation = QuatNLerp(a.rotation, rot, t),
      .scale = Vec3Lerp(a.scale, b.scale, t),
  };
}

Mat4 TransformToMat4(Transform t) {
  // Extract the rotation basis of the transform
  Vec3 x = QuatTransformVec3(t.rotation, Vec3Right);
  Vec3 y = QuatTransformVec3(t.rotation, Vec3Up);
  Vec3 z = QuatTransformVec3(t.rotation, Vec3Backward);

  // Scale the basis vectors
  x = Vec3Scale(x, t.scale.x);
  y = Vec3Scale(y, t.scale.y);
  z = Vec3Scale(z, t.scale.z);

  // Extract the position of the transform
  Vec3 p = t.position;

  // TODO(cedmundo): Verify if this is the correct order of the matrix.
  // clang-format off
  return (Mat4){
    x.x, x.y, x.z, 0.0f,
    y.x, y.y, y.z, 0.0f,
    z.x, z.y, z.z, 0.0f,
    p.x, p.y, p.z, 1.0f,
  };
  // clang-format on
}

Transform Mat4ToTransform(Mat4 m) {
  Transform r = {0};

  r.position = (Vec3){m.wx, m.wy, m.wz};
  r.rotation = Mat4ToQuat(m);

  // clang-format off
  Mat4 rotScaleMat = {
    m.xx, m.xy, m.xz, 0.0f,
    m.yx, m.yy, m.yz, 0.0f,
    m.zx, m.zy, m.zz, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  };
  // clang-format on
  Mat4 invRotMat = QuatToMat4(QuatInvert(r.rotation));
  Mat4 scaleSkewMat = Mat4Mul(rotScaleMat, invRotMat);

  r.scale = (Vec3){
      scaleSkewMat.xx,
      scaleSkewMat.yy,
      scaleSkewMat.zz,
  };

  return r;
}

Vec3 TransformPoint(Transform a, Vec3 b) {
  Vec3 r = {0};
  r = QuatTransformVec3(a.rotation, Vec3Cross(a.scale, b));
  r = Vec3Add(a.position, r);
  return r;
}

Vec3 TransformVec3(Transform a, Vec3 b) {
  Vec3 r = {0};
  r = QuatTransformVec3(a.rotation, Vec3Cross(a.scale, b));
  return r;
}
