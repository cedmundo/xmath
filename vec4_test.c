// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "vec4.h"
#include "common_testing.h"
#include "scalar.h"

static void test_Vec4Constants(void** state) {
  UNUSED(state);

  Vec4 zeroes = {0.0f, 0.0f, 0.0f, 0.0f};
  assert_true(Vec4EqualApprox(zeroes, Vec4Zero));

  Vec4 ones = {1.0f, 1.0f, 1.0f, 1.0f};
  assert_true(Vec4EqualApprox(ones, Vec4One));
}

static void test_Vec4Floats(void** state) {
  UNUSED(state);

  Vec4 value = {1.0f, 2.0f, 3.0f, 4.0f};
  float expected[] = {1.0f, 2.0f, 3.0f, 4.0f};
  float* result = Vec4Floats(&value);
  assert_memory_equal(expected, result, sizeof(float) * 4);

  result[3] = 5.0f;
  assert_memory_not_equal(expected, result, sizeof(float) * 4);

  value.w = 4.0f;
  assert_memory_equal(expected, result, sizeof(float) * 4);
}

static void test_Vec4Add(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  Vec4 e;
  Vec4 r;

  a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = (Vec4){5.0f, 5.0f, 5.0f, 5.0f};
  r = Vec4Add(a, b);
  assert_true(Vec4EqualApprox(e, r));

  a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  b = (Vec4){-4.0f, -3.0f, -2.0f, -1.0f};
  e = (Vec4){-3.0f, -1.0f, 1.0f, 3.0f};
  r = Vec4Add(a, b);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Sub(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  Vec4 e;
  Vec4 r;

  a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = (Vec4){-3.0f, -1.0f, 1.0f, 3.0f};
  r = Vec4Sub(a, b);
  assert_true(Vec4EqualApprox(e, r));

  a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  b = (Vec4){-4.0f, -3.0f, -2.0f, -1.0f};
  e = (Vec4){5.0f, 5.0f, 5.0f, 5.0f};
  r = Vec4Sub(a, b);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Scale(void** state) {
  UNUSED(state);

  Vec4 v;
  float s;
  Vec4 e;
  Vec4 r;

  v = (Vec4){2.0f, 2.0f, 2.0f, 2.0f};
  s = 2.0f;
  e = (Vec4){4.0f, 4.0f, 4.0f, 4.0f};
  r = Vec4Scale(v, s);
  assert_true(Vec4EqualApprox(e, r));

  v = (Vec4){2.0f, 2.0f, 2.0f, 2.0f};
  s = -2.0f;
  e = (Vec4){-4.0f, -4.0f, -4.0f, -4.0f};
  r = Vec4Scale(v, s);
  assert_true(Vec4EqualApprox(e, r));

  v = (Vec4){2.0f, 2.0f, 2.0f, 2.0f};
  s = 0.0f;
  e = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  r = Vec4Scale(v, s);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4SqrLen(void** state) {
  UNUSED(state);

  Vec4 v;
  float e;
  float r;

  v = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  e = 30.0f;
  r = Vec4SqrLen(v);
  assert_true(FEqualApprox(e, r));

  v = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  e = 0.0f;
  r = Vec4SqrLen(v);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec4Len(void** state) {
  UNUSED(state);

  Vec4 v;
  float e;
  float r;

  v = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  e = 5.477225575f;
  r = Vec4Len(v);
  assert_true(FEqualApprox(e, r));

  v = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  e = 0.0f;
  r = Vec4Len(v);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec4Norm(void** state) {
  UNUSED(state);

  Vec4 v;
  Vec4 e;
  Vec4 r;

  v = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  e = (Vec4){0.182574f, 0.365148f, 0.547723f, 0.730297f};
  r = Vec4Norm(v);
  assert_true(Vec4EqualApprox(e, r));

  v = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  e = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  r = Vec4Norm(v);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Max(void** state) {
  UNUSED(state);

  Vec4 a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  Vec4 b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  Vec4 e = (Vec4){4.0f, 3.0f, 3.0f, 4.0f};
  Vec4 r = Vec4Max(a, b);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Min(void** state) {
  UNUSED(state);

  Vec4 a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  Vec4 b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  Vec4 e = (Vec4){1.0f, 2.0f, 2.0f, 1.0f};
  Vec4 r = Vec4Min(a, b);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Angle(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  float e;
  float r;

  a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = 0.841069f;
  r = Vec4Angle(a, b);
  assert_true(FEqualApprox(e, r));

  a = (Vec4){-1.0f, -1.0f, -1.0f, -1.0f};
  b = (Vec4){1.0f, 1.0f, 1.0f, 1.0f};
  e = XMATH_PI;
  r = Vec4Angle(a, b);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec4Dot(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  float e;
  float r;

  a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = 20.0f;
  r = Vec4Dot(a, b);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec4Project(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  Vec4 e;
  Vec4 r;

  a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = (Vec4){2.66666675f, 2.0f, 1.33333337f, 0.666666687f};
  r = Vec4Project(a, b);
  assert_true(Vec4EqualApprox(e, r));

  a = Vec4Zero;
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = Vec4Zero;
  r = Vec4Project(a, b);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Reject(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  Vec4 e;
  Vec4 r;

  a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = (Vec4){-1.66666675f, 0.0f, 1.66666663f, 3.33333325f};
  r = Vec4Reject(a, b);
  assert_true(Vec4EqualApprox(e, r));

  a = Vec4Zero;
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = Vec4Zero;
  r = Vec4Reject(a, b);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Reflect(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  Vec4 e;
  Vec4 r;

  a = (Vec4){1.0f, 2.0f, 3.0f, 4.0f};
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = (Vec4){-4.33333302f, -2.0f, 0.333333492f, 2.66666675f};
  r = Vec4Reflect(a, b);
  assert_true(Vec4EqualApprox(e, r));

  a = Vec4Zero;
  b = (Vec4){4.0f, 3.0f, 2.0f, 1.0f};
  e = Vec4Zero;
  r = Vec4Reflect(a, b);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Lerp(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  float c;
  Vec4 e;
  Vec4 r;

  a = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  b = (Vec4){10.0f, 10.0f, 10.0f, 10.0f};
  c = 0.5f;
  e = (Vec4){5.0f, 5.0f, 5.0f, 5.0f};
  r = Vec4Lerp(a, b, c);
  assert_true(Vec4EqualApprox(e, r));

  a = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  b = (Vec4){10.0f, 10.0f, 10.0f, 0.0f};
  c = 0.0f;
  e = a;
  r = Vec4Lerp(a, b, c);
  assert_true(Vec4EqualApprox(e, r));

  a = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  b = (Vec4){10.0f, 10.0f, 10.0f, 10.0f};
  c = 1.0f;
  e = b;
  r = Vec4Lerp(a, b, c);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Slerp(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  float c;
  Vec4 e;
  Vec4 r;

  a = (Vec4){1.0f, 0.0f, 0.0f, 0.0f};
  b = (Vec4){0.0f, 1.0f, 0.0f, 0.0f};
  c = 0.5f;
  e = (Vec4){0.707106769f, 0.707106769f, 0.0f, 0.0f};
  r = Vec4Slerp(a, b, c);
  assert_true(Vec4EqualApprox(e, r));

  a = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  b = (Vec4){10.0f, 10.0f, 10.0f, 10.0f};
  c = 0.0f;
  e = a;
  r = Vec4Slerp(a, b, c);
  assert_true(Vec4EqualApprox(e, r));

  a = (Vec4){1.0f, 0.0f, 0.0f, 0.0f};
  b = (Vec4){0.0f, 1.0f, 0.0f, 0.0f};
  c = 1.0f;
  e = b;
  r = Vec4Slerp(a, b, c);
  assert_true(Vec4EqualApprox(e, r));
}

static void test_Vec4Nlerp(void** state) {
  UNUSED(state);

  Vec4 a;
  Vec4 b;
  float c;
  Vec4 e;
  Vec4 r;

  a = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  b = (Vec4){1.0f, 1.0f, 1.0f, 1.0f};
  c = 0.5f;
  e = (Vec4){0.5f, 0.5f, 0.5f, 0.5f};
  r = Vec4Nlerp(a, b, c);
  assert_true(Vec4EqualApprox(e, r));

  a = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  b = (Vec4){1.0f, 1.0f, 1.0f, 1.0f};
  c = 0.0f;
  e = a;
  r = Vec4Nlerp(a, b, c);
  assert_true(Vec4EqualApprox(e, r));

  a = (Vec4){0.0f, 0.0f, 0.0f, 0.0f};
  b = (Vec4){0.5f, 0.5f, 0.5f, 0.5f};
  c = 1.0f;
  e = b;
  r = Vec4Nlerp(a, b, c);
  assert_true(Vec4EqualApprox(e, r));
}

int main() {
  UNUSED_TYPE(jmp_buf);
  UNUSED_TYPE(va_list);
  // clang-format off
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_Vec4Constants),
      cmocka_unit_test(test_Vec4Floats),
      cmocka_unit_test(test_Vec4Add),
      cmocka_unit_test(test_Vec4Sub),
      cmocka_unit_test(test_Vec4Scale),
      cmocka_unit_test(test_Vec4SqrLen),
      cmocka_unit_test(test_Vec4Len),
      cmocka_unit_test(test_Vec4Norm),
      cmocka_unit_test(test_Vec4Max),
      cmocka_unit_test(test_Vec4Min),
      cmocka_unit_test(test_Vec4Angle),
      cmocka_unit_test(test_Vec4Dot),
      cmocka_unit_test(test_Vec4Project),
      cmocka_unit_test(test_Vec4Reject),
      cmocka_unit_test(test_Vec4Reflect),
      cmocka_unit_test(test_Vec4Lerp),
      cmocka_unit_test(test_Vec4Slerp),
      cmocka_unit_test(test_Vec4Nlerp),
  };
  // clang-format on

  return cmocka_run_group_tests(tests, NULL, NULL);
}
