#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>

#include "suso.h"

bool operator==(const Position& lhs, const Position& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(const Position& lhs, const Position& rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &stream, const Metrics &metrics) {
    stream << "Cells filled by definition: " << metrics.given << std::endl;
    stream << "Numbers found by searching naked singles: " << metrics.solvedNaked << std::endl;
    stream << "Numbers found by searching hidden Singles: " << metrics.solvedHidden << std::endl;
    stream << "Numbers found by backtracking: " << metrics.solvedBacktracking << std::endl;
    stream << "Time used: " << metrics.duration.count() << "ms" << std::endl;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, Sudoku &sudoku) {
    Position pos;
    for (pos.y = 0; pos.y < 9; pos.y++) {
        stream << " ";
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
            stream << "---------|---------|---------" << std::endl;
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

Metrics Sudoku::getSolvingMetrics() {
    return metrics;
}

bool Sudoku::isEmpty(Position pos) {
    return field[pos.y][pos.x] == 0;
}

void Sudoku::insertNumber(Position pos, int num) {
    field[pos.y][pos.x] = num;
}

std::vector<int> Sudoku::validNumbers(Position pos) {
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

bool Sudoku::solveNakedSingles() throw(std::string){
    bool changed = false;
    Position pos;

    for (pos.x = 0; pos.x < 9; pos.x++) {
        for (pos.y = 0; pos.y < 9; pos.y++) {
            if (isEmpty(pos)) {
                std::vector<int> res = validNumbers(pos);
                if (res.empty()){
                    throw std::string("Can not solve Sudoku, there are no valid numbers at:" + std::to_string(pos.x) + "," + std::to_string(pos.y));
                }
                else if (res.size() == 1) {
                    insertNumber(pos, res[0]);
                    metrics.solvedNaked++;
                    changed = true;
                }
            }
        }
    }
    return changed;
}

bool Sudoku::solveHiddenSingles() throw(std::string){
    bool changed = false;
    Position pos;
    //Spalten
    for (pos.x = 0; pos.x < 9; pos.x++) {
        std::map<int,Position> column;
        for (pos.y = 0; pos.y < 9; pos.y++) {
            if (isEmpty(pos)) {
                std::vector<int> res = validNumbers(pos);
                if (res.empty()){
                    throw std::string("Can not solve Sudoku, there are no valid numbers at:" + std::to_string(pos.x) + "," + std::to_string(pos.y));
                }
                for (unsigned int i = 0; i < res.size(); i++) {
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
                metrics.solvedHidden++;
                changed = true;
            }
        }
    }
    //Zeilen
    for (pos.y = 0; pos.y < 9; pos.y++) {
        std::map<int,Position> row;
        for (pos.x = 0; pos.x < 9; pos.x++) {
            if (isEmpty(pos)) {
                std::vector<int> res = validNumbers(pos);
                if (res.empty()){
                    throw std::string("Can not solve Sudoku, there are no valid numbers at:" + std::to_string(pos.x) + "," + std::to_string(pos.y));
                }
                for (unsigned int i = 0; i < res.size(); i++) {
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
                metrics.solvedHidden++;
                changed = true;
            }
        }
    }
    //Block
    for (int xBlock = 0; xBlock < 9; xBlock +=3){
        for (int yBlock = 0; yBlock < 9; yBlock+=3){
            std::map<int,Position> block;
            for (int x = 0; x < 3; x++){
                for (int y = 0; y <3; y++){
                    pos.x = xBlock + x;
                    pos.y = yBlock + y;
                    if (isEmpty(pos)) {
                        std::vector<int> res = validNumbers(pos);
                        if (res.empty()){
                            throw std::string("Can not solve Sudoku, there are no valid numbers at:" + std::to_string(pos.x) + "," + std::to_string(pos.y));
                        }
                        for (unsigned int i = 0; i < res.size(); i++) {
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
                    metrics.solvedHidden++;
                    changed = true;
                }
            }
        }
    }

    return changed;
}

bool Sudoku::getNextEmptyCell(Position &pos) {
    for (pos.x = 0; pos.x < 9; pos.x++) {
        for (pos.y = 0; pos.y < 9; pos.y++) {
            if (isEmpty(pos)) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::solveBacktracking(){
    Position pos;
    //Überprüfen, ob es noch eine freie Zelle gibt. Falls ja mit der nächsten weiter machen.
    if (!getNextEmptyCell(pos)) {
        return true;
    }
    //Alle möglichen Zahlen für die freie Zelle durchprobieren
    std::vector<int> res = validNumbers(pos);
    for (std::vector<int>::size_type i = 0; i < res.size(); i++) {
        insertNumber(pos, res[i]);
        //Mit nächster Zelle weitermachen
        if (solveBacktracking()) {
            metrics.solvedBacktracking++;
            return true;
        }
    }
    insertNumber(pos, 0); //Zelle zurücksetzen
    return false;
}

void Sudoku::checkSolvability() const throw(std::string) {
    //Zeilen überprüfen
    for (int i = 0; i < 9; i++) {
        std::vector<int> numbers;
        for (int j = 0; j < 9; j++) {
            numbers.push_back(field[i][j]);
        }
        std::sort(numbers.begin(), numbers.end());
        for (int k = 0; k < numbers.size() - 1; k++) {
            if (numbers[k] != 0 && numbers[k] == numbers[k + 1]) {
                throw std::string("Row " + std::to_string(i) + " contains number '" + std::to_string(numbers[k]) +"' multiple times.");
            }
        }
    }
    //Spalten überprüfen
    for (int i = 0; i < 9; i++) {
        std::vector<int> numbers;
        for (int j = 0; j < 9; j++) {
            numbers.push_back(field[j][i]);
        }
        std::sort(numbers.begin(), numbers.end());
        for (int k = 0; k < numbers.size() - 1; k++) {
            if (numbers[k] != 0 && numbers[k] == numbers[k + 1]) {
                throw std::string("Column " + std::to_string(i) + " contains number '" + std::to_string(numbers[k]) +"' multiple times.");
            }
        }
    }
    //Blöcke überprüfen
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::vector<int> numbers;
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    numbers.push_back(field[i * 3 + k][j * 3 + l]);
                }
            }
            std::sort(numbers.begin(), numbers.end());
            for (int m = 0; m < numbers.size() - 1; m++) {
                if (numbers[m] != 0 && numbers[m] == numbers[m + 1]) {
                    throw std::string("Block (" + std::to_string(i) + ", " + std::to_string(j) + ") contains number '" + std::to_string(numbers[m]) +"' multiple times.");
                }
            }
        }
    }
}

bool Sudoku::loadFromFile(std::string path) {
    bool res = false;
    std::ifstream fin;
    fin.open(path, std::ios::in);

    bool write = true;
    char read_character;
    int line_number = 0;
    int column_number = 0;

    while (!fin.eof()) {
        fin.get(read_character);

        if (read_character == '\n') {
            if (column_number == 8 || (column_number == 0 && line_number > 8)) {
                ++line_number;
                column_number = 0;
                write = true;
            } else {
                std::cout << "line error at " << line_number << "," << column_number << std::endl;
                res = false;
                break;
            }

        } else if (read_character == ',') {
            if (column_number < 8) {
                ++column_number;
                write = true;
            } else {
                std::cout << "Too many symbols in line " << std::to_string(line_number) << std::endl;
                res = false;
                break;
            };
        } else if (isdigit(read_character)) {
            int number = read_character - '0';

            if (number < 0 || number > 9 || line_number > 8 || column_number > 8 || !write) {
                res = false;
                break;
            } else {
                Position pos;
                pos.x = column_number;
                pos.y = line_number;
                insertNumber(pos, number);
                if (number > 0) {
                    metrics.given++;
                }
                write = false;
                res = true;
            }
        } else {
            res = false;
            break;
        }
    }

    fin.close();

    return res;
}

void Sudoku::solve(Mode algorithm) throw(std::string){
    auto start = std::chrono::high_resolution_clock::now();
    if(algorithm == Mode::DEFAULT){
        bool changed;
        //Naked Singles
        do {
            changed = solveNakedSingles();
        } while (changed);
        //Hidden Single
        do {
            changed = solveHiddenSingles();
        } while (changed);
        //Backtracking
        if(!solveBacktracking()){
            throw std::string("Can not solve Sudoku, backtracking has failed.");
        }
    }
    else if(algorithm == Mode::BACKTRACKING){
        if(!solveBacktracking()){
            throw std::string("Can not solve Sudoku, backtracking has failed.");
        }
    }
    else if(algorithm == Mode::LAST_RESORT_BACKTRACKING){
        bool changed;
        //Naked Singles
        do {
            changed = solveNakedSingles();
            if (!changed){
                changed = solveHiddenSingles();
            }
        } while (changed);
        if(!solveBacktracking()){
            throw std::string("Can not solve Sudoku, backtracking has failed.");
        }
    }
    else if(algorithm == Mode::HIDDEN) {
        bool changed;
        do {
            changed = solveHiddenSingles();
        } while (changed);
        Position pos;
        if(getNextEmptyCell(pos)) {
            throw std::string("Can not solve Sudoku, hidden single has failed.");
        }
    }
    else if(algorithm == Mode::NAKED) {
        bool changed;
        do {
            changed = solveNakedSingles();
        } while (changed);
        Position pos;
        if(getNextEmptyCell(pos)) {
            throw std::string("Can not solve Sudoku, naked single has failed.");
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    metrics.duration = end - start;
}
