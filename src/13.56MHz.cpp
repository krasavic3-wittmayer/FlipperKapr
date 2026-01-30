#include "menu.hpp"

namespace MHz1356 {
    bool write() { return false; }
    bool read() { return false; }
    bool saved() { return false; }

    MenuItem items1[4] = {
        {"Write", write, nullptr},
        {"Read", read, nullptr},
        {"Saved", saved, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage pages[1] = {
        {items1, 4},
    };

    Menu menu = { pages, 1, 0 };
}