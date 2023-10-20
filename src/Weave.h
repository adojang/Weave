#ifndef WEAVE_H
#define WEAVE_H


/* Kernal*/
#include <Arduino.h>
#include <ArduinoJson.h>

/* Wifi and Networking */
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <ESPmDNS.h>
#include <esp_now.h>

/* MQTT */
#include <AsyncMqttClient.h>
extern "C" {
	#include "freertos/FreeRTOS.h"
	#include "freertos/timers.h"
}

#include "MQTT.h"

/* Utilities */
#include <AsyncElegantOTA.h>
#include <WebSerial.h>
#include <AsyncTimer.h>

class Weave
{
  public:
    Weave(); // Constructor declaration

      /**
     * Custom SSID, Password, etc.
     * 
     * @param SSID The SSID ESP32, either to connect to, or to host.
     * @param Password The Password. for either AP or STA.
     * @param WifiType WIFI_STA, WIFI_AP, or WIFI_AP_STA
     * @return 0 if successful, 1 if failed.
     */
    void init(const char* ssid, const char* password, wifi_mode_t WIFITYPE, const char* mdnsName);
    void init(const char* ssid, const char* password, wifi_mode_t WIFITYPE, const char* mdnsName,const char* OTA_USER, const char* OTA_PASS);
    /**
     * @brief Initialize Entire Octopus Functionality
     * @attention Starts Wifi, mDNS, OTA, WebSerial, and Dashboard    
     */
    uint8_t fullstack();


    uint8_t startwifi();
    uint8_t startmdns();
        // uint8_t startota();
    uint8_t startota();
    uint8_t startwebserial();

  //    template <typename T>
  // unsigned short addSerialCmd(T lambda, const char* command) {
  //   Callback lambda_cb(lambda);
  // };

    /**
     * @brief This should be called last. Required by OTA, Webserial, and ESP-Dash
     * 
     * @return 0 - All Good.
     */
    uint8_t startserver();



  private:
    const char* _mdnsName = "octopus";
    const char* _ssid = "Octopus Demo"; // setup in config.h
    const char* _password = "12345678"; // setup in config.h
    const char* _OTA_USER = "admin"; // setup in config.h
    const char* _OTA_PASS = "admin1234"; // setup in config.h


    
    
    wifi_mode_t _wifitype = WIFI_AP;
    void recvMsg(uint8_t *data, size_t len);


};



#endif