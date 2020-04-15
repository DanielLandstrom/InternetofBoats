// The classes and the naming are based on the 1.4.0 specification of SignalK
// https://signalk.org/specification/1.4.0/doc/vesselsBranch.html

/*
 * 
inline bool N2kIsNA(double v) { return v==N2kDoubleNA; }
inline bool N2kIsNA(uint8_t v) { return v==N2kUInt8NA; }
inline bool N2kIsNA(int8_t v) { return v==N2kInt8NA; }
inline bool N2kIsNA(uint16_t v) { return v==N2kUInt16NA; }
inline bool N2kIsNA(int16_t v) { return v==N2kInt16NA; }
inline bool N2kIsNA(uint32_t v) { return v==N2kUInt32NA; }
inline bool N2kIsNA(int32_t v) { return v==N2kInt32NA; }

 
inline double RadToDeg(double v) { return N2kIsNA(v)?v:v*180.0/3.1415926535897932384626433832795; }
inline double DegToRad(double v) { return N2kIsNA(v)?v:v/180.0*3.1415926535897932384626433832795; }
inline double CToKelvin(double v) { return N2kIsNA(v)?v:v+273.15; }
inline double KelvinToC(double v) { return N2kIsNA(v)?v:v-273.15; }
inline double FToKelvin(double v) { return N2kIsNA(v)?v:(v-32)*5.0/9.0+273.15; }
inline double KelvinToF(double v) { return N2kIsNA(v)?v:(v-273.15)*9.0/5.0+32; }
inline double mBarToPascal(double v) { return N2kIsNA(v)?v:v*100; }
inline double PascalTomBar(double v) { return N2kIsNA(v)?v:v/100; }
inline double hPAToPascal(double v) { return N2kIsNA(v)?v:v*100; }
inline double PascalTohPA(double v) { return N2kIsNA(v)?v:v/100; }
inline double AhToCoulomb(double v) { return N2kIsNA(v)?v:v*3600; }
inline double CoulombToAh(double v) { return N2kIsNA(v)?v:v/3600; }
inline double hToSeconds(double v) { return N2kIsNA(v)?v:v*3600; }
inline double SecondsToh(double v) { return N2kIsNA(v)?v:v/3600; }
inline double msToKnots(double v) { return N2kIsNA(v)?v:v*3600/1852.0; }

*/
/*
enum tN2000KFluidType {
                            N2kft_Fuel=0,
                            N2kft_Water=1,
                            N2kft_GrayWater=2,
                            N2kft_LiveWell=3,
                            N2kft_Oil=4,
                            N2kft_BlackWater=5,
                            N2kft_FuelGasoline=6,
                            N2kft_Error=14,
                            N2kft_Unavailable=15
                          };
*/

struct positions{
  double longitude;
  double latitude;
  double altitude;
};
//typedef struct positions Position;

/*
typedef struct positions {
  double longitude;
  double latitude;
  double altitude;
} Position;
*/
struct positions here;
struct positions daniel = {1.2, 3.4, 5.6};
//daniel.longitude = 12.345;

/* Environment
/vessels/<RegExp>/environment/outside/temperature
/vessels/<RegExp>/environment/outside/dewPointTemperature
/vessels/<RegExp>/environment/outside/apparentWindChillTemperature
/vessels/<RegExp>/environment/outside/theoreticalWindChillTemperature
/vessels/<RegExp>/environment/outside/heatIndexTemperature
/vessels/<RegExp>/environment/outside/pressure
/vessels/<RegExp>/environment/outside/humidity
/vessels/<RegExp>/environment/outside/airDensity
/vessels/<RegExp>/environment/outside/illuminance
/vessels/<RegExp>/environment/inside
/vessels/<RegExp>/environment/inside/heatIndexTemperature
/vessels/<RegExp>/environment/inside/pressure
/vessels/<RegExp>/environment/inside/relativeHumidity
/vessels/<RegExp>/environment/inside/dewPoint
/vessels/<RegExp>/environment/inside/airDensity
/vessels/<RegExp>/environment/inside/illuminance
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/temperature
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/heatIndexTemperature
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/pressure
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/relativeHumidity
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/dewPoint
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/airDensity
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/illuminance
/vessels/<RegExp>/environment/water
/vessels/<RegExp>/environment/water/temperature
/vessels/<RegExp>/environment/water/salinity
/vessels/<RegExp>/environment/depth
/vessels/<RegExp>/environment/depth/belowKeel
/vessels/<RegExp>/environment/depth/belowTransducer
/vessels/<RegExp>/environment/depth/belowSurface
/vessels/<RegExp>/environment/depth/transducerToKeel
/vessels/<RegExp>/environment/depth/surfaceToTransducer
/vessels/<RegExp>/environment/current
drift (m/s)
setTrue (rad)
setMagnetic (rad)
/vessels/<RegExp>/environment/tide
/vessels/<RegExp>/environment/tide/heightHigh
/vessels/<RegExp>/environment/tide/heightNow
/vessels/<RegExp>/environment/tide/heightLow
/vessels/<RegExp>/environment/tide/timeLow
/vessels/<RegExp>/environment/tide/timeHigh
/vessels/<RegExp>/environment/heave
/vessels/<RegExp>/environment/wind
/vessels/<RegExp>/environment/wind/angleApparent
/vessels/<RegExp>/environment/wind/angleTrueGround
/vessels/<RegExp>/environment/wind/angleTrueWater
/vessels/<RegExp>/environment/wind/directionChangeAlarm
/vessels/<RegExp>/environment/wind/directionTrue
/vessels/<RegExp>/environment/wind/directionMagnetic
/vessels/<RegExp>/environment/wind/speedTrue
/vessels/<RegExp>/environment/wind/speedOverGround
/vessels/<RegExp>/environment/wind/speedApparent
/vessels/<RegExp>/environment/time
/vessels/<RegExp>/environment/mode
*/

/*
NMEAenvironment.getOutsideTemperature
NMEAenvironment.getOutsideDewPointTemperature
NMEAenvironment.getOutsideApparentWindChillTemperature
NMEAenvironment.getOutsideTheoreticalWindChillTemperature
NMEAenvironment.getOutsideHeatIndexTemperature
NMEAenvironment.getOutsidePressure
NMEAenvironment.getOutsideHumidity
NMEAenvironment.getOutsideAirDensity
NMEAenvironment.getOutsideIlluminance

NMEAenvironment.getInsideHeatIndexTemperature
NMEAenvironment.getInsidePressure
NMEAenvironment.getInsideRelativeHumidity
NMEAenvironment.getInsideDewPoint
NMEAenvironment.getInsideAirDensity
NMEAenvironment.getInsideIlluminance

/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/temperature
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/heatIndexTemperature
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/pressure
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/relativeHumidity
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/dewPoint
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/airDensity
/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/illuminance

NMEAenvironment.getWaterTemperature
NMEAenvironment.getWaterSalinity
NMEAenvironment.getDepth
NMEAenvironment.getDepthBelowKeel
NMEAenvironment.getDepthBelowTransducer
NMEAenvironment.getDepthBelowSurface
NMEAenvironment.getDepthTransducerToKeel
NMEAenvironment.getDepthSurfaceToTransducer
NMEAenvironment.getCurrent
drift (m/s)
setTrue (rad)
setMagnetic (rad)
NMEAenvironment.getTide
NMEAenvironment.getTideHeightHigh
NMEAenvironment.getTideHeightNow
NMEAenvironment.getTideHeightLow
NMEAenvironment.getTideTimeLow
NMEAenvironment.getTideTimeHigh
NMEAenvironment.getHeave
NMEAenvironment.setWindAngleApparent(double)
NMEAenvironment.getWindAngleApparent
NMEAenvironment.getWindAngleTrueGround
NMEAenvironment.getWindAngleTrueWater
NMEAenvironment.getWindDirectionChangeAlarm
NMEAenvironment.getWindDirectionTrue
NMEAenvironment.getWindDirectionMagnetic
NMEAenvironment.getWindSpeedTrue
NMEAenvironment.getWindSpeedOverGround
NMEAenvironment.getWindSpeedApparent
NMEAenvironment.getTime
NMEAenvironment.getMode
*/

class NMEAenvironment {
  
  private:
    // General varables
    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "serial";   // Needed for all sensors
    int _thingSpeakField        = 0;
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

    // SignalK varables 
    double _OutsideTemperature                      = 0.0;
    double _OutsideDewPointTemperature              = 0.0;
    double _OutsideApparentWindChillTemperature     = 0.0;
    double _OutsideTheoreticalWindChillTemperature  = 0.0;
    double _OutsideHeatIndexTemperature             = 0.0;
    double _OutsidePressure                         = 0.0;
    double _OutsideHumidity                         = 0.0;
    double _OutsideAirDensity                       = 0.0;
    double _OutsideIlluminance                      = 0.0;
    double _InsideTemperature                       = 0.0;
    double _InsideHeatIndexTemperature              = 0.0;
    double _InsidePressure                          = 0.0;
    double _InsideRelativeHumidity                  = 0.0;
    double _InsideDewPoint                          = 0.0;
    double _InsideAirDensity                        = 0.0;
    double _InsideIlluminance                       = 0.0;
    /*
    /vessels/<RegExp>/environment/inside/[A-Za-z0-9]+
    /vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/temperature
    /vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/heatIndexTemperature
    /vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/pressure
    /vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/relativeHumidity
    /vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/dewPoint
    /vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/airDensity
    /vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/illuminance
    */
    double _WaterTemperature                        = 0.0;
    double _WaterSalinity                           = 0.0;
    double _Depth                                   = 0.0;
    unsigned char _SID;
    double _Offset                                  = 0.0;
    double _DepthBelowKeel                          = 0.0;
    double _DepthBelowTransducer                    = 0.0;
    double _DepthBelowSurface                       = 0.0;
    double _DepthTransducerToKeel                   = 0.0;
    double _DepthSurfaceToTransducer                = 0.0;
    double _Current                                 = 0.0;
    double _CurrentDrift                            = 0.0;
    double _CurrentSetTrue                          = 0.0;
    double _CurrentSetMagnetic                      = 0.0;
    double _TideHeightHigh                          = 0.0;
    double _TideHeightNow                           = 0.0;
    double _TideHeightLow                           = 0.0;
    double _TideTimeLow                             = 0.0;
    double _TideTimeHigh                            = 0.0;
    double _Heave                                   = 0.0;
    double _WindAngleApparent                       = 0.0;
    double _WindAngleTrueGround                     = 0.0;
    double _WindAngleTrueWater                      = 0.0;
    double _WindDirectionChangeAlarm                = 0.0;
    double _WindDirectionTrue                       = 0.0;
    double _WindDirectionMagnetic                   = 0.0;
    double _WindSpeedTrue                           = 0.0;
    double _WindSpeedOverGround                     = 0.0;
    double _WindSpeedApparent                       = 0.0;
    unsigned char _WindInstance;
    
    unsigned long _Time                             = 0;
    String  _Mode                                   = "unkown";

    //const int numReadings = 10;
    //int readIndex = 0;              // the index of the current reading
    //int readings[numReadings];      // the readings from the analog input
    //int total = 0;                  // the running total
    //int average = 0;                // the average

    const int numReadings = 10;
    int readIndex = 0;                  // the index of the current reading
    double xReadings[10];      // the readings in the X-dir
    double xTotal = 0;                  // the running total in the X-dir
    double xAverage = 0;                // the average in the X-dir
    double yReadings[10];      // the readings in the Y-dir
    double yTotal = 0;                  // the running total in the Y-dir
    double yAverage = 0;                // the average in the Y-dir


  public:
  
    NMEAenvironment(void) {
    }

    // Alterative constructor
    void begin(String name = "environment", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;

      // initialize all the readings to 0:
      for (int thisReading = 0; thisReading < numReadings; thisReading++) {
        xReadings[thisReading] = 0.0;
        yReadings[thisReading] = 0.0;
      }
    }

