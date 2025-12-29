#include <SPI.h>
#include <LoRa.h>

//receiver

//8266 Wemos D1 mini
// MOSI -> 13 // D7
// MISO -> 12 //D6
// SCK  -> 14 //D5
#define SS 5 //D1
#define RST 4 //D2
#define DIO0 15 //D8

// Scanning indicator variables
unsigned long lastScanTime = 0;
int scanDots = 0;

void setup() {
  Serial.begin(115200);
  delay(500); // Give ESP8266 time to fully boot
  Serial.println(".");
  Serial.println("Setup Lora receiver");

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
  
  // 3 quick blinks to indicate setup is complete
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, LOW);   // LED on
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);  // LED off
    delay(150);
  }

  Serial.print("Scanning");
  lastScanTime = millis();
}

void loop() {
  if (LoRa.parsePacket()) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("\nReceiving...");

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.printf("    (%d)\n", LoRa.packetRssi());
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Finished.");
    
    // Reset scanning indicator
    Serial.print("Scanning");
    scanDots = 0;
    lastScanTime = millis();
  } else {
    // Show scanning progress every 2 seconds
    if (millis() - lastScanTime >= 2000) {
      Serial.print(".");
      scanDots++;
      
      // Reset after 10 dots to keep output clean
      if (scanDots >= 10) {
        Serial.println("");
        scanDots = 0;
      }
      
      lastScanTime = millis();
    }
  }
}