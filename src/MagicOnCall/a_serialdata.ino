#include "Arduino.h"

class serialData {
  
  private:
    byte _pin;                                // Needed for all sensors
    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "serial";   // Needed for all sensors
    int _thingSpeakField        = 0;
    unsigned long _duration     = 0;          // Needed for all sensors
    unsigned long _pastduration = 0;          // Needed for all sensors
    unsigned long _changetime   = 0;          // Needed for all sensors
    
    float _warningValue         = 12.7;
    int _threshold              = 30; 

    boolean _currentState       = LOW;
    float _lastReportedValue    = 0.0;        // Needed for all sensors
    float _lastReadValue        = 0.0;        // Needed for all sensors
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors
    
    boolean _sync               = false;      // Used to indicate if the sensor asked for updated values via the sync command
    float _diff = 0.3;  // Needed for all sensors
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;  // Needed for all sensors

  public:
  
    serialData(void) {

    }

    // Alterative constructor
    void begin(String name = "serial", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
//      this->_pin = pin;
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(String name = "serial", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
//      this->_pin = pin;
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("SerialData called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }

    // Sends a request for new data to the subArduinos connected via Serial2
    void sync(void)
    {
      _sync = true;
      Serial2.println("{ \"status\":\"sync\" }");
    } 
    
    void set(float serialValue)
    {
      //if (serialValue isnot NAN) {
        _readingIntervalTimer = millis();
        _sync = false;
        _lastReadValue = serialValue;
        if (serialValue <= _warningValue){
          _currentState = HIGH;
        } else {
          _currentState = LOW;
        }
        if (_debug) {
          Serial.println(_name + ": serialData  set: " + (String) serialValue + " , Warning: " + (String) _currentState);
        }
      //}
    }

    float read(void)
    {
      if (_debug) {
        Serial.println(_name + ": serialData read: " + (String) _lastReadValue + " , Warning: " + (String) _currentState);
      }
      return _lastReadValue;
    }

    // Checks the state
    boolean state(void) {
      return _currentState;
    }

    void check(float diff = 0.1){
      float value = read();
      if ((millis() - _postingIntervalTimer  > _postingIntervalDelay)|| 
       (fabs(value - _lastReportedValue) >= diff ))
      { 
        if (_debug) {
          Serial.println(_name + ": Published value: " + (String) value);
        } 
        mqttJSON[_name ] = value;  // Using the name of this instance, we put the voltage reading in the JSON container that we send via MQTT.
        if (_thingSpeakField != 0) {
          ThingSpeak.setField(_thingSpeakField, value);
        }
        _postingIntervalTimer = millis();
        _lastReportedValue = value;
      }
    }
    
};
