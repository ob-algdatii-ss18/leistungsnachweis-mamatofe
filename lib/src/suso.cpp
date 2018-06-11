#include <iostream>
#include <vector>
#include <set>
#include <map>

#include "suso.h"

bool operator==(const position& lhs, const position& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(const position& lhs, const position& rhs) {
    return !(lhs == rhs);
}

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
                if (res.empty()){
                    throw "Can not solve Sudoku!";
                }
                else if (res.size() == 1) {
                    insertNumber(pos, res[0]);
                    changed = true;
                }
            }
        }
    }
    return changed;
}

bool Sudoku::solveHiddenSingles(){
    bool changed = false;
    struct position pos;
    //Spalten
    for (pos.x = 0; pos.x < 9; pos.x++) {
        std::map<int,position> column;
        for (pos.y = 0; pos.y < 9; pos.y++) {
            if (isEmpty(pos)) {
                std::vector<int> res = validNumbers(pos);
                if (res.empty()){
                    throw "Can not solve Sudoku!";
                }
                for (int i = 0; i < res.size(); i++) {
                    if(column.count(res[i]) == 0) {
                        column[res[i]]= pos;
                    } else {
                        column[res[i]] = INVALID_POS;
                    }
                }
            }
        }
        for (auto i = column.begin(); i != column.end(); i++)
        {
            if(i->second != INVALID_POS){
                insertNumber(i-> second, i->first);
                changed = true;
            }
        }
    }
    //Zeilen
    for (pos.y = 0; pos.y < 9; pos.y++) {
        std::map<int,position> row;
        for (pos.x = 0; pos.x < 9; pos.x++) {
            if (isEmpty(pos)) {
                std::vector<int> res = validNumbers(pos);
                if (res.empty()){
                    throw "Can not solve Sudoku!";
                }
                for (int i = 0; i < res.size(); i++) {
                    if(row.count(res[i]) == 0) {
                        row[res[i]]= pos;
                    } else {
                        row[res[i]] = INVALID_POS;
                    }
                }
            }
        }
        for (auto i = row.begin(); i != row.end(); i++)
        {
            if(i->second != INVALID_POS){
                insertNumber(i-> second, i->first);
                changed = true;
            }
        }
    }
    //Block
    for (int xBlock = 0; xBlock < 9; xBlock +=3){
        for (int yBlock = 0; yBlock < 9; yBlock+=3){
            std::map<int,position> block;
            for (int x = 0; x < 3; x++){
                for (int y = 0; y <3; y++){
                    pos.x = xBlock + x;
                    pos.y = yBlock + y;
                    if (isEmpty(pos)) {
                        std::vector<int> res = validNumbers(pos);
                        if (res.empty()){
                            throw "Can not solve Sudoku!";
                        }
                        for (int i = 0; i < res.size(); i++) {
                            if(block.count(res[i]) == 0) {
                                block[res[i]]= pos;
                            } else {
                                block[res[i]] = INVALID_POS;
                            }
                        }
                    }
                }
            }
            for (auto i = block.begin(); i != block.end(); i++)
            {
                if(i->second != INVALID_POS){
                    insertNumber(i-> second, i->first);
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
    //Alle möglichen Zahlen für die frei Zelle durchprobieren
    std::vector<int> res = validNumbers(pos);
    if (res.empty()){
        throw "Can not solve Sudoku!";
    }
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
