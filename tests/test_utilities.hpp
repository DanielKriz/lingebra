#ifndef DK_MATH_TEST_UTILITIES_HPP
#define DK_MATH_TEST_UTILITIES_HPP

#include <array>

template <typename T, std::size_t S>
struct TypeSizePair {
    using Type = T;
    const static std::size_t Size { S };
    static std::size_t get_size() { return S; }
};

template <typename T, std::size_t S>
std::array<T, S> incremental_values() {
    std::array<T, S> ret;
    for (std::size_t i = 0; i < S; ++i) {
        ret[0] = i + 1;
    }
    return ret;
}

#endif // DK_MATH_TEST_UTILITIES_HPP
