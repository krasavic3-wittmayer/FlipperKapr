#pragma once

#include "menu.hpp"

namespace badUSB {
    bool sendUSB();
    bool newUSB();
    bool savedUSB();

    extern MenuItem badUSBitems1[4];
    extern MenuPage badUSBPages[1];
    extern Menu badUSBMenu;
}