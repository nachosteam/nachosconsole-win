#include <iostream>
#include "../toml.hpp"

static void startPkg(std::string enteredFirst, std::string input) {
    auto data = toml::parse("nc-bin/" + enteredFirst + "/pkg-info.toml");

    std::string exe = data["execute"].as_string();
    std::string args = input.substr(enteredFirst.length());
    std::string run = "nc-bin\\" + enteredFirst + "\\" + exe + args;

    system(run.c_str());
}