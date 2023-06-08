cmake_minimum_required(VERSION 3.21)
project(gef-rx)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions("-DENABLE_MEM_PROFILE")
    add_definitions("-DENABLE_MEM_RECORD")
endif()

add_subdirectory(libs/gef-core)

add_executable(gef-pub src/simple_publisher.c src/kbhit.c libs/mqtt-c/mqtt.c libs/mqtt-c/mqtt_pal.c)

IF(WIN32)
    target_link_libraries(gef-pub gef-core ws2_32 wsock32)
ELSE()
    target_link_libraries(gef-pub gef-core)
ENDIF()

target_include_directories(gef-pub PUBLIC
    inc
)

target_include_directories(gef-pub PRIVATE
    libs/gef-core/inc
    libs/mqtt-c
)

add_executable(gef-sub src/simple_subscriber.c src/kbhit.c libs/mqtt-c/mqtt.c libs/mqtt-c/mqtt_pal.c)

IF(WIN32)
    target_link_libraries(gef-sub gef-core ws2_32 wsock32)
ELSE()
    target_link_libraries(gef-sub gef-core)
ENDIF()

target_include_directories(gef-sub PUBLIC
    inc
)

target_include_directories(gef-sub PRIVATE
    libs/gef-core/inc
    libs/mqtt-c
)
