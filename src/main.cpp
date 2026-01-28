#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

#include "menu.hpp"
#include "inputMenu.hpp"



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

bool back() {
    return true;
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

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);

    lcd.setCursor(0, 14);
    lcd.write(byte(0));

    lcd.setCursor(0, 1);
    lcd.print(line2);
}

bool sendIR() { return false; }
bool recIR() { return false; }

bool write125() { return false; }
bool read125() { return false; }
bool saved125() { return false; }

bool write1356() { return false; }
bool read1356() { return false; }
bool saved1356() { return false; }

bool sendUSB() { return false; }
bool newUSB() { return false; }
bool savedUSB() { return false; }

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
            while (analogRead(A1) > 824) {temp_index += 1; if (temp_index >= 100) {break;} delay(1);}
        }

        else if (analogRead(A1) < 200) {
            index -= 1;
            
            if (index == -1) {
                index = menu.pages[page].len - 1;
            }
            
            ShowScreen(menu);
            temp_index = 0;
            while (analogRead(A1) < 200) {temp_index += 1; if (temp_index >= 100) {break;} delay(1);}
        }

        else if (analogRead(A2) < 200) {
            temp_page = page;
            page += 1;
            
            if (page >= menu.len) {
                page = 0;
            }
            
            if (menu.pages[page].len < menu.pages[temp_page].len) {
                index = menu.pages[page].len;
            }

            ShowScreen(menu);
            temp_index = 0;
            while (analogRead(A2) < 200) {temp_index += 1; if (temp_index >= 100) {break;} delay(1);}
        }

        else if (analogRead(A2) > 824) {
            temp_page = page;
            page -= 1;
            
            if (page == -1) {
                page = menu.len - 1;
            }
            
            if (menu.pages[page].len < menu.pages[temp_page].len) {
                index = menu.pages[page].len;
            }

            ShowScreen(menu);
            temp_index = 0;
            while (analogRead(A2) > 824) {temp_index += 1; if (temp_index >= 100) {break;} delay(1);}
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
            while (digitalRead(6) == LOW) {temp_index += 1; if (temp_index >= 100) {break;} delay(1);}
        }

        delay(10);
    }

    return false;
}

Menu mainMenu;
Menu IRMenu;
Menu RFID125Menu;
Menu RFID1356Menu;
Menu badUSBMenu;
Menu InputMenu;

MenuItem IRItems1[] = {
    {"Send", sendIR, nullptr},
    {"Receive", recIR, nullptr},
    {"Back", back, nullptr},
};

MenuItem RFID125items1[] = {
    {"Write", write125, nullptr},
    {"Read", read125, nullptr},
    {"Saved", saved125, nullptr},
    {"Back", back, nullptr},
};

MenuItem RFID1356items1[] = {
    {"Write", write1356, nullptr},
    {"Read", read1356, nullptr},
    {"Saved", saved1356, nullptr},
    {"Back", back, nullptr},
};

MenuItem badUSBitems1[] = {
    {"Send payload", sendUSB, nullptr},
    {"New payload", newUSB, nullptr},
    {"Saved", savedUSB, nullptr},
    {"Back", back, nullptr},
};

MenuItem mainMenuItems1[] = {
    {"IR", nullptr, &IRMenu},
    {"RFID 125 kHz", nullptr, &RFID125Menu},
    {"RFID 13.56 MHz", nullptr, &RFID1356Menu},
    {"Bad USB", nullptr, &badUSBMenu},
    {"Master save", mainSave, nullptr},
    {"Input menu", nullptr, &InputMenu},
};

MenuPage IRPages[] = {
    {IRItems1, 3},
};

MenuPage RFID125Pages[] = {
    {RFID125items1, 4},
};

MenuPage RFID1356Pages[] = {
    {RFID1356items1, 4},
};

MenuPage badUSBPages[] = {
    {badUSBitems1, 4 },
}; 

MenuPage mainMenuPages[] = {
    {mainMenuItems1, 6 },
};

MenuPage inputMenuPages[] = {
    {input::MenuItems1, 27},
    {input::MenuItems2, 27},
    {input::MenuItems3, 11},
    {input::MenuItems4, 14},
};

void setup() {
    IRMenu = { IRPages, 1, 0 };
    RFID125Menu = { RFID125Pages, 1, 0 };
    RFID1356Menu = { RFID1356Pages, 1, 0 };
    badUSBMenu = { badUSBPages, 1, 0 };
    InputMenu = { inputMenuPages, 4, 1 };
    mainMenu = { mainMenuPages, 1, 0 };
    lcd.begin(16, 2);
    lcd.createChar(0, arrowLeft);
    lcd.createChar(1, line);

    pinMode(6, INPUT_PULLUP);

}

void loop() {
    MemuFunction(mainMenu);
}

