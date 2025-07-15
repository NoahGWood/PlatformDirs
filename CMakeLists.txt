cmake_minimum_required(VERSION 3.14)
project(platform_dirs_test LANGUAGES CXX)

add_executable(test_platform_dirs tests/test.cpp)
target_include_directories(test_platform_dirs PRIVATE include)
target_compile_features(test_platform_dirs PRIVATE cxx_std_17)
