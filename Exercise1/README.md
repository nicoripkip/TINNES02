
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

## Installation

This step is only nessecary to pull the repo from github
```bash
git clone https://github.com/nicoripkip/TINNES02.git
```

Move into the folder
```bash
cd TINNES02/Exercise1
```

Start the server
```bash
docker compose up
```

## Author

Nico van Ommen | 1030808