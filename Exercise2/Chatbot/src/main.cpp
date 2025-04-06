#include <Arduino.h>
#include "network.hpp"
#include <DHT.h>
#include <DHT_U.h>
#include "commands.hpp"


#define DHT_PIN 17
#define DHT_TYPE DHT11


DHT_Unified dht(DHT_PIN, DHT_TYPE);
uint32_t delayMS;


void test(void *args, uint8_t len)
{
  Serial.println("Dit is een test!");
}


Command testCommand(1, "help", test);
CommandHandler ch('#', 10);


void register_commands();


void setup() {
  // Setup serial communication
  Serial.begin(115200);

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

  register_commands();

  Serial.print("Total commands: ");
  Serial.println(ch.get_total_commands());

  ch.execute_command("#help", NULL, 0);
}


void loop() {
  // Delay between measurements.
  // delay(delayMS);
  // Get temperature event and print its value.
  // sensors_event_t event;
  // dht.temperature().getEvent(&event);
  // if (isnan(event.temperature)) {
  //   Serial.println(F("Error reading temperature!"));
  // }
  // else {
  //   Serial.print(F("Temperature: "));
  //   Serial.print(event.temperature);
  //   Serial.println(F("°C"));
  // }
  // // Get humidity event and print its value.
  // dht.humidity().getEvent(&event);
  // if (isnan(event.relative_humidity)) {
  //   Serial.println(F("Error reading humidity!"));
  // }
  // else {
  //   Serial.print(F("Humidity: "));
  //   Serial.print(event.relative_humidity);
  //   Serial.println(F("%"));
  // }

  poll_mqtt();
}


void register_commands()
{
  ch.register_command(&testCommand);
}