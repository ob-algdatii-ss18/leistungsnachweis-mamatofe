#ifndef __SUSO_H__
#define __SUSO_H__

#include <array>
#include <vector>

struct position {
    int x, y;
};

class Sudoku {
private:
    std::array<std::array<int, 9>, 9> field;
public:
    Sudoku() : field({{{5, 3, 0, 0, 7, 0, 0, 0, 0},
                              {6, 0, 0, 1, 9, 5, 0, 0, 0},
                              {0, 9, 8, 0, 0, 0, 0, 6, 0},
                              {8, 0, 0, 0, 6, 0, 0, 0, 3},
                              {4, 0, 0, 8, 0, 3, 0, 0, 1},
                              {7, 0, 0, 0, 2, 0, 0, 0, 6},
                              {0, 6, 0, 0, 0, 0, 2, 8, 0},
                              {0, 0, 0, 4, 1, 9, 0, 0, 5},
                              {0, 0, 0, 0, 8, 0, 0, 7, 9}}}) {};

    std::vector<int> validNumbers(position pos);

    bool solveNakedSingles();

    bool solveHiddenSngles();

    friend std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku);
};

#endif // __SUSO_H__