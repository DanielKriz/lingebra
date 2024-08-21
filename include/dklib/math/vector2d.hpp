#ifndef DK_MATH_VECTOR_2D_HPP
#define DK_MATH_VECTOR_2D_HPP

#include <ostream>

#include <dklib/math/concepts.hpp>
#include <dklib/math/types.hpp>
#include <dklib/math/vector.hpp>
#include <dklib/math/vector_concepts.hpp>

namespace dk::math {

template <Numeric T = real>
class Vector2 : public Vector<T, 2> {
public:
    using Base = Vector<T, 2>;

    constexpr Vector2() = default;
    constexpr Vector2(T value)
        : Base(value) {};
    constexpr Vector2(T x, T y)
        : Base({ x, y }) {};
    constexpr Vector2(std::array<T, 2> elems)
        : Base(elems) {};
    explicit constexpr Vector2(const Base &base)
        : Base(base) {};

    // template <class C>
    // requires std::is_base_of_v<C, Vector2>
    // explicit constexpr Vector2(const C &base)
    //     : C(base) {};

    DK_INIT_METHOD Vector2 unit() noexcept { return { 1 }; };
    DK_INIT_METHOD Vector2 zero() noexcept { return { 0 }; };

    [[nodiscard]] constexpr T get_x() const noexcept { return (*this)[0]; }
    [[nodiscard]] constexpr T get_y() const noexcept { return (*this)[1]; }

    constexpr void set_x(T value) noexcept { (*this)[0] = value; }
    constexpr void set_y(T value) noexcept { (*this)[1] = value; }

    constexpr Vector2 &operator-() noexcept {
        set_x(-get_x());
        set_y(-get_y());
        return *this;
    }

    constexpr Vector2 &operator+=(const Vector2 &other) noexcept {
        (*this)[0] += other.get_x();
        (*this)[1] += other.get_y();
        return *this;
    }
    constexpr Vector2 &operator-=(const Vector2 &other) noexcept {
        (*this)[0] -= other.get_x();
        (*this)[1] -= other.get_y();
        return *this;
    }
    constexpr Vector2 &operator*=(const Vector2 &other) noexcept {
        (*this)[0] *= other.get_x();
        (*this)[1] *= other.get_y();
        return *this;
    }
    constexpr Vector2 &operator/=(const Vector2 &other) {
        if (other.get_x() == 0 or other.get_y() == 0) {
            throw std::runtime_error("Division by zero");
        }
        (*this)[0] /= other.get_x();
        (*this)[1] /= other.get_y();
        return *this;
    }

    template <std::convertible_to<T> T1>
    constexpr Vector2 &operator*=(T1 value) noexcept {
        (*this)[0] *= value;
        (*this)[1] *= value;
        return *this;
    };

    template <std::convertible_to<T> T1>
    constexpr Vector2 &operator/=(T1 value) {
        if (value == 0) {
            throw std::runtime_error("Division by zero");
        }
        (*this)[0] *= value;
        (*this)[1] *= value;
        return *this;
    }

    friend constexpr bool operator==(const Vector2 &lhs, const Vector2 &rhs) noexcept {
        return lhs.elems_ == rhs.elems_;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const Vector2 &vec) noexcept {
        return os << '(' << vec.get_x() << ", " << vec.get_y() << ')';
    }

private:
};

template <Numeric T>
struct is_vector_type<Vector2<T>> : std::true_type { };

using Vector2D = Vector2<real>;

} // namespace dk::math

#endif // DK_MATH_VECTOR_2D_HPP
