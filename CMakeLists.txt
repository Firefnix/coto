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

set(src_files src/amplitude.cpp src/qdd.cpp src/absi.cpp)
set(header_files include/amplitude.h include/qdd.h include/absi.h)
set(test_files test/amplitude_test.cpp test/qdd_test.cpp test/absi_test.cpp)

set(sources
    ${src_files}
    ${header_files}
    ${test_files}
    )

# add_link_options(-lgcov --coverage)
# add_definitions(-fprofile-arcs -ftest-coverage)

# add_custom_target(init
#     COMMAND ${CMAKE_MAKE_PROGRAM} clean
#     COMMAND rm -f ${OBJECT_DIR}/*.gcno
#     COMMAND rm -f ${OBJECT_DIR}/*.gcda
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
# )

# add_custom_target(gcov
#     COMMAND mkdir -p gcoverage
#     COMMAND ${CMAKE_MAKE_PROGRAM} test
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
# )

# add_dependencies(gcov amplitude qdd)


# add_custom_command(TARGET gcov
#     COMMAND echo "=================== GCOV ===================="
#     COMMAND gcov -b ${CMAKE_SOURCE_DIR}/src/*.cpp -o ${OBJECT_DIR} -a
#     COMMAND echo "-- Source directory: ${CMAKE_SOURCE_DIR}/src/"
#     COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/gcoverage"
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gcoverage
# )

# add_custom_target(lcov
#     COMMAND mkdir -p lcoverage
# )

# add_custom_command(TARGET lcov
#     COMMAND echo "=================== LCOV ===================="
#     COMMAND echo "-- Passing lcov tool under code coverage"
#     COMMAND lcov --capture --directory ../ --output-file lcoverage/main_coverage.info
#     COMMAND echo "-- Generating HTML output files"
#     COMMAND genhtml lcoverage/main_coverage.info --output-directory lcoverage
# )


# Amplitude test
add_library(amplitude STATIC src/amplitude.cpp)
add_executable(amplitude_test test/amplitude_test.cpp)
target_link_libraries(amplitude_test amplitude GTest::gtest_main)

# ABSI test
add_library(absi STATIC src/absi.cpp)
add_executable(absi_test test/absi_test.cpp)
target_link_libraries(absi_test absi amplitude GTest::gtest_main)

# QDD test
add_library(qdd STATIC src/qdd.cpp src/amplitude.cpp)
add_executable(qdd_test test/qdd_test.cpp)
target_link_libraries(qdd_test qdd amplitude GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(amplitude_test)
gtest_discover_tests(absi_test)
gtest_discover_tests(qdd_test)