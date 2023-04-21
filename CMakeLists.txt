cmake_minimum_required(VERSION 3.21)
project(gef-rx)

include(CheckTypeSize)

aux_source_directory(src DIR_SRC)

add_library(gef-rx STATIC ${DIR_SRC})

add_subdirectory(libs/gef-core)

option(ENABLE_MEM_PROFILE "Enable memory profiling" OFF)
option(ENABLE_MEM_RECORD "Enable memory record" OFF)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(ENABLE_MEM_PROFILE ON)
    set(ENABLE_MEM_RECORD ON)
endif()

target_include_directories(gef-rx PUBLIC 
    inc 
    ${CMAKE_CURRENT_BINARY_DIR}/libs/gef-core
    libs/gef-core/inc
)

if(PROJECT_IS_TOP_LEVEL AND CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "${PROJECT_NAME} enables testing.")
    enable_testing()
    add_subdirectory(tests)
endif()