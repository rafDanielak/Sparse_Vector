cmake_minimum_required(VERSION 3.5.0)
project(sparse_vector VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(SPVECTOR_SOURCES sp_vector.h)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(spv_demo spv_demo.cpp ${SPVECTOR_SOURCES})
add_executable(spv_test spv_test.cpp ${SPVECTOR_SOURCES})
target_link_libraries(spv_test PUBLIC gtest_main)