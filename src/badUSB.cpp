#include "menu.hpp"

namespace badUSB {
    bool sendUSB() { return false; }
    bool newUSB() { return false; }
    bool savedUSB() { return false; }

    MenuItem badUSBitems1[4] = {
        {"Send payload", sendUSB, nullptr},
        {"New payload", newUSB, nullptr},
        {"Saved", savedUSB, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage badUSBPages[1] = {
        {badUSBitems1, 4 },
    }; 

    Menu badUSBMenu = { badUSBPages, 1, 0 };
}