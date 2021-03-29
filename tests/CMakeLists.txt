add_executable(graphtest graph_test.c)
add_executable(dijkstratest dijkstra_test.c)

set(include_dirs
        ${PROJECT_SOURCE_DIR}/src/graph/include
        ${PROJECT_SOURCE_DIR}/src/algorithms/include
)

target_link_libraries(graphtest PUBLIC unity graph)
target_include_directories(graphtest PUBLIC ${include_dirs})

target_link_libraries(dijkstratest PUBLIC unity dijkstra)
target_include_directories(dijkstratest PUBLIC ${include_dirs})

add_test(NAME graph COMMAND graphtest)
add_test(NAME dijkstra COMMAND dijkstratest)