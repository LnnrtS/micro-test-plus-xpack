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
endmacro()

# -----------------------------------------------------------------------------

# The preprocessor symbols are defined in micro-os-plus-platform-stm32f4discovery.

function(target_sources_micro_os_plus_platform target)

  target_sources(
    ${target}

    PRIVATE
      ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/initialize-hardware.cpp
      ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/src/interrupts-handlers.cpp
  )

  target_sources_micro_os_plus_platform_stm32f4discovery(${target})

endfunction()

function(target_include_directories_micro_os_plus_platform target)

  target_include_directories(
    ${target}

    PRIVATE
      ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/include
  )

  target_include_directories_micro_os_plus_platform_stm32f4discovery(${target})

endfunction()

function(target_compile_definitions_micro_os_plus_platform target)

  target_compile_definitions(
    ${target}

    PRIVATE
      ${xpack_platform_compile_definition}
      ${xpack_device_compile_definition}
      ${xpack_device_family_compile_definition}

      OS_USE_SEMIHOSTING_SYSCALLS

      $<$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">:OS_USE_TRACE_SEMIHOSTING_DEBUG>
  )

  target_compile_definitions_micro_os_plus_platform_stm32f4discovery(${target})

endfunction()

function(target_options_micro_os_plus_platform target)

  get_target_property(target_output_name "${target}" "OUTPUT_NAME")

  target_link_options(
    ${target}

    PRIVATE
      -nostartfiles
      # nano has no exceptions.
      # -specs=nano.specs
      -Xlinker --gc-sections
      -Wl,-Map,${target_output_name}.map

      # Including files from other packages is not very nice, but functional.
      # Use absolute paths, otherwise set -L.
      -T${xpack_project_folder}/xpacks/micro-os-plus-platform-stm32f4discovery/linker-scripts/mem.ld
      -T${xpack_project_folder}/xpacks/micro-os-plus-architecture-cortexm/linker-scripts/sections.ld
  )

  target_options_micro_os_plus_platform_stm32f4discovery(${target})

endfunction()

# -----------------------------------------------------------------------------
