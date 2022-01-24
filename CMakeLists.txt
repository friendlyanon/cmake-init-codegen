cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    codegen
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Generate source ----

find_program(PARSE_EXECUTABLE parse)
if(NOT PARSE_EXECUTABLE)
  message(FATAL_ERROR "PARSE_EXECUTABLE is required: ${PARSE_EXECUTABLE}")
endif()

set(src "${PROJECT_SOURCE_DIR}")
set(bin "${PROJECT_BINARY_DIR}")
add_custom_command(
    OUTPUT parse_output/bytes.hpp
    COMMAND "${CMAKE_COMMAND}" -E make_directory parse_output
    COMMAND "${PARSE_EXECUTABLE}"
    "${src}/assets/bytes.txt" parse_output/bytes.hpp.tmp
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
    parse_output/bytes.hpp.tmp parse_output/bytes.hpp
    COMMAND "${CMAKE_COMMAND}" -E remove parse_output/bytes.hpp.tmp
    MAIN_DEPENDENCY assets/bytes.txt
    WORKING_DIRECTORY "${bin}"
    COMMENT "Processing bytes.txt"
    VERBATIM
)

# ---- Declare library ----

add_library(
    codegen_lib OBJECT
    source/lib.cpp
    "${bin}/parse_output/bytes.hpp"
)

target_include_directories(
    codegen_lib ${warning_guard}
    PUBLIC "$<BUILD_INTERFACE:${src}/source>"
    PRIVATE "${bin}/parse_output"
)

target_compile_features(codegen_lib PUBLIC cxx_std_17)

# ---- Declare executable ----

add_executable(codegen_exe source/main.cpp)
add_executable(codegen::exe ALIAS codegen_exe)

set_target_properties(
    codegen_exe PROPERTIES
    OUTPUT_NAME codegen
    EXPORT_NAME exe
)

target_compile_features(codegen_exe PRIVATE cxx_std_17)

target_link_libraries(codegen_exe PRIVATE codegen_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT codegen_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of codegen"
  )
endif()

include(cmake/dev-mode.cmake)
