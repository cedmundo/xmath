/**
 * @file vec4.h
 * @brief Definitions, functions and utilities for 4x4 matrices.
 */
#ifndef XMATH_MAT4_H
#define XMATH_MAT4_H
#include <stdbool.h>
#include "vec3.h"
#include "vec4.h"
// clang-format off

/**
 * @brief Square matrix of 4x4 elements.
 */
typedef struct {
  float xx, xy, xz, xw;
  float yx, yy, yz, yw;
  float zx, zy, zz, zw;
  float wx, wy, wz, ww;
} Mat4;

//! @brief a Mat4 full of zeroes.
static const Mat4 Mat4Zero = {
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f,
};

//! @brief an identity form of Mat4.
static const Mat4 Mat4Identity = {
  1.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f,
};
// clang-format on

/**
 * @brief Get the consecutive floating values from a Mat4.
 * @param m reference of the matrix.
 * @return The address of first component of first column.
 */
float* Mat4Floats(Mat4* m);

/**
 * @brief Compare the elements of two matrices and return if they are approx
 * equal.
 * @param a first matrix.
 * @param b second matrix.
 * @return true if a elements are near b elements.
 */
bool Mat4EqualApprox(Mat4 a, Mat4 b);

/**
 * \brief Gets a matrix row by its index.
 *
 * \param Mat4 m, matrix to lookup in.
 * \param int i, row index, between 0 and 3. Warning: do not use quantities
 * outside range. \return a Vec4 containing the full row.
 */
Vec4 Mat4Row(Mat4 m, unsigned int i);

/**
 * \brief Gets a matrix column by its index.
 *
 * \param Mat4 m, matrix to lookup in.
 * \param int i, column index, between 0 and 3. Warning: do not use quantities
 * outside range. \return a Vec4 containing the full column.
 */
Vec4 Mat4Col(Mat4 m, unsigned int i);

/**
 * \brief Transposes a matrix.
 *
 * \param Mat4 m matrix to be transposed (not modified).
 * \return transposed matrix.
 */
Mat4 Mat4Transpose(Mat4 m);

/**
 * \brief Get the inverse of a matrix.
 *
 * \param Mat4 result (out).
 * \param Mat4 m matrix to be inverted (not modified).
 * \return true if the matrix can be inverted, false otherwise.
 */
bool Mat4Invert(Mat4* result, Mat4 m);

/**
 * \brief Adds two matrices.
 * \param Mat4 a left operand.
 * \param Mat4 b right operand.
 * \return a new stack matrix with a+b components result.
 */
Mat4 Mat4Add(Mat4 a, Mat4 b);

/**
 * \brief Substracts two matrices.
 * \param Mat4 a left operand.
 * \param Mat4 b right operand.
 * \return a new stack matrix with a-b components result.
 */
Mat4 Mat4Sub(Mat4 a, Mat4 b);

/**
 * \brief Scales a matrix by a scalar factor.
 * \param Mat4 a matrix to scale.
 * \param float s scalar factor.
 * \return new stack scaled matrix.
 */
Mat4 Mat4Scale(Mat4 a, float s);

/**
 * \brief Multiplies two matrices.
 * \param Mat4 a left operand.
 * \param Mat4 b right operand.
 * \return a result of multiplication between axb.
 */
Mat4 Mat4Mul(Mat4 a, Mat4 b);

/**
 * \brief Multiplies a vector with a matrix.
 */
Vec4 Mat4MulVec4(Mat4 a, Vec4 b);

/**
 * \brief Makes a new ortho matrix.
 *
 * Generates a new projection matrix usen left, right, bottom, top, near and far
 * parameters.
 *
 * \param float l left
 * \param float r right
 * \param float b bottom
 * \param float t top
 * \param float n near
 * \param float f far
 * \return a othographic projection matrix.
 */
Mat4 Mat4MakeOrtho(float l, float r, float b, float t, float n, float f);

/**
 * \brief Makes a new perspective matrix.
 *
 * Generates a new projection matrix usen fov, aspect, near and far parameters.
 *
 * \param float yfov Field of view from Y axis
 * \param float aspect ratio
 * \param float n near
 * \param float f far
 * \return a prerspective projection matrix.
 */
Mat4 Mat4MakePerspective(float yfov, float aspect, float n, float f);

/**
 * \brief Makes a new "looking at" matrix.
 *
 * \param float position of object
 * \param float target to look at
 * \param float up
 */
Mat4 Mat4LookAt(Vec3 position, Vec3 target, Vec3 up);

#endif
