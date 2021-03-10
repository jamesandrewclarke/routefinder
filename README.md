# Route Finder

Given a set of nodes and edges connecting them, this program will compute the shortest path between two nodes.

## Setup

This repository contains submodules, their source must be retrieved using:

```
git submodule update --init
```

### Building

Create a build directory e.g. `build`

```
mkdir build
```

```
cd build
cmake ..
make
```

Tests can be run using

```
make test
```