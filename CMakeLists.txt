cmake_minimum_required(VERSION 3.14)
project(coto)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b10fad38c4026a29ea6561ab15fc4818170d1c10.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(include/)

enable_testing()

# Formal calculus library
set(CALC_SOURCES src/number.cpp src/integer.cpp src/rational.cpp)
add_library(calc STATIC "${CALC_SOURCES}")
add_executable(calc_test test/calc_test.cpp)
target_link_libraries(calc_test calc GTest::gtest_main)

# Lang test
add_library(lang STATIC src/lang.cpp)
add_executable(lang_test test/lang_test.cpp)
target_link_libraries(lang_test lang GTest::gtest_main)

# Amplitude test
add_library(amplitude STATIC src/amplitude.cpp)
add_executable(amplitude_test test/amplitude_test.cpp)
target_link_libraries(amplitude_test amplitude GTest::gtest_main)

# QDD test
add_library(qdd STATIC src/qdd.cpp src/amplitude.cpp)
add_executable(qdd_test test/qdd_test.cpp)
target_link_libraries(qdd_test qdd amplitude GTest::gtest_main)

include(GoogleTest)
# gtest_discover_tests(lang_test)
# gtest_discover_tests(calc_test)
gtest_discover_tests(amplitude_test)
gtest_discover_tests(qdd_test)