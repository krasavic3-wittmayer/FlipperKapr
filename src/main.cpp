#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

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

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
