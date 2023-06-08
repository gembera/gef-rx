cmake_minimum_required(VERSION 3.21)
project(gef-rx)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions("-DENABLE_MEM_PROFILE")
    add_definitions("-DENABLE_MEM_RECORD")
endif()

add_subdirectory(libs/gef-core)


add_executable(gef-pub src/simple_publisher.c libs/mqtt-c/mqtt.c libs/mqtt-c/mqtt_pal.c)

target_link_libraries(gef-pub gef-core)

target_include_directories(gef-pub PUBLIC 
    inc 
)

target_include_directories(gef-pub PRIVATE 
    libs/gef-core/inc
    libs/mqtt-c
)


add_executable(gef-sub src/simple_subscriber.c libs/mqtt-c/mqtt.c libs/mqtt-c/mqtt_pal.c)

target_link_libraries(gef-sub gef-core)

target_include_directories(gef-sub PUBLIC 
    inc 
)

target_include_directories(gef-sub PRIVATE 
    libs/gef-core/inc
    libs/mqtt-c
)
