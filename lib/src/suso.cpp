#include <iostream>

#include "suso.h"

std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku) {
    for (const auto &line : sudoku.field) {
        for (const auto &cell : line) {
            stream << cell << "  ";
        }
        stream << std::endl;
    }
    return stream;
}
