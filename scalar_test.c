// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "scalar.h"

static void test_FEqualApprox(void** state) {
  (void)state;

  assert_true(FEqualApprox(1.0f, 1.0f));
  assert_true(FEqualApprox(1.0f, 1.00000001f));
  assert_true(FEqualApprox(0.999999999f, 1.0f));
}

static void test_FMaxFMin(void **state) {
  (void)state;

  assert_float_equal(FMax(1.0f, 0.0f), 1.0f, XMATH_EPSILON);
  assert_float_equal(FMax(1.0f, -1.0f), 1.0f, XMATH_EPSILON);
  assert_float_equal(FMax(-2.0f, -1.0f), -1.0f, XMATH_EPSILON);

  assert_float_equal(FMin(1.0f, 0.0f), 0.0f, XMATH_EPSILON);
  assert_float_equal(FMin(1.0f, -1.0f), -1.0f, XMATH_EPSILON);
  assert_float_equal(FMin(-2.0f, -1.0f), -2.0f, XMATH_EPSILON);
}

static void test_FLerpLRemap(void **state) {
  (void)state;

  assert_float_equal(FLerp(0.0f, 10.0f, 0.5f), 5.0f, XMATH_EPSILON);
  assert_float_equal(FLerp(0.0f, 10.0f, 0.25f), 2.5f, XMATH_EPSILON);
  assert_float_equal(FRemap(5.0f, 0.0, 10.0f, 0.0f, 100.0f), 45.0f, XMATH_EPSILON);
}

static void test_FDegRad(void **state) {
  (void)state;

  assert_float_equal(FDeg2Rad(0.0f), 0.0f, XMATH_EPSILON);
  assert_float_equal(FDeg2Rad(90.0f), 1.570796f, XMATH_EPSILON);
  assert_float_equal(FDeg2Rad(180.0f), XMATH_PI, XMATH_EPSILON);

  assert_float_equal(FRad2Deg(0.0f), 0.0f, XMATH_EPSILON);
  assert_float_equal(FRad2Deg(2.0f), 114.591560f, XMATH_EPSILON);
  assert_float_equal(FRad2Deg(XMATH_PI), 180.0f, XMATH_EPSILON);
}

int main() {
  (void)(jmp_buf*)0;
  (void)(va_list*)0;

  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_FEqualApprox),
      cmocka_unit_test(test_FMaxFMin),
      cmocka_unit_test(test_FLerpLRemap),
      cmocka_unit_test(test_FDegRad),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
