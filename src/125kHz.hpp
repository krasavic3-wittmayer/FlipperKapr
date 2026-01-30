#pragma once

#include "menu.hpp"

namespace kHz125 {
    bool write125();
    bool read125();
    bool saved125();

    extern MenuItem RFID125items1[4];
    extern MenuPage RFID125Pages[1];
    extern Menu RFID125Menu;
}