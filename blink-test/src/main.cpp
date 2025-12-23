#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  
  // Initialize serial communication for debugging
  Serial.begin(115200);
  Serial.println("\nStarting Blink Program...");
  
  
  // Initialize the LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Turn off the LED initially (LOW = OFF for built-in LED)
  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.println("Setup complete! v1.1");

  int result = myFunction(2, 3);
  Serial.print("Result of myFunction(2, 3): ");
  Serial.println(result);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Turn the LED on (LOW = ON for built-in LED on ESP8266)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1 second  
  digitalWrite(LED_BUILTIN, HIGH);
  
  delay(200); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(200); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(200); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200); 
  digitalWrite(LED_BUILTIN, LOW);
  delay(200); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200); 
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1 second
  
  // Turn the LED off (HIGH = OFF for built-in LED on ESP8266)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1 second
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}