#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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

byte lineChar[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000
};

// extern menu declarations (ponecháno)
extern const char* menu125kHz[];
extern const char* menu13MHz[];
extern const char* menuIR[];
extern const char* menuBadUSB[];

// main menu (ponecháno)
const char* mainMenu[] = {
  "IR",
  "RFID 125kHz",
  "RFID 13.56MHz",
  "Bad USB"
};

// =================== NÁHRADA ZA std::tuple + std::function ===================
struct Item {
  const char* text;
  bool (*func)();   // ukazatel na funkci
};

// místo std::vector
Item list[];

// testovací funkce
bool t() {
  return true;
}

// =================== OPRAVENÁ FUNKCE ===================
void showScreen(item[] menu) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

// =================== SETUP ===================
void setup() {
  lcd.begin(16, 2);

  lcd.createChar(0, arrowLeft);
  lcd.createChar(1, lineChar);

  // inicializace "list"
  list[0] = {"1.", t};
  list[1] = {"2.", t};
  list[2] = {"3.", t};

  // test zobrazení
  showScreen(list[0].text, "OK");
}

// =================== LOOP ===================
void loop() {
  // zatím prázdné – stejně jako původně
}
