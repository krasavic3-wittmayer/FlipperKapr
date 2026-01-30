#include "menu.hpp"

namespace IR {
    bool send() { return false; }
    bool rec() { return false; }

    MenuItem IRItems1[3] = {
        {"Send", send, nullptr},
        {"Receive", rec, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage IRPages[1] = {
        {IRItems1, 3},
    };

    Menu IRMenu = { IRPages, 1, 0 };
}