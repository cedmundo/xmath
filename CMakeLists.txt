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

include(cmake/FetchCMocka.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions("-Wall")
if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
  add_definitions("-g")
endif()

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

if(XMATH_BUILD_TESTS)
  enable_testing()
  macro(setup_test TEST_SUBJECT ...)
    add_executable(${TEST_SUBJECT}_test ${TEST_SUBJECT}_test.c ${ARGN})
    target_link_libraries(${TEST_SUBJECT}_test cmocka)
    add_test(TEST ${TEST_SUBJECT}_test COMMAND ${TEST_SUBJECT})
  endmacro()

  setup_test(xmath xmath.c xmath.h)
endif()

set_target_properties(xmath PROPERTIES PUBLIC_HEADER ${HEADERS})
install(
  TARGETS xmath
  PUBLIC_HEADER DESTINATION xmath
)
