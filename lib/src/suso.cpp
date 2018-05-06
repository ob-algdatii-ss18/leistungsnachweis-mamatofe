#include <iostream>
#include <set>

#include "suso.h"

Sudoku::Sudoku() {
    field = {{{5, 3, 0, 0, 7, 0, 0, 0, 0},
                     {6, 0, 0, 1, 9, 5, 0, 0, 0},
                     {0, 9, 8, 0, 0, 0, 0, 6, 0},
                     {8, 0, 0, 0, 6, 0, 0, 0, 3},
                     {4, 0, 0, 8, 0, 3, 0, 0, 1},
                     {7, 0, 0, 0, 2, 0, 0, 0, 6},
                     {0, 6, 0, 0, 0, 0, 2, 8, 0},
                     {0, 0, 0, 4, 1, 9, 0, 0, 5},
                     {0, 0, 0, 0, 8, 0, 0, 7, 9}}};
}

std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku) {
    for (const auto& line : sudoku.field) {
        for (const auto& cell : line) {
            stream << cell << "  ";
        }
        stream << std::endl;
    }
    return stream;
}

std::vector<int> Sudoku::validNumbers(position pos) {
    std::set<int> posNumbers;
    std::vector<int> res;

    for(int i = 0; i<9; i++){
        posNumbers.insert(i+1);
    }

    for(int j = 0; j< 9; j++){
        posNumbers.erase(field[j][pos.y]);
    }

    for(int k = 0; k< 9; k++){
        posNumbers.erase(field[pos.x][k]);
    }

    int xBlock = (pos.x / 3) * 3;
    int yBlock = (pos.y / 3) *3;

    for (int l = 0; l < 3; l++){
        for(int m = 0; m < 3; m++){
            posNumbers.erase(field[xBlock + l][yBlock + m]);
        }
    }

    for (std::set<int>::iterator it=posNumbers.begin(); it!=posNumbers.end(); ++it){
        res.push_back(*it);
    }
    return res;
}

bool Sudoku::solveNakedSingles(){
    bool changed = false;
    struct position pos;

    for(int k = 0; k<9; k++){
        for(int l = 0; l<9; l++){
            pos.x = k;
            pos.y = l;
            std::vector<int> res = validNumbers(pos);

            if(res.size() == 1 && field[k][l] == 0) {
                field[k][l] = res[0];
                changed = true;
            }
        }
    }
    return changed;
}
