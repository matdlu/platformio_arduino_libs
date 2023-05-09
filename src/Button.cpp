#include "Button.h"

void Button::setup(uint32_t pin) {
    _pin = pin;
}

void Button::_update() {
    _lastState = _currentState;
    _currentState = digitalRead(_pin);
}

bool Button::pressed(long interval) {
    _update();
    bool pressed = _currentState == BUTTON_ON && _timer.available(interval);
    if ( pressed ) {
        _timer.stop();
    }
    return pressed;
}

bool Button::shortPressed() {
    return pressed(BUTTON_SHORT_PRESS_TIME);
}

bool Button::released(long interval) {
    _update();
    _timer.begin(interval);
    bool released = _lastState == BUTTON_ON && _currentState == BUTTON_OFF && _timer.available(interval);
    if ( released ) {
        _timer.stop();
    }
    return released;
}

bool Button::shortReleased() {
    return released(BUTTON_SHORT_MIN_PRESS_TIME);
}
