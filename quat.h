/**
* @file quat.h
* @brief Definitions, functions and utilities for quaternions.
*/
#ifndef XMATH_QUAT_H
#define XMATH_QUAT_H
#include <stdbool.h>

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
float *QuatFloats(Quat *quat);

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
 * @return a vector containing v components with s scale.
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

#endif  // XMATH_QUAT_H
