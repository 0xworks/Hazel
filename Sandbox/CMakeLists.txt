# CMakeList.txt : CMake project for Sandbox application.
# Sandbox project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

add_executable(
   Sandbox
   "pch.cpp"
   "src/Sandbox.cpp"
)

set_target_properties(
   Sandbox PROPERTIES
   VERSION ${PROJECT_VERSION}
)

add_precompiled_header(Sandbox "pch.h" SOURCE_CXX "pch.cpp")

target_include_directories(
   Sandbox PUBLIC
   "."
   "include"
   "${PROJECT_SOURCE_DIR}/Hazel/include"
)

target_link_libraries(
   Sandbox PUBLIC
   Hazel
   spdlog
)

add_custom_command(
   TARGET Sandbox POST_BUILD 
   COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:Hazel>" "${CMAKE_CURRENT_BINARY_DIR}"
)