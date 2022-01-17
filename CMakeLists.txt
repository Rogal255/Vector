cmake_minimum_required(VERSION 3.21)
project(Vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(Vector main.cpp Helpers.cpp)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(UT UT.cpp Helpers.cpp)
target_link_libraries(UT gtest_main)
