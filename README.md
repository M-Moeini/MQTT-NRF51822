# MQTT Project on Nordic Microcontrollers

This project demonstrates the implementation of the MQTT protocol on Nordic microcontrollers using GPRS connectivity. It includes functionalities for connecting, publishing, and subscribing. The project works well for all features except subscribing.

## Overview
- `mqtt.c`: Contains the implementation of the MQTT protocol, including message handling and protocol operations.
- `simplepubsub.c`: Implements a simple publish and subscribe mechanism using the MQTT protocol.

The project includes two primary components:
- **GPRS Connection**: Establishes a GPRS connection to the internet.
- **MQTT Functionality**: Handles MQTT protocol operations including initialization, connection, publishing, and subscribing.

## Key Functions

- **`GPRS_CON`**: Connects to the internet via GPRS.
- **`MQTT_INIT`**: Initializes the MQTT server parameters.
- **`MQTT_CON`**: Establishes the MQTT connection.
- **`CONNECT`**: Connects to the MQTT broker using its name as an argument.
- **`PUBLISH`**: Publishes messages to a specified topic.
- **`SUBSCRIBE`**: Subscribes to a specified topic.
- **`READSERVER`**: Reads data received from the server. When `ciprxget=0,1`, it indicates that data has arrived from the server, sets a flag (`client_available_f`), and reads the data into an array. This function works for all cases except subscribing.
- **`LOOP`**: Handles the main loop with a timeout, calling `READSERVER` and `pinghandle` to maintain a stable connection.
- **`Pinghandle`**: Sends a ping request to the server to indicate presence and maintain the connection. It is called with a timeout set in the `LOOP` function and receives a ping acknowledgment (208 and 0).

### Prerequisites

- NRF851 ARM microcontroller
- C Compiler compatible with ARM architecture
- MQTT Broker for testing (e.g., Mosquitto)

## Usage

1. **Setup**: Ensure you have the necessary libraries `SimplePubSub` and `mqtt`. Both should be used together in the project.
2. **Configuration**: Adjust the MQTT broker parameters and topics as needed.
3. **Running**: Compile and flash the code to your Nordic microcontroller.

## Known Issues

- **Subscribing**: While initial subscription is successful, there is a minor issue where data published from the broker is not received on the subscribing end. The subscribe functionality works but does not handle incoming data correctly.

## Acknowledgements

- The project translates key concepts from Arduino libraries to ARM, with the exception of the callback mechanism in subscribing, which was adapted using interrupt concepts. Despite this, there remains a small issue with data reception during subscription.

## Contribution
Feel free to fork this repository and contribute by submitting a pull request. For major changes, please open an issue first to discuss what you would like to change.

## Contact
- **Mahdi Moeini**
  - **Email**: [mmoeini@mun.ca](mailto:mmoeini@mun.ca)
  - **LinkedIn**: [linkedin.com/in/mmoeini](https://linkedin.com/in/mmoeini)
  - **GitHub**: [m-moeini.github.io](https://m-moeini.github.io)
