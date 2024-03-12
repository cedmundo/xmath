/**
 * @file vec2.h
 * @brief Definitions, functions and utilities for 2d vectors.
 */
#ifndef XMATH_VEC2_H
#define XMATH_VEC2_H
#include <stdbool.h>

/**
 * @brief Vector of two dimensions.
 *
 * Just two float aligned by default, this structure should suffice for most
 * use cases, when contiguous memory usage is needed then `float *Vec2Floats()`
 * can be used.
 */
typedef struct {
  float x;
  float y;
} Vec2;

/**
 * A 2d vector containing only zeroes.
 */
static const Vec2 Vec2Zero = {0.0f, 0.0f};

/**
 * A 2d vector containing only ones.
 */
static const Vec2 Vec2One = {1.0f, 1.0f};

/**
 * @brief Get the consecutive floating values from a Vec2.
 * @param vec reference of the vector.
 * @return The address of first component.
 */
float* Vec2Floats(Vec2* vec);

/**
 * @brief Compare the components of two vectors and return if they are approx
 * equal.
 * @param a first vector.
 * @param b second vector.
 * @return true if a components are near b components.
 */
bool Vec2EqualApprox(Vec2 a, Vec2 b);

/**
 * @brief Standard vector addition (component by component).
 * @param a left vector.
 * @param b right vector.
 * @return always a Vec2 with the sum of each component.
 */
Vec2 Vec2Add(Vec2 a, Vec2 b);

/**
 * @brief Standard vector subtraction (component by component).
 * @param a left vector.
 * @param b right vector.
 * @return always a Vec2 with the difference of each component.
 */
Vec2 Vec2Sub(Vec2 a, Vec2 b);

/**
 * @brief Standard vector scale (component by scalar product).
 * @param v vector to scale.
 * @param f factor to multiply each component.
 * @return always a scaled Vec2.
 */
Vec2 Vec2Scale(Vec2 v, float f);

/**
 * @brief Squared length of a vector.
 *
 * Calculates the standard length of a vector without doing the square root
 * saving a little bit of resources.
 * @param v vector.
 * @return squared vector's length.
 */
float Vec2SqrLen(Vec2 v);

/**
 * @brief Standard length of a vector.
 * @param v vector.
 * @return vector's length.
 */
float Vec2Len(Vec2 v);

/**
 * @brief Normalize a vector (divide each component by its inverse length).
 * @param v vector (unaffected).
 * @return normalized vector.
 */
Vec2 Vec2Norm(Vec2 v);

/**
 * @brief Return the greater value of each component of two vectors.
 *
 * This function will return a new vector containing the greater values of each
 * component, not the greater vector.
 * @param a first vector.
 * @param b second vector.
 * @return a new vector containing the max values of each vector.
 */
Vec2 Vec2Max(Vec2 a, Vec2 b);

/**
 * @brief Return the lesser value of each component of two vectors.
 *
 * This function will return a new vector containing the lesser values of each
 * component, not the greater vector.
 * @param a first vector.
 * @param b second vector.
 * @return a new vector containing the min values of each vector.
 */
Vec2 Vec2Min(Vec2 a, Vec2 b);

#endif  // XMATH_VEC2_H
