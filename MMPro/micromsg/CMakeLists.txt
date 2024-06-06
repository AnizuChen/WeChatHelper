
cmake_minimum_required (VERSION 3.8)

# project(micromsg)

add_compile_options(/MP)

aux_source_directory(./src micromsg)

add_library(micromsg STATIC  ${micromsg} )

message(STATUS "include directory: ${include_directories}")

target_include_directories(micromsg PUBLIC protobuf)





