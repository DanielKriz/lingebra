#ifndef DK_MATH_MATRIX_2D_HPP
#define DK_MATH_MATRIX_2D_HPP

#include <ostream>

#include <dklib/math/concepts.hpp>
#include <dklib/math/matrix.hpp>
#include <dklib/math/tensor.hpp>
#include <dklib/math/types.hpp>

namespace dk::math {

template <Numeric T = real>
class Matrix2 : public Matrix<T, 2, 2> {
public:
    using Base = Matrix<T, 2, 2>;
    using arr_type = std::array<T, 2>;

    constexpr Matrix2() = default;

    explicit constexpr Matrix2(const Base &base)
        : Base(base) {};

    constexpr Matrix2(const arr_type &x, const arr_type &y)
        : Base({ x, y }) {};

    DK_INIT_METHOD Matrix2 zero() noexcept { return { 0 }; }

    DK_INIT_METHOD Matrix2 unit() noexcept { return { 1 }; }

    DK_INIT_METHOD Matrix2 diagonal() noexcept { return {}; }

    DK_INIT_METHOD Matrix2 diagonal(Base::vector_type vec) noexcept {
        return {};
    }

    DK_INIT_METHOD Matrix2
    diagonal(Base::storage_type_diagonal values) noexcept {
        return {};
    }

    DK_INIT_METHOD Matrix2 anti_diagonal() noexcept { return {}; }

    DK_INIT_METHOD Matrix2 anti_diagonal(Base::vector_type vec) noexcept {
        return {};
    }

    DK_INIT_METHOD Matrix2
    anti_diagonal(Base::storage_type_diagonal values) noexcept {
        return {};
    }

    [[nodiscard]] constexpr double determinant() const noexcept;

    friend constexpr double determinant(const Matrix2 &mat) noexcept {
        return mat.determinant();
    }

    constexpr Matrix2 &operator-() noexcept;

    constexpr Matrix2 &operator+=(const Matrix2 &other) noexcept;
    constexpr Matrix2 &operator-=(const Matrix2 &other) noexcept;
    constexpr Matrix2 &operator*=(const Matrix2 &other) noexcept;
    constexpr Matrix2 &operator/=(const Matrix2 &other) noexcept;

    template <std::convertible_to<T> T1>
    constexpr Matrix2 &operator*=(T1 value) noexcept;

    template <std::convertible_to<T> T1>
    constexpr Matrix2 &operator/=(T value) noexcept;

    constexpr Matrix2 transpose() noexcept {
        const auto &self = *this;
        return {
            { self[0], self[2] },
            { self[1], self[3] },
        };
    }

    friend constexpr bool operator==(const Matrix2 &lhs, const Matrix2 &rhs) noexcept {
        return lhs.elems_ == rhs.elems_;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const Matrix2 &vec) noexcept {
        return os;
    }
};

using Matrix2D = Matrix2<real>;

} // namespace dk::math

#endif // DK_MATH_MATRIX_2D_HPP
