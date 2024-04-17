/**
 * @file transform.h
 * @brief Definitions, functions and utilities for transforms.
 */
#ifndef XMATH_TRANSFORM_H
#define XMATH_TRANSFORM_H
#include <stdbool.h>
#include "mat4.h"
#include "quat.h"
#include "vec3.h"

typedef struct {
  Vec3 position;
  Quat rotation;
  Vec3 scale;
} Transform;

/**
 * @brief Compare two transforms.
 * @param a first transform.
 * @param b second transform.
 * @return true if they are approximately equal.
 */
bool TransformEqualApprox(Transform a, Transform b);

/**
 * @brief Combine two transform in right-to-left order.
 * @param a combining transform.
 * @param b combined space transform.
 * @return a transform with a relative to b.
 */
Transform TransformCombine(Transform a, Transform b);

/**
 * @brief Get the inverse of a transform.
 * @param t transform to get inverse (unaffected).
 */
Transform TransformInverse(Transform t);

/**
 * @brief Linear interpolation between two transforms.
 * @param a source transform (unaffected).
 * @param b target transform (unaffected).
 * @param t factor of interpolation.
 * @return a transform on the way from a to b by t.
 */
Transform TransformLerp(Transform a, Transform b, float t);

/**
 * @brief Convert from a Transform into a Mat4.
 * @param t transform to convert (unaffected).
 * @return a matrix representing the affine transformations of t.
 */
Mat4 TransformToMat4(Transform t);

/**
 * @brief Convert a transform matrix back into a Transform.
 * @param m matrix to convert (unaffected).
 * @return a Transform with each component equivalent to m transformations.
 */
Transform Mat4ToTransform(Mat4 m);

/**
 * @brief Transform a point.
 * @param a transform to use as basis.
 * @param b Vec3 representing a point.
 * @return b point in Transform space.
 */
Vec3 TransformPoint(Transform a, Vec3 b);

/**
 * @brief Transform a vector (do not apply translation of a into b).
 * @param a transform to use as basis.
 * @param b Vec3 representing.
 * @return b vec3 in Transform space.
 */
Vec3 TransformVec3(Transform a, Vec3 b);

#endif /* XMATH_TRANSFORM_H */
