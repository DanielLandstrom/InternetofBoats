
// Daniel
// The example code is modified by defining the can pins 
// #define ESP32_CAN_RX_PIN GPIO_NUM_15
// #define ESP32_CAN_TX_PIN GPIO_NUM_5
// to reflect my first refrence design based on ESP32 
// Also this line is changed to ListenAndNode 
//   NMEA2000.SetMode(tNMEA2000::N2km_ListenAndNode,22);  


// Demo: NMEA2000 library. Send battery status to the bus.
//
//
//      In this example are shown ways to minimize the size and RAM usage using two techniques:
//        1) Moving data strictures to PROGMEM vs. using inline constantans when calling a function
//        2) Reducing the size of NMEA CAN buffer to the min needed.  Use caution with this, as some functions
//           (specifically fast packet Messages) require bigger buffer. 
//



#include <Arduino.h>
//#define N2k_CAN_INT_PIN 21

#define ESP32_CAN_RX_PIN GPIO_NUM_15 // This line needs to be before #include <NMEA2000_CAN.h> as to define pin used for CAN/NMEA2000 before including the library
#define ESP32_CAN_TX_PIN GPIO_NUM_2  // This line needs to be before #include <NMEA2000_CAN.h> as to define pin used for CAN/NMEA2000 before including the library

#define N2k_CAN_INT_PIN 21
#include <NMEA2000_CAN.h>       // This will automatically choose right CAN library and create suitable NMEA2000 object
#include <N2kMessages.h>
#include <N2kMessagesEnumToStr.h>


typedef struct {
  unsigned long PGN;
  void (*Handler)(const tN2kMsg &N2kMsg); 
} tNMEA2000Handler;

void HandleNMEA2000Msg(const tN2kMsg &N2kMsg);  

void Wind(const tN2kMsg &N2kMsg);
void SystemTime(const tN2kMsg &N2kMsg);
void Rudder(const tN2kMsg &N2kMsg);
void EngineRapid(const tN2kMsg &N2kMsg);
void EngineDynamicParameters(const tN2kMsg &N2kMsg);
void TransmissionParameters(const tN2kMsg &N2kMsg);
void Speed(const tN2kMsg &N2kMsg);
void WaterDepth(const tN2kMsg &N2kMsg);
void BinaryStatusFull(const tN2kMsg &N2kMsg); // Added by Daniel, May not be needed as the Full version only is used inside the "non-Full"
void BinaryStatus(const tN2kMsg &N2kMsg);
void FluidLevel(const tN2kMsg &N2kMsg);
void OutsideEnvironmental(const tN2kMsg &N2kMsg);
void Temperature(const tN2kMsg &N2kMsg);
void TemperatureExt(const tN2kMsg &N2kMsg);
void DCStatus(const tN2kMsg &N2kMsg);
void BatteryConfigurationStatus(const tN2kMsg &N2kMsg);
void COGSOG(const tN2kMsg &N2kMsg);
void GNSS(const tN2kMsg &N2kMsg);
void Attitude(const tN2kMsg &N2kMsg);
void Heading(const tN2kMsg &N2kMsg);
void Pressure(const tN2kMsg &N2kMsg);



// This was lacking and had to be implemented
//const char* tN2kWindReferenceStrs[] = { "True_North", "Magnetic", "Apparent", "True_boat", "True_water", "Error", "Unavailable" };
//MakeN2kEnumTypeToStrFunc(tN2kWindReference,tN2kWindReferenceStrs)


tNMEA2000Handler NMEA2000Handlers[]={
  {126992L,&SystemTime},
  {127245L,&Rudder },
  {127250L,&Heading},
  {127257L,&Attitude},
  {127488L,&EngineRapid},
  {127489L,&EngineDynamicParameters},
  {127493L,&TransmissionParameters},
  {127501L,&BinaryStatus},
  {127505L,&FluidLevel},
  {127506L,&DCStatus},
  {127513L,&BatteryConfigurationStatus},
  {128259L,&Speed},
  {128267L,&WaterDepth},
  {129026L,&COGSOG},
  {129029L,&GNSS},
  {130306L,&Wind},
  {130310L,&OutsideEnvironmental},
  {130312L,&Temperature},
  {130314L,&Pressure},
  {130316L,&TemperatureExt},
  {0,0}
};


Stream *OutputStream;

extern WindMeter nmeaWind;
WindMeter nmeaWind;
extern Navigation nmeaNav;
Navigation nmeaNav;
extern Boat nmeaBoat;
Boat nmeaBoat;

