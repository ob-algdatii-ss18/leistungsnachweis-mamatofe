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
    EXPECT_THROW(sudoku.checkSolvability(), std::runtime_error);
}

TEST(susoTest, exceptionHandlingTest) {
    Sudoku sudoku1;
    Sudoku sudoku2;
    Sudoku sudoku3;

    sudoku1.loadFromFile("./../../../testdata/sampleBadFile4.csv");
    EXPECT_THROW(sudoku1.solveNakedSingles(), std::runtime_error);
    sudoku2.loadFromFile("./../../../testdata/sampleBadFile4.csv");
    EXPECT_THROW(sudoku2.solveHiddenSingles(), std::runtime_error);
    sudoku3.loadFromFile("./../../../testdata/sampleBadFile4.csv");
    EXPECT_THROW(sudoku3.solve(Mode::BACKTRACKING), std::runtime_error);
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
    Sudoku sudoku, solvedSudoku;
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

TEST(susoTest, solveSolvable) {
    Sudoku sudoku, solvedSudoku;
    solvedSudoku.loadFromFile("./../../../testdata/sampleFileSol.csv");

    sudoku.loadFromFile("./../../../testdata/sampleFile.csv");
    EXPECT_NO_THROW(sudoku.solve(Mode::DEFAULT));
    EXPECT_EQ(sudoku == solvedSudoku, true);

    sudoku.loadFromFile("./../../../testdata/sampleFile.csv");
    EXPECT_NO_THROW(sudoku.solve(Mode::BACKTRACKING));
    EXPECT_EQ(sudoku == solvedSudoku, true);

    sudoku.loadFromFile("./../../../testdata/sampleFile.csv");
    EXPECT_NO_THROW(sudoku.solve(Mode::LAST_RESORT_BACKTRACKING));
    EXPECT_EQ(sudoku == solvedSudoku, true);

    solvedSudoku.loadFromFile("./../../../testdata/solvedSudoku.csv");

    sudoku.loadFromFile("./../../../testdata/sudoku.csv");
    EXPECT_NO_THROW(sudoku.solve(Mode::NAKED));
    EXPECT_EQ(sudoku == solvedSudoku, true);

    sudoku.loadFromFile("./../../../testdata/sudoku.csv");
    EXPECT_NO_THROW(sudoku.solve(Mode::HIDDEN));
    EXPECT_EQ(sudoku == solvedSudoku, true);
}

TEST(susoTest, solveUnsolvable) {
    Sudoku sudoku;

    sudoku.loadFromFile("./../../../testdata/sampleFile.csv");
    EXPECT_THROW(sudoku.solve(Mode::NAKED), std::runtime_error);

    sudoku.loadFromFile("./../../../testdata/sampleFile.csv");
    EXPECT_THROW(sudoku.solve(Mode::HIDDEN), std::runtime_error);
}
