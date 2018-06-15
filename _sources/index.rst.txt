.. _index:

Sudoku-Solver
=============

Build instructions
------------------

To build and test the project, execute the following commands:

.. code-block:: sh

    mkdir build
    cd build
    cmake ..
    cmake --build .
    ctest .

If you only want to run the application, you will find the binary under ``build/app/sudoku-solver``.
More information about the build can be found under :ref:`build`.

.. toctree::
   :maxdepth: 2
   :hidden:

   build
   usage
   documentation
