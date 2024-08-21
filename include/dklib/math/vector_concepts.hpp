#ifndef DK_MATH_VECTOR_CONCEPTS_HPP
#define DK_MATH_VECTOR_CONCEPTS_HPP

#include <dklib/math/concepts.hpp>

#include <type_traits>

namespace dk::math {

template <Numeric T, std::size_t D>
requires(D > 0)
class Vector;

template <typename T>
struct is_vector_type : std::false_type { };

template <template <typename, std::size_t> typename C, typename T, std::size_t D>
struct is_vector_type<C<T, D>> : std::is_base_of<Vector<T, D>, C<T, D>> { };

template <typename T>
inline constexpr bool is_vector_type_v = is_vector_type<T>::value;

template <typename T>
concept VectorType = is_vector_type_v<T>;

} // namespace dk::math

#endif // DK_MATH_VECTOR_CONCEPTS_HPP
