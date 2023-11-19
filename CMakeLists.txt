cmake_minimum_required(VERSION 3.14)
project(coto)

# GoogleTest requires at least C++20
set(CMAKE_CXX_STANDARD 20)
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

# Amplitude test
add_library(amplitude STATIC src/amplitude.cpp)
add_executable(amplitude_test test/amplitude_test.cpp)
target_link_libraries(amplitude_test amplitude GTest::gtest_main)

# QDD test
add_library(qdd STATIC src/qdd.cpp src/amplitude.cpp)
add_executable(qdd_test test/qdd_test.cpp)
target_link_libraries(qdd_test qdd amplitude GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(amplitude_test)
gtest_discover_tests(qdd_test)