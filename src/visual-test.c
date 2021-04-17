//
// Created by James Clarke on 16/04/2021.
//

#include "gnuplot_i.h"
#include "stdio.h"

int main()
{
    gnuplot_ctrl *h = gnuplot_init();
    gnuplot_cmd(h, "set terminal qt");
    gnuplot_plot_equation(h, "sin(x)", "Test Graph");

    printf("Press enter to close\n");
    scanf(" "); // suspends the program
    gnuplot_close(h);
}