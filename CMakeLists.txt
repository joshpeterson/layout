cmake_minimum_required(VERSION 3.1)

project(layout, CXX)
set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/lib/llvm-3.8/include)
set(CMAKE_EXE_LINKER_FLAGS -L/usr/lib/llvm-3.8/lib, -lclang)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(layout_test ${SRC_FILES} ${INCLUDE_FILES} ${TEST_FILES})
