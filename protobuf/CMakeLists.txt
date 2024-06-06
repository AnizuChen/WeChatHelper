
cmake_minimum_required (VERSION 3.8)

# project(protobuf)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE PROTOBUF_SOURCE "*.cc")

add_library(protobuf STATIC ${PROTOBUF_SOURCE} ${CMAKE_CURRENT_SOURCE_DIR})

# target_compile_definitions(protobuf PUBLIC _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS=1)

target_include_directories(protobuf PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf)




