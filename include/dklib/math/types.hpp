#ifndef DK_MATH_TYPES_HPP
#define DK_MATH_TYPES_HPP

#if DK_USE_DOUBLE_PRECISION
#define DK_DEFAULT_PRECISION_TYPE = double;
#else
#define DK_DEFAULT_PRECISION_TYPE = float;
#endif

#define DK_INIT_METHOD [[nodiscard]] inline static constexpr

namespace dk {
using real = float;
} // namespace dk

#endif // DK_MATH_TYPES_HPP
