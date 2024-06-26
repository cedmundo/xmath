/**
 * @file vec4.h
 * @brief Definitions, functions and utilities for 4d vectors.
 */
#ifndef XMATH_VEC4_H
#define XMATH_VEC4_H
#include <stdbool.h>

/**
 * @brief Vector of four dimensions.
 *
 * Just four floats aligned by default, this structure should suffice for most
 * use cases, when contiguous memory usage is needed then `float *Vec4Floats()`
 * can be used.
 */
typedef struct {
  float x;
  float y;
  float z;
  float w;
} Vec4;

//! @brief a Vec4 full of zeroes.
static const Vec4 Vec4Zero = {0.0f, 0.0f, 0.0f, 0.0f};

//! @brief a Vec4 full of ones.
static const Vec4 Vec4One = {1.0f, 1.0f, 1.0f, 1.0f};

/**
 * @brief Get the consecutive floating values from a Vec4.
 * @param vec reference of the vector.
 * @return The address of first component.
 */
float* Vec4Floats(Vec4* vec);

/**
 * @brief Compare the components of two vectors and return if they are approx
 * equal.
 * @param a first vector.
 * @param b second vector.
 * @return true if a components are near b components.
 */
bool Vec4EqualApprox(Vec4 a, Vec4 b);

/**
 * @brief Standard 4d vector addition.
 * @param a first element.
 * @param b second element.
 * @return the sum of each element's components.
 */
Vec4 Vec4Add(Vec4 a, Vec4 b);

/**
 * @brief Standard 4d vector subtraction.
 * @param a first element.
 * @param b second element.
 * @return the difference of each element's components.
 */
Vec4 Vec4Sub(Vec4 a, Vec4 b);

/**
 * @brief Standard 4d vector scale.
 * @param v a vector (unaffected).
 * @param s a scale.
 * @return a vector containing v components with s scale.
 */
Vec4 Vec4Scale(Vec4 v, float s);

/**
 * @brief Squared length of a 4d vector.
 *
 * Calculates the standard length of a vector without doing the square root
 * saving a little bit of resources.
 * @param v a vector (unaffected).
 * @return squared vector length.
 */
float Vec4SqrLen(Vec4 v);

/**
 * @brief Standard length of a 4d vector.
 * @param v a vector (unaffected).
 * @return vector's length.
 */
float Vec4Len(Vec4 v);

/**
 * @brief Normalize a vector (divide each component by its inverse length).
 * @param v vector (unaffected).
 * @return normalized vector.
 */
Vec4 Vec4Norm(Vec4 v);

/**
 * @brief Return the greater value of each component of two vectors.
 *
 * This function will return a new vector containing the greater values of each
 * component, not the greater vector.
 * @param a first vector.
 * @param b second vector.
 * @return a new vector containing the max values of each vector.
 */
Vec4 Vec4Max(Vec4 a, Vec4 b);

/**
 * @brief Return the lesser value of each component of two vectors.
 *
 * This function will return a new vector containing the lesser values of each
 * component, not the greater vector.
 * @param a first vector.
 * @param b second vector.
 * @return a new vector containing the min values of each vector.
 */
Vec4 Vec4Min(Vec4 a, Vec4 b);

/**
 * @brief Angle between two vectors.
 * @param a any vector.
 * @param b any vector.
 * @return angle in radians.
 */
float Vec4Angle(Vec4 a, Vec4 b);

/**
 * @brief Dot product of two vector.
 * @param a any vector.
 * @param b any vector.
 * @return standard dot result.
 */
float Vec4Dot(Vec4 a, Vec4 b);

/**
 * @brief Projects a vector into another.
 * @param a projecting vector.
 * @param b projected into vector.
 * @return the vector within b that's a projection of a.
 */
Vec4 Vec4Project(Vec4 a, Vec4 b);

/**
 * @brief Rejection of a vector into another.
 * @param a rejecting vector
 * @param b rejected into vector.
 * @return the subtraction between rejecting vector and a and b's projection.
 */
Vec4 Vec4Reject(Vec4 a, Vec4 b);

/**
 * @brief Reflection of a vector into another.
 * @param a
 * @param b
 * @return
 */
Vec4 Vec4Reflect(Vec4 a, Vec4 b);

/**
 * @brief Linear interpolation of a into b by factor f.
 * @param a initial vector.
 * @param b final vector.
 * @param f factor (between 0 and 1).
 * @return a linearly interpolated vector.
 */
Vec4 Vec4Lerp(Vec4 a, Vec4 b, float f);

/**
 * @brief Spherical linear interpolation of a into b by factor f.
 * @param a initial vector.
 * @param b final vector.
 * @param f factor (between 0 and 1).
 * @return a spherical linearly interpolated vector.
 */
Vec4 Vec4Slerp(Vec4 a, Vec4 b, float f);

/**
 * @brief Normalized linear interpolation of a into b by factor f.
 * @param a initial vector.
 * @param b final vector.
 * @param f factor (between 0 and 1).
 * @return a normalized linearly interpolated vector.
 */
Vec4 Vec4Nlerp(Vec4 a, Vec4 b, float f);

#endif  // XMATH_VEC4_H