void nmea2k_setup() {

  // Wind
  nmeaWind.begin("WindMeter", 0, 27000);
  // Navigation (position, estimated position, course, speed, SoG, CoG) 
  nmeaNav.begin("Navigator", 0, 29000);
  // Boat misc that (depth, Sea_temperature, 
  nmeaBoat.begin("Boat", 0, 28000);

  // Initailize motorRPM 
  int rpm = 2900; 
  motor.setRPM(rpm);

  OutputStream=&Serial;
  
  // Set Product information
  // Reserve enough buffer for sending all messages. This does not work on small memory devices like Uno or Mega
  NMEA2000.SetN2kCANSendFrameBufSize(250);
//NMEA2000.SetN2kCANSendFrameBufSize(100);
  NMEA2000.SetProductInformation("00000001", // Manufacturer's Model serial code
                                 100, // Manufacturer's product code
                                 "Message sender example",  // Manufacturer's Model ID
                                 "1.0.0.15 (2017-01-01)",  // Manufacturer's Software version code
                                 "1.0.0.0 (2017-01-01)" // Manufacturer's Model version
                                 );
  // Set device information
  NMEA2000.SetDeviceInformation(1, // Unique number. Use e.g. Serial number.
                                132, // Device function=Analog to NMEA 2000 Gateway. See codes on http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                25, // Device class=Inter/Intranetwork Device. See codes on  http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                2046 // Just choosen free from code list on http://www.nmea.org/Assets/20121020%20nmea%202000%20registration%20list.pdf                               
                               );
  // Uncomment 3 rows below to see, what device will send to bus                           
   // already done in the setup-function in tha main, Serial.begin(115200);
   NMEA2000.SetForwardStream(&Serial);  // PC output on due programming port
   NMEA2000.SetForwardType(tNMEA2000::fwdt_Text); // Show in clear text. Leave uncommented for default Actisense format.
   NMEA2000.SetForwardOwnMessages();

  // If you also want to see all traffic on the bus use N2km_ListenAndNode instead of N2km_NodeOnly below
  //NMEA2000.SetMode(tNMEA2000::N2km_NodeOnly,22);
  NMEA2000.SetMode(tNMEA2000::N2km_ListenAndNode,22); 
  //NMEA2000.SetDebugMode(tNMEA2000::dm_ClearText); // Uncomment this, so you can test code without CAN bus chips on Arduino Mega
  NMEA2000.EnableForward(false); // Disable all msg forwarding to USB (=Serial)

  NMEA2000.SetMsgHandler(HandleNMEA2000Msg);

  NMEA2000.Open();

}


//*****************************************************************************
template<typename T> void PrintLabelValWithConversionCheckUnDef(const char* label, T val, double (*ConvFunc)(double val)=0, bool AddLf=false ) {
  OutputStream->print(label);
  if (!N2kIsNA(val)) {
    if (ConvFunc) { OutputStream->print(ConvFunc(val)); } else { OutputStream->print(val); }
  } else OutputStream->print("not available");
  if (AddLf) OutputStream->println();
}

