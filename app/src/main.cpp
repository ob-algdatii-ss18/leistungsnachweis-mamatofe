#include <iostream>
#include <args.hxx>

#include "suso.h"

enum Modes {
    DEFAULT,
    BACKTRACKING,
};

int main(int argc, const char *argv[]) {

    std::unordered_map<std::string, Modes> map{
            {"default",      Modes::DEFAULT},
            {"backtracking", Modes::BACKTRACKING}};

    args::ArgumentParser parser("Solves the classical Sudoku game.");
    args::HelpFlag help(parser, "help", "Display this help", {'h', "help"});
    args::ValueFlag<std::string> file(parser, "file", "The file containing the Sudoku to solve", {'f', "file"});
    args::MapFlag<std::string, Modes> algo(parser, "algorithm", "The algorithm that should be used to solve the Sudoku",
                                           {'a', "algo"}, map);

    try {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help) {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if (file) {
        std::cout << "file: " << args::get(file) << std::endl;
    }
    if (algo) {
        std::cout << "algo: " << args::get(algo) << std::endl;
    }

    Sudoku sudoku;
    std::cout << sudoku << std::endl;

    bool changed = true;

    while (changed) {
        changed = sudoku.solveNakedSingles();
    }

    std::cout << sudoku << std::endl;
    return 0;
}