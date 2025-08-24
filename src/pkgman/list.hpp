#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include "../toml.hpp"

static void listPackages() {
    auto pkgs = toml::parse("nc-bin/packages.toml");

    for (auto& [pkgName, pkgData] : pkgs.as_table()) {
        std::string version = pkgData["version"].as_string();
        std::vector<std::string> archList = toml::find<std::vector<std::string>>(pkgData, "arch");

        std::string archs;
        for (size_t i = 0; i < archList.size(); i++) {
            archs += archList[i];
            if (i + 1 < archList.size()) archs += ",";
        }

        std::string status;
        if (std::filesystem::exists("nc-bin/" + pkgName))
            status = " -- Installed";

        std::cout << pkgName << " - " << version << " - " << archs << status << std::endl;
    }
}
