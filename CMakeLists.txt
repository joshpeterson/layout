cmake_minimum_required(VERSION 3.5)
project(clang-expand)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

set(CLANG_LIBS clang)

find_package(LLVM REQUIRED)

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
include_directories(SYSTEM ${CLANG_INCLUDE_DIRS})

link_directories(${LLVM_LIBRARY_DIRS})
set(CMAKE_EXE_LINKER_FLAGS ${LLVM_LD_FLAGS_STRING})

set(CXX_STANDARD_REQUIRED ON)

set(CPP_FLAGS -std=c++14 -fno-rtti)
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG -DENABLE_FAKING")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_EXE_LINKER_FLAGS "-flto")
endif()

add_compile_options(${CPP_FLAGS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
message(STATUS "Binaries will land in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_executable(layout exe/main.cpp)
target_link_libraries(layout layoutlib ${CLANG_LIBS})

file(GLOB LAYOUT_TEST_SOURCES test/*.cpp)
add_compile_options("-fexceptions")
add_executable(layout_test ${LAYOUT_TEST_SOURCES})
target_link_libraries(layout_test layoutlib ${CLANG_LIBS} stdc++fs)
