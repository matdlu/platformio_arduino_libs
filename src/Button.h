#pragma once

#include "Timer.h"
#include "Arduino.h"

#define BUTTON_SHORT_PRESS_TIME 300
#define BUTTON_SHORT_MIN_PRESS_TIME 100
#define BUTTON_ON LOW
#define BUTTON_OFF HIGH

/* Tactile buttons */
class Button 
{
private:
    int _currentState = LOW;
    int _lastState = LOW;
    Timer _timer;
    void _update();
    uint32_t _pin;

public:
    void setup(uint32_t pin);
    bool pressed(long interval);
    bool shortPressed();
    bool released(long interval);
    bool shortReleased();
};