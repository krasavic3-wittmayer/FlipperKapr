#include "menu.hpp"

namespace MHz1356 {
    bool write1356() { return false; }
    bool read1356() { return false; }
    bool saved1356() { return false; }

    MenuItem RFID1356items1[4] = {
        {"Write", write1356, nullptr},
        {"Read", read1356, nullptr},
        {"Saved", saved1356, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage RFID1356Pages[1] = {
        {RFID1356items1, 4},
    };

    Menu RFID1356Menu = { RFID1356Pages, 1, 0 };
}