//*****************************************************************************
void Wind(const tN2kMsg &N2kMsg) {
  
    unsigned char WindInstance;
    double WindSpeed; 
    double WindAngle;
    tN2kWindReference WindReference;
         
    if (ParseN2kWindSpeed(N2kMsg, WindInstance, WindSpeed, WindAngle, WindReference) ) {
      
      nmeaWind.setWindData(WindInstance, WindSpeed, RadToDeg(WindAngle)); // Orginal
      //nmeaWind.setWindData(WindInstance, WindSpeed, WindAngle);
      //environment.setWindData(WindInstance, WindSpeed, RadToDeg(WindAngle));
      environment.setWindData(WindInstance, WindSpeed, WindAngle);
      
      
      PrintLabelValWithConversionCheckUnDef("Wind params: ",WindInstance,0,true);
//                        OutputStream->print("  gear: "); PrintN2kEnumType(TransmissionGear,OutputStream);
      PrintLabelValWithConversionCheckUnDef("  wind speed (m/s): ",WindSpeed,0,true);
      PrintLabelValWithConversionCheckUnDef("  wind angle (deg): ",WindAngle,&RadToDeg,true);
//      PrintLabelValWithConversionCheckUnDef("  wind reference: ",DiscreteStatus1,0,true);
//                         OutputStream->print("  wind reference: "); PrintN2kEnumType(WindReference,OutputStream);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void SystemTime(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    uint16_t SystemDate;
    double SystemTime;
    tN2kTimeSource TimeSource;
    
    if (ParseN2kSystemTime(N2kMsg,SID,SystemDate,SystemTime,TimeSource) ) {
      PrintLabelValWithConversionCheckUnDef("System time: ",SID,0,true);
      PrintLabelValWithConversionCheckUnDef("  days since 1.1.1970: ",SystemDate,0,true);
      PrintLabelValWithConversionCheckUnDef("  seconds since midnight: ",SystemTime,0,true);
                        OutputStream->print("  time source: "); PrintN2kEnumType(TimeSource,OutputStream);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void Rudder(const tN2kMsg &N2kMsg) {
    unsigned char Instance;
    tN2kRudderDirectionOrder RudderDirectionOrder;
    double RudderPosition;
    double AngleOrder;
    
    if (ParseN2kRudder(N2kMsg,RudderPosition,Instance,RudderDirectionOrder,AngleOrder) ) {
      PrintLabelValWithConversionCheckUnDef("Rudder: ",Instance,0,true);
      PrintLabelValWithConversionCheckUnDef("  position (deg): ",RudderPosition,&RadToDeg,true);
                        OutputStream->print("  direction order: "); PrintN2kEnumType(RudderDirectionOrder,OutputStream);
      PrintLabelValWithConversionCheckUnDef("  angle order (deg): ",AngleOrder,&RadToDeg,true);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void EngineRapid(const tN2kMsg &N2kMsg) {
    unsigned char EngineInstance;
    double EngineSpeed;
    double EngineBoostPressure;
    int8_t EngineTiltTrim;
    
    if (ParseN2kEngineParamRapid(N2kMsg,EngineInstance,EngineSpeed,EngineBoostPressure,EngineTiltTrim) ) {
      PrintLabelValWithConversionCheckUnDef("Engine rapid params: ",EngineInstance,0,true);
      PrintLabelValWithConversionCheckUnDef("  RPM: ",EngineSpeed,0,true);
      PrintLabelValWithConversionCheckUnDef("  boost pressure (Pa): ",EngineBoostPressure,0,true);
      PrintLabelValWithConversionCheckUnDef("  tilt trim: ",EngineTiltTrim,0,true);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void EngineDynamicParameters(const tN2kMsg &N2kMsg) {
    unsigned char EngineInstance;
    double EngineOilPress;
    double EngineOilTemp;
    double EngineCoolantTemp;
    double AltenatorVoltage;
    double FuelRate;
    double EngineHours;
    double EngineCoolantPress;
    double EngineFuelPress; 
    int8_t EngineLoad;
    int8_t EngineTorque;
    
    if (ParseN2kEngineDynamicParam(N2kMsg,EngineInstance,EngineOilPress,EngineOilTemp,EngineCoolantTemp,
                                   AltenatorVoltage,FuelRate,EngineHours,
                                   EngineCoolantPress,EngineFuelPress,
                                   EngineLoad,EngineTorque) ) {
      PrintLabelValWithConversionCheckUnDef("Engine dynamic params: ",EngineInstance,0,true);
      PrintLabelValWithConversionCheckUnDef("  oil pressure (Pa): ",EngineOilPress,0,true);
      PrintLabelValWithConversionCheckUnDef("  oil temp (C): ",EngineOilTemp,&KelvinToC,true);
      PrintLabelValWithConversionCheckUnDef("  coolant temp (C): ",EngineCoolantTemp,&KelvinToC,true);
      PrintLabelValWithConversionCheckUnDef("  altenator voltage (V): ",AltenatorVoltage,0,true);
      PrintLabelValWithConversionCheckUnDef("  fuel rate (l/h): ",FuelRate,0,true);
      PrintLabelValWithConversionCheckUnDef("  engine hours (h): ",EngineHours,&SecondsToh,true);
      PrintLabelValWithConversionCheckUnDef("  coolant pressure (Pa): ",EngineCoolantPress,0,true);
      PrintLabelValWithConversionCheckUnDef("  fuel pressure (Pa): ",EngineFuelPress,0,true);
      PrintLabelValWithConversionCheckUnDef("  engine load (%): ",EngineLoad,0,true);
      PrintLabelValWithConversionCheckUnDef("  engine torque (%): ",EngineTorque,0,true);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void TransmissionParameters(const tN2kMsg &N2kMsg) {
    unsigned char EngineInstance;
    tN2kTransmissionGear TransmissionGear;
    double OilPressure;
    double OilTemperature;
    unsigned char DiscreteStatus1;
    
    if (ParseN2kTransmissionParameters(N2kMsg,EngineInstance, TransmissionGear, OilPressure, OilTemperature, DiscreteStatus1) ) {
      PrintLabelValWithConversionCheckUnDef("Transmission params: ",EngineInstance,0,true);
                        OutputStream->print("  gear: "); PrintN2kEnumType(TransmissionGear,OutputStream);
      PrintLabelValWithConversionCheckUnDef("  oil pressure (Pa): ",OilPressure,0,true);
      PrintLabelValWithConversionCheckUnDef("  oil temperature (C): ",OilTemperature,&KelvinToC,true);
      PrintLabelValWithConversionCheckUnDef("  discrete status: ",DiscreteStatus1,0,true);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void Heading(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    tN2kHeadingReference HeadingReference;
    double Heading;
    double Deviation;
    double Variation;
    
    if (ParseN2kHeading(N2kMsg,SID,Heading,Deviation,Variation,HeadingReference) ) {

      nmeaNav.setHeading(Heading, Deviation, Variation);
      //nmeaNav.setHeading(unsigned char SID, tN2kHeadingReference HeadingReference, double Heading, double Deviation, double Variation);
      //nmeaNav.setHeading(SID, HeadingReference, Heading, Deviation, Variation);

    
      PrintLabelValWithConversionCheckUnDef("Heading: ",SID,0,true);
                        OutputStream->print("  reference: "); PrintN2kEnumType(HeadingReference,OutputStream);
      PrintLabelValWithConversionCheckUnDef("  Heading (deg): ",Heading,&RadToDeg,true);
      PrintLabelValWithConversionCheckUnDef("  Deviation (deg): ",Deviation,&RadToDeg,true);
      PrintLabelValWithConversionCheckUnDef("  Variation (deg): ",Variation,&RadToDeg,true);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void COGSOG(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    tN2kHeadingReference HeadingReference;
    double COG;
    double SOG;
    
    if (ParseN2kCOGSOGRapid(N2kMsg,SID,HeadingReference,COG,SOG) ) {
      PrintLabelValWithConversionCheckUnDef("COG/SOG: ",SID,0,true);
                        OutputStream->print("  reference: "); PrintN2kEnumType(HeadingReference,OutputStream);
      PrintLabelValWithConversionCheckUnDef("  COG (deg): ",COG,&RadToDeg,true);
      PrintLabelValWithConversionCheckUnDef("  SOG (m/s): ",SOG,0,true);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void GNSS(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    uint16_t DaysSince1970;
    double SecondsSinceMidnight; 
    double Latitude;
    double Longitude;
    double Altitude; 
    tN2kGNSStype GNSStype;
    tN2kGNSSmethod GNSSmethod;
    unsigned char nSatellites;
    double HDOP;
    double PDOP;
    double GeoidalSeparation;
    unsigned char nReferenceStations;
    tN2kGNSStype ReferenceStationType;
    uint16_t ReferenceSationID;
    double AgeOfCorrection;

    if (ParseN2kGNSS(N2kMsg,SID,DaysSince1970,SecondsSinceMidnight,
                  Latitude,Longitude,Altitude,
                  GNSStype,GNSSmethod,
                  nSatellites,HDOP,PDOP,GeoidalSeparation,
                  nReferenceStations,ReferenceStationType,ReferenceSationID,
                  AgeOfCorrection) ) {
      PrintLabelValWithConversionCheckUnDef("GNSS info: ",SID,0,true);
      PrintLabelValWithConversionCheckUnDef("  days since 1.1.1970: ",DaysSince1970,0,true);
      PrintLabelValWithConversionCheckUnDef("  seconds since midnight: ",SecondsSinceMidnight,0,true);
      PrintLabelValWithConversionCheckUnDef("  latitude: ",Latitude,0,true);
      PrintLabelValWithConversionCheckUnDef("  longitude: ",Longitude,0,true);
      PrintLabelValWithConversionCheckUnDef("  altitude: (m): ",Altitude,0,true);
                        OutputStream->print("  GNSS type: "); PrintN2kEnumType(GNSStype,OutputStream);
                        OutputStream->print("  GNSS method: "); PrintN2kEnumType(GNSSmethod,OutputStream);
      PrintLabelValWithConversionCheckUnDef("  satellite count: ",nSatellites,0,true);
      PrintLabelValWithConversionCheckUnDef("  HDOP: ",HDOP,0,true);
      PrintLabelValWithConversionCheckUnDef("  PDOP: ",PDOP,0,true);
      PrintLabelValWithConversionCheckUnDef("  geoidal separation: ",GeoidalSeparation,0,true);
      PrintLabelValWithConversionCheckUnDef("  reference stations: ",nReferenceStations,0,true);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void OutsideEnvironmental(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    double WaterTemperature;
    double OutsideAmbientAirTemperature;
    double AtmosphericPressure;
    
    if (ParseN2kOutsideEnvironmentalParameters(N2kMsg,SID,WaterTemperature,OutsideAmbientAirTemperature,AtmosphericPressure) ) {
      PrintLabelValWithConversionCheckUnDef("Water temp: ",WaterTemperature,&KelvinToC);
      PrintLabelValWithConversionCheckUnDef(", outside ambient temp: ",OutsideAmbientAirTemperature,&KelvinToC);
      PrintLabelValWithConversionCheckUnDef(", pressure: ",AtmosphericPressure,0,true);
    } else {
      OutputStream->print("Failed to parse PGN: ");  OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void Temperature(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    unsigned char TempInstance;
    tN2kTempSource TempSource;
    double ActualTemperature;
    double SetTemperature;
    
    if (ParseN2kTemperature(N2kMsg,SID,TempInstance,TempSource,ActualTemperature,SetTemperature) ) {
                        OutputStream->print("Temperature source: "); PrintN2kEnumType(TempSource,OutputStream,false);
      PrintLabelValWithConversionCheckUnDef(", actual temperature: ",ActualTemperature,&KelvinToC);
      PrintLabelValWithConversionCheckUnDef(", set temperature: ",SetTemperature,&KelvinToC,true);
    } else {
      OutputStream->print("Failed to parse PGN: ");  OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void Pressure(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    unsigned char Instance;
    tN2kPressureSource PressureSource;
    double ActualPressure;
    
    if ( ParseN2kPressure(N2kMsg,SID,Instance,PressureSource,ActualPressure) ) {
                        OutputStream->print("Pressure source: "); PrintN2kEnumType(PressureSource,OutputStream,false);
      PrintLabelValWithConversionCheckUnDef(", pressure: ",ActualPressure,&PascalTomBar,true);
    } else {
      OutputStream->print("Failed to parse PGN: ");  OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void TemperatureExt(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    unsigned char TempInstance;
    tN2kTempSource TempSource;
    double ActualTemperature;
    double SetTemperature;
    
    if (ParseN2kTemperatureExt(N2kMsg,SID,TempInstance,TempSource,ActualTemperature,SetTemperature) ) {
                        OutputStream->print("Temperature source: "); PrintN2kEnumType(TempSource,OutputStream,false);
      PrintLabelValWithConversionCheckUnDef(", actual temperature: ",ActualTemperature,&KelvinToC);
      PrintLabelValWithConversionCheckUnDef(", set temperature: ",SetTemperature,&KelvinToC,true);
    } else {
      OutputStream->print("Failed to parse PGN: ");  OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void BatteryConfigurationStatus(const tN2kMsg &N2kMsg) {
    unsigned char BatInstance;
    tN2kBatType BatType;
    tN2kBatEqSupport SupportsEqual;
    tN2kBatNomVolt BatNominalVoltage;
    tN2kBatChem BatChemistry;
    double BatCapacity;
    int8_t BatTemperatureCoefficient;
    double PeukertExponent; 
    int8_t ChargeEfficiencyFactor;

    if (ParseN2kBatConf(N2kMsg,BatInstance,BatType,SupportsEqual,BatNominalVoltage,BatChemistry,BatCapacity,BatTemperatureCoefficient,PeukertExponent,ChargeEfficiencyFactor) ) {
      PrintLabelValWithConversionCheckUnDef("Battery instance: ",BatInstance,0,true);
                        OutputStream->print("  - type: "); PrintN2kEnumType(BatType,OutputStream);
                        OutputStream->print("  - support equal.: "); PrintN2kEnumType(SupportsEqual,OutputStream);
                        OutputStream->print("  - nominal voltage: "); PrintN2kEnumType(BatNominalVoltage,OutputStream);
                        OutputStream->print("  - chemistry: "); PrintN2kEnumType(BatChemistry,OutputStream);
      PrintLabelValWithConversionCheckUnDef("  - capacity (Ah): ",BatCapacity,&CoulombToAh,true);
      PrintLabelValWithConversionCheckUnDef("  - temperature coefficient (%): ",BatTemperatureCoefficient,0,true);
      PrintLabelValWithConversionCheckUnDef("  - peukert exponent: ",PeukertExponent,0,true);
      PrintLabelValWithConversionCheckUnDef("  - charge efficiency factor (%): ",ChargeEfficiencyFactor,0,true);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void DCStatus(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    unsigned char DCInstance;
    tN2kDCType DCType;
    unsigned char StateOfCharge;
    unsigned char StateOfHealth;
    double TimeRemaining;
    double RippleVoltage;
    
    if (ParseN2kDCStatus(N2kMsg,SID,DCInstance,DCType,StateOfCharge,StateOfHealth,TimeRemaining,RippleVoltage) ) {
      OutputStream->print("DC instance: ");
      OutputStream->println(DCInstance);
      OutputStream->print("  - type: "); PrintN2kEnumType(DCType,OutputStream);
      OutputStream->print("  - state of charge (%): "); OutputStream->println(StateOfCharge);
      OutputStream->print("  - state of health (%): "); OutputStream->println(StateOfHealth);
      OutputStream->print("  - time remaining (h): "); OutputStream->println(TimeRemaining/60);
      OutputStream->print("  - ripple voltage: "); OutputStream->println(RippleVoltage);
    } else {
      OutputStream->print("Failed to parse PGN: ");  OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
void Speed(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    double SOW;
    double SOG;
    tN2kSpeedWaterReferenceType SWRT;

    if (ParseN2kBoatSpeed(N2kMsg,SID,SOW,SOG,SWRT) ) {
      OutputStream->print("Boat speed:");
      PrintLabelValWithConversionCheckUnDef(" SOW:",N2kIsNA(SOW)?SOW:msToKnots(SOW));
      PrintLabelValWithConversionCheckUnDef(", SOG:",N2kIsNA(SOG)?SOG:msToKnots(SOG));
      OutputStream->print(", ");
      PrintN2kEnumType(SWRT,OutputStream,true);
    }
}

//*****************************************************************************
void WaterDepth(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    double DepthBelowTransducer;
    double Offset;

    if (ParseN2kWaterDepth(N2kMsg,SID,DepthBelowTransducer,Offset) ) {
      if ( N2kIsNA(Offset) ) {
        PrintLabelValWithConversionCheckUnDef("Depth below transducer",DepthBelowTransducer);
        OutputStream->println(", offset not available");
      } else {
        if (Offset>0) {
          OutputStream->print("Water depth:");
        } else {
          OutputStream->print("Depth below keel:");
        }
        if ( !N2kIsNA(DepthBelowTransducer) ) { 
          OutputStream->println(DepthBelowTransducer+Offset); 
        } else {  OutputStream->println(" not available"); }
      }
    }
}

//*****************************************************************************
void printLLNumber(Stream *OutputStream, unsigned long long n, uint8_t base=10)
{
  unsigned char buf[16 * sizeof(long)]; // Assumes 8-bit chars.
  unsigned long long i = 0;

  if (n == 0) {
    OutputStream->print('0');
    return;
  }

  while (n > 0) {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    OutputStream->print((char) (buf[i - 1] < 10 ?
      '0' + buf[i - 1] :
      'A' + buf[i - 1] - 10));
}

//*****************************************************************************

void BinaryStatusFull(const tN2kMsg &N2kMsg) {
    unsigned char BankInstance;
    tN2kBinaryStatus BankStatus;

    if (ParseN2kBinaryStatus(N2kMsg,BankInstance,BankStatus) ) {
      OutputStream->print("Binary status for bank "); OutputStream->print(BankInstance); OutputStream->println(":");
      OutputStream->print("  "); //printLLNumber(OutputStream,BankStatus,16);
      for (uint8_t i=1; i<=28; i++) {
        if (i>1) OutputStream->print(",");
        PrintN2kEnumType(N2kGetStatusOnBinaryStatus(BankStatus,i),OutputStream,false);
      }
      OutputStream->println();
    }
}

//*****************************************************************************
void BinaryStatus(const tN2kMsg &N2kMsg) {
    unsigned char BankInstance;
    tN2kOnOff Status1,Status2,Status3,Status4;

    if (ParseN2kBinaryStatus(N2kMsg,BankInstance,Status1,Status2,Status3,Status4) ) {
      if (BankInstance>2) { // note that this is only for testing different methods. MessageSender.ini sends 4 status for instace 2
        BinaryStatusFull(N2kMsg);
      } else {
        OutputStream->print("Binary status for bank "); OutputStream->print(BankInstance); OutputStream->println(":");
        OutputStream->print("  Status1=");PrintN2kEnumType(Status1,OutputStream,false);
        OutputStream->print(", Status2=");PrintN2kEnumType(Status2,OutputStream,false);
        OutputStream->print(", Status3=");PrintN2kEnumType(Status3,OutputStream,false);
        OutputStream->print(", Status4=");PrintN2kEnumType(Status4,OutputStream,false);
        OutputStream->println();
      }
    }
}




//*****************************************************************************
void FluidLevel(const tN2kMsg &N2kMsg) {
    unsigned char Instance;
    tN2kFluidType FluidType;
    double Level=0;
    double Capacity=0;

    if (ParseN2kFluidLevel(N2kMsg,Instance,FluidType,Level,Capacity) ) {
      switch (FluidType) {
        case N2kft_Fuel:
          OutputStream->print("Fuel level :");
          break;
        case N2kft_Water:
          OutputStream->print("Water level :");
          break;
        case N2kft_GrayWater:
          OutputStream->print("Gray water level :");
          break;
        case N2kft_LiveWell:
          OutputStream->print("Live well level :");
          break;
        case N2kft_Oil:
          OutputStream->print("Oil level :");
          break;
        case N2kft_BlackWater:
          OutputStream->print("Black water level :");
          break;
      }
      OutputStream->print(Level); OutputStream->print("%"); 
      OutputStream->print(" ("); OutputStream->print(Capacity*Level/100); OutputStream->print("l)");
      OutputStream->print(" capacity :"); OutputStream->println(Capacity);
    }
}

//*****************************************************************************
void Attitude(const tN2kMsg &N2kMsg) {
    unsigned char SID;
    double Yaw;
    double Pitch;
    double Roll;
    
    if (ParseN2kAttitude(N2kMsg,SID,Yaw,Pitch,Roll) ) {
      PrintLabelValWithConversionCheckUnDef("Attitude: ",SID,0,true);
      PrintLabelValWithConversionCheckUnDef("  Yaw (deg): ",Yaw,&RadToDeg,true);
      PrintLabelValWithConversionCheckUnDef("  Pitch (deg): ",Pitch,&RadToDeg,true);
      PrintLabelValWithConversionCheckUnDef("  Roll (deg): ",Roll,&RadToDeg,true);
    } else {
      OutputStream->print("Failed to parse PGN: "); OutputStream->println(N2kMsg.PGN);
    }
}

//*****************************************************************************
//NMEA 2000 message handler
//void HandleNMEA2000Msg(const tN2kMsg &N2kMsg);

void HandleNMEA2000Msg(const tN2kMsg &N2kMsg) {
  int iHandler;
  
  // Find handler
  OutputStream->print("In Main Handler: "); OutputStream->println(N2kMsg.PGN);
  for (iHandler=0; NMEA2000Handlers[iHandler].PGN!=0 && !(N2kMsg.PGN==NMEA2000Handlers[iHandler].PGN); iHandler++);
  
  if (NMEA2000Handlers[iHandler].PGN!=0) {
    NMEA2000Handlers[iHandler].Handler(N2kMsg); 
  }
}


void nmea2k_loop() {

  // Serial read a JSON and set its value with motor.set(rpm); dummy int for now
  //int rpm = 2900; 
  //motor.setRPM(rpm);
  
  SendN2kRapidData();
  SendN2kSlowData();
  NMEA2000.ParseMessages();
}

double ReadCabinTemp() {
  return CToKelvin(21.11); // Read here the true temperature e.g. from analog input
}

double ReadWaterTemp() {
  return CToKelvin(15.5); // Read here the true temperature e.g. from analog input
}

#define SlowDataUpdatePeriod 1000

void SendN2kSlowData() {
  static unsigned long SlowDataUpdated=millis();
  tN2kMsg N2kMsg;
  static double Heading=227.5;
  
  // !delay is not good practise withing loops! I use it in this sample since
  // I tested Arduino Mega as receiver without inteerupt and it could not handle all messages
  // send without delay. With interrupt, it can do it and you can set DelayBetweenSend to 0.
  const int DelayBetweenSend=0; 
  
  if ( SlowDataUpdated+SlowDataUpdatePeriod<millis() ) {
    SlowDataUpdated=millis();

    // Daniel: Raymarine sätter Battery2 till 12.7 och Battery2 85%, 1:an indikerar batteri2 (+1) 
    //SetN2kDCBatStatus(N2kMsg, 1, 12.72);
    SetN2kDCBatStatus(N2kMsg, 1, 13.72);
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);

    static unsigned char sid=0;
    //SetN2kPGN127508(N2kMsg, BatteriNummer-1, Spänning, Ström, N2kDoubleNA, sid++);
//    SetN2kDCBatStatus(N2kMsg, 0, 12.45, 5.08, CToKelvin(27.15));
    //SetN2kPGN127508(N2kMsg, 0, 13.8, 0.95, N2kDoubleNA, sid++);
    SetN2kPGN127508(N2kMsg, 0, 13.8, 0.95, CToKelvin(27.15), 25);
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    
    SetN2kTemperatureExt(N2kMsg, 1, 1, N2kts_MainCabinTemperature, ReadCabinTemp(),CToKelvin(21.6));
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);

    SetN2kTemperature(N2kMsg, 1, 1, N2kts_MainCabinTemperature, ReadCabinTemp(),CToKelvin(21.6));
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    
    SetN2kEnvironmentalParameters(N2kMsg, 1, N2kts_MainCabinTemperature, ReadCabinTemp(),N2khs_InsideHumidity, 55, mBarToPascal(1013.5));
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    
    SetN2kOutsideEnvironmentalParameters(N2kMsg, 1, ReadWaterTemp(), CToKelvin(25.3), mBarToPascal(1013.5));
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    
    SetN2kBatConf(N2kMsg,1,N2kDCbt_AGM,N2kDCES_Yes,N2kDCbnv_12v,N2kDCbc_LeadAcid,AhToCoulomb(410),95,1.26,97);
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    
    SetN2kDCStatus(N2kMsg,1,1,N2kDCt_Alternator,86,91,1420,0.21);
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);

    SetN2kAttitude(N2kMsg,1,DegToRad(-3.1),DegToRad(2.4),DegToRad(-7.8));
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);

    SetN2kEngineDynamicParam(N2kMsg,0,656000,CToKelvin(86.3),CToKelvin(82.1),14.21,5.67,hToSeconds(2137.55),N2kDoubleNA,N2kDoubleNA,N2kInt8NA,N2kInt8NA,true);
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    
    SetN2kTransmissionParameters(N2kMsg,0,N2kTG_Forward,750000, CToKelvin(65.5),true,false,true);
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    
    SetN2kSystemTime(N2kMsg,1,17555,62000);
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    
//    SetN2kGNSS(N2kMsg,1,17555,62000,60.1,22.5,10.5,N2kGNSSt_GPS,N2kGNSSm_GNSSfix,12,0.8,0.5,15,1,N2kGNSSt_GPS,15,2);
    SetN2kGNSS(N2kMsg,1,17555,62000,55.6786,12.591,10.5,N2kGNSSt_GPS,N2kGNSSm_GNSSfix,12,0.8,0.5,15,1,N2kGNSSt_GPS,15,2);  //Nyhavn
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);

    SetN2kGNSSDOPData(N2kMsg,1,N2kGNSSdm_Auto,N2kGNSSdm_Auto,1.2,-0.8,N2kDoubleNA);
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    // Serial.print(millis()); Serial.println(", Temperature send ready");

    SetN2kMagneticHeading(N2kMsg, 0, DegToRad(Heading), DegToRad(-3.0), DegToRad(5.5)); 
    delay(DelayBetweenSend); NMEA2000.SendMsg(N2kMsg);
    //Heading+=1; if (Heading>=360.0 ) Heading-=360.0;

    SetN2kAISClassAPosition(N2kMsg, 1, tN2kAISRepeat::N2kaisr_First, 123456789, 26.396, -80.075, 1, 1, 1, 20, 20, 30, 0, tN2kAISNavStatus::N2kaisns_At_Anchor);
    NMEA2000.SendMsg(N2kMsg);

    SetN2kBinaryStatus(N2kMsg,2,N2kOnOff_On,N2kOnOff_Unavailable,N2kOnOff_Off);
    NMEA2000.SendMsg(N2kMsg);

    SetN2kPressure(N2kMsg,0,2,N2kps_Atmospheric,mBarToPascal(1024));
    NMEA2000.SendMsg(N2kMsg);

    SetN2kRudder(N2kMsg,DegToRad(10),1,N2kRDO_MoveToStarboard,DegToRad(-10));
    NMEA2000.SendMsg(N2kMsg);

    tN2kBinaryStatus SwitchBoard;
    N2kResetBinaryStatus(SwitchBoard);
    N2kSetStatusBinaryOnStatus(SwitchBoard,N2kOnOff_On,7);
    SetN2kBinaryStatus(N2kMsg,3,SwitchBoard);
    NMEA2000.SendMsg(N2kMsg);
  }
}

#define RapidDataUpdatePeriod 167 // Some strange periot to cause Slow and rapid to run unsync.

void SendN2kRapidData() {
  static unsigned long RapidDataUpdated=millis();
  tN2kMsg N2kMsg;

  if ( RapidDataUpdated+RapidDataUpdatePeriod<millis() ) {
    RapidDataUpdated=millis();

    // 3 rows below added by daniel
    //int analogreading = analogRead(33);
    //double RPM = map(analogreading, 0, 1023, 0, 50000)/10.0;
    //SetN2kEngineParamRapid(N2kMsg,0,RPM); //,820000,48);
    SetN2kEngineParamRapid(N2kMsg,0, (double) motor.readRPM()*1.0); // double HztoRPM(engine.getRevolutions()); }
    //SetN2kEngineParamRapid(N2kMsg,0,4350); //,820000,48);
    NMEA2000.SendMsg(N2kMsg);
    SetN2kCOGSOGRapid(N2kMsg,1,N2khr_true,DegToRad(115.6),0.1);
    NMEA2000.SendMsg(N2kMsg);
  }
}
