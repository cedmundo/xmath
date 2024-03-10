cmake_minimum_required(VERSION 3.22)
project(xmath
  VERSION       "0.0.1"
  DESCRIPTION   "Simple library for linear math in C11"
  HOMEPAGE_URL  "https://github.com/cedmundo/xmath"
  LANGUAGES     C
)

set(XMATH_BUILD_STATIC  "Build as static library" ON)
set(XMATH_BUILD_TESTS   "Build unit tests" ON)
set(XMATH_BUILD_DOCS    "Build HTML docs" ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HEADERS xmath.h)
set(SOURCES xmath.c)

if(XMATH_BUILD_STATIC)
  add_library(xmath STATIC)
else()
  add_library(xmath SHARED)
endif()

target_sources(xmath
  PRIVATE ${SOURCES}
  PUBLIC ${HEADERS}
)

set_target_properties(xmath PROPERTIES PUBLIC_HEADER ${HEADERS})
install(
  TARGETS xmath
  PUBLIC_HEADER DESTINATION xmath
)
