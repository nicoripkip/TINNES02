# TINNES02

## About

This repo contains all the problemsets needed to pass the course TINNES02. This course was a combination course of security and networking. This exercise centers arround 
building and interfacing an IOT device with a MQTT broker. The exercise was setup with an ESP32 configured as a chatbot. The chatbot interfaces with an online mqtt server and the frontend which was build in the previous exercise also interfaces with the mqtt server.


## Dependencies
### Containers
- Node

### Libraries

- PubSubClient
- dht11

### Hardware

- Firebeetle ESP32E
- DHT11 sensor
- 10k ohm resistor
- 470 ohm resistor
- Blue led

## Configuration

The TLS certificates can be found under:
```
./certs/cert.pem
./certs/key.pem
```
This certificate is selfsigned by me.

The webserver is written in express js. The file can be found under: 
```
./app/app.js
```
This file contains all the code for configuring the webserver. Features can be added to this file

The sourcecode for the chatbot can be found under the folder chatbot

## Installation

1. Clone the github repo
```bash
git clone https://github.com/nicoripkip/TINNES02.git
```

2. Move into the folder
```bash
cd TINNES02/Exersice2
```

3. With the docker compose file the frontend can be started, if it's the first time, docker will automaticly pull it's needed dependencies and build an image for you
```bash
docker compose up --build
```

4. Open the folder in vscode and make sure platformio is installed
```bash
code .
```

5. Build and upload the code to the microcontroller via platform io

6. (optional) To run the containers as a background task, the following command can be executed.
```bash
docker compose up --build -d
```

7. The IP addresses wil be randomly assigned to the chatapp. On the hostmachine the chatapp can be accessed with localhost, but on another machine the IP of the server is needed to access the chatapp. The chatapp can be accessed on port: 443.

## Commands

- #test - Check if the chatbot is operational
- #temp - Get a read of the temperature
- #humidity - Get a read of the humidity
- #led:on - Turn the led on
- #led:off - Turn the led off

## Author

Nico van Ommen | 1030808
