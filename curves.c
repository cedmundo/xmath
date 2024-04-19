#include "curves.h"

Vec3 BeizerInterpolate(BeizerCurve curve, float t) {
  float it = 1.0f - t;
  Vec3 a = Vec3Scale(curve.p1, it * it * it);
  Vec3 b = Vec3Scale(curve.c1, 3.0f * it * it * t);
  Vec3 c = Vec3Scale(curve.c2, 3.0f * it * t * t);
  Vec3 d = Vec3Scale(curve.p2, t * t * t);
  return Vec3Add(Vec3Add(Vec3Add(a, b), c), d);
}

Vec3 HermitInterpolate(HermitCurve curve, float t) {
  Vec3 a = Vec3Scale(curve.p1, (1.0f + 2.0f * t) * (1.0f - t) * (1.0f - t));
  Vec3 b = Vec3Scale(curve.s1, t * (1.0f - t) * (1.0f - t));
  Vec3 c = Vec3Scale(curve.p2, (t * t) * (3.0f - 2.0f * t));
  Vec3 d = Vec3Scale(curve.s2, (t * t) * (t - 1.0f));
  return Vec3Add(Vec3Add(Vec3Add(a, b), c), d);
}
