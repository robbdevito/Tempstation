#include "DHT.h"                              //Library für die DHT Sensoren
#define DHTTYPE DHT22                         //Ab hier wird geladene Bib genutzt. Definition des DHT Types (Tempsensor)
const int DHT22PIN = D1;                      //Namensgebung des Pins; Hinweis: Konstanten immer komplett groß schreiben
DHT temp_sens(DHT22PIN, DHTTYPE);             //Benennung und Verknüpfung des Pins plus dem Typ des DHT22

void setup() {
  Serial.begin(9600);                         //Serieller Port wird geöffnet
  temp_sens.begin();                          //Initialisiert Tempsensor DHT22
}
void loop() {
  float temp = temp_sens.readTemperature();   //Variable temp entspricht gelesenen Temp-Werten
  float hum = temp_sens.readHumidity();       //Variable hum entspricht gelesenen Humidity-Werten
  Serial.print("Temperatur: ");
  Serial.println(temp);
  Serial.print("Luftfeuchte: ");
  Serial.println(hum);                        //Ausgabendefinition
  delay(2000);                                //Delay, damit Daten nicht zu schnell gesendet werden
}
