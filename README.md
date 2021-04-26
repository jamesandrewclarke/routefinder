# Route Finder

This program will take a dataset of nodes and paths, compute their shortest route and display a visualisation.

## Build Instructions

Unity must first be retrieved as a Git submodule using:

```
git submodule update --init
```


**The project targets a minimum CMake version of 3.13**

On the university Linux machines, this can be loaded by executing `module load cmake/3.15.1`


```
mkdir build && cd build
cmake ..
make
```

The test suite can be run by executing `make test` in the build directory.

## Usage

The main executable is called `main`, located in `build/src`. Instructions for using the program can be fonud using `./main --help`.

Each node in the .map file is assigned an incremental unique ID, for example you can instruct the program to find a route between nodes `4` and `77` by running `./main 4 77`. To show a visualisation of the route in gnuplot, add the `-v` option.