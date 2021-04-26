add_library(dataset dataset.c convert.c)

target_link_libraries(dataset graph)
target_include_directories(dataset PUBLIC include)