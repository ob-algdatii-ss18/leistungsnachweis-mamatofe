.. _build:

Build information
=================

The build process is fully handled by cmake.

.. _build-instr:

Build
-----

To build our application you have to use cmake to set up the project.
To do this you need to follow these steps.

1. Create a new folder in the project root (i.e. ``build/``) that will contain the project configuration.
   Change into this directory.
2. Execute

   .. code-block:: sh

      cmake ..

   to generate all files needed for the build.
3. Execute

   .. code-block:: sh

      cmake --build .

   to fire up the compiler and fully build the application.

You will then find the binary to execute in the build folder under ``app/sudoku-solver``.

Testing
-------

If you want to execute the tests you need to setup the project like described under :ref:`build-instr`.
After that you can execute

.. code-block:: sh

   ctest .

To run all our tests.

Documentation
-------------

Doxygen, Sphinx and breathe need to be installed to generate the documentation.
You have to run these commands to build the documentation:

.. code-block:: sh

    cd doc
    doxygen
    make html
