// FLASH Led
/*
#include "Arduino.h"

class FlashLED {
  private:
    byte _pin;  // Needed for all sensors
    boolean _debug = false; // Needed for all sensors
    String  _name               = "touch";  // Needed for all sensors
    unsigned long _duration     = 0;          // Needed for all sensors
    unsigned long _pastduration = 0;          // Needed for all sensors

    // Variables for the flash
    int _out = 0;

    int _flash_counter = 0;
    int _flash_state = 0;
    unsigned long  _flash_starttime = 0;
    int _flash_activations = 0;
    int _flash_maxcount = 10000;

    //    int _threshold = 30;
    boolean _currentState = LOW;
    float _lastReportedValue = 0.0;// Needed for all sensors
    //    float _lastReadValue = 0.0;   // Needed for all sensors
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors

    //float diff = 0.1;  // Needed for all sensors
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;// Needed for all sensors

  public:
    FlashLED(byte pin = 5) {
      this->_pin = pin;
      pinMode(pin, OUTPUT);
    }

    // Alterative constructor
    void begin(byte pin = 5, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      pinMode(pin, OUTPUT);
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(byte pin = 5, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      pinMode(pin, OUTPUT);
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Flash on pin: " + (String) _pin );
      }
    }


    void activate()
    {
      _flash_activations = _flash_activations + 1;
      _flash_state = 0;
      _flash_starttime = millis();
    }


    int check() {
      _flash_counter = millis()-_flash_starttime;
      bool flash_done = false;
      if (_flash_activations > 0 ) {
        if (_flash_counter > _flash_maxcount) {
          flash_done = true;
          if (_flash_state == 1) {
            _flash_activations = _flash_activations - 1;
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low - reset");}
          }
        }
        else if ((_flash_counter > 8000) && !flash_done) {
          flash_done = true;
          if (_flash_state == 0) {
            _flash_state = 1;
            digitalWrite(_pin, HIGH);
            if (_debug) {Serial.println("High 8000");}
          }
        }
        else if ((_flash_counter > 6000) && !flash_done) {
          flash_done = true;
          if (_flash_state == 1) {
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low 6000");}
          }
        }
        else if ((_flash_counter > 4000) && !flash_done) {
          flash_done = true;
          if (_flash_state == 0) {
            _flash_state = 1;
            digitalWrite(_pin, HIGH);
            if (_debug) {Serial.println("High 4000");}
          }
        }
        else if ((_flash_counter > 3000) && !flash_done) {
          flash_done = true;
          if (_flash_state == 1) {
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low 3000");}
          }
        }
        else if ((_flash_counter > 2000) && !flash_done) {
          flash_done = true;
          if (_flash_state == 0) {
            _flash_state = 1;
            digitalWrite(_pin, HIGH);
            if (_debug) {Serial.println("High 2000");}
          }
        }
        else if ((_flash_counter > 1000) && !flash_done) {
          flash_done = true;
          if (_flash_state == 1) {
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low 1000");}
          }
        }
        else if ((_flash_counter > 1) && !flash_done) {
          flash_done = true;
          if (_flash_state == 0) {
            _flash_state = 1;
            digitalWrite(_pin, HIGH);
            if (_debug) {Serial.println("High 1");}
          }
        }
        else {
          if (_flash_state == 1) {
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low else");}
          }
        }
        return _flash_activations;
      }
    }

    int strobe() {
      _flash_counter = millis()-_flash_starttime;
      bool flash_done = false;
      if (_flash_activations > 0 ) {
        if (_flash_counter > _flash_maxcount/10) {
          flash_done = true;
          _flash_activations = _flash_activations - 1;
          _flash_starttime = millis();
          if (_flash_state == 1) {
            //_flash_activations = _flash_activations - 1;
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low - reset");}
          }
        }
        else if ((_flash_counter > 800) && !flash_done) {
          flash_done = true;
          if (_flash_state == 1) {
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("High 8000");}
          }
        }
        else if ((_flash_counter > 700) && !flash_done) {
          flash_done = true;
          if (_flash_state == 0) {
            _flash_state = 1;
            digitalWrite(_pin, HIGH);
            if (_debug) {Serial.println("High 8000");}
          }
        }
        else if ((_flash_counter > 600) && !flash_done) {
          flash_done = true;
          if (_flash_state == 1) {
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low 6000");}
          }
        }
        else if ((_flash_counter > 400) && !flash_done) {
          flash_done = true;
          if (_flash_state == 0) {
            _flash_state = 1;
            digitalWrite(_pin, HIGH);
            if (_debug) {Serial.println("High 4000");}
          }
        }
        else if ((_flash_counter > 300) && !flash_done) {
          flash_done = true;
          if (_flash_state == 1) {
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low 3000");}
          }
        }
        else if ((_flash_counter > 200) && !flash_done) {
          flash_done = true;
          if (_flash_state == 0) {
            _flash_state = 1;
            digitalWrite(_pin, HIGH);
            if (_debug) {Serial.println("High 2000");}
          }
        }
        else if ((_flash_counter > 100) && !flash_done) {
          flash_done = true;
          if (_flash_state == 1) {
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low 1000");}
          }
        }
        else if ((_flash_counter > 1) && !flash_done) {
          flash_done = true;
          if (_flash_state == 0) {
            _flash_state = 1;
            digitalWrite(_pin, HIGH);
            if (_debug) {Serial.println("High 1");}
          }
        }
        else {
          if (_flash_state == 1) {
            _flash_state = 0;
            digitalWrite(_pin, LOW);
            if (_debug) {Serial.println("Low else");}
          }
        }
        return _flash_activations;
      }
    }

};
*/
