#include <Arduino.h>
#include <LiquidCrystal.h>

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  53
#define RST_PIN 49

MFRC522 mfrc522(SS_PIN, RST_PIN);

#include "menu.hpp"
#include "inputMenu.hpp"
#include "IR.hpp"
#include "125kHz.hpp"
#include "13.56MHz.hpp"
#include "badUSB.hpp"
#include "SD.hpp"

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

const char* menu_name = "";
int depeth = 0;

DynamicVal Value = {};
DynamicMenu dynMenu;

void print(const char* line1, const char* line2) {
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

void ShowScreen(Menu menu) {
    const char* line1 = menu.pages[page].items[index].text;
    const char* line2;

    if (index + 1 >= menu.pages[page].len) {
        line2 = menu.pages[page].items[0].text;
    }
    else {
        line2 = menu.pages[page].items[index + 1].text;
    }

    print(line1, line2);
}

void ShowScreen(DynamicMenu menu) {
    const char* line1 = menu.pages[1].items[index].text;
    const char* line2;

    if (index + 1 >= menu.pages[1].len) {
        line2 = menu.pages[1].items[0].text;
    }
    else {
        line2 = menu.pages[1].items[index + 1].text;
    }

    print(line1, line2);
}


bool mainSave() { return false; }


bool MemuFunction(Menu menu) {
    index = 0;
    page = menu.mainPage;

    int temp_index = 0;
    int temp_page = 0;

    if (depeth <= 1) {
        menu_name = menu.name;
    }

    ShowScreen(menu);

    while (true) {
        if (analogRead(A1) > 824) {
            index += 1;
            
            if (index >= menu.pages[page].len) {
                index = 0;
            }
            
            while (analogRead(A1) > 824) {temp_index += 1; if (temp_index >= 1000 / (scrolls <= speed_switcher ? slow_scroll_speed : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (analogRead(A1) < 200) {
            index -= 1;
            
            if (index == -1) {
                index = menu.pages[page].len - 1;
            }
            
            while (analogRead(A1) < 200) {temp_index += 1; if (temp_index >= 1000 / (scrolls <= speed_switcher ? slow_scroll_speed : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
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

            while (analogRead(A2) < 200) {temp_index += 1; if (temp_index >= 1000 / (scrolls <= speed_switcher ? slow_scroll_speed : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
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

            while (analogRead(A2) > 824) {temp_index += 1; if (temp_index >= 1000 / (scrolls <= speed_switcher ? slow_scroll_speed : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (digitalRead(6) == LOW) {
            if (menu.pages[page].items[index].action == nullptr) {
                temp_index = index;
                temp_page = page;

                depeth += 1;
                
                input::create();
                MemuFunction(*menu.pages[page].items[index].menu);

                if (depeth <= 1) {
                    menu_name = menu.name;
                }
                    
                index = temp_index;
                page = temp_page;
                
            }
            else {
                if (menu.pages[page].items[index].action()) {
                    break;
                }
            }

            while (digitalRead(6) == LOW) {temp_index += 1; if (temp_index >= 1000 / (scrolls <= speed_switcher ? slow_scroll_speed : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }
        
        temp_index = 0;
        if (!(digitalRead(6) == LOW) && !(analogRead(A2) < 200) && !(analogRead(A2) > 824) && !(analogRead(A1) > 824) && !(analogRead(A1) < 200)) {
            scrolls = 0;
        }

        ShowScreen(menu);
        delay(10);
    }

    return false;
}


bool DynamicMenuFunction() {
    index = 0;
    page = 0;

    int temp_index = 0;

    DynamicMenu menu;
    menu.len = 16;
    int next_page = 0;

    menu.pages[0] = load_page(menu_name, menu.len - 1);
    menu.pages[1] = load_page(menu_name, 0);
    menu.pages[2] = load_page(menu_name, 1);

    ShowScreen(menu);
    
    while (true) {
        if (analogRead(A1) < 200) {
            index -= 1;

            if (index <= -1) index = menu.pages[1].len - 1;

            while (analogRead(A1) < 200) {temp_index += 1; if (temp_index >= 1000 / (scrolls <= speed_switcher ? slow_scroll_speed : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (analogRead(A1) > 824) {
            index += 1;

            if (index >= menu.pages[1].len) index = 0;

            while (analogRead(A1) > 824) {temp_index += 1; if (temp_index >= 1000 / (scrolls <= speed_switcher ? slow_scroll_speed : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (analogRead(A2) < 200) {
            page += 1;
            if (page >= menu.len) page = 0;

            menu.pages[0] = menu.pages[1];
            menu.pages[1] = menu.pages[2];

            if (index >= menu.pages[1].len) {
                index = menu.pages[1].len - 1;
            }


            if (page + 1 >= menu.len) { next_page = 0; } else { next_page = page + 1; }
            menu.pages[2] = load_page(menu_name, next_page);

            while (analogRead(A2) < 200) {temp_index += 1; if (temp_index >= 1000 / (scrolls <= speed_switcher ? slow_scroll_speed : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (analogRead(A2) > 824) {
            page -= 1;
            if (page <= -1) page = menu.len - 1;

            menu.pages[2] = menu.pages[1];
            menu.pages[1] = menu.pages[0];


            if (page - 1 <= -1) { next_page = 15; } else { next_page = page - 1; }
            menu.pages[0] = load_page(menu_name, next_page);

            while (analogRead(A2) > 824) {temp_index += 1; if (temp_index >= 1000 / (scrolls <= speed_switcher ? slow_scroll_speed : fast_scroll_speed)) {break;} delay(1);} scrolls += 1;
        }

        else if (digitalRead(6) == LOW) {
            Value = menu.pages[1].items[index].val;
            break;
        }
        
        if (!(digitalRead(6) == LOW) && !(analogRead(A2) < 200) && !(analogRead(A2) > 824) && !(analogRead(A1) > 824) && !(analogRead(A1) < 200)) {
            scrolls = 0;
        }
        delay(10);

        ShowScreen(menu);
    }

    return false;
}

bool DynamicTest() {
    char buf[15] = {};
    load_val(Value, buf, 15);

    lcd.setCursor(0, 0);
    lcd.print(buf);

    delay(1000);

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
    {"Dynamic test - 1", DynamicMenuFunction, nullptr},
    {"Dynamic test - 2", DynamicTest, nullptr},
};

MenuPage pages[] = {
    {items1, 8 },
};

byte cardUID[10] = {};
byte UIDlen = 0;

#define SS_PIN 53
#define RST_PIN 48

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
    menu = { pages, 1, 0, "main" };

    Serial.begin(9600);
    SPI.begin();

    mfrc522.PCD_Init();

    Serial.println("Přilož kartu...");

    lcd.begin(16, 2);
    delay(100);
    lcd.clear();
    delay(100);
    lcd.createChar(0, arrowLeft);
    lcd.createChar(1, line);

    SPI.begin();
    rfid.PCD_Init();

    pinMode(6, INPUT_PULLUP);
}

void loop() {
    MemuFunction(menu);
}