#include "Arduino.h"

//RGB Test
//8266 Wemos D1 mini

// Define RGB LED pins (Wemos D1 mini pins)
#define RED_PIN D1    // GPIO5
#define GREEN_PIN D2  // GPIO4
#define BLUE_PIN D3   // GPIO0

// Variables for color cycling
int hue = 0;  // Color hue (0-360)
int cycleSpeed = 1;  // Speed of color change (higher = faster)

// Function to convert HSV to RGB
void setColorHSV(int h, int s, int v) {
  float hf = h / 60.0;
  int i = (int)hf;
  float f = hf - i;
  float p = v * (1.0 - s / 255.0);
  float q = v * (1.0 - s / 255.0 * f);
  float t = v * (1.0 - s / 255.0 * (1.0 - f));
  
  int r, g, b;
  
  switch(i % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }
  
  // Write PWM values (0-255) - inverted for common anode LED
  analogWrite(RED_PIN, 255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
}

void setup() {
  Serial.begin(115200);
  delay(500); // Give ESP8266 time to fully boot
  Serial.println(".");
  Serial.println("Setup RGB Test");
  
  // Setup RGB LED pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  Serial.println("Setup complete, entering loop");
  
  // 3 quick blinks to indicate setup is complete
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, LOW);   // LED on
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);  // LED off
    delay(150);
  }
}

void loop() {
  // Cycle through colors smoothly
  setColorHSV(hue, 255, 255);  // Full saturation and brightness
  
  hue += cycleSpeed;
  if (hue >= 360) {
    hue = 0;
  }
  
  delay(20);  // Adjust this for smoother/faster cycling
}