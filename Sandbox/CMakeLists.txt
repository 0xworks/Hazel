cmake_minimum_required (VERSION 3.10)

project ("Sandbox" VERSION 0.1 DESCRIPTION "Sandbox demo")

add_executable(
   ${PROJECT_NAME}
   "pch.cpp"
   "src/SandboxApp.cpp"
)

set_target_properties(
   ${PROJECT_NAME} PROPERTIES
   VERSION ${PROJECT_VERSION}
)

add_precompiled_header(${PROJECT_NAME} "pch.h" SOURCE_CXX "pch.cpp")

target_link_libraries(
   ${PROJECT_NAME} PRIVATE
   Hazel
)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets
)
