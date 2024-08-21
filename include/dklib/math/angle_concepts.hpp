#ifndef DK_ANGLE_CONCEPTS_HPP
#define DK_ANGLE_CONCEPTS_HPP

#include <concepts>

// WARNING: this is working only with doubles, at many other places I have
// floats, this might degrade performance
template <typename T>
concept AngleConvertible = requires(T repr, double value) {
    // TODO: this should return Angle
    { repr.to_radians(value) } -> std::convertible_to<double>;
};

#endif // DK_ANGLE_CONCEPTS_HPP
