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

TEST(susoTest, updateSudokuTest) {
Sudoku sudoku1;
Sudoku sudoku2;
Sudoku sudoku3;
Sudoku sudoku4;

sudoku1.updateSudoku("./../../../testdata/sampleBadFile4.csv");
EXPECT_THROW("Can not solve Sudoku!", const char* msg);
sudoku2.updateSudoku("./../../../testdata/sampleBadFile4.csv");
EXPECT_THROW("Can not solve Sudoku!", const char* msg);
sudoku3.updateSudoku("./../../../testdata/sampleBadFile4.csv");
EXPECT_THROW("Can not solve Sudoku!", const char* msg);
sudoku4.updateSudoku("./../../../testdata/sampleBadFile4.csv");
EXPECT_THROW("Can not solve Sudoku!", const char* msg);
}

