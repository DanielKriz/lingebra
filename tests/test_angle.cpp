#include <doctest/doctest.h>
#include <dklib/math/angle.hpp>

#include <numbers>

using namespace dk::math;

TEST_SUITE_BEGIN("Angle");

TEST_CASE("It should be possible to initialize angle") { Angle(1); }

TEST_CASE("Angles should be the same if they hold the same value") {
    CHECK(Angle(1) == Angle(1));
}

TEST_CASE("Angles should be the different if they hold the different value") {
    CHECK(Angle(0) == Angle::from<Degrees>(0));
    CHECK(Angle(0) == Angle::from<Radians>(0));
}

TEST_CASE("Angle should by default represent radians") {
    CHECK(Angle(1) == Angle::from<Radians>(1));
    CHECK(Angle(1) != Angle::from<Degrees>(1));
}

TEST_CASE("Angle comparisons") {
    CHECK(Angle(1) < Angle(2));
    CHECK(Angle(1) <= Angle(1));
    CHECK(Angle(1) <= Angle(2));
    CHECK(Angle(2) > Angle(1));
    CHECK(Angle(1) >= Angle(1));
    CHECK(Angle(2) >= Angle(1));
}

TEST_CASE("Angle implicitly convertible to double") {
    CHECK(std::sin(1) == std::sin(static_cast<double>(Angle(1))));
    CHECK(std::sin(1) == std::sin(Angle(1)));
}

TEST_CASE("Angles from degrees and radians should be comparabel") {
    CHECK(Angle::from<Radians>(std::numbers::pi) == Angle::from<Degrees>(180));
    CHECK(Angle::from<Radians>(std::numbers::pi) != Angle::from<Degrees>(90));
}

TEST_CASE("Angle degree literal") {
    CHECK(180_deg == Angle::from<Degrees>(180));
    CHECK(180.0_deg == Angle::from<Degrees>(180));
}

TEST_CASE("Angle radian literal") {
    CHECK(1_rad == Angle::from<Radians>(1));
    CHECK(1.0_rad == Angle::from<Radians>(1));
}

TEST_SUITE_END();
