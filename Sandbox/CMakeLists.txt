# CMakeList.txt : CMake project for Sandbox application.
# Sandbox project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

set(ProjectName Sandbox)

add_executable(
   ${ProjectName}
   "pch.cpp"
   "src/SandboxApp.cpp"
)

set_target_properties(
   ${ProjectName} PROPERTIES
   VERSION ${PROJECT_VERSION}
)

add_precompiled_header(Sandbox "pch.h" SOURCE_CXX "pch.cpp")

target_include_directories(
   ${ProjectName} PUBLIC
)

target_link_libraries(
   ${ProjectName} PUBLIC
   Hazel
)

add_custom_command(
  TARGET ${ProjectName} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets
)
