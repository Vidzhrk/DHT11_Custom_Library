# DHT11 Custom Arduino Library

A lightweight custom library for interfacing DHT11 Temperature & Humidity sensor using manual bit-timing protocol.  
Built from scratch — no external libraries used.

---

## Features
✔ Built with low-level DHT11 protocol  
✔ Timeout protection (no infinite blocking)  
✔ Works with Arduino & ESP32  
✔ Checksum validation  
✔ Written in C++ OOP style

---

## Wiring

| DHT11 | Arduino/ESP32 |
|-------|---------------|
| VCC   | 3.3V / 5V     |
| GND   | GND           |
| DATA  | D2 (or any GPIO) |
| 10k resistor | DATA → VCC |

---

## Example Usage

```cpp
#include "DHT11.h"

#define DHTPIN 2
DHT11 dht(DHTPIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
  uint8_t humidity = dht.read_humidity();
  uint8_t temperature = dht.read_temperature();

  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temperature);

  delay(2000);
}
