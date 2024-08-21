#ifndef DK_MATH_ANGLE_HPP
#define DK_MATH_ANGLE_HPP

#include <cmath>
#include <numbers>
#include <ostream>

#include <dklib/math/angle_concepts.hpp>

namespace dk::math {

class Angle {
public:
    template <AngleConvertible Representation>
    static inline constexpr Angle from(double value) {
        return Angle { Representation::to_radians(value) };
    }

    template <AngleConvertible Representation>
    [[nodiscard]] static inline constexpr double as(double value) {
        return Representation::from_radians(value);
    }

    constexpr auto operator<=>(const Angle &other) const = default;

    constexpr operator double() const { return radians_; }

    constexpr explicit Angle(double radians)
        : radians_ { radians } {};

    friend constexpr std::ostream &operator<<(std::ostream &os, const Angle &angle) {
        return os << angle.radians_;
    }

protected:
    /// Default internal representation is in radians, this makes it possible
    /// to suffice the open-closed principle.
    double radians_;
};

class Degrees : public Angle {
public:
    static inline constexpr double to_radians(double degrees) {
        return degrees * radian_coversion_coef;
    }

    static inline constexpr double from_radians(double radians) {
        return radians / radian_coversion_coef;
    }

private:
    static constexpr double radian_coversion_coef = std::numbers::pi / 180.0;
};

constexpr Angle operator""_deg(const char *value) {
    return Angle::from<Degrees>(std::stod(value));
}

constexpr Angle operator""_deg(unsigned long long value) {
    return Angle::from<Degrees>(static_cast<double>(value));
}

constexpr Angle operator""_deg(long double value) {
    return Angle::from<Degrees>(value);
}

// we want to be sure than we don't have to create reference
static_assert(sizeof(Degrees) == sizeof(double));
static_assert(std::is_trivially_copyable<Degrees>());

class Radians : public Angle {
public:
    static inline double constexpr to_radians(double radians) { return radians; }
};

constexpr Angle operator""_rad(const char *value) {
    return Angle::from<Radians>(std::stod(value));
}

constexpr Angle operator""_rad(unsigned long long value) {
    return Angle::from<Radians>(static_cast<double>(value));
}

constexpr Angle operator""_rad(long double value) {
    return Angle::from<Radians>(value);
}

static_assert(sizeof(Radians) == sizeof(double));
static_assert(std::is_trivially_copyable<Radians>());

} // namespace dk::math

#endif // DK_MATH_ANGLE_HPP
