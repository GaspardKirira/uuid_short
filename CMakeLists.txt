cmake_minimum_required(VERSION 3.20)
project(uuid_short LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(uuid_short INTERFACE)
add_library(uuid_short::uuid_short ALIAS uuid_short)

target_include_directories(uuid_short INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(uuid_short INTERFACE /W4 /permissive-)
else()
  target_compile_options(uuid_short INTERFACE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
enable_testing()

add_executable(uuid_short_basic_test tests/test_basic.cpp)
target_link_libraries(uuid_short_basic_test PRIVATE uuid_short::uuid_short)
add_test(NAME uuid_short.basic COMMAND uuid_short_basic_test)
