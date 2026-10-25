// Utils.h - small helper used by both menus.
// readInt() keeps asking until the user types a valid integer,
// so the program does not break when letters are typed by mistake.
#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

inline int readInt(const std::string& prompt) {
    int x;
    while (true) {
        std::cout << prompt;
        if (std::cin >> x) {
#ifdef ECHO_INPUT
            std::cout << x << "\n";   // only used to generate sample-output/output.txt
#endif
            return x;
        }
        if (std::cin.eof()) std::exit(0);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter an integer.\n";
    }
}
