// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on


#include "common_testing.h"
#include "scalar.h"
#include "vec2.h"

static void test_Vec2Constants(void** state) {
  UNUSED(state);

  assert_float_equal(Vec2Zero.x, 0.0f, XMATH_EPSILON);
  assert_float_equal(Vec2Zero.y, 0.0f, XMATH_EPSILON);
  assert_float_equal(Vec2One.x, 1.0f, XMATH_EPSILON);
  assert_float_equal(Vec2One.y, 1.0f, XMATH_EPSILON);
}

static void test_Vec2Floats(void** state) {
  UNUSED(state);

  Vec2 value = {1.0f, 2.0f};
  float expected[] = { 1.0f, 2.0f };
  float *result = Vec2Floats(&value);
  assert_memory_equal(expected, result, sizeof(float) * 2);

  result[1] = 3.0f;
  assert_memory_not_equal(expected, result, sizeof(float) * 2);

  value.y = 2.0f;
  assert_memory_equal(expected, result, sizeof(float) * 2);
}

static void test_Vec2Add(void** state) {
  UNUSED(state);

  Vec2 first;
  Vec2 second;
  Vec2 expected;
  Vec2 result;

  first = (Vec2){ 1.0f, 1.0f };
  second = (Vec2){ 2.0f, 3.0f };
  expected = (Vec2) { 3.0f, 4.0f };
  result = Vec2Add(first, second);
  assert_true(Vec2EqualApprox(expected, result));

  first = (Vec2){ 2.0f, 2.0f };
  second = (Vec2){ -1.0f, -2.0f };
  expected = (Vec2) { 1.0f, 0.0f };
  result = Vec2Add(first, second);
  assert_true(Vec2EqualApprox(expected, result));
}

static void test_Vec2Sub(void** state) {
  UNUSED(state);

  Vec2 first;
  Vec2 second;
  Vec2 expected;
  Vec2 result;

  first = (Vec2){ 2.0f, 3.0f };
  second = (Vec2){ 1.0f, 1.0f };
  expected = (Vec2) { 1.0f, 2.0f };
  result = Vec2Sub(first, second);
  assert_true(Vec2EqualApprox(expected, result));

  first = (Vec2){ 2.0f, 2.0f };
  second = (Vec2){ -1.0f, -2.0f };
  expected = (Vec2) { 3.0f, 4.0f };
  result = Vec2Sub(first, second);
  assert_true(Vec2EqualApprox(expected, result));
}

static void test_Vec2Scale(void** state) {
  UNUSED(state);

  Vec2 v;
  float s;
  Vec2 expected;
  Vec2 result;

  v = (Vec2) { 2.0f, 2.0f };
  s = 2.0f;
  expected = (Vec2) { 4.0f, 4.0f };
  result = Vec2Scale(v, s);
  assert_true(Vec2EqualApprox(expected, result));

  v = (Vec2) { 2.0f, 2.0f };
  s = 0.5f;
  expected = (Vec2) { 1.0f, 1.0f };
  result = Vec2Scale(v, s);
  assert_true(Vec2EqualApprox(expected, result));

  v = (Vec2) { 2.0f, 2.0f };
  s = -1.0f;
  expected = (Vec2) { -2.0f, -2.0f };
  result = Vec2Scale(v, s);
  assert_true(Vec2EqualApprox(expected, result));
}

static void test_Vec2SqrLen(void** state) {
  UNUSED(state);

  Vec2 v = (Vec2) { 2.0f, 2.0f };
  float e = 8.0f;
  float r = Vec2SqrLen(v);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec2Len(void** state) {
  UNUSED(state);

  Vec2 v = (Vec2) { 2.0f, 2.0f };
  float e = 2.828427125f;
  float r = Vec2Len(v);
  assert_true(FEqualApprox(e, r));
}

static void test_Vec2Norm(void** state) {
  UNUSED(state);

  Vec2 v = (Vec2){ 2.0f, 2.0f };
  Vec2 e = (Vec2) { 0.707106781f, 0.707106781f };
  Vec2 r = Vec2Norm(v);
  assert_true(Vec2EqualApprox(e, r));
  assert_true(FEqualApprox(Vec2Len(e), 1.0f));
}

static void test_Vec2Max(void** state) {
  UNUSED(state);

  Vec2 a = (Vec2) { 1.0f, 2.0f };
  Vec2 b = (Vec2) { 2.0f, 1.0f };
  Vec2 e = (Vec2) { 2.0f, 2.0f };
  Vec2 r = Vec2Max(a, b);
  assert_true(Vec2EqualApprox(e, r));
}

static void test_Vec2Min(void** state) {
  UNUSED(state);

  Vec2 a = (Vec2) { 1.0f, 2.0f };
  Vec2 b = (Vec2) { 2.0f, 1.0f };
  Vec2 e = (Vec2) { 1.0f, 1.0f };
  Vec2 r = Vec2Min(a, b);
  assert_true(Vec2EqualApprox(e, r));
}

int main() {
  UNUSED_TYPE(jmp_buf);
  UNUSED_TYPE(va_list);

  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_Vec2Floats),
      cmocka_unit_test(test_Vec2Constants),
      cmocka_unit_test(test_Vec2Add),
      cmocka_unit_test(test_Vec2Sub),
      cmocka_unit_test(test_Vec2Scale),
      cmocka_unit_test(test_Vec2SqrLen),
      cmocka_unit_test(test_Vec2Len),
      cmocka_unit_test(test_Vec2Norm),
      cmocka_unit_test(test_Vec2Max),
      cmocka_unit_test(test_Vec2Min),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
