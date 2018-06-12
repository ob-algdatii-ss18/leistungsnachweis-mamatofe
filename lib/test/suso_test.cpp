#include "gtest/gtest.h"
#include "suso.h"


TEST(susoTest, validNumbersTest) {
    Sudoku sudoku;
    sudoku.loadFromFile("./../../../testdata/sudoku.csv");
    Position pos;
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
    sudoku.loadFromFile("./../../../testdata/sudoku.csv");
    changed = sudoku.solveNakedSingles();
    EXPECT_EQ(changed, true);
    changed = sudoku.solveNakedSingles();
    EXPECT_EQ(changed, true);
    changed = sudoku.solveNakedSingles();
    EXPECT_EQ(changed, true);
}

TEST(susoTest, checkSolvability) {
    Sudoku sudoku;
    sudoku.loadFromFile("./../../../testdata/checkSolvability.csv");
    EXPECT_THROW(sudoku.checkSolvability(), std::string);
}

TEST(susoTest, exceptionHandlingTest) {
    Sudoku sudoku1;
    Sudoku sudoku2;
    Sudoku sudoku3;

    sudoku1.loadFromFile("./../../../testdata/sampleBadFile4.csv");
    EXPECT_THROW(sudoku1.solveNakedSingles(), std::string);
    sudoku2.loadFromFile("./../../../testdata/sampleBadFile4.csv");
    EXPECT_THROW(sudoku2.solveHiddenSingles(), std::string);
    sudoku3.loadFromFile("./../../../testdata/sampleBadFile4.csv");
    EXPECT_THROW(sudoku3.solve(Mode::BACKTRACKING), std::string);
}

TEST(susoTest, updateSudokuTest) {
    Sudoku sudoku;
    bool success;

    success = sudoku.loadFromFile("./../../../testdata/sampleFile.csv");
    EXPECT_EQ(success, true);
    success = sudoku.loadFromFile("./../../../testdata/sampleBadFile1.csv");
    EXPECT_EQ(success, false);
    success = sudoku.loadFromFile("./../../../testdata/sampleBadFile2.csv");
    EXPECT_EQ(success, false);
    success = sudoku.loadFromFile("./../../../testdata/sampleBadFile3.csv");
    EXPECT_EQ(success, false);
}

TEST(susoTest, solveBacktracking) {
    Sudoku sudoku;
    sudoku.loadFromFile("./../../../testdata/sudoku.csv");
    bool solved = sudoku.solveBacktracking();
    EXPECT_EQ(solved, true);
    Sudoku solvedSudoku;
    solvedSudoku.loadFromFile("./../../../testdata/solvedSudoku.csv");
    EXPECT_EQ(sudoku == solvedSudoku, true);
}

TEST(susoTest, solveHiddenSingle) {
    Sudoku sudoku,solvedSudoku;
    sudoku.loadFromFile("./../../../testdata/hiddenSingleBlock.csv");
    solvedSudoku.loadFromFile("./../../../testdata/SolHiddenSingleBlock.csv");
    EXPECT_NO_THROW(sudoku.solveHiddenSingles());
    EXPECT_EQ(sudoku == solvedSudoku, true);
    sudoku.loadFromFile("./../../../testdata/hiddenSingleRow.csv");
    solvedSudoku.loadFromFile("./../../../testdata/SolHiddenSingleRow.csv");
    EXPECT_NO_THROW(sudoku.solveHiddenSingles());
    EXPECT_EQ(sudoku == solvedSudoku, true);
    sudoku.loadFromFile("./../../../testdata/hiddenSingleColumn.csv");
    solvedSudoku.loadFromFile("./../../../testdata/SolHiddenSingleColumn.csv");
    EXPECT_NO_THROW(sudoku.solveHiddenSingles());
    EXPECT_EQ(sudoku == solvedSudoku, true);
}