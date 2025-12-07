#ifndef DHT11_H
#define DHT11_H

#include <Arduino.h>

class DHT11 {
public:
    DHT11(uint8_t pin);
    
    int check_response();
    int receive_data();
    int checksum();

    int read_temperature();
    int read_humidity();

private:
    uint8_t _pin;
    uint8_t answer[5];
};

#endif
