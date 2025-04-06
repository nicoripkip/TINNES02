#include <Arduino.h>
#include "network.hpp"

void setup() {
  Serial.begin(115200);

  init_network();

  delay(100);

  connect_mqtt_server();
}


void loop() {
  // Serial.println("Hej, Verden fra nyt esp32!");
  // delay(1000);
}
