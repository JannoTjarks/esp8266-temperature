# ESP8266-temperature

This code is the base of my self-developed "smart-home" temperature and 
humidity sensor based on an ESP8266 with the DTH11. The measurments are sent
to a mqtt server.

## How does it work
The wiring is really easy. Powered is the esp8226 with usb or by a power supply
on the VIN pin. The dth11 sensor needs 3.3V, which can be taken from the
esp8226. At least the data pin of the esp8226 needs to be connected on a
gpio. For my setup I use the gpio 5.

For the development and upload of the code I use `platformio`.

## Configuration
Because I use several esp8226 for different rooms, I made the code
variablized. The configuration can be set inside the file
`include/configuration.h`.
This is a blueprint of the configuration.h:
```c++
#define SSID "<your-ssid>"
#define WLAN_PASSWORD "<your-wifi-password>"

#define DHT_PIN <number-of-the-used-gpio>
#define DHT_TYPE <type-of-the-dht-sensor> // Possible values are DHT11 or DHT22

#define MQTT_SERVER "<mqtt-server-ip-or-dns>"
#define MQTT_HEALTH_TOPIC "<health-topic>"
#define MQTT_TEMPERATURE_TOPIC "<temperature-topic>"
#define MQTT_HUMIDITY_TOPIC "<humidity-topic>"
```