    // Alterative constructor that enables debug printouts
    void debug(String name = "environment", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("NMEAenvironment called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }

    // Sends a request for new data to the subArduinos connected via Serial2
    void sync(void)
    {
      _sync = true;
      //Serial2.println("{ \"status\":\"sync\" }");
    } 

    void check(float diff = 0.1){ 
      /*
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
    */  
    }
    
/*    void setCurrentLevel(double currentLevel)
    {
      //if (serialValue isnot NAN) {
        _readingIntervalTimer = millis();
        _sync = false;
        _lastReadValue = currentLevel;
        if (currentLevel <= _warningValue){
          _currentState = HIGH;
        } else {
          _currentState = LOW;
        }
        if (_debug) {
          Serial.println(_name + ": serialData  set: " + (String) currentLevel + " , Warning: " + (String) _currentState);
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
*/
    double getOutsideTemperature(void) {return _OutsideTemperature; }
    double getOutsideDewPointTemperature(void) {return _OutsideDewPointTemperature; }
    double getOutsideApparentWindChillTemperature(void) {return _OutsideApparentWindChillTemperature; }
    double getOutsideTheoreticalWindChillTemperature(void) {return _OutsideTheoreticalWindChillTemperature; }
    double getOutsideHeatIndexTemperature(void) {return _OutsideHeatIndexTemperature; }
    double getOutsidePressure(void) {return _OutsidePressure; }
    double getOutsideHumidity(void) {return _OutsideHumidity; }
    double getOutsideAirDensity(void) {return _OutsideAirDensity; }
    double getOutsideIlluminance(void) {return _OutsideIlluminance; }
    double getInsideTemperature(void) {return _InsideTemperature; }
    double getInsideHeatIndexTemperature(void) {return _InsideHeatIndexTemperature; }
    double getInsidePressure(void) {return _InsidePressure; }
    double getInsideRelativeHumidity(void) {return _InsideRelativeHumidity; }
    double getInsideDewPoint(void) {return _InsideDewPoint; }
    double getInsideAirDensity(void) {return _InsideAirDensity; }
    double getInsideIlluminance(void) {return _InsideIlluminance; }

    double getWaterTemperature(void) {return _WaterTemperature; }
    double getWaterSalinity(void) {return _WaterSalinity; }
    void   setDepthData(unsigned char SID, double DepthBelowTransducer, double Offset) {
    
      // 1. Remove any incorrect data (outliers, incorrcetly decoded messages) 

      // 2. Average the data as to improve the accuracy and stabilize the information 

      // 3. Store the data in the class internal variables 
//      this->_SID                    = SID;
      this->_DepthBelowTransducer   = DepthBelowTransducer;
      this->_Offset                 = Offset;
      if (_debug) {
        Serial.println(_name + ":set DepthBelowTransducer: " + (String) DepthBelowTransducer + " , Offset: " + (String) Offset);
      }
    }
//    double getDepth(void) {return _Depth; }
//    double getDepthBelowKeel(void) {return _DepthBelowKeel; }
    double getDepthBelowTransducer(void) {return _DepthBelowTransducer; }
    double getDepthBelowSurface(void) {
      double DepthBelowSurface = _DepthBelowTransducer + _Offset;
      return DepthBelowSurface;
    }
//    double getDepthTransducerToKeel(void) {return _DepthTransducerToKeel; }
//    double getDepthSurfaceToTransducer(void) {return _DepthSurfaceToTransducer; }
    
    double getCurrent(void) {return _Current; }
    double getCurrentDrift(void) {return _CurrentDrift; }
    double getCurrentsetTrue(void) {return _CurrentSetTrue; }
    double getCurrentsetMagnetic(void) {return _CurrentSetMagnetic; }
    
    double getTideHeightHigh(void) {return _TideHeightHigh; }
    double getTideHeightNow(void) {return _TideHeightNow; }
    double getTideHeightLow(void) {return _TideHeightLow; }
    double getTideTimeLow(void) {return _TideTimeLow; }
    double getTideTimeHigh(void) {return _TideTimeHigh; }
    double getHeave(void) {return _Heave; }
        
    void setWindData(unsigned char WindInstance, double WindSpeedApparent, double WindAngleApparent){

      // 1. Remove any incorrect data (outliers, incorrcetly decoded messages) 

      // 2. Average the data as to improve the accuracy and stabilize the information 
        // subtract the last reading:
        xTotal = xTotal - xReadings[readIndex];
        yTotal = yTotal - yReadings[readIndex];
        // read from the sensor:
        xReadings[readIndex] = WindSpeedApparent*cos(WindAngleApparent/180.0*3.1415926535897932384626433832795);
        yReadings[readIndex] = WindSpeedApparent*sin(WindAngleApparent/180.0*3.1415926535897932384626433832795);
        // add the reading to the total:
        xTotal = xTotal + xReadings[readIndex];
        yTotal = yTotal + yReadings[readIndex];
        // advance to the next position in the array:
        readIndex = readIndex + 1;
      
        // if we're at the end of the array...
        if (readIndex >= numReadings) {
          // ...wrap around to the beginning:
          readIndex = 0;
        }
      
        // calculate the average:
        xAverage = xTotal / numReadings;
        yAverage = yTotal / numReadings;
      
        // Transform to polar coordinates 
        _WindSpeedApparent = sqrt(xAverage*xAverage + yAverage*yAverage);
        _WindAngleApparent = atan2(yAverage,xAverage)*180.0/3.1415926535897932384626433832795;
      // 3. Store the data in the class internal variables 
        //this->_WindInstance           = WindInstance;
        _WindSpeedApparent      = WindSpeedApparent;  // UnAveraged, to compare with for pipecleaning
        //this->_WindSpeedApparent      = sqrt(xAverage*xAverage + yAverage*yAverage);
        _WindAngleApparent      = WindAngleApparent;  // UnAveraged, to compare with for pipecleaning
        //this->_WindAngleApparent      = atan2(yAverage,xAverage)*180.0/3.1415926535897932384626433832795;
        //this->_WindAngleApparent      = (360.0 + atan2(yAverage,xAverage)*180.0/3.1415926535897932384626433832795) / 360.0;
        // this->_WindAngleApparent      = (360 + atan2(yAverage,xAverage)*180.0/3.1415926535897932384626433832795) % 360;
      if (_debug) {
        Serial.println(_name + ":set Windspeed: " + (String) _WindSpeedApparent + " , WindAngle: " + (String) _WindAngleApparent);
      }
    }

    double getWindSpeedApparent(void)
    {
      // 1. Check that the data is not too old, or that data have been injected recently 

      // 2. Return the data 
      if (_debug) {
        Serial.println(_name + ":red WindSpeedApparent: " + (String) _WindSpeedApparent);
      }
      return _WindSpeedApparent;
    }

    double getWindAngleApparent(void)
    {
      // 1. Check that the data is not too old, or that data have been injected recently 

      // 2. Return the data 
      if (_debug) {
        Serial.println(_name + ":red WindAngleApparent: " + (String) _WindAngleApparent);
      }
      return _WindAngleApparent;
    }

    double getWindAngleTrueGround(void) {return _WindAngleTrueGround; }
    double getWindAngleTrueWater(void) {return _WindAngleTrueWater; }
    double getWindDirectionChangeAlarm(void) {return _WindDirectionChangeAlarm; }
    double getWindDirectionTrue(void) {return _WindDirectionTrue; }
    double getWindDirectionMagnetic(void) {return _WindDirectionMagnetic; }
    double getWindSpeedTrue(void) {return _WindSpeedTrue; }
    double getWindSpeedOverGround(void) {return _WindSpeedOverGround; }
    unsigned long getTime(void) {return _Time; }
    String getMode(void) {return _Mode; }

}; //NMEAenvironment   



class NMEAtanks {
  
  private:
    // General varables
    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "tank";   // Needed for all sensors
    int _thingSpeakField        = 0;
    boolean _sync               = false;      // Used to indicate if the sensor asked for updated values via the sync command
    float _diff = 0.3;  // Needed for all sensors
    
    double _warningValue         = 12.7;
    int _threshold              = 30; 

    boolean _currentState       = LOW;
    double _lastReportedValue    = 0.0;        // Needed for all sensors
    double _lastReadValue        = 0.0;        // Needed for all sensors
    unsigned long _readingIntervalTimer = 0;  // Needed for all sensors

    unsigned long _postingIntervalDelay = 27 * 1000; //Read and post the temperature every second second.  // Needed for all sensors
    unsigned long _postingIntervalTimer = 0;  // Needed for all sensors

    // SignalK varables 
    String _Name                = "tank"; 
    String _Type                = "unknown";
    /*
petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
     */
    double _Capacity            = 0.0;  
    double _CurrentLevel        = 0.0;
    double _CurrentVolume       = 0.0;
    double _Pressure            = 0.0;
    double _Temperature         = 0.0;
    double _Viscosity           = 0.0;
    double _Extinguishant       = 0.0;

  public:
  
    NMEAtanks(void) {
    }

    // Alterative constructor
    void begin(String name = "tank", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(String name = "tank", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Tank called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }

    // Sends a request for new data to the subArduinos connected via Serial2
    void sync(void)
    {
      _sync = true;
      //Serial2.println("{ \"status\":\"sync\" }");
    } 

    void check(float diff = 0.1){
      float value = getCurrentLevel();
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
    
    void setCurrentLevel(double currentLevel)
    {
      //if (serialValue isnot NAN) {
        _readingIntervalTimer = millis();
        _sync = false;
        _lastReadValue = currentLevel;
        if (currentLevel <= _warningValue){
          _currentState = HIGH;
        } else {
          _currentState = LOW;
        }
        if (_debug) {
          Serial.println(_name + ": tank set: " + (String) currentLevel + " , Warning: " + (String) _currentState);
        }
      //}
    }

    float read(void)
    {
      if (_debug) {
        Serial.println(_name + ": tank read: " + (String) _lastReadValue + " , Warning: " + (String) _currentState);
      }
      return _lastReadValue;
    }

    String getName(void) {return _Name; }
    String getType(void) {return _Type; }
    double getCapacity(void) {return _Capacity; }
    double getCurrentLevel(void) {return _CurrentLevel; }
    double getCurrentVolume(void) {return _CurrentVolume; }
    double getPressure(void) {return _Pressure; }
    double getTemperature(void) {return _Temperature; }
    double getViscosity(void) {return _Viscosity; }
    double getExtinguishant(void) {return _Extinguishant; }

}; // class NMEAtanks

/*
NMEAtanks FreshWater.getName
NMEAtanks FreshWater.getType
NMEAtanks FreshWater.getCapacity
NMEAtanks FreshWater.getCurrentLevel
NMEAtanks FreshWater.getCurrentVolume
NMEAtanks FreshWater.getPressure
NMEAtanks FreshWater.getTemperature
NMEAtanks FreshWater.getViscosity
NMEAtanks FreshWater.getExtinguishant

NMEAtanks.getFreshWaterName
NMEAtanks.getFreshWaterType
NMEAtanks.getFreshWaterCapacity
NMEAtanks.getFreshWaterCurrentLevel
NMEAtanks.getFreshWaterCurrentVolume
NMEAtanks.getFreshWaterPressure
NMEAtanks.getFreshWaterTemperature
NMEAtanks.getFreshWaterViscosity
NMEAtanks.getFreshWaterExtinguishant
tanks/wasteWater/<RegExp>/name
tanks/wasteWater/<RegExp>/type
tanks/wasteWater/<RegExp>/capacity
tanks/wasteWater/<RegExp>/currentLevel
tanks/wasteWater/<RegExp>/currentVolume
tanks/wasteWater/<RegExp>/pressure
tanks/wasteWater/<RegExp>/temperature
tanks/wasteWater/<RegExp>/viscosity
tanks/wasteWater/<RegExp>/extinguishant

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum

/vessels/<RegExp>/tanks
/vessels/<RegExp>/tanks/freshWater
/vessels/<RegExp>/tanks/freshWater/<RegExp>
/vessels/<RegExp>/tanks/freshWater/<RegExp>/name
/vessels/<RegExp>/tanks/freshWater/<RegExp>/type
/vessels/<RegExp>/tanks/freshWater/<RegExp>/capacity
/vessels/<RegExp>/tanks/freshWater/<RegExp>/currentLevel
/vessels/<RegExp>/tanks/freshWater/<RegExp>/currentVolume
/vessels/<RegExp>/tanks/freshWater/<RegExp>/pressure
/vessels/<RegExp>/tanks/freshWater/<RegExp>/temperature
/vessels/<RegExp>/tanks/freshWater/<RegExp>/viscosity
/vessels/<RegExp>/tanks/freshWater/<RegExp>/extinguishant
/vessels/<RegExp>/tanks/wasteWater
/vessels/<RegExp>/tanks/wasteWater/<RegExp>
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/name
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/type
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/capacity
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/currentLevel
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/currentVolume
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/pressure
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/temperature
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/viscosity
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/extinguishant
/vessels/<RegExp>/tanks/blackWater
/vessels/<RegExp>/tanks/blackWater/<RegExp>
/vessels/<RegExp>/tanks/blackWater/<RegExp>/name
/vessels/<RegExp>/tanks/blackWater/<RegExp>/type
/vessels/<RegExp>/tanks/blackWater/<RegExp>/capacity
/vessels/<RegExp>/tanks/blackWater/<RegExp>/currentLevel
/vessels/<RegExp>/tanks/blackWater/<RegExp>/currentVolume
/vessels/<RegExp>/tanks/blackWater/<RegExp>/pressure
/vessels/<RegExp>/tanks/blackWater/<RegExp>/temperature
/vessels/<RegExp>/tanks/blackWater/<RegExp>/viscosity
/vessels/<RegExp>/tanks/blackWater/<RegExp>/extinguishant
/vessels/<RegExp>/tanks/fuel
/vessels/<RegExp>/tanks/fuel/<RegExp>
/vessels/<RegExp>/tanks/fuel/<RegExp>/name
/vessels/<RegExp>/tanks/fuel/<RegExp>/type
/vessels/<RegExp>/tanks/fuel/<RegExp>/capacity
/vessels/<RegExp>/tanks/fuel/<RegExp>/currentLevel
/vessels/<RegExp>/tanks/fuel/<RegExp>/currentVolume
/vessels/<RegExp>/tanks/fuel/<RegExp>/pressure
/vessels/<RegExp>/tanks/fuel/<RegExp>/temperature
/vessels/<RegExp>/tanks/fuel/<RegExp>/viscosity
/vessels/<RegExp>/tanks/fuel/<RegExp>/extinguishant
/vessels/<RegExp>/tanks/lubrication
/vessels/<RegExp>/tanks/lubrication/<RegExp>
/vessels/<RegExp>/tanks/lubrication/<RegExp>/name
/vessels/<RegExp>/tanks/lubrication/<RegExp>/type
/vessels/<RegExp>/tanks/lubrication/<RegExp>/capacity
/vessels/<RegExp>/tanks/lubrication/<RegExp>/currentLevel
/vessels/<RegExp>/tanks/lubrication/<RegExp>/currentVolume
/vessels/<RegExp>/tanks/lubrication/<RegExp>/pressure
/vessels/<RegExp>/tanks/lubrication/<RegExp>/temperature
/vessels/<RegExp>/tanks/lubrication/<RegExp>/viscosity
/vessels/<RegExp>/tanks/lubrication/<RegExp>/extinguishant
/vessels/<RegExp>/tanks/liveWell
/vessels/<RegExp>/tanks/liveWell/<RegExp>
/vessels/<RegExp>/tanks/liveWell/<RegExp>/name
/vessels/<RegExp>/tanks/liveWell/<RegExp>/type
/vessels/<RegExp>/tanks/liveWell/<RegExp>/capacity
/vessels/<RegExp>/tanks/liveWell/<RegExp>/currentLevel
/vessels/<RegExp>/tanks/liveWell/<RegExp>/currentVolume
/vessels/<RegExp>/tanks/liveWell/<RegExp>/pressure
/vessels/<RegExp>/tanks/liveWell/<RegExp>/temperature
/vessels/<RegExp>/tanks/liveWell/<RegExp>/viscosity
/vessels/<RegExp>/tanks/liveWell/<RegExp>/extinguishant
/vessels/<RegExp>/tanks/baitWell
/vessels/<RegExp>/tanks/baitWell/<RegExp>
/vessels/<RegExp>/tanks/baitWell/<RegExp>/name
/vessels/<RegExp>/tanks/baitWell/<RegExp>/type
/vessels/<RegExp>/tanks/baitWell/<RegExp>/capacity
/vessels/<RegExp>/tanks/baitWell/<RegExp>/currentLevel
/vessels/<RegExp>/tanks/baitWell/<RegExp>/currentVolume
/vessels/<RegExp>/tanks/baitWell/<RegExp>/pressure
/vessels/<RegExp>/tanks/baitWell/<RegExp>/temperature
/vessels/<RegExp>/tanks/baitWell/<RegExp>/viscosity
/vessels/<RegExp>/tanks/baitWell/<RegExp>/extinguishant
/vessels/<RegExp>/tanks/gas
/vessels/<RegExp>/tanks/gas/<RegExp>
/vessels/<RegExp>/tanks/gas/<RegExp>/name
/vessels/<RegExp>/tanks/gas/<RegExp>/type
/vessels/<RegExp>/tanks/gas/<RegExp>/capacity
/vessels/<RegExp>/tanks/gas/<RegExp>/currentLevel
/vessels/<RegExp>/tanks/gas/<RegExp>/currentVolume
/vessels/<RegExp>/tanks/gas/<RegExp>/pressure
/vessels/<RegExp>/tanks/gas/<RegExp>/temperature
/vessels/<RegExp>/tanks/gas/<RegExp>/viscosity
/vessels/<RegExp>/tanks/gas/<RegExp>/extinguishant
/vessels/<RegExp>/tanks/ballast
/vessels/<RegExp>/tanks/ballast/<RegExp>
/vessels/<RegExp>/tanks/ballast/<RegExp>/name
/vessels/<RegExp>/tanks/ballast/<RegExp>/type
/vessels/<RegExp>/tanks/ballast/<RegExp>/capacity
/vessels/<RegExp>/tanks/ballast/<RegExp>/currentLevel
/vessels/<RegExp>/tanks/ballast/<RegExp>/currentVolume
/vessels/<RegExp>/tanks/ballast/<RegExp>/pressure
/vessels/<RegExp>/tanks/ballast/<RegExp>/temperature
/vessels/<RegExp>/tanks/ballast/<RegExp>/viscosity
/vessels/<RegExp>/tanks/ballast/<RegExp>/extinguishant
*/

/*
NMEAnavigation getLights
NMEAnavigation getCourseOverGroundMagnetic
NMEAnavigation getCourseOverGroundTrue
NMEAnavigation getCourseRhumbline
NMEAnavigation getCourseRhumblineCrossTrackError
NMEAnavigation getCourseRhumblineBearingTrackTrue
NMEAnavigation getCourseRhumblineBearingTrackMagnetic
NMEAnavigation getCourseRhumblineActiveRoute
NMEAnavigation getCourseRhumblineActiveRouteHref
NMEAnavigation getCourseRhumblineActiveRouteEstimatedTimeOfArrival
NMEAnavigation getCourseRhumblineActiveRouteStartTime
NMEAnavigation getCourseRhumblineNextPoint
NMEAnavigation getCourseRhumblinePreviousPoint
type
href
NMEAnavigation getCourseRhumblinePreviousPointDistance
NMEAnavigation getCourseRhumblinePreviousPointPosition
longitude (deg)
latitude (deg)
altitude (m)
NMEAnavigation getCourseGreatCircle
NMEAnavigation getCourseGreatCircleCrossTrackError
NMEAnavigation getCourseGreatCircleBearingTrackTrue
NMEAnavigation getCourseGreatCircleBearingTrackMagnetic
NMEAnavigation getCourseGreatCircleActiveRoute
NMEAnavigation getCourseGreatCircleActiveRouteHref
NMEAnavigation getCourseGreatCircleActiveRouteEstimatedTimeOfArrival
NMEAnavigation getCourseGreatCircleActiveRouteStartTime
NMEAnavigation getCourseGreatCircleNextPoint
NMEAnavigation getCourseGreatCirclePreviousPoint
NMEAnavigation getCourseGreatCirclePreviousPointDistance
NMEAnavigation getCourseGreatCirclePreviousPointPosition
longitude (deg)
latitude (deg)
altitude (m)
NMEAnavigation getClosestApproach
distance (m)
timeTo (s)
NMEAnavigation getRacing
NMEAnavigation getRacingStartLineStb
NMEAnavigation getRacingStartLinePort
NMEAnavigation getRacingDistanceStartline
NMEAnavigation getRacingTimeToStart
NMEAnavigation getRacingTimePortDown
NMEAnavigation getRacingTimePortUp
NMEAnavigation getRacingTimeStbdDown
NMEAnavigation getRacingTimeStbdUp
NMEAnavigation getRacingLayline
NMEAnavigation getRacingLaylineDistance
NMEAnavigation getRacingLaylineTime
NMEAnavigation getRacingOppositeLayline
NMEAnavigation getRacingOppositeLaylineTime
NMEAnavigation getMagneticVariation
NMEAnavigation getMagneticVariationAgeOfService
NMEAnavigation getDestination
NMEAnavigation getDestinationCommonName
NMEAnavigation getDestinationEta
NMEAnavigation getDestinationWaypoint
NMEAnavigation getGnss
NMEAnavigation getGnssType
NMEAnavigation getGnssMethodQuality
NMEAnavigation getGnssIntegrity
NMEAnavigation getGnssSatellites
NMEAnavigation getGnssAntennaAltitude
NMEAnavigation getGnssHorizontalDilution
NMEAnavigation getGnssPositionDilution
NMEAnavigation getGnssGeoidalSeparation
NMEAnavigation getGnssDifferentialAge
NMEAnavigation getGnssDifferentialReference
NMEAnavigation getHeadingMagnetic
NMEAnavigation getMagneticDeviation
NMEAnavigation getHeadingCompass
NMEAnavigation getHeadingTrue
NMEAnavigation getPosition
longitude (deg)
latitude (deg)
altitude (m)
NMEAnavigation getAttitude
roll (rad)
pitch (rad)
yaw (rad)
NMEAnavigation getManeuver
NMEAnavigation getRateOfTurn
NMEAnavigation getSpeedOverGround
NMEAnavigation getSpeedThroughWater
NMEAnavigation getSpeedThroughWaterTransverse
NMEAnavigation getSpeedThroughWaterLongitudinal
NMEAnavigation getLeewayAngle
NMEAnavigation getLog
NMEAnavigation getTrip
NMEAnavigation getTripLog
NMEAnavigation getTripLastReset
NMEAnavigation getState
NMEAnavigation getAnchor
NMEAnavigation getAnchorMaxRadius
NMEAnavigation getAnchorCurrentRadius
NMEAnavigation getAnchorPosition
NMEAnavigation getDatetime

*/
//=================
/*
/vessels/<RegExp>/navigation
/vessels/<RegExp>/navigation/lights
/vessels/<RegExp>/navigation/courseOverGroundMagnetic
/vessels/<RegExp>/navigation/courseOverGroundTrue
/vessels/<RegExp>/navigation/courseRhumbline
/vessels/<RegExp>/navigation/courseRhumbline/crossTrackError
/vessels/<RegExp>/navigation/courseRhumbline/bearingTrackTrue
/vessels/<RegExp>/navigation/courseRhumbline/bearingTrackMagnetic
/vessels/<RegExp>/navigation/courseRhumbline/activeRoute
/vessels/<RegExp>/navigation/courseRhumbline/activeRoute/href
/vessels/<RegExp>/navigation/courseRhumbline/activeRoute/estimatedTimeOfArrival
/vessels/<RegExp>/navigation/courseRhumbline/activeRoute/startTime
/vessels/<RegExp>/navigation/courseRhumbline/nextPoint
/vessels/<RegExp>/navigation/courseRhumbline/previousPoint
type
href
/vessels/<RegExp>/navigation/courseRhumbline/previousPoint/distance
/vessels/<RegExp>/navigation/courseRhumbline/previousPoint/position
longitude (deg)
latitude (deg)
altitude (m)
/vessels/<RegExp>/navigation/courseGreatCircle
/vessels/<RegExp>/navigation/courseGreatCircle/crossTrackError
/vessels/<RegExp>/navigation/courseGreatCircle/bearingTrackTrue
/vessels/<RegExp>/navigation/courseGreatCircle/bearingTrackMagnetic
/vessels/<RegExp>/navigation/courseGreatCircle/activeRoute
/vessels/<RegExp>/navigation/courseGreatCircle/activeRoute/href
/vessels/<RegExp>/navigation/courseGreatCircle/activeRoute/estimatedTimeOfArrival
/vessels/<RegExp>/navigation/courseGreatCircle/activeRoute/startTime
/vessels/<RegExp>/navigation/courseGreatCircle/nextPoint
/vessels/<RegExp>/navigation/courseGreatCircle/previousPoint
/vessels/<RegExp>/navigation/courseGreatCircle/previousPoint/distance
/vessels/<RegExp>/navigation/courseGreatCircle/previousPoint/position
longitude (deg)
latitude (deg)
altitude (m)
/vessels/<RegExp>/navigation/closestApproach
distance (m)
timeTo (s)
/vessels/<RegExp>/navigation/racing
/vessels/<RegExp>/navigation/racing/startLineStb
/vessels/<RegExp>/navigation/racing/startLinePort
/vessels/<RegExp>/navigation/racing/distanceStartline
/vessels/<RegExp>/navigation/racing/timeToStart
/vessels/<RegExp>/navigation/racing/timePortDown
/vessels/<RegExp>/navigation/racing/timePortUp
/vessels/<RegExp>/navigation/racing/timeStbdDown
/vessels/<RegExp>/navigation/racing/timeStbdUp
/vessels/<RegExp>/navigation/racing/layline
/vessels/<RegExp>/navigation/racing/layline/distance
/vessels/<RegExp>/navigation/racing/layline/time
/vessels/<RegExp>/navigation/racing/oppositeLayline
/vessels/<RegExp>/navigation/racing/oppositeLayline/time
/vessels/<RegExp>/navigation/magneticVariation
/vessels/<RegExp>/navigation/magneticVariationAgeOfService
/vessels/<RegExp>/navigation/destination
/vessels/<RegExp>/navigation/destination/commonName
/vessels/<RegExp>/navigation/destination/eta
/vessels/<RegExp>/navigation/destination/waypoint
/vessels/<RegExp>/navigation/gnss
/vessels/<RegExp>/navigation/gnss/type
/vessels/<RegExp>/navigation/gnss/methodQuality
/vessels/<RegExp>/navigation/gnss/integrity
/vessels/<RegExp>/navigation/gnss/satellites
/vessels/<RegExp>/navigation/gnss/antennaAltitude
/vessels/<RegExp>/navigation/gnss/horizontalDilution
/vessels/<RegExp>/navigation/gnss/positionDilution
/vessels/<RegExp>/navigation/gnss/geoidalSeparation
/vessels/<RegExp>/navigation/gnss/differentialAge
/vessels/<RegExp>/navigation/gnss/differentialReference
/vessels/<RegExp>/navigation/headingMagnetic
/vessels/<RegExp>/navigation/magneticDeviation
/vessels/<RegExp>/navigation/headingCompass
/vessels/<RegExp>/navigation/headingTrue
/vessels/<RegExp>/navigation/position
longitude (deg)
latitude (deg)
altitude (m)
/vessels/<RegExp>/navigation/attitude
roll (rad)
pitch (rad)
yaw (rad)
/vessels/<RegExp>/navigation/maneuver
/vessels/<RegExp>/navigation/rateOfTurn
/vessels/<RegExp>/navigation/speedOverGround
/vessels/<RegExp>/navigation/speedThroughWater
/vessels/<RegExp>/navigation/speedThroughWaterTransverse
/vessels/<RegExp>/navigation/speedThroughWaterLongitudinal
/vessels/<RegExp>/navigation/leewayAngle
/vessels/<RegExp>/navigation/log
/vessels/<RegExp>/navigation/trip
/vessels/<RegExp>/navigation/trip/log
/vessels/<RegExp>/navigation/trip/lastReset
/vessels/<RegExp>/navigation/state
/vessels/<RegExp>/navigation/anchor
/vessels/<RegExp>/navigation/anchor/maxRadius
/vessels/<RegExp>/navigation/anchor/currentRadius
/vessels/<RegExp>/navigation/anchor/position
/vessels/<RegExp>/navigation/datetime
*/

enum tSK_DriveType {
                    SK_saildrive = 0,
                    SK_shaft = 1, 
                    SK_outboard = 2, 
                    SK_jet = 3, 
                    SK_pod = 4, 
                    SK_other = 5, 
                    SK_Error=14,
                    SK_Unavailable=15
};

class NMEApropulsion {
  
  private:
    // General varables
    boolean _debug              = false;      // Needed for all sensors
    String  _name               = "serial";   // Needed for all sensors
    int _thingSpeakField        = 0;
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

    // SignalK varables 
    String _Label                             = "";
    String _State                             = "";
    double _Revolutions                       = 0.0;
    double _Temperature                       = 0.0;
    double _OilTemperature                    = 0.0;
    double _OilPressure                       = 0.0;
    double _AlternatorVoltage                 = 0.0;
    double _RunTime                           = 0.0;
    double _CoolantTemperature                = 0.0;
    double _CoolantPressure                   = 0.0;
    double _BoostPressure                     = 0.0;
    double _IntakeManifoldTemperature         = 0.0;
    double _EngineLoad                        = 0.0;
    double _EngineTorque                      = 0.0;
    double _Transmission                      = 0.0;
    double _TransmissionGear                  = 0.0;
    double _TransmissionGearRatio             = 0.0;
    double _TransmissionOilTemperature        = 0.0;
    double _TransmissionOilPressure           = 0.0;
    double _Drive                             = 0.0;
    //String _DriveType                         = "";
    tSK_DriveType _DriveType = SK_Unavailable;
//Enum values:
//saildrive
//shaft
//outboard
//jet
//pod
//other
    double _DriveTrimState                    = 0.0;
    double _DriveThrustAngle                  = 0.0;
    double _DrivePropeller                    = 0.0;
    String _Fuel                              = "";
    String _FuelType                          = "";
//Enum values:
//diesel
//petrol
//electric
//coal/wood
//other
    double _FuelUsed                          = 0.0;
    double _FuelPressure                      = 0.0;
    double _FuelRate                          = 0.0;
    double _FuelEconomyRate                   = 0.0;
    double _FuelAverageRate                   = 0.0;
    double _ExhaustTemperature                = 0.0;

    // to be replaced 
    int _rpm = 0; 
    double _temp = 0.0;

  public:
  
    NMEApropulsion(void) {
    }

    // Alterative constructor
    void begin(String name = "propulsion", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
    }

    // Alterative constructor that enables debug printouts
    void debug(String name = "propulsion", int thingSpeakField = 0, unsigned long postingIntervalDelay = 27 * 1000) {
      this->_name = name;
      this->_thingSpeakField = thingSpeakField;
      this->_postingIntervalDelay = postingIntervalDelay;
      _debug = true;
      if (_debug) {
        Serial.println("Propulsion called: " + name + " has _postingIntervalDelay: " + (String) _postingIntervalDelay);
      }
    }

    // Sends a request for new data to the subArduinos connected via Serial2
    void sync(void)
    {
      _sync = true;
      //Serial2.println("{ \"status\":\"sync\" }");
    } 

    /*
    void setCurrentLevel(double currentLevel)
    {
      //if (serialValue isnot NAN) {
        _readingIntervalTimer = millis();
        _sync = false;
        _lastReadValue = currentLevel;
        if (currentLevel <= _warningValue){
          _currentState = HIGH;
        } else {
          _currentState = LOW;
        }
        if (_debug) {
          Serial.println(_name + ": propulsion set: " + (String) currentLevel + " , Warning: " + (String) _currentState);
        }
      //}
    }

    float read(void)
    {
      if (_debug) {
        Serial.println(_name + ": propulsion read: " + (String) _lastReadValue + " , Warning: " + (String) _currentState);
      }
      return _lastReadValue;
    }
*/

    // Set the value of the motor rpm
    //void setRevolutions(double Revolutions) { _Revolutions = Revolutions;
    void setRPM(int rpm) {
      _rpm = rpm;
      if (_debug) {
        Serial.println("Motor set RPM: " + (String) _rpm );
      }
    }

    // Reads the value of the motor rpm
    // double getRevolutions(void) {return _Revolutions; }
    int getRPM(void) {
      if (_debug) {
        Serial.println("Motor reading RPM: " + (String) _rpm );
      }
      return _rpm;
    }
    
    // Set the value of the motor temp
    void setExhaustTemperature(double temp) {
      _ExhaustTemperature = temp;
      if (_debug) {
        Serial.println("Motor set ExhaustTemperature: " + (String) _ExhaustTemperature );
      }
    }
    
    // Reads the value of the motor temp
    double getExhaustTemperature(void) {
      if (_debug) {
        Serial.println("Motor reading ExhaustTemperature: " + (String) _ExhaustTemperature );
      }
      return _ExhaustTemperature;
    }

    void check(int diff = 10){
      int rpm = getRPM();
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

    String getLabel(void) {return _Label; }
    String getState(void) {return _State; }
    double getRevolutions(void) {return _Revolutions; }
    double getTemperature(void) {return _Temperature; }
    double getOilTemperature(void) {return _OilTemperature; }
    double getOilPressure(void) {return _OilPressure; }
    double getAlternatorVoltage(void) {return _AlternatorVoltage; }
    double getRunTime(void) {return _RunTime; }
    double getCoolantTemperature(void) {return _CoolantTemperature; }
    double getCoolantPressure(void) {return _CoolantPressure; }
    double getBoostPressure(void) {return _BoostPressure; }
    double getIntakeManifoldTemperature(void) {return _IntakeManifoldTemperature; }
    double getEngineLoad(void) {return _EngineLoad; }
    double getEngineTorque(void) {return _EngineTorque; }
    double getTransmission(void) {return _Transmission; }
    double getTransmissionGear(void) {return _TransmissionGear; }
    double getTransmissionGearRatio(void) {return _TransmissionGearRatio; }
    double getTransmissionOilTemperature(void) {return _TransmissionOilTemperature; }
    double getTransmissionOilPressure(void) {return _TransmissionOilPressure; }
    double getDrive(void) {return _Drive; }
    //String getDriveType(void) {return _DriveType; }
    tSK_DriveType getDriveType(void) {return _DriveType; }
//Enum values:
//saildrive
//shaft
//outboard
//jet
//pod
//other
    double getDriveTrimState(void) {return _DriveTrimState; }
    double getDriveThrustAngle(void) {return _DriveThrustAngle; }
    double getDrivePropeller(void) {return _DrivePropeller; }
    String getFuel(void) {return _Fuel; }
    String getFuelType(void) {return _FuelType; }
//Enum values:
//diesel
//petrol
//electric
//coal/wood
//other
    double getFuelUsed(void) {return _FuelUsed; }
    double getFuelPressure(void) {return _FuelPressure; }
    double getFuelRate(void) {return _FuelRate; }
    double getFuelEconomyRate(void) {return _FuelEconomyRate; }
    double getFuelAverageRate(void) {return _FuelAverageRate; }
// defined above    double getExhaustTemperature(void) {return _ExhaustTemperature; }

}; // class NMEApropulsion

/*
NMEApropulsion portEngine.getLabel
NMEApropulsion portEngine.getState
NMEApropulsion portEngine.getRevolutions
NMEApropulsion portEngine.getTemperature
NMEApropulsion portEngine.getOilTemperature
NMEApropulsion portEngine.getOilPressure
NMEApropulsion portEngine.getAlternatorVoltage
NMEApropulsion portEngine.getRunTime
NMEApropulsion portEngine.getCoolantTemperature
NMEApropulsion portEngine.getCoolantPressure
NMEApropulsion portEngine.getBoostPressure
NMEApropulsion portEngine.getIntakeManifoldTemperature
NMEApropulsion portEngine.getEngineLoad
NMEApropulsion portEngine.getEngineTorque
NMEApropulsion portEngine.getTransmission
NMEApropulsion portEngine.getTransmissionGear
NMEApropulsion portEngine.getTransmissionGearRatio
NMEApropulsion portEngine.getTransmissionOilTemperature
NMEApropulsion portEngine.getTransmissionOilPressure
NMEApropulsion portEngine.getDrive
NMEApropulsion portEngine.getDriveType
Enum values:
saildrive
shaft
outboard
jet
pod
other
NMEApropulsion portEngine.getDriveTrimState
NMEApropulsion portEngine.getDriveThrustAngle
NMEApropulsion portEngine.getDrivePropeller
NMEApropulsion portEngine.getFuel
NMEApropulsion portEngine.getFuelType
Enum values:
diesel
petrol
electric
coal/wood
other
NMEApropulsion portEngine.getFuelUsed
NMEApropulsion portEngine.getFuelPressure
NMEApropulsion portEngine.getFuelRate
NMEApropulsion portEngine.getFuelEconomyRate
NMEApropulsion portEngine.getFuelAverageRate
NMEApropulsion portEngine.getExhaustTemperature
*/

/*
/vessels/<RegExp>/propulsion
/vessels/<RegExp>/propulsion/<RegExp>
/vessels/<RegExp>/propulsion/<RegExp>/label
/vessels/<RegExp>/propulsion/<RegExp>/state
/vessels/<RegExp>/propulsion/<RegExp>/revolutions
/vessels/<RegExp>/propulsion/<RegExp>/temperature
/vessels/<RegExp>/propulsion/<RegExp>/oilTemperature
/vessels/<RegExp>/propulsion/<RegExp>/oilPressure
/vessels/<RegExp>/propulsion/<RegExp>/alternatorVoltage
/vessels/<RegExp>/propulsion/<RegExp>/runTime
/vessels/<RegExp>/propulsion/<RegExp>/coolantTemperature
/vessels/<RegExp>/propulsion/<RegExp>/coolantPressure
/vessels/<RegExp>/propulsion/<RegExp>/boostPressure
/vessels/<RegExp>/propulsion/<RegExp>/intakeManifoldTemperature
/vessels/<RegExp>/propulsion/<RegExp>/engineLoad
/vessels/<RegExp>/propulsion/<RegExp>/engineTorque
/vessels/<RegExp>/propulsion/<RegExp>/transmission
/vessels/<RegExp>/propulsion/<RegExp>/transmission/gear
/vessels/<RegExp>/propulsion/<RegExp>/transmission/gearRatio
/vessels/<RegExp>/propulsion/<RegExp>/transmission/oilTemperature
/vessels/<RegExp>/propulsion/<RegExp>/transmission/oilPressure
/vessels/<RegExp>/propulsion/<RegExp>/drive
/vessels/<RegExp>/propulsion/<RegExp>/drive/type
Enum values:
saildrive
shaft
outboard
jet
pod
other
/vessels/<RegExp>/propulsion/<RegExp>/drive/trimState
/vessels/<RegExp>/propulsion/<RegExp>/drive/thrustAngle
/vessels/<RegExp>/propulsion/<RegExp>/drive/propeller
/vessels/<RegExp>/propulsion/<RegExp>/fuel
/vessels/<RegExp>/propulsion/<RegExp>/fuel/type
Enum values:
diesel
petrol
electric
coal/wood
other
/vessels/<RegExp>/propulsion/<RegExp>/fuel/used
/vessels/<RegExp>/propulsion/<RegExp>/fuel/pressure
/vessels/<RegExp>/propulsion/<RegExp>/fuel/rate
/vessels/<RegExp>/propulsion/<RegExp>/fuel/economyRate
/vessels/<RegExp>/propulsion/<RegExp>/fuel/averageRate
/vessels/<RegExp>/propulsion/<RegExp>/exhaustTemperature
*/


/*
/vessels/<RegExp>/electrical
/vessels/<RegExp>/electrical/batteries
/vessels/<RegExp>/electrical/batteries/<RegExp>
/vessels/<RegExp>/electrical/batteries/<RegExp>/name
/vessels/<RegExp>/electrical/batteries/<RegExp>/location
/vessels/<RegExp>/electrical/batteries/<RegExp>/dateInstalled
/vessels/<RegExp>/electrical/batteries/<RegExp>/manufacturer
/vessels/<RegExp>/electrical/batteries/<RegExp>/manufacturer/name
/vessels/<RegExp>/electrical/batteries/<RegExp>/manufacturer/model
/vessels/<RegExp>/electrical/batteries/<RegExp>/manufacturer/URL
/vessels/<RegExp>/electrical/batteries/<RegExp>/associatedBus
/vessels/<RegExp>/electrical/batteries/<RegExp>/voltage
/vessels/<RegExp>/electrical/batteries/<RegExp>/voltage/ripple
/vessels/<RegExp>/electrical/batteries/<RegExp>/current
/vessels/<RegExp>/electrical/batteries/<RegExp>/temperature
/vessels/<RegExp>/electrical/batteries/<RegExp>/chemistry
/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity
/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/nominal
/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/actual
/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/remaining
/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/dischargeLimit
/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/stateOfCharge
/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/stateOfHealth
/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/dischargeSinceFull
/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/timeRemaining
/vessels/<RegExp>/electrical/batteries/<RegExp>/lifetimeDischarge
/vessels/<RegExp>/electrical/batteries/<RegExp>/lifetimeRecharge
/vessels/<RegExp>/electrical/inverters
/vessels/<RegExp>/electrical/inverters/<RegExp>
/vessels/<RegExp>/electrical/inverters/<RegExp>/name
/vessels/<RegExp>/electrical/inverters/<RegExp>/location
/vessels/<RegExp>/electrical/inverters/<RegExp>/dateInstalled
/vessels/<RegExp>/electrical/inverters/<RegExp>/manufacturer
/vessels/<RegExp>/electrical/inverters/<RegExp>/manufacturer/name
/vessels/<RegExp>/electrical/inverters/<RegExp>/manufacturer/model
/vessels/<RegExp>/electrical/inverters/<RegExp>/manufacturer/URL
/vessels/<RegExp>/electrical/inverters/<RegExp>/dc
/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/associatedBus
/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/voltage
/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/voltage/ripple
/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/current
/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/temperature
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/associatedBus
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/lineNeutralVoltage
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/lineLineVoltage
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/current
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/frequency
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/reactivePower
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/powerFactor
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/powerFactorLagging
Enum values:
leading
lagging
error
not available
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/realPower
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/apparentPower
/vessels/<RegExp>/electrical/inverters/<RegExp>/inverterMode
/vessels/<RegExp>/electrical/chargers
/vessels/<RegExp>/electrical/chargers/<RegExp>
/vessels/<RegExp>/electrical/chargers/<RegExp>/name
/vessels/<RegExp>/electrical/chargers/<RegExp>/location
/vessels/<RegExp>/electrical/chargers/<RegExp>/dateInstalled
/vessels/<RegExp>/electrical/chargers/<RegExp>/manufacturer
/vessels/<RegExp>/electrical/chargers/<RegExp>/manufacturer/name
/vessels/<RegExp>/electrical/chargers/<RegExp>/manufacturer/model
/vessels/<RegExp>/electrical/chargers/<RegExp>/manufacturer/URL
/vessels/<RegExp>/electrical/chargers/<RegExp>/associatedBus
/vessels/<RegExp>/electrical/chargers/<RegExp>/voltage
/vessels/<RegExp>/electrical/chargers/<RegExp>/voltage/ripple
/vessels/<RegExp>/electrical/chargers/<RegExp>/current
/vessels/<RegExp>/electrical/chargers/<RegExp>/temperature
/vessels/<RegExp>/electrical/chargers/<RegExp>/chargingAlgorithm
/vessels/<RegExp>/electrical/chargers/<RegExp>/chargerRole
/vessels/<RegExp>/electrical/chargers/<RegExp>/chargingMode
/vessels/<RegExp>/electrical/chargers/<RegExp>/setpointVoltage
/vessels/<RegExp>/electrical/chargers/<RegExp>/setpointCurrent
/vessels/<RegExp>/electrical/alternators
/vessels/<RegExp>/electrical/alternators/<RegExp>
/vessels/<RegExp>/electrical/alternators/<RegExp>/name
/vessels/<RegExp>/electrical/alternators/<RegExp>/location
/vessels/<RegExp>/electrical/alternators/<RegExp>/dateInstalled
/vessels/<RegExp>/electrical/alternators/<RegExp>/manufacturer
/vessels/<RegExp>/electrical/alternators/<RegExp>/manufacturer/name
/vessels/<RegExp>/electrical/alternators/<RegExp>/manufacturer/model
/vessels/<RegExp>/electrical/alternators/<RegExp>/manufacturer/URL
/vessels/<RegExp>/electrical/alternators/<RegExp>/associatedBus
/vessels/<RegExp>/electrical/alternators/<RegExp>/voltage
/vessels/<RegExp>/electrical/alternators/<RegExp>/voltage/ripple
/vessels/<RegExp>/electrical/alternators/<RegExp>/current
/vessels/<RegExp>/electrical/alternators/<RegExp>/temperature
/vessels/<RegExp>/electrical/alternators/<RegExp>/chargingAlgorithm
/vessels/<RegExp>/electrical/alternators/<RegExp>/chargerRole
/vessels/<RegExp>/electrical/alternators/<RegExp>/chargingMode
/vessels/<RegExp>/electrical/alternators/<RegExp>/setpointVoltage
/vessels/<RegExp>/electrical/alternators/<RegExp>/setpointCurrent
/vessels/<RegExp>/electrical/alternators/<RegExp>/revolutions
/vessels/<RegExp>/electrical/alternators/<RegExp>/pulleyRatio
/vessels/<RegExp>/electrical/alternators/<RegExp>/fieldDrive
/vessels/<RegExp>/electrical/alternators/<RegExp>/regulatorTemperature
/vessels/<RegExp>/electrical/solar
/vessels/<RegExp>/electrical/solar/<RegExp>
/vessels/<RegExp>/electrical/solar/<RegExp>/name
/vessels/<RegExp>/electrical/solar/<RegExp>/location
/vessels/<RegExp>/electrical/solar/<RegExp>/dateInstalled
/vessels/<RegExp>/electrical/solar/<RegExp>/manufacturer
/vessels/<RegExp>/electrical/solar/<RegExp>/manufacturer/name
/vessels/<RegExp>/electrical/solar/<RegExp>/manufacturer/model
/vessels/<RegExp>/electrical/solar/<RegExp>/manufacturer/URL
/vessels/<RegExp>/electrical/solar/<RegExp>/associatedBus
/vessels/<RegExp>/electrical/solar/<RegExp>/voltage
/vessels/<RegExp>/electrical/solar/<RegExp>/voltage/ripple
/vessels/<RegExp>/electrical/solar/<RegExp>/current
/vessels/<RegExp>/electrical/solar/<RegExp>/temperature
/vessels/<RegExp>/electrical/solar/<RegExp>/chargingAlgorithm
/vessels/<RegExp>/electrical/solar/<RegExp>/chargerRole
/vessels/<RegExp>/electrical/solar/<RegExp>/chargingMode
/vessels/<RegExp>/electrical/solar/<RegExp>/setpointVoltage
/vessels/<RegExp>/electrical/solar/<RegExp>/setpointCurrent
/vessels/<RegExp>/electrical/solar/<RegExp>/controllerMode
/vessels/<RegExp>/electrical/solar/<RegExp>/panelVoltage
/vessels/<RegExp>/electrical/solar/<RegExp>/panelCurrent
/vessels/<RegExp>/electrical/solar/<RegExp>/panelTemperature
/vessels/<RegExp>/electrical/solar/<RegExp>/load
/vessels/<RegExp>/electrical/solar/<RegExp>/loadCurrent
/vessels/<RegExp>/electrical/ac
/vessels/<RegExp>/electrical/ac/<RegExp>
/vessels/<RegExp>/electrical/ac/<RegExp>/name
/vessels/<RegExp>/electrical/ac/<RegExp>/location
/vessels/<RegExp>/electrical/ac/<RegExp>/dateInstalled
/vessels/<RegExp>/electrical/ac/<RegExp>/manufacturer
/vessels/<RegExp>/electrical/ac/<RegExp>/manufacturer/name
/vessels/<RegExp>/electrical/ac/<RegExp>/manufacturer/model
/vessels/<RegExp>/electrical/ac/<RegExp>/manufacturer/URL
/vessels/<RegExp>/electrical/ac/<RegExp>/phase
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/associatedBus
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/lineNeutralVoltage
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/lineLineVoltage
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/current
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/frequency
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/reactivePower
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/powerFactor
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/powerFactorLagging
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/realPower
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/apparentPower
*/

//===============================================================
/*
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
*/

/*

/vessels
Description: A wrapper object for vessel objects, each describing vessels in range, including this vessel.

/vessels/<RegExp>
Title: vessel

Description: This regex pattern is used for validation of an MMSI or Signal K UUID identifier for the vessel. Examples: urn:mrn:imo:mmsi:230099999 urn:mrn:signalk:uuid:c0d79334-4e25-4245-8892-54e8ccc8021d

/vessels/<RegExp>/url
Description: URL based identity of the vessel, if available.

/vessels/<RegExp>/mmsi
Description: MMSI number of the vessel, if available.

/vessels/<RegExp>/mothershipMmsi
Description: MMSI number of the mothership of this vessel, if available.

/vessels/<RegExp>/uuid
Description: A unique Signal K flavoured maritime resource identifier, assigned by the server.

/vessels/<RegExp>/name
Description: The common name of the vessel

/vessels/<RegExp>/flag
Description: The country of ship registration, or flag state of the vessel

/vessels/<RegExp>/port
Description: The home port of the vessel

/vessels/<RegExp>/registrations
Description: The various registrations of the vessel.

/vessels/<RegExp>/registrations/imo
Description: The IMO number of the vessel.

/vessels/<RegExp>/registrations/national
Description: The national registration number of the vessel.

/vessels/<RegExp>/registrations/national/<RegExp>
Description: This regex pattern is used for validating the identifier for the registration

/vessels/<RegExp>/registrations/national/<RegExp>/country
Description: The ISO 3166-2 country code.

/vessels/<RegExp>/registrations/national/<RegExp>/registration
Description: The registration code

/vessels/<RegExp>/registrations/national/<RegExp>/description
Description: The registration description

/vessels/<RegExp>/registrations/local
Description: A local or state registration number of the vessel.

/vessels/<RegExp>/registrations/local/<RegExp>
Description: This regex pattern is used for validating the identifier for the registration

/vessels/<RegExp>/registrations/local/<RegExp>/registration
Description: The registration code

/vessels/<RegExp>/registrations/local/<RegExp>/description
Description: The registration description

/vessels/<RegExp>/registrations/other
Description: Other registration or permits for the vessel.

/vessels/<RegExp>/registrations/other/<RegExp>
Description: This regex pattern is used for validating the identifier for the registration

/vessels/<RegExp>/registrations/other/<RegExp>/registration
Description: The registration code

/vessels/<RegExp>/registrations/other/<RegExp>/description
Description: The registration description

/vessels/<RegExp>/communication
Title: communication

Description: Communication data including Radio, Telephone, E-Mail, etc.

/vessels/<RegExp>/communication/callsignVhf
Description: Callsign for VHF communication

/vessels/<RegExp>/communication/callsignHf
Description: Callsign for HF communication

/vessels/<RegExp>/communication/phoneNumber
Description: Phone number of skipper

/vessels/<RegExp>/communication/emailHf
Description: Email address to be used for HF email (Winmail, Airmail, Sailmail)

/vessels/<RegExp>/communication/email
Description: Regular email for the skipper

/vessels/<RegExp>/communication/satPhoneNumber
Description: Satellite phone number for vessel.

/vessels/<RegExp>/communication/skipperName
Description: Full name of the skipper of the vessel.

/vessels/<RegExp>/communication/crewNames
Description: Array with the names of the crew

/vessels/<RegExp>/environment
Title: environment

Description: Environmental data measured locally including Depth, Wind, Temp, etc.

/vessels/<RegExp>/environment/outside
Description: Environmental conditions outside of the vessel's hull

/vessels/<RegExp>/environment/outside/temperature
Units: K (Kelvin)

Description: Current outside air temperature

/vessels/<RegExp>/environment/outside/dewPointTemperature
Units: K (Kelvin)

Description: Current outside dew point temperature

/vessels/<RegExp>/environment/outside/apparentWindChillTemperature
Units: K (Kelvin)

Description: Current outside apparent wind chill temperature

/vessels/<RegExp>/environment/outside/theoreticalWindChillTemperature
Units: K (Kelvin)

Description: Current outside theoretical wind chill temperature

/vessels/<RegExp>/environment/outside/heatIndexTemperature
Units: K (Kelvin)

Description: Current outside heat index temperature

/vessels/<RegExp>/environment/outside/pressure
Units: Pa (Pascal)

Description: Current outside air ambient pressure

/vessels/<RegExp>/environment/outside/humidity
Units: ratio (Ratio)

Description: Current outside air relative humidity

/vessels/<RegExp>/environment/outside/airDensity
Units: kg/m3 (undefined)

Description: Current outside air density

/vessels/<RegExp>/environment/outside/illuminance
Units: Lux (undefined)

Description: Current outside ambient light flux.

/vessels/<RegExp>/environment/inside
Description: Environmental conditions inside the vessel's hull

/vessels/<RegExp>/environment/inside/temperature
Units: K (Kelvin)

Description: Temperature

/vessels/<RegExp>/environment/inside/heatIndexTemperature
Units: K (Kelvin)

Description: Current heat index temperature in zone

/vessels/<RegExp>/environment/inside/pressure
Units: Pa (Pascal)

Description: Pressure in zone

/vessels/<RegExp>/environment/inside/relativeHumidity
Units: ratio (Ratio)

Description: Relative humidity in zone

/vessels/<RegExp>/environment/inside/dewPoint
Units: K (Kelvin)

Description: Dewpoint in zone

/vessels/<RegExp>/environment/inside/airDensity
Units: kg/m3 (undefined)

Description: Air density in zone

/vessels/<RegExp>/environment/inside/illuminance
Units: Lux (undefined)

Description: Illuminance in zone

/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+
Description: This regex pattern is used for validation of the identifier for the environmental zone, eg. engineRoom, mainCabin, refrigerator

/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/temperature
Units: K (Kelvin)

Description: Temperature

/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/heatIndexTemperature
Units: K (Kelvin)

Description: Current heat index temperature in zone

/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/pressure
Units: Pa (Pascal)

Description: Pressure in zone

/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/relativeHumidity
Units: ratio (Ratio)

Description: Relative humidity in zone

/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/dewPoint
Units: K (Kelvin)

Description: Dewpoint in zone

/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/airDensity
Units: kg/m3 (undefined)

Description: Air density in zone

/vessels/<RegExp>/environment/inside/[A-Za-z0-9]+/illuminance
Units: Lux (undefined)

Description: Illuminance in zone

/vessels/<RegExp>/environment/water
Description: Environmental conditions of the water that the vessel is sailing in

/vessels/<RegExp>/environment/water/temperature
Units: K (Kelvin)

Description: Current water temperature

/vessels/<RegExp>/environment/water/salinity
Units: ratio (Ratio)

Description: Water salinity

/vessels/<RegExp>/environment/depth
Title: depth

Description: Depth related data

/vessels/<RegExp>/environment/depth/belowKeel
Units: m (Meter)

Description: Depth below keel

/vessels/<RegExp>/environment/depth/belowTransducer
Units: m (Meter)

Description: Depth below Transducer

/vessels/<RegExp>/environment/depth/belowSurface
Units: m (Meter)

Description: Depth from surface

/vessels/<RegExp>/environment/depth/transducerToKeel
Units: m (Meter)

Description: Depth from the transducer to the bottom of the keel

/vessels/<RegExp>/environment/depth/surfaceToTransducer
Units: m (Meter)

Description: Depth transducer is below the water surface

/vessels/<RegExp>/environment/current
Title: current

Description: Direction and strength of current affecting the vessel

Object value with properties

drift (m/s)
setTrue (rad)
setMagnetic (rad)
/vessels/<RegExp>/environment/tide
Title: tide

Description: Tide data

/vessels/<RegExp>/environment/tide/heightHigh
Units: m (Meter)

Description: Next high tide height relative to lowest astronomical tide (LAT/Chart Datum)

/vessels/<RegExp>/environment/tide/heightNow
Units: m (Meter)

Description: The current tide height relative to lowest astronomical tide (LAT/Chart Datum)

/vessels/<RegExp>/environment/tide/heightLow
Units: m (Meter)

Description: The next low tide height relative to lowest astronomical tide (LAT/Chart Datum)

/vessels/<RegExp>/environment/tide/timeLow
Units: RFC 3339 (UTC) (undefined)

Description: Time of the next low tide in UTC

/vessels/<RegExp>/environment/tide/timeHigh
Units: RFC 3339 (UTC) (undefined)

Description: Time of next high tide in UTC

/vessels/<RegExp>/environment/heave
Units: m (Meter)

Description: Vertical movement of the vessel due to waves

/vessels/<RegExp>/environment/wind
Title: wind

Description: Wind data.

/vessels/<RegExp>/environment/wind/angleApparent
Units: rad (Radian)

Description: Apparent wind angle, negative to port

/vessels/<RegExp>/environment/wind/angleTrueGround
Units: rad (Radian)

Description: True wind angle based on speed over ground, negative to port

/vessels/<RegExp>/environment/wind/angleTrueWater
Units: rad (Radian)

Description: True wind angle based on speed through water, negative to port

/vessels/<RegExp>/environment/wind/directionChangeAlarm
Units: rad (Radian)

Description: The angle the wind needs to shift to raise an alarm

/vessels/<RegExp>/environment/wind/directionTrue
Units: rad (Radian)

Description: The wind direction relative to true north

/vessels/<RegExp>/environment/wind/directionMagnetic
Units: rad (Radian)

Description: The wind direction relative to magnetic north

/vessels/<RegExp>/environment/wind/speedTrue
Units: m/s (Meters per second)

Description: Wind speed over water (as calculated from speedApparent and vessel's speed through water)

/vessels/<RegExp>/environment/wind/speedOverGround
Units: m/s (Meters per second)

Description: Wind speed over ground (as calculated from speedApparent and vessel's speed over ground)

/vessels/<RegExp>/environment/wind/speedApparent
Units: m/s (Meters per second)

Description: Apparent wind speed

/vessels/<RegExp>/environment/time
Description: A time reference for the vessel. All clocks on the vessel dispaying local time should use the timezone offset here. If a timezoneRegion is supplied the timezone must also be supplied. If timezoneRegion is supplied that should be displayed by UIs in preference to simply timezone. ie 12:05 (Europe/London) should be displayed in preference to 12:05 (UTC+01:00)

/vessels/<RegExp>/environment/mode
Description: Mode of the vessel based on the current conditions. Can be combined with navigation.state to control vessel signals eg switch to night mode for instrumentation and lights, or make sound signals for fog.

/vessels/<RegExp>/navigation
Title: navigation

Description: Navigation data including Position, Course to next WP information, etc.

/vessels/<RegExp>/navigation/lights
Title: Navigation lights

Description: Current state of the vessels navigation lights

/vessels/<RegExp>/navigation/courseOverGroundMagnetic
Units: rad (Radian)

Description: Course over ground (magnetic)

/vessels/<RegExp>/navigation/courseOverGroundTrue
Units: rad (Radian)

Description: Course over ground (true)

/vessels/<RegExp>/navigation/courseRhumbline
Title: Course

Description: Course information computed with Rhumbline

/vessels/<RegExp>/navigation/courseRhumbline/crossTrackError
Units: m (Meter)

Description: The distance from the vessel's present position to the closest point on a line (track) between previousPoint and nextPoint. A negative number indicates that the vessel is currently to the left of this line (and thus must steer right to compensate), a positive number means the vessel is to the right of the line (steer left to compensate).

/vessels/<RegExp>/navigation/courseRhumbline/bearingTrackTrue
Units: rad (Radian)

Description: The bearing of a line between previousPoint and nextPoint, relative to true north.

/vessels/<RegExp>/navigation/courseRhumbline/bearingTrackMagnetic
Units: rad (Radian)

Description: The bearing of a line between previousPoint and nextPoint, relative to magnetic north.

/vessels/<RegExp>/navigation/courseRhumbline/activeRoute
Description: Data required if sailing to an active route, defined in resources.

/vessels/<RegExp>/navigation/courseRhumbline/activeRoute/href
Description: A reference (URL) to the presently active route, in resources.

/vessels/<RegExp>/navigation/courseRhumbline/activeRoute/estimatedTimeOfArrival
Description: The estimated time of arrival at the end of the current route

/vessels/<RegExp>/navigation/courseRhumbline/activeRoute/startTime
Description: The time this route was activated

/vessels/<RegExp>/navigation/courseRhumbline/nextPoint
Description: The point on earth the vessel's presently navigating towards

/vessels/<RegExp>/navigation/courseRhumbline/previousPoint
Description: The point on earth the vessel's presently navigating from

Object value with properties

type
href
/vessels/<RegExp>/navigation/courseRhumbline/previousPoint/distance
Units: m (Meter)

Description: The distance in meters between previousPoint and the vessel's present position

/vessels/<RegExp>/navigation/courseRhumbline/previousPoint/position
Title: position

Description: The position of lastPoint in two dimensions

Object value with properties

longitude (deg)
latitude (deg)
altitude (m)
/vessels/<RegExp>/navigation/courseGreatCircle
Title: Course

Description: Course information computed with Great Circle

/vessels/<RegExp>/navigation/courseGreatCircle/crossTrackError
Units: m (Meter)

Description: The distance from the vessel's present position to the closest point on a line (track) between previousPoint and nextPoint. A negative number indicates that the vessel is currently to the left of this line (and thus must steer right to compensate), a positive number means the vessel is to the right of the line (steer left to compensate).

/vessels/<RegExp>/navigation/courseGreatCircle/bearingTrackTrue
Units: rad (Radian)

Description: The bearing of a line between previousPoint and nextPoint, relative to true north.

/vessels/<RegExp>/navigation/courseGreatCircle/bearingTrackMagnetic
Units: rad (Radian)

Description: The bearing of a line between previousPoint and nextPoint, relative to magnetic north.

/vessels/<RegExp>/navigation/courseGreatCircle/activeRoute
Description: Data required if sailing to an active route, defined in resources.

/vessels/<RegExp>/navigation/courseGreatCircle/activeRoute/href
Description: A reference (URL) to the presently active route, in resources.

/vessels/<RegExp>/navigation/courseGreatCircle/activeRoute/estimatedTimeOfArrival
Description: The estimated time of arrival at the end of the current route

/vessels/<RegExp>/navigation/courseGreatCircle/activeRoute/startTime
Description: The time this route was activated

/vessels/<RegExp>/navigation/courseGreatCircle/nextPoint
Description: The point on earth the vessel's presently navigating towards

/vessels/<RegExp>/navigation/courseGreatCircle/previousPoint
Description: The point on earth the vessel's presently navigating from

Object value with properties

type
href
/vessels/<RegExp>/navigation/courseGreatCircle/previousPoint/distance
Units: m (Meter)

Description: The distance in meters between previousPoint and the vessel's present position

/vessels/<RegExp>/navigation/courseGreatCircle/previousPoint/position
Title: position

Description: The position of lastPoint in two dimensions

Object value with properties

longitude (deg)
latitude (deg)
altitude (m)
/vessels/<RegExp>/navigation/closestApproach
Description: Calculated values for other vessels, e.g. from AIS

Object value with properties

distance (m)
timeTo (s)
/vessels/<RegExp>/navigation/racing
Description: Specific navigational data related to yacht racing.

/vessels/<RegExp>/navigation/racing/startLineStb
Title: position

Description: Position of starboard start mark

Object value with properties

longitude (deg)
latitude (deg)
altitude (m)
/vessels/<RegExp>/navigation/racing/startLinePort
Title: position

Description: Position of port start mark

Object value with properties

longitude (deg)
latitude (deg)
altitude (m)
/vessels/<RegExp>/navigation/racing/distanceStartline
Units: m (Meter)

Description: The current distance to the start line

/vessels/<RegExp>/navigation/racing/timeToStart
Units: s (Second)

Description: Time left before start

/vessels/<RegExp>/navigation/racing/timePortDown
Units: s (Second)

Description: Time to arrive at the start line on port, turning downwind

/vessels/<RegExp>/navigation/racing/timePortUp
Units: s (Second)

Description: Time to arrive at the start line on port, turning upwind

/vessels/<RegExp>/navigation/racing/timeStbdDown
Units: s (Second)

Description: Time to arrive at the start line on starboard, turning downwind

/vessels/<RegExp>/navigation/racing/timeStbdUp
Units: s (Second)

Description: Time to arrive at the start line on starboard, turning upwind

/vessels/<RegExp>/navigation/racing/layline
Description: The layline crossing the current course

/vessels/<RegExp>/navigation/racing/layline/distance
Units: m (Meter)

Description: The current distance to the layline

/vessels/<RegExp>/navigation/racing/layline/time
Units: s (Second)

Description: The time to the layline at current speed and heading

/vessels/<RegExp>/navigation/racing/oppositeLayline
Description: The layline parallell to current course

/vessels/<RegExp>/navigation/racing/oppositeLayline/distance
Units: m (Meter)

Description: The current distance to the layline

/vessels/<RegExp>/navigation/racing/oppositeLayline/time
Units: s (Second)

Description: The time to the layline at current speed and heading

/vessels/<RegExp>/navigation/magneticVariation
Units: rad (Radian)

Description: The magnetic variation (declination) at the current position that must be added to the magnetic heading to derive the true heading. Easterly variations are positive and Westerly variations are negative (in Radians).

/vessels/<RegExp>/navigation/magneticVariationAgeOfService
Units: s (Second)

Description: Seconds since the 1st Jan 1970 that the variation calculation was made

/vessels/<RegExp>/navigation/destination
Title: destination

Description: The intended destination of this trip

/vessels/<RegExp>/navigation/destination/commonName
Description: Common name of the Destination, eg 'Fiji', also used in ais messages

/vessels/<RegExp>/navigation/destination/eta
Description: Expected time of arrival at destination waypoint

/vessels/<RegExp>/navigation/destination/waypoint
Description: UUID of destination waypoint

/vessels/<RegExp>/navigation/gnss
Title: gnss

Description: Global satellite navigation meta information

/vessels/<RegExp>/navigation/gnss/type
Description: Fix type

/vessels/<RegExp>/navigation/gnss/methodQuality
Description: Quality of the satellite fix

/vessels/<RegExp>/navigation/gnss/integrity
Description: Integrity of the satellite fix

/vessels/<RegExp>/navigation/gnss/satellites
Description: Number of satellites

/vessels/<RegExp>/navigation/gnss/antennaAltitude
Units: m (Meter)

Description: Altitude of antenna

/vessels/<RegExp>/navigation/gnss/horizontalDilution
Description: Horizontal Dilution of Precision

/vessels/<RegExp>/navigation/gnss/positionDilution
Description: Positional Dilution of Precision

/vessels/<RegExp>/navigation/gnss/geoidalSeparation
Description: Difference between WGS84 earth ellipsoid and mean sea level

/vessels/<RegExp>/navigation/gnss/differentialAge
Units: s (Second)

Description: Age of DGPS data

/vessels/<RegExp>/navigation/gnss/differentialReference
Description: ID of DGPS base station

/vessels/<RegExp>/navigation/headingMagnetic
Units: rad (Radian)

Description: Current magnetic heading of the vessel, equals 'headingCompass adjusted for magneticDeviation'

/vessels/<RegExp>/navigation/magneticDeviation
Units: rad (Radian)

Description: Magnetic deviation of the compass at the current headingCompass

/vessels/<RegExp>/navigation/headingCompass
Units: rad (Radian)

Description: Current magnetic heading received from the compass. This is not adjusted for magneticDeviation of the compass

/vessels/<RegExp>/navigation/headingTrue
Units: rad (Radian)

Description: The current true north heading of the vessel, equals 'headingMagnetic adjusted for magneticVariation'

/vessels/<RegExp>/navigation/position
Title: position

Description: The position of the vessel in 2 or 3 dimensions (WGS84 datum)

Object value with properties

longitude (deg)
latitude (deg)
altitude (m)
/vessels/<RegExp>/navigation/attitude
Title: Attitude

Description: Vessel attitude: roll, pitch and yaw

Object value with properties

roll (rad)
pitch (rad)
yaw (rad)
/vessels/<RegExp>/navigation/maneuver
Description: Special maneuver such as regional passing arrangement. (from ais)

/vessels/<RegExp>/navigation/rateOfTurn
Units: rad/s (Radian per second)

Description: Rate of turn (+ve is change to starboard). If the value is AIS RIGHT or LEFT, set to +-0.0206 rads and add warning in notifications

/vessels/<RegExp>/navigation/speedOverGround
Units: m/s (Meters per second)

Description: Vessel speed over ground. If converting from AIS 'HIGH' value, set to 102.2 (Ais max value) and add warning in notifications

/vessels/<RegExp>/navigation/speedThroughWater
Units: m/s (Meters per second)

Description: Vessel speed through the water

/vessels/<RegExp>/navigation/speedThroughWaterTransverse
Units: m/s (Meters per second)

Description: Transverse speed through the water (Leeway)

/vessels/<RegExp>/navigation/speedThroughWaterLongitudinal
Units: m/s (Meters per second)

Description: Longitudinal speed through the water

/vessels/<RegExp>/navigation/leewayAngle
Units: rad (Radian)

Description: Leeway Angle derived from the longitudinal and transverse speeds through the water

/vessels/<RegExp>/navigation/log
Units: m (Meter)

Description: Total distance traveled

/vessels/<RegExp>/navigation/trip
Description: Trip data

/vessels/<RegExp>/navigation/trip/log
Units: m (Meter)

Description: Total distance traveled on this trip / since trip reset

/vessels/<RegExp>/navigation/trip/lastReset
Description: Trip log reset time

/vessels/<RegExp>/navigation/state
Title: state

Description: Current navigational state of the vessel

/vessels/<RegExp>/navigation/anchor
Title: anchor

Description: The anchor data, for anchor watch etc

/vessels/<RegExp>/navigation/anchor/maxRadius
Units: m (Meter)

Description: Radius of anchor alarm boundary. The distance from anchor to the center of the boat

/vessels/<RegExp>/navigation/anchor/currentRadius
Units: m (Meter)

Description: Current distance to anchor

/vessels/<RegExp>/navigation/anchor/position
Title: position

Description: The actual anchor position of the vessel in 3 dimensions, probably an estimate at best

Object value with properties

longitude (deg)
latitude (deg)
altitude (m)
/vessels/<RegExp>/navigation/datetime
Description: Time and Date from the GNSS Positioning System

/vessels/<RegExp>/propulsion
Title: propulsion

Description: Engine data, each engine identified by a unique name i.e. Port_Engine

/vessels/<RegExp>/propulsion/<RegExp>
Description: This regex pattern is used for validation of the identifier for the propulsion unit

/vessels/<RegExp>/propulsion/<RegExp>/label
Description: Human readable label for the propulsion unit

/vessels/<RegExp>/propulsion/<RegExp>/state
Description: The current state of the engine

/vessels/<RegExp>/propulsion/<RegExp>/revolutions
Units: Hz (Hertz)

Description: Engine revolutions (x60 for RPM)

/vessels/<RegExp>/propulsion/<RegExp>/temperature
Units: K (Kelvin)

Description: Engine temperature

/vessels/<RegExp>/propulsion/<RegExp>/oilTemperature
Units: K (Kelvin)

Description: Oil temperature

/vessels/<RegExp>/propulsion/<RegExp>/oilPressure
Units: Pa (Pascal)

Description: Oil pressure

/vessels/<RegExp>/propulsion/<RegExp>/alternatorVoltage
Units: V (Volt)

Description: Alternator voltage

/vessels/<RegExp>/propulsion/<RegExp>/runTime
Units: s (Second)

Description: Total running time for engine (Engine Hours in seconds)

/vessels/<RegExp>/propulsion/<RegExp>/coolantTemperature
Units: K (Kelvin)

Description: Coolant temperature

/vessels/<RegExp>/propulsion/<RegExp>/coolantPressure
Units: Pa (Pascal)

Description: Coolant pressure

/vessels/<RegExp>/propulsion/<RegExp>/boostPressure
Units: Pa (Pascal)

Description: Engine boost (turbo, supercharger) pressure

/vessels/<RegExp>/propulsion/<RegExp>/intakeManifoldTemperature
Units: K (Kelvin)

Description: Intake manifold temperature

/vessels/<RegExp>/propulsion/<RegExp>/engineLoad
Units: ratio (Ratio)

Description: Engine load ratio, 0<=ratio<=1, 1 is 100%

/vessels/<RegExp>/propulsion/<RegExp>/engineTorque
Units: ratio (Ratio)

Description: Engine torque ratio, 0<=ratio<=1, 1 is 100%

/vessels/<RegExp>/propulsion/<RegExp>/transmission
Description: The transmission (gear box) of the named engine

/vessels/<RegExp>/propulsion/<RegExp>/transmission/gear
Description: Currently selected gear the engine is in i.e. Forward, Reverse, etc.

/vessels/<RegExp>/propulsion/<RegExp>/transmission/gearRatio
Units: ratio (Ratio)

Description: Gear ratio, engine rotations per propeller shaft rotation

/vessels/<RegExp>/propulsion/<RegExp>/transmission/oilTemperature
Units: K (Kelvin)

Description: Oil temperature

/vessels/<RegExp>/propulsion/<RegExp>/transmission/oilPressure
Units: Pa (Pascal)

Description: Oil pressure

/vessels/<RegExp>/propulsion/<RegExp>/drive
Description: Data about the engine's drive.

/vessels/<RegExp>/propulsion/<RegExp>/drive/type
Description: The type of drive the boat has i.e Outboard, shaft, jet, etc.

Enum values:

saildrive
shaft
outboard
jet
pod
other
/vessels/<RegExp>/propulsion/<RegExp>/drive/trimState
Units: ratio (Ratio)

Description: Trim/tilt state, 0<=ratio<=1, 1 is 100% up

/vessels/<RegExp>/propulsion/<RegExp>/drive/thrustAngle
Units: rad (Radian)

Description: Current thrust angle for steerable drives, +ve is thrust to Starboard

/vessels/<RegExp>/propulsion/<RegExp>/drive/propeller
Description: Data about the drive's propeller (pitch and slip)

/vessels/<RegExp>/propulsion/<RegExp>/fuel
Description: Data about the engine's Fuel Supply

/vessels/<RegExp>/propulsion/<RegExp>/fuel/type
Description: Fuel type

Enum values:

diesel
petrol
electric
coal/wood
other
/vessels/<RegExp>/propulsion/<RegExp>/fuel/used
Units: m3 (Cubic meter)

Description: Used fuel since last reset. Resetting is at user discretion

/vessels/<RegExp>/propulsion/<RegExp>/fuel/pressure
Units: Pa (Pascal)

Description: Fuel pressure

/vessels/<RegExp>/propulsion/<RegExp>/fuel/rate
Units: m3/s (Cubic meter per second)

Description: Fuel rate of consumption

/vessels/<RegExp>/propulsion/<RegExp>/fuel/economyRate
Units: m3/s (Cubic meter per second)

Description: Economy fuel rate of consumption

/vessels/<RegExp>/propulsion/<RegExp>/fuel/averageRate
Units: m3/s (Cubic meter per second)

Description: Average fuel rate of consumption

/vessels/<RegExp>/propulsion/<RegExp>/exhaustTemperature
Units: K (Kelvin)

Description: Exhaust temperature

/vessels/<RegExp>/electrical
Title: electrical

Description: Electrical data, each electrical device indentified by a unique name i.e. Battery_1

/vessels/<RegExp>/electrical/batteries
Description: Data about the vessel's batteries

/vessels/<RegExp>/electrical/batteries/<RegExp>
Title: Battery keyed by instance id

Description: Batteries, one or many, within the vessel

/vessels/<RegExp>/electrical/batteries/<RegExp>/name
Description: Unique ID of device (houseBattery, alternator, Generator, solar1, inverter, charger, combiner, etc.)

/vessels/<RegExp>/electrical/batteries/<RegExp>/location
Description: Installed location of device on vessel

/vessels/<RegExp>/electrical/batteries/<RegExp>/dateInstalled
Units: RFC 3339 (UTC) (undefined)

Description: Date device was installed

/vessels/<RegExp>/electrical/batteries/<RegExp>/manufacturer
Description: [missing]

/vessels/<RegExp>/electrical/batteries/<RegExp>/manufacturer/name
Description: Manufacturer's name

/vessels/<RegExp>/electrical/batteries/<RegExp>/manufacturer/model
Description: Model or part number

/vessels/<RegExp>/electrical/batteries/<RegExp>/manufacturer/URL
Description: Web referance / URL

/vessels/<RegExp>/electrical/batteries/<RegExp>/associatedBus
Description: Name of BUS device is associated with

/vessels/<RegExp>/electrical/batteries/<RegExp>/voltage
Units: V (Volt)

Description: Voltage measured at or as close as possible to the device

/vessels/<RegExp>/electrical/batteries/<RegExp>/voltage/ripple
Units: V (Volt)

Description: DC Ripple voltage

/vessels/<RegExp>/electrical/batteries/<RegExp>/current
Units: A (Ampere)

Description: Current flowing out (+ve) or in (-ve) to the device

/vessels/<RegExp>/electrical/batteries/<RegExp>/temperature
Title: temperature

Units: K (Kelvin)

Description: Temperature measured within or on the device

/vessels/<RegExp>/electrical/batteries/<RegExp>/chemistry
Description: Type of battery FLA, LiFePO4, etc.

/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity
Title: capacity

Description: Data about the battery's capacity

/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/nominal
Units: J (Joule)

Description: The capacity of battery as specified by the manufacturer

/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/actual
Units: J (Joule)

Description: The measured capacity of battery. This may change over time and will likely deviate from the nominal capacity.

/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/remaining
Units: J (Joule)

Description: Capacity remaining in battery

/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/dischargeLimit
Units: J (Joule)

Description: Minimum capacity to be left in the battery while discharging

/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/stateOfCharge
Units: ratio (Ratio)

Description: State of charge, 1 = 100%

/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/stateOfHealth
Units: ratio (Ratio)

Description: State of Health, 1 = 100%

/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/dischargeSinceFull
Units: C (Coulomb)

Description: Cumulative discharge since battery was last full

/vessels/<RegExp>/electrical/batteries/<RegExp>/capacity/timeRemaining
Units: s (Second)

Description: Time to discharge to discharge limit at current rate

/vessels/<RegExp>/electrical/batteries/<RegExp>/lifetimeDischarge
Units: C (Coulomb)

Description: Cumulative charge discharged from battery over operational lifetime of battery

/vessels/<RegExp>/electrical/batteries/<RegExp>/lifetimeRecharge
Units: C (Coulomb)

Description: Cumulative charge recharged into battery over operational lifetime of battery

/vessels/<RegExp>/electrical/inverters
Description: Data about the Inverter that has both DC and AC qualities

/vessels/<RegExp>/electrical/inverters/<RegExp>
Title: Inverter

Description: DC to AC inverter, one or many, within the vessel

/vessels/<RegExp>/electrical/inverters/<RegExp>/name
Description: Unique ID of device (houseBattery, alternator, Generator, solar1, inverter, charger, combiner, etc.)

/vessels/<RegExp>/electrical/inverters/<RegExp>/location
Description: Installed location of device on vessel

/vessels/<RegExp>/electrical/inverters/<RegExp>/dateInstalled
Units: RFC 3339 (UTC) (undefined)

Description: Date device was installed

/vessels/<RegExp>/electrical/inverters/<RegExp>/manufacturer
Description: [missing]

/vessels/<RegExp>/electrical/inverters/<RegExp>/manufacturer/name
Description: Manufacturer's name

/vessels/<RegExp>/electrical/inverters/<RegExp>/manufacturer/model
Description: Model or part number

/vessels/<RegExp>/electrical/inverters/<RegExp>/manufacturer/URL
Description: Web referance / URL

/vessels/<RegExp>/electrical/inverters/<RegExp>/dc
Title: DC Qualities

Description: DC common qualities

/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/associatedBus
Description: Name of BUS device is associated with

/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/voltage
Units: V (Volt)

Description: Voltage measured at or as close as possible to the device

/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/voltage/ripple
Units: V (Volt)

Description: DC Ripple voltage

/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/current
Units: A (Ampere)

Description: Current flowing out (+ve) or in (-ve) to the device

/vessels/<RegExp>/electrical/inverters/<RegExp>/dc/temperature
Title: temperature

Units: K (Kelvin)

Description: Temperature measured within or on the device

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac
Title: AC Qualities

Description: AC equipment common qualities

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/associatedBus
Description: Name of BUS device is associated with

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/lineNeutralVoltage
Units: V (Volt)

Description: RMS voltage measured between phase and neutral

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/lineLineVoltage
Units: V (Volt)

Description: RMS voltage measured between phases

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/current
Units: A (Ampere)

Description: RMS current

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/frequency
Units: Hz (Hertz)

Description: AC frequency.

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/reactivePower
Units: W (Watt)

Description: Reactive power

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/powerFactor
Description: Power factor

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/powerFactorLagging
Description: Lead/lag status.

Enum values:

leading
lagging
error
not available
/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/realPower
Units: W (Watt)

Description: Real power.

/vessels/<RegExp>/electrical/inverters/<RegExp>/ac/apparentPower
Units: W (Watt)

Description: Apparent power.

/vessels/<RegExp>/electrical/inverters/<RegExp>/inverterMode
Description: Mode of inverter

/vessels/<RegExp>/electrical/chargers
Description: Data about AC sourced battery charger

/vessels/<RegExp>/electrical/chargers/<RegExp>
Title: Charger

Description: Battery charger

/vessels/<RegExp>/electrical/chargers/<RegExp>/name
Description: Unique ID of device (houseBattery, alternator, Generator, solar1, inverter, charger, combiner, etc.)

/vessels/<RegExp>/electrical/chargers/<RegExp>/location
Description: Installed location of device on vessel

/vessels/<RegExp>/electrical/chargers/<RegExp>/dateInstalled
Units: RFC 3339 (UTC) (undefined)

Description: Date device was installed

/vessels/<RegExp>/electrical/chargers/<RegExp>/manufacturer
Description: [missing]

/vessels/<RegExp>/electrical/chargers/<RegExp>/manufacturer/name
Description: Manufacturer's name

/vessels/<RegExp>/electrical/chargers/<RegExp>/manufacturer/model
Description: Model or part number

/vessels/<RegExp>/electrical/chargers/<RegExp>/manufacturer/URL
Description: Web referance / URL

/vessels/<RegExp>/electrical/chargers/<RegExp>/associatedBus
Description: Name of BUS device is associated with

/vessels/<RegExp>/electrical/chargers/<RegExp>/voltage
Units: V (Volt)

Description: Voltage measured at or as close as possible to the device

/vessels/<RegExp>/electrical/chargers/<RegExp>/voltage/ripple
Units: V (Volt)

Description: DC Ripple voltage

/vessels/<RegExp>/electrical/chargers/<RegExp>/current
Units: A (Ampere)

Description: Current flowing out (+ve) or in (-ve) to the device

/vessels/<RegExp>/electrical/chargers/<RegExp>/temperature
Title: temperature

Units: K (Kelvin)

Description: Temperature measured within or on the device

/vessels/<RegExp>/electrical/chargers/<RegExp>/chargingAlgorithm
Description: Algorithm being used by the charger

/vessels/<RegExp>/electrical/chargers/<RegExp>/chargerRole
Description: How is charging source configured? Standalone, or in sync with another charger?

/vessels/<RegExp>/electrical/chargers/<RegExp>/chargingMode
Description: Charging mode i.e. float, overcharge, etc.

/vessels/<RegExp>/electrical/chargers/<RegExp>/setpointVoltage
Units: V (Volt)

Description: Target regulation voltage

/vessels/<RegExp>/electrical/chargers/<RegExp>/setpointCurrent
Units: A (Ampere)

Description: Target current limit

/vessels/<RegExp>/electrical/alternators
Description: Data about an Alternator charging device

/vessels/<RegExp>/electrical/alternators/<RegExp>
Title: Alternator

Description: Mechanically driven alternator, includes dynamos

/vessels/<RegExp>/electrical/alternators/<RegExp>/name
Description: Unique ID of device (houseBattery, alternator, Generator, solar1, inverter, charger, combiner, etc.)

/vessels/<RegExp>/electrical/alternators/<RegExp>/location
Description: Installed location of device on vessel

/vessels/<RegExp>/electrical/alternators/<RegExp>/dateInstalled
Units: RFC 3339 (UTC) (undefined)

Description: Date device was installed

/vessels/<RegExp>/electrical/alternators/<RegExp>/manufacturer
Description: [missing]

/vessels/<RegExp>/electrical/alternators/<RegExp>/manufacturer/name
Description: Manufacturer's name

/vessels/<RegExp>/electrical/alternators/<RegExp>/manufacturer/model
Description: Model or part number

/vessels/<RegExp>/electrical/alternators/<RegExp>/manufacturer/URL
Description: Web referance / URL

/vessels/<RegExp>/electrical/alternators/<RegExp>/associatedBus
Description: Name of BUS device is associated with

/vessels/<RegExp>/electrical/alternators/<RegExp>/voltage
Units: V (Volt)

Description: Voltage measured at or as close as possible to the device

/vessels/<RegExp>/electrical/alternators/<RegExp>/voltage/ripple
Units: V (Volt)

Description: DC Ripple voltage

/vessels/<RegExp>/electrical/alternators/<RegExp>/current
Units: A (Ampere)

Description: Current flowing out (+ve) or in (-ve) to the device

/vessels/<RegExp>/electrical/alternators/<RegExp>/temperature
Title: temperature

Units: K (Kelvin)

Description: Temperature measured within or on the device

/vessels/<RegExp>/electrical/alternators/<RegExp>/chargingAlgorithm
Description: Algorithm being used by the charger

/vessels/<RegExp>/electrical/alternators/<RegExp>/chargerRole
Description: How is charging source configured? Standalone, or in sync with another charger?

/vessels/<RegExp>/electrical/alternators/<RegExp>/chargingMode
Description: Charging mode i.e. float, overcharge, etc.

/vessels/<RegExp>/electrical/alternators/<RegExp>/setpointVoltage
Units: V (Volt)

Description: Target regulation voltage

/vessels/<RegExp>/electrical/alternators/<RegExp>/setpointCurrent
Units: A (Ampere)

Description: Target current limit

/vessels/<RegExp>/electrical/alternators/<RegExp>/revolutions
Units: Hz (Hertz)

Description: Alternator revolutions per second (x60 for RPM)

/vessels/<RegExp>/electrical/alternators/<RegExp>/pulleyRatio
Units: ratio (Ratio)

Description: Mechanical pulley ratio of driving source (Used to back calculate engine RPMs)

/vessels/<RegExp>/electrical/alternators/<RegExp>/fieldDrive
Units: % (undefined)

Description: % (0..100) of field voltage applied

/vessels/<RegExp>/electrical/alternators/<RegExp>/regulatorTemperature
Units: K (Kelvin)

Description: Current temperature of critical regulator components

/vessels/<RegExp>/electrical/solar
Description: Data about Solar charging device(s)

/vessels/<RegExp>/electrical/solar/<RegExp>
Title: Solar

Description: Photovoltaic charging devices

/vessels/<RegExp>/electrical/solar/<RegExp>/name
Description: Unique ID of device (houseBattery, alternator, Generator, solar1, inverter, charger, combiner, etc.)

/vessels/<RegExp>/electrical/solar/<RegExp>/location
Description: Installed location of device on vessel

/vessels/<RegExp>/electrical/solar/<RegExp>/dateInstalled
Units: RFC 3339 (UTC) (undefined)

Description: Date device was installed

/vessels/<RegExp>/electrical/solar/<RegExp>/manufacturer
Description: [missing]

/vessels/<RegExp>/electrical/solar/<RegExp>/manufacturer/name
Description: Manufacturer's name

/vessels/<RegExp>/electrical/solar/<RegExp>/manufacturer/model
Description: Model or part number

/vessels/<RegExp>/electrical/solar/<RegExp>/manufacturer/URL
Description: Web referance / URL

/vessels/<RegExp>/electrical/solar/<RegExp>/associatedBus
Description: Name of BUS device is associated with

/vessels/<RegExp>/electrical/solar/<RegExp>/voltage
Units: V (Volt)

Description: Voltage measured at or as close as possible to the device

/vessels/<RegExp>/electrical/solar/<RegExp>/voltage/ripple
Units: V (Volt)

Description: DC Ripple voltage

/vessels/<RegExp>/electrical/solar/<RegExp>/current
Units: A (Ampere)

Description: Current flowing out (+ve) or in (-ve) to the device

/vessels/<RegExp>/electrical/solar/<RegExp>/temperature
Title: temperature

Units: K (Kelvin)

Description: Temperature measured within or on the device

/vessels/<RegExp>/electrical/solar/<RegExp>/chargingAlgorithm
Description: Algorithm being used by the charger

/vessels/<RegExp>/electrical/solar/<RegExp>/chargerRole
Description: How is charging source configured? Standalone, or in sync with another charger?

/vessels/<RegExp>/electrical/solar/<RegExp>/chargingMode
Description: Charging mode i.e. float, overcharge, etc.

/vessels/<RegExp>/electrical/solar/<RegExp>/setpointVoltage
Units: V (Volt)

Description: Target regulation voltage

/vessels/<RegExp>/electrical/solar/<RegExp>/setpointCurrent
Units: A (Ampere)

Description: Target current limit

/vessels/<RegExp>/electrical/solar/<RegExp>/controllerMode
Description: The current state of the engine

/vessels/<RegExp>/electrical/solar/<RegExp>/panelVoltage
Units: V (Volt)

Description: Voltage being supplied from Solar Panels to controller

/vessels/<RegExp>/electrical/solar/<RegExp>/panelCurrent
Units: A (Ampere)

Description: Amperage being supplied from Solar Panels to controller

/vessels/<RegExp>/electrical/solar/<RegExp>/panelTemperature
Units: K (Kelvin)

Description: Temperature of panels

/vessels/<RegExp>/electrical/solar/<RegExp>/load
Description: State of load port on controller (if applicable)

/vessels/<RegExp>/electrical/solar/<RegExp>/loadCurrent
Units: A (Ampere)

Description: Amperage being supplied to load directly connected to controller

/vessels/<RegExp>/electrical/ac
Description: AC buses

/vessels/<RegExp>/electrical/ac/<RegExp>
Title: AC Bus keyed by instance id

Description: AC Bus, one or many, within the vessel

/vessels/<RegExp>/electrical/ac/<RegExp>/name
Description: Unique ID of device (houseBattery, alternator, Generator, solar1, inverter, charger, combiner, etc.)

/vessels/<RegExp>/electrical/ac/<RegExp>/location
Description: Installed location of device on vessel

/vessels/<RegExp>/electrical/ac/<RegExp>/dateInstalled
Units: RFC 3339 (UTC) (undefined)

Description: Date device was installed

/vessels/<RegExp>/electrical/ac/<RegExp>/manufacturer
Description: [missing]

/vessels/<RegExp>/electrical/ac/<RegExp>/manufacturer/name
Description: Manufacturer's name

/vessels/<RegExp>/electrical/ac/<RegExp>/manufacturer/model
Description: Model or part number

/vessels/<RegExp>/electrical/ac/<RegExp>/manufacturer/URL
Description: Web referance / URL

/vessels/<RegExp>/electrical/ac/<RegExp>/phase
Description: Single or A,B or C in 3 Phase systems

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])
Title: AC Qualities

Description: AC equipment common qualities

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/associatedBus
Description: Name of BUS device is associated with

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/lineNeutralVoltage
Units: V (Volt)

Description: RMS voltage measured between phase and neutral

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/lineLineVoltage
Units: V (Volt)

Description: RMS voltage measured between phases

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/current
Units: A (Ampere)

Description: RMS current

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/frequency
Units: Hz (Hertz)

Description: AC frequency.

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/reactivePower
Units: W (Watt)

Description: Reactive power

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/powerFactor
Description: Power factor

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/powerFactorLagging
Description: Lead/lag status.

Enum values:

leading
lagging
error
not available
/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/realPower
Units: W (Watt)

Description: Real power.

/vessels/<RegExp>/electrical/ac/<RegExp>/phase/(single)|([A-C])/apparentPower
Units: W (Watt)

Description: Apparent power.

/vessels/<RegExp>/notifications
Title: notifications

Description: Notifications currently raised. Major categories have well-defined names, but the tree can be extended by any hierarchical structure

/vessels/<RegExp>/notifications/mob
Description: Man overboard

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/fire
Description: Fire onboard

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/sinking
Description: Vessel is sinking

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/flooding
Description: Vessel is flooding

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/collision
Description: In collision with another vessel or object

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/grounding
Description: Vessel grounding

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/listing
Description: Vessel is listing

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/adrift
Description: Vessel is adrift

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/piracy
Description: Under attack or danger from pirates

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/abandon
Description: Abandon ship

Object value with properties

method
state
message
/vessels/<RegExp>/notifications/<RegExp>
Description: This regex pattern is used for validation of the path of the alarm

/vessels/<RegExp>/steering
Title: steering

Description: Vessel steering data for steering controls (not Autopilot 'Nav Data')

/vessels/<RegExp>/steering/rudderAngle
Units: rad (Radian)

Description: Current rudder angle, +ve is rudder to Starboard

/vessels/<RegExp>/steering/rudderAngleTarget
Units: rad (Radian)

Description: The angle the rudder should move to, +ve is rudder to Starboard

/vessels/<RegExp>/steering/autopilot
Title: autopilot

Description: Autopilot data

/vessels/<RegExp>/steering/autopilot/state
Description: Autopilot state

/vessels/<RegExp>/steering/autopilot/mode
Description: Operational mode

/vessels/<RegExp>/steering/autopilot/target
Title: target

Description: Autopilot target

/vessels/<RegExp>/steering/autopilot/target/windAngleApparent
Units: rad (Radian)

Description: Target angle to steer, relative to Apparent wind +port -starboard

/vessels/<RegExp>/steering/autopilot/target/headingTrue
Units: rad (Radian)

Description: Target heading for autopilot, relative to North

/vessels/<RegExp>/steering/autopilot/target/headingMagnetic
Units: rad (Radian)

Description: Target heading for autopilot, relative to Magnetic North

/vessels/<RegExp>/steering/autopilot/deadZone
Units: rad (Radian)

Description: Dead zone to ignore for rudder corrections

/vessels/<RegExp>/steering/autopilot/backlash
Units: rad (Radian)

Description: Slack in the rudder drive mechanism

/vessels/<RegExp>/steering/autopilot/gain
Description: Auto-pilot gain, higher number equals more rudder movement for a given turn

/vessels/<RegExp>/steering/autopilot/maxDriveCurrent
Units: A (Ampere)

Description: Maximum current to use to drive servo

/vessels/<RegExp>/steering/autopilot/maxDriveRate
Units: rad/s (Radian per second)

Description: Maximum rudder rotation speed

/vessels/<RegExp>/steering/autopilot/portLock
Units: rad (Radian)

Description: Position of servo on port lock

/vessels/<RegExp>/steering/autopilot/starboardLock
Units: rad (Radian)

Description: Position of servo on starboard lock

/vessels/<RegExp>/tanks
Title: tanks

Description: Tank data, each tank indentified by a unique name i.e. FreshWater_2

/vessels/<RegExp>/tanks/freshWater
Description: Fresh water tank (drinking)

/vessels/<RegExp>/tanks/freshWater/<RegExp>
Description: Tank, one or many, within the vessel

/vessels/<RegExp>/tanks/freshWater/<RegExp>/name
Description: The name of the tank. Useful if multiple tanks of a certain type are on board

/vessels/<RegExp>/tanks/freshWater/<RegExp>/type
Description: The type of tank

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
/vessels/<RegExp>/tanks/freshWater/<RegExp>/capacity
Units: m3 (Cubic meter)

Description: Total capacity

/vessels/<RegExp>/tanks/freshWater/<RegExp>/currentLevel
Units: ratio (Ratio)

Description: Level of fluid in tank 0-100%

/vessels/<RegExp>/tanks/freshWater/<RegExp>/currentVolume
Units: m3 (Cubic meter)

Description: Volume of fluid in tank

/vessels/<RegExp>/tanks/freshWater/<RegExp>/pressure
Units: Pa (Pascal)

Description: Pressure of contents in tank, especially LPG/gas

/vessels/<RegExp>/tanks/freshWater/<RegExp>/temperature
Units: K (Kelvin)

Description: Temperature of tank, especially cryogenic or LPG/gas

/vessels/<RegExp>/tanks/freshWater/<RegExp>/viscosity
Units: Pa/s (undefined)

Description: Viscosity of the fluid, if applicable

/vessels/<RegExp>/tanks/freshWater/<RegExp>/extinguishant
Description: The preferred extinguishant to douse a fire in this tank

/vessels/<RegExp>/tanks/wasteWater
Description: Waste water tank (grey water)

/vessels/<RegExp>/tanks/wasteWater/<RegExp>
Description: Tank, one or many, within the vessel

/vessels/<RegExp>/tanks/wasteWater/<RegExp>/name
Description: The name of the tank. Useful if multiple tanks of a certain type are on board

/vessels/<RegExp>/tanks/wasteWater/<RegExp>/type
Description: The type of tank

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
/vessels/<RegExp>/tanks/wasteWater/<RegExp>/capacity
Units: m3 (Cubic meter)

Description: Total capacity

/vessels/<RegExp>/tanks/wasteWater/<RegExp>/currentLevel
Units: ratio (Ratio)

Description: Level of fluid in tank 0-100%

/vessels/<RegExp>/tanks/wasteWater/<RegExp>/currentVolume
Units: m3 (Cubic meter)

Description: Volume of fluid in tank

/vessels/<RegExp>/tanks/wasteWater/<RegExp>/pressure
Units: Pa (Pascal)

Description: Pressure of contents in tank, especially LPG/gas

/vessels/<RegExp>/tanks/wasteWater/<RegExp>/temperature
Units: K (Kelvin)

Description: Temperature of tank, especially cryogenic or LPG/gas

/vessels/<RegExp>/tanks/wasteWater/<RegExp>/viscosity
Units: Pa/s (undefined)

Description: Viscosity of the fluid, if applicable

/vessels/<RegExp>/tanks/wasteWater/<RegExp>/extinguishant
Description: The preferred extinguishant to douse a fire in this tank

/vessels/<RegExp>/tanks/blackWater
Description: Black water tank (sewage)

/vessels/<RegExp>/tanks/blackWater/<RegExp>
Description: Tank, one or many, within the vessel

/vessels/<RegExp>/tanks/blackWater/<RegExp>/name
Description: The name of the tank. Useful if multiple tanks of a certain type are on board

/vessels/<RegExp>/tanks/blackWater/<RegExp>/type
Description: The type of tank

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
/vessels/<RegExp>/tanks/blackWater/<RegExp>/capacity
Units: m3 (Cubic meter)

Description: Total capacity

/vessels/<RegExp>/tanks/blackWater/<RegExp>/currentLevel
Units: ratio (Ratio)

Description: Level of fluid in tank 0-100%

/vessels/<RegExp>/tanks/blackWater/<RegExp>/currentVolume
Units: m3 (Cubic meter)

Description: Volume of fluid in tank

/vessels/<RegExp>/tanks/blackWater/<RegExp>/pressure
Units: Pa (Pascal)

Description: Pressure of contents in tank, especially LPG/gas

/vessels/<RegExp>/tanks/blackWater/<RegExp>/temperature
Units: K (Kelvin)

Description: Temperature of tank, especially cryogenic or LPG/gas

/vessels/<RegExp>/tanks/blackWater/<RegExp>/viscosity
Units: Pa/s (undefined)

Description: Viscosity of the fluid, if applicable

/vessels/<RegExp>/tanks/blackWater/<RegExp>/extinguishant
Description: The preferred extinguishant to douse a fire in this tank

/vessels/<RegExp>/tanks/fuel
Description: Fuel tank (petrol or diesel)

/vessels/<RegExp>/tanks/fuel/<RegExp>
Description: Tank, one or many, within the vessel

/vessels/<RegExp>/tanks/fuel/<RegExp>/name
Description: The name of the tank. Useful if multiple tanks of a certain type are on board

/vessels/<RegExp>/tanks/fuel/<RegExp>/type
Description: The type of tank

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
/vessels/<RegExp>/tanks/fuel/<RegExp>/capacity
Units: m3 (Cubic meter)

Description: Total capacity

/vessels/<RegExp>/tanks/fuel/<RegExp>/currentLevel
Units: ratio (Ratio)

Description: Level of fluid in tank 0-100%

/vessels/<RegExp>/tanks/fuel/<RegExp>/currentVolume
Units: m3 (Cubic meter)

Description: Volume of fluid in tank

/vessels/<RegExp>/tanks/fuel/<RegExp>/pressure
Units: Pa (Pascal)

Description: Pressure of contents in tank, especially LPG/gas

/vessels/<RegExp>/tanks/fuel/<RegExp>/temperature
Units: K (Kelvin)

Description: Temperature of tank, especially cryogenic or LPG/gas

/vessels/<RegExp>/tanks/fuel/<RegExp>/viscosity
Units: Pa/s (undefined)

Description: Viscosity of the fluid, if applicable

/vessels/<RegExp>/tanks/fuel/<RegExp>/extinguishant
Description: The preferred extinguishant to douse a fire in this tank

/vessels/<RegExp>/tanks/lubrication
Description: Lubrication tank (oil or grease)

/vessels/<RegExp>/tanks/lubrication/<RegExp>
Description: Tank, one or many, within the vessel

/vessels/<RegExp>/tanks/lubrication/<RegExp>/name
Description: The name of the tank. Useful if multiple tanks of a certain type are on board

/vessels/<RegExp>/tanks/lubrication/<RegExp>/type
Description: The type of tank

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
/vessels/<RegExp>/tanks/lubrication/<RegExp>/capacity
Units: m3 (Cubic meter)

Description: Total capacity

/vessels/<RegExp>/tanks/lubrication/<RegExp>/currentLevel
Units: ratio (Ratio)

Description: Level of fluid in tank 0-100%

/vessels/<RegExp>/tanks/lubrication/<RegExp>/currentVolume
Units: m3 (Cubic meter)

Description: Volume of fluid in tank

/vessels/<RegExp>/tanks/lubrication/<RegExp>/pressure
Units: Pa (Pascal)

Description: Pressure of contents in tank, especially LPG/gas

/vessels/<RegExp>/tanks/lubrication/<RegExp>/temperature
Units: K (Kelvin)

Description: Temperature of tank, especially cryogenic or LPG/gas

/vessels/<RegExp>/tanks/lubrication/<RegExp>/viscosity
Units: Pa/s (undefined)

Description: Viscosity of the fluid, if applicable

/vessels/<RegExp>/tanks/lubrication/<RegExp>/extinguishant
Description: The preferred extinguishant to douse a fire in this tank

/vessels/<RegExp>/tanks/liveWell
Description: Live tank (fish)

/vessels/<RegExp>/tanks/liveWell/<RegExp>
Description: Tank, one or many, within the vessel

/vessels/<RegExp>/tanks/liveWell/<RegExp>/name
Description: The name of the tank. Useful if multiple tanks of a certain type are on board

/vessels/<RegExp>/tanks/liveWell/<RegExp>/type
Description: The type of tank

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
/vessels/<RegExp>/tanks/liveWell/<RegExp>/capacity
Units: m3 (Cubic meter)

Description: Total capacity

/vessels/<RegExp>/tanks/liveWell/<RegExp>/currentLevel
Units: ratio (Ratio)

Description: Level of fluid in tank 0-100%

/vessels/<RegExp>/tanks/liveWell/<RegExp>/currentVolume
Units: m3 (Cubic meter)

Description: Volume of fluid in tank

/vessels/<RegExp>/tanks/liveWell/<RegExp>/pressure
Units: Pa (Pascal)

Description: Pressure of contents in tank, especially LPG/gas

/vessels/<RegExp>/tanks/liveWell/<RegExp>/temperature
Units: K (Kelvin)

Description: Temperature of tank, especially cryogenic or LPG/gas

/vessels/<RegExp>/tanks/liveWell/<RegExp>/viscosity
Units: Pa/s (undefined)

Description: Viscosity of the fluid, if applicable

/vessels/<RegExp>/tanks/liveWell/<RegExp>/extinguishant
Description: The preferred extinguishant to douse a fire in this tank

/vessels/<RegExp>/tanks/baitWell
Description: Bait tank

/vessels/<RegExp>/tanks/baitWell/<RegExp>
Description: Tank, one or many, within the vessel

/vessels/<RegExp>/tanks/baitWell/<RegExp>/name
Description: The name of the tank. Useful if multiple tanks of a certain type are on board

/vessels/<RegExp>/tanks/baitWell/<RegExp>/type
Description: The type of tank

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
/vessels/<RegExp>/tanks/baitWell/<RegExp>/capacity
Units: m3 (Cubic meter)

Description: Total capacity

/vessels/<RegExp>/tanks/baitWell/<RegExp>/currentLevel
Units: ratio (Ratio)

Description: Level of fluid in tank 0-100%

/vessels/<RegExp>/tanks/baitWell/<RegExp>/currentVolume
Units: m3 (Cubic meter)

Description: Volume of fluid in tank

/vessels/<RegExp>/tanks/baitWell/<RegExp>/pressure
Units: Pa (Pascal)

Description: Pressure of contents in tank, especially LPG/gas

/vessels/<RegExp>/tanks/baitWell/<RegExp>/temperature
Units: K (Kelvin)

Description: Temperature of tank, especially cryogenic or LPG/gas

/vessels/<RegExp>/tanks/baitWell/<RegExp>/viscosity
Units: Pa/s (undefined)

Description: Viscosity of the fluid, if applicable

/vessels/<RegExp>/tanks/baitWell/<RegExp>/extinguishant
Description: The preferred extinguishant to douse a fire in this tank

/vessels/<RegExp>/tanks/gas
Description: Lpg/propane and other gases

/vessels/<RegExp>/tanks/gas/<RegExp>
Description: Tank, one or many, within the vessel

/vessels/<RegExp>/tanks/gas/<RegExp>/name
Description: The name of the tank. Useful if multiple tanks of a certain type are on board

/vessels/<RegExp>/tanks/gas/<RegExp>/type
Description: The type of tank

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
/vessels/<RegExp>/tanks/gas/<RegExp>/capacity
Units: m3 (Cubic meter)

Description: Total capacity

/vessels/<RegExp>/tanks/gas/<RegExp>/currentLevel
Units: ratio (Ratio)

Description: Level of fluid in tank 0-100%

/vessels/<RegExp>/tanks/gas/<RegExp>/currentVolume
Units: m3 (Cubic meter)

Description: Volume of fluid in tank

/vessels/<RegExp>/tanks/gas/<RegExp>/pressure
Units: Pa (Pascal)

Description: Pressure of contents in tank, especially LPG/gas

/vessels/<RegExp>/tanks/gas/<RegExp>/temperature
Units: K (Kelvin)

Description: Temperature of tank, especially cryogenic or LPG/gas

/vessels/<RegExp>/tanks/gas/<RegExp>/viscosity
Units: Pa/s (undefined)

Description: Viscosity of the fluid, if applicable

/vessels/<RegExp>/tanks/gas/<RegExp>/extinguishant
Description: The preferred extinguishant to douse a fire in this tank

/vessels/<RegExp>/tanks/ballast
Description: Ballast tanks

/vessels/<RegExp>/tanks/ballast/<RegExp>
Description: Tank, one or many, within the vessel

/vessels/<RegExp>/tanks/ballast/<RegExp>/name
Description: The name of the tank. Useful if multiple tanks of a certain type are on board

/vessels/<RegExp>/tanks/ballast/<RegExp>/type
Description: The type of tank

Enum values:

petrol
fresh water
greywater
blackwater
holding
lpg
diesel
liveWell
baitWell
ballast
rum
/vessels/<RegExp>/tanks/ballast/<RegExp>/capacity
Units: m3 (Cubic meter)

Description: Total capacity

/vessels/<RegExp>/tanks/ballast/<RegExp>/currentLevel
Units: ratio (Ratio)

Description: Level of fluid in tank 0-100%

/vessels/<RegExp>/tanks/ballast/<RegExp>/currentVolume
Units: m3 (Cubic meter)

Description: Volume of fluid in tank

/vessels/<RegExp>/tanks/ballast/<RegExp>/pressure
Units: Pa (Pascal)

Description: Pressure of contents in tank, especially LPG/gas

/vessels/<RegExp>/tanks/ballast/<RegExp>/temperature
Units: K (Kelvin)

Description: Temperature of tank, especially cryogenic or LPG/gas

/vessels/<RegExp>/tanks/ballast/<RegExp>/viscosity
Units: Pa/s (undefined)

Description: Viscosity of the fluid, if applicable

/vessels/<RegExp>/tanks/ballast/<RegExp>/extinguishant
Description: The preferred extinguishant to douse a fire in this tank

/vessels/<RegExp>/design
Title: design

Description: Design/dimensional data of this vessel

/vessels/<RegExp>/design/displacement
Units: kg (Kilogram)

Description: The displacement of the vessel

/vessels/<RegExp>/design/aisShipType
Description: The ais ship type see http://www.bosunsmate.org/ais/message5.php

Object value with properties

id
name
/vessels/<RegExp>/design/draft
Title: draft

Description: The draft of the vessel

Object value with properties

minimum (m)
maximum (m)
current (m)
canoe (m)
/vessels/<RegExp>/design/length
Title: length

Description: The various lengths of the vessel

Object value with properties

overall (m)
hull (m)
waterline (m)
/vessels/<RegExp>/design/keel
Title: keel

Description: Information about the vessel's keel

/vessels/<RegExp>/design/keel/angle
Units: rad (Radian)

Description: A number indicating at which angle the keel currently is (in case of a canting keel), negative to port.

/vessels/<RegExp>/design/keel/lift
Units: ratio (Ratio)

Description: In the case of a lifting keel, centreboard or daggerboard, the part of the keel which is extended. 0 is 'all the way up' and 1 is 'all the way down'. 0.8 would be 80% down.

/vessels/<RegExp>/design/beam
Units: m (Meter)

Description: Beam length

/vessels/<RegExp>/design/airHeight
Units: m (Meter)

Description: Total height of the vessel

/vessels/<RegExp>/design/rigging
Title: rigging

Description: Information about the vessel's rigging

/vessels/<RegExp>/sails
Title: sails

Description: Sails data

/vessels/<RegExp>/sails/inventory
Description: An object containing a description of each sail available to the vessel crew

/vessels/<RegExp>/sails/inventory/<RegExp>
Description: 'sail' data type.

/vessels/<RegExp>/sails/area
Description: An object containing information about the vessels' sails.

/vessels/<RegExp>/sails/area/total
Units: m2 (Square meter)

Description: The total area of all sails on the vessel

/vessels/<RegExp>/sails/area/active
Units: m2 (Square meter)

Description: The total area of the sails currently in use on the vessel

/vessels/<RegExp>/sensors
Title: sensors

Description: Sensors, their state, and data.

/vessels/<RegExp>/sensors/<RegExp>
Title: sensor

Description: This regex pattern is used for validation UUID identifier for the sensor

/vessels/<RegExp>/sensors/<RegExp>/name
Description: The common name of the sensor

/vessels/<RegExp>/sensors/<RegExp>/sensorType
Description: The datamodel definition of the sensor data. FIXME - need to create a definitions lib of sensor datamodel types

/vessels/<RegExp>/sensors/<RegExp>/sensorData
Description: The data of the sensor data. FIXME - need to ref the definitions of sensor types

/vessels/<RegExp>/sensors/<RegExp>/fromBow
Description: The distance from the bow to the sensor location

/vessels/<RegExp>/sensors/<RegExp>/fromCenter
Description: The distance from the centerline to the sensor location, -ve to starboard, +ve to port

/vessels/<RegExp>/performance
Title: performance

Description: Performance Sailing data including VMG, Polar Speed, tack angle, etc.

/vessels/<RegExp>/performance/polarSpeed
Units: m/s (Meters per second)

Description: The current polar speed based on current polar diagram, WindSpeedTrue and angleTrueWater.

/vessels/<RegExp>/performance/polarSpeedRatio
Units: ratio (Ratio)

Description: The ratio of current speed through water to the polar speed.

/vessels/<RegExp>/performance/velocityMadeGood
Units: m/s (Meters per second)

Description: The current velocity made good derived from the speed through water and appearant wind angle. A positive value is heading to upwind, negative to downwind.

/vessels/<RegExp>/performance/velocityMadeGoodToWaypoint
Units: m/s (Meters per second)

Description: The current velocity made good to the next waypoint derived from the speedOverGround, courseOverGround.

/vessels/<RegExp>/performance/beatAngle
Units: rad (Radian)

Description: The true wind beat angle for the best velocity made good based on current current polar diagram and WindSpeedTrue.

/vessels/<RegExp>/performance/beatAngleVelocityMadeGood
Units: m/s (Meters per second)

Description: The velocity made good for the beat angle.

/vessels/<RegExp>/performance/beatAngleTargetSpeed
Units: m/s (Meters per second)

Description: The target speed for the beat angle.

/vessels/<RegExp>/performance/gybeAngle
Units: rad (Radian)

Description: The true wind gybe angle for the best velocity made good downwind based on current polar diagram and WindSpeedTrue.

/vessels/<RegExp>/performance/gybeAngleVelocityMadeGood
Units: m/s (Meters per second)

Description: The velocity made good for the gybe angle

/vessels/<RegExp>/performance/gybeAngleTargetSpeed
Units: m/s (Meters per second)

Description: The target speed for the gybe angle.

/vessels/<RegExp>/performance/targetAngle
Units: rad (Radian)

Description: The true wind gybe or beat angle for the best velocity made good downwind or upwind based on current polar diagram and WindSpeedTrue.

/vessels/<RegExp>/performance/targetSpeed
Units: m/s (Meters per second)

Description: The target speed for the beat angle or gybe angle, which ever is applicable.

/vessels/<RegExp>/performance/leeway
Units: rad (Radian)

Description: Current leeway

/vessels/<RegExp>/performance/tackMagnetic
Units: rad (Radian)

Description: Magnetic heading on opposite tack.

/vessels/<RegExp>/performance/tackTrue
Units: rad (Radian)

Description: True heading on opposite tack.

*/
