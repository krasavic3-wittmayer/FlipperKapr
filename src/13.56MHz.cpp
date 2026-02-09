#include "menu.hpp"
#include "SD.hpp"

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

extern bool (DynamicMenuFunction)();
extern DynamicVal Value;

namespace MHz1356 {
    bool write();
    bool read();
    bool saved() {
        return DynamicMenuFunction();
    };

    MenuItem items1[4] = {
        {"Write", write, nullptr},
        {"Read", read, nullptr},
        {"Saved", saved, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage pages[1] = {
        {items1, 4},
    };

    Menu menu = { pages, 1, 0, "1356" };
}

bool MHz1356::write() {
    return false;
}

bool MHz1356::read() {
    return false;
}