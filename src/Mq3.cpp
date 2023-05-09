#include "Mq3.h"
#include "Arduino.h"

void Mq3::setup(uint32_t signalPin, uint32_t heaterPin) {
    _signalPin = signalPin;
    _heaterPin = heaterPin;
    pinMode(_heaterPin, OUTPUT);
    digitalWrite(_heaterPin, LOW);
    pinMode(_signalPin, INPUT);
}

void Mq3::turnOn() {
    digitalWrite(_heaterPin, HIGH);
}

void Mq3::turnOff() {
    digitalWrite(_heaterPin, LOW);
}

void Mq3::calibrate() {
    long read_n = 20;
    long read_sum = 0;
    for(int i = 0; i < read_n; i++) {
        read_sum += analogRead(_signalPin);
        delay(100);
    }
    _offset = read_sum / read_n;
}

int Mq3::read() {
    int read = analogRead(_signalPin) - _offset;
    return read > 0 ? read : 0;
}

// convert mgl measurement to permille
int Mq3::permille(int mgl) {
    return mgl * BBR;
}