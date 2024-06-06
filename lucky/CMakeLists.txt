
cmake_minimum_required (VERSION 3.8)

#project(lucky VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()


message(${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(/MP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}    /std:c++17  /MD  /EHsc /FAcs")


file(GLOB_RECURSE CPP_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c )

file(GLOB_RECURSE ASM_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.asm )

add_library(lucky STATIC  ${CPP_FILES} ${ASM_FILES})

target_compile_definitions(lucky PRIVATE WECHAT_VERSION=391019)




