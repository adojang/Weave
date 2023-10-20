/*
  Weave OTA Example - This example will host an AP from the ESP32 that allows you to do OTA updates to it using the ElegantOTA by Ayush Sharma
  You can find your build file under your build dir in Platformio. look for "firmware.bin".
  -----
  Author: Adriaan van Wijk (https://github.com/adojang/)
  
  Please consider starring the repository on Github if you like the library 
  Repository Link: https://github.com/adojang/Weave
*/


#include <Weave.h>

Weave wv;
AsyncWebServer server(80);
AsyncTimer asynctimer;

const char* SSID = "Mourning to Dancing";
const char* PASS = "throughchristalone";
const char* mdns = "weave";

void setup(){
    Serial.begin(115200);

    //Setup Variables
    
    //Alternatively, call wv.init(SSID, PASS, WIFI_STA, mdns, username, pass) to set a custom OTA username / password
    wv.init(SSID, PASS, WIFI_STA, mdns);
    

    //Start Wifi
    wv.startwifi();

    //Choose which Components we want to enable
    wv.startmdns();
    wv.startota();

    //Start the server
    wv.startserver();

    Serial.printf("Setup Complete. Go to %s.local/update to verify it works\n\n", mdns);
    Serial.printf("Default Username: admin\nDefault Password: admin1234\n");
}



void loop(){


asynctimer.handle();
}