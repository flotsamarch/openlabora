cmake_minimum_required(VERSION 3.24)

#
# Project details
#

project(
  OpenLabora
  VERSION 0.1.0
  LANGUAGES CXX
)

#
# Set project options and language standard
#

set(CMAKE_CXX_STANDARD 20)

include(cmake/StandardSettings.cmake)
include(cmake/StaticAnalyzers.cmake)
include(cmake/Utils.cmake)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...\n")

#
# Setup alternative names
#

if(${PROJECT_NAME}_USE_ALT_NAMES)
  string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)
  string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)
else()
  set(PROJECT_NAME_LOWERCASE ${PROJECT_NAME})
  set(PROJECT_NAME_UPPERCASE ${PROJECT_NAME})
endif()

#
# Prevent building in the source directory
#

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n")
endif()

#
# Fetch and setup external dependencies
#

include(cmake/ExternalProjects.cmake)

message(STATUS "Finished fetching dependencies.\n")

#
# Create library, setup header and source files
#

# Find all headers and implementation files
include(cmake/SourcesAndHeaders.cmake)

# Build executable
add_executable(${PROJECT_NAME} ${headers} ${exe_sources})

# Tests
if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
  add_library(${PROJECT_NAME}_LIB ${headers} ${sources})
endif()

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)
if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
  set_target_properties(
    ${PROJECT_NAME}_LIB
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/"
    OUTPUT_NAME ${PROJECT_NAME}
  )
endif()

message(STATUS "Added all header and implementation files.\n")

#
# Set the project warnings
#

include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME})

verbose_message("Applied compiler warnings. Using standard ${CMAKE_CXX_STANDARD}.\n")

#
# Model project dependencies
#

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(TGUI CONFIG REQUIRED)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  sfml-system sfml-network sfml-graphics sfml-window sfml-audio
  tgui
)

if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
  target_link_libraries(
    ${PROJECT_NAME}_LIB
    PRIVATE
    sfml-system sfml-network sfml-graphics sfml-window sfml-audio
    tgui
  )
endif()

Win32CopyDlls(${PROJECT_NAME})

# For Windows, it is necessary to link with the MultiThreaded library.
# Depending on how the rest of the project's dependencies are linked, it might be necessary
# to change the line to statically link with the library.
#
# This is done as follows:
#
# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#
# On Linux and Mac this variable is ignored. If any issues rise from it, try commenting it out
# and letting CMake decide how to link with it.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

verbose_message("Successfully added all dependencies and linked against them.")

#
# Set the build/user include directories
#

# Allow usage of header files in the `src` directory, but only for utilities
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${EXTERNAL_INSTALL_LOCATION}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
  target_include_directories(
    ${PROJECT_NAME}_LIB
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${EXTERNAL_INSTALL_LOCATION}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/test/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
endif()

message(STATUS "Finished setting up include directories.\n")

#
# Provide alias to library for
#

add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

verbose_message("Project is now aliased as ${PROJECT_NAME}::${PROJECT_NAME}.\n")

#
# Install library for easy downstream inclusion
#

#include(GNUInstallDirs)
# install(
#   TARGETS
#   ${PROJECT_NAME}
#   EXPORT
#   ${PROJECT_NAME}Targets
#   LIBRARY DESTINATION
#   ${CMAKE_INSTALL_LIBDIR}
#   RUNTIME DESTINATION
#   ${CMAKE_INSTALL_BINDIR}
#   ARCHIVE DESTINATION
#   ${CMAKE_INSTALL_LIBDIR}
#   INCLUDES DESTINATION
#   include
#   PUBLIC_HEADER DESTINATION
#   include
# )

# install(
#   EXPORT
#   ${PROJECT_NAME}Targets
#   FILE
#   ${PROJECT_NAME}Targets.cmake
#   NAMESPACE
#   ${PROJECT_NAME}::
#   DESTINATION
#   ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
# )

#
# Add version header
#

#configure_file(
#   ${CMAKE_CURRENT_LIST_DIR}/cmake/version.hpp.in
#   include/${PROJECT_NAME_LOWERCASE}/version.hpp
#   @ONLY
# )

# install(
#   FILES
#   ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME_LOWERCASE}/version.hpp
#   DESTINATION
#   include/${PROJECT_NAME_LOWERCASE}
# )

#
# Install the `include` directory
#

#   include/${PROJECT_NAME_LOWERCASE}
#   DESTINATION
#   include
# )

# verbose_message("Install targets succesfully build. Install with `cmake --build <build_directory> --target install --config <build_config>`.")

#
# Quick `ConfigVersion.cmake` creation
#

# include(CMakePackageConfigHelpers)
# write_basic_package_version_file(
#   ${PROJECT_NAME}ConfigVersion.cmake
#   VERSION
#   ${PROJECT_VERSION}
#   COMPATIBILITY
#   SameMajorVersion
# )

# configure_package_config_file(
#   ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
#   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
#   INSTALL_DESTINATION
#   ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
# )

# install(
#   FILES
#   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
#   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
#   DESTINATION
#   ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
# )

#
# Generate export header if specified
#

# if(${PROJECT_NAME}_GENERATE_EXPORT_HEADER)
#   include(GenerateExportHeader)
#   generate_export_header(${PROJECT_NAME})
#   install(
#     FILES
#     ${PROJECT_BINARY_DIR}/${PROJECT_NAME_LOWERCASE}_export.h
#     DESTINATION
#     include
  # )

  # message(STATUS "Generated the export header `${PROJECT_NAME_LOWERCASE}_export.h` and installed it.")
# endif()

# message(STATUS "Finished building requirements for installing the package.\n")

#
# Unit testing setup
#

if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
  enable_testing()
  message(STATUS "Build unit tests for the project. Tests should always be found in the test folder\n")
  add_subdirectory(test)
endif()
