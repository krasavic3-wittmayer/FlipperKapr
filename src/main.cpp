#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

#include "menu.h"
#include "inputMenu.h"



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

        }
        else if (analogRead(A1) < 200) {
            index -= 1;

            if (index == -1) {
                index = menu.pages[page].len - 1;
            }

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
        }

        ShowScreen(menu);
        delay(250);
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


MenuItem inputMenuItems1[] = {
    {"A", input::A, nullptr},
    {"B", input::B, nullptr},
    {"C", input::C, nullptr},
    {"D", input::D, nullptr},
    {"E", input::E, nullptr},
    {"F", input::Fchar, nullptr},
    {"G", input::G, nullptr},
    {"H", input::H, nullptr},
    {"I", input::I, nullptr},
    {"J", input::J, nullptr},
    {"K", input::K, nullptr},
    {"L", input::L, nullptr},
    {"M", input::M, nullptr},
    {"N", input::N, nullptr},
    {"O", input::O, nullptr},
    {"P", input::P, nullptr},
    {"Q", input::Q, nullptr},
    {"R", input::R, nullptr},
    {"S", input::S, nullptr},
    {"T", input::T, nullptr},
    {"U", input::U, nullptr},
    {"V", input::V, nullptr},
    {"W", input::W, nullptr},
    {"X", input::X, nullptr},
    {"Y", input::Y, nullptr},
    {"Z", input::Z, nullptr},
    input::enterItem,
};

MenuItem inputMenuItems2[] = {
    {"a", input::a, nullptr},
    {"b", input::b, nullptr},
    {"c", input::c, nullptr},
    {"d", input::d, nullptr},
    {"e", input::e, nullptr},
    {"f", input::f, nullptr},
    {"g", input::g, nullptr},
    {"h", input::h, nullptr},
    {"i", input::i, nullptr},
    {"j", input::j, nullptr},
    {"k", input::k, nullptr},
    {"l", input::l, nullptr},
    {"m", input::m, nullptr},
    {"n", input::n, nullptr},
    {"o", input::o, nullptr},
    {"p", input::p, nullptr},
    {"q", input::q, nullptr},
    {"r", input::r, nullptr},
    {"s", input::s, nullptr},
    {"t", input::t, nullptr},
    {"u", input::u, nullptr},
    {"v", input::v, nullptr},
    {"w", input::w, nullptr},
    {"x", input::x, nullptr},
    {"y", input::y, nullptr},
    {"z", input::z, nullptr},
    input::enterItem,
};

MenuItem inputMenuItems3[] = {
    {"1", input::in1, nullptr},
    {"2", input::in2, nullptr},
    {"3", input::in3, nullptr},
    {"4", input::in4, nullptr},
    {"5", input::in5, nullptr},
    {"6", input::in6, nullptr},
    {"7", input::in7, nullptr},
    {"8", input::in8, nullptr},
    {"9", input::in9, nullptr},
    {"0", input::in0, nullptr},
    input::enterItem,
};

MenuItem inputMenuItems4[] = {
    {".", input::in_tec, nullptr},
    {",", input::in_car, nullptr},
    {"(", input::in_onz, nullptr},
    {")", input::in_znz, nullptr},
    {":", input::in_dvo, nullptr},
    {"_", input::in_ptr, nullptr},
    {"-", input::in_dash, nullptr},
    {"+", input::in_plus, nullptr},
    {"*", input::in_star, nullptr},
    {"/", input::in_slash, nullptr},
    {"=", input::in_eq, nullptr},
    {"?", input::in_qm, nullptr},
    {"!", input::in_em, nullptr},
    input::enterItem,
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
    {inputMenuItems1, 26},
    {inputMenuItems2, 26},
    {inputMenuItems3, 11},
    {inputMenuItems4, 14},
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

