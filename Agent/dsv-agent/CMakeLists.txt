cmake_minimum_required(VERSION 3.20)
project(dsv_agent LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_library(dsv_agent SHARED agent/src/interpose.c)
set_target_properties(dsv_agent PROPERTIES OUTPUT_NAME "dsv_agent")

add_executable(list_demo sample/list_demo.cpp)

# warnings on
if(CMAKE_C_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
  target_compile_options(dsv_agent PRIVATE -Wall -Wextra -fvisibility=hidden)
endif()
