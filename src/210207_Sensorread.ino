#include "DHT.h"
const int DHT22PIN = D1;                           //Definition dass D0 Pin am NodeMCU einen leicht zu erkennenden Namen hat
#define DHTTYPE DHT22                               //Ab hier wird geladene Bib genutzt
DHT temp_sens(DHT22PIN, DHTTYPE);                    //Benennung und verknüpfung des Pins plus dem Typ des DHT22

                                                   //Konstanten immer komplett Groß schreiben
void setup() {
  Serial.begin(9600); //Serieller Port wird geöffnet
  temp_sens.begin();                              //Initialisiert Tempsensor DHT22
  
}

void loop() {
  float temp = temp_sens.readTemperature();
  float hum = temp_sens.readHumidity();

  Serial.print("Temperatur: ");
  Serial.println(temp);
  Serial.print("Luftfeuchte: ");
  Serial.println(hum);
  delay(2000);                                      //Delay, damit Daten nicht zu schnell gesendet werden
}
