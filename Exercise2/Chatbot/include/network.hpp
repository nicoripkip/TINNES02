#ifndef INC_TINNES02_NETWORK_HPP
#define INC_TINNES02_NETWORK_HPP


#include "Arduino.h"


void init_network();
void connect_mqtt_server();
void disconnect_mqtt_server();
void poll_mqtt();



#endif