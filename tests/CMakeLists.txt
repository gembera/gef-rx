

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc ${CMAKE_CURRENT_BINARY_DIR})

create_test_sourcelist(tests
    all_test.c
    test_rx.c
)

add_executable(all-gef-rx-tests ${tests})
target_link_libraries(all-gef-rx-tests gef-rx gef-core)

set(all-gef-rx-tests-to-run ${tests})
remove(all-gef-rx-tests-to-run all_test.c)

foreach(test ${all-gef-rx-tests-to-run})
    get_filename_component(tname ${test} NAME_WE)
    add_test(NAME ${tname} COMMAND all-gef-rx-tests ${tname})
endforeach()