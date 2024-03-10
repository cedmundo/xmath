// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "scalar.h"

static void test_fequalapprox(void** state) {
  (void)state;

  assert_true(FEqualApprox(1.0f, 1.0f));
  assert_true(FEqualApprox(1.0f, 1.00000001f));
  assert_true(FEqualApprox(0.9999999f, 1.0f));
}

int main() {
  (void)(jmp_buf*)0;
  (void)(va_list*)0;
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fequalapprox),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
