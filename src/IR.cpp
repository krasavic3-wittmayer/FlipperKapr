#include "menu.hpp"

namespace IR {
    bool send() { return false; }
    bool rec() { return false; }

    MenuItem items1[3] = {
        {"Send", send, nullptr},
        {"Receive", rec, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage pages[1] = {
        {items1, 3},
    };

    Menu menu = { pages, 1, 0 };
}