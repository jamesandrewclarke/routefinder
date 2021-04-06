# Route Finder

This program will take a dataset of nodes and paths,compute their shortest route and display a visualisation.

## Setup

External code is located in `extern`. For testing, Unity must be retrieved as a Git submodule using:

```
git submodule update --init
```

### Building

**The project requires an up to date version of CMake (3.15.1)**

On the university Linux machines, this can be loaded by executing `module load cmake/3.15.1`


```
mkdir build
cd build
cmake ..
make
```

Tests can be run using

```
make test
```