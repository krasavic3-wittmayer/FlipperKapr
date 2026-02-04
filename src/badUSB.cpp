#include "menu.hpp"

namespace badUSB {
    bool send() { return false; }
    bool create() { return false; }
    bool saved() { return false; }

    MenuItem items1[4] = {
        {"Send payload", send, nullptr},
        {"New payload", create, nullptr},
        {"Saved", saved, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage pages[1] = {
        {items1, 4 },
    }; 

    Menu menu = { pages, 1, 0 };
}