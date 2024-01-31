#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>

#define SENSOR_PIN 33  // Pin DHT
#define LED_PIN 26     // Pin de la LED
#define DHT_TYPE DHT11 // DHT11

DHT_Unified dht(SENSOR_PIN, DHT_TYPE);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  delay(2000); 

  // Console série
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("DHTxx Unified Sensor Example"));
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print(F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print(F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print(F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print(F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print(F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));


  sensors_event_t event;
  dht.temperature().getEvent(&event);

  if (!isnan(event.temperature)) {
    
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  } else {
    Serial.println(F("Error reading temperature!"));
  }

 
  dht.humidity().getEvent(&event);

  if (!isnan(event.relative_humidity)) {
   
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  } else {
    Serial.println(F("Error reading humidity!"));
  }

  
  if (event.temperature > 25.0) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // Mode deep sleep pendant 5 secondes
  esp_deep_sleep(5e6); 
}

void loop() {
  
}
