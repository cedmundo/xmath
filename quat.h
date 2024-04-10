/**
 * @file quat.h
 * @brief Definitions, functions and utilities for quaternions.
 */
#ifndef XMATH_QUAT_H
#define XMATH_QUAT_H
#include <stdbool.h>

#include "mat4.h"
#include "vec3.h"
#include "vec4.h"

/**
 * @brief Quaternion defined by its four xyzw components.
 */
typedef struct {
  float x;
  float y;
  float z;
  float w;
} Quat;

//! @brief a Quaternion full of zeroes.
static const Quat QuatZero = {0.0f, 0.0f, 0.0f, 0.0f};

//! @brief a Quaternion equal to 1.
static const Quat QuatIdentity = {0.0f, 0.0f, 0.0f, 1.0f};

/**
 * @brief Get the consecutive floating values from a Quaternion.
 * @param quat reference to the quaternion data.
 * @return The address of first component.
 */
float* QuatFloats(Quat* quat);

/**
 * @brief Make a quaternion using angle and axis.
 * @param angle in radians.
 * @param axis rotation.
 * @return Quat with angle * axis rotation.
 */
Quat QuatMakeAngleAxis(float angle, Vec3 axis);

/**
 * @brief Make a quaternion of the rotation from one vector to another.
 * @param from first vector
 * @param to second vector
 * @return The rotation between from and to vectors.
 */
Quat QuatMakeFromTo(Vec3 from, Vec3 to);

/**
 * @brief Get the axis of a quaternion.
 * @param quat valid quaternion.
 * @return normalized Vec3 of the axis values.
 */
Vec3 QuatGetAxis(Quat quat);

/**
 * @brief Get the angle of a quaternion.
 * @param quat valid quaternion.
 * @return the angle of quaternion as radians.
 */
float QuatGetAngle(Quat quat);

/**
 * @brief Get the imaginary part of a quaternion.
 * @param q any quaternion.
 * @return a vector containing ijk part of the quaternion number.
 */
Vec3 QuatGetImgPart(Quat q);

/**
 * @brief Get the real part of a quaternion.
 * @param q any quaternion.
 * @return a scalar representing the real part of the number.
 */
float QuatGetRealPart(Quat q);

/**
 * @brief Compare two quaternions and return if they are approx equal.
 * @param a first quat.
 * @param b second quat.
 * @return true if a components are near b components.
 */
bool QuatEqualApprox(Quat a, Quat b);

/**
 * @brief Standard quaternion addition.
 * @param a first element.
 * @param b second element.
 * @return the sum of each element's components.
 */
Quat QuatAdd(Quat a, Quat b);

/**
 * @brief Standard quaternion subtraction.
 * @param a first element.
 * @param b second element.
 * @return the difference of each element's components.
 */
Quat QuatSub(Quat a, Quat b);

/**
 * @brief Standard quaternion scale.
 * @param q a quaternion (unaffected).
 * @param s a scale.
 * @return a quaternion containing v components with s scale.
 */
Quat QuatScale(Quat q, float s);

/**
 * @brief Negate a quaternion components.
 * @param q a quaternion (unaffected).
 * @return Same quaternion with each component multiplied by -1.
 */
Quat QuatNeg(Quat q);

/**
 * @brief Check if two quaternions have the same orientation.
 * @param a first quaternion.
 * @param b second quaternion.
 * @return true if they are oriented the same, false otherwise.
 */
bool QuatSameOrientation(Quat a, Quat b);

/**
 * @brief How similar two quaternion are.
 * @param a first quaternion.
 * @param b second quaternion.
 * @return standard dot product.
 */
float QuatDot(Quat a, Quat b);

/**
 * @brief Squared length of a quaternion.
 *
 * Calculates the standard length of a quaternion without doing the square root
 * saving a little bit of resources.
 * @param q a quaternion (unaffected).
 * @return squared quaternion length.
 */
float QuatSqrLen(Quat q);

/**
 * @brief Standard length of a quaternion.
 * @param q a quaternion (unaffected).
 * @return quaternion's length.
 */
float QuatLen(Quat q);

/**
 * @brief Normalize a quaternion (divide each component by its inverse length).
 * @param q quaternion (unaffected).
 * @return normalized quaternion.
 */
Quat QuatNorm(Quat q);

/**
 * @brief Flip the given quaternion.
 * @param q a normalized quaternion (unaffected).
 * @return q with its imaginary part negated.
 */
Quat QuatConjugate(Quat q);

/**
 * @brief Get proper quaternion inverse.
 * @param q any quaternion (unaffected).
 * @return inverted q.
 */
Quat QuatInvert(Quat q);

/**
 * @brief Multiply two quaternions.
 * @param a any quaternion (unaffected).
 * @param b any quaternion (unaffected).
 * @return product of a by b.
 */
Quat QuatCross(Quat a, Quat b);

/**
 * @brief Transform a Vec3 using a quaternion.
 *
 * Effective rotation of a point in space relative to origin.
 * @param q any quaternion (unaffected).
 * @param v any vector to rotate its position.
 * @return same v rotated by q.
 */
Vec3 QuatTransformVec3(Quat q, Vec3 v);

/**
 * @brief Linear interpolation between two quaternions.
 * @param from origin quaternion.
 * @param to quaternion.
 * @param t transition value.
 */
Quat QuatLerp(Quat from, Quat to, float t);

/**
 * @brief Normalized linear interpolation between two quaternions.
 * @param from origin quaternion.
 * @param to quaternion.
 * @param t transition value.
 */
Quat QuatNLerp(Quat from, Quat to, float t);

/**
 * @brief Spherical interpolation between two quaternions.
 * @param from origin quaternion.
 * @param to quaternion.
 * @param t transition value.
 */
Quat QuatSLerp(Quat from, Quat to, float t);

/**
 * @brief Create a quaternion to look at the desired direction.
 * @param dir point on the universe to look at.
 * @param up world or relative up to use to align correctly the rotation.
 * @return the quaternion to look at dir.
 */
Quat QuatLookRotation(Vec3 dir, Vec3 up);

/**
 * @brief Convert a quaternion into a matrix representation.
 * @param q quaternion to be converted (unaffected).
 * @return a matrix with the same rotation as the quaternion.
 */
Mat4 QuatToMat4(Quat q);

/**
 * @brief Convert a transform matrix into a quaternion.
 * @param m matrix to be converted (unaffected).
 * @return a quaternion with the same orientation as the transform matrix.
 */
Quat Mat4ToQuat(Mat4 m);

#endif  // XMATH_QUAT_H
