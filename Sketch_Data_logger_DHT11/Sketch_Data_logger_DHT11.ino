#include "ThingSpeak.h"
#include <WiFi.h>
#include <DHT.h>

#define DHTPIN 5

DHT dht(DHTPIN,DHT11);

const char* ssid = "Purba";
const char* password = "hafizhah";
int keyIndex = 0;
WiFiClient client;

unsigned long channelNumber = 1239087;
// Service API Key
const char* apiKey = "JSVGUY3AHSQN0YGL";

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  Serial.println("Connecting...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    
    ThingSpeak.begin(client); 
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  int x = ThingSpeak.writeFields(channelNumber, apiKey);
  if(x == 200){
    Serial.println("You've been connected to ThingSpeak");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" C");
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println("%");
    }
    else {
      Serial.println("Failed to connect to ThingSpeak, HTTP error code " + String(x));
      }
      delay(15000); //delay 15 detik
}
