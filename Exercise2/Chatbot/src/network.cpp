#include "network.hpp"
#include "Arduino.h"
#include "WiFi.h"
#include <WiFiClientSecure.h>
#include "secret.h"
#include "PubSubClient.h"
#include <time.h>
#include <string.h>
#include <DHT.h>
#include <DHT_U.h>


WiFiClientSecure        wifi_client;
PubSubClient            mqtt_client;
static DHT_Unified*     sdht = nullptr;


/**
 * @brief Method that handles all the callback logic for the mqtt handler
 * 
 * @param topic
 * @param payload
 * @param length
 */
void mqttCallback(const char *topic, byte *payload, unsigned int length)
{
    Serial.println("Message received");

    char buff[10];
    memset(buff, 0, 10);

    // Make sure the first 10 bytes or smaller are collected for the commands
    size_t copy_len = length < 10 ? length : 10;
    memcpy(buff, payload, copy_len);
    buff[9] = '\0';

    char b[100];

    // This command is to test the bot
    if (strcmp(buff, "#test") == 0) {
        memset(b, 0, 100);

        sprintf(b, "The ESP32 chatbot is online");

        mqtt_client.publish("chat/message", b);

    // This command is to collect information from the temperatrure
    } else if (strcmp(buff, "#temp") == 0) {
        memset(b, 0, 100);
        
        sensors_event_t event;
        sdht->temperature().getEvent(&event);
        if (isnan(event.temperature)) {
            sprintf(b, "Error reading temperature!");
            Serial.println(F("Error reading temperature!"));
            mqtt_client.publish("chat/message", b);
        }
        else {
            Serial.print(F("Temperature: "));
            Serial.print(event.temperature);
            Serial.println(F("°C"));

            sprintf(b, "Current temperature is: %.2f°C!", event.temperature);

            mqtt_client.publish("chat/message", b);
        }
        // This command is to collect information from the humidity
    } else if (strcmp(buff, "#humidity") == 0) {
        memset(b, 0, 100);
        sensors_event_t event;
        sdht->humidity().getEvent(&event);
        if (isnan(event.relative_humidity)) {
            sprintf(b, "Error reading humidity!");

            Serial.println(F("Error reading humidity!"));

            mqtt_client.publish("chat/message", b);
        }
        else {
            Serial.print(F("Humidity: "));
            Serial.print(event.relative_humidity);
            Serial.println(F("%"));

            sprintf(b, "Current humidity is: %.2f%!", event.relative_humidity);

            mqtt_client.publish("chat/message", b);
        }
        // This command is to turn the led on
    } else if (strcmp(buff, "#led:on") == 0) {
        memset(b, 0, 100);

        sprintf(b, "Led is on!");

        digitalWrite(16, HIGH);

        mqtt_client.publish("chat/message", b);

         // This command is to turn the led off
    } else if (strcmp(buff, "#led:off") == 0) {
        memset(b, 0, 100);

        sprintf(b, "Led is off!");

        digitalWrite(16, LOW);

        mqtt_client.publish("chat/message", b);
    }
}



/**
 * @brief Function to setup the network connections
 * 
 */
void init_network()
{
    // Configure wifi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    // Start searching for a network
    Serial.println("Start searching for network!");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
    }

    Serial.println(".");
    Serial.println("Connected to wifi!!");

    // Sync time with the time server
    Serial.println("Trying to sync time!");
    configTime(0, (3600 * 2), "ntppool1.time.nl", "ntppool2.time.nl");

    // Set CA cert for wifi client
    wifi_client.setCACert(local_root_ca);

    // Setup the mqtt stuff
    mqtt_client.setClient(wifi_client);
    mqtt_client.setServer(MQTT_HOST, MQTT_PORT);
    mqtt_client.setCallback(mqttCallback);
}


/**
 * @brief Function to connect the bot to the mqtt server
 * 
 */
void connect_mqtt_server()
{
    Serial.println("ESP32 tries to connect to the mqtt server!");

    bool res = mqtt_client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS);

    if (!res) {
        Serial.println("Could not connect to the mqtt server!");
        return;
    }

    Serial.println("ESP32 is connected to the MQTT server!");

    Serial.println("ESP32 tries to subscribe to topic!");
    mqtt_client.subscribe("chat/message");
    Serial.println("ESP32 has succesfully subscribed to topic!");
}


/**
 * @brief Function to disconnect the mqtt server
 * 
 * 
 */
void disconnect_mqtt_server()
{

}


/**
 * @brief Function polls the mqtt server and makes sure all trafic is processed
 * 
 * 
 */
void poll_mqtt()
{
    mqtt_client.loop();
}


/**
 * @brief Function works as a passthrough function for the dht class
 * 
 * @param dht
 */
void add_dht_sensor(DHT_Unified *dht)
{
    sdht = dht;
}