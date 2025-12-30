#include <ESP8266WiFi.h>

WiFiClient client;
const char* SSID = "jerkstore";
const char* PASSWORD = "[wifi-password]";

#include <ThingSpeak.h>

unsigned long myChannelNumber = 2748084;
const char * myReadAPIKey = "XWSUVN0KNYQB467H ";

#include <Adafruit_NeoPixel.h>

#define LED_COUNT 8
#define LED_PIN 2
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);  
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  delay(100);
  
  ThingSpeak.begin(client);

  strip.begin();
  strip.setBrightness(100);
  delay(100);
}

void loop() {
  // Serial.println("light on");
  // for (int i = 0; i < LED_COUNT; i++) {
  //   strip.setPixelColor(i, strip.Color(255,255,255));
  // }
  // strip.show();

  // delay(1000);
  // Serial.println("light off");
  // for (int i = 0; i < LED_COUNT; i++) {
  //   strip.setPixelColor(i, strip.Color(0,0,0));
  // }
  // strip.show();
  // delay(2000);

  int field1 = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey);
  if (field1 == 1) {
    //Turn on
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, strip.Color(255,255,255));
    }
    strip.show();
  }
  else if (field1 == 0) {
    //Turn off
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
    strip.show();
  }
  delay(15000);
}