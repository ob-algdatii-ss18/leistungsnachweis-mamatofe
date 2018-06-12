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


TEST(susoTest, exceptionHandlingTest) {
    Sudoku sudoku1;
    Sudoku sudoku2;
    Sudoku sudoku3;

    sudoku1.updateSudoku("./../../../testdata/sampleBadFile4.csv");
    EXPECT_THROW(sudoku1.solveNakedSingles(), std::string);
    sudoku2.updateSudoku("./../../../testdata/sampleBadFile4.csv");
    EXPECT_THROW(sudoku2.solveHiddenSingles(), std::string);
    sudoku3.updateSudoku("./../../../testdata/sampleBadFile4.csv");
    EXPECT_THROW(sudoku3.solve(Modes::BACKTRACKING), std::string);
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


TEST(susoTest, updateSudokuTest) {
    Sudoku sudoku;
    bool success;

    success = sudoku.updateSudoku("./../../../testdata/sampleFile.csv");
    EXPECT_EQ(success, true);
    success = sudoku.updateSudoku("./../../../testdata/sampleBadFile1.csv");
    EXPECT_EQ(success, false);
    success = sudoku.updateSudoku("./../../../testdata/sampleBadFile2.csv");
    EXPECT_EQ(success, false);
    success = sudoku.updateSudoku("./../../../testdata/sampleBadFile3.csv");
    EXPECT_EQ(success, false);
}


