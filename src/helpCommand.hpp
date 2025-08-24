#pragma once
#include <iostream>
#include "toml.hpp"

void help(const std::string& place) {
    if (place == "default") {
        std::cout <<
			"help pkg             Shows help for pkg" << std::endl <<
            "about                Info about NachosConsole" << std::endl <<
            "pkg <param> [pkg]    Package manager" << std::endl <<
            "adduser              Adds a new user (root access required)" << std::endl <<
            "rmuser               Deletes a user (root access required)" << std::endl <<
            "passwd               Changes the password of the current user" << std::endl <<
            "clear                Clears the terminal window" << std::endl <<
            "ls [dir or file]     Shows files in the directory or a specific file (beta)" << std::endl <<
            "cat <file>           Shows contents of the file (beta)" << std::endl <<
            "logout               Logs out of the account" << std::endl <<
            "exit                 Stops running NachosConsole" << std::endl;
    } 
    else if (place == "pkg") {
        std::cout <<
            "-i <pkg>   Install package" << std::endl <<
            "-r <pkg>   Remove package" << std::endl <<
            "-u         Update available packages list" << std::endl;
    }
}