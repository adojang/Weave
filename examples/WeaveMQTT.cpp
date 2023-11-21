/*
  Weave MQTT Example - This example will connect to your wifi and  post to a public MQTT broker using the Async-mqtt-client library by Marvin Roger
  -----
  Author: Adriaan van Wijk (https://github.com/adojang/)
  
  Please consider starring the repository on Github if you like the library 
  Repository Link: https://github.com/adojang/Weave
*/

#include <Weave.h>

Weave wv;
AsyncTimer asynctimer;

const char* SSID = "Mourning to Dancing";
const char* PASS = "throughchristalone";
const char* mdns = "weave";

//From the public broker
const char* mqtt_username = "rw";
const char* mqtt_password = "readwrite";

//Mosquitto Public Test Broker - https://test.mosquitto.org/
IPAddress MQTT_HOST = IPAddress(91, 121, 93, 94);

// const int MQTT_PORT = 1883;  //for anonymous access (no username / password)
const int MQTT_PORT = 1884;  // for secure access


void setup(){
    Serial.begin(115200);

    //Setup Variables
    wv.init(SSID, PASS, WIFI_STA, mdns);
    
    // initMQTT(MQTT_HOST,MQTT_PORT); //For Anonymous Access:
    initMQTT(MQTT_HOST,MQTT_PORT, mqtt_username,mqtt_password);

    //Start Wifi
    wv.startwifi();

      //Delay Needed to wait for MQTT init
  while(!connected()){
    //Wait until MQTT has initialized
    delay(10);
  }

    //optionally subscribes to a topic. This allows two way communication since the ESP will be listening.
    mqttSubscribe("Weave/example");


  //We use AsyncTimer to regularly send updates (useful for logging/monitoring)
  asynctimer.setInterval([]()
    { 
    
        StaticJsonDocument<200> jsonDoc;
        jsonDoc["temperature"] = random(0,50);
        jsonDoc["status"] = "Totally Online!";

        String jsonString;
        String topic = "Weave/example";
        serializeJson(jsonDoc, jsonString);

        publishJSON(jsonString, topic);
    
    },
    1000);

}



void loop(){


asynctimer.handle();
}