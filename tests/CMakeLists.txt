add_executable(unittest test.c)

target_link_libraries(unittest PUBLIC unity)

add_test(NAME unittest COMMAND unittest)