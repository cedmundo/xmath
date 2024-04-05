// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "common_testing.h"

#include "mat4.h"
#include "scalar.h"

#include <math.h>

static void test_Mat4Constants(void** state) {
  UNUSED(state);

  Mat4 zeroes = {
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
  };
  assert_true(Mat4EqualApprox(zeroes, Mat4Zero));

  Mat4 ones = {
      1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
  };
  assert_true(Mat4EqualApprox(ones, Mat4Identity));
}

static void test_Mat4ColRow(void** state) {
  UNUSED(state);

  Mat4 m = Mat4Identity;

  Vec4 expectedRow = {0.0f, 1.0f, 0.0f, 0.0f};
  Vec4 secondRow = Mat4Row(m, 1);
  assert_true(Vec4EqualApprox(expectedRow, secondRow));

  Vec4 expectedCol = {0.0f, 1.0f, 0.0f, 0.0f};
  Vec4 secondCol = Mat4Row(m, 1);
  assert_true(Vec4EqualApprox(expectedCol, secondCol));
}

static void test_Mat4Transpose(void** state) {
  UNUSED(state);

  Mat4 m = Mat4Identity;
  Mat4 t0 = Mat4Transpose(m);
  assert_true(Mat4EqualApprox(t0, Mat4Identity));

  Mat4 o = m;
  o.xy = 1.0f;
  o.xz = 1.0f;
  o.xw = 1.0f;

  Mat4 t1 = Mat4Transpose(o);
  Mat4 expected = {
      1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  assert_true(Mat4EqualApprox(t1, expected));
}

static void test_Mat4Add(void** state) {
  UNUSED(state);

  Mat4 a = {
      1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };

  Mat4 b = {
      0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
  };

  Mat4 e = {
      1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  };

  Mat4 r = Mat4Add(a, b);
  assert_true(Mat4EqualApprox(r, e));
}

static void test_Mat4Sub(void** state) {
  UNUSED(state);

  Mat4 a = {
      2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f,
      2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f,
  };

  Mat4 b = {
      1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  };

  Mat4 e = b;
  Mat4 r = Mat4Sub(a, b);
  assert_true(Mat4EqualApprox(r, e));
}

static void test_Mat4Scale(void** state) {
  UNUSED(state);

  Mat4 a = Mat4Identity;
  Mat4 e = {
      2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f,
  };

  Mat4 r = Mat4Scale(a, 2.0f);
  assert_true(Mat4EqualApprox(r, e));
}

static void test_Mat4Mul(void** state) {
  UNUSED(state);

  Mat4 a = Mat4Identity;
  Mat4 b = Mat4Identity;
  Mat4 e = Mat4Identity;

  Mat4 r = Mat4Mul(a, b);
  assert_true(Mat4EqualApprox(r, e));

  // clang-format off
  a = (Mat4){
    1.0f, 2.0f, 3.0f, 4.0f,
    4.0f, 3.0f, 2.0f, 1.0f,
    1.0f, 2.0f, 3.0f, 4.0f,
    4.0f, 3.0f, 2.0f, 1.0f,
  };

  b = (Mat4){
    4.0f, 3.0f, 2.0f, 1.0f,
    1.0f, 2.0f, 3.0f, 4.0f,
    4.0f, 3.0f, 2.0f, 1.0f,
    1.0f, 2.0f, 3.0f, 4.0f,
  };

  e = (Mat4) {
    22.0f, 24.0f, 26.0f, 28.0f,
    28.0f, 26.0f, 24.0f, 22.0f,
    22.0f, 24.0f, 26.0f, 28.0f,
    28.0f, 26.0f, 24.0f, 22.0f,
  };
  // clang-format on

  r = Mat4Mul(a, b);
  assert_true(Mat4EqualApprox(r, e));
}

static void test_Mat4MulVec4(void** state) {
  UNUSED(state);

  Mat4 a = Mat4Identity;
  Vec4 b = Vec4One;
  Vec4 e = Vec4One;

  Vec4 r = Mat4MulVec4(a, b);
  assert_true(Vec4EqualApprox(r, e));

  // clang-format off
  a = (Mat4){
    1.0f, 0.0f, 0.0f, 2.0f,
    0.0f, 1.0f, 0.0f, 2.0f,
    0.0f, 0.0f, 1.0f, 2.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  };
  // clang-format on

  b = (Vec4){0.0f, 0.0f, 0.0f, 1.0f};
  e = (Vec4){2.0f, 2.0f, 2.0f, 1.0f};

  r = Mat4MulVec4(a, b);
  assert_true(Vec4EqualApprox(r, e));
}

static void test_Mat4MakeOrtho(void** state) {
  UNUSED(state);

  // clang-format off
  Mat4 e = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, -0.0200200193f, 0.0f,
    0.0f, 0.0f, -1.002002f, 1.0f,
  };
  // clang-format on

  Mat4 r = Mat4MakeOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
  assert_true(Mat4EqualApprox(r, e));
}

static void test_Mat4MakePerspective(void** state) {
  UNUSED(state);

  float e = 1.000000195f;
  float zz = -1.002002f;
  float zw = -0.2002002f;

  // clang-format off
  Mat4 expected = {
    e, 0.0f, 0.0f, 0.0f,
    0.0f, e, 0.0f, 0.0f,
    0.0f, 0.0f, zz, -1.0f,
    0.0f, 0.0f, zw, 0.0f,
  };
  // clang-format on

  Mat4 r = Mat4MakePerspective(90.0f, 1.0f, 0.1f, 100.0f);
  assert_true(Mat4EqualApprox(r, expected));
}

static void test_Mat4LookAt(void** state) {
  UNUSED(state);

  // clang-format off
  Mat4 expected = {
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
  };
  // clang-format on

  Vec3 p = {-1.0f, 0.0f, 0.0f};
  Vec3 t = Vec3Zero;
  Vec3 u = Vec3Up;

  Mat4 r = Mat4LookAt(p, t, u);
  assert_true(Mat4EqualApprox(r, expected));
}

int main() {
  UNUSED_TYPE(jmp_buf);
  UNUSED_TYPE(va_list);
  // clang-format off
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_Mat4Constants),
      cmocka_unit_test(test_Mat4ColRow),
      cmocka_unit_test(test_Mat4Transpose),
      cmocka_unit_test(test_Mat4Add),
      cmocka_unit_test(test_Mat4Sub),
      cmocka_unit_test(test_Mat4Scale),
      cmocka_unit_test(test_Mat4Mul),
      cmocka_unit_test(test_Mat4MulVec4),
      cmocka_unit_test(test_Mat4MakeOrtho),
      cmocka_unit_test(test_Mat4MakePerspective),
      cmocka_unit_test(test_Mat4LookAt),
  };
  // clang-format on

  return cmocka_run_group_tests(tests, NULL, NULL);
}
