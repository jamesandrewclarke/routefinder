add_executable(main main.c)

target_link_libraries(main graph dijkstra dataset gnuplot_i)

add_subdirectory(graph)
add_subdirectory(dijkstra)
add_subdirectory(dataset)