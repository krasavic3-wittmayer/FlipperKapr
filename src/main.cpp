#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 6   // ← tady musí sedět pin, kam jsi zapojil RST

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);   // Mega tohle zvládne

  SPI.begin();

  // Zpomalíme SPI – děliče to ocení
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  rfid.PCD_Init();
  Serial.println("RC522 ready");
}

void loop() {
  // čekáme na kartu
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) Serial.print("0");
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
