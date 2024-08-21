#ifndef DK_MATH_VECTOR_HPP
#define DK_MATH_VECTOR_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <ostream>
#include <type_traits>

#include <dklib/math/concepts.hpp>
#include <dklib/math/tensor.hpp>
#include <dklib/math/types.hpp>
#include <dklib/math/vector_concepts.hpp>

namespace dk::math {

enum class Dimension {
    x = 0,
    y = 1,
    z = 2,
    w = 3,
};

template <Numeric T = real, std::size_t Dims = 1>
requires(Dims > 0)
class Vector : public Tensor<T, Dims> {
public:
    using Base = Tensor<T, Dims>;

    constexpr Vector() = default;
    constexpr Vector(T value)
        : Base(value) {};
    constexpr Vector(std::array<T, Dims> elems)
        : Base(elems) {};
    explicit constexpr Vector(const Base &base)
        : Base(base) {};

    template <std::convertible_to<T> T1>
    explicit constexpr Vector(const Vector<T1, Dims> &other) {
        for (int i = 0; i < other.size(); ++i) {
            (*this)[i] = static_cast<T>(other[i]);
        }
    };

    DK_INIT_METHOD Vector unit() noexcept { return { 1 }; };
    DK_INIT_METHOD Vector zero() noexcept { return { 1 }; };

    DK_INIT_METHOD Vector get_axis_vector(Dimension axis) {
        auto ret = Vector::zero();
        ret[static_cast<std::size_t>(axis)] = static_cast<T>(1);
        return ret;
    }

    DK_INIT_METHOD Vector get_axis_vector(Dimension axis, const Vector &vec) {
        auto ret = Vector::zero();
        ret[static_cast<std::size_t>(axis)] = vec[static_cast<std::size_t>(axis)];
        return ret;
    }

    DK_INIT_METHOD Vector x_axis() noexcept {
        return get_axis_vector(Dimension::x);
    }

    DK_INIT_METHOD Vector y_axis() noexcept
    requires(Dims > 1)
    {
        return get_axis_vector(Dimension::y);
    }

    DK_INIT_METHOD Vector z_axis() noexcept
    requires(Dims > 2)
    {
        return get_axis_vector(Dimension::z);
    }

    DK_INIT_METHOD Vector x_axis(const Vector &vec) noexcept {
        return get_axis_vector(Dimension::x, vec);
    }

    DK_INIT_METHOD Vector y_axis(const Vector &vec) noexcept(Dims > 1) {
        return get_axis_vector(Dimension::y, vec);
    }

    DK_INIT_METHOD Vector z_axis(const Vector &vec) noexcept(Dims > 2) {
        return get_axis_vector(Dimension::z, vec);
    }

    [[nodiscard]] constexpr bool is_perpendicular(const Vector other) {
        constexpr double EPSILON = 1e-6;
        return std::fabs(dot(other)) < EPSILON;
    }

    [[nodiscard]] constexpr bool is_parallel(const Vector other) {
        constexpr double EPSILON = 1e-6;
        return std::fabs(std::fabs(dot(other)) - static_cast<double>(magnitude() * other.magnitude())) < EPSILON;
    }

    [[nodiscard]] constexpr double magnitude() const noexcept {
        return std::sqrt(magnitude_squared());
    }

    [[nodiscard]] constexpr double magnitude_squared() const noexcept {
        double result = 0;
        std::ranges::for_each(this->elems_, [&result](auto v) {
            result += static_cast<double>(v * v);
        });
        return result;
    }

    template <typename Self>
    [[nodiscard]] constexpr double dot(this const Self &self, const Self &other) noexcept {
        return static_cast<double>(std::inner_product(
            self.elems_.begin(), self.elems_.end(), other.elems_.begin(), T {}
        ));
    }

    [[nodiscard]] constexpr double norm() const noexcept { return magnitude(); }

    template <template <typename, std::size_t> typename Self>
    requires(not std::same_as<std::common_type_t<real, T>, T>)
    constexpr Self<std::common_type_t<real, T>, Dims>
    normalize(this Self<T, Dims> &self) noexcept {
        auto ret = Self<std::common_type_t<real, T>, Dims>(self);
        return ret *= T { 1 } / self.norm();
    }

    template <template <typename> typename Self>
    requires(not std::same_as<std::common_type_t<real, T>, T>)
    constexpr Self<std::common_type_t<real, T>>
    normalize(this Self<T> &self) noexcept {
        auto ret = Self<std::common_type_t<real, T>>(self);
        return ret *= T { 1 } / self.norm();
    }

    template <template <typename, std::size_t> typename Self>
    requires(std::same_as<std::common_type_t<real, T>, T>)
    constexpr Self<T, Dims> &normalize(this Self<T, Dims> &self) noexcept {
        return self *= T { 1 } / self.norm();
    }

    template <template <typename> typename Self>
    requires std::same_as<std::common_type_t<real, T>, T>
    constexpr Self<T> &normalize(this Self<T> &self) noexcept {
        return self *= T { 1 } / self.norm();
    }

    template <template <typename> typename Self>
    requires std::same_as<std::common_type_t<real, T>, T>
    constexpr Self<T> &normalize(this Self<T> &&self) noexcept {
        return self *= T { 1 } / self.norm();
    }

    template <typename Self>
    [[nodiscard]] constexpr Self normalized(this Self self) noexcept {
        return self.normalize();
    }

    constexpr Vector &operator-() noexcept { }

    constexpr Vector &operator+=(const Vector &other) noexcept;
    constexpr Vector &operator-=(const Vector &other) noexcept;
    constexpr Vector &operator*=(const Vector &other) noexcept;
    constexpr Vector &operator/=(const Vector &other) noexcept;

    template <std::convertible_to<T> T1>
    constexpr Vector &operator*=(T1 value) noexcept;

    template <std::convertible_to<T> T1>
    constexpr Vector &operator/=(T value) noexcept;

    friend constexpr bool operator==(const Vector &lhs, const Vector &rhs) noexcept {
        return lhs.elems_ == rhs.elems_;
    }

    friend constexpr auto operator<=>(const Vector &lhs, const Vector &rhs) noexcept {
        /// We do not have to compare magnitudes and use expensive square root
        return lhs.magnitude_squared() <=> rhs.magnitude_squared();
    }

    friend constexpr Vector operator<<(std::ostream &os, const Vector &vec) noexcept {
        return os;
    }
};

template <VectorType V>
constexpr double dot(const V &lhs, const V &rhs) {
    return lhs.dot(rhs);
}

template <VectorType V>
constexpr double magnitude(const V &vec) {
    return vec.magnitude();
}

template <VectorType V>
constexpr double magnitude_squared(const V &vec) {
    return vec.magnitude_squared();
}

template <VectorType V>
constexpr double norm(const V &vec) {
    return vec.norm();
}

static_assert(std::is_standard_layout_v<Vector<int, 3>>);
static_assert(std::is_standard_layout_v<Vector<float, 3>>);
static_assert(std::is_standard_layout_v<Vector<double, 3>>);
static_assert(std::is_trivial_v<Vector<int, 3>>);
static_assert(std::is_trivial_v<Vector<float, 3>>);
static_assert(std::is_trivial_v<Vector<double, 3>>);

} // namespace dk::math

#endif // DK_MATH_VECTOR_HPP
