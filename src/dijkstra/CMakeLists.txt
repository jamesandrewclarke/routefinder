add_library(dijkstra include/dijkstra.h dijkstra.c)
add_library(queue queue.c)

target_link_libraries(dijkstra PUBLIC graph queue)
target_include_directories(dijkstra PUBLIC include)
target_include_directories(queue PUBLIC include)