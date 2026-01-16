#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

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

extern const char* menu125kHz[];
extern const char* menu13MHz[];
extern const char* menuIR[];
extern const char* menuBadUSB[];

int index = 0;

struct Menu;

struct MenuItem {
    const char* text;
    bool (*action)();
    Menu* menu;
};

struct Menu {
    MenuItem* items;
    int len;
};

bool back() {
    return true;
}

void ShowScreen(Menu menu) {
    const char *line1 = menu.items[index].text;
    const char *line2;

    if (index + 1 >= menu.len) {
        line2 = menu.items[0].text;
    }
    else {
        line2 = menu.items[index + 1].text;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);

    lcd.setCursor(0, 14);
    lcd.write(byte(0));

    lcd.setCursor(0, 1);
    lcd.print(line2);
}

bool MemuFunction(Menu menu) {
    index = 0;
    int temp_index;
    ShowScreen(menu);
    int input;

    while (true) {
        input = analogRead(A1);

        if (input > 800) {
            while (input > 800);

            index += 1;

            if (index >= menu.len) {
                index = 0;
            }

        }
        else if (input < 200) {
            while (input < 200);

            index -= 1;

            if (index == -1) {
                index = menu.len - 1;
            }

        }
        else if (digitalRead(6) == LOW) {
            while (digitalRead(6) == LOW);

            if (menu.items[index].action == nullptr) {
                temp_index = index;
                MemuFunction(*menu.items[index].menu);
                index = temp_index;

            }
            else {
                if (menu.items[index].action()) {
                    break;
                }
            }
        }

        ShowScreen(menu);
        delay(50);
    }

    return false;
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

Menu mainMenu;
Menu IRMenu;
Menu RFID125Menu;
Menu RFID1356Menu;
Menu badUSBMenu;

MenuItem IRItems[] = {
    {"Send", sendIR, nullptr},
    {"Receive", recIR, nullptr},
    {"Back", back, nullptr},
};

MenuItem RFID125items[] = {
    {"Write", write125, nullptr},
    {"Read", read125, nullptr},
    {"Saved", saved125, nullptr},
    {"Back", back, nullptr},
};

MenuItem RFID1356items[] = {
    {"Write", write1356, nullptr},
    {"Read", read1356, nullptr},
    {"Saved", saved1356, nullptr},
    {"Back", back, nullptr},
};

MenuItem badUSBitems[] = {
    {"Send payload", sendUSB, nullptr},
    {"New payload", newUSB, nullptr},
    {"Saved", savedUSB, nullptr},
    {"Back", back, nullptr},
};

MenuItem mainMenuItems[] = {
    {"IR", nullptr, &IRMenu},
    {"RFID 125 kHz", nullptr, &RFID125Menu},
    {"RFID 13.56 MHz", nullptr, &RFID1356Menu},
    {"Bad USB", nullptr, &badUSBMenu},
    {"Master save", mainSave, nullptr},

};

void setup() {
    IRMenu = { IRItems, 3 };
    RFID125Menu = { RFID125items, 4 };
    RFID1356Menu = { RFID1356items, 4 };
    badUSBMenu = { badUSBitems, 4 };
    mainMenu = { mainMenuItems, 4 };
    
    lcd.begin(16, 2);
    pinMode(6, INPUT_PULLUP);
}

void loop() {
    MemuFunction(mainMenu);
}