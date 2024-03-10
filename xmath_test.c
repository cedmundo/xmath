// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static void test_dummy(void **state) {
  (void)state;
  assert_int_equal(0, 0);
}

int main() {
  (void)(jmp_buf *)0;
  (void)(va_list *)0;
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_dummy),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
