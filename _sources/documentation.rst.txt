.. _documentation:

Documentation
=============

The application is split into a CLI that can be found under ``app/`` and a library (``suso``) that does all the heavylifting.
You can find the documentation of the library here.

Glossary
--------
.. glossary::

    cell
        The cells are the places of a Sudoku where the numbers are placed.
        A cell can be empty or filled with exactly one number.

    field
        The whole 9x9 grid of a Sudoku with all its 81 cells.

    row
        A row of 9 cells in the field. There are always nine rows in one field.

    column
        A column of 9 cells in the field.
        There are always nine columns in one field.

    block
        A section of the field with 3x3 cells.
        There are nine of these non overlapping sections in one field.
        In the visualized Sudokus they are mostly marked by stronger lines.

    group
        An area where numbers have to be unique in.
        This can be a block, a row or a column.


Library documentation
---------------------

.. doxygenfile:: suso.h
   :project: sudoku
