#include <LiquidCrystal.h>
#include <Arduino.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
    // Initialization code here
    delay(1000);
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEST");
}

void loop() {
    // Main code here
}