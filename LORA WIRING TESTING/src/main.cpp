#include <Arduino.h>
#include <SPI.h>

#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LORA_SS, OUTPUT);
  digitalWrite(LORA_SS, HIGH);

  pinMode(LORA_RST, OUTPUT);
  digitalWrite(LORA_RST, LOW);
  delay(10);
  digitalWrite(LORA_RST, HIGH);
  delay(10);

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);

  // Read RegVersion (0x42) — should return 0x12 for SX1278
  digitalWrite(LORA_SS, LOW);
  SPI.transfer(0x42 & 0x7F);   // read = MSB 0
  uint8_t version = SPI.transfer(0x00);
  digitalWrite(LORA_SS, HIGH);

  Serial.print("SX1278 Version Register: 0x");
  Serial.println(version, HEX);

  if (version == 0x12) {
    Serial.println("SUCCESS — chip is responding correctly.");
  } else if (version == 0x00 || version == 0xFF) {
    Serial.println("FAILED — no response. This is a wiring/power problem, not a code problem.");
  } else {
    Serial.println("Unexpected value — possible partial connection or wrong chip.");
  }
}

void loop() {}