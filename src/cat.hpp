#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

static void cat(const std::string& filename) {
    namespace fs = std::filesystem;

    fs::path filePath = filename;

    if (!fs::exists(filePath)) {
        std::cout << "File(" << filename << ") not found!" << std::endl;
        return;
    }

    if (fs::is_directory(filePath)) {
        std::cout << "File(" << filename << ") is a directory" << std::endl;
        return;
    }

    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error: cannot open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}