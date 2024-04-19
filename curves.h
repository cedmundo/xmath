/**
 * @file curves.h
 * @brief Beizer and hermit curves types and related procedures.
 */
#ifndef XMATH_CURVES_H
#define XMATH_CURVES_H

#include "vec3.h"

/**
 * @brief Represent a single Beizer curve along a spline.
 */
typedef struct {
  Vec3 p1;
  Vec3 c1;
  Vec3 p2;
  Vec3 c2;
} BeizerCurve;

/**
 * @brief Represent a single Hermit curve along a spline.
 */
typedef struct {
  Vec3 p1;
  Vec3 s1;
  Vec3 p2;
  Vec3 s2;
} HermitCurve;

/**
 * @brief Interpolates a beizer curve at point t.
 * @param curve any valid beizer curve.
 * @param t point of interpolation.
 * @return the Vec3 after applying lerp on all points and controls.
 */
Vec3 BeizerInterpolate(BeizerCurve curve, float t);

/**
 * @brief Interpolates a hermit curve at point t.
 * @param curve any valid beizer curve.
 * @param t point of interpolation.
 * @return the Vec3 after applying lerp on all points and controls.
 */
Vec3 HermitInterpolate(HermitCurve curve, float t);

#endif /* XMATH_CURVES_H */
