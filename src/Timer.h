#pragma once

class Timer
{
private:
  long _endTime = 0;
  long _interval = 0;

public:
  // interval - value in ms
  void begin(long interval);
  bool atBegin();
  // auto starts when calling availible
  bool available(long interval);
  void restart();
  void stop();
  long timeUntil();
};
