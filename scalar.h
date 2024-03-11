/**
 * @file scalar.h
 * @brief Miscellaneous scalar functions (such compare, interpolation, etc).
 */
#ifndef XMATH_SCALAR_H
#define XMATH_SCALAR_H
#include <stdbool.h>

#define XMATH_EPSILON (0.000001f)
#define XMATH_PI (3.1415926f)

/**
 * @brief Compares two float values.
 * @return true if they are approximately equal (diff less than epsilon).
 */
bool FEqualApprox(float a, float b);

/**
 * @brief Max value between to floats.
 * @param a First value.
 * @param b Second value.
 * @return The greater number between a and b.
 */
float FMax(float a, float b);

/**
 * @brief Min value between to floats.
 * @param a first value.
 * @param b second value.
 * @return The lesser number between a and b.
 */
float FMin(float a, float b);

/**
 * @brief Linearly interpolates first and second by factor.
 * It uses the 'precise' method which guarantees that result is second when
 * factor is 1.0.
 *
 * @param first value (any range).
 * @param second value (any range).
 * @param factor value between 0.0f and 1.0f.
 * @return Interpolated value.
 */
float FLerp(float first, float second, float factor);

/**
 * @brief Remap a value between range [minSrc, maxSrc] into new range [minDst, maxDst].
 * @param value value to remap (any range).
 * @param minSrc low value of source range.
 * @param maxSrc high value of source range.
 * @param minDst low value of destination range.
 * @param maxDst high value of destination range.
 * @return the value as it were on [minDst, maxDest]
 */
float FRemap(float value, float minSrc, float maxSrc, float minDst, float maxDst);

/**
 * @brief Convert radians into degrees.
 * @param rad value in radians.
 * @return value in degrees.
 */
float FRad2Deg(float rad);

/**
 * @brief Convert degrees into radians.
 * @param deg value in degrees.
 * @return value in radians.
 */
float FDeg2Rad(float deg);

#endif /* XMATH_SCALAR_H */