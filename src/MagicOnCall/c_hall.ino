// HALL_sensor
class Hall {
  private:
    byte _pin;  // Needed for all sensors 
    boolean _debug = false; // Needed for all sensors 
    String  _name               = "hall";  // Needed for all sensors
    unsigned long _duration     = 0;          // Needed for all sensors
    unsigned long _pastduration = 0;          // Needed for all sensors

    int _threshold = 30; 
    boolean _currentState = LOW;
    int _lastReportedValue = 0;// Needed for all sensors 
    int _lastReadValue = 0;   // Needed for all sensors 
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors 

    int diff = 20;  // Needed for all sensors 
    unsigned long _postingIntervalDelay = 27000; //Read and post the temperature every second second.  // Needed for all sensors 
    unsigned long _postingIntervalTimer = 0;// Needed for all sensors 

  public:
    Hall(byte pin = T8, unsigned long postingIntervalDelay = 27000) {
      this->_pin = pin;
      this->_postingIntervalDelay = postingIntervalDelay;
    }
    
    // Alterative constructor 
    void begin(byte pin = T8, unsigned long postingIntervalDelay = 27000) {
      this->_pin = pin;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts 
    void debug(byte pin = T8, unsigned long postingIntervalDelay = 27000) {
      this->_pin = pin;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("HallSensor on pin: " + (String) _pin + " , _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }

    }
    
    // Reads the value of the touch pin
    int read(void) {
      int hallreading;
      if (millis() - _readingIntervalTimer < 100) // A 100 is a bit high I think
      {
        return _lastReadValue;
      }
      else
      {
        hallreading = hallRead();
        _readingIntervalTimer = millis();
        _lastReadValue = hallreading;
        if (hallreading <= _threshold){
          _currentState = HIGH;
        } else {
          _currentState = LOW;
        }
        if (_debug) {
          Serial.println("Hall reading: " + (String) hallreading );
        }
        return hallreading;
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

    void check(int diff = 20){
      int hallreading = read();
      if ((millis() - _postingIntervalTimer  > _postingIntervalDelay)|| 
       (abs(hallreading - _lastReportedValue) >= diff ))
      {
        if (_debug) {
          Serial.println("Published hallreading: " + (String) hallreading + " , _lastReportedValue: " + (String) _lastReportedValue + " , diff: " + (String) diff);
        }
        mqttJSON[_name] = hallreading;
        _postingIntervalTimer = millis();
        _lastReportedValue = hallreading;
      }
    }


    // A function that test the sensor, proves that you code works, and illustrates how the sensor works.
    void test(void){
      Serial.println("The internal hall sensor needs a better test function and is not connected on pin: " + (String) _pin );
    }

};
 
