#include "Weave.h"

//Initialization - When Created.
Weave::Weave(){

_mdnsName = "weave";
_ssid = "Weave Demo"; // setup in weaveconfig.h
_password = "12345678"; // setup in weaveconfig.h
_OTA_USER = "admin"; // setup in weaveconfig.h
_OTA_PASS = "admin1234"; // setup in weaveconfig.h
 _wifitype = WIFI_AP;
}

extern AsyncWebServer server;
void Weave::recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println(d);

  if (d == "ready"){
    WebSerial.println("You Are Ready for Action!");
  }

    if (d == "restart"){
    WebSerial.println("Restarting...");
    delay(2000);
    ESP.restart();
  }
}

void Weave::init(const char* ssid, const char* password, wifi_mode_t wifitype, const char* mdnsName)
{
  _ssid = ssid;
  _password = password;
  _wifitype = wifitype; 
  _mdnsName = mdnsName;
}

void Weave::init(const char* ssid, const char* password, wifi_mode_t wifitype, const char* mdnsName,const char* OTA_USER, const char* OTA_PASS)
{
  _ssid = ssid;
  _password = password;
  _wifitype = wifitype; 
  _mdnsName = mdnsName;
  _OTA_USER = OTA_USER;
  _OTA_PASS = OTA_PASS;
}


uint8_t Weave::startwifi(){
  Serial.println("Starting Wifi Module...");

  if(_wifitype == WIFI_AP_STA)
  {
  Serial.printf("WiFi Type Configured as: AP_STA\n Will Host a hidden network for ESP-NOW communication, and connect to an existing network.");

  /* Host a Hidden Network for use by ESP Now Mult=Mult */
  WiFi.softAP(_mdnsName, "pinecones", 0, 1, 4);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(_ssid, _password);
  Serial.println("Connecting to WiFi Network");
      int wifitimeout = 0;
        while (WiFi.status() != WL_CONNECTED) {
          Serial.print('.');
          delay(1000);
          wifitimeout += 1;
          if(wifitimeout > 10){
            Serial.println("Could not connect to WiFi Network, restarting ESP32");
            ESP.restart();
          }
        }

  } else{
    Serial.printf("WiFi Type Configured as:");
    if(_wifitype == WIFI_AP) {
      Serial.printf(" AP\n Please note that mDNS will not work for an AP. Use the IP Address Below");
      WiFi.mode(_wifitype);
      WiFi.softAP(_ssid, _password);

      Serial.println("Wait 100 ms for AP_START...");
      delay(100);
      Serial.println("Setting the AP");
      IPAddress Ip(192, 168, 10, 10);    //setto IP Access Point same as gateway
      IPAddress NMask(255, 255, 255, 0);
      WiFi.softAPConfig(Ip, Ip, NMask);
      Serial.print("ESP32 IP as soft AP: ");
      Serial.println(WiFi.softAPIP());

  }
    
    if(_wifitype == WIFI_STA){ 
      Serial.printf(" STA\n");
      WiFi.mode(_wifitype);
      WiFi.begin(_ssid, _password);
      Serial.println("Connecting to WiFi Network");
      int wifitimeout = 0;
        while (WiFi.status() != WL_CONNECTED) {
          Serial.print('.');
          delay(1000);
          wifitimeout += 1;

        if(wifitimeout > 10){
          Serial.println("Could not connect to WiFi Network, restarting ESP32");
          ESP.restart();
        }
  }
      Serial.print("\nESP32 IP on the WiFi network: ");
      Serial.println(WiFi.localIP());


    }
    /* STA connect to Router, AP - Be the Router */
   



  }
  


  WiFi.setAutoReconnect(true);
  // unsigned long wifitimeout = millis();
  // Serial.println("Attempting to Connect.");
  // Serial.println();
  Serial.println("******** ********");
  Serial.println("Wifi Start");
  return 0;
}

uint8_t Weave::startmdns(){
    /* MDNS Initialize */ 
  if (!MDNS.begin(_mdnsName))
  {
    Serial.println("mDNS Fail! Please check your network...");
    return 1;
  } 
  else
    {
      Serial.println("mDNS Start");
      return 0;
    }
  
}

// uint8_t Weave::startota(AsyncWebServer& server){
uint8_t Weave::startota(){
    /* Elegant OTA */
  AsyncElegantOTA.begin(&server, _OTA_USER, _OTA_PASS);
  Serial.println("AsyncOTA Start");
  return 0;
}

uint8_t Weave::startwebserial(){

  /*WebSerial*/
  WebSerial.begin(&server);
  Serial.println("WebSerial Start");
  
  //Callback Function
  auto callback = [&](uint8_t* data, size_t len) {
    recvMsg(data, len);
  };

  WebSerial.msgCallback(callback);
  return 0;
}

uint8_t Weave::startserver(){
  const char* NAME = _mdnsName;

  server.on("/", HTTP_GET, [NAME](AsyncWebServerRequest *request){
String webstring = String(NAME) + ".local/update</h1>";
String webserial = String(NAME) + ".local/webserial</h1>";
String html1 = R"HTML(
    <!DOCTYPE html>
    <html>
    <head>
        <style>
            body {
                background-color: #f5f5f5;
                font-family: "Helvetica Neue", Arial, sans-serif;
                font-size: 24px;
                color: #333333;
                text-align: center;
                margin-top: 200px;
            }
            h1 {
                font-size: 48px;
                color: #147efb;
                margin-bottom: 20px;
            }
        </style>
    </head>
    <body>
    <h1>Weave Correctly Configured!</h1>
        <h1>Update Webserver on )HTML";
        
  String html2  =   R"HTML(
        <h1>View WebSerial on )HTML";

String html3   =   R"HTML(    
    </body>
    </html>
)HTML";

String html = html1 + webstring + html2 + webserial + html3;
    request->send(200, "text/html", html);
});


  
  server.begin();

  Serial.println("WebServer Start");
  MDNS.addService("http", "tcp", 80);

  return 0;
}

uint8_t Weave::fullstack(){
  Serial.println("EscCore 1.0 (c) Adriaan van Wijk 2023");

  startwifi();
  startmdns();
  startota();
  startwebserial();
  startserver();
  //Server Default Page.

  return 0;
}

