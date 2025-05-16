#ifndef INC_TINNES02_NETWORK_HPP
#define INC_TINNES02_NETWORK_HPP


#include "Arduino.h"
#include <DHT.h>
#include <DHT_U.h>


void init_network();
void connect_mqtt_server();
void disconnect_mqtt_server();
void poll_mqtt();

void add_dht_sensor(DHT_Unified *dht);


#endif