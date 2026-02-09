#include "menu.hpp"
#include "SD.hpp"

extern bool (DynamicMenuFunction)();
extern DynamicVal Value;

namespace badUSB {
    bool send();
    bool create();
    bool saved() { return DynamicMenuFunction(); }

    MenuItem items1[4] = {
        {"Send payload", send, nullptr},
        {"New payload", create, nullptr},
        {"Saved", saved, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage pages[1] = {
        {items1, 4 },
    }; 

    Menu menu = { pages, 1, 0, "BUSB" };
}

bool badUSB::send() { return false; }

bool badUSB::create() { return false; }