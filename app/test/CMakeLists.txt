enable_testing()
add_test(NAME sudoku-solverTest COMMAND sudoku-solver ../../../testdata/sampleFile.csv)
add_test(NAME sudoku-solverHelpTest COMMAND sudoku-solver -h)

add_test(NAME sudoku-solverNoFileTest COMMAND sudoku-solver)
add_test(NAME sudoku-solverWrongFlagTest COMMAND sudoku-solver -x)
add_test(NAME sudoku-solverBadFileTest COMMAND sudoku-solver ../../../testdata/sampleBadFile1.csv)
add_test(NAME sudoku-solverUnsolvableTest COMMAND sudoku-solver ../../../testdata/sampleFile.csv -a hidden)
set_tests_properties(
        sudoku-solverNoFileTest
        sudoku-solverWrongFlagTest
        sudoku-solverBadFileTest
        sudoku-solverUnsolvableTest
        PROPERTIES WILL_FAIL true)
