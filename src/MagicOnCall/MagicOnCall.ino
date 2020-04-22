/*
 * 
 * Libraries included:
 * Form within Arduino IDE
 * ArduinoJSON
 * External libraries
 * NMEA2000
 * NMEA2000_esp
 * 
 * Versions: 
 * 1.05 Almost working implemention on NMEA for a part form the function 
 * void HandleNMEA2000Msg(const tN2kMsg &N2kMsg) which needs to be commented out as for it to compile
 * 
 * 1.06 Renames the class LED with Relay.h 
 * 
 * 1.07 Add support for IR receiver 
 * 
 * 1.08 Will add support for NMEA-2000 by adding DataDisplay2 for receiving data from the NMEA-2000 network 
 * 
 * 1.09 Will add support for NMEA-2000 by adding 
 * 
 * 1.10 sent off to Christian for review, 
 * 
 * 1.12 Sends Wind from NMEA to webserver
 * 
 * 1.18 Average wind data, more SignalK classes 
 * 
 * 
 */
// ToDo:  Remove IP adress in two places, now commented out 
// Remove ThingSpeak function in WiFi-tab
// move SendHTML to webserver tab
// Please FIX: inconsitant order in the inparameters for different begin functions in the main tab


// Seatalk:   http://boatprojects.blogspot.com/2012/12/beginners-guide-to-raymarines-seatalk.html
// Seatalk:   thomasknauf.de/rap/seatalk2.htm
// https://forum.arduino.cc/index.php?topic=54120.15 
// https://www.vela-navega.com/forum/viewtopic.php?f=14&t=64  // electronic design, optical insulated at high speed 
// NMEA2000:  https://www.yachtd.com/products/
// https://github.com/astuder?tab=stars

// MQTT_MAX_PACKET_SIZE : Maximum packet size
//#ifndef MQTT_MAX_PACKET_SIZE
//#define MQTT_MAX_PACKET_SIZE 256
#define MQTT_MAX_PACKET_SIZE 1256
#undef MQTT_MAX_PACKET_SIZE
#define MQTT_MAX_PACKET_SIZE 512
//#endif


// Max message size calculated by PubSubClient is (MQTT_MAX_PACKET_SIZE < 5 + 2 + strlen(topic) + plength)
#if (MQTT_MAX_PACKET_SIZE -TOPSZ -7) < MIN_MESSZ  // If the max message size is too small, throw a warning at compile time. See PubSubClient.cpp line 359
  #warning "MQTT_MAX_PACKET_SIZE is too small in libraries/PubSubClient/src/PubSubClient.h, increasing it to 1000"
  #undef MQTT_MAX_PACKET_SIZE
  #define MQTT_MAX_PACKET_SIZE 1000
#endif


// Json
//https://arduinojson.org/v6/assistant/

#include "Arduino.h"
#include "Wire.h"
// Libraries for ThingSpeak.com
#include "ThingSpeak.h"
#include "a_personal_daniel.h"
//include "a_personal_generic.h"


// Declaration of functions that handles most of "what will happen" when you control your boat
//void actOnIR(String IRstring);
void actOnJSON(void); 
void actOnReportJSON(void);

// The JSONs are needs to be defined first as they are used in most classes 
// Libraries for Json (Version 6.0 or higher)
#include <ArduinoJson.h> //tested with 6.10.

// JSON definitions for MQTT JSON
const size_t json_capacity_MQTT = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(25) + 80 + 500;
extern StaticJsonDocument<json_capacity_MQTT> mqttJSON;
StaticJsonDocument<json_capacity_MQTT> mqttJSON;

// JSON definitions for reporting JSON
const size_t json_capacity_report = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(15) + 80;
extern StaticJsonDocument<json_capacity_report> reportJSON;
StaticJsonDocument<json_capacity_report> reportJSON;

// JSON definitions for serial JSON
const size_t json_capacity_serial = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(15) + 80;
extern StaticJsonDocument<json_capacity_serial> serialJSON;
StaticJsonDocument<json_capacity_serial> serialJSON;

// JSON definitions for controling JSON
const size_t json_capacity_control = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(15) + 80;
extern StaticJsonDocument<json_capacity_control> controlJSON;
StaticJsonDocument<json_capacity_control> controlJSON;

// To be reomved leagay code 
// JSON definitions for temporary MQTT
//extern const int json_capacity_MINI;
const size_t json_capacity_MINI = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(15) + 80;
//const int json_capacity_MINI = JSON_ARRAY_SIZE(2) + 15*JSON_OBJECT_SIZE(2);
extern StaticJsonDocument<json_capacity_MINI> miniJSON;
StaticJsonDocument<json_capacity_MINI> miniJSON;

// Most classes make use of JSONs so they have to be defined before #include:ing classes 
#include "nmea_classes.h"
Motor motor;
#include "SignalK.h"
extern NMEAenvironment environment;
NMEAenvironment environment;
extern NMEAtanks watertank;
NMEAtanks watertank;
extern NMEAtanks fueltank;
NMEAtanks fueltank;
// extern NMEApropulsion portEngine;
// NMEApropulsion portEngine;
// extern NMEApropulsion starbEngine;
// NMEApropulsion starbEngine;
extern NMEApropulsion engine;
NMEApropulsion engine;


