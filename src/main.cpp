#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "configuration.h"

void setup();
void loop();
void setup_wifi();
void mqtt_reconnect();
void send_measurements_to_mqtt();
float get_temperature();
float get_humidity();

DHT dht(DHT_PIN, DHT_TYPE);

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void setup() {
  Serial.begin(115200);

  setup_wifi();

  dht.begin();

  mqtt_client.setServer(MQTT_SERVER, 1883);

  delay(10);
}

void loop() {
  if (!mqtt_client.connected()) {
    mqtt_reconnect();
  }
  mqtt_client.loop();

  send_measurements_to_mqtt();

  delay(30000);
}

void setup_wifi() {
  WiFi.begin(SSID, WLAN_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void mqtt_reconnect() {
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (mqtt_client.connect(clientId.c_str())) {
      Serial.println("connected");
      mqtt_client.publish(MQTT_HEALTH_TOPIC, "connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void send_measurements_to_mqtt() {
  float temperature = get_temperature();
  if(!isnan(temperature)){
    Serial.println("Send temperature to mqtt-server...");
    mqtt_client.publish(MQTT_TEMPERATURE_TOPIC, String(temperature).c_str());
    Serial.println("Done!");
  }

  float humidity = get_humidity();
  if(!isnan(humidity)){
    Serial.println("Send humidity to mqtt-server...");
    mqtt_client.publish(MQTT_HUMIDITY_TOPIC, String(humidity).c_str());
    Serial.println("Done!");
  }
}

float get_temperature() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Error reading temperature!");
  }

  Serial.println("Temperature: " + String(temperature) + "C");

  return temperature;
}

float get_humidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("Error reading humidity!");
  }

  Serial.println("Humidity: " + String(humidity) + "%");

  return humidity;
}
