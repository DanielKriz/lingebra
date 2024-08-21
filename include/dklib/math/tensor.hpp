#ifndef DK_MATH_TENSOR_HPP
#define DK_MATH_TENSOR_HPP

#include <array>
#include <ostream>
#include <stdexcept>
#include <vector>

#include <dklib/math/concepts.hpp>
#include <dklib/math/tensor_concepts.hpp>
#include <dklib/math/types.hpp>

#include <iostream>

namespace dk::math {

template <Numeric T = real, std::size_t... Dims>
requires((Dims > 0) and ...)
class Tensor {
public:
    using value_type = T;
    using storage_type = std::array<T, (... * Dims)>;

    constexpr Tensor() = default;
    constexpr Tensor(T value) { elems_.fill(value); }
    constexpr Tensor(std::array<T, (... * Dims)> elems)
        : elems_ { elems } {};

    [[nodiscard]] constexpr std::vector<std::size_t> get_shape() const noexcept {
        return std::vector<std::size_t> { Dims... };
    }

    template <std::size_t... Dims1>
    requires((... * Dims) == (... * Dims1))
    Tensor<T, Dims1...> reshape() const {};

    [[nodiscard]] constexpr std::size_t size() const noexcept {
        return elems_.size();
    };

    [[nodiscard]] constexpr T &operator[](std::size_t idx) noexcept {
        return elems_[idx];
    }
    [[nodiscard]] constexpr T operator[](std::size_t idx) const noexcept {
        return elems_[idx];
    }

    [[nodiscard]] constexpr T &at(std::size_t idx) {
        if (idx >= size()) {
            throw std::runtime_error("index out of bounds");
        }
        return elems_[idx];
    };
    [[nodiscard]] constexpr T at(std::size_t idx) const {
        if (idx >= size()) {
            throw std::runtime_error("index out of bounds");
        }
        return elems_[idx];
    };

    [[nodiscard]] constexpr const T *data() const { return elems_.data(); };
    [[nodiscard]] constexpr T *data() { return elems_.data(); };

    friend constexpr std::ostream &operator<<(std::ostream &os, const Tensor &tensor) {
        os << '(';
        for (auto elem : tensor.elems_) {
            os << elem << ", ";
        }
        return os << ')';
    }

protected:
    storage_type elems_;
};

template <TensorType T>
constexpr T operator&(const T &lhs, const T &rhs) {
    return T { lhs } += rhs;
}

template <TensorType T>
constexpr T operator+(const T &lhs, const T &rhs) {
    return T { lhs } += rhs;
}

template <TensorType T>
constexpr T operator-(const T &lhs, const T &rhs) {
    return T { lhs } -= rhs;
}

template <TensorType T>
constexpr T operator*(const T &lhs, const T &rhs) {
    return T { lhs } *= rhs;
}

template <TensorType T>
constexpr T operator/(const T &lhs, const T &rhs) {
    return T { lhs } /= rhs;
}

template <TensorType T, std::convertible_to<double> F>
constexpr T operator*(const T &other, F value) {
    return T { other } *= value;
}

template <TensorType T, std::convertible_to<double> F>
constexpr T operator*(F value, const T &other) {
    return T { other } *= value;
}

template <TensorType T, std::floating_point F>
constexpr T operator/(const T &other, F value) {
    return T { other } /= value;
}

static_assert(std::is_standard_layout_v<Tensor<int, 3>>);
static_assert(std::is_standard_layout_v<Tensor<float, 3>>);
static_assert(std::is_standard_layout_v<Tensor<double, 3>>);
static_assert(std::is_trivial_v<Tensor<int, 3>>);
static_assert(std::is_trivial_v<Tensor<float, 3>>);
static_assert(std::is_trivial_v<Tensor<double, 3>>);

} // namespace dk::math

#endif // DK_MATH_TENSOR_HPP
