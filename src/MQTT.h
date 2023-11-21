#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H

#include <AsyncMqttClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

void connectToWifi();
bool connected();
void connectToMqtt();
void WiFiEvent(WiFiEvent_t event);
void onMqttConnect(bool sessionPresent);
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
void onMqttSubscribe(uint16_t packetId, uint8_t qos);
void onMqttUnsubscribe(uint16_t packetId);
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
void onMqttPublish(uint16_t packetId);
void initMQTT(IPAddress host, const int  port, const char* username, const char* password);
void initMQTT(IPAddress host, const int  port);
void publishJSON(String jsonString, String topic, int QOS = 0);
void mqttSubscribe(String topic, int QOS = 0);
#endif
