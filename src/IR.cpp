#include "menu.hpp"
#include "SD.hpp"

#include <IRremote.hpp>

extern bool (DynamicMenuFunction)();
extern DynamicVal Value;

namespace IR {
    bool send();
    bool rec();
    

    MenuItem items1[3] = {
        {"Send", send, nullptr},
        {"Receive", rec, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage pages[1] = {
        {items1, 3},
    };

    Menu menu = { pages, 1, 0, "IR" };
}

bool IR::send() { return false; }

bool IR::rec() { return false; }