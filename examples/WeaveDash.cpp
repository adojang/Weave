/*
  Weave Dashboard Example - This example will host an AP from the ESP32 and broadcast an interactive dashboard
   using the ESPDash library by Ayush Sharma. OTA, WebSerial, mDNS, and MQTT are also enabled.
   Currently, the fullstack() is required to run ESPDash.
  -----
  Author: Adriaan van Wijk (https://github.com/adojang/)
  
  Please consider starring the repository on Github if you like the library 
  Repository Link: https://github.com/adojang/Weave
*/


#include <Weave.h>
#include <ESPDash.h>


Weave wv;
AsyncWebServer server(80);
AsyncTimer asynctimer;
ESPDash dashboard(&server,false);

//Set your own Wifi and SSID below.
const char* SSID = "Mourning to Dancing";
const char* PASS = "throughchristalone";
const char* mdns = "weave";

/*ESPDash Cards*/

Card card_button(&dashboard, BUTTON_CARD, "Test Button");
Card card_status(&dashboard, STATUS_CARD, "Status", "idle");
Card card_generic(&dashboard, GENERIC_CARD, "Times Button Clicked");
Card card_temp(&dashboard, TEMPERATURE_CARD, "Device Temperature");
Card timesinceboot(&dashboard, HUMIDITY_CARD, "Time Since Boot", "min");


String truetimesinceboot = "Startup";
int timesbuttonclicked = 0;

void configDash()
{
  card_generic.update(0, "times");
  card_temp.update(25, "C");
  card_status.update("Startup", "success");
  dashboard.sendUpdates();
}

void buttonTimeout(Card *cardptr, int timeout = 500)
{
  cardptr->update(1);
  asynctimer.setTimeout([cardptr]()
                        {
    cardptr->update(0);
    dashboard.sendUpdates(); },
                        timeout);
  dashboard.sendUpdates();
}

void startButtonCB()
{
  card_button.attachCallback([&](int value)
                             {
    static int state = 0;
    timesbuttonclicked += 1;
    card_generic.update(timesbuttonclicked);


    /* Update Status*/
    if(state == 0) card_status.update("State 0", "success");
    if(state == 1) card_status.update("State 1", "danger");
    if(state == 2) card_status.update("State 2", "warning");
    if(state == 3) card_status.update("State 3", "idle");
    state++;
    if(state > 3) state = 0;

    buttonTimeout(&card_button); // Auto Timeout to Reset Button
    dashboard.sendUpdates(); });

}

void updateTime()
{

  int seconds = millis() / 1000;
  int minutes = seconds / 60;
  int hours = minutes / 60;

  if (seconds < 60)
  {
    timesinceboot.update(seconds, "seconds");
    truetimesinceboot = String(seconds) + " seconds";
  }
  else
  {
    if (minutes < 60)
    {
      String timeA = String(minutes) + ":" + String(seconds % 60);
      timesinceboot.update(timeA, "min");
      truetimesinceboot = timeA + " min";
    }
    else
    {
      String timeB = String(hours) + ":" + String(minutes % 60) + ":" + String(seconds % 60);
      timesinceboot.update(timeB, "sec");
      truetimesinceboot = timeB + " sec";
    }
  }
  dashboard.sendUpdates();
}



void setup(){
    Serial.begin(115200);

    //Setup Variables
    
    wv.init(SSID, PASS, WIFI_AP_STA, mdns);
    wv.fullstack();

    //For some reason, startwebserial() is required, otherwise the whole stack crashes.
    //This is why wv.fullstack() is used.


    configDash();
    startButtonCB();

    
    Serial.printf("Setup Complete.\n");
    Serial.printf("Go to %s.local to verify the Dashboard is enabled\n", mdns);

    asynctimer.setInterval([]()
                         { updateTime(); },
                         1000);
}

unsigned long boottime = millis();
unsigned long simulateTemp = millis();

void loop(){

  if (millis() - boottime > 1000){
    boottime = millis();
    WebSerial.printf("Time Since Boot: %d\n", int(boottime/1000));
  }

  
  //Simulate temperature updates
  if(millis() - simulateTemp > 500){
    simulateTemp = millis();
    card_temp.update(float(random(40,43)/1.73));
    dashboard.sendUpdates();
  }


asynctimer.handle();
}