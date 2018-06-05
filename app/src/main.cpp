#include <iostream>
#include <args.hxx>

#include "suso.h"

int main() {
    Sudoku sudoku;
    std::cout << sudoku << std::endl;


    bool changed = true;

    while (changed) {
        changed = sudoku.solveNakedSingles();
    }

    std::cout << sudoku << std::endl;
    return 0;
}