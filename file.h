#pragma once
#include <fstream>
#include <string>

std::string read_file(const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }

    std::string contents = "";
    std::string line = "";

    while (std::getline(file, line)) {
        contents += line;
        contents += "\n";
    }

    return contents;
}
