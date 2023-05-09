#pragma once

#include "Timer.h"
#include "inttypes.h"

// for common anode display ON = LOW, OFF = HIGH
#define SEG_ON LOW
#define SEG_OFF HIGH
#define SEG_DIGIT_ON HIGH
#define SEG_DIGIT_OFF LOW

#define MAX_DIGITS 4

struct SegmentPins {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t dt;
    int digits_n; 
    uint32_t digits[MAX_DIGITS]; 
};

/* 7 segment display */
class Segment
{
private:
    // diode pins
    SegmentPins _pins;

    // loading
    long _loading_time = 0;
    long _loading_step = 0;

    // displayNumber
    enum SegmentState {
        SEGMENT_START,
        SEGMENT_DISPLAY,
        SEGMENT_WAIT,
        SEGMENT_END,
    };
    Timer _timer;
    Timer _endTimer;
    int _div = 1;
    SegmentState _state = SEGMENT_DISPLAY;

public:
    void setup(SegmentPins pins);
    void showDigit(int n, bool value);
    void setSegment(bool a, bool b, bool c, bool d, bool e, bool f, bool g);
    void setDot(bool value);
    void setDigit(unsigned short digit);
    void setE();
    void clear();
    void loading(unsigned int interval);
    void displayNumberBlock(int number, int interval);
    void displayNumber(int number, int interval = 500, int endInterval = 1500);
#ifdef SEGMENT_DEMO
    void demo() {
#endif
};