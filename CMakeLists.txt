
cmake_minimum_required (VERSION 3.8)

project(WeChatHelper VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(/MP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}    /std:c++17  /MD  /EHsc /FAcs /DWIN32_LEAN_AND_MEAN ")

include_directories(${CMAKE_SOURCE_DIR}/lucky/src)
include_directories(${CMAKE_SOURCE_DIR}/protobuf)
include_directories(${CMAKE_SOURCE_DIR}/MMPro/include)
include_directories(${CMAKE_SOURCE_DIR}/MMPro/micromsg/src)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/mongoose/)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/Detours/include)

set(DETOURS_LIBRARY "${CMAKE_SOURCE_DIR}/3rdparty/Detours/lib.X64/detours.lib")

add_subdirectory(./3rdparty 3rdparty)
add_subdirectory(lucky lucky)
add_subdirectory(protobuf protobuf)
add_subdirectory(MMPro/micromsg micromsg)


add_library(wxhelper SHARED src/DLLMain.cc )

target_include_directories(wxhelper PRIVATE
    ${CMAKE_SOURCE_DIR}/lucky/src
)

target_link_libraries(
     wxhelper
     PRIVATE ${DETOURS_LIBRARY}
     PRIVATE lucky 
     PRIVATE micromsg
     PRIVATE protobuf
     PRIVATE mongoose 
)

SET_TARGET_PROPERTIES(wxhelper PROPERTIES LINKER_LANGUAGE C
                      ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
                      LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
                      OUTPUT_NAME "wxhelper"
                      PREFIX "")


