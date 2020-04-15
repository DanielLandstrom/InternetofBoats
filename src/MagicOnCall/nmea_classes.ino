// =============== Motor ============================================================================ 
// Moved into a .h file to be able to include it with a #include "nmea_classes.h"
/*
class Motor {

    private:
    boolean _debug = false; // Needed for all sensors 
    String  _name               = "motor";  // Needed for all sensors
    unsigned long _changetime   = 0; 
    unsigned long _duration     = 0;          // Needed for all sensors
    unsigned long _pastduration = 0;          // Needed for all sensors

    int       _rpm    = 0; 
    float     _temp   = 0.0; 
    boolean _currentState = LOW;
    int _lastReportedValue = 0;// Needed for all sensors 
    int _lastReadValue = 0;   // Needed for all sensors 
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors 

    //float diff = 0.1;  // Needed for all sensors 
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors 
    unsigned long _postingIntervalTimer = 0; // Needed for all sensors 

  public:
    Motor(void) {
    }
    
    // Alterative constructor 
    void begin(String name = "motor", unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts 
    void debug(String name = "motor", unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Motor called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }

    // Set the value of the motor rpm
    void setRPM(int rpm) {
      _rpm = rpm;
      if (_debug) {
        Serial.println("Motor set rpm: " + (String) _rpm + " , State: " + (String) _currentState);
      }
    }

    // Set the value of the motor temp
    void setTemp(float temp) {
      _temp = temp;
      if (_debug) {
        Serial.println("Motor set temp: " + (String) _temp + " , State: " + (String) _currentState);
      }
    }

    // Reads the value of the motor rpm
    int readRPM(void) {
      if (_debug) {
        Serial.println("Motor reading RPM: " + (String) _rpm + " , State: " + (String) _currentState);
      }
      return _rpm;
    }
    
    // Reads the value of the motor temp
    float readTemp(void) {
      if (_debug) {
        Serial.println("Motor reading Temp: " + (String) _temp + " , State: " + (String) _currentState);
      }
      return _temp;
    }

    void check(int diff = 10){
      int rpm = readRPM();
      if ((millis() - _postingIntervalTimer  > _postingIntervalDelay)|| 
         (abs(rpm - _lastReportedValue) >= diff ))
      {
        if (_debug) {
         Serial.println("Published motor: " + (String) rpm + " , _lastReportedValue: " + (String) _lastReportedValue + " , diff: " + (String) diff);
        }
        mqttJSON[ _name ] = rpm;
        _postingIntervalTimer = millis();
        _lastReportedValue = rpm;
      }
    }

}; // end class Motor

*/
