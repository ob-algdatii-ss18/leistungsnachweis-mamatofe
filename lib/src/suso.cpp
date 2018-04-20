#include <iostream>

#include "suso.h"

Sudoku::Sudoku() {
    field = {{{5, 3, 0, 0, 7, 0, 0, 0, 0},
                     {6, 0, 0, 1, 9, 5, 0, 0, 0},
                     {0, 9, 8, 0, 0, 0, 0, 6, 0},
                     {8, 0, 0, 0, 6, 0, 0, 0, 3},
                     {4, 0, 0, 8, 0, 3, 0, 0, 1},
                     {7, 0, 0, 0, 2, 0, 0, 0, 6},
                     {0, 6, 0, 0, 0, 0, 2, 8, 0},
                     {0, 0, 0, 4, 1, 9, 0, 0, 5},
                     {0, 0, 0, 0, 8, 0, 0, 7, 9}}};
}

std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku) {
    for (const auto& line : sudoku.field) {
        for (const auto& cell : line) {
            stream << cell << "  ";
        }
        stream << std::endl;
    }
    return stream;
}
