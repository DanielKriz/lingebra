#ifndef DK_MATH_VECTOR_3D_HPP
#define DK_MATH_VECTOR_3D_HPP

#include <ostream>

#include <dklib/math/concepts.hpp>
#include <dklib/math/types.hpp>
#include <dklib/math/vector.hpp>
#include <dklib/math/vector_concepts.hpp>

namespace dk::math {

template <Numeric T = real>
class Vector3 : public Vector<T, 3> {
public:
    using Base = Vector<T, 3>;

    constexpr Vector3() = default;
    constexpr Vector3(T value)
        : Base(value) {};
    constexpr Vector3(T x, T y, T z)
        : Base({ x, y, z }) {};
    constexpr Vector3(std::array<T, 3> elems)
        : Base(elems) {};
    explicit constexpr Vector3(const Base &base)
        : Base(base) {};

    DK_INIT_METHOD Vector3 unit() noexcept { return { 1 }; };
    DK_INIT_METHOD Vector3 zero() noexcept { return { 0 }; };

    DK_INIT_METHOD Vector3 x_axis() noexcept { return { 1.0f, 0.0f, 0.0f }; }

    DK_INIT_METHOD Vector3 y_axis() noexcept { return { 0.0f, 1.0f, 0.0f }; }

    DK_INIT_METHOD Vector3 z_axis() noexcept { return { 0.0f, 0.0f, 1.0f }; }

    DK_INIT_METHOD Vector3 x_axis(const Vector3 &vec) noexcept {
        return { vec.get_x(), 0.0f, 0.0f };
    }

    DK_INIT_METHOD Vector3 y_axis(const Vector3 &vec) noexcept {
        return { 0.0f, vec.get_y(), 0.0f };
    }

    DK_INIT_METHOD Vector3 z_axis(const Vector3 &vec) noexcept {
        return { 0.0f, 0.0f, vec.get_z() };
    }

    [[nodiscard]] constexpr T get_x() const noexcept { return (*this)[0]; }
    [[nodiscard]] constexpr T get_y() const noexcept { return (*this)[1]; }
    [[nodiscard]] constexpr T get_z() const noexcept { return (*this)[2]; }

    constexpr void set_x(T value) noexcept { (*this)[0] = value; }
    constexpr void set_y(T value) noexcept { (*this)[1] = value; }
    constexpr void set_z(T value) noexcept { (*this)[2] = value; }

    constexpr Vector3 operator-() const noexcept {
        return { -get_x(), -get_y(), -get_z() };
    }

    constexpr Vector3 &operator+=(const Vector3 &other) noexcept {
        (*this)[0] += other.get_x();
        (*this)[1] += other.get_y();
        (*this)[2] += other.get_z();
        return *this;
    }
    constexpr Vector3 &operator-=(const Vector3 &other) noexcept {
        (*this)[0] -= other.get_x();
        (*this)[1] -= other.get_y();
        (*this)[2] -= other.get_z();
        return *this;
    }
    constexpr Vector3 &operator*=(const Vector3 &other) noexcept {
        (*this)[0] *= other.get_x();
        (*this)[1] *= other.get_y();
        (*this)[2] *= other.get_z();
        return *this;
    }
    constexpr Vector3 &operator/=(const Vector3 &other) {
        if (std::any_of(other.elems_.cbegin(), other.elems_.cend(), [](auto v) { return v == 0; })) {
            throw std::runtime_error("Division by zero");
        }
        (*this)[0] /= other.get_x();
        (*this)[1] /= other.get_y();
        (*this)[2] /= other.get_z();
        return *this;
    }

    template <std::convertible_to<T> T1>
    constexpr Vector3 &operator*=(T1 value) noexcept {
        (*this)[0] *= value;
        (*this)[1] *= value;
        (*this)[2] *= value;
        return *this;
    }

    template <std::convertible_to<T> T1>
    constexpr Vector3 &operator/=(T1 value) {
        if (value == 0) {
            throw std::runtime_error("Division by zero");
        }
        (*this)[0] /= value;
        (*this)[1] /= value;
        (*this)[2] /= value;
        return *this;
    }

    friend constexpr bool operator==(const Vector3 &lhs, const Vector3 &rhs) noexcept {
        return lhs.elems_ == rhs.elems_;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const Vector3 &vec) noexcept {
        return os << '(' << vec.get_x() << ", " << vec.get_y() << ", "
                  << vec.get_z() << ')';
    }

    constexpr Vector3 cross(const Vector3 &other) const noexcept {
        Vector3 res = {
            this->get_y() * other.get_z() - this->get_z() * other.get_y(),
            this->get_z() * other.get_x() - this->get_x() * other.get_z(),
            this->get_x() * other.get_y() - this->get_y() * other.get_x()
        };
        // We are doing this to avoid having negative zero in the result.
        return res + Vector3::zero();
    }
    friend Vector3 cross(const Vector3 &lhs, const Vector3 &rhs) noexcept {
        return lhs.cross(rhs);
    }
};

template <Numeric T>
struct is_vector_type<Vector3<T>> : std::true_type { };

using Vector3D = Vector3<real>;

} // namespace dk::math

#endif // DK_MATH_VECTOR_3D_HPP
