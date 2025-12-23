#include <SPI.h>
#include <LoRa.h>

//sending unit

//8266 Wemos D1 mini
// MOSI -> 13 // D7
// MISO -> 12 //D6
// SCK  -> 14 //D5
#define SS 5 //D1 
#define RST 4 //D2
#define DIO0 15 //D8


void setup() {
  Serial.begin(9600);
  delay(500); // Give ESP8266 time to fully boot
  Serial.println(".");
  Serial.println("setup Lora sender");

  pinMode(LED_BUILTIN, OUTPUT);
  LoRa.setPins(SS, RST, DIO0);
  
  // 433E6: Asia, 868E6: Europe, 915E6: North America
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0x34);          // 0-0xFF sync word to match the receiver
  LoRa.setSpreadingFactor(12);     // (6-12) higher value increases range but decreases data rate
  LoRa.setSignalBandwidth(125E3);  // lower value increases range but decreases data rate
  LoRa.setCodingRate4(8);          // higher value increases range but decreases data rate
  LoRa.enableCrc();                // improves data reliability

  Serial.println("Setup complete, entering loop");
}

void loop() {
  static int counter = 0;

  Serial.print("Sending counter: ");
  Serial.println(++counter);

  digitalWrite(LED_BUILTIN, LOW);
  LoRa.beginPacket();
  LoRa.print("Counter=");
  LoRa.print(counter);
  LoRa.endPacket();
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("sent now delay...");
  delay(2000);
}