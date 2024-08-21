#ifndef DK_MATH_MATRIX_4D_HPP
#define DK_MATH_MATRIX_4D_HPP

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
class Matrix4 : public Matrix<T, 4, 4> {
public:
    using Base = Matrix<T, 4, 4>;
    using arr_type = std::array<T, 4>;

    constexpr Matrix4() = default;
    constexpr Matrix4(T value)
        : Base(value) {};
    explicit constexpr Matrix4(const Base &base)
        : Base(base) {};
    explicit constexpr Matrix4(const Base::storage_type_2d &values)
        : Base(values) {};

    constexpr Matrix4(const arr_type &x, const arr_type &y, const arr_type &z, const arr_type &w)
        : Base({ x, y, z, w }) {};

    DK_INIT_METHOD Matrix4 zero() noexcept { return { 0 }; }

    DK_INIT_METHOD Matrix4 unit() noexcept { return { 1 }; }

    DK_INIT_METHOD Matrix4
    diagonal(const Base::storage_type_diagonal &values) noexcept {
        return {
            { values[0], 0, 0, 0 },
            { 0, values[1], 0, 0 },
            { 0, 0, values[2], 0 },
            { 0, 0, 0, values[3] },
        };
    }

    DK_INIT_METHOD Matrix4 diagonal(T value) noexcept {
        return diagonal({ value, value, value });
    }

    DK_INIT_METHOD Matrix4 diagonal(const Base::vector_type &vec) noexcept {
        return diagonal({ vec[0], vec[1], vec[2] });
    }

    DK_INIT_METHOD Matrix4
    anti_diagonal(const Base::storage_type_diagonal &values) noexcept {
        return anti_diagonal({ values[0], values[1], values[2], values[3] });
    }

    DK_INIT_METHOD Matrix4 anti_diagonal(T value) noexcept {
        return anti_diagonal(value, value, value, value);
    }

    DK_INIT_METHOD Matrix4 anti_diagonal(T x, T y, T z, T w) noexcept {
        return {
            { 0, 0, 0, x },
            { 0, 0, y, 0 },
            { 0, z, 0, 0 },
            { w, 0, 0, 0 },
        };
    }

    DK_INIT_METHOD Matrix4
    anti_diagonal(const Base::vector_type &vec) noexcept {
        return anti_diagonal(vec[0], vec[1], vec[2], vec[3]);
    }

    DK_INIT_METHOD Matrix4 identity() noexcept { return diagonal(1); }

    DK_INIT_METHOD Matrix4 translate() noexcept { return {}; }

    DK_INIT_METHOD Matrix4 rotation() noexcept { return {}; }

    DK_INIT_METHOD Matrix4 scale() noexcept { return {}; }

    DK_INIT_METHOD Matrix4 skew() noexcept { return {}; }

    DK_INIT_METHOD Matrix4 projection() noexcept { return {}; }

    DK_INIT_METHOD Matrix4 reflect() noexcept { return {}; }

    DK_INIT_METHOD Matrix4 retract() noexcept { return {}; }

    [[nodiscard]] constexpr double determinant() const noexcept;

    friend constexpr double determinant(const Matrix4 &mat) noexcept {
        return mat.determinant();
    }

    constexpr Matrix4 &operator-() noexcept;

    constexpr Matrix4 &operator+=(const Matrix4 &other) noexcept {
        std::ranges::transform(this->elems_, other.elems_, this->elems_.begin(), std::plus<T>());
        return *this;
    }

    constexpr Matrix4 &operator-=(const Matrix4 &other) noexcept;

    constexpr Matrix4 &operator*=(const Matrix4 &other) noexcept {
        Matrix4 result_matrix { 0 };
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

    constexpr Matrix4 &operator/=(const Matrix4 &other) noexcept;

    template <std::convertible_to<T> T1>
    constexpr Matrix4 &operator*=(T1 value) noexcept;

    template <std::convertible_to<T> T1>
    constexpr Matrix4 &operator/=(T value) noexcept;

    constexpr Matrix4 transpose() noexcept {
        const auto &self = *this;
        return {};
    }

    friend constexpr bool operator==(const Matrix4 &lhs, const Matrix4 &rhs) noexcept {
        return lhs.elems_ == rhs.elems_;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const Matrix4 &mat) noexcept {
        os << "(";
        os << "(" << mat[0] << ", " << mat[1] << ", " << mat[2] << ", " << mat[3]
           << "), ";
        os << "(" << mat[4] << ", " << mat[5] << ", " << mat[6] << ", " << mat[7]
           << "), ";
        os << "(" << mat[8] << ", " << mat[9] << ", " << mat[10] << ", " << mat[11]
           << "), ";
        os << "(" << mat[12] << ", " << mat[13] << ", " << mat[14] << ", "
           << mat[15] << ")";
        os << ")";
        return os;
    }
};

using Matrix4D = Matrix4<real>;

} // namespace dk::math

#endif // DK_MATH_MATRIX_4D_HPP
