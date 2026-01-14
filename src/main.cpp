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
int index = 0;

// testovací funkce
bool t() {
  return true;
}

// =================== OPRAVENÁ FUNKCE ===================
void showScreen(Item[] menu) {
  const char* line1 = menu[index].text;

  if (index + 1 >= menu.len) {
    const char* line2 = menu[0].text;
  } else {
    const char* line2 = menu[index + 1].text;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

bool Menu(Item[] menu) {
  index = 0;

  while (true) {
    if (analogRead(A1) >= 824) {
      index += 1;

      if (index >= menu.len) {
        index = 0;
      }

    } else if (analogRead(A1) <= 200) {
      index -= 1;

      if (index == -1) {
        index = menu.len - 1;
      }
    } else if (digitalRead(1) == LOW) {
      int temp_index = index;

      if (menu[index].func()) {
        break;
      }
    }

    showScreen(menu)
    sleep(10)
    
  }
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
  //
}
