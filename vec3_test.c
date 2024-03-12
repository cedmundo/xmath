// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "common_testing.h"
#include "vec3.h"
#include "scalar.h"

static void test_Vec3Constants(void **state) {
  UNUSED(state);

  Vec3 zeroes = { 0.0f,0.0f, 0.0f};
  assert_true(Vec3EqualApprox(zeroes, Vec3Zero));

  Vec3 ones = {1.0f, 1.0f, 1.0f};
  assert_true(Vec3EqualApprox(ones, Vec3One));
}

static void test_Vec3Floats(void **state) {
  UNUSED(state);

  Vec3 value = {1.0f, 2.0f, 3.0f};
  float expected[] = { 1.0f, 2.0f, 3.0f };
  float *result = Vec3Floats(&value);
  assert_memory_equal(expected, result, sizeof(float) * 3);

  result[2] = 4.0f;
  assert_memory_not_equal(expected, result, sizeof(float) * 3);

  value.z = 3.0f;
  assert_memory_equal(expected, result, sizeof(float) * 3);
}

static void test_Vec3Add(void **state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  Vec3 e;
  Vec3 r;

  a = (Vec3){1.0f, 2.0f, 3.0f};
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = (Vec3){4.0f, 4.0f, 4.0f};
  r = Vec3Add(a, b);
  assert_true(Vec3EqualApprox(e, r));

  a = (Vec3){1.0f, 2.0f, 3.0f};
  b = (Vec3){-3.0f, -2.0f, -1.0f};
  e = (Vec3){-2.0f, 0.0f, 2.0f};
  r = Vec3Add(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Sub(void **state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  Vec3 e;
  Vec3 r;

  a = (Vec3){1.0f, 2.0f, 3.0f};
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = (Vec3){-2.0f, 0.0f, 2.0f};
  r = Vec3Sub(a, b);
  assert_true(Vec3EqualApprox(e, r));

  a = (Vec3){1.0f, 2.0f, 3.0f};
  b = (Vec3){-3.0f, -2.0f, -1.0f};
  e = (Vec3){4.0f, 4.0f, 4.0f};
  r = Vec3Sub(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Scale(void **state) {
  UNUSED(state);

  Vec3 v;
  float s;
  Vec3 e;
  Vec3 r;

  v = (Vec3) {2.0f, 2.0f, 2.0f};
  s = 2.0f;
  e = (Vec3) {4.0f, 4.0f, 4.0f};
  r = Vec3Scale(v, s);
  assert_true(Vec3EqualApprox(e, r));

  v = (Vec3) {2.0f, 2.0f, 2.0f};
  s = -2.0f;
  e = (Vec3) {-4.0f, -4.0f, -4.0f};
  r = Vec3Scale(v, s);
  assert_true(Vec3EqualApprox(e, r));

  v = (Vec3) {2.0f, 2.0f, 2.0f};
  s = 0.0f;
  e = (Vec3) {0.0f, 0.0f, 0.0f};
  r = Vec3Scale(v, s);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3SqrLen(void **state) {
  UNUSED(state);

  Vec3 v;
  float e;
  float r;

  v = (Vec3) { 1.0f, 2.0f, 3.0f };
  e = 14.0f;
  r = Vec3SqrLen(v);
  assert_true(FEqualApprox(e, r));

  v = (Vec3) { 0.0f, 0.0f, 0.0f };
  e = 0.0f;
  r = Vec3SqrLen(v);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec3Len(void **state) {
  UNUSED(state);

  Vec3 v;
  float e;
  float r;

  v = (Vec3) { 1.0f, 2.0f, 3.0f };
  e = 3.7416573f;
  r = Vec3Len(v);
  assert_true(FEqualApprox(e, r));

  v = (Vec3) { 0.0f, 0.0f, 0.0f };
  e = 0.0f;
  r = Vec3Len(v);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec3Norm(void **state) {
  UNUSED(state);

  Vec3 v;
  Vec3 e;
  Vec3 r;

  v = (Vec3) {2.0f, 3.0f, 4.0f};
  e = (Vec3) {0.371391f, 0.557086f, 0.742781f};
  r = Vec3Norm(v);
  assert_true(Vec3EqualApprox(e, r));

  v = (Vec3) {0.0f, 0.0f, 0.0f};
  e = (Vec3) {0.0f, 0.0f, 0.0f};
  r = Vec3Norm(v);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Max(void** state) {
  UNUSED(state);

  Vec3 a = (Vec3) { 1.0f, 2.0f, 3.0f };
  Vec3 b = (Vec3) { 2.0f, 1.0f, 0.0f };
  Vec3 e = (Vec3) { 2.0f, 2.0f, 3.0f };
  Vec3 r = Vec3Max(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Min(void** state) {
  UNUSED(state);

  Vec3 a = (Vec3) { 1.0f, 2.0f, 3.0f };
  Vec3 b = (Vec3) { 2.0f, 1.0f, 0.0f };
  Vec3 e = (Vec3) { 1.0f, 1.0f, 0.0f };
  Vec3 r = Vec3Min(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Angle(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  float e;
  float r;

  a = (Vec3) {1.0f, 2.0f, 3.0f};
  b = (Vec3) {3.0f, 2.0f, 1.0f};
  e = 0.775193f;
  r = Vec3Angle(a, b);
  assert_true(FEqualApprox(e, r));

  a = (Vec3) {-1.0f, -1.0f, -1.0f};
  b = (Vec3) {1.0f, 1.0f, 1.0f};
  e = XMATH_PI;
  r = Vec3Angle(a, b);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec3Dot(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  float e;
  float r;

  a = Vec3Up;
  b = Vec3Down;
  e = -1.0f;
  r = Vec3Dot(a, b);
  assert_true(FEqualApprox(e, r));

  a = Vec3Up;
  b = Vec3Left;
  e = 0.0f;
  r = Vec3Dot(a, b);
  assert_true(FEqualApprox(e, r));

  a = (Vec3){1.0f, 1.0f, 1.0f};
  b = (Vec3){-1.0f, 2.0f, 3.0f};
  e = 4.0f;
  r = Vec3Dot(a, b);
  assert_true(FEqualApprox(e, r));
}

int main() {
  UNUSED_TYPE(jmp_buf);
  UNUSED_TYPE(va_list);
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_Vec3Constants),
      cmocka_unit_test(test_Vec3Floats),
      cmocka_unit_test(test_Vec3Add),
      cmocka_unit_test(test_Vec3Sub),
      cmocka_unit_test(test_Vec3Scale),
      cmocka_unit_test(test_Vec3SqrLen),
      cmocka_unit_test(test_Vec3Len),
      cmocka_unit_test(test_Vec3Norm),
      cmocka_unit_test(test_Vec3Max),
      cmocka_unit_test(test_Vec3Min),
      cmocka_unit_test(test_Vec3Angle),
      cmocka_unit_test(test_Vec3Dot),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
