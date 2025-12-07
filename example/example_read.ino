#include <Arduino.h>
#include "DHT11.h"

#define DHTPIN 4 // Change to your pin
DHT11 dht(DHTPIN);

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("DHT11 Test Starting...");
}

void loop() {
  // Reset data buffer for every reading
  for (int i = 0; i < 5; i++) dht.answer[i] = 0;

  // Step 1: Check sensor response
  if (!dht.check_response()) {
    Serial.println("No response from DHT11!");
    delay(2000);
    return;
  }

  // Step 2: Receive data (40 bits)
  if (!dht.receive_data()) {
    Serial.println("Data Timeout/Error!");
    delay(2000);
    return;
  }

  // Step 3: Validate checksum
  if (!dht.checksum()) {
    Serial.println("Checksum Error!");
    delay(2000);
    return;
  }

  // Step 4: Extract and print values
  Serial.print("Humidity: ");
  Serial.print(dht.read_humidity());
  Serial.print("%   |   Temp: ");
  Serial.print(dht.read_temperature());
  Serial.println("°C");

  delay(2000);
}
