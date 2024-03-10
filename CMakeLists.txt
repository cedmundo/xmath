cmake_minimum_required(VERSION 3.22)
project(xmath
  VERSION       "0.0.1"
  DESCRIPTION   "Simple library for linear math in C11"
  HOMEPAGE_URL  "https://github.com/cedmundo/xmath"
  LANGUAGES     C
)

include(cmake/FetchCMocka.cmake)

option(BUILD_STATIC "Build as static library" ON)
option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_DOCS "Build HTML docs" ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions("-Wall")
if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
  add_definitions("-g")
endif()

set(HEADERS xmath.h)
set(SOURCES xmath.c)

if(BUILD_STATIC)
  add_library(xmath STATIC)
else()
  add_library(xmath SHARED)
endif()

target_sources(xmath
  PRIVATE ${SOURCES}
  PUBLIC ${HEADERS}
)

if(BUILD_TESTS)
  enable_testing()
  macro(setup_test TEST_SUBJECT)
    add_executable(${TEST_SUBJECT}_test ${TEST_SUBJECT}_test.c ${ARGN})
    target_link_libraries(${TEST_SUBJECT}_test xmath cmocka)
    add_test(TEST ${TEST_SUBJECT}_test COMMAND ${TEST_SUBJECT})
  endmacro()

  setup_test(xmath)
endif()

set_target_properties(xmath PROPERTIES PUBLIC_HEADER ${HEADERS})
install(
  TARGETS xmath
  PUBLIC_HEADER DESTINATION xmath
)

if(BUILD_DOCS)
  find_package(Doxygen REQUIRED)
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  add_custom_target(xmath_docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generate docs with doxygen"
    VERBATIM
  )
endif()
