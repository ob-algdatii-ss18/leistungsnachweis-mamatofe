.. _usage:

Usage
=====

::

  sudoku-solver {OPTIONS} [file]

    Solves the classical Sudoku game.

  OPTIONS:

      -h, --help                        Display this help
      -a[algorithm], --algo [algorithm] The algorithm that should be used to
                                        solve the Sudoku. Possible values are:
                                        default, naked, hidden, backtracking,
                                        lrb (last_resort_backtracking)
      file                              The file containing the Sudoku to solve
