add_executable(main main.c)

set(include_dirs
        ${PROJECT_SOURCE_DIR}/src/graph/include
        ${PROJECT_SOURCE_DIR}/src/dijkstra/include
        ${PROJECT_SOURCE_DIR}/src/dataset/include
        ${PROJECT_SOURCE_DIR}/extern/gnuplot_i/src)

target_link_libraries(main graph dijkstra dataset gnuplot_i)
target_include_directories(main PUBLIC ${include_dirs})

add_subdirectory(graph)
add_subdirectory(dijkstra)
add_subdirectory(dataset)