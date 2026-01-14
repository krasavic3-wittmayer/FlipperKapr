#include <LiquidCrystal.h>
#include <Arduino.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
    // Initialization code here
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("Hello, World!");
}

void loop() {
    // Main code here
}