// =============== Motor ============================================================================ 
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

//===============================================================

class WindMeter {
  private:
    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "wind";     // Needed for all sensors
    int _thingSpeakField        = 0;

    boolean _currentState       = LOW;
    float _lastReportedValue    = 0.0;        // Needed for all sensors
    float _lastReadValue        = 0.0;        // Needed for all sensors

    float _diff = 0.3;  // Needed for all sensors
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;  // Needed for all sensors

    unsigned char _WindInstance;
    double _WindSpeed = 0.0; 
    double _WindAngle = 0.0;

  public:
  
    WindMeter(void) {
    }

    // Alterative constructor
    void begin(String name = "WindMeter", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(String name = "WindMeter", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("WindMeter (NMEA), called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }

    void setWindData(unsigned char WindInstance, double WindSpeed, double WindAngle){
      this->_WindInstance   = WindInstance;
      this->_WindSpeed      = WindSpeed;
      this->_WindAngle      = WindAngle;
      if (_debug) {
        Serial.println(_name + ":set Windspeed: " + (String) WindSpeed + " , WindAngle: " + (String) WindAngle);
      }
    }

    double read(void)
    {
      if (_debug) {
        Serial.println(_name + ":red Windspeed: " + (String) _WindSpeed + " , WindAngle: " + (String) _WindAngle);
      }
      return _WindSpeed;
    }

    double getWindSpeed(void)
    {
      if (_debug) {
        Serial.println(_name + ":red Windspeed: " + (String) _WindSpeed);
      }
      return _WindSpeed;
    }

    double getWindDirection(void)
    {
      if (_debug) {
        Serial.println(_name + ":red Winddirection: " + (String) _WindAngle);
      }
      return _WindAngle;
    }

}; // end class WindMeter

//===============================================================
class Navigation {
    private:
    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "navigatior";     // Needed for all sensors
    int _thingSpeakField        = 0;

    boolean _currentState       = LOW;
    float _lastReportedValue    = 0.0;        // Needed for all sensors
    float _lastReadValue        = 0.0;        // Needed for all sensors

    float _diff = 0.3;  // Needed for all sensors
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;  // Needed for all sensors

    unsigned char _WindInstance;
    double _lat = 0.0; 
    double _long = 0.0;
    
// Navigation (position, estimated position, course, speed, SoG, CoG) 

    unsigned char _SID; 
//    tN2kHeadingReference _HeadingReference;  
    double _Heading; 
    double _Deviation;
    double _Variation;
    unsigned long _setTimeHeading;

    double _COG;
    double _SOG;

    unsigned char SID;
    uint16_t _SystemDate;
    double _SystemTime;

    //nsigned char SID;
    uint16_t DaysSince1970;
    double SecondsSinceMidnight; 
    double Latitude;
    double Longitude;
    double Altitude; 
//    tN2kGNSStype GNSStype;
//    tN2kGNSSmethod GNSSmethod;
    unsigned char nSatellites;
    double HDOP;
    double PDOP;
    double GeoidalSeparation;
    unsigned char nReferenceStations;
//    tN2kGNSStype ReferenceStationType;
    uint16_t ReferenceSationID;
    double AgeOfCorrection;
    unsigned long _setTimeGNSS;


  public:
  
    Navigation(void) {
    }

    // Alterative constructor
    void begin(String name = "navigator", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(String name = "navigator", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Navigation (NMEA), called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }
    
    void setHeading(double Heading, double Deviation, double Variation) {
    //void setHeading(unsigned char SID, tN2kHeadingReference HeadingReference, double Heading, double Deviation, double Variation) {
    //  this->_SID              = SID;
    //  this->_HeadingReference = HeadingReference;
      this->_Heading          = Heading;
      this->_Deviation        = Deviation;
      this->_Variation        = Variation;
      _setTimeHeading         = millis();  // save the time for when data is injected as to detect old data or do "deadrecon" if it is missing
    }

    void setPosition(unsigned char WindInstance, double Lat, double Long){
      this->_WindInstance   = WindInstance;
      this->_lat          = Lat;
      this->_long         = Long;
      if (_debug) {
        Serial.println(_name + ":set Position: Lat: " + (String) _lat + " , Long: " + (String) _long);
      }
    }

    double getPosition(void)
    {
      if (_debug) {
        Serial.println(_name + ":get Position: Lat: " + (String) _lat + " , Long: " + (String) _long);
      }
      return _lat;
    }

    void setSystemTime(unsigned char SID, uint16_t SystemDate, double SystemTime){
      this->_SID   = SID;
      this->_SystemDate   = SystemDate;
      this->_SystemTime   = SystemTime;
      if (_debug) {
        Serial.println(_name + ":set SystemDate:" + (String) SystemDate + " , SystemTime: " + (String) SystemTime);
      }
    }

    uint16_t getSystemDate(void){
      if (_debug) {
        Serial.println(_name + ":get SystemDate:" + (String) _SystemDate);
      }
      return _SystemDate;
    }

    double getSystemTime(void){
      if (_debug) {
        Serial.println(_name + ":get SystemTime: " + (String) _SystemTime);
      }
      return _SystemTime;
    }


}; // end class Navigation
  
//===============================================================
class Boat {
    private:
    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "boat";     // Needed for all sensors
    int _thingSpeakField        = 0;

    boolean _currentState       = LOW;
    float _lastReportedValue    = 0.0;        // Needed for all sensors
    float _lastReadValue        = 0.0;        // Needed for all sensors

    float _diff = 0.3;  // Needed for all sensors
    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;  // Needed for all sensors

    unsigned char _WindInstance;
    double _tempSea = 0.0; 
    double _temp = 0.0;


  public:
  
    Boat(void) {
    }

    // Alterative constructor
    void begin(String name = "boat", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(String name = "boat", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Boat (NMEA), called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }

    void setTempSea(unsigned char WindInstance, double tempSea, double temp){
      this->_WindInstance   = WindInstance;
      this->_tempSea        = tempSea;
      this->_temp           = temp;
      if (_debug) {
        Serial.println(_name + ":set tempSea: " + (String) tempSea + " , temp: " + (String) temp);
      }
    }

    double getTempSea(void)
    {
      if (_debug) {
        Serial.println(_name + ":get TempSea: " + (String) _tempSea);
      }
      return _tempSea;
    
    }

}; // end class Boat
