#include <dklib/math/matrix.hpp>
#include <dklib/math/matrix3d.hpp>
#include <dklib/math/matrix4d.hpp>
#include <dklib/math/vector2d.hpp>
#include <dklib/math/vector3d.hpp>
#include <doctest/doctest.h>

#include <iostream>
#include <type_traits>
#include <utility>

#include "test_utilities.hpp"

using namespace dk::math;

#define integral_types                                                          \
    Vector<int, 1>, Vector<int, 5>, Vector<long, 1>, Vector<long, 5>,           \
        Vector2<int>, Vector2<long>, Vector3<int>, Vector3<long>, Vector4<int>, \
        Vector4<long>
#define floating_types                                                   \
    Vector<float, 1>, Vector<double, 1>, Vector<long double, 1>,         \
        Vector<float, 5>, Vector<double, 5>, Vector<long double, 5>,     \
        Vector2<float>, Vector2<double>, Vector2<long double>, Vector2D, \
        Vector3<float>, Vector3<double>, Vector3<long double>, Vector3D, \
        Vector4<float>, Vector4<double>, Vector4<long double>, Vector4D
#define parameter_types integral_types floating_types

#define TEST_CASE_VECTOR_INTEGRAL(msg) \
    TEST_CASE_TEMPLATE(msg, T, integral_types)
#define TEST_CASE_VECTOR_FLOATING(msg) \
    TEST_CASE_TEMPLATE(msg, T, floating_types)
#define TEST_CASE_VECTOR(msg) TEST_CASE_TEMPLATE(msg, T, parameter_types)

TEST_SUITE_BEGIN("Vector");

// Constructors

// Type Traits

// Factory Methods

// Axis Access

// Equality

// Negation

// Self Addition

// Addition

// Self Subtraction

// Subtraction

// Self multiplication

// Multiplication

// Self Division

// Division

// Magnitude

// Magnitude Squared

// Length-wise comparison

// Norm

// Normalization

// Dot product

// Is parallel predicate

// Is perpendicular predicate

TEST_SUITE_END();
