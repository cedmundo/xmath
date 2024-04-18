// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "quat.h"
#include "common_testing.h"
#include "scalar.h"

static void test_Constants(void** state) {
  UNUSED(state);

  Quat zero = {0};
  assert_true(QuatEqualApprox(zero, QuatZero));

  Quat identity = {0.0f, 0.0f, 0.0f, 1.0f};
  assert_true(QuatEqualApprox(identity, QuatIdentity));
}

static void test_QuatFloats(void** state) {
  UNUSED(state);

  Quat q = {1.0f, 2.0f, 3.0f, 4.0f};
  float* f = QuatFloats(&q);
  assert_float_equal(f[1], 2.0f, XMATH_EPSILON);

  q.y = 4.0f;
  assert_float_equal(f[1], 4.0f, XMATH_EPSILON);
}

static void test_QuatMakeAngleAxis(void** state) {
  UNUSED(state);

  Vec3 axis = {1.0f, 0.0f, 0.0f};
  float angle = FDeg2Rad(90.0f);
  Quat q = QuatMakeAngleAxis(angle, axis);
  Quat e = {0.707106709f, 0.0f, 0.0f, 0.707106709f};
  assert_true(QuatEqualApprox(q, e));
}

static void test_QuatMakeFromTo(void** state) {
  UNUSED(state);

  Vec3 from = Vec3Norm(Vec3Down);
  Vec3 to = Vec3Norm(Vec3Forward);
  Quat q = QuatMakeFromTo(from, to);
  Quat e = {0.707106709f, 0.0f, 0.0f, 0.707106709f};
  assert_true(QuatEqualApprox(q, e));

  from = Vec3Norm(Vec3Back);
  to = Vec3Norm(Vec3Forward);
  q = QuatMakeFromTo(from, to);
  e = (Quat){0.0f, 1.0f, 0.0f, 0.0f};
  assert_true(QuatEqualApprox(q, e));
}

static void test_QuatGet(void** state) {
  UNUSED(state);

  Quat q = {0.274506f, 0.109802f, 0.054901f, 0.953717f};
  Vec3 qAxis = QuatGetAxis(q);
  Vec3 eAxis = {0.912871f, 0.365148f, 0.182574f};
  assert_true(Vec3EqualApprox(qAxis, eAxis));

  float qAngle = QuatGetAngle(q);
  float eAngle = 0.61086535453796f;
  assert_true(FEqualApprox(qAngle, eAngle));

  Vec3 qImg = QuatGetImgPart(q);
  Vec3 eImg = {0.274506f, 0.109802f, 0.054901f};
  assert_true(Vec3EqualApprox(qImg, eImg));

  float qReal = QuatGetRealPart(q);
  float eReal = 0.953717f;
  assert_true(FEqualApprox(qReal, eReal));
}

static void test_QuatAdd(void** state) {
  UNUSED(state);

  Quat a = {0.23f, 0.31f, 0.79f, 0.47f};
  Quat b = {0.30f, 0.55f, 0.30f, 0.56f};
  Quat e = {0.53f, 0.86f, 1.09f, 1.03f};
  Quat r = QuatAdd(a, b);
  assert_true(QuatEqualApprox(r, e));
}

static void test_QuatSub(void** state) {
  UNUSED(state);

  Quat a = {0.23f, 0.31f, 0.79f, 0.47f};
  Quat b = {0.30f, 0.55f, 0.30f, 0.56f};
  Quat e = {-0.070f, -0.240f, 0.490f, -0.090f};
  Quat r = QuatSub(a, b);
  assert_true(QuatEqualApprox(r, e));
}

static void test_QuatScale(void** state) {
  UNUSED(state);

  Quat q = {0.23f, 0.31f, 0.79f, 0.47f};
  Quat e = {0.460f, 0.620f, 1.580f, 0.940f};
  Quat r = QuatScale(q, 2.0f);
  assert_true(QuatEqualApprox(r, e));
}

static void test_QuatNeg(void** state) {
  UNUSED(state);

  Quat q = {0.23f, 0.31f, 0.79f, 0.47f};
  Quat e = {-0.23f, -0.31f, -0.79f, -0.47f};
  Quat r = QuatNeg(q);
  assert_true(QuatEqualApprox(r, e));
}

