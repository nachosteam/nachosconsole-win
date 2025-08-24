#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <filesystem>

std::string readInputWithHistory(const std::string& prompt, std::vector<std::string>& history, int& historyIndex) {
    std::string buffer;
    size_t cursorPos = 0;
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
            if (cursorPos > 0) {
                buffer.erase(cursorPos - 1, 1);
                cursorPos--;
                std::cout << "\r" << prompt << buffer << " \b";
                for (size_t i = buffer.size(); i > cursorPos; i--) std::cout << "\b";
                std::cout << std::flush;
            }
        }
        else if (ch == 0 || ch == 224) {
            int code = _getch();
            if (code == 72) {
                if (historyIndex > 0) {
                    historyIndex--;
                    buffer = history[historyIndex];
                    cursorPos = buffer.size();
                    std::cout << "\r" << std::string(200, ' ') << "\r" << prompt << buffer << std::flush;
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
                cursorPos = buffer.size();
                std::cout << "\r" << std::string(200, ' ') << "\r" << prompt << buffer << std::flush;
            }
            else if (code == 75) {
                if (cursorPos > 0) {
                    cursorPos--;
                    std::cout << "\b" << std::flush;
                }
            }
            else if (code == 77) {
                if (cursorPos < buffer.size()) {
                    std::cout << buffer[cursorPos];
                    cursorPos++;
                    std::cout << std::flush;
                }
            }
        }
        else if (ch == 9) {
            continue;
        }
        else {
            buffer.insert(cursorPos, 1, (char)ch);
            std::cout << buffer.substr(cursorPos) << std::flush;
            cursorPos++;
            for (size_t i = buffer.size(); i > cursorPos; i--) std::cout << "\b";
        }
    }
}