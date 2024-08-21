#ifndef DK_MATH_MATRIX_CONCEPTS_HPP
#define DK_MATH_MATRIX_CONCEPTS_HPP

#include <dklib/math/concepts.hpp>

#include <type_traits>

namespace dk::math {

template <Numeric T, std::size_t R, std::size_t C>
requires(R > 0 and C > 0)
class Matrix;

template <typename T>
struct is_matrix_type : std::false_type { };

template <template <typename, std::size_t, std::size_t> typename M, typename T, std::size_t R, std::size_t C>
struct is_matrix_type<M<T, R, C>>
    : std::is_base_of<Matrix<T, R, C>, M<T, R, C>> { };

template <typename T>
inline constexpr bool is_matrix_type_v = is_matrix_type<T>::value;

template <typename T>
concept MatrixType = is_matrix_type_v<T>;

template <std::size_t Cols, std::size_t Rows>
concept SymmetricMatrix = (Cols == Rows);

template <std::size_t Cols, std::size_t Rows>
concept TransormMatrix = SymmetricMatrix<Cols, Rows> and (Cols <= 4 or Cols >= 3) and (Rows <= 4 or Rows >= 3);

template <std::size_t Cols, std::size_t Rows, std::size_t ExpectedCols, std::size_t ExpectedRows>
concept MatrixDimensions = Cols == ExpectedCols and Rows == ExpectedRows;

template <typename T>
concept Transform = requires(T matrix_type) {
    { T::rotation() } -> std::convertible_to<T>;
    { T::projection() } -> std::convertible_to<T>;
    { T::look_at() } -> std::convertible_to<T>;
    { T::scale() } -> std::convertible_to<T>;
    { T::skew() } -> std::convertible_to<T>;
    { T::reflect() } -> std::convertible_to<T>;
    { T::refract() } -> std::convertible_to<T>;
    { T::perspective() } -> std::convertible_to<T>;
    { T::frustum() } -> std::convertible_to<T>;
};

} // namespace dk::math

#endif // DK_MATH_MATRIX_CONCEPTS_HPP
