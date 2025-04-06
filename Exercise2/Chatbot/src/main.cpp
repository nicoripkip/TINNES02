#include <Arduino.h>


void setup() {
  Serial.begin(115200);
}


void loop() {
  Serial.println("Hej, Verden fra nyt esp32!");
  delay(1000);
}
