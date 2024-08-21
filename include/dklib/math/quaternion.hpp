#ifndef DK_MATH_QUATERNION_HPP
#define DK_MATH_QUATERNION_HPP

#include <dklib/math/angle.hpp>
#include <dklib/math/vector3d.hpp>

#include <cmath>
#include <ostream>

namespace dk::math {

class Quaternion {
public:
    /// Imaginary part of a quaternion.
    Vector3D imag;
    /// Real part of a quaternion.
    float real;

    constexpr Quaternion() = default;

    /// Default exhaustive constructor for Quaternion class.
    ///
    /// It delegates most work to the vector based constructor.
    ///
    /// @param  [in] a,b,c An imaginary part of quaternion.
    /// @param  [in] s A real part of a vector, oftern addressed as scalar.
    constexpr Quaternion(float a, float b, float c, float s);
    constexpr Quaternion(float a, float b, float c, Angle angle);

    /// Constructor for so-called pure quaternion, i.e. quaternion which real part
    /// is equal to zero.
    ///
    /// It delegates most work to the vector based constructor.
    constexpr Quaternion(float a, float b, float c);

    /// Constuctor which represents the imaginary part as a vector.
    constexpr Quaternion(const Vector3D &vec, float s);
    constexpr Quaternion(const Vector3D &vec, Angle s);

    /// @brief Checks whether the Quaternion instance is unit quaternion.
    ///
    /// Unit quaternion is a quaternion which magnitude is equal to one.
    ///
    /// @return True if the quaternion is indeed unit quaternion.
    [[nodiscard]] constexpr bool is_unit() const;

    /// @brief Checks whether the quaternion is pure.
    ///
    /// Quaternion is pure when its real part is equal to zero.
    ///
    /// @return True if the quaternion is indeed pure.
    [[nodiscard]] constexpr bool is_pure() const noexcept;

    /// @brief Accessor to the imaginary part.
    ///
    /// @return Vector representing the copy of imaginary part of our quaternion.
    [[nodiscard]] constexpr Vector3D vector_part() const;

    /// Equality operators.
    friend constexpr bool operator==(const Quaternion &lhs, const Quaternion &rhs);
    friend constexpr bool operator!=(const Quaternion &lhs, const Quaternion &rhs);

    /// Equality operators.
    constexpr Quaternion &operator*=(const Quaternion &other) noexcept;
    constexpr Quaternion &operator-=(const Quaternion &other) noexcept;
    constexpr Quaternion &operator+=(const Quaternion &other) noexcept;

    friend constexpr Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs);
    friend constexpr Quaternion operator+(const Quaternion &lhs, const Quaternion &rhs);
    friend constexpr Quaternion operator-(const Quaternion &lhs, const Quaternion &rhs);

    friend constexpr std::ostream &operator<<(std::ostream &os, const Quaternion &quat);

    /// @brief rotates given vector around given axis with given angle.
    ///
    /// @param  [in] vec A vector which we want to rotate.
    /// @param  [in] angle An angle in degrees.
    /// @param  [in] axis Axis over which we are going to rotate our vector,
    ///                   it can be any arbitrary axis.
    ///
    /// @return Rotated copy (which is created as copy of the original vector).
    constexpr static Vector3D rotate(const Vector3D &vec, Angle angle, const Vector3D &axis);

    /// @brief Returns the norm of quaternion.
    ///
    /// In the case of quaternions, the norm is equal to the square root of sum
    /// of the dot product of imaginary part and squared value of real part.
    ///
    /// @return Value of the normalization factor of current Quaternion instance.
    [[nodiscard]] constexpr float norm() const noexcept;

    /// @brief Returns the squared norm of quaternion.
    ///
    /// As the `sqrt` is notoriously slow, when we would need the squared norm
    /// value, it much more efficient to simply don't apply the square root at
    /// the first place.
    ///
    /// @return Squared value of the normalization factor of current Quaternion
    /// instance.
    [[nodiscard]] constexpr float norm_squared() const noexcept;

    /// @brief Returns normalized unit quaternion with respect to the angle.
    ///
    /// As a side effect this function transform the real part to radians.
    [[nodiscard]] constexpr Quaternion unit_norm() const noexcept;

    /// @brief Mutating variant of `unit_norm` method.
    constexpr Quaternion &to_unit_norm() noexcept;

    /// @brief Returns pure equivalent of our Quaternion instance.
    [[nodiscard]] constexpr Quaternion pure() const noexcept;

    /// @brief Mutating variant of `pure` method.
    constexpr Quaternion &to_pure() noexcept;

    /// @brief Returns normalized quaternion.
    [[nodiscard]] constexpr Quaternion normalized() const;

    /// @brief Mutating variant of normalized quaternion.
    constexpr Quaternion &normalize();

    /// @brief Returns the conjugate of our Quaternion instance.
    ///
    /// The conjugate quaternion has its imaginary part negated.
    [[nodiscard]] constexpr Quaternion conjugate() const noexcept;

