#pragma once
#include <windows.h>

static DWORD orig_console_mode;

void enableRawMode() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &orig_console_mode);

    DWORD raw = orig_console_mode;
    raw &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    SetConsoleMode(hStdin, raw);
}

void disableRawMode() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hStdin, orig_console_mode);
}