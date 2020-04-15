// TOUCH_sensor

// ToDO
// report state to mqtt rather than value
// add support for name
// add support for duration -> longtouch, superlongtouch, 

// Functions
/*
void    begin(byte pin = T8, String name = "touch", unsigned long postingIntervalDelay = 27 * 1000);
void    debug(byte pin = T8, String name = "touch", unsigned long postingIntervalDelay = 27 * 1000);
int     read(void);
boolean state(void);
void    check(int diff = 10)
void    test(void); 
// Not yet implemented 
int     duration(void);
boolean isTouched(void); // redundant, use state instead? 
boolean isLongTouched(); 
 
*/
 
class Touch {
  private:
    byte _pin;  // Needed for all sensors 
    boolean _debug = false; // Needed for all sensors 
    String  _name               = "touch";  // Needed for all sensors
    unsigned long _changetime   = 0; 
    unsigned long _duration     = 0;          // Needed for all sensors
    unsigned long _pastduration = 0;          // Needed for all sensors

    int _threshold = 20; 
    boolean _currentState = LOW;
    int _lastReportedValue = 0;// Needed for all sensors 
    int _lastReadValue = 0;   // Needed for all sensors 
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors 

    //float diff = 0.1;  // Needed for all sensors 
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors 
    unsigned long _postingIntervalTimer = 0; // Needed for all sensors 

  public:
    Touch(byte pin = T0) {
      this->_pin = pin;
    }
    
    // Alterative constructor 
    void begin(byte pin = T0, String name = "touch", unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      this->_name = name;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts 
    void debug(byte pin = T0, String name = "touch", unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      this->_name = name;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Touch on pin: " + (String) _pin + " , called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }
    
    // Reads the value of the touch pin
    int read(void) {
      int touchme;
      if (millis() - _readingIntervalTimer < 100) // A 100 is a bit high I think
      {
        return _lastReadValue;
      }
      else
      {
        touchme = touchRead(_pin);
        _readingIntervalTimer = millis();
        _lastReadValue = touchme;
        if (touchme <= _threshold){
          _currentState = HIGH;
        } else {
          _currentState = LOW;
        }
        if (_debug) {
          Serial.println("Touch reading: " + (String) touchme + " , State: " + (String) _currentState);
        }
        return touchme;
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
      int touchme = read();
      if ((millis() - _postingIntervalTimer  > _postingIntervalDelay)|| 
       (abs(touchme - _lastReportedValue) >= diff ))
      {
        if (_debug) {
         Serial.println("Published touch: " + (String) touchme + " , _lastReportedValue: " + (String) _lastReportedValue + " , diff: " + (String) diff);
        }
        mqttJSON[ _name ] = touchme;
        _postingIntervalTimer = millis();
        _lastReportedValue = touchme;
      }
    }


    // A function that test the sensor, proves that you code works, and illustrates how the sensor works.
    void test(void){
      Serial.println("The touch sensor is connected on pin: " + (String) _pin );

/*
      Serial.println(touchRead(4));   // get value of Touch 0 pin = GPIO  4
      Serial.println(touchRead(2));   // get value of Touch 2 pin = GPIO  2
      Serial.println(touchRead(15));  // get value of Touch 3 pin = GPIO 15
      Serial.println(touchRead(13));  // get value of Touch 4 pin = GPIO 13
      Serial.println(touchRead(12));  // get value of Touch 5 pin = GPIO 12
      Serial.println(touchRead(14));  // get value of Touch 6 pin = GPIO 14
      Serial.println(touchRead(27));  // get value of Touch 7 pin = GPIO 27
      Serial.println(touchRead(33));  // get value of Touch 8 pin = GPIO 33
      Serial.println(touchRead(32));  // get value of Touch 9 pin = GPIO 32
      Serial.println("----  Tested all touch");  
*/
    }

};
 
