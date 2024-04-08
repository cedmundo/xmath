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
  assert_true(QuatSameOrientation(q, e));
}

static void test_QuatMakeFromTo(void** state) {
  UNUSED(state);
}

static void test_QuatGetAxis(void** state) {
  UNUSED(state);
}

static void test_QuatGetAngle(void** state) {
  UNUSED(state);
}

static void test_QuatGetImgPart(void** state) {
  UNUSED(state);
}

static void test_QuatGetRealPart(void** state) {
  UNUSED(state);
}

static void test_QuatAdd(void** state) {
  UNUSED(state);
}

static void test_QuatSub(void** state) {
  UNUSED(state);
}

static void test_QuatScale(void** state) {
  UNUSED(state);
}

static void test_QuatNeg(void** state) {
  UNUSED(state);
}

static void test_QuatPow(void** state) {
  UNUSED(state);
}

static void test_QuatSameOrientation(void** state) {
  UNUSED(state);
}

static void test_QuatDot(void** state) {
  UNUSED(state);
}

static void test_QuatSqrLen(void** state) {
  UNUSED(state);
}

static void test_QuatLen(void** state) {
  UNUSED(state);
}

static void test_QuatNorm(void** state) {
  UNUSED(state);
}

static void test_QuatConjugate(void** state) {
  UNUSED(state);
}

static void test_QuatInvert(void** state) {
  UNUSED(state);
}

static void test_QuatMul(void** state) {
  UNUSED(state);
}

static void test_QuatTransformVec3(void** state) {
  UNUSED(state);
}

static void test_QuatMix(void** state) {
  UNUSED(state);
}

static void test_QuatNLerp(void** state) {
  UNUSED(state);
}

static void test_QuatSLerp(void** state) {
  UNUSED(state);
}

static void test_LookRotation(void** state) {
  UNUSED(state);
}

static void test_QuatToMat4(void** state) {
  UNUSED(state);
}

static void test_Mat4ToQuat(void** state) {
  UNUSED(state);
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
      cmocka_unit_test(test_QuatGetAxis),
      cmocka_unit_test(test_QuatGetAngle),
      cmocka_unit_test(test_QuatGetImgPart),
      cmocka_unit_test(test_QuatGetRealPart),
      cmocka_unit_test(test_QuatAdd),
      cmocka_unit_test(test_QuatSub),
      cmocka_unit_test(test_QuatScale),
      cmocka_unit_test(test_QuatNeg),
      cmocka_unit_test(test_QuatPow),
      cmocka_unit_test(test_QuatSameOrientation),
      cmocka_unit_test(test_QuatDot),
      cmocka_unit_test(test_QuatSqrLen),
      cmocka_unit_test(test_QuatLen),
      cmocka_unit_test(test_QuatNorm),
      cmocka_unit_test(test_QuatConjugate),
      cmocka_unit_test(test_QuatInvert),
      cmocka_unit_test(test_QuatMul),
      cmocka_unit_test(test_QuatTransformVec3),
      cmocka_unit_test(test_QuatMix),
      cmocka_unit_test(test_QuatNLerp),
      cmocka_unit_test(test_QuatSLerp),
      cmocka_unit_test(test_LookRotation),
      cmocka_unit_test(test_QuatToMat4),
      cmocka_unit_test(test_Mat4ToQuat),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
