# [Sudoku-Solver](https://ob-algdatii-ss18.github.io/leistungsnachweis-mamatofe/)

[![Build Status](https://travis-ci.org/ob-algdatii-ss18/leistungsnachweis-mamatofe.svg?branch=master)](https://travis-ci.org/ob-algdatii-ss18/leistungsnachweis-mamatofe)
[![Coverage Status](https://coveralls.io/repos/github/ob-algdatii-ss18/leistungsnachweis-mamatofe/badge.svg?branch=master)](https://coveralls.io/github/ob-algdatii-ss18/leistungsnachweis-mamatofe?branch=master)

## Build instructions

To build and test the project, execute the following commands:

```sh
mkdir build
cd build
cmake ..
cmake --build .
ctest .
```

If you only want to run the application, you will find the binary under `build/app/sudoku-solver`.

## Documentation

Doxygen, Sphinx and breathe need to be installed to generate the documentation.
You have to run these commands: 

```sh
cd doc
doxygen
make html
``` 

The documentation can also be found online under [https://ob-algdatii-ss18.github.io/leistungsnachweis-mamatofe/](https://ob-algdatii-ss18.github.io/leistungsnachweis-mamatofe/).
