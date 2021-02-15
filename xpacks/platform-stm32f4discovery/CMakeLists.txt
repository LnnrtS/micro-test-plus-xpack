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

message(STATUS "Including platform-stm32f4discovery...")

# Set global properties that should be applied to any target
# This should contain everything that defines the ABI

macro(set_abi)
set(platform_cpu_option
  -mcpu=cortex-m4
  -mthumb
  -mfloat-abi=soft
)

set(platform_common_options

  -fmessage-length=0
  -fsigned-char
  -ffunction-sections
  -fdata-sections
  -fno-move-loop-invariants

  $<$<COMPILE_LANGUAGE:CXX>:-fabi-version=0>
  # $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>

  # -Wunused
  # -Wuninitialized
  # -Wall
  # -Wextra
  # -Wconversion
  # -Wpointer-arith
  # -Wshadow
  # -Wlogical-op
  # -Wfloat-equal

  # $<$<COMPILE_LANGUAGE:CXX>:-Wctor-dtor-privacy>
  # $<$<COMPILE_LANGUAGE:CXX>:-Wnoexcept>
  # $<$<COMPILE_LANGUAGE:CXX>:-Wnon-virtual-dtor>
  # $<$<COMPILE_LANGUAGE:CXX>:-Wstrict-null-sentinel>
  # $<$<COMPILE_LANGUAGE:CXX>:-Wsign-promo>
)

add_compile_options(
    ${platform_cpu_option}
    ${platform_common_options}
)

add_link_options(
  ${platform_cpu_option}
  ${platform_common_options}
)

#get_target_property(target_output_name "${target}" "OUTPUT_NAME")

add_link_options(
    -nostartfiles
    # nano has no exceptions.
    #-specs=nano.specs
    -Xlinker --gc-sections
    #-Wl,-Map,${target_output_name}.map

    # Including files from other packages is not very nice, but functional.
    # Use absolute paths, otherwise set -L.
    -T${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-platform-stm32f4discovery/linker-scripts/mem.ld
    -T${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-architecture-cortexm/linker-scripts/sections.ld
)

endmacro()
set_abi()

# -----------------------------------------------------------------------------

include("${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-platform-stm32f4discovery/meta/xpack-helper.cmake")
include("${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-devices-stm32f4/meta/xpack-helper.cmake")
include("${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-architecture-cortexm/meta/xpack-helper.cmake")

include("${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-diag-trace/meta/xpack-helper.cmake")
include("${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-libs-c/meta/xpack-helper.cmake")
include("${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-libs-cpp/meta/xpack-helper.cmake")
include("${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-semihosting/meta/xpack-helper.cmake")
include("${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-startup/meta/xpack-helper.cmake")
include("${CMAKE_SOURCE_DIR}/xpacks/micro-os-plus-version/meta/xpack-helper.cmake")

# -----------------------------------------------------------------------------

add_library(test_platform STATIC)

target_include_directories(test_platform
  PUBLIC
    include
  )

target_sources(test_platform
  PRIVATE
    src/initialize-hardware.cpp
    src/interrupts-handlers.cpp
  )

# The preprocessor symbols are defined in micro-os-plus-platform-stm32f4discovery.
target_compile_definitions(test_platform
  PUBLIC
    ${xpack_platform_compile_definition}
    ${xpack_device_compile_definition}
    ${xpack_device_family_compile_definition}

    OS_USE_SEMIHOSTING_SYSCALLS

    $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">:OS_USE_TRACE_SEMIHOSTING_DEBUG>
)

target_sources_micro_os_plus_platform_stm32f4discovery(test_platform)
target_include_directories_micro_os_plus_platform_stm32f4discovery(test_platform)
target_compile_definitions_micro_os_plus_platform_stm32f4discovery(test_platform)
target_options_micro_os_plus_platform_stm32f4discovery(test_platform)

# -----------------------------------------------------------------------------

# Device specific settings.
target_sources_micro_os_plus_device(test_platform)
target_include_directories_micro_os_plus_device(test_platform)

# Architecture specific settings.
target_sources_micro_os_plus_architecture(test_platform)
target_include_directories_micro_os_plus_architecture(test_platform)

# Portable settings.
target_sources_micro_os_plus_diag_trace(test_platform)
target_include_directories_micro_os_plus_diag_trace(test_platform)

target_sources_micro_os_plus_libs_c(test_platform)
target_include_directories_micro_os_plus_libs_c(test_platform)

target_sources_micro_os_plus_libs_cpp(test_platform)
target_include_directories_micro_os_plus_libs_cpp(test_platform)

target_sources_micro_os_plus_semihosting(test_platform)
target_include_directories_micro_os_plus_semihosting(test_platform)

target_sources_micro_os_plus_startup(test_platform)
target_include_directories_micro_os_plus_startup(test_platform)

# Header only, no sources.
target_include_directories_micro_os_plus_version(test_platform)

#---------------------------------------------------------------------
add_library(platform INTERFACE)
target_link_libraries(platform INTERFACE test_platform)
target_link_options(platform INTERFACE
  -Wl,--whole-archive $<TARGET_FILE:test_platform> -Wl,--no-whole-archive
)