    /// @brief Returns the inverse of our Quaternion instance.
    [[nodiscard]] constexpr Quaternion inverse() const noexcept;
};

static_assert(std::is_trivial_v<Quaternion>);
static_assert(std::is_standard_layout_v<Quaternion>);

constexpr Quaternion::Quaternion(float a, float b, float c, float scalar)
    : imag(a, b, c)
    , real(scalar) { }

constexpr Quaternion::Quaternion(float a, float b, float c, Angle angle)
    : imag(a, b, c)
    , real(static_cast<float>(Degrees::from_radians(angle))) {};

constexpr Quaternion::Quaternion(const Vector3D &vec, float scalar)
    : imag(vec)
    , real(scalar) { }

constexpr Quaternion::Quaternion(const Vector3D &vec, Angle angle)
    : imag(vec)
    , real(static_cast<float>(Degrees::from_radians(angle))) {};

constexpr Vector3D Quaternion::vector_part() const { return imag; }

constexpr Vector3D Quaternion::rotate(const Vector3D &vec, Angle angle, const Vector3D &axis) {
    const Quaternion pure_quat = { vec, 0.0f };
    const Vector3D rotation_axis = axis.normalized();
    const Quaternion rotation_quat = Quaternion(rotation_axis, angle).to_unit_norm();
    const Quaternion rotation_quat_inverse = rotation_quat.inverse();
    const Quaternion rotated = rotation_quat * pure_quat * rotation_quat_inverse;

    return rotated.imag;
}

constexpr bool operator==(const Quaternion &lhs, const Quaternion &rhs) {
    return (lhs.imag == rhs.imag and lhs.real == rhs.real);
}
constexpr bool operator!=(const Quaternion &lhs, const Quaternion &rhs) {
    return not(lhs == rhs);
}

constexpr std::ostream &operator<<(std::ostream &os, const Quaternion &quat) {
    return os << '(' << quat.imag.get_x() << ", " << quat.imag.get_y() << ", "
              << quat.imag.get_z() << ", " << quat.real << ')';
}

constexpr bool Quaternion::is_unit() const { return *this == normalized(); }

constexpr Quaternion &Quaternion::normalize() {
    auto norm_value = norm();
    if (norm_value != 0.0f) {
        float normalization_factor = 1 / norm_value;
        imag *= normalization_factor;
        real *= normalization_factor;
    } else {
        throw std::runtime_error("Cannot normalize zero quaternion");
    }
    return *this;
}

constexpr Quaternion Quaternion::normalized() const {
    Quaternion copy = *this;
    copy.normalize();
    return copy;
}

constexpr float Quaternion::norm() const noexcept {
    return std::sqrt(dot(imag, imag) + (real * real));
}

constexpr float Quaternion::norm_squared() const noexcept {
    return (dot(imag, imag) + (real * real));
}

constexpr Quaternion Quaternion::conjugate() const noexcept {
    return { -imag, real };
}

constexpr bool Quaternion::is_pure() const noexcept { return real == 0.0f; }

constexpr Quaternion Quaternion::inverse() const noexcept {
    auto conj = conjugate();
    return conj * (*this * conj);
}

constexpr Quaternion &Quaternion::operator+=(const Quaternion &other) noexcept {
    imag += other.imag;
    real += other.real;
    return *this;
}

constexpr Quaternion &Quaternion::operator-=(const Quaternion &other) noexcept {
    imag -= other.imag;
    real -= other.real;
    return *this;
}

constexpr Quaternion &Quaternion::operator*=(const Quaternion &other) noexcept {
    const float new_real = real * other.real - dot(imag, other.imag);
    const Vector3D new_imag = imag * other.real + real * other.imag + cross(imag, other.imag);
    real = new_real;
    imag = new_imag;
    return *this;
}

constexpr Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs) {
    auto copy = lhs;
    copy *= rhs;
    return copy;
}

constexpr Quaternion operator+(const Quaternion &lhs, const Quaternion &rhs) {
    return { lhs.imag + rhs.imag, lhs.real + rhs.real };
}

constexpr Quaternion operator-(const Quaternion &lhs, const Quaternion &rhs) {
    return { lhs.imag - rhs.imag, lhs.real - rhs.real };
}

constexpr Quaternion Quaternion::unit_norm() const noexcept {
    auto copy = *this;
    return copy.to_unit_norm();
};

constexpr Quaternion &Quaternion::to_unit_norm() noexcept {
    auto angle = Angle::from<Degrees>(static_cast<double>(real));
    imag.normalize();
    real = static_cast<float>(std::cos(angle * 0.5));
    imag *= static_cast<float>(std::sin(angle * 0.5));
    return *this;
};

constexpr Quaternion Quaternion::pure() const noexcept { return { imag, 0.0f }; }

constexpr Quaternion &Quaternion::to_pure() noexcept {
    real = 0.0f;
    return *this;
}

} // namespace dk::math

#endif // DK_MATH_QUATERNION_HPP
