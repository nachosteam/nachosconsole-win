/*
   Copyright 2025 NachosTeam

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <filesystem>
#include "toml.hpp"
#include "SHA512.h"
#include "sessionData.hpp"

static std::string getHiddenPassword() {
    std::string pass;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!pass.empty()) {
                pass.pop_back();
                std::cout << "\b \b";
            }
        } else {
            pass.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return pass;
}

static void firstSettings() {
    std::string root_pass;
    std::cout << "\t|Enter root password: ";
    root_pass = getHiddenPassword();

    auto data = toml::parse("nc-bin/cfg.toml");
    data["root"]["pass_hash"] = sha512.hash(root_pass);

    std::string pc_name;
    std::cout << "\t|Enter pc name: ";
    getline(std::cin, pc_name);
    data["pc"] = pc_name;

    std::ofstream cfg("nc-bin/cfg.toml");
    cfg << data;
    cfg.close();
}

static void reg() {
    auto data = toml::parse("nc-bin/cfg.toml");
    while (true) {
        std::cout << "Creating user" << std::endl;
        std::string usr;
        std::cout << "\tLogin: ";
        getline(std::cin, usr);

        if (data.contains(usr)) {
            std::cout << "This user already exists! Try again." << std::endl;
            continue;
        }

        std::cout << "\tPassword: ";
        std::string pass = getHiddenPassword();

        data[usr]["pass_hash"] = sha512.hash(pass);

        std::ofstream cfg("nc-bin/cfg.toml");
        cfg << data;
        cfg.close();

        mainInfo.currentUsr = usr;
        std::cout << "User created successfully!" << std::endl;
        break;
    }
}

static void login() {
    auto data = toml::parse("nc-bin/cfg.toml");
    while (true) {
        std::string usr;
        std::cout << "\tLogin: ";
        getline(std::cin, usr);

        if (!data.contains(usr)) {
            std::cout << "This user does not exist. Try again." << std::endl;
            continue;
        }

        std::cout << "\tPassword: ";
        std::string pass = getHiddenPassword();

        if (toml::find<std::string>(data, usr, "pass_hash") == sha512.hash(pass)) {
            mainInfo.currentUsr = usr;
            std::cout << "Welcome, " << usr << "!" << std::endl;
            break;
        } else {
            std::cout << "Incorrect password. Try again." << std::endl;
        }
    }
}