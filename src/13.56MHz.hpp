#pragma once

#include "menu.hpp"

namespace MHz1356 {
    bool write();
    bool read();
    bool saved();

    extern MenuItem items1[4];
    extern MenuPage pages[1];
    extern Menu menu;
}