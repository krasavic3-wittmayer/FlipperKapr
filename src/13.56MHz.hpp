#pragma once

#include "menu.hpp"

namespace MHz1356 {
    bool write1356();
    bool read1356();
    bool saved1356();

    extern MenuItem RFID1356items1[4];
    extern MenuPage RFID1356Pages[1];
    extern Menu RFID1356Menu;
}