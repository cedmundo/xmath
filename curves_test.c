// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "curves.h"
#include "common_testing.h"

static void test_BeizerInterpolate(void** state) {
  UNUSED(state);
  float t;
  BeizerCurve c;
  Vec3 e;
  Vec3 r;

  c = (BeizerCurve){
      .p1 = {-4.0f, 0.0f, 0.0f},
      .c1 = {-4.0f, 4.0f, 0.0f},
      .p2 = {4.0f, 0.0f, 0.0f},
      .c2 = {4.0f, 4.0f, 0.0f},
  };
  t = 0.0f;
  e = (Vec3){-4.0f, 0.0f, 0.0f};
  r = BeizerInterpolate(c, t);
  assert_true(Vec3EqualApprox(r, e));

  c = (BeizerCurve){
      .p1 = {-4.0f, 0.0f, 0.0f},
      .c1 = {-4.0f, 4.0f, 0.0f},
      .p2 = {4.0f, 0.0f, 0.0f},
      .c2 = {4.0f, 4.0f, 0.0f},
  };
  t = 1.0f;
  e = (Vec3){4.0f, 0.0f, 0.0f};
  r = BeizerInterpolate(c, t);
  assert_true(Vec3EqualApprox(r, e));

  c = (BeizerCurve){
      .p1 = {-4.0f, 0.0f, 0.0f},
      .c1 = {-4.0f, 4.0f, 0.0f},
      .p2 = {4.0f, 0.0f, 0.0f},
      .c2 = {4.0f, 4.0f, 0.0f},
  };
  t = 0.5f;
  e = (Vec3){0.0f, 3.0f, 0.0f};
  r = BeizerInterpolate(c, t);
  assert_true(Vec3EqualApprox(r, e));
}

static void test_HermitInterpolate(void** state) {
  UNUSED(state);
  HermitCurve c;
  float t;
  Vec3 e;
  Vec3 r;

  c = (HermitCurve){
      .p1 = {-4.0f, 4.0f, 0.0f},
      .s1 = {0.0f, 4.0f, 0.0f},
      .p2 = {4.0f, 0.0f, 0.0f},
      .s2 = {6.0f, 0.0f, 0.0f},
  };
  t = 0.0f;
  e = (Vec3){-4.0f, 4.0f, 0.0f};
  r = HermitInterpolate(c, t);
  assert_true(Vec3EqualApprox(r, e));

  c = (HermitCurve){
      .p1 = {-4.0f, 4.0f, 0.0f},
      .s1 = {0.0f, 4.0f, 0.0f},
      .p2 = {4.0f, 0.0f, 0.0f},
      .s2 = {6.0f, 0.0f, 0.0f},
  };
  t = 1.0f;
  e = (Vec3){4.0f, 0.0f, 0.0f};
  r = HermitInterpolate(c, t);
  assert_true(Vec3EqualApprox(r, e));

  c = (HermitCurve){
      .p1 = {-4.0f, 4.0f, 0.0f},
      .s1 = {0.0f, 4.0f, 0.0f},
      .p2 = {4.0f, 0.0f, 0.0f},
      .s2 = {6.0f, 0.0f, 0.0f},
  };
  t = 0.5f;
  e = (Vec3){-0.75f, 2.5f, 0.0f};
  r = HermitInterpolate(c, t);
  assert_true(Vec3EqualApprox(r, e));
}

int main() {
  UNUSED_TYPE(jmp_buf);
  UNUSED_TYPE(va_list);

  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_BeizerInterpolate),
      cmocka_unit_test(test_HermitInterpolate),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
