cmake_minimum_required(VERSION 3.16.3)

project(WordleSolver C CXX)

add_executable(${PROJECT_NAME} 
    main.cpp
    engine/algorithm.cpp
    engine/baseline.cpp
    engine/randomAccess.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native)

# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)
# target_link_libraries(${PROJECT_NAME} Threads::Threads)