cmake_minimum_required(VERSION 3.18)

add_executable(unit-test-app)

# Source folders.
target_sources(
  unit-test-app

  PRIVATE
    unit-test.cpp
)

target_link_libraries(unit-test-app
  PRIVATE
    micro-test-plus
)

if(PLATFORM_NAME STREQUAL "stm32f4discovery")

  # Platform specific settings.
  target_sources_micro_os_plus_platform(unit-test-app)
  target_include_directories_micro_os_plus_platform(unit-test-app)
  target_compile_definitions_micro_os_plus_platform(unit-test-app)
  # Many interesting things come from the platfrom specific definitions.
  target_options_micro_os_plus_platform(unit-test-app)

  # Device specific settings.
  target_sources_micro_os_plus_device(unit-test-app)
  target_include_directories_micro_os_plus_device(unit-test-app)

  # Architecture specific settings.
  target_sources_micro_os_plus_architecture(unit-test-app)
  target_include_directories_micro_os_plus_architecture(unit-test-app)

  # Portable settings.
  target_sources_micro_os_plus_diag_trace(unit-test-app)
  target_include_directories_micro_os_plus_diag_trace(unit-test-app)

  target_sources_micro_os_plus_libs_c(unit-test-app)
  target_include_directories_micro_os_plus_libs_c(unit-test-app)

  target_sources_micro_os_plus_libs_cpp(unit-test-app)
  target_include_directories_micro_os_plus_libs_cpp(unit-test-app)

  target_sources_micro_os_plus_semihosting(unit-test-app)
  target_include_directories_micro_os_plus_semihosting(unit-test-app)

  target_sources_micro_os_plus_startup(unit-test-app)
  target_include_directories_micro_os_plus_startup(unit-test-app)

  # Header only, no sources.
  target_include_directories_micro_os_plus_version(unit-test-app)

  add_custom_command(
    TARGET unit-test-app POST_BUILD
    COMMAND arm-none-eabi-size --format=berkeley $<TARGET_FILE:unit-test-app>
  )

endif()

# -----------------------------------------------------------------------------

add_executable(sample-test-app)

# Application sources.
target_sources(
  sample-test-app

  PRIVATE
    sample-test.cpp
)

target_link_libraries(sample-test-app
  PRIVATE
    micro-test-plus
)

if(PLATFORM_NAME STREQUAL "stm32f4discovery")

  # Platform specific settings.
  target_sources_micro_os_plus_platform(sample-test-app)
  target_include_directories_micro_os_plus_platform(sample-test-app)
  target_compile_definitions_micro_os_plus_platform(sample-test-app)
  # Many interesting things come from the platfrom specific definitions.
  target_options_micro_os_plus_platform(sample-test-app)

  # Device specific settings.
  target_sources_micro_os_plus_device(sample-test-app)
  target_include_directories_micro_os_plus_device(sample-test-app)

  # Architecture specific settings.
  target_sources_micro_os_plus_architecture(sample-test-app)
  target_include_directories_micro_os_plus_architecture(sample-test-app)

  # Portable settings.
  target_sources_micro_os_plus_diag_trace(sample-test-app)
  target_include_directories_micro_os_plus_diag_trace(sample-test-app)

  target_sources_micro_os_plus_libs_c(sample-test-app)
  target_include_directories_micro_os_plus_libs_c(sample-test-app)

  target_sources_micro_os_plus_libs_cpp(sample-test-app)
  target_include_directories_micro_os_plus_libs_cpp(sample-test-app)

  target_sources_micro_os_plus_semihosting(sample-test-app)
  target_include_directories_micro_os_plus_semihosting(sample-test-app)

  target_sources_micro_os_plus_startup(sample-test-app)
  target_include_directories_micro_os_plus_startup(sample-test-app)

  # Header only, no sources.
  target_include_directories_micro_os_plus_version(sample-test-app)

  add_custom_command(
    TARGET sample-test-app POST_BUILD
    COMMAND arm-none-eabi-size --format=berkeley $<TARGET_FILE:sample-test-app>
  )

endif()

# -----------------------------------------------------------------------------

enable_testing()

add_test(
  NAME "unit-test"
  COMMAND unit-test-app
)

add_test(
  NAME "sample-test"
  COMMAND sample-test-app
)
