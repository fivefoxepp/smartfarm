#define BLYNK_TEMPLATE_ID "*****"
#define BLYNK_TEMPLATE_NAME "*****"
#define BLYNK_AUTH_TOKEN "*******"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

#define RELAY1 4
#define RELAY2 2
#define DHTPIN 15          
#define DHTTYPE DHT11

#define MOISTURE_PIN1 34     
#define MOISTURE_PIN2 35

char ssid[] = "nam wifi";
char pass[] = "yourpasswifi";

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  
  int moisture1 = analogRead(MOISTURE_PIN1); 
  int moisture2 = analogRead(MOISTURE_PIN2);


  
  Blynk.virtualWrite(V2, t);       
  Blynk.virtualWrite(V3, h);       
  Blynk.virtualWrite(V4, moisture1); 
  Blynk.virtualWrite(V5, moisture2);

}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY1, 1);
  digitalWrite(RELAY2, 1);

  dht.begin();

  timer.setInterval(5000L, sendSensor);  
}

void loop() {
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(RELAY1, value);
}

BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(RELAY2, value);
}
