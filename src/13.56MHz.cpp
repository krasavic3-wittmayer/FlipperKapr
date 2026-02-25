#include "menu.hpp"
#include "SD.hpp"

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

extern bool (DynamicMenuFunction)();
extern DynamicVal Value;

extern MFRC522 mfrc522;
extern LiquidCrystal lcd;

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
    unsigned long startTime = millis();

    Serial.println("Čtu, lásko.");
    while (millis() - startTime < 5000) {

        if (!mfrc522.PICC_IsNewCardPresent()) continue;
        if (!mfrc522.PICC_ReadCardSerial()) continue;

        Serial.print("UID: ");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            Serial.print(mfrc522.uid.uidByte[i], HEX);
        }
        Serial.println();

        mfrc522.PICC_HaltA();
        return true;
    }

    Serial.println("Cas vyprsel, karta nenalezena");
    return false;
}