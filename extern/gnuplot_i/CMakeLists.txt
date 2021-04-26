# Added by James Clarke

add_library(gnuplot_i src/gnuplot_i.c)

target_include_directories(gnuplot_i PUBLIC src)

set_property(TARGET gnuplot_i PROPERTY C_STANDARD 90)