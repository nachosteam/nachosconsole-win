#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

std::string readInputWithHistory(const std::string& prompt, std::vector<std::string>& history, int& historyIndex) {
    std::string buffer;
    std::cout << prompt << std::flush;

    while (true) {
        int ch = _getch();

        if (ch == '\r') {
            std::cout << "\n";
            if (!buffer.empty()) {
                history.push_back(buffer);
                historyIndex = history.size();
            }
            return buffer;
        }
        else if (ch == 8) {
            if (!buffer.empty()) {
                buffer.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        }
        else if (ch == 0 || ch == 224) { 
            int code = _getch();
            if (code == 72) {
                if (historyIndex > 0) {
                    historyIndex--;
                    buffer = history[historyIndex];
                    std::cout << "\r" << std::string(200, ' ') << "\r"
                              << prompt << buffer << std::flush;
                }
            }
            else if (code == 80) {
                if (historyIndex + 1 < (int)history.size()) {
                    historyIndex++;
                    buffer = history[historyIndex];
                } else {
                    historyIndex = history.size();
                    buffer.clear();
                }
                std::cout << "\r" << std::string(200, ' ') << "\r"
                          << prompt << buffer << std::flush;
            }
        }
        else {
            buffer += (char)ch;
            std::cout << (char)ch << std::flush;
        }
    }
}