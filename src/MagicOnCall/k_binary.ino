// Binary input
// Like switch and detectors, PIR sensor, Landström detector,

// ToDo: 
// Add a full json with duration and pastduration
// Add a function that count the number of on/off with a swichtime less than a second
//  as to have different things happening if one toggels 2 times, or toggle 3 times
//  will be used in Digital Switching applications


#include "Arduino.h"

class Binary {
  
  private:
    byte _pin;                                // Needed for all sensors
    boolean _inverted           = false; 
    boolean _LOW                = LOW; 
    boolean _HIGH               = HIGH; 
    

    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "binary";   // Needed for all sensors
    int _thingSpeakField        = 0;
    unsigned long _changetime   = 0; 
    unsigned long _duration       = 0;          // Needed for all sensors
    unsigned long _pastduration   = 0;          // Needed for all sensors
    unsigned long _past2duration  = 0;          // Needed for all sensors
    unsigned long _past3duration  = 0;          // Needed for all sensors
    unsigned long _past4duration  = 0;          // Needed for all sensors
    unsigned long _past5duration  = 0;          // Needed for all sensors

    //float _warningVoltage       = 12.7;
    //int _threshold              = 30; 
    boolean _count2             = LOW;
    boolean _count3             = LOW;
    boolean _count4             = LOW;
    boolean _stateDS            = LOW;
    boolean _currentState       = LOW;
    float _lastReportedValue    = 0.0;        // Needed for all sensors
    float _lastReadValue        = 0.0;        // Needed for all sensors
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors

    float _diff = 0.3;  // Needed for all sensors
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;  // Needed for all sensors

  public:
  
    Binary(byte pin = 36) {
      this->_pin = pin;
      pinMode(pin, INPUT);
    }

    // Alterative constructor
    void begin(byte pin = 36, boolean inverted = false, String name = "binary", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      pinMode(pin, INPUT);
      this->_inverted = inverted; 
      if (_inverted) {
        _LOW          = HIGH; 
        _HIGH         = LOW; 
      } else {
        _LOW          = LOW; 
        _HIGH         = HIGH; 
      }
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(byte pin = 36, boolean inverted = false, String name = "binary", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      pinMode(pin, INPUT);
      this->_inverted = inverted; 
      if (_inverted) {
        _LOW          = HIGH; 
        _HIGH         = LOW; 
      } else {
        _LOW          = LOW; 
        _HIGH         = HIGH; 
      }
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Binary on pin: " + (String) _pin + " , called: " + _name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }

    void check(float diff = 0.1){
      
      unsigned long m = millis();
      if (digitalRead(_pin) == _HIGH) {  
        if (_debug) {
          digitalWrite(LED_BUILTIN, _HIGH);   // turn LED ON
          delay(100);                // delay 100 milliseconds 
        }
        if ( _currentState == LOW) {
          if (_debug) { Serial.println("Binary on pin: " + (String) _pin + " , called: " + _name + " : Active!"); }
           _currentState  = HIGH;       // update variable state to HIGH
           _past5duration = _past4duration;
           _past4duration = _past3duration;
           _past3duration = _past2duration;
           _past2duration = _pastduration;
           _pastduration = _duration; 
           _duration = m - _changetime; 
           if ( (_currentState) && (_pastduration > 1000) && (_duration < 2000)) {_stateDS = HIGH; _count2 = HIGH; _count3 = LOW; _count4 = LOW;}
           if ( (_currentState) && (_past3duration < 1000) && (_past2duration < 1000) && (_pastduration < 1000) && (_duration < 2000)) {_count3 = HIGH; _count2 = LOW; _count4 = LOW;}
           if ( (_currentState) && (_past5duration < 1000) && (_past4duration < 1000) && (_past3duration < 1000) && (_past2duration < 1000) && (_pastduration < 1000) && (_duration < 2000)) {_count4 = HIGH; _count2 = LOW; _count3 = LOW;}
           if (_debug) { Serial.println("Binary on pin: " + (String) _pin + " , called: " + _name + " : Previous state: " + (String) _duration + " ms"); }
           _changetime = m;
           mqttJSON[_name ] = 1;  
           if (_thingSpeakField != 0) {
              ThingSpeak.setField(_thingSpeakField, 1);
           }
           _postingIntervalTimer = millis();
           _lastReportedValue = 1; 
        }
      } 
      else {
        if (_debug) {
          digitalWrite(LED_BUILTIN, _LOW); // turn LED OFF
          delay(200);             // delay 200 milliseconds 
        }  
        if ( _currentState  == HIGH){
          if (_debug) { Serial.println("Binary on pin: " + (String) _pin + " , called: " + _name + " : Passive!"); }
          _currentState  = LOW;       // update variable state to LOW
          _past5duration = _past4duration;
          _past4duration = _past3duration;
          _past3duration = _past2duration;
          _past2duration = _pastduration;
          _pastduration = _duration; 
          _duration = m - _changetime; 
          _stateDS = LOW;
          _count2 = LOW;
          _count3 = LOW;
          _count4 = LOW;
          if (_debug) { Serial.println("Binary on pin: " + (String) _pin + " , called: " + _name + " : Previous state: " + (String) _duration + " ms"); }
          _changetime = m;
          mqttJSON[_name ] = 0;  
          if (_thingSpeakField != 0) {
            ThingSpeak.setField(_thingSpeakField, 0);
          }
          _postingIntervalTimer = millis();
          _lastReportedValue = 0; 
        }
      }
    }

    // Checks the state of the binary pin
    boolean state(void) {
      if (millis()- _readingIntervalTimer < 1000)
      {
        return _currentState;
      }
      else
      {
        //read();
        return _currentState;
      }
    }

 /* 
    // Checks the state of the binary pin
    boolean state(void) {
      return _currentState;
    }
*/

    // Sets the state of the DS low
    void digitalswitchLow(void) {
      _stateDS = LOW;
      //return _stateDS;
    }
    
    // Sets the state of the DS low
    void digitalswitchHigh(void) {
      _stateDS = HIGH;
      //return _stateDS;
    }
    
    // returns the state of the DS low
    boolean digitalswitchState(void) {
      return _stateDS;
    }

    boolean count2(void) {
      return _count2;
    }
    
    boolean count3(void) {
      return _count3;
    }
    
    boolean count4(void) {
      return _count4;
    }

};