#include "relay.h"
Relay lantern;
Relay decklight;
Relay fan;
Relay outlet;
Relay onboardLED;
Relay blueLED;
Relay greenLED;
Relay redLED;
Relay tableUp;
Relay tableDown;

//#include "dimmer.h"
//Dimmer fan;

// Global variables
//  This varable is needed to make all sensors report their status when the mqtt server send a request to sync to the IoT device.
const boolean status_debug = true; // false; // used for controling status messages to the serial monitor
int mqtt_sync_int = 0;  //  Initialised to zero as to have them all report at startup. 
                        
int switch_counter = 0;  // Defining the counter that helps us execute one slow sensor per main loop in the main function

#define BUF_SIZE  75
char display_1[BUF_SIZE];

float batterylevel = 0.0;
float startbatterylevel = 0.0;
//float batteryvoltage = 0.0;
//float startbatteryvoltage = 0.0;
float temp = 0.0;

// NMEA readouts
uint16_t systemDate = 0;
double systemTime = 0.0;
double SeaTemp = 0.0;

double winds = 0.0;
double windd = 0.0;
double SKwinds = 0.0;
double SKwindd = 0.0;


// Function used in the webserver to publish data
// SendHTML function declaration; 
String  SendHTML(boolean led1stat, boolean led2stat, float batteryvoltage, float temp);

// https://www.tablesgenerator.com/html_tables

String  SendHTML(boolean led1stat, boolean led2stat, float batteryvoltage, float temp) {  
//String  SendHTML(uint8_t led1stat, uint8_t led2stat) {
  String html_meassage = "<!DOCTYPE html> <html>\n";
  html_meassage +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  //html_meassage +="<meta http-equiv=\"refresh\" content=\"2\">\n";  // EDALLAM: this works to refresh
  html_meassage +="<meta http-equiv=\"refresh\" content=\"2; URL=/\">\n";  // EDALLAM: this works to refresh
  html_meassage +="<title>Simply Magic Sailing</title>\n";
  html_meassage +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  html_meassage +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  html_meassage +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  html_meassage +=".button-on {background-color: #3498db;}\n";
  html_meassage +=".button-on:active {background-color: #2980b9;}\n";
  html_meassage +=".button-off {background-color: #34495e;}\n";
  html_meassage +=".button-off:active {background-color: #2c3e50;}\n";
  html_meassage +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  html_meassage +="</style>\n";
  html_meassage +="</head>\n";
  html_meassage +="<body>\n";
  html_meassage +="<h1>Simply Magic</h1>\n";  html_meassage +="<h3>The IoT sailing yacht</h3>\n";  
  
  html_meassage +="<h4>Battery level: " + (String) batteryvoltage  + " volt</h4>\n";
  html_meassage +="<h4>Temperature: " + (String) temp  + " Celsius</h4>\n";
  html_meassage +="<h4>Wind speed: " + (String) winds  + " m/s</h4>\n";
  html_meassage +="<h4>Wind direction: " + (String) windd  + " deg </h4>\n";
  
  html_meassage +="<center><table><tr>\n";
  html_meassage +="<th>Temperature:<br>"    + (String) temp  + " C</th>\n";
  html_meassage +="<th>House battery:<br>"  + (String) batteryvoltage  + " volt</th>\n";
  html_meassage +="<th>Start battery:<br>"  + (String) startbatterylevel  + " volt</th>\n";
  html_meassage +="</tr>\n <tr>\n";  
  html_meassage +="<th>Wind speed:<br> "    + (String) SKwinds  + " knop</td>\n";
  html_meassage +="<th>Wind angle:<br> "    + (String) SKwindd + " deg</td>\n";
  html_meassage +="<th>Speed:<br> "         + (String) temp  + " knop</td>\n";
/*
  html_meassage +="</tr>\n <tr>\n";  
  html_meassage +="<td>3Battery level:<br>" + (String) batteryvoltage  + " volt</td>\n";
  html_meassage +="<td>3House battery:<br>" + (String) batteryvoltage*2.0  + " volt</td>\n";
  html_meassage +="<td>3Start battery:<br>" + (String) batteryvoltage*4.0  + " volt</td>\n";
*/
  html_meassage +="</tr>\n </table></center>\n";


  if (led1stat) //( lantern.state() ) //(led1stat)
//  {html_meassage +="<p>Green LED Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  {html_meassage +="<p>Lanternor: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
//  {html_meassage +="<p>Green LED Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}
  {html_meassage +="<p>Lanternor: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if (led2stat) //( decklight.state() ) //(led2stat)
//  {html_meassage +="<p>Blue LED Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  {html_meassage +="<p>Decklight: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
//  {html_meassage +="<p>Blue LED Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}
  {html_meassage +="<p>Decklight: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  html_meassage +="</body>\n";
  html_meassage +="</html>\n";
  return html_meassage;
}
