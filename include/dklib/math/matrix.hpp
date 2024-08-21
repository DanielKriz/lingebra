#ifndef DK_MATH_MATRIX_HPP
#define DK_MATH_MATRIX_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <ostream>

#include <dklib/math/concepts.hpp>
#include <dklib/math/matrix_concepts.hpp>
#include <dklib/math/tensor.hpp>
#include <dklib/math/types.hpp>
#include <dklib/math/vector.hpp>

namespace dk::math {

template <Numeric T = real, std::size_t Rows = 1, std::size_t Cols = 1>
requires(Rows > 0 and Cols > 0)
class Matrix : public Tensor<T, Rows, Cols> {
public:
    using Base = Tensor<T, Rows, Cols>;
    using vector_type = Vector<T, Rows>;
    using storage_type_2d = std::array<std::array<T, Cols>, Rows>;
    using storage_type_diagonal = std::array<T, Cols>;

    constexpr Matrix() = default;

    constexpr Matrix(T value)
        : Base(value) {};

    explicit constexpr Matrix(const Base &base)
        : Base(base) {};

    explicit constexpr Matrix(const storage_type_2d &values) {
        std::size_t i = 0;
        for (const auto &row : values) {
            for (const auto value : row) {
                this->elems_[i++] = value;
            }
        }
    };

    DK_INIT_METHOD Matrix zero() noexcept { return {}; }

    DK_INIT_METHOD Matrix unit() noexcept { return {}; }

    DK_INIT_METHOD Matrix diagonal() noexcept { return {}; }

    DK_INIT_METHOD Matrix diagonal(vector_type vec) noexcept { return {}; }

    DK_INIT_METHOD Matrix diagonal(storage_type_diagonal values) noexcept {
        return {};
    }

    DK_INIT_METHOD Matrix anti_diagonal() noexcept { return {}; }

    DK_INIT_METHOD Matrix anti_diagonal(vector_type vec) noexcept {
        return {};
    }

    DK_INIT_METHOD Matrix
    anti_diagonal(storage_type_diagonal values) noexcept {
        return {};
    }

    [[nodiscard]] constexpr double determinant() const noexcept;

    friend constexpr double determinant(const Matrix &mat) noexcept {
        return mat.determinant();
    }

    [[nodiscard]] constexpr T &operator[](std::size_t idx) noexcept {
        return this->elems_[idx];
    }

    [[nodiscard]] constexpr T operator[](std::size_t idx) const noexcept {
        return this->elems_[idx];
    }

    [[nodiscard]] constexpr T &operator[](std::size_t x, std::size_t y) noexcept {
        return this->elems_[x * cols() + y];
    }

    [[nodiscard]] constexpr T operator[](std::size_t x, std::size_t y) const noexcept {
        return this->elems_[x * cols() + y];
    }

    [[nodiscard]] constexpr T &at(std::size_t x, std::size_t y) {
        std::size_t offset = x * cols() + y;
        if (offset >= this->size()) {
            throw std::runtime_error("index is out of bounds");
        }
        return this->elems_[x * cols() + y];
    }

    [[nodiscard]] constexpr T at(std::size_t x, std::size_t y) const {
        std::size_t offset = x * cols() + y;
        if (offset >= this->size()) {
            throw std::runtime_error("index is out of bounds");
        }
        return this->elems_[x * cols() + y];
    }

    [[nodiscard]] constexpr T &at(std::size_t idx) {
        if (idx >= this->size()) {
            throw std::runtime_error("index out of bounds");
        }
        return this->elems_[idx];
    };

    [[nodiscard]] constexpr T at(std::size_t idx) const {
        if (idx >= this->size()) {
            throw std::runtime_error("index out of bounds");
        }
        return this->elems_[idx];
    };

    constexpr Matrix &operator-() noexcept {
        std::ranges::for_each(this->elems_, std::negate<T>());
        return *this;
    }

    constexpr Matrix &operator+=(const Matrix &other) noexcept {
        std::ranges::transform(this->elems_, other.elems_, this->elems_.begin(), std::plus<T>());
        return *this;
    }

    constexpr Matrix &operator-=(const Matrix &other) noexcept {
        std::ranges::transform(this->elems_, other.elems_, this->elems_.begin(), std::minus<T>());
        return *this;
    }

    template <std::convertible_to<T> T1>
    constexpr Matrix &operator*=(T1 value) noexcept {
        std::ranges::for_each(this->elems_, [value](auto &v) { v *= value; });
        return *this;
    }

    template <std::convertible_to<T> T1>
    constexpr Matrix &operator/=(T value) noexcept {
        std::ranges::for_each(this->elems_, [value](auto &v) { v /= value; });
        return *this;
    }

    constexpr Matrix<T, Cols, Rows> transpose() noexcept {
        Matrix<T, Cols, Rows> return_matrix;
        for (std::size_t i = 0; i < return_matrix.rows(); ++i) {
            for (std::size_t j = 0; j < return_matrix.cols(); ++j) {
                return_matrix[i, j] = (*this)[j, i];
            }
        }
        return return_matrix;
    }

    [[nodiscard]] constexpr std::size_t rows() const noexcept { return Rows; }
    [[nodiscard]] constexpr std::size_t cols() const noexcept { return Cols; }

    friend constexpr bool operator==(const Matrix &lhs, const Matrix &rhs) noexcept {
        return lhs.elems_ == rhs.elems_;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const Matrix &mat) noexcept {
        os << "(";
        for (std::size_t i = 0; i < mat.size(); ++i) {
            os << mat[i] << ", ";
        }
        os << ")";
        return os;
    }
};

// TODO: use implementation which is not O(n^3)
template <Numeric T, std::size_t Rows1, std::size_t Cols1, std::size_t Rows2, std::size_t Cols2>
requires(Cols1 == Rows2)
constexpr Matrix<T, Rows1, Cols2>
operator*(const Matrix<T, Rows1, Cols1> &lhs, const Matrix<T, Rows2, Cols2> &rhs) noexcept {
    Matrix<T, Rows1, Cols2> result_matrix { 0 };
    for (std::size_t i = 0; i < lhs.rows(); ++i) {
        for (std::size_t j = 0; j < rhs.cols(); ++j) {
            for (std::size_t k = 0; k < rhs.rows(); ++k) {
                result_matrix[i, j] += lhs[i, k] * rhs[k, j];
            }
        }
    }
    return result_matrix;
}

using Matrix2x3 = Matrix<real, 2, 3>;
using Matrix3x2 = Matrix<real, 3, 2>;
using Matrix4x3 = Matrix<real, 4, 3>;
using Matrix3x4 = Matrix<real, 3, 4>;
using Matrix2x4 = Matrix<real, 2, 4>;
using Matrix4x2 = Matrix<real, 4, 2>;

} // namespace dk::math

#endif // DK_MATH_MATRIX_HPP
