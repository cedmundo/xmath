/**
 * @file vec3.h
 * @brief Definitions, functions and utilities for 3d vectors.
 */
#ifndef XMATH_VEC3_H
#define XMATH_VEC3_H
#include <stdbool.h>

/**
 * @brief Vector of three dimensions.
 *
 * Just three floats aligned by default, this structure should suffice for most
 * use cases, when contiguous memory usage is needed then `float *Vec3Floats()`
 * can be used.
 */
typedef struct {
  float x;
  float y;
  float z;
} Vec3;

//! @brief a Vec3 full of zeroes
static const Vec3 Vec3Zero = {0.0f, 0.0f, 0.0f};

//! @brief a Vec3 full of ones
static const Vec3 Vec3One = {1.0f, 1.0f, 1.0f};

//! @brief a Vec3 representing the general up direction
static const Vec3 Vec3Up = {0.0f, 1.0f, 0.0f};

//! @brief a Vec3 representing the general down direction
static const Vec3 Vec3Down = {0.0f, -1.0f, 0.0f};

//! @brief a Vec3 representing the general left direction
static const Vec3 Vec3Left = {-1.0f, 0.0f, 0.0f};

//! @brief a Vec3 representing the general right direction
static const Vec3 Vec3Right = {1.0f, 0.0f, 0.0f};

//! @brief a Vec3 representing the general forward direction
static const Vec3 Vec3Forward = {0.0f, 0.0f, -1.0f};

//! @brief a Vec3 representing the general backward direction
static const Vec3 Vec3Backward = {0.0f, 0.0f, 1.0f};

/**
 * @brief Get the consecutive floating values from a Vec3.
 * @param vec reference of the vector.
 * @return The address of first component.
 */
float* Vec3Floats(Vec3* vec);

/**
 * @brief Compare the components of two vectors and return if they are approx
 * equal.
 * @param a first vector.
 * @param b second vector.
 * @return true if a components are near b components.
 */
bool Vec3EqualApprox(Vec3 a, Vec3 b);

/**
 * @brief Standard 3d vector addition.
 * @param a first element.
 * @param b second element.
 * @return the sum of each element's components.
 */
Vec3 Vec3Add(Vec3 a, Vec3 b);

/**
 * @brief Standard 3d vector subtraction.
 * @param a first element.
 * @param b second element.
 * @return the difference of each element's components.
 */
Vec3 Vec3Sub(Vec3 a, Vec3 b);

/**
 * @brief Standard 3d vector scale.
 * @param v a vector (unaffected).
 * @param s a scale.
 * @return a vector containing v components with s scale.
 */
Vec3 Vec3Scale(Vec3 v, float s);

/**
 * @brief Squared length of a 3d vector.
 *
 * Calculates the standard length of a vector without doing the square root
 * saving a little bit of resources.
 * @param v a vector (unaffected).
 * @return squared vector length.
 */
float Vec3SqrLen(Vec3 v);

/**
 * @brief Standard length of a 3d vector.
 * @param v a vector (unaffected).
 * @return vector's length.
 */
float Vec3Len(Vec3 v);

/**
 * @brief Normalize a vector (divide each component by its inverse length).
 * @param v vector (unaffected).
 * @return normalized vector.
 */
Vec3 Vec3Norm(Vec3 v);

/**
 * @brief Return the greater value of each component of two vectors.
 *
 * This function will return a new vector containing the greater values of each
 * component, not the greater vector.
 * @param a first vector.
 * @param b second vector.
 * @return a new vector containing the max values of each vector.
 */
Vec3 Vec3Max(Vec3 a, Vec3 b);

/**
 * @brief Return the lesser value of each component of two vectors.
 *
 * This function will return a new vector containing the lesser values of each
 * component, not the greater vector.
 * @param a first vector.
 * @param b second vector.
 * @return a new vector containing the min values of each vector.
 */
Vec3 Vec3Min(Vec3 a, Vec3 b);

/**
 * @brief Angle between two vectors.
 * @param a any vector.
 * @param b any vector.
 * @return angle in radians.
 */
float Vec3Angle(Vec3 a, Vec3 b);

/**
 * @brief Dot product of two vector.
 * @param a any vector.
 * @param b any vector.
 * @return standard dot result.
 */
float Vec3Dot(Vec3 a, Vec3 b);

/**
 * @brief Cross product of two vectors.
 * @param l any vector.
 * @param r any vector.
 * @return standard cross product.
 */
Vec3 Vec3Cross(Vec3 l, Vec3 r);

/**
 * @brief Projects a vector into another.
 * @param a projecting vector.
 * @param b projected into vector.
 * @return the vector within b that's a projection of a.
 */
Vec3 Vec3Project(Vec3 a, Vec3 b);

/**
 * @brief Rejection of a vector into another.
 * @param a rejecting vector
 * @param b rejected into vector.
 * @return the subtraction between rejecting vector and a and b's projection.
 */
Vec3 Vec3Reject(Vec3 a, Vec3 b);

/**
 * @brief Reflection of a vector into another.
 * @param a
 * @param b
 * @return
 */
Vec3 Vec3Reflect(Vec3 a, Vec3 b);

/**
 * @brief Linear interpolation of a into b by factor f.
 * @param a initial vector.
 * @param b final vector.
 * @param f factor (between 0 and 1).
 * @return a linearly interpolated vector.
 */
Vec3 Vec3Lerp(Vec3 a, Vec3 b, float f);

/**
 * @brief Spherical linear interpolation of a into b by factor f.
 * @param a initial vector.
 * @param b final vector.
 * @param f factor (between 0 and 1).
 * @return a spherical linearly interpolated vector.
 */
Vec3 Vec3Slerp(Vec3 a, Vec3 b, float f);

/**
 * @brief Normalized linear interpolation of a into b by factor f.
 * @param a initial vector.
 * @param b final vector.
 * @param f factor (between 0 and 1).
 * @return a normalized linearly interpolated vector.
 */
Vec3 Vec3Nlerp(Vec3 a, Vec3 b, float f);

#endif /* XMATH_VEC3_H */
