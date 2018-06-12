#include "gtest/gtest.h"
#include "suso.h"


TEST(susoTest, validNumbersTest) {
    Sudoku sudoku;
    sudoku.updateSudoku("./../../../testdata/sudoku.csv");
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
    Sudoku sudoku;
    sudoku.updateSudoku("./../../../testdata/checkSolvability.csv");
    EXPECT_THROW(sudoku.checkSolvability(), std::string);
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

TEST(susoTest, solveBacktracking) {
    Sudoku sudoku;
    sudoku.updateSudoku("./../../../testdata/sudoku.csv");
    bool solved = sudoku.solveBacktracking();
    EXPECT_EQ(solved, true);
    Sudoku solvedSudoku;
    solvedSudoku.updateSudoku("./../../../testdata/solvedSudoku.csv");
    EXPECT_EQ(sudoku == solvedSudoku, true);
}

TEST(susoTest, solveHiddenSingle) {
    Sudoku sudoku,solvedSudoku;
    sudoku.updateSudoku("./../../../testdata/hiddenSingleBlock.csv");
    solvedSudoku.updateSudoku("./../../../testdata/SolHiddenSingleBlock.csv");
    EXPECT_NO_THROW(sudoku.solveHiddenSingles());
    EXPECT_EQ(sudoku == solvedSudoku, true);
    sudoku.updateSudoku("./../../../testdata/hiddenSingleRow.csv");
    solvedSudoku.updateSudoku("./../../../testdata/SolHiddenSingleRow.csv");
    EXPECT_NO_THROW(sudoku.solveHiddenSingles());
    EXPECT_EQ(sudoku == solvedSudoku, true);
    sudoku.updateSudoku("./../../../testdata/hiddenSingleColumn.csv");
    solvedSudoku.updateSudoku("./../../../testdata/SolHiddenSingleColumn.csv");
    EXPECT_NO_THROW(sudoku.solveHiddenSingles());
    EXPECT_EQ(sudoku == solvedSudoku, true);
}