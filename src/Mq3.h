#pragma once

#include "inttypes.h"

// Polish BBR ratio
#define BBR 2.1

/* Mq3 alcohol and gas sensor */
class Mq3 
{
private:
    uint32_t _signalPin;
    uint32_t _heaterPin;
    long _offset = 0;
public:
    void setup(uint32_t signalPin, uint32_t heaterPin);
    void turnOn();
    void turnOff();
    void calibrate();
    int read();
    int read_avg();
    int permille(int mgl);
};