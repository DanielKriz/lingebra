#ifndef DK_MATH_TENSOR_CONCEPTS_HPP
#define DK_MATH_TENSOR_CONCEPTS_HPP

#include <dklib/math/concepts.hpp>

#include <type_traits>

namespace dk::math {

template <Numeric T, std::size_t... Dims>
requires((Dims > 0) and ...)
class Tensor;

template <typename T>
struct is_tensor_type : std::false_type { };

template <template <typename, std::size_t...> typename C, typename T, std::size_t... Dims>
struct is_tensor_type<C<T, Dims...>>
    : std::is_base_of<Tensor<T, Dims...>, C<T, Dims...>> { };

template <typename T>
inline constexpr bool is_tensor_type_v = is_tensor_type<T>::value;

template <typename T>
concept TensorType = is_tensor_type_v<T> or is_tensor_type_v<typename T::Base>;

} // namespace dk::math

#endif // DK_MATH_TENSOR_CONCEPTS_HPP
