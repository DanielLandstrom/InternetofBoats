// Light monitor

#include "Arduino.h"

class Light {
  
  private:
    byte _pin;                                // Needed for all sensors
    boolean _debug = false;                   // Needed for all sensors
    String  _name               = "light";    // Needed for all sensors
    unsigned long _changetime   = 0; 
    unsigned long _duration     = 0;          // Needed for all sensors
    unsigned long _pastduration = 0;          // Needed for all sensors

    int _threshold = 30; 

    boolean _currentState = LOW;              // Night = LOW, Day = HIGH 
    float _lastReportedValue = 0.0;           // Needed for all sensors
    float _lastReadValue = 0.0;               // Needed for all sensors
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors

    float _diff = 20;  // Needed for all sensors
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;  // Needed for all sensors

  public:
    Light(byte pin = 34) {
      this->_pin = pin;
    }

    // Alterative constructor
    void begin(byte pin = 34, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(byte pin = 34, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Lightsensor on pin: " + (String) _pin + " , called: " + _name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }


    float read(void)
    {
      unsigned long m = millis(); 
      if (millis()- _readingIntervalTimer < 100) // A 100 is a bit high I think
      {
        return _lastReadValue;
      }
      else
      {
        float light = analogRead(_pin)/4096*100;
        _readingIntervalTimer = millis();
        _lastReadValue = light;
        if (light <= _threshold){
          _currentState = HIGH;
          // add code for detecting when swhitching state (with hysteres)
          _pastduration = _duration; 
          _duration = m - _changetime; 

        } else {
          _currentState = LOW;
        }
        if (_debug) {
          Serial.println("Light on pin: " + (String) _pin + " , called: " + _name + " : " + (String) light + " State: " + (String) _currentState);
        }
        return light;
      }
    }

    // Checks the state of the touch pin
    boolean state(void) {
      if (millis()- _readingIntervalTimer < 100)
      {
        return _currentState;
      }
      else
      {
        read();
        return _currentState;
      }
    }

    void check(float diff = 2.0){

      float light = read();
      if ((millis() - _postingIntervalTimer  > _postingIntervalDelay)|| 
       (fabs(light - _lastReportedValue) >= diff ))
      { 
        if (_debug) {
          Serial.println("Light on pin: " + (String) _pin + " , called: " + _name + " : Published light: " + (String) light);
        } 
        mqttJSON[ _name ] = light;  // Using the name of this instance, we put the light reading in the JSON container that we send via MQTT.
        mqttJSON[ _name + "_state" ] = _currentState; // and also the state
        _postingIntervalTimer = millis();
        _lastReportedValue = light;
      }
    }

};
