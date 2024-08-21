#include <doctest/doctest.h>
#include <dklib/math/vector3d.hpp>

#include <iostream>
#include <sstream>
#include <type_traits>
#include <utility>

#include "test_utilities.hpp"

using namespace dk::math;

#define integral_types Vector3<int>, Vector3<long>
#define floating_types \
    Vector3<float>, Vector3<double>, Vector3<long double>, Vector3D
#define parameter_types integral_types floating_types

#define TEST_CASE_VECTOR_INTEGRAL(msg) \
    TEST_CASE_TEMPLATE(msg, T, integral_types)
#define TEST_CASE_VECTOR_FLOATING(msg) \
    TEST_CASE_TEMPLATE(msg, T, floating_types)
#define TEST_CASE_VECTOR(msg) TEST_CASE_TEMPLATE(msg, T, parameter_types)

TEST_SUITE_BEGIN("Vector3");

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

#define DOCTEST_VALUE_PARAMETERIZED_DATA(data, data_container)                                                \
    static size_t _doctest_subcase_idx = 0;                                                                   \
    std::for_each(                                                                                            \
        data_container.begin(), data_container.end(), [&](const auto &val) {                                  \
            DOCTEST_SUBCASE((std::string(#data_container "[") + std::to_string(_doctest_subcase_idx++) + "]") \
                                .c_str()) {                                                                   \
                data = val;                                                                                   \
            }                                                                                                 \
        }                                                                                                     \
    );                                                                                                        \
    _doctest_subcase_idx = 0

using namespace dk::math;

TEST_SUITE_BEGIN("Vector3D");

TEST_CASE("Default constructor") {
    auto vec = Vector3D();
    CHECK(vec.get_x() == 0.0f);
    CHECK(vec.get_y() == 0.0f);
    CHECK(vec.get_z() == 0.0f);
}

TEST_CASE("Constructor with single value") {
    std::vector<float> values = { 0.0f, 1.0f, -2.0f };
    float value = 0.0f;
    DOCTEST_VALUE_PARAMETERIZED_DATA(value, values);
    auto vec = Vector3D(value);
    CHECK(vec.get_x() == value);
    CHECK(vec.get_y() == value);
    CHECK(vec.get_z() == value);
}

TEST_CASE("Constructor with multiple value") {
    std::vector<std::tuple<float, float, float>> values = {
        { 0.0f, 1.0f, -2.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 2.0f, 3.0f },
        { -1.0f, -2.0f, -3.0f },
    };

    std::tuple<float, float, float> value;
    DOCTEST_VALUE_PARAMETERIZED_DATA(value, values);
    auto [x, y, z] = value;
    auto vec = Vector3D(x, y, z);
    CHECK(vec.get_x() == x);
    CHECK(vec.get_y() == y);
    CHECK(vec.get_z() == z);
}

TEST_CASE("Equality operator") {
    auto vec = Vector3D::unit();
    CHECK(vec == vec);
}

TEST_CASE("Inequality operator") {
    auto vec = Vector3D::unit();
    CHECK(vec != Vector3D::zero());
}

TEST_CASE("Getting the generic x axis") {
    CHECK(Vector3D::x_axis() == Vector3D(1.0f, 0.0f, 0.0f));
}

TEST_CASE("Getting the generic y axis") {
    CHECK(Vector3D::y_axis() == Vector3D(0.0f, 1.0f, 0.0f));
}

TEST_CASE("Getting the generic z axis") {
    CHECK(Vector3D::z_axis() == Vector3D(0.0f, 0.0f, 1.0f));
}

TEST_CASE("Getting the arbitrary x axis") {
    CHECK(Vector3D::x_axis(Vector3D(2.0f, 3.0f, 4.0f)) == Vector3D(2.0f, 0.0f, 0.0f));
}

TEST_CASE("Getting the arbitrary y axis") {
    CHECK(Vector3D::y_axis(Vector3D(2.0f, 3.0f, 4.0f)) == Vector3D(0.0f, 3.0f, 0.0f));
}

TEST_CASE("Getting the arbitrary z axis") {
    CHECK(Vector3D::z_axis(Vector3D(2.0f, 3.0f, 4.0f)) == Vector3D(0.0f, 0.0f, 4.0f));
}

TEST_CASE("Unit vector static factory method") {
    auto vec = Vector3D::unit();
    CHECK(vec == Vector3D(1.0f, 1.0f, 1.0f));
}

TEST_CASE("Zero vector static factory method") {
    auto vec = Vector3D::zero();
    CHECK(vec == Vector3D(0.0f, 0.0f, 0.0f));
}

TEST_CASE("Compatibility with ostream") {
    auto vec = Vector3D::unit();
    std::stringstream os;
    os << vec;
    CHECK(os.str() == "(1, 1, 1)");
}

TEST_CASE("Negation operator with lvalues") {
    auto vec = Vector3D::unit();
    CHECK(-vec == Vector3D(-1.0f));
}

TEST_CASE("Negation operator rvalues") {
    CHECK(-Vector3D::unit() == Vector3D(-1.0f));
    CHECK(-Vector3D(1.0f) == Vector3D(-1.0f));
}

TEST_CASE("Negation operator of zero vector") {
    auto vec = Vector3D::zero();
    CHECK(-vec == Vector3D::zero());
}

TEST_CASE("Negation operator does not change original vector") {
    auto vec = Vector3D::unit();
    auto res = -vec;
    CHECK(vec == Vector3D::unit());
    CHECK(vec != res);
}

TEST_CASE("Self assignement with addition") {
    auto vec = Vector3D::unit();
    vec += Vector3D::unit();
    CHECK(vec == Vector3D(2.0f));
}

TEST_CASE("Self assignement with addition of zero vector") {
    auto vec = Vector3D::unit();
    vec += Vector3D::unit();
    CHECK(vec == Vector3D(2.0f));
}

TEST_CASE("Self assignement with addition negative unit vector") {
    auto vec = Vector3D::unit();
    vec += -Vector3D::unit();
    CHECK(vec == Vector3D::zero());
}

TEST_CASE("Self assignement with subtraction") {
    auto vec = Vector3D::unit();
    vec -= Vector3D::unit();
    CHECK(vec == Vector3D::zero());
}

TEST_CASE("Self assignement with subtraction of zero vector") {
    auto vec = Vector3D::unit();
    vec -= Vector3D::zero();
    CHECK(vec == Vector3D::unit());
}

TEST_CASE("Self assignement with subtraction of negative unit vector") {
    auto vec = Vector3D::zero();
    vec -= -Vector3D::unit();
    CHECK(vec == Vector3D::unit());
}

TEST_CASE("Self assignement with multiplication") {
    auto vec = Vector3D::unit();
    vec *= 2.0f;
    CHECK(vec == Vector3D(2.0f));
}

TEST_CASE("Self assignement with 0 multiplication") {
    auto vec = Vector3D::unit();
    vec *= 0.0f;
    CHECK(vec == Vector3D::zero());
}

TEST_CASE("Self assignement with 1 multiplication") {
    auto vec = Vector3D::unit();
    vec *= 1.0f;
    CHECK(vec == Vector3D::unit());
}

TEST_CASE("Self assignement with -1 multiplication") {
    auto vec = Vector3D::unit();
    vec *= -1.0f;
    CHECK(vec == -Vector3D::unit());
}

TEST_CASE("Self assignement with unit vector multiplication") {
    auto vec = Vector3D::unit();
    vec *= Vector3D::unit();
    CHECK(vec == Vector3D::unit());
}

TEST_CASE("Self assignement with arbitrary vector multiplication") {
    auto vec = Vector3D::unit();
    vec *= Vector3D(1.0f, 2.0f, 3.0f);
    CHECK(vec == Vector3D(1.0f, 2.0f, 3.0f));
}

TEST_CASE("Self assignement with arbitrary and zero vector multiplication") {
    auto vec = Vector3D::zero();
    vec *= Vector3D(1.0f, 2.0f, 3.0f);
    CHECK(vec == Vector3D::zero());
}

TEST_CASE("Self assignement with division") {
    auto vec = Vector3D::unit();
    vec /= 2.0f;
    CHECK(vec == Vector3D(0.5f));
}

TEST_CASE("Self assignement with 0 division") {
    auto vec = Vector3D::unit();
    CHECK_THROWS_WITH_AS(vec /= 0.0f, "Division by zero", std::runtime_error);
}

TEST_CASE("Self assignement with 1 division") {
    auto vec = Vector3D::unit();
    vec /= 1.0f;
    CHECK(vec == Vector3D::unit());
}

TEST_CASE("Self assignement with -1 division") {
    auto vec = Vector3D::unit();
    vec /= -1.0f;
    CHECK(vec == -Vector3D::unit());
}

TEST_CASE("Addition operator with rvalues") {
    CHECK(Vector3D::unit() + Vector3D::unit() == Vector3D(2.0f));
}

TEST_CASE("Addition operator with lvalues") {
    auto vec1 = Vector3D::unit();
    auto vec2 = Vector3D::unit();
    CHECK(vec1 + vec2 == Vector3D(2.0f));
}

TEST_CASE("Addition operator with zero vector") {
    CHECK(Vector3D::unit() + Vector3D::zero() == Vector3D::unit());
}

TEST_CASE("Addition operator with negation vector") {
    CHECK(Vector3D::unit() + -Vector3D::unit() == Vector3D::zero());
}

TEST_CASE("Subtraction operator with rvalues") {
    CHECK(Vector3D::unit() - Vector3D::unit() == Vector3D::zero());
}

TEST_CASE("Subtraction operator with lvalues") {
    auto vec1 = Vector3D::unit();
    auto vec2 = Vector3D::unit();
    CHECK(vec1 - vec2 == Vector3D::zero());
}

TEST_CASE("Subtraction operator with zero vector") {
    CHECK(Vector3D::unit() - Vector3D::zero() == Vector3D::unit());
}

TEST_CASE("Subtraction operator with negation vector") {
    CHECK(Vector3D::unit() - -Vector3D::unit() == Vector3D(2.0f));
}

TEST_CASE("Multiplication operator with rvalues") {
    CHECK(Vector3D::unit() * 2.0f == Vector3D(2.0f));
}

TEST_CASE("Multiplication operator with lvalues") {
    auto vec = Vector3D::unit();
    float val = 2.0f;
    CHECK(vec * val == Vector3D(2.0f));
}

TEST_CASE("Multiplication operator with rvalue vectors") {
    CHECK(Vector3D::unit() * Vector3D(2.0f) == Vector3D(2.0f));
}

TEST_CASE("Multiplication operator with lvalue vectors") {
    auto vec1 = Vector3D::unit();
    auto vec2 = Vector3D(2.0f);
    CHECK(vec1 * vec2 == Vector3D(2.0f));
}

TEST_CASE("Multiplication operator should be symmetric") {
    CHECK(Vector3D::unit() * 2.0f == 2.0f * Vector3D::unit());
}

TEST_CASE("Multiplication operator with 1") {
    CHECK(Vector3D::unit() * 1.0f == Vector3D::unit());
    CHECK(Vector3D::unit() * Vector3D::unit() == Vector3D::unit());
}

TEST_CASE("Multiplication operator with 0") {
    CHECK(Vector3D::unit() * 0.0f == Vector3D::zero());
    CHECK(Vector3D::unit() * Vector3D::zero() == Vector3D::zero());
}

TEST_CASE("Multiplication operator with -1") {
    CHECK(Vector3D::unit() * -1.0f == Vector3D(-1.0f));
    CHECK(Vector3D::unit() * -Vector3D::unit() == -Vector3D::unit());
}

TEST_CASE("Multiplication of zero vector") {
    CHECK(Vector3D::zero() * -1.0f == Vector3D::zero());
    CHECK(Vector3D::zero() * 1.0f == Vector3D::zero());
}

TEST_CASE("Multiplication of negative vector") {
    CHECK(-Vector3D::unit() * -1.0f == Vector3D::unit());
    CHECK(-Vector3D::unit() * 1.0f == -Vector3D::unit());
}

TEST_CASE("Division operator with rvalues") {
    CHECK(Vector3D::unit() / 2.0f == Vector3D(0.5f));
}

TEST_CASE("Division operator with lvalues") {
    auto vec = Vector3D::unit();
    float val = 2.0f;
    CHECK(vec / val == Vector3D(0.5f));
}

TEST_CASE("Division operator with rvalue vectors") {
    CHECK(Vector3D::unit() / Vector3D(2.0f) == Vector3D(0.5f));
}

TEST_CASE(
    "Division operator with vector and scalar should produce same values"
) {
    auto vec = Vector3D(2.0f);
    CHECK(vec / 2.0f == vec / Vector3D(2.0f));
}

TEST_CASE("Division operator with lvalue vectors") {
    auto vec1 = Vector3D::unit();
    auto vec2 = Vector3D(2.0f);
    CHECK(vec1 / vec2 == Vector3D(0.5f));
}

TEST_CASE("Division operator with 1") {
    CHECK(Vector3D::unit() / 1.0f == Vector3D::unit());
    CHECK(Vector3D::unit() / Vector3D::unit() == Vector3D::unit());
}

TEST_CASE("Division operator with 0") {
    CHECK_THROWS_WITH_AS(Vector3D::unit() / 0.0f, "Division by zero", std::runtime_error);
    CHECK_THROWS_WITH_AS(Vector3D::unit() / Vector3D::zero(), "Division by zero", std::runtime_error);
}

TEST_CASE("Division operator with -1") {
    CHECK(Vector3D::unit() / -1.0f == Vector3D(-1.0f));
    CHECK(Vector3D::unit() / -Vector3D::unit() == -Vector3D::unit());
}

// Dot product related tests:

TEST_CASE("Dot product from a method") {
    CHECK(Vector3D::unit().dot(Vector3D::unit()) == 3.0f);
}

TEST_CASE(
    "Dot product method does not change the values in the original vector"
) {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    auto backup = vec;
    (void)vec.dot(Vector3D::unit());
    CHECK(vec == backup);
}

TEST_CASE("Dot product from a method with lvalues") {
    auto vec1 = Vector3D(1.0f, 2.0f, 3.0f);
    auto vec2 = Vector3D(3.0f, 2.0f, 1.0f);
    CHECK(vec1.dot(vec2) == 10.0f);
}

TEST_CASE("Dot product from a method with arbitrary vector") {
    CHECK(Vector3D::unit().dot(Vector3D(1.0f, 2.0f, 3.0f)) == 6.0f);
}

TEST_CASE("Dot product from a method with zero vector") {
    CHECK(Vector3D::unit().dot(Vector3D::zero()) == 0.0f);
}

TEST_CASE("Dot product function") {
    CHECK(dot(Vector3D::unit(), Vector3D::unit()) == 3.0f);
}

TEST_CASE(
    "Dot product function does not change the values in original vectors"
) {
    auto vec1 = Vector3D::unit();
    auto vec2 = Vector3D::unit();
    auto backup1 = vec1;
    auto backup2 = vec2;
    (void)dot(vec1, vec2);
    CHECK(vec1 == backup1);
    CHECK(vec2 == backup2);
}

TEST_CASE("Dot product function with lvalues") {
    auto vec1 = Vector3D(1.0f, 2.0f, 3.0f);
    auto vec2 = Vector3D(3.0f, 2.0f, 1.0f);
    CHECK(dot(vec1, vec2) == 10.0f);
}

TEST_CASE("Dot product function with zero vector") {
    CHECK(dot(Vector3D::unit(), Vector3D::zero()) == 0.0f);
}

TEST_CASE("Dot product function with arbitrary vector") {
    CHECK(dot(Vector3D::unit(), Vector3D(1.0f, 2.0f, 3.0f)) == 6.0f);
}

// Magnitude related tests:

TEST_CASE("Magnitude of arbitrary vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    CHECK(vec.magnitude() == doctest::Approx(std::sqrt(14.0f)));
}

TEST_CASE(
    "Magnitude method does not change the values in the original vector"
) {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    auto backup = vec;
    (void)vec.magnitude();
    CHECK(vec == backup);
}

TEST_CASE("Magnitude of a zero vector") {
    auto vec = Vector3D::zero();
    CHECK(vec.magnitude() == doctest::Approx(std::sqrt(0.0f)));
}

TEST_CASE("Magnitude of an unit vector") {
    auto vec = Vector3D::unit();
    CHECK(vec.magnitude() == doctest::Approx(std::sqrt(3.0f)));
}

TEST_CASE("Magnitude of a negative unit vector") {
    auto vec = -Vector3D::unit();
    CHECK(vec.magnitude() == doctest::Approx(std::sqrt(3.0f)));
}

TEST_CASE("Magnitude function of arbitrary vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    CHECK(magnitude(vec) == doctest::Approx(std::sqrt(14.0f)));
}

TEST_CASE(
    "Magnitude function does not change the values in the original vector"
) {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    auto backup = vec;
    (void)magnitude(vec);
    CHECK(vec == backup);
}

TEST_CASE("Magnitude function of a zero vector") {
    auto vec = Vector3D::zero();
    CHECK(magnitude(vec) == doctest::Approx(std::sqrt(0.0f)));
}

TEST_CASE("Magnitude function of an unit vector") {
    auto vec = Vector3D::unit();
    CHECK(magnitude(vec) == doctest::Approx(std::sqrt(3.0f)));
}

TEST_CASE("Magnitude function of a negative unit vector") {
    auto vec = -Vector3D::unit();
    CHECK(magnitude(vec) == doctest::Approx(std::sqrt(3.0f)));
}

// Squared Magnitude related tests:

TEST_CASE("Square magnitude of arbitrary vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    CHECK(vec.magnitude_squared() == 14.0f);
}

TEST_CASE("Squared magnitude method does not change the values in the original "
          "vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    auto backup = vec;
    (void)vec.magnitude_squared();
    CHECK(vec == backup);
}

TEST_CASE("Square magnitude of a zero vector") {
    auto vec = Vector3D::zero();
    CHECK(vec.magnitude_squared() == 0.0f);
}

TEST_CASE("Square magnitude of an unit vector") {
    auto vec = Vector3D::unit();
    CHECK(vec.magnitude_squared() == 3.0f);
}

TEST_CASE("Square magnitude of a negative unit vector") {
    auto vec = -Vector3D::unit();
    CHECK(vec.magnitude_squared() == 3.0f);
}

TEST_CASE("Square magnitude function of arbitrary vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    CHECK(magnitude_squared(vec) == 14.0f);
}

TEST_CASE("Squared magnitude function does not change the values in the "
          "original vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    auto backup = vec;
    (void)magnitude_squared(vec);
    CHECK(vec == backup);
}

TEST_CASE("Square magnitude function of a zero vector") {
    auto vec = Vector3D::zero();
    CHECK(magnitude_squared(vec) == 0.0f);
}

TEST_CASE("Square magnitude function of an unit vector") {
    auto vec = Vector3D::unit();
    CHECK(magnitude_squared(vec) == 3.0f);
}

TEST_CASE("Square magnitude function of a negative unit vector") {
    auto vec = -Vector3D::unit();
    CHECK(magnitude_squared(vec) == 3.0f);
}

// // Sum related tests:

// TEST_CASE("Sum of a vector") {
//     auto vec = Vector3D(1.0f, 2.0f, 3.0f);
//     CHECK(vec.sum() == 6.0f);
// }

// TEST_CASE("Sum of a zero vector") {
//     auto vec = Vector3D::zero();
//     CHECK(vec.sum() == 0.0f);
// }

// TEST_CASE("Sum of an unit vector") {
//     auto vec = Vector3D::unit();
//     CHECK(vec.sum() == 3.0f);
// }

// TEST_CASE("Sum of a negative unit vector") {
//     auto vec = -Vector3D::unit();
//     CHECK(vec.sum() == -3.0f);
// }

// TEST_CASE("Sum with a unit vector") {
//     auto vec = Vector3D(1.0f, 2.0f, 3.0f);
//     CHECK(vec.sum(Vector3D::unit()) == 9.0f);
// }

// TEST_CASE("Sum does not change the values in the original vector") {
//     auto vec = Vector3D(1.0f, 2.0f, 3.0f);
//     auto backup = vec;
//     (void)vec.sum();
//     CHECK(vec == backup);
// }

// TEST_CASE("Sum with a zero vector equals self sum") {
//     auto vec = Vector3D(1.0f, 2.0f, 3.0f);
//     CHECK(vec.sum(Vector3D::zero()) == vec.sum());
// }

// TEST_CASE("Sum of an unit vector") {
//     auto vec = Vector3D::unit();
//     CHECK(vec.sum() == 3.0f);
// }

// TEST_CASE("Sum of an unit vector") {
//     auto vec = Vector3D::unit();
//     CHECK(vec.sum() == 3.0f);
// }

// // Ceil related tests:

// TEST_CASE("Ceil method of an arbitrary vector") {
//     auto vec = Vector3D(0.3f, 1.5f, 2.8f);
//     CHECK(vec.ceil() == Vector3D(1.0f, 2.0f, 3.0f));
// }

// TEST_CASE("Ceil method of a zero vector") {
//     CHECK(Vector3D::zero().ceil() == Vector3D::zero());
// }

// TEST_CASE("Ceil method of a unit vector") {
//     CHECK(Vector3D::unit().ceil() == Vector3D::unit());
// }

// TEST_CASE("Ceil method of a negative unit vector") {
//     CHECK((-Vector3D::unit()).ceil() == -Vector3D::unit());
// }

// TEST_CASE("Ceil method with copy of an arbitrary const vector") {
//     const auto vec = Vector3D(0.3f, 1.5f, 2.8f);
//     Vector3D res = vec.ceiled();
//     CHECK(res == Vector3D(1.0f, 2.0f, 3.0f));
// }

// TEST_CASE("Ceil method with copy of an arbitrary vector") {
//     auto original_vec = Vector3D(0.3f, 1.5f, 2.8f);
//     const auto vec = original_vec;
//     Vector3D res = vec.ceiled();
//     CHECK(res == Vector3D(1.0f, 2.0f, 3.0f));
//     CHECK(vec == original_vec);
// }

// TEST_CASE("Ceil function of an arbitrary vector") {
//     auto vec = Vector3D(0.3f, 1.5f, 2.8f);
//     CHECK(ceil(vec) == Vector3D(1.0f, 2.0f, 3.0f));
// }

// TEST_CASE("Ceil function of a zero vector") {
//     CHECK(ceil(Vector3D::zero()) == Vector3D::zero());
// }

// TEST_CASE("Ceil function of a unit vector") {
//     CHECK(ceil(Vector3D::unit()) == Vector3D::unit());
// }

// TEST_CASE("Ceil function of a unit vector") {
//     CHECK(ceil(-Vector3D::unit()) == -Vector3D::unit());
// }

// TEST_CASE("Ceil method of an arbitrary negative vector") {
//     auto vec = Vector3D(-0.3f, -1.5f, -2.8f);
//     CHECK(vec.ceil() == Vector3D(-0.0f, -1.0f, -2.0f));
// }

// TEST_CASE("Ceil method with copy of an arbitrary negative vector") {
//     auto original_vec = Vector3D(-0.3f, -1.5f, -2.8f);
//     const auto vec = original_vec;
//     Vector3D res = vec.ceiled();
//     CHECK(res == Vector3D(-0.0f, -1.0f, -2.0f));
//     CHECK(vec == original_vec);
// }

// TEST_CASE("Ceil function of an arbitrary negative vector") {
//     auto vec = Vector3D(-0.3f, -1.5f, -2.8f);
//     CHECK(ceil(vec) == Vector3D(-0.0f, -1.0f, -2.0f));
// }

// TEST_CASE("Ceil function of does not change original vector") {
//     auto original_vec = Vector3D(0.3f, 1.5f, 2.8f);
//     auto vec = original_vec;
//     CHECK(ceil(vec) == Vector3D(1.0f, 2.0f, 3.0f));
//     CHECK(vec == original_vec);
// }

// // floor related tests:

// TEST_CASE("Floor method of an arbitrary vector") {
//     auto vec = Vector3D(0.3f, 1.5f, 2.8f);
//     CHECK(vec.floor() == Vector3D(0.0f, 1.0f, 2.0f));
// }

// TEST_CASE("Floor method of a zero vector") {
//     CHECK(Vector3D::zero().floor() == Vector3D::zero());
// }

// TEST_CASE("Floor method of a unit vector") {
//     CHECK(Vector3D::unit().floor() == Vector3D::unit());
// }

// TEST_CASE("Floor method of a negative unit vector") {
//     CHECK((-Vector3D::unit()).floor() == -Vector3D::unit());
// }

// TEST_CASE("Floor method with copy of an arbitrary const vector") {
//     const auto vec = Vector3D(0.3f, 1.5f, 2.8f);
//     Vector3D res = vec.floored();
//     CHECK(res == Vector3D(0.0f, 1.0f, 2.0f));
// }

// TEST_CASE("Floor method with copy of an arbitrary vector") {
//     auto original_vec = Vector3D(0.3f, 1.5f, 2.8f);
//     const auto vec = original_vec;
//     Vector3D res = vec.floored();
//     CHECK(res == Vector3D(0.0f, 1.0f, 2.0f));
//     CHECK(vec == original_vec);
// }

// TEST_CASE("Floor function of an arbitrary vector") {
//     auto vec = Vector3D(0.3f, 1.5f, 2.8f);
//     CHECK(floor(vec) == Vector3D(0.0f, 1.0f, 2.0f));
// }

// TEST_CASE("Floor function of a zero vector") {
//     CHECK(floor(Vector3D::zero()) == Vector3D::zero());
// }

// TEST_CASE("Floor function of a unit vector") {
//     CHECK(floor(Vector3D::unit()) == Vector3D::unit());
// }

// TEST_CASE("Floor function of a unit vector") {
//     CHECK(floor(-Vector3D::unit()) == -Vector3D::unit());
// }

// TEST_CASE("Floor method of an arbitrary negative vector") {
//     auto vec = Vector3D(-0.3f, -1.5f, -2.8f);
//     CHECK(vec.floor() == Vector3D(-1.0f, -2.0f, -3.0f));
// }

// TEST_CASE("Floor method with copy of an arbitrary negative vector") {
//     auto original_vec = Vector3D(-0.3f, -1.5f, -2.8f);
//     const auto vec = original_vec;
//     Vector3D res = vec.floored();
//     CHECK(res == Vector3D(-1.0f, -2.0f, -3.0f));
//     CHECK(vec == original_vec);
// }

// TEST_CASE("Floor function of an arbitrary negative vector") {
//     auto vec = Vector3D(-0.3f, -1.5f, -2.8f);
//     CHECK(floor(vec) == Vector3D(-1.0f, -2.0f, -3.0f));
// }

// TEST_CASE("Floor function of does not change original vector") {
//     auto original_vec = Vector3D(0.3f, 1.5f, 2.8f);
//     auto vec = original_vec;
//     CHECK(floor(vec) == Vector3D(0.0f, 1.0f, 2.0f));
//     CHECK(vec == original_vec);
// }

// // Round related tests:

// TEST_CASE("Round method of an arbitrary vector") {
//     auto vec = Vector3D(0.3f, 1.5f, 2.8f);
//     CHECK(vec.round() == Vector3D(0.0f, 2.0f, 3.0f));
// }

// TEST_CASE("Round method of a zero vector") {
//     CHECK(Vector3D::zero().round() == Vector3D::zero());
// }

// TEST_CASE("Round method of a unit vector") {
//     CHECK(Vector3D::unit().round() == Vector3D::unit());
// }

// TEST_CASE("Round method of a negative unit vector") {
//     CHECK((-Vector3D::unit()).round() == -Vector3D::unit());
// }

// TEST_CASE("Round method with copy of an arbitrary const vector") {
//     const auto vec = Vector3D(0.3f, 1.5f, 2.8f);
//     Vector3D res = vec.rounded();
//     CHECK(res == Vector3D(0.0f, 2.0f, 3.0f));
// }

// TEST_CASE("Round method with copy of an arbitrary vector") {
//     auto original_vec = Vector3D(0.3f, 1.5f, 2.8f);
//     const auto vec = original_vec;
//     Vector3D res = vec.rounded();
//     CHECK(res == Vector3D(0.0f, 2.0f, 3.0f));
//     CHECK(vec == original_vec);
// }

// TEST_CASE("Round function of an arbitrary vector") {
//     auto vec = Vector3D(0.3f, 1.5f, 2.8f);
//     CHECK(round(vec) == Vector3D(0.0f, 2.0f, 3.0f));
// }

// TEST_CASE("Round function of a zero vector") {
//     CHECK(round(Vector3D::zero()) == Vector3D::zero());
// }

// TEST_CASE("Round function of a unit vector") {
//     CHECK(round(Vector3D::unit()) == Vector3D::unit());
// }

// TEST_CASE("Round function of a unit vector") {
//     CHECK(round(-Vector3D::unit()) == -Vector3D::unit());
// }

// TEST_CASE("Round method of an arbitrary negative vector") {
//     auto vec = Vector3D(-0.3f, -1.5f, -2.8f);
//     CHECK(vec.round() == Vector3D(-0.0f, -2.0f, -3.0f));
// }

// TEST_CASE("Round method with copy of an arbitrary negative vector") {
//     auto original_vec = Vector3D(-0.3f, -1.5f, -2.8f);
//     const auto vec = original_vec;
//     Vector3D res = vec.rounded();
//     CHECK(res == Vector3D(-0.0f, -2.0f, -3.0f));
//     CHECK(vec == original_vec);
// }

// TEST_CASE("Round function of an arbitrary negative vector") {
//     auto vec = Vector3D(-0.3f, -1.5f, -2.8f);
//     CHECK(round(vec) == Vector3D(-0.0f, -2.0f, -3.0f));
// }

// TEST_CASE("Round function of does not change original vector") {
//     auto original_vec = Vector3D(0.3f, 1.5f, 2.8f);
//     auto vec = original_vec;
//     CHECK(round(vec) == Vector3D(0.0f, 2.0f, 3.0f));
//     CHECK(vec == original_vec);
// }

// // Abs related tests:

// TEST_CASE("abs method of an arbitrary vector") {
//     auto vec = Vector3D(0.0f, -1.5f, 2.8f);
//     CHECK(vec.abs() == Vector3D(0.0f, 1.5f, 2.8f));
// }

// TEST_CASE("abs method of a zero vector") {
//     CHECK(Vector3D::zero().abs() == Vector3D::zero());
// }

// TEST_CASE("abs method of a unit vector") {
//     CHECK(Vector3D::unit().abs() == Vector3D::unit());
// }

// TEST_CASE("abs method of a negative unit vector") {
//     CHECK((-Vector3D::unit()).abs() == Vector3D::unit());
// }

// TEST_CASE("abs method with copy of an arbitrary const vector") {
//     const auto vec = Vector3D(0.0f, -1.5f, 2.8f);
//     Vector3D res = vec.absed();
//     CHECK(res == Vector3D(0.0f, 1.5f, 2.8f));
// }

// TEST_CASE("abs method with copy of an arbitrary vector") {
//     const auto original_vec = Vector3D(0.0f, -1.5f, 2.8f);
//     const auto vec = original_vec;
//     Vector3D res = vec.absed();
//     CHECK(res == Vector3D(0.0f, 1.5f, 2.8f));
//     CHECK(vec == original_vec);
// }

// TEST_CASE("abs function of an arbitrary vector") {
//     auto vec = Vector3D(0.0f, -1.5f, 2.8f);
//     CHECK(abs(vec) == Vector3D(0.0f, 1.5f, 2.8f));
// }

// TEST_CASE("abs function of a zero vector") {
//     CHECK(abs(Vector3D::zero()) == Vector3D::zero());
// }

// TEST_CASE("abs function of a unit vector") {
//     CHECK(abs(Vector3D::unit()) == Vector3D::unit());
// }

// TEST_CASE("abs function of a unit vector") {
//     CHECK(abs(-Vector3D::unit()) == Vector3D::unit());
// }

// TEST_CASE("abs function of does not change original vector") {
//     auto original_vec = Vector3D(0.0f, -1.5f, 2.8f);
//     auto vec = original_vec;
//     CHECK(abs(vec) == Vector3D(0.0f, 1.5f, 2.8f));
//     CHECK(vec == original_vec);
// }

// // Clamp related tests:

// TEST_CASE("Clamp of arbitrary vector") {
//     auto vec = Vector3D(0.9f, 2.0f, 3.0f);
//     CHECK(vec.clamp(1.0f, 2.0f) == Vector3D(1.0f, 2.0f, 2.0f));
// }

// TEST_CASE("Clamp of arbitrary vector with a copy") {
//     const auto vec = Vector3D(0.9f, 2.0f, 3.0f);
//     auto res = vec.clamped(1.0f, 2.0f);
//     CHECK(res == Vector3D(1.0f, 2.0f, 2.0f));
// }

// TEST_CASE("Clamp of arbitrary vector with same values") {
//     auto vec = Vector3D(0.9f, 2.0f, 3.0f);
//     CHECK(vec.clamp(1.0f, 1.0f) == Vector3D(1.0f, 1.0f, 1.0f));
// }

// TEST_CASE("Clamp of arbitrary vector with negative values") {
//     auto vec = Vector3D(0.9f, 2.0f, 3.0f);
//     CHECK(vec.clamp(-1.0f, -2.0f) == -(2 * Vector3D::unit()));
// }

// TEST_CASE("Clamp of arbitrary vector with negative min but positive max") {
//     auto vec = Vector3D(0.9f, 2.0f, 3.0f);
//     CHECK(vec.clamp(-1.0f, 0.0f) == Vector3D::zero());
// }

// TEST_CASE("Clamp of zero vector with zero clamp") {
//     CHECK(Vector3D::zero().clamp(0.0f, 2.0f) == Vector3D::zero());
// }

// TEST_CASE("Clamp of zero vector with non zero clamp") {
//     CHECK(Vector3D::zero().clamp(1.0f, 2.0f) == Vector3D::unit());
// }

// TEST_CASE("Clamp of negative unit vector") {
//     CHECK((-Vector3D::unit()).clamp(0.0f, 1.0f) == Vector3D::zero());
// }

// TEST_CASE("Clamp equality between function and method") {
//     CHECK(clamp(Vector3D::unit(), 0.0f, 0.9f) == Vector3D::unit().clamp(0.0f,
//     0.9f));
// }

// TEST_CASE("Clamp function of arbitrary vector") {
//     auto vec = Vector3D(0.9f, 2.0f, 3.0f);
//     CHECK(clamp(vec, 1.0f, 2.0f) == Vector3D(1.0f, 2.0f, 2.0f));
// }

// TEST_CASE("Clamp function of arbitrary vector with same values") {
//     auto vec = Vector3D(0.9f, 2.0f, 3.0f);
//     CHECK(clamp(vec, 1.0f, 1.0f) == Vector3D(1.0f, 1.0f, 1.0f));
// }

// TEST_CASE("Clamp function of arbitrary vector with negative values") {
//     auto vec = Vector3D(0.9f, 2.0f, 3.0f);
//     CHECK(clamp(vec, -1.0f, -2.0f) == -(2 * Vector3D::unit()));
// }

// TEST_CASE(
//     "Clamp function of arbitrary vector with negative min but positive max"
// ) {
//     auto vec = Vector3D(0.9f, 2.0f, 3.0f);
//     CHECK(clamp(vec, -1.0f, 0.0f) == Vector3D::zero());
// }

// TEST_CASE("Clamp function of zero vector with zero clamp") {
//     CHECK(clamp(Vector3D::zero(), 0.0f, 2.0f) == Vector3D::zero());
// }

// TEST_CASE("Clamp function of zero vector with non zero clamp") {
//     CHECK(clamp(Vector3D::zero(), 1.0f, 2.0f) == Vector3D::unit());
// }

// TEST_CASE("Clamp function of negative unit vector") {
//     CHECK(clamp(-Vector3D::unit(), 0.0f, 1.0f) == Vector3D::zero());
// }

// TEST_CASE("Clamp function does not change the original vector") {
//     auto original_vec = Vector3D(0.0f, -1.5f, 2.8f);
//     auto vec = original_vec;
//     CHECK(clamp(vec, -1.0f, 0.0f) == Vector3D(0.0f, -1.0f, 0.0f));
//     CHECK(vec == original_vec);
// }

// Norm related tests:

TEST_CASE("Norm of arbitrary vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    CHECK(vec.norm() == doctest::Approx(std::sqrt(14.0f)));
}

TEST_CASE("Norm is basically an alias to magnitude") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    const auto cvec = vec;
    CHECK(vec.norm() == vec.magnitude());
    CHECK(cvec.norm() == cvec.magnitude());
    CHECK(norm(vec) == magnitude(vec));
}

TEST_CASE("Norm method does not change the values in the original vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    auto backup = vec;
    (void)vec.norm();
    CHECK(vec == backup);
}

TEST_CASE("Norm of a zero vector") {
    auto vec = Vector3D::zero();
    CHECK(vec.norm() == doctest::Approx(std::sqrt(0.0f)));
}

TEST_CASE("Norm of an unit vector") {
    auto vec = Vector3D::unit();
    CHECK(vec.norm() == doctest::Approx(std::sqrt(3.0f)));
}

TEST_CASE("Norm of a negative unit vector") {
    auto vec = -Vector3D::unit();
    CHECK(vec.norm() == doctest::Approx(std::sqrt(3.0f)));
}

TEST_CASE("Norm function of arbitrary vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    CHECK(norm(vec) == doctest::Approx(std::sqrt(14.0f)));
}

TEST_CASE("Norm function does not change the values in the original vector") {
    auto vec = Vector3D(1.0f, 2.0f, 3.0f);
    auto backup = vec;
    (void)norm(vec);
    CHECK(vec == backup);
}

TEST_CASE("Norm function of a zero vector") {
    auto vec = Vector3D::zero();
    CHECK(norm(vec) == doctest::Approx(std::sqrt(0.0f)));
}

TEST_CASE("Norm function of an unit vector") {
    auto vec = Vector3D::unit();
    CHECK(norm(vec) == doctest::Approx(std::sqrt(3.0f)));
}

TEST_CASE("Norm function of a negative unit vector") {
    auto vec = -Vector3D::unit();
    CHECK(norm(vec) == doctest::Approx(std::sqrt(3.0f)));
}

// Cross product related tests:

TEST_CASE("Cross product between arbitrary vectors") {
    const auto vec1 = Vector3D(2.0f, 3.0f, 4.0f);
    const auto vec2 = Vector3D(5.0f, 6.0f, 7.0f);
    const auto expected = Vector3D(-3.0f, 6.0f, -3.0f);
    CHECK(vec1.cross(vec2) == expected);
}

TEST_CASE(
    "Cross product of two parallel vectors should be equal to zero vector"
) {
    CHECK(Vector3D::unit().cross(Vector3D::unit()) == Vector3D::zero());
    CHECK(-Vector3D::unit().cross(Vector3D::unit()) == Vector3D::zero());
    CHECK(Vector3D::unit().cross(-Vector3D::unit()) == Vector3D::zero());
    CHECK(-Vector3D::unit().cross(-Vector3D::unit()) == Vector3D::zero());
}

TEST_CASE("Cross function should return the same value as cross method") {
    auto vec1 = Vector3D(1.0f, 2.0f, 3.0f);
    auto vec2 = Vector3D(3.0f, 2.0f, 1.0f);
    CHECK(cross(vec1, vec2) == vec1.cross(vec2));
}

TEST_CASE("Switching of sides of the cross product should produce negation of "
          "result") {
    auto vec1 = Vector3D(1.0f, 2.0f, 3.0f);
    auto vec2 = Vector3D(3.0f, 2.0f, 1.0f);
    CHECK(vec1.cross(vec2) == -vec2.cross(vec1));
}

TEST_CASE(
    "Rotating around the same perpendicular vector should return said vector"
) {
    auto expected = Vector3D(0.0f, -1.0f, 0.0f);
    CHECK(Vector3D(1, 0, 0).cross(Vector3D(0, 0, 1)) == expected);
    CHECK(Vector3D(0, 0, 1).cross(Vector3D(-1, 0, 0)) == expected);
    CHECK(Vector3D(-1, 0, 0).cross(Vector3D(0, 0, -1)) == expected);
    CHECK(Vector3D(0, 0, -1).cross(Vector3D(1, 0, 0)) == expected);
}

// Normalize related tests:

TEST_CASE("Testing what it can do") {
    std::cout << Vector3D::unit().normalize() << std::endl;
    std::cout << (3 * Vector3D::unit()).normalize() << std::endl;
    std::cout << ((Vector3D(1, 0, 1))).normalize() << std::endl;
}

// Vector comparison

TEST_CASE("Unit vector is bigger than zero") {
    CHECK(Vector3D::unit() > Vector3D::zero());
}

// Predicates related tests:

TEST_CASE("is_parallel with two parallel vectors") { }

TEST_CASE("is_parallel with two vectors that are not parallel") { }

TEST_SUITE_END();
