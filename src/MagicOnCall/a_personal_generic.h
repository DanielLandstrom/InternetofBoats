/*
// Personal data 
// All personal data stored in one file as to avoid exposing this information when sharing code (just avoid sharing this file) 

#include "Arduino.h"

// ThingSpeak.com
// Instruction: Create an account at ThingSpeak.com and add your Channel_ID  and Write_API_Key to the variabels below
#define THINGSPEAK              "DEFINED" // Uncomment this line, will define THINGSPEAK, and enable functionality to report your data to your ThingSpeak channel
#define THINGSPEAK_CH_ID        000000  // replace 0000000 with your channel number
#define THINGSPEAK_WRITE_APIKEY "ZO2LKEBDJVV1BQBQ"   // replace XYZ with your channel write API Key = THINGSPEAK_WRITE_APIKEY;


//#ifndef MQTT
#define MQTT               "DEFINED" // Uncomment this line, will define MQTT, and enable functionality to report your data to your over MQTT
#define MQTT_CLIENT_NAME   "MagicOnCall_home"  // Needs to be uniqe for the devise as to not confuse the MQTT server (consider adding the MAC-adress)
#define MQTT_TOPIC_DATA    "MagicOnCall/data"     // Topic used for publishing data 
#define MQTT_TOPIC_STATUS  "edallam/MagicOnCall/status"   // Topic used for indicating status for a device 
#define MQTT_TOPIC_CONTROL "MagicOnCall/#"
//#define MQTT_TOPIC_CONTROL "MagicOnCall/control"  // Topic used for controling a device (subscribing)

#define MQTT_SUB_PREFIX   "MagicOnCall/"   // this one is used in the q_mqtt function and must be simmilar to MQTT_TOPIC_CONTROL
#define MQTT_PHONE        "owntracks/ErONE/Phone"
//#endif


//The MKRNB lib needs this even if its blank
const char PINNUMBER[]        = "";  // PIN code  for the sim card
//const char PINNUMBER[]      = "1178";

//==============================================
// MQTT Settings
//==============================================
#define TOKEN ""
//const char mqttClientName[]   = MQTT_CLIENT_NAME + (String) WiFi.macAddress();
//const char mqttClientName[50]   = "NB-IoT_TrashCan"; // add  WiFi.macAdress as to make sure it becomes uniq

//var things for storage
char payload[100];
//char topic[150];
//char topicPublish[150];

char topicPublish[150] = "IoT_Can/data"; // should we make these const
char topicStatus[150]  = "IoT_Can/status"; // should we make these const
char topicSubscribe[100];

//change this value to subscribe to a different topic
char subtopic[50] = "IoT_Can/#";
////////////////////////////////////////////////
////////////////////////////////////////////////





class Personal {
  
  private:
    boolean _debug = false; // Needed for all sensors 

  public:
  
    // Personal parameters
    // WiFi
//    const char* wifi_ssid     = "Telia-7F7C4";
//    const char* wifi_password = "A38F72E4B";

//#define SECRET_SSID "Telia-774C4"    // replace MySSID with your WiFi network name
//#define SECRET_PASS "A38F724DB"    // replace MyPassword with your WiFi password


    
    // MQTT
    //const char mqttClientName[]   = MQTT_CLIENT_NAME + (String) WiFi.macAddress();
    const char mqttClientName[50]   = MQTT_CLIENT_NAME; // ToDo: Add  WiFi.macAdress as to make sure it becomes uniqe

    //char mqttServer[]       = "iot.eclipse.org";  // Free open MQTT server 
    //char mqttServer[]       = "192.192.76.56";
    const char* mqttServer    = "192.192.76.56";
    int   mqttPort            = 1883;
    char  mqttUser[20]        = "EONE";    // Username for the MQTT server 
    char  mqttPassword[30]    = "Garage";  // Password for the MQTT server 
    //char  mqttUser[20]        = "edm";
    //char  mqttPassword[30]    = "a3f3"; 

    // ThingSpeak

    Personal(void) {
      this->_debug = false;
    }

};

Personal personalData;
*/
