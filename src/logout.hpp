#pragma once
#include "sessionData.hpp"
#include "account.hpp"
#include "term/termControl.hpp"

static void logout() {
    system("cls");
    mainInfo.currentUsr.clear();
    disableRawMode();
    signIn();
    enableRawMode();
}