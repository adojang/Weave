/*
  Weave OTA Example - This example demonstrates the complete feature set of the Weave Library, and the power of compouded software stacks.
  -----  
  The Following is Enabled:

  -ESP Dash
  -Webserial
  -ElegantOTA
  -MQTT Client
  -ESP-NOW
  -AsyncTimer
  -----
  Author: Adriaan van Wijk (https://github.com/adojang/)
  
  Please consider starring the repository on Github if you like the library 
  Repository Link: https://github.com/adojang/Weave
*/


#include <Weave.h>

Weave wv;
AsyncWebServer server(80);
AsyncTimer asynctimer;

//Set your own Wifi and SSID below.
const char* SSID = "Mourning to Dancing";
const char* PASS = "throughchristalone";
const char* mdns = "weave";

void setup(){
    Serial.begin(115200);

    //Setup Variables
    
    //Alternatively, call wv.init(SSID, PASS, WIFI_STA, mdns, username, pass) to set a custom OTA username / password
    wv.init(SSID, PASS, WIFI_AP_STA, mdns);
    wv.fullstack();

    
    
    Serial.printf("Setup Complete:\n");
    Serial.printf("Go to %s.local to verify the fullstack is enabled\n", mdns);

}


unsigned long timesinceboot = millis();
void loop(){

  if (millis() - timesinceboot > 1000){
    timesinceboot = millis();
    WebSerial.printf("Time Since Boot: %d\n", int(timesinceboot/1000));
  }



asynctimer.handle();
}