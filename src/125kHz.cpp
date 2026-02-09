#include "menu.hpp"
#include "SD.hpp"

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

extern bool (DynamicMenuFunction)();
extern DynamicVal Value;

namespace kHz125 {
    bool write();
    bool read();
    bool saved() { return DynamicMenuFunction(); }

    MenuItem items1[4] = {
        {"Write", write, nullptr},
        {"Read", read, nullptr},
        {"Saved", saved, nullptr},
        {"Back", back, nullptr},
    };

    MenuPage pages[1] = {
        {items1, 4},
    };

    Menu menu = { pages, 1, 0, "125" };
}

bool kHz125::write() {
    return false;
};

bool kHz125::read() {
    return false;
};