cmake_minimum_required(VERSION 3.1O)

#--- SETUP C++ ---
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(compiler-project)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/compiler")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/compiler/*.h" "${CMAKE_SOURCE_DIR}/compiler/*.cpp")
link_directories(/shares/public/tp/ANTLR4-CPP/lib)
include_directories(/shares/public/tp/ANTLR4-CPP/antlr4-runtime)
add_executable(ifcc ${SOURCES})
target_link_libraries(ifcc "-lantlr4-runtime")
