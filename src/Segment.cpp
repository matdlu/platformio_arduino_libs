#include "Segment.h"
#include "Arduino.h"

static void pinModeSink(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, SEG_OFF);
}

void Segment::setup(SegmentPins pins) {
    _pins = pins;
    for(int i=0; i<_pins.digits_n; i++) {
        pinMode(_pins.digits[i], OUTPUT);
        digitalWrite(_pins.digits[i], SEG_DIGIT_OFF);
    }
    pinModeSink(_pins.a);
    pinModeSink(_pins.b);
    pinModeSink(_pins.f);
    pinModeSink(_pins.c);
    pinModeSink(_pins.dt);
    pinModeSink(_pins.e);
    pinModeSink(_pins.d);
    pinModeSink(_pins.g);

}

void Segment::showDigit(int n, bool value) { 
    digitalWrite(_pins.digits[n], value ? SEG_DIGIT_ON : SEG_DIGIT_OFF);
}

void Segment::setDot(bool value) {
    digitalWrite(_pins.dt, value ? SEG_ON : SEG_OFF);
}

void Segment::setSegment(bool a, bool b, bool c, bool d, bool e, bool f, bool g) {
    digitalWrite(_pins.a, a ? SEG_ON : SEG_OFF);
    digitalWrite(_pins.b, b ? SEG_ON : SEG_OFF);
    digitalWrite(_pins.c, c ? SEG_ON : SEG_OFF);
    digitalWrite(_pins.d, d ? SEG_ON : SEG_OFF);
    digitalWrite(_pins.e, e ? SEG_ON : SEG_OFF);
    digitalWrite(_pins.f, f ? SEG_ON : SEG_OFF);
    digitalWrite(_pins.g, g ? SEG_ON : SEG_OFF);
}

/* 0 - 9*/
void Segment::setDigit(unsigned short digit) {
    switch (digit)
    {
    case 0:
        setSegment(true, true, true, true, true, true, false);
        break;
    case 1:
        setSegment(false, true, true, false, false, false, false);
        break;
    case 2:
        setSegment(true, true, false, true, true, false, true);
        break;
    case 3:
        setSegment(true, true, true, true, false, false, true);
        break;
    case 4:
        setSegment(false, true, true, false, false, true, true);
        break;
    case 5:
        setSegment(true, false, true, true, false, true, true);
        break;
    case 6:
        setSegment(true, false, true, true, true, true, true);
        break;
    case 7:
        setSegment(true, true, true, false, false, false, false);
        break;
    case 8:
        setSegment(true, true, true, true, true, true, true);
        break;
    case 9:
        setSegment(true, true, true, true, false, true, true);
        break;
    default:
        // Segment error, digit larger than 9 or smaller than 0.
        Serial.println("Segment error, digit larger than 9 or smaller than 0.");
        setE();
        return;
    }
}

void Segment::setE() {
    setSegment(true, false, false, true, true, true, true);
    showDigit(0, true);
    showDigit(1, false);
    setDot(false);
}

void Segment::clear() {
    digitalWrite(_pins.a, SEG_OFF);
    digitalWrite(_pins.b, SEG_OFF);
    digitalWrite(_pins.f, SEG_OFF);
    digitalWrite(_pins.c, SEG_OFF);
    digitalWrite(_pins.dt, SEG_OFF);
    digitalWrite(_pins.e, SEG_OFF);
    digitalWrite(_pins.d, SEG_OFF);
    digitalWrite(_pins.g, SEG_OFF);
}

void Segment::loading(unsigned int interval) {
    if ( _loading_time == 0 ) {
        _loading_time = millis();
        showDigit(0, false);
        showDigit(1, true);
        setDot(false);
        switch(_loading_step) {
        case 0:
            setSegment(false, false, false, false, false, false, true);
            break;
        case 1:
            setSegment(false, false, true, false, false, false, false);
            break;
        case 2:
            setSegment(false, false, false, true, false, false, false);
            break;
        case 3:
            setSegment(false, false, false, false, true, false, false);
            break;
        }
        _loading_step++;
        if ( _loading_step >= 4 ) {
            _loading_step = 0;
        } 
    } else if ((millis() - _loading_time) > interval) {
        _loading_time = 0;
    } 
}

void Segment::displayNumberBlock(int number, int interval) {
    int div = 1;
    while(div < number){
        div *= 10;
    }
    div /= 10;
    while(div > 0) {
        Segment::clear();
        Segment::setDigit((number / div) % 10);
        Segment::showDigit(0, true);
        Segment::showDigit(1, false);
        delay(interval);
        Segment::clear();
        delay(interval);
        div /= 10;
    }
}

void Segment::displayNumber(int number, int interval, int endInterval) {
    switch ( _state ) 
    {
    case SEGMENT_START:
        _div = 1;
        while(_div < number){
            _div *= 10;
        }
        _div /= 10;
        _state = SEGMENT_DISPLAY;
        break;
    case SEGMENT_DISPLAY:
        if ( _timer.available(interval) ) {
            Segment::clear();
            Segment::setDigit((number / _div) % 10);
            Segment::showDigit(0, true);
            Segment::showDigit(1, false);
            _state = SEGMENT_WAIT;
            _timer.restart(); // next tick
        } 
        break;
    case SEGMENT_WAIT:
        if ( _timer.available(interval) ) {
            Segment::clear();
            _div /= 10;
            if (_div <= 0) {
                _state = SEGMENT_END;
            } else {
                _state = SEGMENT_DISPLAY;
            }
            _timer.restart(); // next tick
        }
        break;
    case SEGMENT_END:
        if ( _endTimer.available(endInterval) ) {
            Segment::clear();
            _state = SEGMENT_START;
            _timer.stop(); // replay sequance
            _endTimer.stop();
        }
        break;
    }
}
    
#ifdef SEGMENT_DEMO
void Segment::demo() {
    Segment::showDigit(0, true);
    Segment::showDigit(1, true);
    Segment::setDot(true);
    for(int i = 0; i < 10; i++) {
        Segment::setDigit(i);
        delay(1000);
    }
}
#endif