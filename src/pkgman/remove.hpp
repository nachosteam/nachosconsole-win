#include <iostream>
#include <filesystem>
#include "../toml.hpp"

static void remove(std::string package) {
    if (package.empty() || package.find_first_of("\\/:*?\"<>|") != std::string::npos || package == "." || package == "..") {
        std::cout << "Package(" << package << ") not found!" << std::endl;
        return;
    }

    std::filesystem::path pkgPath = "nc-bin\\" + package;

    if (std::filesystem::exists(pkgPath)) {
        try {
            std::filesystem::remove_all(pkgPath);
            std::cout << "Package(" << package << ") removed successfully." << std::endl;
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Package(" << package << ") not found!" << std::endl;
    }
}