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

  target_link_libraries(unit-test-app PRIVATE platform)

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

  target_link_libraries(sample-test-app PRIVATE platform)

  add_custom_command(
    TARGET sample-test-app POST_BUILD
    COMMAND arm-none-eabi-size --format=berkeley $<TARGET_FILE:sample-test-app>
  )
endif()

# -----------------------------------------------------------------------------

add_test(
  NAME "unit-test"
  COMMAND unit-test-app
)

add_test(
  NAME "sample-test"
  COMMAND sample-test-app
)
