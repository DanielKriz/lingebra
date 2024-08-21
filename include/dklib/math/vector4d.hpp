#ifndef DK_MATH_VECTOR_4D_HPP
#define DK_MATH_VECTOR_4D_HPP

#include <algorithm>
#include <ostream>

#include <dklib/math/concepts.hpp>
#include <dklib/math/types.hpp>
#include <dklib/math/vector.hpp>

namespace dk::math {

template <Numeric T = real>
class Vector4 : public Vector<T, 4> {
public:
    using Base = Vector<T, 4>;

    constexpr Vector4() = default;
    constexpr Vector4(T value)
        : Base(value) {};
    constexpr Vector4(std::array<T, 4> elems)
        : Base(elems) {};
    constexpr Vector4(T x, T y, T z, T w)
        : Base({ x, y, z, w }) {};
    explicit constexpr Vector4(const Base &base)
        : Base(base) {};

    DK_INIT_METHOD Vector4 unit() noexcept { return { 1 }; };
    DK_INIT_METHOD Vector4 zero() noexcept { return { 0 }; };

    [[nodiscard]] constexpr T get_x() const noexcept { return (*this)[0]; }
    [[nodiscard]] constexpr T get_y() const noexcept { return (*this)[1]; }
    [[nodiscard]] constexpr T get_z() const noexcept { return (*this)[2]; }
    [[nodiscard]] constexpr T get_w() const noexcept { return (*this)[3]; }

    [[nodiscard]] constexpr T &get_x() noexcept { return (*this)[0]; }
    [[nodiscard]] constexpr T &get_y() noexcept { return (*this)[1]; }
    [[nodiscard]] constexpr T &get_z() noexcept { return (*this)[2]; }
    [[nodiscard]] constexpr T &get_w() noexcept { return (*this)[3]; }

    constexpr void set_x(T value) noexcept { (*this)[0] = value; }
    constexpr void set_y(T value) noexcept { (*this)[1] = value; }
    constexpr void set_z(T value) noexcept { (*this)[2] = value; }
    constexpr void set_w(T value) noexcept { (*this)[3] = value; }

    constexpr Vector4 &operator-() noexcept {
        (*this)[0] = -(*this)[0];
        (*this)[1] = -(*this)[1];
        (*this)[2] = -(*this)[2];
        (*this)[3] = -(*this)[3];
        return *this;
    };

    constexpr Vector4 &operator+=(const Vector4 &other) noexcept {
        this->get_x() += other.get_x();
        this->get_y() += other.get_y();
        this->get_z() += other.get_z();
        this->get_w() += other.get_w();
        return *this;
    };
    constexpr Vector4 &operator-=(const Vector4 &other) noexcept {
        (*this)[0] -= other.get_x();
        (*this)[1] -= other.get_y();
        (*this)[2] -= other.get_z();
        (*this)[3] -= other.get_w();
        return *this;
    }
    constexpr Vector4 &operator*=(const Vector4 &other) noexcept {
        (*this)[0] *= other.get_x();
        (*this)[1] *= other.get_y();
        (*this)[2] *= other.get_z();
        (*this)[3] *= other.get_w();
        return *this;
    }
    constexpr Vector4 &operator/=(const Vector4 &other) {
        if (std::any_of(other.elems_.cbegin(), other.elems_.cend(), [](auto v) { return v == 0; })) {
            throw std::runtime_error("Division by zero");
        }
        (*this)[0] /= other.get_x();
        (*this)[1] /= other.get_y();
        (*this)[2] /= other.get_z();
        (*this)[3] /= other.get_w();
        return *this;
    }

    template <std::convertible_to<T> T1>
    constexpr Vector4 &operator*=(T1 value) noexcept {
        (*this)[0] *= value;
        (*this)[1] *= value;
        (*this)[2] *= value;
        (*this)[3] *= value;
        return *this;
    }

    template <std::convertible_to<T> T1>
    constexpr Vector4 &operator/=(T1 value) {
        if (value == 0) {
            throw std::runtime_error("Division by zero");
        }
        (*this)[0] /= value;
        (*this)[1] /= value;
        (*this)[2] /= value;
        (*this)[3] /= value;
        return *this;
    }

    friend constexpr bool operator==(const Vector4 &lhs, const Vector4 &rhs) noexcept {
        return lhs.elems_ == rhs.elems_;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const Vector4 &vec) noexcept {
        return os << '(' << vec.get_x() << ", " << vec.get_y() << ", "
                  << vec.get_z() << ", " << vec.get_w() << ')';
    }
};

template <Numeric T>
struct is_vector_type<Vector4<T>> : std::true_type { };

using Vector4D = Vector4<real>;

} // namespace dk::math

#endif // DK_MATH_VECTOR_4D_HPP
