// Led
/*
#include "Arduino.h"

class LED {
  private:
    byte _pin;                                // Needed for all sensors
    boolean _report             = false;      // Needed for all sensors
    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "LED";      // Needed for all sensors
    unsigned long _duration     = 0;          // Needed for all sensors
    unsigned long _pastduration = 0;          // Needed for all sensors
    unsigned long _changetime   = 0;          // Needed for all sensors

    boolean _inverted     = false; 
    boolean _LOW          = LOW; 
    boolean _HIGH         = HIGH; 
    
    boolean _currentState   = LOW;
    int _lastReportedValue  = 0;    // Needed for all sensors
    int _lastReadValue      = 0;   // Needed for all sensors
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors

    int diff = 1;  // Needed for all sensors
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;// Needed for all sensors

    int _periodicity = 1;
    int _longPeriodicity = 2000;
    int _shortPeriodicity = 200;
    boolean _currentPinState = LOW;


  public:
    LED(byte pin = LED_BUILTIN) {
      this->_pin = pin;
      pinMode(pin, OUTPUT);
      if (_pin != 0 ) { digitalWrite(_pin, _LOW); } // does not take inverted into consideration, please fix 
    }

    // Alterative constructor
    void begin(byte pin = LED_BUILTIN, String name = "LED", unsigned long postingIntervalDelay = 27 * 1000, boolean inverted = false) {
  
      this->_pin = pin;
//      this->_report = report;
      this->_name = name;
      this->_postingIntervalDelay = postingIntervalDelay;
      this->_inverted = inverted;
      if (_inverted) {
        _LOW          = HIGH; 
        _HIGH         = LOW; 
      } else {
        _LOW          = LOW; 
        _HIGH         = HIGH; 
      }      
      pinMode(pin, OUTPUT);
      if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
      mqttJSON[_name ] = "off";
      _postingIntervalTimer = millis();
    }

    // Alterative constructor
    void begin(byte pin = LED_BUILTIN, boolean report = false , String name = "LED", unsigned long postingIntervalDelay = 27 * 1000, boolean inverted = false) {
  
      this->_pin = pin;
      this->_report = report;
      this->_name = name;
      this->_postingIntervalDelay = postingIntervalDelay;
      this->_inverted = inverted;
      if (_inverted) {
        _LOW          = HIGH; 
        _HIGH         = LOW; 
      } else {
        _LOW          = LOW; 
        _HIGH         = HIGH; 
      }      
      pinMode(pin, OUTPUT);
      if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
      mqttJSON[_name ] = "off";
      _postingIntervalTimer = millis();
    }

    // Alterative constructor that enables debug printouts
    void debug(byte pin = LED_BUILTIN, String name = "LED", unsigned long postingIntervalDelay = 27 * 1000, boolean inverted = false) {
      this->_pin = pin;
      this->_name = name;
      this->_postingIntervalDelay = postingIntervalDelay;
      this->_inverted = inverted;
      if (_inverted) {
        _LOW          = HIGH; 
        _HIGH         = LOW; 
      } else {
        _LOW          = LOW; 
        _HIGH         = HIGH; 
      }
      pinMode(pin, OUTPUT);
      if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
      _debug = true;
      if (_debug) {
        Serial.println("LED on pin: " + (String) _pin + " , _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }      
      mqttJSON[_name ] = "off";
      _postingIntervalTimer = millis();
    }
    
    // Alterative constructor that enables debug printouts
    void debug(byte pin = LED_BUILTIN, boolean report = false , String name = "LED", unsigned long postingIntervalDelay = 27 * 1000, boolean inverted = false) {
  
      this->_pin = pin;
      this->_report = report;
      this->_name = name;
      this->_postingIntervalDelay = postingIntervalDelay;
      this->_inverted = inverted;
      if (_inverted) {
        _LOW          = HIGH; 
        _HIGH         = LOW; 
      } else {
        _LOW          = LOW; 
        _HIGH         = HIGH; 
      }      
      pinMode(pin, OUTPUT);
      if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
      _debug = true;
      if (_debug) {
        Serial.println("LED on pin: " + (String) _pin + " , _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
      mqttJSON[_name ] = "off";
      _postingIntervalTimer = millis();
    }

    void on()
    {
      if (_currentState == LOW ) 
      {
        //mqttJSON[_name ] = 1; 
        mqttJSON[_name ] = "on";
        _postingIntervalTimer = millis();
        _lastReportedValue = 1;
        if (_report) { reportJSON[_name] = "on"; }
      }; 
      if (_pin != 0 ) { digitalWrite(_pin, _HIGH); }
      if (_debug) {Serial.println("LED on pin: " + (String) _pin + " is: On");}
      _currentState = HIGH;
    }

    void off()
    {
      if (_currentState == HIGH ) 
      {
        //mqttJSON[_name ] = 0;  
        mqttJSON[_name ] = "off";
        _postingIntervalTimer = millis();
        _lastReportedValue = 0;
        if (_report) { reportJSON[_name] = "off"; }
      }; 
      if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
      if (_debug) {Serial.println("LED on pin: " + (String) _pin + " is: Off");}
      _currentState = LOW;
    }

    void flash()
    {
      _periodicity = 1000;
      if (_currentState == LOW ) 
      {
        //mqttJSON[_name ] = 1;  
        mqttJSON[_name ] = "on";
        _postingIntervalTimer = millis();
        _lastReportedValue = 1;
        if (_report) { reportJSON[_name] = "flash"; }
      }; 
      if (_pin != 0 ) { digitalWrite(_pin, _HIGH); }
      if (_debug) {Serial.println("LED on pin: " + (String) _pin + " is: Flashing");}
      _currentState = HIGH;
    }

    void quickflash()
    {
      _periodicity = 500;
      if (_currentState == LOW ) 
      {
        //mqttJSON[_name ] = 1; 
        mqttJSON[_name ] = "on"; 
        _postingIntervalTimer = millis();
        _lastReportedValue = 1;
        if (_report) { reportJSON[_name] = "quickflash"; }
      }; 
      if (_pin != 0 ) { digitalWrite(_pin, _HIGH); }
      if (_debug) {Serial.println("LED on pin: " + (String) _pin + " is: Quick Flashing");}
      _currentState = HIGH;
    }

    void slowflash()
    {
      _periodicity = 10000;
      if (_currentState == LOW ) 
      {
        //mqttJSON[_name ] = 1;
        mqttJSON[_name ] = "on";
        _postingIntervalTimer = millis();
        _lastReportedValue = 1;
        if (_report) { reportJSON[_name] = "slowflash"; }
      }; 
      if (_pin != 0 ) { digitalWrite(_pin, _HIGH); }
      if (_debug) {Serial.println("LED on pin: " + (String) _pin + " is: Slow Flashing");}
      _currentState = HIGH;
    }

    void setCommand(String message)
    {
      // needs to be written
    } 

    int check(float diff = 0.2) {
      if ((millis() - _postingIntervalTimer  > _postingIntervalDelay)) {
        if (_debug) {Serial.println(_name + " : reported (in check) via mqtt as postingintervall was reached");}
        if (_currentState == HIGH ) {
          mqttJSON[_name ] = "on";
        } else {
          mqttJSON[_name ] = "off";
        }
        _postingIntervalTimer = millis();
      }

      if (diff < 0.1) {  // report status over MQTT when sync-flag sets diff to zero
        if (_debug) {Serial.println(_name + " : reported (in check) via mqtt as sync flag was set");}
        if (_currentState == HIGH ) {
          mqttJSON[_name ] = "on";
        } else {
          mqttJSON[_name ] = "off";
        }
        _postingIntervalTimer = millis();
      }
      if (_currentState == HIGH ) 
      {
//        if ((millis() % _periodicity - _periodicity/2) < _periodicity/2 ) // Change to > _periodicity
        if ((millis() % _periodicity - _periodicity/2) > _periodicity ) 
        { 
          if (_pin != 0 ) { digitalWrite(_pin, _HIGH); }
        } else {
          if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
        }
      }
      else
      {
        if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
      }
    }


    int check2(float diff = 0.2) {
      if ((millis() - _postingIntervalTimer  > _postingIntervalDelay)) {
        if (_debug) {Serial.println(_name + " : reported (in check2) via mqtt as postingintervall was reached");}
        if (_currentState == HIGH ) {
          mqttJSON[_name ] = "on";
        } else {
          mqttJSON[_name ] = "off";
        }
        _postingIntervalTimer = millis();
      }

      if (diff < 0.1) {  // report status over MQTT when sync-flag sets diff to zero
        if (_debug) {Serial.println(_name + " : reported (in check2) via mqtt as sync flag was set");}
        if (_currentState == HIGH ) {
          mqttJSON[_name ] = "on";
        } else {
          mqttJSON[_name ] = "off";
        }
        _postingIntervalTimer = millis();
      }
      if (_currentState == HIGH ) 
      {
        unsigned long m = millis();
        if  (((m % _longPeriodicity - _longPeriodicity/2) > _longPeriodicity) && ((m % _shortPeriodicity - _shortPeriodicity/2) > _shortPeriodicity)) {
          if (_currentPinState == LOW) {
            if (_pin != 0 ) { digitalWrite(_pin, _HIGH); }
            _pastduration = _duration; 
            _duration = m - _changetime; 
            //Serial.println("LOW : " + (String) _duration); 
            if (_debug) { Serial.println("LED on pin: " + (String) _pin + " , called: " + _name + " : now HIGH : Previous state: " + (String) _duration + " ms"); }
            _changetime = m;
            _currentPinState = HIGH;
          }
        } else {
          if (_currentPinState == HIGH) {
            if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
            _pastduration = _duration; 
            _duration = m - _changetime; 
            //Serial.println("HIGH : " + (String) duration); 
            if (_debug) { Serial.println("LED on pin: " + (String) _pin + " , called: " + _name + " : now LOW : Previous state: " + (String) _duration + " ms"); }
            _changetime = m;
            _currentPinState = LOW;
          }
        }

      } 
      else 
      {
        if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
      }
    }

    int checkBin(float diff = 0.2) {
      if ((millis() - _postingIntervalTimer  > _postingIntervalDelay)) {
        if (_debug) {Serial.println(_name + " : reported (in checkBin) via mqtt as postingintervall was reached");}
        if (_currentState == HIGH ) {
          mqttJSON[_name ] = "on";
        } else {
          mqttJSON[_name ] = "off";
        }
        _postingIntervalTimer = millis();
      }
      if (diff < 0.1) {  // report status over MQTT when sync-flag sets diff to zero
        if (_debug) {Serial.println(_name + " : reported (in checkBin) via mqtt as sync flag was set");}
        if (_currentState == HIGH ) {
          mqttJSON[_name ] = "on";
        } else {
          mqttJSON[_name ] = "off";
        }
        _postingIntervalTimer = millis();
      }  
      unsigned long m = millis();
      if (_currentState == HIGH ) 
      {
          if (_currentPinState == LOW) {
            if (_pin != 0 ) { digitalWrite(_pin, _HIGH); }
            _pastduration = _duration; 
            _duration = m - _changetime;  
            if (_debug) { Serial.println("BinaryOut on pin: " + (String) _pin + " , called: " + _name + " : now HIGH : Previous state: " + (String) _duration + " ms"); }
            _changetime = m;
            _currentPinState = HIGH;
          }
        } else {
          if (_currentPinState == HIGH) {
            if (_pin != 0 ) { digitalWrite(_pin, _LOW); }
            _pastduration = _duration; 
            _duration = m - _changetime; 
            if (_debug) { Serial.println("BinaryOut on pin: " + (String) _pin + " , called: " + _name + " : now LOW : Previous state: " + (String) _duration + " ms"); }
            _changetime = m;
            _currentPinState = LOW;
          }
        }
      } 


    boolean state() {
      if (_debug) {
        //Serial.println("LED on pin: " + (String) _pin + " is: " + (String) _currentState);
      }
      return _currentState; 
    }


};

LED lantern;
LED decklight;
LED fan;
LED outlet;
LED onboardLED;
LED blueLED;
LED greenLED;
LED redLED;

LED tableUp;
LED tableDown;

*/
