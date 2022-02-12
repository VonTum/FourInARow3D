cmake_minimum_required(VERSION 3.10)

project(FourInARow3D VERSION 1.0)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Building with: ${CMAKE_CXX_COMPILER_ID}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")

	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Oi /ot /GL")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g  -fsanitize=address")
endif()

add_executable(FourInARow3D
  FourInARow3D.cpp
)
