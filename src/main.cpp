#include <Arduino.h>
#include <LiquidCrystal.h>

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
    else if (digitalRead(1) == LOW) { // ENTER
      while (digitalRead(1) == LOW);

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
Menu submenu5;
Menu mainMenu;

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
  pinMode(1, INPUT_PULLUP);
}

void loop() {
  runMenu(&mainMenu);
}
