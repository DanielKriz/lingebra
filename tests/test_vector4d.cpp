#include <doctest/doctest.h>
#include <dklib/math/vector4d.hpp>

#include <iostream>
#include <type_traits>
#include <utility>

#include "test_utilities.hpp"

using namespace dk::math;

#define integral_types Vector4<int>, Vector4<long>
#define floating_types \
    Vector4<float>, Vector4<double>, Vector4<long double>, Vector4D
#define parameter_types integral_types floating_types

#define TEST_CASE_VECTOR_INTEGRAL(msg) \
    TEST_CASE_TEMPLATE(msg, T, integral_types)
#define TEST_CASE_VECTOR_FLOATING(msg) \
    TEST_CASE_TEMPLATE(msg, T, floating_types)
#define TEST_CASE_VECTOR(msg) TEST_CASE_TEMPLATE(msg, T, parameter_types)

TEST_SUITE_BEGIN("Vector4");

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
