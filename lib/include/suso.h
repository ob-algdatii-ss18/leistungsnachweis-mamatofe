#ifndef __SUSO_H__
#define __SUSO_H__

#include <array>
#include <vector>

/*!
 * A position contains the coordinates of one cell inside a Sudoku field.
 */
struct position {
    /*!
     * The x-component of the coordinate. This can also be described as the
     * number of the column.
     */
    int x;
    /*!
     * The y-component of the coordinate. This can also be described as the
     * number of the row.
     */
    int y;
    /*!
     * Checks equality of two positions.
     */
    //bool operator==(const position& lhs, const position& rhs);
    /*!
     * Checks inequality of two positions.
     */
    //bool operator!=(const position& lhs, const position& rhs);
};

/*!
 * A position.
 */
const struct position INVALID_POS = {-1, -1};

/*!
 * A Sudoku represents the complete field of one Sudoku. It also has functions
 * to solve the Sudoku using different algorithms.
 */
class Sudoku {
private:
    std::array<std::array<int, 9>, 9> field;

    /*!
     * Returns if a given cell is not filled with a number.
     * @param pos the position to check
     * @return true if the cell is empty, false otherwise
     */
    bool isEmpty(position pos);

    /*!
     * Writes a number into the Sudoku field at a given position.
     * No checks of the number are performed.
     * @param pos where to insert the number
     * @param num the number to insert
     */
    void insertNumber(position pos, int num);

public:
    /*!
     * At the moment the constructor creates a Sudoku from a hardcoded array of
     * numbers. This will be fixed soon.
     */
    Sudoku() : field({{       {1, 8, 0, 0, 0, 0, 0, 0, 0},
                              {0, 5, 3, 0, 0, 0, 0, 0, 0},
                              {9, 0, 2, 0, 0, 0, 0, 0, 0},
                              {0, 0, 7, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 7, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0}}}) {};

    /*!
     * This function returns all numbers that could be placed in the cell at the
     * given position so they do not conflict with the numbers already placed in
     * the field.
     * @param pos the position to check
     * @return all possible numbers for the position
     */
    std::vector<int> validNumbers(position pos);

    /*!
     * This function tries to fill cells by searching for naked singles. These
     * are cells where only one number is valid. The function iterates over the
     * whole field and fills in the number when it finds a naked single.
     * @return true if the field has been changed (at least one number filled
     * into a cell), false otherwise
     */
    bool solveNakedSingles();

    /*!
     * This function tries to fill cells by searching for hidden singles. This
     * is a cell that is the only one in a group, that could contain a specific
     * number. The function iterates over all groups and fills in the numbers
     * when it finds hidden singles inside a group.
     * @return true if the field has been changed (at least one number filled
     * into a cell), false otherwise
     */
    bool solveHiddenSingles();

    /*!
     * This function can be used to print out the current state of the Sudoku.
     * Cells that are already filled with a number are printed as the number,
     * empty cells show up as zero.
     */
    friend std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku);

};

#endif // __SUSO_H__