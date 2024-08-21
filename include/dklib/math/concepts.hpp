#ifndef DK_MATH_CONCEPTS_HPP
#define DK_MATH_CONCEPTS_HPP

#include <concepts>

namespace dk::math {

template <typename T>
concept Numeric = std::integral<T> or std::floating_point<T>;

template <typename T>
concept Signed = std::signed_integral<T> or std::floating_point<T>;

template <std::size_t N>
concept PositiveNumber = N > 0;

} // namespace dk::math

#endif // DK_MATH_CONCEPTS_HPP
