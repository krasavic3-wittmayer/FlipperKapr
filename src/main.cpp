#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/* ===== LCD CHARS ===== */
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

/* ===== MENU STRUCTURES ===== */
struct Menu;

struct MenuItem {
  const char* text;
  bool (*action)();
  Menu* submenu;
};

struct Menu {
  MenuItem* items;
  int len;
};

/* ===== ACTIONS ===== */
bool back() { return true; }

bool sendIR()   { return false; }
bool recIR()    { return false; }

bool write125() { return false; }
bool read125()  { return false; }
bool saved125() { return false; }

bool write1356(){ return false; }
bool read1356() { return false; }
bool saved1356(){ return false; }

bool sendUSB()  { return false; }
bool newUSB()   { return false; }
bool savedUSB() { return false; }

/* ===== MENUS (GLOBAL!) ===== */
Menu IRMenu, RFID125Menu, RFID1356Menu, badUSBMenu, mainMenu;

MenuItem IRItems[] = {
  {"Send", sendIR, nullptr},
  {"Receive", recIR, nullptr},
  {"Back", back, nullptr},
};

MenuItem RFID125Items[] = {
  {"Write", write125, nullptr},
  {"Read", read125, nullptr},
  {"Saved", saved125, nullptr},
  {"Back", back, nullptr},
};

MenuItem RFID1356Items[] = {
  {"Write", write1356, nullptr},
  {"Read", read1356, nullptr},
  {"Saved", saved1356, nullptr},
  {"Back", back, nullptr},
};

MenuItem badUSBItems[] = {
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
};

/* ===== UI ===== */
void showScreen(Menu* menu, int index) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menu->items[index].text);

  lcd.setCursor(15, 0);
  lcd.write(byte(0));

  lcd.setCursor(0, 1);
  lcd.print(menu->items[(index + 1) % menu->len].text);
}

bool MenuFunction(Menu* menu) {
  int index = 0;
  showScreen(menu, index);

  while (true) {
    int input = analogRead(A1);

    if (input > 824) {
      delay(150);
      index = (index + 1) % menu->len;
      showScreen(menu, index);
    }
    else if (input < 200) {
      delay(150);
      index = (index - 1 + menu->len) % menu->len;
      showScreen(menu, index);
    }
    else if (digitalRead(6) == LOW) {
      delay(200);

      MenuItem& item = menu->items[index];

      if (item.submenu) {
        MenuFunction(item.submenu);
        showScreen(menu, index);
      }
      else if (item.action) {
        if (item.action()) return false;
      }
    }
  }
}

/* ===== SETUP / LOOP ===== */
void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, arrowLeft);

  pinMode(6, INPUT_PULLUP);

  IRMenu        = { IRItems, 3 };
  RFID125Menu  = { RFID125Items, 4 };
  RFID1356Menu = { RFID1356Items, 4 };
  badUSBMenu   = { badUSBItems, 4 };
  mainMenu     = { mainMenuItems, 4 };
}

void loop() {
  MenuFunction(&mainMenu);
  delay(50);
}
