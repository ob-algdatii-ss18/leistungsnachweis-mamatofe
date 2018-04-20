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
    Sudoku();

    std::vector<int> validNumbers(position pos);

    bool solveNakedSingles();
    bool solveHiddenSngles();

    friend std::ostream& operator<< (std::ostream& stream, const Sudoku& sudoku);
};

#endif // __SUSO_H__