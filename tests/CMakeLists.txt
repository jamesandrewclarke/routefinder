add_executable(graphtest graph_test.c)

target_link_libraries(graphtest PUBLIC unity graph)
target_include_directories(graphtest PUBLIC "${PROJECT_SOURCE_DIR}/src/graph/include")

add_test(NAME graph COMMAND graphtest)