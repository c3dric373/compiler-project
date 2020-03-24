cmake_minimum_required(VERSION 3.13)

#--- SETUP C++ ---
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(compiler-project)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/compiler")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/compiler/*.h" "${CMAKE_SOURCE_DIR}/compiler/*.cpp")

add_executable(ifcc ${SOURCES} tests/tests/Init/5_definition.c tests/tests/Init/2_affectation.c tests/tests/Init/3_declaration.c tests/tests/Init/4_defdeclexpr.c)
target_link_libraries(ifcc "-lantlr4-runtime")
include_directories(/usr/include/antlr4-runtime)

