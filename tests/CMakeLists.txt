add_executable(graphtest graph_test.c)
add_executable(dijkstratest dijkstra_test.c)
add_executable(queuetest queue_test.c)
add_executable(datasettest dataset_test.c)

set(include_dirs
        ${PROJECT_SOURCE_DIR}/src/graph/include
        ${PROJECT_SOURCE_DIR}/src/algorithms/include
        ${PROJECT_SOURCE_DIR}/src/dataset/include
)

target_link_libraries(graphtest PUBLIC unity graph)
target_include_directories(graphtest PUBLIC ${include_dirs})

target_link_libraries(dijkstratest PUBLIC unity dijkstra queue)
target_include_directories(dijkstratest PUBLIC ${include_dirs})

target_link_libraries(queuetest PUBLIC unity queue)
target_include_directories(queuetest PUBLIC ${include_dirs})

target_link_libraries(datasettest PUBLIC unity dataset)
target_include_directories(datasettest PUBLIC ${include_dirs})

add_test(NAME graph COMMAND graphtest)
add_test(NAME dijkstra COMMAND dijkstratest)
add_test(NAME queue COMMAND queuetest)
add_test(NAME dataset COMMAND datasettest)