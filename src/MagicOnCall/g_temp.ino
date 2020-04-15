// Litterature:
//https://randomnerdtutorials.com/esp32-multiple-ds18b20-temperature-sensors/
//https://lastminuteengineers.com/multiple-ds18b20-arduino-tutorial/

// Libraries for DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

boolean temp_debug = true; // Needed for all sensors
//boolean temp_debug = false; // Needed for all sensors

// DS18B20 init
#define DS18B20_ONE_WIRE_BUS 2
OneWire DS18B20_oneWire(DS18B20_ONE_WIRE_BUS);
DallasTemperature DS18B20_sensors(&DS18B20_oneWire);
DeviceAddress DS18B20_Thermometer[10];
// variable to hold device addresses
DeviceAddress Thermometer;

int DS18B20_deviceCount = 0;
unsigned long  DS18B20_readingIntervalTimer = 0;
float DS18B20_lastReadValue;
float DS18B20_lastReportedValue = 0.0; 
unsigned long DS18B20_postingIntervalDelay = 29 * 1000; //Read and post the temperature every second second.
unsigned long DS18B20_postingIntervalTimer = 0;

void DS18B20_begin(void);
float DS18B20_read(void);
void Temperature_check(float DS18B20_diff);

void DS18B20_begin(void)
{
  DS18B20_sensors.begin();
  //DS18B20_postingIntervalTimer = millis();
}
 
/*
void DS18B20_printAddress(DeviceAddress deviceAddress)
{ 
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println("");
}
*/

float DS18B20_read(void)
{
  if (millis()- DS18B20_readingIntervalTimer < 1000) // Check temperature no more often than twise per second 
  {
     return DS18B20_lastReadValue;
  }
  else
  {
      DS18B20_deviceCount = DS18B20_sensors.getDeviceCount();
      if (temp_debug) {
          Serial.println("Found " + (String) DS18B20_deviceCount + " temperature sensors.");
      } 
      DS18B20_sensors.requestTemperatures();
      float temp; 
      //float tempC;
      for (int i = 0; i < DS18B20_deviceCount; i++)
      {
        DS18B20_sensors.getAddress(DS18B20_Thermometer[i], i);
        if (temp_debug) {
          Serial.print((String)"Thermometer[" + i + "] adress ");
          //DS18B20_printAddress(DS18B20_Thermometer[i]);
        }
        temp =  DS18B20_sensors.getTempC(DS18B20_Thermometer[i]);
        if (temp_debug) {
          Serial.println((String) "Temp[" + i + "]: " + (String) temp);
        } 

        
        //tempC = sensors.getTempCByIndex(i);
        //Serial.print(tempC);
        //Serial.print((char)176);//shows degrees character
        //Serial.print("C  |  ");

      }
      DS18B20_readingIntervalTimer = millis();
      DS18B20_lastReadValue = temp;
    
      return temp;
  }
}

void Temperature_check(float DS18B20_diff = 0.1)
{
  float temp = DS18B20_read();
  if ((millis() - DS18B20_postingIntervalTimer > DS18B20_postingIntervalDelay) || 
      (fabs(temp - DS18B20_lastReportedValue) >= DS18B20_diff ))
  {
    mqttJSON["temp"] = temp; 
    ThingSpeak.setField(5, temp);
    DS18B20_postingIntervalTimer = millis();
    DS18B20_lastReportedValue = temp;
  }
}


/*
int deviceCount = 0;
float tempC;

void test(void)
{
  sensors.begin();  // Start up the library
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
}

void loop(void)
{ 
  // Send command to all the sensors for temperature conversion
  sensors.requestTemperatures(); 
  
  // Display temperature from each sensor
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
    Serial.print((char)176);//shows degrees character
    Serial.print("C  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print((char)176);//shows degrees character
    Serial.println("F");
  }
*/
