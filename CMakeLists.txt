#
# This file is part of the µOS++ distribution.
#   (https://github.com/micro-os-plus)
# Copyright (c) 2021 Liviu Ionescu
#
# This Source Code Form is subject to the terms of the MIT License.
# If a copy of the license was not distributed with this file, it can
# be obtained from https://opensource.org/licenses/MIT/.
#
# -----------------------------------------------------------------------------

# https://cmake.org/cmake/help/v3.18/
cmake_minimum_required(VERSION 3.18)
message(STATUS "CMake version: ${CMAKE_VERSION}")

# Generate the compile_commands.json file to feed the indexer.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------

set(xpack_project_folder ${CMAKE_CURRENT_LIST_DIR})

include("${xpack_project_folder}/xpacks/micro-os-plus-build-helper/cmake/xpack-helper.cmake")

append_cmake_prefix_path("${xpack_project_folder}")

# Leave the result in PACKAGE_JSON_VERSION[*]
parse_package_json_semver("${xpack_project_folder}/package.json")

# -----------------------------------------------------------------------------

project(
  xpack-test
  DESCRIPTION "µTest++ tests"
  VERSION "${PACKAGE_JSON_VERSION}"
)

enable_language(C)
enable_language(CXX)
enable_language(ASM)

# Specify the C/C++ standards.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Platform name: ${PLATFORM_NAME}")
# CMAKE_BUILD_TYPE: Debug, Release, RelWithDebInfo, MinSizeRel
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Project path: ${xpack_project_folder}")
message(STATUS "Prefix path: ${CMAKE_PREFIX_PATH}")

if(PLATFORM_NAME STREQUAL "stm32f4discovery")
  add_subdirectory("${xpack_project_folder}/xpacks/platform-stm32f4discovery/")
  set_abi()
endif()

if(PLATFORM_NAME STREQUAL "native")
  # No platform specific definitions so far.
elseif(PLATFORM_NAME STREQUAL "stm32f4discovery")
  include("${xpack_project_folder}/xpacks/micro-os-plus-platform-stm32f4discovery/meta/xpack-helper.cmake")
  include("${xpack_project_folder}/xpacks/micro-os-plus-devices-stm32f4/meta/xpack-helper.cmake")
  include("${xpack_project_folder}/xpacks/micro-os-plus-architecture-cortexm/meta/xpack-helper.cmake")

  include("${xpack_project_folder}/xpacks/micro-os-plus-diag-trace/meta/xpack-helper.cmake")
  include("${xpack_project_folder}/xpacks/micro-os-plus-libs-c/meta/xpack-helper.cmake")
  include("${xpack_project_folder}/xpacks/micro-os-plus-libs-cpp/meta/xpack-helper.cmake")
  include("${xpack_project_folder}/xpacks/micro-os-plus-semihosting/meta/xpack-helper.cmake")
  include("${xpack_project_folder}/xpacks/micro-os-plus-startup/meta/xpack-helper.cmake")
  include("${xpack_project_folder}/xpacks/micro-os-plus-version/meta/xpack-helper.cmake")

else()
  message(FATAL_ERROR, "Unsupported PLATFORM_NAME")
endif()

#------------------------------------------------------------------------------

if(PLATFORM_NAME STREQUAL "stm32f4discovery")
  set(CMAKE_CROSSCOMPILING_EMULATOR
    qemu-system-gnuarmeclipse
    --verbose
    --board STM32F4-Discovery
    -d unimp,guest_errors
    --nographic
    --semihosting-config enable=on,target=native
    --image
  )
endif()

# -----------------------------------------------------------------------------

# Bare-metal executables have the .elf extension.
if(CMAKE_SYSTEM_NAME STREQUAL "Generic")
  set(CMAKE_EXECUTABLE_SUFFIX ".elf")
endif()

# -----------------------------------------------------------------------------

add_compile_definitions(
    # NDEBUG provided by the toolchain definitions on release.
    $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">:DEBUG>
    $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">:TRACE>
)

# -----------------------------------------------------------------------------

add_library(micro-test-plus STATIC)

target_include_directories(micro-test-plus
  PUBLIC
    ${xpack_project_folder}/include
  )

target_sources(micro-test-plus
  PRIVATE
    ${xpack_project_folder}/src/micro-test-plus.cpp
  )

# -----------------------------------------------------------------------------

add_subdirectory(tests)

# -----------------------------------------------------------------------------

# Display an empty line, to better see the configuration output.
message(STATUS "")

# -----------------------------------------------------------------------------
