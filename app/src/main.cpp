#include <iostream>

#include "suso.h"

int main () {
    Sudoku sudoku;
    std::cout << sudoku << std::endl;

    struct position pos;
    pos.x = 2;
    pos.y = 3;

    sudoku.validNumbers(pos);
    return 0;
}