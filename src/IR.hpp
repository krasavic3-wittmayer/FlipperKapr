#pragma once

#include "menu.hpp"

namespace IR {
    bool send();
    bool rec();

    extern MenuItem items1[3];
    extern MenuPage pages[1];
    extern Menu menu;
}