#include "Timer.h"
#include "Arduino.h"

void Timer::begin(long interval) {
  if (_interval == 0 && _endTime == 0) {
    _interval = interval;
    _endTime = millis() + _interval;
  } 
}

bool Timer::atBegin() {
  return _interval == 0 && _endTime == 0;
}

void Timer::restart() {
  _endTime = millis() + _interval;
}

void Timer::stop() {
  _interval = 0;
  _endTime = 0;
}

bool Timer::available(long interval) {
  begin(interval);
  return millis() >= _endTime;
}

long Timer::timeUntil() {
  long currentTime = millis();
  return _endTime > currentTime ? _endTime - currentTime : 0;
}