cmake_minimum_required(VERSION 3.20)
project(dsv_agent LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Build the interposer library
add_library(dsv_agent SHARED agent/src/interpose.cpp)
set_target_properties(dsv_agent PROPERTIES OUTPUT_NAME "dsv_agent")

# Link against dl library (for dlsym)
target_link_libraries(dsv_agent PRIVATE ${CMAKE_DL_LIBS})

# Important: Make sure it exports all symbols
if(APPLE)
    target_link_options(dsv_agent PRIVATE -flat_namespace -undefined dynamic_lookup)
endif()

# Build the test program
add_executable(list_demo sample/list_demo.cpp)

# Warnings
if(CMAKE_C_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
  target_compile_options(dsv_agent PRIVATE -Wall -Wextra)
endif()
