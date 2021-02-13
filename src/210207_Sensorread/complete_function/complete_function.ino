/* by robbdevito
 *  13.02.21
 *  reading and sending datas with an DHT22 Sensor, connecting to known WiFi, sending the Data to ThingSpeak-Server
 *  Used Parts:
 *  - NodeMCU
 *  - DHT22 Sensor
 *  - ThingSpeak.com
*/

#include <ESP8266WiFi.h>
#include "DHT.h"                      //Lib of Sensor
#define DHTTYPE DHT22                 //Type of Sensor

String apiKey = "V3VYXB1ADM9360A5";   //Personal write API at Thingspeak
const char* ssid =  "ELIL-1860";      //personal WIFI SSID
const char* password =  "976764542267995454467053270947";
const char* server = "api.thingspeak.com";
const int DHT22PIN = D1;              //used pin at NODE MCU for Sensor

DHT temp_sens(DHT22PIN, DHTTYPE);     //Naming of Sensor and its link between pin and type

WiFiClient client;                    //Creates a client that can connect to to a specified internet IP address and port as defined in client.connect().

void setup() {

/*setup for Sensor*/
  temp_sens.begin(); 

/*WIFI connection setup --> Can be replaced with LIB*/  
  WiFi.mode(WIFI_STA);    //disconnect all WIFI connections
  WiFi.disconnect();
  delay(100);

  Serial.begin(115200);   //beginn communication with Baudrate 115200
  delay(10);

  Serial.println();
  Serial.println("Connecting to following network:");
  Serial.println(ssid);

/* Start WiFi connection, for not established connection print: ...
   after successfully connecting to WiFi, print success message 
   and IP of ESP module*/
   
  WiFi.begin(ssid, password);       
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi Connection successful"); 
    Serial.print("IP of own ESP-Module: ");
    Serial.println(WiFi.localIP());
/*End of WIFI connection process*/
}

void loop() {
  float temp = temp_sens.readTemperature();   //Variable temp corresponds to read temp-values
  float hum = temp_sens.readHumidity();       //Variable hum corresponds to read Humidity-Werten

if (client.connect(server,80))                //src: internet: "184.106.153.149" or api.thingspeak.com
{
  String postStr = apiKey;
  postStr +="&field1=";
  postStr += String(temp);
  postStr +="&field2=";
  postStr += String(hum);
  postStr += "\r\n\r\n";
  
  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(postStr.length());
  client.print("\n\n");
  client.print(postStr);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" degrees Celcius, Humidity: ");
  Serial.print(hum);
  Serial.println("%. Send to Thingspeak.");
}
client.stop();

Serial.println("Waiting...");
delay(30000);                                 //as Thingspeak needs at least 15 sec to proceed messages, delay. 
}
