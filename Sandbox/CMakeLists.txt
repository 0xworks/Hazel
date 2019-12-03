# CMakeList.txt : CMake project for Sandbox application.
# Sandbox project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

add_executable(
   Sandbox
   "pch.cpp"
   "src/SandboxApp.cpp"
   "../vendor/Tracy/TracyClient.cpp"
)

set_target_properties(
   Sandbox PROPERTIES
   VERSION ${PROJECT_VERSION}
)

add_precompiled_header(Sandbox "pch.h" SOURCE_CXX "pch.cpp")

# no precompiled header for TracyClient.cpp
set_source_files_properties(
   "../vendor/Tracy/TracyClient.cpp" PROPERTIES
   COMPILE_FLAGS /Y-
)

target_include_directories(
   Sandbox PUBLIC
   "."
   "include"
   "${PROJECT_SOURCE_DIR}/Hazel/include"
)

target_link_libraries(
   Sandbox PUBLIC
   Hazel
   glm
   spdlog
)

add_custom_command(
  TARGET Sandbox POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets
    ${CMAKE_CURRENT_BINARY_DIR}/Assets
)
