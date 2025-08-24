#pragma once
#include <iostream>
#include <filesystem>
#include <string>

static void ls(const std::string& folder = ".") {
    namespace fs = std::filesystem;

    try {
        fs::path dir = folder;

        if (!fs::exists(dir)) {
            std::cout << "Folder(" << folder << ") not found!" << std::endl;
            return;
        }

        if (fs::is_regular_file(dir)) {
            std::cout << dir.filename().string() << std::endl;
            return;
        }

        for (const auto& entry : fs::directory_iterator(dir)) {
            std::cout << entry.path().filename().string() << std::endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}