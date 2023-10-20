![Weave Banner](https://github.com/adojang/Weave/assets/48274045/38f192c2-787c-4b49-9bb7-b7692e08df27)


### The Ultimate Telematics and Telemetry Library for the ESP32

Weave is a collection of niche telemetry libraries designed to create a sophisticated all-in-one solution for collecting and displaying data in real-time, beautifully. This library is primarily designed for the ESP32 microcontroller but may also be compatible with the ESP8266 microcontroller.

<p align="center">
<img src="https://img.shields.io/github/last-commit/adojang/Weave?style=for-the-badge" />
&nbsp;
&nbsp;
<img src="https://img.shields.io/github/license/adojang/Weave.svg?style=for-the-badge" />
</p>

## Features

Weave includes the following features and functionality:

- ESPDash
- ElegantOTA
- Webserial
- MQTT
- AsyncTimer
- mDNS support
- ESP-NOW support for all configurations

  




# API

## init(const char* ssid, const char* password, wifi_mode_t WIFITYPE, const char* mdnsName);

Initializes Weave.

`init` takes in the `SSID` and `PASSWORD` from the main program. The `WIFITYPE` is either `WIFI_AP`, `WIFI_STA`, or `WIFI_AP_STA`. The mdnsName is the domain where the dashboard, webserial, and OTA will be accessed from.

If `WIFITYPE` is `WIFI_AP`, the `SSID` and `PASSWORD` are used to create an AP hosted on the ESP32 with those credentials.

If `WIFITYPE` is `WIFI_STA`, the `SSID` and `PASSWORD` are used to try and connect to an existing wifi network with those credentials.

if `WIFITYPE` is `WIFI_AP_STA`, the ESP32 will use the `SSID` and `PASSWORD` to connect to an existing wifi network, exactly how `WIFI_STA` behaves. A hidden additional network is hosted from the ESP32 with the `SSID` of `mdnsName` and the arbitrary password: `pinecones` 


#### Example:

- Initializing the ESP32 to connect to your exising network

```
  const char* SSID = "yourSSID";
  const char* PASS = "yourpass";
  const char* mdns = "weave";
  wv.init(SSID, PASS, WIFI_AP, mdns);
  wv.startwifi();

```

# Examples

- WeaveOTA - Demonstrate OTA functionality
- WeaveMQTT - Send a message to an MQTT broker with the ESP32 acting as a client.
- WeaveWebSerial - Demonstrate WebSerial functionality
- Weave-NOW - Show how to setup an ESP-NOW mesh
- WeaveDashboard - ESPDash integration demonstration.

# License

This library is licensed under [MIT](https://github.com/adojang/Weave/master/LICENSE).

# Copyright

Copyright 2023 - Adojang

Adriaan van Wijk

