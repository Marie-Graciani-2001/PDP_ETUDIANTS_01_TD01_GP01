#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>

#define SENSOR_PIN 33  // Pin auquel le capteur DHT est connecté
#define LED_PIN 26     // Pin de la LED
#define DHT_TYPE DHT22 // Type de capteur DHT que vous utilisez (DHT11, DHT22, DHT21)

DHT_Unified dht(SENSOR_PIN, DHT_TYPE);

// Déclarer la variable pour stocker le temps de veille en microsecondes (5 secondes dans cet exemple)
const uint64_t DEEP_SLEEP_TIME_US = 5e6;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  dht.begin();

  // Imprimez les détails du capteur DHT dans la console série
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

  // Mesurer la température et l'humidité
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  
  if (!isnan(event.temperature)) {
    // Affichez la température avec un peu de formatage
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  } else {
    Serial.println(F("Error reading temperature!"));
  }

  // Obtenir l'événement d'humidité
  dht.humidity().getEvent(&event);
  
  if (!isnan(event.relative_humidity)) {
    // Affichez l'humidité relative avec un peu de formatage
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  } else {
    Serial.println(F("Error reading humidity!"));
  }

  // Ajoutez ici le code pour contrôler la LED en fonction des valeurs mesurées, par exemple :
  if (event.temperature > 25.0) {
    digitalWrite(LED_PIN, HIGH); // Allumez la LED si la température est supérieure à 25 °C
  } else {
    digitalWrite(LED_PIN, LOW); // Éteignez la LED sinon
  }

  // Configuration du mode de veille "Deep sleep"
  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME_US);

  // Mettez l'ESP32 en mode deep sleep
  esp_deep_sleep_start();
}

void loop() {
  // La fonction loop ne doit rien contenir car toute la logique est déplacée dans la fonction setup
}
