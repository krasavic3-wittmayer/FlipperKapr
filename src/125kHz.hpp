#pragma once

#include "menu.hpp"

namespace kHz125 {
    bool write();
    bool read();
    bool saved();

    extern MenuItem items1[4];
    extern MenuPage pages[1];
    extern Menu menu;
}