#include "gtest/gtest.h"
#include "suso.h"

TEST(susoTest, validNumbersTest) {
    Sudoku sudoku;
    struct position pos;
    pos.x = 4;
    pos.y = 4;
    EXPECT_EQ(sudoku.validNumbers(pos).size(), 1);
    EXPECT_EQ(sudoku.validNumbers(pos)[0], 5);
    pos.x = 0;
    pos.y = 2;
    EXPECT_EQ(sudoku.validNumbers(pos).size(), 2);
    EXPECT_EQ(sudoku.validNumbers(pos)[0], 1);
    EXPECT_EQ(sudoku.validNumbers(pos)[1], 2);
    pos.x = 8;
    pos.y = 0;
    EXPECT_EQ(sudoku.validNumbers(pos).size(), 3);
    EXPECT_EQ(sudoku.validNumbers(pos)[0], 2);
    EXPECT_EQ(sudoku.validNumbers(pos)[1], 4);
    EXPECT_EQ(sudoku.validNumbers(pos)[2], 8);
}

TEST(susoTest, solveNakedSingleTest) {
    Sudoku sudoku;
    bool changed;
    changed = sudoku.solveNakedSingles();
    EXPECT_EQ(changed, true);
    changed = sudoku.solveNakedSingles();
    EXPECT_EQ(changed, true);
    changed = sudoku.solveNakedSingles();
    EXPECT_EQ(changed, true);
}

TEST(susoTest, checkSolvability) {
    Sudoku sudoku = Sudoku({{       {5, 3, 3, 0, 7, 0, 0, 0, 0},
                                     {6, 0, 0, 1, 9, 5, 0, 0, 0},
                                     {0, 9, 8, 0, 0, 0, 0, 6, 0},
                                     {8, 0, 0, 0, 6, 0, 0, 0, 3},
                                     {4, 0, 0, 8, 0, 3, 0, 0, 1},
                                     {7, 0, 0, 0, 2, 0, 0, 0, 6},
                                     {0, 6, 0, 0, 0, 0, 2, 8, 0},
                                     {0, 0, 0, 4, 1, 9, 0, 0, 5},
                                     {0, 0, 0, 0, 8, 0, 0, 7, 9}}});
    try {
        sudoku.checkSolvability();
        FAIL() << "Expected exception";
    }
    catch(const std::string& e) {
        EXPECT_EQ(e, std::string("Der Wert 3 kommt mehrmals in der Zeile 0 vor."));
    }
    catch(...) {
        FAIL() << "Expected exception";
    }
}

TEST(susoTest, solveBacktracking) {
    Sudoku sudoku;
    bool solved = sudoku.solveBacktracking();
    EXPECT_EQ(solved, true);
    std::array<std::array<int, 9>, 9> solutionField = {{{5, 3, 4, 6, 7, 8, 9, 1, 2},
            {6, 7, 2, 1, 9, 5, 3, 4, 8},
            {1, 9, 8, 3, 4, 2, 5, 6, 7},
            {8, 5, 9, 7, 6, 1, 4, 2, 3},
            {4, 2, 6, 8, 5, 3, 7, 9, 1},
            {7, 1, 3, 9, 2, 4, 8, 5, 6},
            {9, 6, 1, 5, 3, 7, 2, 8, 4},
            {2, 8, 7, 4, 1, 9, 6, 3, 5},
            {3, 4, 5, 2, 8, 6, 1, 7, 9}}};
    Sudoku solvedSudoku = Sudoku(solutionField);
    EXPECT_EQ(sudoku == solvedSudoku, true);
}
