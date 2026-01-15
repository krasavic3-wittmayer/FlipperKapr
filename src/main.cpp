#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 49
#define SS_PIN  53

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(9600);

    // POVINNÉ NA ARDUINO MEGA
    pinMode(53, OUTPUT);       // HW SS MUSÍ být OUTPUT
    digitalWrite(53, HIGH);

    SPI.begin();
    SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    mfrc522.PCD_Init();
    delay(4);

    mfrc522.PCD_DumpVersionToSerial();
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent()) return;
    if (!mfrc522.PICC_ReadCardSerial()) return;

    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
