// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "transform.h"
#include "common_testing.h"

static void test_Dummy(void** state) {
  UNUSED(state);
  assert_true(1);
}

void test_TransformCombine(void** state) {
  UNUSED(state);
}

void test_TransformInverse(void** state) {
  UNUSED(state);
}

void test_TransformLerp(void** state) {
  UNUSED(state);
}

void test_TransformToMat4(void** state) {
  UNUSED(state);
}

void test_Mat4ToTransform(void** state) {
  UNUSED(state);
}

void test_TransformPoint(void** state) {
  UNUSED(state);
}

void test_TransformVec3(void** state) {
  UNUSED(state);
}

int main() {
  UNUSED_TYPE(jmp_buf);
  UNUSED_TYPE(va_list);

  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_Dummy),
      cmocka_unit_test(test_TransformCombine),
      cmocka_unit_test(test_TransformInverse),
      cmocka_unit_test(test_TransformLerp),
      cmocka_unit_test(test_TransformToMat4),
      cmocka_unit_test(test_Mat4ToTransform),
      cmocka_unit_test(test_TransformPoint),
      cmocka_unit_test(test_TransformVec3),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
