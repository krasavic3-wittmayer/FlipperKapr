#pragma once

#include "menu.hpp"

namespace IR {
    bool send();
    bool rec();

    extern MenuItem IRItems1[3];
    extern MenuPage IRPages[1];
    extern Menu IRMenu;
}