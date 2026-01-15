#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

/* ================= LCD ================= */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/* ================= MENU STRUCTURES ================= */
struct Menu;

typedef bool (*Action)();

struct MenuItem {
  const char* text;
  Action action;     // funkce (lambda v Pythonu)
  Menu* submenu;     // vnořené menu
};

struct Menu {
  MenuItem* items;
  int length;
};

// LCD custom chars   
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
extern Menu mainMenu;
extern Menu submenu5;

/* ================= GLOBALS ================= */
int index = 0;

/* ================= DISPLAY ================= */
void showMenu(Menu* menu) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("-> ");
  lcd.print(menu->items[index].text);

  lcd.setCursor(0, 1);
  int next = (index + 1 >= menu->length) ? 0 : index + 1;
  lcd.print("   ");
  lcd.print(menu->items[next].text);
}

/* ================= MENU ENGINE ================= */
bool runMenu(Menu* menu) {
  index = 0;
  showMenu(menu);

  while (true) {
    int joy = analogRead(A1);

    if (joy > 800) {                  // DOWN
      while (analogRead(A1) > 800);
      index++;
      if (index >= menu->length) index = 0;
      showMenu(menu);
    }
    else if (joy < 200) {             // UP
      while (analogRead(A1) < 200);
      index--;
      if (index < 0) index = menu->length - 1;
      showMenu(menu);
    }
    else if (digitalRead(6) == LOW) { // ENTER
      while (digitalRead(6) == LOW);

      MenuItem* item = &menu->items[index];

      if (item->submenu) {
        if (runMenu(item->submenu)) return true;
      }
      else if (item->action) {
        if (item->action()) return true;
      }

      showMenu(menu);
    }

    delay(20);
  }
}

/* ================= ACTIONS ================= */
bool ok() {
  return true;
}

bool print52() {
  lcd.clear();
  lcd.print("5.2 pressed");
  delay(1000);
  return false;
}

/* ================= MENU DEFINITIONS ================= */

MenuItem submenu5Items[] = {
  {"5.1", ok, nullptr},
  {"5.2", print52, nullptr},
  {"5.3", ok, nullptr},
  {"5.4", ok, nullptr},
  {"5.5", ok, nullptr},
};

MenuItem mainMenuItems[] = {
  {"1.", ok, nullptr},
  {"2.", ok, nullptr},
  {"3.", ok, nullptr},
  {"4.", ok, nullptr},
  {"5.", nullptr, &submenu5},
};

Menu submenu5 = { submenu5Items, 5 };
Menu mainMenu = { mainMenuItems, 5 };

/* ================= SETUP / LOOP ================= */
void setup() {
  lcd.begin(16, 2);
  pinMode(6, INPUT_PULLUP);
}

void loop() {
  runMenu(&mainMenu);
}
