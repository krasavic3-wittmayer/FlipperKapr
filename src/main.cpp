#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

#include "menu.hpp"
#include "inputMenu.hpp"
#include "IR.hpp"
#include "125kHz.hpp"
#include "13.56MHz.hpp"
#include "badUSB.hpp"

const int slow_scroll_speed = 4; // In scrolls per second
const int fast_scroll_speed = 8; // In scrolls per second
const int speed_switcher = 3; // How many slow scrolls befor fast scrolls

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte arrowLeft[8] = {
  B00010,
  B00100,
  B01100,
  B11111,
  B01100,
  B00100,
  B00010,
  B00000
};
byte line[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000
};

int index = 0;
int page = 0;
int scrolls = 0;

void ShowScreen(Menu menu) {
    const char* line1 = menu.pages[page].items[index].text;
    const char* line2;

    if (index + 1 >= menu.pages[page].len) {
        line2 = menu.pages[page].items[0].text;
    }
    else {
        line2 = menu.pages[page].items[index + 1].text;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);

    lcd.setCursor(14, 0);
    lcd.write(byte(0));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));

    lcd.setCursor(0, 1);
    lcd.print(line2);
}

bool mainSave() { return false; }


bool MemuFunction(Menu menu) {
    index = 0;
    page = menu.mainPage;

    int temp_index;
    int temp_page;

    ShowScreen(menu);

    while (true) {
        if (analogRead(A1) > 824) {
            index += 1;
            
            if (index >= menu.pages[page].len) {
                index = 0;
            }
            
            ShowScreen(menu);
            temp_index = 0;
            while (analogRead(A1) > 824) {temp_index += 1; if (temp_index >= 1000 / (slow_scroll_speed ? scrolls <= speed_switcher : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (analogRead(A1) < 200) {
            index -= 1;
            
            if (index == -1) {
                index = menu.pages[page].len - 1;
            }
            
            ShowScreen(menu);
            temp_index = 0;
            while (analogRead(A1) < 200) {temp_index += 1; if (temp_index >= 1000 / (slow_scroll_speed ? scrolls <= speed_switcher : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (analogRead(A2) < 200) {
            temp_page = page;
            page += 1;
            
            if (page >= menu.len) {
                page = 0;
            }
            
            if (index > menu.pages[page].len) {
                index = menu.pages[page].len - 1;
            }

            ShowScreen(menu);
            temp_index = 0;
            while (analogRead(A2) < 200) {temp_index += 1; if (temp_index >= 1000 / (slow_scroll_speed ? scrolls <= speed_switcher : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (analogRead(A2) > 824) {
            temp_page = page;
            page -= 1;
            
            if (page == -1) {
                page = menu.len - 1;
            }
            
            if (index > menu.pages[page].len) {
                index = menu.pages[page].len - 1;
            }

            ShowScreen(menu);
            temp_index = 0;
            while (analogRead(A2) > 824) {temp_index += 1; if (temp_index >= 1000 / (slow_scroll_speed ? scrolls <= speed_switcher : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (digitalRead(6) == LOW) {
            if (menu.pages[page].items[index].action == nullptr) {
                temp_index = index;
                temp_page = page;
                
                input::create();
                MemuFunction(*menu.pages[page].items[index].menu);
                
                index = temp_index;
                page = temp_page;
                
            }
            else {
                if (menu.pages[page].items[index].action()) {
                    break;
                }
            }

            ShowScreen(menu);
            temp_index = 0;
            while (digitalRead(6) == LOW) {temp_index += 1; if (temp_index >= 1000 / (slow_scroll_speed ? scrolls <= speed_switcher : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        if (!(digitalRead(6) == LOW) && !(analogRead(A2) < 200) && !(analogRead(A2) > 824) && !(analogRead(A1) > 824) && !(analogRead(A1) < 200)) {
            scrolls = 0;
        }
        delay(10);
    }

    return false;
}

Menu menu;

MenuItem items1[] = {
    {"IR", nullptr, &IR::menu},
    {"RFID 125 kHz", nullptr, &kHz125::menu},
    {"RFID 13.56 MHz", nullptr, &MHz1356::menu},
    {"Bad USB", nullptr, &badUSB::menu},
    {"Master save", mainSave, nullptr},
    {"Input menu", nullptr, &input::menu},
};

MenuPage pages[] = {
    {items1, 6 },
};

void setup() {
    menu = { pages, 1, 0 };

    lcd.begin(16, 2);
    lcd.createChar(0, arrowLeft);
    lcd.createChar(1, line);

    pinMode(6, INPUT_PULLUP);
}

void loop() {
    MemuFunction(menu);
}

