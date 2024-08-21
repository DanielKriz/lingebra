#include <doctest/doctest.h>
#include <dklib/math/tensor.hpp>

#include <iostream>
#include <type_traits>
#include <utility>

#include "test_utilities.hpp"

using namespace dk::math;

#define tensor_types                             \
    TypeSizePair<Tensor<int, 1, 2, 3>, 6>,       \
        TypeSizePair<Tensor<float, 1, 2, 3>, 6>, \
        TypeSizePair<Tensor<double, 1, 2, 3>, 6>
#define TENSOR_TYPE(TType) using TType = typename T::Type;
#define TEST_CASE_TENSOR(msg) TEST_CASE_TEMPLATE(msg, T, tensor_types)

TEST_SUITE_BEGIN("Tensor");

TEST_CASE_TENSOR("Basic constructor") {
    TENSOR_TYPE(Tensor)
    auto t = Tensor();
    CHECK(&t != nullptr);
}

TEST_CASE("Shape of a tensor") {
    CHECK(Tensor<int, 1, 2, 3>().get_shape() == std::vector<std::size_t> { 1, 2, 3 });
}

TEST_CASE_TENSOR("Tensor is trivial type") {
    TENSOR_TYPE(Tensor)
    CHECK(std::is_trivial_v<Tensor>);
}

TEST_CASE_TENSOR("Tensor has standard layout") {
    TENSOR_TYPE(Tensor)
    CHECK(std::is_standard_layout_v<Tensor>);
}

TEST_CASE_TENSOR("Access operator reading") {
    TENSOR_TYPE(Tensor)
    auto t = Tensor();
    t[0] = 42;
    CHECK(t[0] == 42);
}

TEST_CASE_TENSOR("Getting the size of a tensor") {
    TENSOR_TYPE(Tensor)
    CHECK(Tensor().size() == T::get_size());
}

TEST_CASE_TENSOR("Constuctor with single value") {
    TENSOR_TYPE(Tensor)
    auto t = Tensor(1);
    for (std::size_t i = 0; i < t.size(); ++i) {
        CHECK(t[i] == 1);
    }
}

TEST_CASE_TENSOR("Constuctor with element assignment") {
    TENSOR_TYPE(Tensor)
    const auto values = incremental_values<typename Tensor::value_type, T::Size>();
    auto t = Tensor(values);
    for (std::size_t i = 0; i < values.size(); ++i) {
        CHECK(t[i] == values[i]);
    }
}

TEST_CASE_TENSOR("Copy constructor") {
    TENSOR_TYPE(Tensor)
    const auto values = incremental_values<typename Tensor::value_type, T::Size>();
    auto t = Tensor(values);
    auto tt { t };
    for (std::size_t i = 0; i < values.size(); ++i) {
        CHECK(tt[i] == values[i]);
    }
}

TEST_CASE_TENSOR("Copy assignment") {
    TENSOR_TYPE(Tensor)
    const auto values = incremental_values<typename Tensor::value_type, T::Size>();
    auto t = Tensor(values);
    auto tt = t;
    for (std::size_t i = 0; i < values.size(); ++i) {
        CHECK(tt[i] == values[i]);
    }
}

TEST_CASE_TENSOR("Move assignment") {
    TENSOR_TYPE(Tensor)
    const auto values = incremental_values<typename Tensor::value_type, T::Size>();
    auto t = Tensor(values);
    auto tt = std::move(t);
    for (std::size_t i = 0; i < values.size(); ++i) {
        CHECK(tt[i] == values[i]);
    }
}

TEST_CASE_TENSOR("Access operator reading from const tensor") {
    TENSOR_TYPE(Tensor)
    const auto t = Tensor(1);
    CHECK(t[0] == 1);
}

TEST_CASE_TENSOR("Safe access operator") {
    TENSOR_TYPE(Tensor)
    SUBCASE("with normal type") {
        auto t = Tensor(1);
        CHECK(t.at(0) == 1);
        t.at(0) = 42;
        CHECK(t.at(0) == 42);
    }
    SUBCASE("with normal type throws on out of bounds") {
        auto t = Tensor(1);
        CHECK_THROWS_WITH_AS(t.at(69000) == 42, "index out of bounds", std::runtime_error);
    }
    SUBCASE("with const type") {
        const auto t = Tensor(1);
        CHECK(t.at(0) == 1);
    }
    SUBCASE("with const type throws on out of bounds") {
        auto t = Tensor(1);
        CHECK_THROWS_WITH_AS(t.at(69000) == 42, "index out of bounds", std::runtime_error);
    }
}

TEST_CASE_TENSOR("Move constructor") {
    TENSOR_TYPE(Tensor)
    const auto values = incremental_values<typename Tensor::value_type, T::Size>();
    SUBCASE("with xvalue") {
        auto t = Tensor(values);
        auto tt { std::move(t) };
        for (std::size_t i = 0; i < values.size(); ++i) {
            CHECK(tt[i] == values[i]);
        }
    }
    SUBCASE("with rvalue") {
        auto tt { Tensor(values) };
        for (std::size_t i = 0; i < values.size(); ++i) {
            CHECK(tt[i] == values[i]);
        }
    }
}

TEST_CASE_TENSOR("Data access") {
    TENSOR_TYPE(Tensor)
    SUBCASE("with normal type") {
        auto t = Tensor(1);
        CHECK(t.data() != nullptr);
        for (std::size_t i = 0; i < t.size(); ++i) {
            CHECK(t.data()[i] == 1);
        }
    }
    SUBCASE("with const type") {
        const auto t = Tensor(1);
        CHECK(t.data() != nullptr);
        for (std::size_t i = 0; i < t.size(); ++i) {
            CHECK(t.data()[i] == 1);
        }
    }
}

TEST_SUITE_END();
