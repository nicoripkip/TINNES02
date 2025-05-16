#include <Arduino.h>
#include "network.hpp"
#include <DHT.h>
#include <DHT_U.h>


#define DHT_PIN 17
#define DHT_TYPE DHT11


DHT_Unified dht(DHT_PIN, DHT_TYPE);
uint32_t delayMS;


void setup() {
  // Setup serial communication
  Serial.begin(115200);

  // Setup IO
  pinMode(16, OUTPUT);

  // Pass classes through
  add_dht_sensor(&dht);


  // Setup network
  init_network();
  delay(100);

  connect_mqtt_server();

  // Setup dht11 sensor
  dht.begin();

  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

}


void loop() {
  poll_mqtt();
}