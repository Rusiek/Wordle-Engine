cmake_minimum_required(VERSION 3.16.3)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(WordleSolver VERSION 1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} 
    main.cpp
    engine/ansReduction.cpp
    engine/algorithm.cpp
    engine/baseline.cpp
    engine/entropy.cpp
    engine/randomAccess.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
set(CLANG_TIDY_COMMAND ${CLANG_TIDY_EXE}
    -checks=engine/*,clang-analyzer-*,cppcoreguidelines-*,google-*,misc-*,performance-*,portability-*,readability-*
    -warnings-as-errors=*
    -header-filter=.*
    -fix
    -format-style=file
    -quiet
    -p=${CMAKE_BINARY_DIR}
    -extra-arg=-Wno-unknown-warning-option
    -extra-arg=-Wno-unknown-cuda-version
    -extra-arg=-Wno-unknown-attribute
    -extra-arg=-Wno-ignored-attributes
    -extra-arg=-Wno-deprecated-declarations
    -extra-arg=-Wno-unused-command-line
)
add_executable(WordleSolver::clang-tidy ALIAS ${PROJECT_NAME})
set_target_properties(WordleSolver PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

enable_testing()
include(GoogleTest)

add_executable(testUT
    engine/utils/tst/testBuildPath.cpp
    engine/utils/tst/testArrayToInt.cpp
    engine/tst/testAnsReduction.cpp
    engine/tst/testAlgorithm.cpp
    engine/tst/testBaseline.cpp
    engine/tst/testRandomAccess.cpp
    engine/ansReduction.cpp
    engine/baseline.cpp
    engine/algorithm.cpp
    )
target_link_libraries(testUT GTest::gtest_main)
gtest_discover_tests(testUT)
