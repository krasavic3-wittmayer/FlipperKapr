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

const char* mainMenu[] = {
  "IR",
  "RFID 125kHz",
  "RFID 13.56MHz",
  "Bad USB"
};

void showScreen(const char* line1, const char line2) {
  // Function to display two lines on the LCD

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