static void test_QuatSameOrientation(void** state) {
  UNUSED(state);

  Quat a = QuatMakeAngleAxis(FDeg2Rad(360.0f), Vec3Forward);
  Quat b = QuatMakeAngleAxis(FDeg2Rad(0.0f), Vec3Forward);
  assert_true(QuatSameOrientation(a, b));

  a = QuatMakeAngleAxis(FDeg2Rad(90.0f), Vec3Forward);
  b = QuatMakeAngleAxis(FDeg2Rad(180.0f), Vec3Forward);
  assert_false(QuatSameOrientation(a, b));
}

static void test_QuatDot(void** state) {
  UNUSED(state);

  Quat a = {0.274506f, 0.109802f, 0.054901f, 0.953717f};
  Quat b = {-0.033477f, 0.044637f, 0.066955f, 0.996195f};
  float e = 0.94947510957718f;
  float r = QuatDot(a, b);
  assert_true(FEqualApprox(e, r));

  a = QuatMakeAngleAxis(0.0f, Vec3Forward);
  b = QuatMakeAngleAxis(0.0f, Vec3Back);
  e = 1.0f;
  r = QuatDot(a, b);
  assert_true(FEqualApprox(e, r));
}

static void test_QuatSqrLen(void** state) {
  UNUSED(state);

  Quat a = {0.137253f, 0.054901f, 0.027451f, 0.476858f};
  float e = 0.25f;
  float r = QuatSqrLen(a);
  assert_true(FEqualApprox(e, r));
}

static void test_QuatLen(void** state) {
  UNUSED(state);

  Quat a = {0.137253f, 0.054901f, 0.027451f, 0.476858f};
  float e = 0.5f;
  float r = QuatLen(a);
  assert_true(FEqualApprox(e, r));
}

static void test_QuatNorm(void** state) {
  UNUSED(state);

  Quat a = {0.631363f, 0.252545f, 0.126273f, 2.193549f};
  Quat e = {0.274506f, 0.109802f, 0.054901f, 0.953717f};
  Quat r = QuatNorm(a);
  assert_true(QuatEqualApprox(e, r));
}

static void test_QuatConjugate(void** state) {
  UNUSED(state);

  Quat a = {0.210f, 0.760f, 0.290f, 0.330f};
  Quat e = {-0.210f, -0.760f, -0.290f, 0.330f};
  Quat r = QuatConjugate(a);
  assert_true(QuatEqualApprox(e, r));
}

static void test_QuatInvert(void** state) {
  UNUSED(state);

  Quat a = {0.274506f, 0.109802f, 0.054901f, 0.953717f};
  Quat e = {-0.274506f, -0.109802f, -0.054901f, 0.953717f};
  Quat r = QuatInvert(a);
  assert_true(QuatEqualApprox(e, r));
}

static void test_QuatCross(void** state) {
  UNUSED(state);

  Quat a = {0.23f, 0.31f, 0.79f, 0.47f};
  Quat b = {0.55f, 0.30f, 0.56f, 0.56f};
  Quat e = {0.3239f, 0.6203f, 0.6041f, -0.3987f};
  Quat r = QuatCross(a, b);
  assert_true(QuatEqualApprox(r, e));
}

static void test_QuatTransformVec3(void** state) {
  UNUSED(state);

  Quat a = {0.274506f, 0.109802f, 0.054901f, 0.953717f};
  Vec3 b = {0.3f, 0.3f, 0.3f};
  Vec3 e = {0.349501f, 0.149017f, 0.354462f};
  Vec3 r = QuatTransformVec3(a, b);
  assert_true(Vec3EqualApprox(r, e));

  a = (Quat){-0.033477f, 0.044637f, 0.066955f, 0.996195f};
  b = (Vec3){0.0f, 0.0f, 1.0f};
  e = (Vec3){0.084451f, 0.072677f, 0.993774f};
  r = QuatTransformVec3(a, b);
  assert_true(Vec3EqualApprox(r, e));
}

static void test_QuatLerp(void** state) {
  UNUSED(state);

  Quat a = {0.23f, 0.31f, 0.79f, 0.47f};
  Quat b = {0.55f, 0.30f, 0.56f, 0.56f};
  Quat e = {0.390000015f, 0.305000007f, 0.675000012f, 0.514999986f};
  float c = 0.5f;
  Quat r = QuatLerp(a, b, c);
  assert_true(QuatEqualApprox(r, e));
}

