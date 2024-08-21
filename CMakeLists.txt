cmake_minimum_required(VERSION 3.23)
project(dklib_math CXX)

# CMake setup
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   add_compile_options (-fcolor-diagnostics)
endif ()

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

file(GLOB SRC_FILES "src/*.cpp" "src/**/*.cpp")
file(GLOB HDR_FILES "include/**/*.hpp" "include/**/*.h")

add_library(dk INTERFACE)

target_include_directories(
    dk
    INTERFACE
    include/
)
target_link_libraries(
    dk
)


# Testing Setup
file(GLOB TEST_SRC_FILES "tests/*.cpp" "tests/**/*.cpp")
file(GLOB TEST_HDR_FILES "tests/*.hpp" "tests/**/*.hpp")

find_package(doctest REQUIRED)
include(doctest)

set(DK_TEST_NAME "test_dklib")
add_executable(
    ${DK_TEST_NAME}
    ${TEST_SRC_FILES}
    ${TEST_HDR_FILES}
)
set_target_properties(
    ${DK_TEST_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
    LINKER_LANGUAGE CXX
)

target_link_libraries(${DK_TEST_NAME} PUBLIC
    dk
)
target_link_options(${DK_TEST_NAME}
    BEFORE PUBLIC -fsanitize=undefined
    PUBLIC -fsanitize=address
    PUBLIC -fsanitize=leak
    # PUBLIC -fsanitize=memory
    PUBLIC -fno-omit-frame-pointer
    PUBLIC -O1
)
target_link_libraries(${DK_TEST_NAME} PRIVATE doctest::doctest)
enable_testing()
doctest_discover_tests(${DK_TEST_NAME})
