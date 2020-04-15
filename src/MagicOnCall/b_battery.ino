// Battery monitor
// LM4040 TO-92 Spänningsreferens 4.096V 0.1%
// 24.00 kr
// http://www.skillbank.co.uk/arduino/measure.htm
// https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference/
// https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/adc.html

#include "Arduino.h"

class Battery {
  
  private:
    byte _pin;                                // Needed for all sensors
    boolean _report             = false;      // Needed for all sensors
    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "battery";  // Needed for all sensors
    int _thingSpeakField        = 0;
    unsigned long _duration     = 0;          // Needed for all sensors
    unsigned long _pastduration = 0;          // Needed for all sensors
    unsigned long _changetime   = 0;          // Needed for all sensors
    
    float _warningVoltage       = 12.7;
    int _threshold              = 30; 

    boolean _currentState       = LOW;
    float _lastReportedValue    = 0.0;        // Needed for all sensors
    float _lastReadValue        = 0.0;        // Needed for all sensors
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors

    float _diff = 0.3;  // Needed for all sensors
    boolean _sync               = false;      // Used to indicate if the sensor asked for updated values via the sync command
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;  // Needed for all sensors
    unsigned long _reportingIntervalTimer = 5000;
    unsigned long _reportingIntervalDelay = 0;

  public:
  
    Battery(byte pin = 32) {
      this->_pin = pin;
    }

    // Alterative constructor
    void begin(byte pin = 32, String name = "battery", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(byte pin = 32, String name = "battery", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Battery on pin: " + (String) _pin + " , called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }
    
    // Alterative constructor
    void begin(byte pin = 32, boolean report = false, String name = "battery", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      this->_report = report;
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(byte pin = 32, boolean report = false, String name = "battery", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_pin = pin;
      this->_report = report;
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Battery on pin: " + (String) _pin + " , called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay + " and _reportingIntervalDelay: " + (String) _reportingIntervalDelay);
      }
    }

    void set(float serialValue)
    {
      //if (serialValue isnot NAN) {
        _readingIntervalTimer = millis();
        _sync = false;
        _lastReadValue = serialValue;
        if (serialValue <= _warningVoltage){
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
      if ((millis()- _readingIntervalTimer < 1000) || (_pin == 0)) // A 100 is a bit high I think
      {
        return _lastReadValue;
      }
      else
      {
        //analogSetPinAttenuation(_pin, ADC_0db);
        //analogSetPinAttenuation(_pin, ADC_11db);
        int analogReading = analogRead(_pin);
        if (_debug) {Serial.println(_name + ": Analog reading on " + (String) _pin + " was: " + (String) analogReading); }
        //float voltage = 10000.0/(10000.0+47000.0)*(float)analogReading/4096.0*3.3;
        //float voltage = ((float)analogReading/4096.0*3.3)/(10000.0/(10000.0+47000.0));
        //float voltage = ((float)analogReading/4096.0*3.3)/(120000.0/(120000.0+430000.0));
        float voltage = ((float)analogReading/4096.0*3.3)/(1000.0/(1000.0+1000.0))+11.062;
        _readingIntervalTimer = millis();
        _lastReadValue = voltage;
        if (voltage <= _warningVoltage){
          _currentState = HIGH;
        } else {
          _currentState = LOW;
        }
        if (_debug) {
          Serial.println(_name + ": Voltage: " + (String) voltage + " , Warning: " + (String) _currentState);
        }
        return voltage;
      }
    }

    // Checks the state of the touch pin
    boolean state(void) {
      if (millis()- _readingIntervalTimer < 1000)
      {
        return _currentState;
      }
      else
      {
        read();
        return _currentState;
      }
    }

    void check(float diff = 0.1){

      float voltage = read();
      if ((millis() - _postingIntervalTimer  > _postingIntervalDelay)|| 
       (fabs(voltage - _lastReportedValue) >= diff ))
      { 
        if (_debug) {
          Serial.println(_name + ": Published voltage: " + (String) voltage);
        } 
        mqttJSON[_name ] = voltage;  // Using the name of this instance, we put the voltage reading in the JSON container that we send via MQTT.
        if (_thingSpeakField != 0) {
          ThingSpeak.setField(_thingSpeakField, voltage);
        }
        _postingIntervalTimer = millis();
        _lastReportedValue = voltage;
      }
      if ((millis() - _reportingIntervalTimer  > _reportingIntervalDelay) && (_report)) 
      { 
        reportJSON[_name ] = voltage;  // Using the name of this instance, we put the voltage reading in the JSON container that we send via serial.
        _reportingIntervalTimer = millis();
      }

    }
};
