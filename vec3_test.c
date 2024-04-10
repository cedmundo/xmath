// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "vec3.h"
#include "common_testing.h"
#include "scalar.h"

static void test_Vec3Constants(void** state) {
  UNUSED(state);

  Vec3 zeroes = {0.0f, 0.0f, 0.0f};
  assert_true(Vec3EqualApprox(zeroes, Vec3Zero));

  Vec3 ones = {1.0f, 1.0f, 1.0f};
  assert_true(Vec3EqualApprox(ones, Vec3One));
}

static void test_Vec3Floats(void** state) {
  UNUSED(state);

  Vec3 value = {1.0f, 2.0f, 3.0f};
  float expected[] = {1.0f, 2.0f, 3.0f};
  float* result = Vec3Floats(&value);
  assert_memory_equal(expected, result, sizeof(float) * 3);

  result[2] = 4.0f;
  assert_memory_not_equal(expected, result, sizeof(float) * 3);

  value.z = 3.0f;
  assert_memory_equal(expected, result, sizeof(float) * 3);
}

static void test_Vec3Add(void** state) {
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

static void test_Vec3Sub(void** state) {
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

static void test_Vec3Scale(void** state) {
  UNUSED(state);

  Vec3 v;
  float s;
  Vec3 e;
  Vec3 r;

  v = (Vec3){2.0f, 2.0f, 2.0f};
  s = 2.0f;
  e = (Vec3){4.0f, 4.0f, 4.0f};
  r = Vec3Scale(v, s);
  assert_true(Vec3EqualApprox(e, r));

  v = (Vec3){2.0f, 2.0f, 2.0f};
  s = -2.0f;
  e = (Vec3){-4.0f, -4.0f, -4.0f};
  r = Vec3Scale(v, s);
  assert_true(Vec3EqualApprox(e, r));

  v = (Vec3){2.0f, 2.0f, 2.0f};
  s = 0.0f;
  e = (Vec3){0.0f, 0.0f, 0.0f};
  r = Vec3Scale(v, s);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3SqrLen(void** state) {
  UNUSED(state);

  Vec3 v;
  float e;
  float r;

  v = (Vec3){1.0f, 2.0f, 3.0f};
  e = 14.0f;
  r = Vec3SqrLen(v);
  assert_true(FEqualApprox(e, r));

  v = (Vec3){0.0f, 0.0f, 0.0f};
  e = 0.0f;
  r = Vec3SqrLen(v);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec3Len(void** state) {
  UNUSED(state);

  Vec3 v;
  float e;
  float r;

  v = (Vec3){1.0f, 2.0f, 3.0f};
  e = 3.7416573f;
  r = Vec3Len(v);
  assert_true(FEqualApprox(e, r));

  v = (Vec3){0.0f, 0.0f, 0.0f};
  e = 0.0f;
  r = Vec3Len(v);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec3Norm(void** state) {
  UNUSED(state);

  Vec3 v;
  Vec3 e;
  Vec3 r;

  v = (Vec3){2.0f, 3.0f, 4.0f};
  e = (Vec3){0.371391f, 0.557086f, 0.742781f};
  r = Vec3Norm(v);
  assert_true(Vec3EqualApprox(e, r));

  v = (Vec3){0.0f, 0.0f, 0.0f};
  e = (Vec3){0.0f, 0.0f, 0.0f};
  r = Vec3Norm(v);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Orthonormalize(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  Vec3 e;
  Vec3 r;

  a = (Vec3){5.0f, -1.0f, 3.0f};
  b = (Vec3){2.0f, 3.0f, 4.0f};
  e = (Vec3){-0.333657f, -0.586427f, -0.73809f};
  r = Vec3Orthonormalize(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Max(void** state) {
  UNUSED(state);

  Vec3 a = (Vec3){1.0f, 2.0f, 3.0f};
  Vec3 b = (Vec3){2.0f, 1.0f, 0.0f};
  Vec3 e = (Vec3){2.0f, 2.0f, 3.0f};
  Vec3 r = Vec3Max(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Min(void** state) {
  UNUSED(state);

  Vec3 a = (Vec3){1.0f, 2.0f, 3.0f};
  Vec3 b = (Vec3){2.0f, 1.0f, 0.0f};
  Vec3 e = (Vec3){1.0f, 1.0f, 0.0f};
  Vec3 r = Vec3Min(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Angle(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  float e;
  float r;

  a = (Vec3){1.0f, 2.0f, 3.0f};
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = 0.775193f;
  r = Vec3Angle(a, b);
  assert_true(FEqualApprox(e, r));

  a = (Vec3){-1.0f, -1.0f, -1.0f};
  b = (Vec3){1.0f, 1.0f, 1.0f};
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

static void test_Vec3Cross(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  Vec3 e;
  Vec3 r;

  a = (Vec3){1.0f, 2.0f, 3.0f};
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = (Vec3){-4.0f, 8.0f, -4.0f};
  r = Vec3Cross(a, b);
  assert_true(Vec3EqualApprox(e, r));

  a = Vec3Up;
  b = Vec3Forward;
  e = Vec3Left;
  r = Vec3Cross(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Project(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  Vec3 e;
  Vec3 r;

  a = (Vec3){1.0f, 2.0f, 3.0f};
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = (Vec3){2.14285707f, 1.42857146f, 0.714285731f};
  r = Vec3Project(a, b);
  assert_true(Vec3EqualApprox(e, r));

  a = Vec3Zero;
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = Vec3Zero;
  r = Vec3Project(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Reject(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  Vec3 e;
  Vec3 r;

  a = (Vec3){1.0f, 2.0f, 3.0f};
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = (Vec3){-1.14285707f, 0.571428537f, 2.28571415f};
  r = Vec3Reject(a, b);
  assert_true(Vec3EqualApprox(e, r));

  a = Vec3Zero;
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = Vec3Zero;
  r = Vec3Reject(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Reflect(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  Vec3 e;
  Vec3 r;

  a = (Vec3){1.0f, 2.0f, 3.0f};
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = (Vec3){-3.28571428f, -0.85714285f, 1.57142857f};
  r = Vec3Reflect(a, b);
  assert_true(Vec3EqualApprox(e, r));

  a = Vec3Zero;
  b = (Vec3){3.0f, 2.0f, 1.0f};
  e = Vec3Zero;
  r = Vec3Reflect(a, b);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Lerp(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  float c;
  Vec3 e;
  Vec3 r;

  a = (Vec3){0.0f, 0.0f, 0.0f};
  b = (Vec3){10.0f, 10.0f, 10.0f};
  c = 0.5f;
  e = (Vec3){5.0f, 5.0f, 5.0f};
  r = Vec3Lerp(a, b, c);
  assert_true(Vec3EqualApprox(e, r));

  a = (Vec3){0.0f, 0.0f, 0.0f};
  b = (Vec3){10.0f, 10.0f, 10.0f};
  c = 0.0f;
  e = a;
  r = Vec3Lerp(a, b, c);
  assert_true(Vec3EqualApprox(e, r));

  a = (Vec3){0.0f, 0.0f, 0.0f};
  b = (Vec3){10.0f, 10.0f, 10.0f};
  c = 1.0f;
  e = b;
  r = Vec3Lerp(a, b, c);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Slerp(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  float c;
  Vec3 e;
  Vec3 r;

  a = (Vec3){1.0f, 0.0f, 0.0f};
  b = (Vec3){0.0f, 1.0f, 0.0f};
  c = 0.5f;
  e = (Vec3){0.707106769f, 0.707106769f, 0.0f};
  r = Vec3Slerp(a, b, c);
  assert_true(Vec3EqualApprox(e, r));

  a = (Vec3){0.0f, 0.0f, 0.0f};
  b = (Vec3){10.0f, 10.0f, 10.0f};
  c = 0.0f;
  e = a;
  r = Vec3Slerp(a, b, c);
  assert_true(Vec3EqualApprox(e, r));

  a = (Vec3){1.0f, 0.0f, 0.0f};
  b = (Vec3){0.0f, 1.0f, 0.0f};
  c = 1.0f;
  e = b;
  r = Vec3Slerp(a, b, c);
  assert_true(Vec3EqualApprox(e, r));
}

static void test_Vec3Nlerp(void** state) {
  UNUSED(state);

  Vec3 a;
  Vec3 b;
  float c;
  Vec3 e;
  Vec3 r;

  a = (Vec3){0.0f, 0.0f, 0.0f};
  b = (Vec3){1.0f, 1.0f, 1.0f};
  c = 0.5f;
  e = (Vec3){0.57735f, 0.57735f, 0.57735f};
  r = Vec3Nlerp(a, b, c);
  assert_true(Vec3EqualApprox(e, r));

  a = (Vec3){0.0f, 0.0f, 0.0f};
  b = (Vec3){1.0f, 1.0f, 1.0f};
  c = 0.0f;
  e = a;
  r = Vec3Nlerp(a, b, c);
  assert_true(Vec3EqualApprox(e, r));

  a = (Vec3){1.0f, 0.0f, 0.0f};
  b = (Vec3){0.0f, 1.0f, 0.0f};
  c = 1.0f;
  e = b;
  r = Vec3Nlerp(a, b, c);
  assert_true(Vec3EqualApprox(e, r));
}

int main() {
  UNUSED_TYPE(jmp_buf);
  UNUSED_TYPE(va_list);
  // clang-format off
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_Vec3Constants),
      cmocka_unit_test(test_Vec3Floats),
      cmocka_unit_test(test_Vec3Add),
      cmocka_unit_test(test_Vec3Sub),
      cmocka_unit_test(test_Vec3Scale),
      cmocka_unit_test(test_Vec3SqrLen),
      cmocka_unit_test(test_Vec3Len),
      cmocka_unit_test(test_Vec3Norm),
      cmocka_unit_test(test_Vec3Orthonormalize),
      cmocka_unit_test(test_Vec3Max),
      cmocka_unit_test(test_Vec3Min),
      cmocka_unit_test(test_Vec3Angle),
      cmocka_unit_test(test_Vec3Dot),
      cmocka_unit_test(test_Vec3Cross),
      cmocka_unit_test(test_Vec3Project),
      cmocka_unit_test(test_Vec3Reject),
      cmocka_unit_test(test_Vec3Reflect),
      cmocka_unit_test(test_Vec3Lerp),
      cmocka_unit_test(test_Vec3Slerp),
      cmocka_unit_test(test_Vec3Nlerp),
  };
  // clang-format on

  return cmocka_run_group_tests(tests, NULL, NULL);
}
