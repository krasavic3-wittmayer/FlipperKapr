#include "menu.hpp"

namespace kHz125 {
    bool write125() { return false; }
    bool read125() { return false; }
    bool saved125() { return false; }

    MenuItem RFID125items1[4] = {
        {"Write", write125, nullptr},
        {"Read", read125, nullptr},
        {"Saved", saved125, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage RFID125Pages[1] = {
        {RFID125items1, 4},
    };

    Menu RFID125Menu = { RFID125Pages, 1, 0 };
}