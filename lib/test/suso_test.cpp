#include "gtest/gtest.h"
#include "suso.h"
#include "direct.h"
#include <iostream>

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
Sudoku sudoku;
bool success;

char buff[FILENAME_MAX];
getcwd( buff, FILENAME_MAX );
std::string current_working_dir(buff);

std::cout <<"Test" << current_working_dir << std::endl;
success = sudoku.updateSudoku("./../../../testdata/sampleFile.csv");
EXPECT_EQ(success, true);
success = sudoku.updateSudoku("./../../../testdata/sampleBadFile1.csv");
EXPECT_EQ(success, false);
success = sudoku.updateSudoku("./../../../testdata/sampleBadFile2.csv");
EXPECT_EQ(success, false);
success = sudoku.updateSudoku("./../../../testdata/sampleBadFile3.csv");
EXPECT_EQ(success, false);
}

