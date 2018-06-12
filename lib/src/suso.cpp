#include <iostream>
#include <vector>
#include <set>

#include "suso.h"

std::ostream &operator<<(std::ostream &stream, Sudoku &sudoku) {
    position pos;
    for (pos.y = 0; pos.y < 9; pos.y++) {
        for (pos.x = 0; pos.x < 9; pos.x++) {
            if (sudoku.isEmpty(pos)) {
                stream << " ";
            } else {
                stream << sudoku.field[pos.y][pos.x];
            }
            if (pos.x % 3 == 2 && pos.x != 8) {
                stream << " | ";
            } else {
                stream << "  ";
            }
        }
        stream << std::endl;
        if (pos.y % 3 == 2 && pos.y != 8) {
            stream << "--------|---------|--------" << std::endl;
        }
    }
    return stream;
}

bool operator==(const Sudoku &lhs, const Sudoku &rhs) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (lhs.field[i][j] != rhs.field[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::isEmpty(position pos) {
    return field[pos.y][pos.x] == 0;
}

void Sudoku::insertNumber(position pos, int num) {
    field[pos.y][pos.x] = num;
}

std::vector<int> Sudoku::validNumbers(position pos) {
    std::set<int> res;
    int xBlock = (pos.x / 3) * 3;
    int yBlock = (pos.y / 3) * 3;
    int x, y;

    for (int i = 1; i <= 9; i++) {
        res.insert(i);
    }

    for (x = 0; x < 9; x++) {
        res.erase(field[pos.y][x]);
    }

    for (y = 0; y < 9; y++) {
        res.erase(field[y][pos.x]);
    }

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            res.erase(field[yBlock + y][xBlock + x]);
        }
    }

    return std::vector<int>(res.begin(), res.end());
}

bool Sudoku::solveNakedSingles() {
    bool changed = false;
    struct position pos;

    for (pos.x = 0; pos.x < 9; pos.x++) {
        for (pos.y = 0; pos.y < 9; pos.y++) {
            if (isEmpty(pos)) {
                std::vector<int> res = validNumbers(pos);
                if (res.size() == 1) {
                    insertNumber(pos, res[0]);
                    changed = true;
                }
            }
        }
    }
    return changed;
}

bool Sudoku::hasEmptyCell(position &pos) {
    for (pos.x = 0; pos.x < 9; pos.x++) {
        for (pos.y = 0; pos.y < 9; pos.y++) {
            if (isEmpty(pos)) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::solveBacktracking() {
    position pos;
    //Überprüfen, ob es noch eine freie Zelle gibt. Falls ja mit der nächsten weiter machen.
    if (!hasEmptyCell(pos)) {
        return true;
    }
    //Alle möglichen Zahlen für die freie Zelle durchprobieren
    std::vector<int> res = validNumbers(pos);
    for (std::vector<int>::size_type i = 0; i < res.size(); i++) {
        insertNumber(pos, res[i]);
        //Mit nächster Zelle weitermachen
        if (solveBacktracking()) {
            return true;
        }
        insertNumber(pos, 0); //Zelle zurücksetzen
    }
    return false;
}