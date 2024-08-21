#ifndef DK_MATH_MATRIX_3D_HPP
#define DK_MATH_MATRIX_3D_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <ostream>

#include <dklib/math/concepts.hpp>
#include <dklib/math/matrix_concepts.hpp>
#include <dklib/math/types.hpp>
#include <dklib/math/vector.hpp>

namespace dk::math {

template <Numeric T = real>
class Matrix3 : public Matrix<T, 3, 3> {
public:
    using Base = Matrix<T, 3, 3>;
    using arr_type = std::array<T, 3>;

    constexpr Matrix3() = default;
    constexpr Matrix3(T value)
        : Base(value) {};
    explicit constexpr Matrix3(const Base &base)
        : Base(base) {};
    explicit constexpr Matrix3(const Base::storage_type_2d &values)
        : Base(values) {};

    constexpr Matrix3(const arr_type &x, const arr_type &y, const arr_type &z)
        : Base({ x, y, z }) {};

    DK_INIT_METHOD Matrix3 zero() noexcept { return { 0 }; }

    DK_INIT_METHOD Matrix3 unit() noexcept { return { 1 }; }

    DK_INIT_METHOD Matrix3
    diagonal(const Base::storage_type_diagonal &values) noexcept {
        return {
            { values[0], 0, 0 },
            { 0, values[1], 0 },
            { 0, 0, values[2] },
        };
    }

    DK_INIT_METHOD Matrix3 diagonal(T value) noexcept {
        return diagonal({ value, value, value });
    }

    DK_INIT_METHOD Matrix3 diagonal(const Base::vector_type &vec) noexcept {
        return diagonal({ vec[0], vec[1], vec[2] });
    }

    DK_INIT_METHOD Matrix3
    anti_diagonal(const Base::storage_type_diagonal &values) noexcept {
        return {
            { 0, 0, values[0] },
            { 0, values[1], 0 },
            { values[2], 0, 0 },
        };
    }

    DK_INIT_METHOD Matrix3 anti_diagonal(T value) noexcept {
        return anti_diagonal({ value, value, value });
    }

    DK_INIT_METHOD Matrix3
    anti_diagonal(const Base::vector_type &vec) noexcept {
        return anti_diagonal({ vec[0], vec[1], vec[2] });
    }

    DK_INIT_METHOD Matrix3 identity() noexcept { return diagonal(1); }

    DK_INIT_METHOD Matrix3 translate() noexcept { return {}; }

    DK_INIT_METHOD Matrix3 rotation() noexcept { return {}; }

    DK_INIT_METHOD Matrix3 scale() noexcept { return {}; }

    DK_INIT_METHOD Matrix3 skew() noexcept { return {}; }

    DK_INIT_METHOD Matrix3 projection() noexcept { return {}; }

    DK_INIT_METHOD Matrix3 reflect() noexcept { return {}; }

    DK_INIT_METHOD Matrix3 retract() noexcept { return {}; }

    [[nodiscard]] constexpr double determinant() const noexcept;

    friend constexpr double determinant(const Matrix3 &mat) noexcept {
        return mat.determinant();
    }

    constexpr Matrix3 &operator-() noexcept;

    constexpr Matrix3 &operator+=(const Matrix3 &other) noexcept {
        std::ranges::transform(this->elems_, other.elems_, this->elems_.begin(), std::plus<T>());
        return *this;
    }

    constexpr Matrix3 &operator-=(const Matrix3 &other) noexcept;

    constexpr Matrix3 &operator*=(const Matrix3 &other) noexcept {
        Matrix3 result_matrix { 0 };
        for (std::size_t i = 0; i < 3; ++i) {
            for (std::size_t j = 0; j < 3; ++j) {
                for (std::size_t k = 0; k < 3; ++k) {
                    result_matrix[i, j] += (*this)[i, k] * other[k, j];
                }
            }
        }
        *this = result_matrix;
        return *this;
    }
    constexpr Matrix3 &operator/=(const Matrix3 &other) noexcept;

    template <std::convertible_to<T> T1>
    constexpr Matrix3 &operator*=(T1 value) noexcept;

    template <std::convertible_to<T> T1>
    constexpr Matrix3 &operator/=(T value) noexcept;

    constexpr Matrix3 transpose() noexcept {
        const auto &self = *this;
        return {
            { self[0], self[3], self[6] },
            { self[1], self[4], self[7] },
            { self[2], self[5], self[8] },
        };
    }

    friend constexpr bool operator==(const Matrix3 &lhs, const Matrix3 &rhs) noexcept {
        return {};
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const Matrix3 &mat) noexcept {
        os << "(";
        os << "(" << mat[0] << ", " << mat[1] << ", " << mat[2] << "), ";
        os << "(" << mat[3] << ", " << mat[4] << ", " << mat[5] << "), ";
        os << "(" << mat[6] << ", " << mat[7] << ", " << mat[8] << ")";
        os << ")";
        return os;
    }
};

using Matrix3D = Matrix3<real>;

} // namespace dk::math

#endif // DK_MATH_MATRIX_HPP
