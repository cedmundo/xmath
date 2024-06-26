// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include "transform.h"
#include "common_testing.h"
#include "scalar.h"

void test_TransformCombine(void** state) {
  UNUSED(state);

  // TODO(cedmundo): Verify with godot the results
  Transform a = {
      .position = {1.0f, 1.0f, 1.0f},
      .rotation = {0.23f, 0.31f, 0.79f, 0.47f},
      .scale = {2.0f, 2.0f, 2.0f},
  };

  Transform b = {
      .position = {1.0f, 3.0f, 1.0f},
      .rotation = {0.55f, 0.30f, 0.56f, 0.56f},
      .scale = {1.0f, 2.0f, 3.0f},
  };

  Transform e = {
      .position = {5.40480042f, -1.44639969f, 3.49600005f},
      .rotation = {0.3239f, 0.6203f, 0.6041f, -0.3987f},
      .scale = {2.0f, -4.0f, 2.0f},
  };

  Transform r = TransformCombine(a, b);
  assert_true(TransformEqualApprox(r, e));
}

void test_TransformInverse(void** state) {
  UNUSED(state);

  Transform a = {
      .position = {2.0f, 1.0f, 2.0f},
      .rotation = QuatMakeAngleAxis(FDeg2Rad(25.0f), Vec3Up),
      .scale = {2.0f, 2.0f, 2.0f},
  };

  Transform e = {
      .position = {-0.48369f, -0.5f, -1.328926f},
      .rotation = {0.0f, -0.21644f, 0.0f, 0.976296f},
      .scale = {0.5f, 0.5f, 0.5f},
  };

  Transform r = TransformInverse(a);
  assert_true(TransformEqualApprox(r, e));
}

void test_TransformLerp(void** state) {
  UNUSED(state);

  Transform a = {
      .position = {0.0f, 0.0f, 0.0f},
      .rotation = {0.23f, 0.31f, 0.79f, 0.47f},
      .scale = {1.0f, 1.0f, 1.0f},
  };

  Transform b = {
      .position = {2.0f, 2.0f, 2.0f},
      .rotation = {0.30f, 0.55f, 0.30f, 0.56f},
      .scale = {2.0f, 2.0f, 2.0f},
  };

  float c = 0.5f;

  Transform e = {
      .position = {1.0f, 1.0f, 1.0f},
      .rotation = {0.293113083f, 0.475617468f, 0.602817476f, 0.569634855f},
      .scale = {1.5f, 1.5f, 1.5f},
  };

  Transform r = TransformLerp(a, b, c);
  assert_true(TransformEqualApprox(r, e));
}

void test_TransformToMat4(void** state) {
  UNUSED(state);

  Transform t = {0};
  t.position = (Vec3){0.0f, 1.0f, 0.0f};
  t.rotation = QuatMakeAngleAxis(FDeg2Rad(45.0f), Vec3Up);
  t.scale = (Vec3){2.0f, 2.0f, 2.0f};

  // clang-format off
  Mat4 e = {
    1.41421378f, 0.0f, -1.41421342f, 0.0f,
    0.0f, 2.0f, 0.0f, 0.0f,
    1.41421342f, 0.0f, 1.41421378f, 0.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
  };
  // clang-format on

  Mat4 r = TransformToMat4(t);
  assert_true(Mat4EqualApprox(r, e));
}

void test_Mat4ToTransform(void** state) {
  UNUSED(state);

  // clang-format off
  Mat4 m = {
      0.390731f, 0.0f, -0.920505f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.920505f, 0.0f, 0.390731f, 0.0f,
      -1.0f, 3.0f, 4.0f, 1.0f,
  };
  // clang-format on

  Transform e = {
      .position = {-1.0f, 3.0f, 4.0f},
      .rotation = {0, 0.551937f, 0, 0.833886f},
      .scale = {1.0f, 1.0f, 1.0f}, // FIXME: Find out why scale is off
  };
  Transform r = Mat4ToTransform(m);
  assert_true(TransformEqualApprox(r, e));
}

void test_TransformPoint(void** state) {
  UNUSED(state);

  Transform a = {
      .position = {1.0f, 0.0f, 0.0f},
      .rotation = QuatMakeAngleAxis(FDeg2Rad(45.0f), Vec3Up),
      .scale = Vec3One,
  };
  Vec3 b = {0.2f, 0.2f, 0.4f};
  Vec3 e = {1.424264f, 0.2f, 0.141421f};
  Vec3 r = TransformPoint(a, b);
  assert_true(Vec3EqualApprox(r, e));
}

void test_TransformVec3(void** state) {
  UNUSED(state);
  Transform a = {
      .position = {1.0f, 0.0f, 0.0f},
      .rotation = QuatMakeAngleAxis(FDeg2Rad(45.0f), Vec3Up),
      .scale = Vec3One,
  };
  Vec3 b = {0.2f, 0.2f, 0.4f};
  Vec3 e = {0.424264f, 0.2f, 0.141421f};
  Vec3 r = TransformVec3(a, b);
  assert_true(Vec3EqualApprox(r, e));
}

int main() {
  UNUSED_TYPE(jmp_buf);
  UNUSED_TYPE(va_list);

  const struct CMUnitTest tests[] = {
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
