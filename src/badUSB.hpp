#pragma once

#include "menu.hpp"

namespace badUSB {
    bool send();
    bool create();
    bool saved();

    extern MenuItem items1[4];
    extern MenuPage pages[1];
    extern Menu menu;
}