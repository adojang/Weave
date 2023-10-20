/*
  Weave WebSerial Example - This example will connect to an AP and broadcast a WebSerial terminal.
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
    wv.startwebserial();

    //Start the server
    wv.startserver();

    Serial.printf("Setup Complete. Go to %s.local/webserial to verify it works\n\n", mdns);
}


unsigned long timesinceboot = millis();
void loop(){

  if (millis() - timesinceboot > 1000){
    timesinceboot = millis();
    WebSerial.printf("Time Since Boot: %d\n", int(timesinceboot/1000));
  }



asynctimer.handle();
}