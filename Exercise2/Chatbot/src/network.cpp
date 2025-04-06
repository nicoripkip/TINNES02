#include "network.hpp"
#include "Arduino.h"
#include "WiFi.h"
#include <WiFiClientSecure.h>
#include "secret.h"
#include "PubSubClient.h"
#include <time.h>
#include <string.h>


WiFiClientSecure    wifi_client;
PubSubClient        mqtt_client;


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

    Serial.print("Message: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println("");
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


void disconnect_mqtt_server()
{

}


void poll_mqtt()
{
    mqtt_client.loop();
}