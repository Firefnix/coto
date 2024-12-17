cmake_minimum_required(VERSION 3.14)
project(coto)

# GoogleTest requires at least C++20
set(CMAKE_GENERATOR Ninja)
set(CMAKE_CXX_STANDARD 23)
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

set(absi_files src/absi/polar.cpp src/absi/cartesian.cpp)
set(absi_libs cartesian polar amplitude)
set(src_files src/amplitude.cpp ${absi_files} src/selection.cpp src/reduction.cpp)
set(header_files include/amplitude.h include/qdd.h include/absi.h)
set(test_files test/amplitude_test.cpp test/qdd_test.cpp test/absi_test.cpp test/selection_test.cpp test/reduction_test.cpp test/diagram_test.cpp)

set(sources
    ${src_files}
    ${header_files}
    ${test_files}
    )


# Amplitude test
add_library(amplitude STATIC src/amplitude.cpp)
add_executable(amplitude_test test/amplitude_test.cpp)
target_link_libraries(amplitude_test amplitude GTest::gtest_main)

# ABStract Interpretation (ABSI) tests
# Encompasses cartesian intervals test and polar intervals tests
add_library(cartesian STATIC src/absi/cartesian.cpp)
add_library(polar STATIC src/absi/polar.cpp)
add_executable(absi_test test/absi_test.cpp)
target_link_libraries(absi_test ${absi_libs} GTest::gtest_main)

# Diagram test
add_executable(diagram_test ${absi_files} test/diagram_test.cpp include/diagram.h)
target_link_libraries(diagram_test ${absi_libs} GTest::gtest_main)

# Selection test
add_library(selection STATIC include/selection.h ${absi_files} src/amplitude.cpp include/diagram.h)
add_executable(selection_test test/selection_test.cpp)
target_link_libraries(selection_test ${absi_libs} selection GTest::gtest_main)

# Reduction test
add_library(reduction STATIC src/reduction.cpp include/diagram.h ${absi_files} src/amplitude.cpp)

# QASM library
FILE(GLOB QasmSources src/qasm/*.cpp)
add_library(qasm STATIC ${QasmSources})
add_executable(qasm_test test/qasm/qasm_test.cpp)
target_link_libraries(qasm_test qasm GTest::gtest_main)

# Command-line prompt
add_executable(prompt)
target_sources(prompt PUBLIC src/prompt.cpp)
target_link_libraries(prompt qasm)

include(GoogleTest)
gtest_discover_tests(amplitude_test)
gtest_discover_tests(absi_test)
gtest_discover_tests(diagram_test)
# gtest_discover_tests(selection_test)
gtest_discover_tests(qasm_test)
