
# TINNES02 Exercise 1

## About

This exercise is togive an introduction to docker and mqtt brokers. The exercise is to build a chatapp which can communicate over a broker. 
The chatapp consists of a frontent interface which is not bound to any specific account, but is browser session bound. The messages are not saved and are lost when the browser is closed.

This exercise is also about security. The chatapp needs to be protected with TLS and the mqtt broker needs to be protected with a password.

## Dependencies

### Containers

- Node
- Mosquitto

### Packages

- express
- mqtt.js
- ejs

## Configuration

The configuration files for the mosquitto container can be found in the folder:
```
./mosquitto/config/mosquitto.conf
./mosquitto/config/pw.txt
```

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


## Installation

1. This step is only nessecary to pull the repo from github
```bash
git clone https://github.com/nicoripkip/TINNES02.git
```

2. Move into the folder
```bash
cd TINNES02/Exercise1
```

3. With the docker compose command the server can be started.
```bash
docker compose up --build
``` 

4. To run the containers as a background task, the following command can be executed.
```bash
docker compose up --build -d
```

5. If the containers are launched for the first time, docker will pull the images from the internet and builds them for you. 

6. The IP addresses wil be randomly assigned to the chatapp. On the hostmachine the chatapp can be accessed with localhost, but on another machine the IP of the server is needed to access the chatapp. The chatapp can be accessed on port: 443.


## Author

Nico van Ommen | 1030808