static void test_QuatNLerp(void** state) {
  UNUSED(state);

  Quat a = {0.23f, 0.31f, 0.79f, 0.47f};
  Quat b = {0.55f, 0.30f, 0.56f, 0.56f};
  Quat e = {0.396809f, 0.310325f, 0.686785f, 0.523992f};
  float c = 0.5f;
  Quat r = QuatNLerp(a, b, c);
  assert_true(QuatEqualApprox(r, e));
}

static void test_QuatSLerp(void** state) {
  UNUSED(state);

  Quat a = {0.23f, 0.31f, 0.79f, 0.47f};
  Quat b = {0.55f, 0.30f, 0.56f, 0.56f};
  Quat e = {0.0537898f, 0.297403f, 0.862126f, 0.397308f};
  float c = -0.5f;
  Quat r = QuatSLerp(a, b, c);
  assert_true(QuatEqualApprox(r, e));
}

static void test_QuatLookRotation(void** state) {
  UNUSED(state);

  Vec3 a = {1.0f, 1.0f, 1.0f};
  Vec3 b = {0.0f, 1.0f, 0.0f};
  Quat e = {-0.174155354f, 1.01505172f, -0.420448244f, -0.420448244f};
  Quat r = QuatLookRotation(a, b);
  assert_true(QuatEqualApprox(r, e));
}

static void test_QuatToMat4(void** state) {
  UNUSED(state);

  Quat q = {0.274506f, 0.109802f, 0.054901f, 0.953717f};
  Mat4 r = QuatToMat4(q);
  // clang-format off
  Mat4 e = {
    0.969859f, 0.165003f, -0.179299f, 0.000f,
    -0.044437f, 0.843265f, 0.535658f,   0.000f,
     0.239581f, -0.511545f, 0.82518f,   0.000f,
     0.000f,  0.000f, 0.000f, 1.000f,
  };
  // clang-format on
  assert_true(Mat4EqualApprox(r, e));
}

static void test_Mat4ToQuat(void** state) {
  UNUSED(state);

  // clang-format off
  Mat4 m = {
    -0.446400017f,  0.885200024f, 0.0719999969f, 0.000f,
    -0.600000024f, -0.360000014f, 0.70600003f,   0.000f,
     0.654800057f,  0.273599982f, 0.69600004f,   0.000f,
     0.000f,  0.000f, 0.000f, 1.000f,
  };
  // clang-format on
  Quat e = {0.229724109f, 0.309628129f, 0.790948808f, 0.469436198f};
  Quat r = Mat4ToQuat(m);
  assert_true(QuatEqualApprox(r, e));
}

int main() {
  UNUSED_TYPE(jmp_buf);
  UNUSED_TYPE(va_list);

  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_Constants),
      cmocka_unit_test(test_Constants),
      cmocka_unit_test(test_QuatFloats),
      cmocka_unit_test(test_QuatMakeAngleAxis),
      cmocka_unit_test(test_QuatMakeFromTo),
      cmocka_unit_test(test_QuatGet),
      cmocka_unit_test(test_QuatAdd),
      cmocka_unit_test(test_QuatSub),
      cmocka_unit_test(test_QuatScale),
      cmocka_unit_test(test_QuatNeg),
      cmocka_unit_test(test_QuatSameOrientation),
      cmocka_unit_test(test_QuatDot),
      cmocka_unit_test(test_QuatSqrLen),
      cmocka_unit_test(test_QuatLen),
      cmocka_unit_test(test_QuatNorm),
      cmocka_unit_test(test_QuatConjugate),
      cmocka_unit_test(test_QuatInvert),
      cmocka_unit_test(test_QuatCross),
      cmocka_unit_test(test_QuatTransformVec3),
      cmocka_unit_test(test_QuatLerp),
      cmocka_unit_test(test_QuatNLerp),
      cmocka_unit_test(test_QuatSLerp),
      cmocka_unit_test(test_QuatLookRotation),
      cmocka_unit_test(test_QuatToMat4),
      cmocka_unit_test(test_Mat4ToQuat),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
