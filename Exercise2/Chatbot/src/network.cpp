#include "network.hpp"
#include "Arduino.h"
#include "WiFi.h"
#include <WiFiClientSecure.h>
#include "secret.h"
#include "PubSubClient.h"
#include <time.h>


WiFiClientSecure    wifi_client;
PubSubClient        mqtt_client;

void printLocalTime(){
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
      return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    Serial.print("Day of week: ");
    Serial.println(&timeinfo, "%A");
    Serial.print("Month: ");
    Serial.println(&timeinfo, "%B");
    Serial.print("Day of Month: ");
    Serial.println(&timeinfo, "%d");
    Serial.print("Year: ");
    Serial.println(&timeinfo, "%Y");
    Serial.print("Hour: ");
    Serial.println(&timeinfo, "%H");
    Serial.print("Hour (12 hour format): ");
    Serial.println(&timeinfo, "%I");
    Serial.print("Minute: ");
    Serial.println(&timeinfo, "%M");
    Serial.print("Second: ");
    Serial.println(&timeinfo, "%S");
  
    Serial.println("Time variables");
    char timeHour[3];
    strftime(timeHour,3, "%H", &timeinfo);
    Serial.println(timeHour);
    char timeWeekDay[10];
    strftime(timeWeekDay,10, "%A", &timeinfo);
    Serial.println(timeWeekDay);
    Serial.println();
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
    configTime(0, (3600 * 2), "ntppool1.time.nl", "ntppool2.time.nl");

    Serial.println("Trying to sync time!");
    printLocalTime();
    // time_t now = time(nullptr);

    // while (now < 100000) {
    //     Serial.print(".");
    //     now = time(nullptr);
    // }

    // struct tm time_info;
    // gmtime_r(&now, &time_info);

    // Set CA cert for wifi client
    
    // wifi_client.setInsecure();
    wifi_client.setCACert(local_root_ca);

    // Setup the mqtt stuff
    mqtt_client.setClient(wifi_client);
    mqtt_client.setServer(MQTT_HOST, MQTT_PORT);
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
}


void disconnect_mqtt_server()
{

}