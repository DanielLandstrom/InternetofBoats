//Litterature
//https://pubsubclient.knolleary.net/api.html#publish2

// ToDo 
/*
subtopic should be like MagicOnCall/incomming/control
and pubtopic MagicOnCall/data 
So one can subscribe to MagicOnCall/incomming/#  and not get the outgoing data back (twice the data used)


*/

//==============================================
// MQTT Settings
//==============================================
const boolean mqtt_debug = true; 
//const boolean mqtt_debug = false; 

// libraries
#include <Arduino.h>
#include <SPI.h>
#include <PubSubClient.h>

//Attach the MQTT instance (PubSub client) to one internet conncetion
PubSubClient mqttClient(wifiClient);    // for Wifi
//PubSubClient mqttClient(nbClient);    // for a NB-IoT modem

//mqttClient.setServer(mqtt_server, 1883);
//mqttClient.setCallback(callback);

void mqttpublishSync()
{
  //mqttClient.publish(MQTT_TOPIC_STATUS,"online");
  //checkLock(0);
}

// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

//int mqtt_sync_int = 1;
void callback(char* topic, byte* payload, unsigned int length)
// Callback function for subscribed data from MQTT server
{
  String mqttSubPrefix = MQTT_SUB_PREFIX ; 
  int topicNr = 3;

  // Convert payload to a string
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);

  if (mqtt_debug) {
    Serial.println("MQTT Topic:   " + String(topic) );
    Serial.println("MQTT Payload: " + String(message) );
  };
  
  bool emptyString = false;

  String mqttPhone = MQTT_PHONE ; 
  
  if (String((char)payload[0]) == String(" ")) // If Text starts with space character
  {                                           // then create an Empty string
    emptyString = true;
  }

  if (String(topic) == String(mqttSubPrefix + "text"))
  {
    topicNr = 1;
  }
  if (String(topic) == String(mqttSubPrefix + "control"))
  {
    topicNr = 2;
    DeserializationError err = deserializeJson(controlJSON, p);
    if (mqtt_debug) {
      Serial.println();
      serializeJsonPretty(controlJSON, Serial);
      Serial.println();
      Serial.println("is now placed in controlJSON and now processed by actOnJSON();");
    }
    actOnJSON();

    
  }
  if (String(topic) == String(mqttSubPrefix + "sync"))
  {
    topicNr = 3;
    mqtt_sync_int = 0;    // Setting the multiplicative factor to zero so that all sensors report their data
    switch_counter = 0;   // reseting switch_counter so all sensors get checked before sending the compleat data over MQTT 
  }
  if (String(topic) == String(mqttSubPrefix + "status"))
  {
    topicNr = 3;
    mqtt_sync_int = 0;
    switch_counter = 0;   
    if ((payload[0] == 's') && (payload[1] == 'y') && (payload[2] == 'n') && (payload[3] == 'c')) {
      mqttpublishSync();
    }
  }
  if (String(topic) == String(mqttSubPrefix + "LEDdisplay/text"))
  {
    topicNr = 1;
  }
  
  if (String(topic) == String(mqttSubPrefix + "greenLED"))
  {
    topicNr = 3;
    if ((payload[0] == 'o') && (payload[1] == 'n')) { // on: 
      greenLED.on();
    }
    if ((payload[0] == 'o') && (payload[1] == 'f')) { // off: 
      greenLED.off();
    }
    if ((payload[0] == 'f') && (payload[1] == 'l')) { // flash: 
      greenLED.flash();
    }
    if ((payload[0] == 'q') && (payload[1] == 'u')) { // quickflash: 
      greenLED.quickflash();
    }
    if ((payload[0] == 's') && (payload[1] == 'l')) { // slowflash: 
      greenLED.slowflash();
    }

    if ((payload[0] == 'l') && (payload[1] == 'e')) { // level: 
      greenLED.setCommand(message); // input a json of just set the level ?? blueLED.setLevel(50);
    }
  }
  
  if (String(topic) == String(mqttSubPrefix + "blueLED"))
  {
    topicNr = 3;
    if ((payload[0] == 'o') && (payload[1] == 'n')) { // on: 
      blueLED.on();
    }
    if ((payload[0] == 'o') && (payload[1] == 'f')) { // off: 
      blueLED.off();
    }
    if ((payload[0] == 'f') && (payload[1] == 'l')) { // flash: 
      blueLED.flash();
    }
    if ((payload[0] == 'q') && (payload[1] == 'u')) { // quickflash: 
      blueLED.quickflash();
    }
    if ((payload[0] == 's') && (payload[1] == 'l')) { // slowflash: 
      blueLED.slowflash();
    }

    if ((payload[0] == 'l') && (payload[1] == 'e')) { // level: 
      blueLED.setCommand(message); // input a json of just set the level ?? blueLED.setLevel(50);
    }
  }

    if (String(topic) == String(mqttSubPrefix + "redLED"))
  {
    topicNr = 3;
    if ((payload[0] == 'o') && (payload[1] == 'n')) { // on: 
      redLED.on();
    }
    if ((payload[0] == 'o') && (payload[1] == 'f')) { // off: 
      redLED.off();
    }
    if ((payload[0] == 'f') && (payload[1] == 'l')) { // flash: 
      redLED.flash();
    }
    if ((payload[0] == 'q') && (payload[1] == 'u')) { // quickflash: 
      redLED.quickflash();
    }
    if ((payload[0] == 's') && (payload[1] == 'l')) { // slowflash: 
      redLED.slowflash();
    }
    if ((payload[0] == 'l') && (payload[1] == 'e')) { // level: 
      redLED.setCommand(message); // input a json of just set the level ?? blueLED.setLevel(50);
    }
  }

  if (String(topic) == String(mqttSubPrefix + "onboardLED"))
  {
    topicNr = 3;
    if ((payload[0] == 'o') && (payload[1] == 'n')) { // on: 
      onboardLED.on();
    }
    if ((payload[0] == 'o') && (payload[1] == 'f')) { // off: 
      onboardLED.off();
    }
    if ((payload[0] == 'l') && (payload[1] == 'e')) { // level: 
      onboardLED.setCommand(message); // input a json of just set the level ?? blueLED.setLevel(50);
    }
  }
  
  switch(topicNr)
  {

    case 1: // Display 1
      if (!emptyString)
      {
        strcpy(display_1, "1: ");  // Add display number to beginning of string
        for (int i = 0; i < length ; i++)  // Add string
        {
          display_1[i + 3] = (char)payload[i];
        }
        display_1[length + 3] = ' ';
        display_1[length + 4] = '\0';
      }
      else
      {
        display_1[0] = ' ';
        display_1[1] = '\0';
      }
      break;
      
    case 2:  //Display 2
      break;

    case 3:  //  Display 3
      break;

    default:
      break;
  }
}


//connection and reconnection function for MQTT
void mqttReconnect() {
    while (!mqttClient.connected()) {
    
    // Attemp to connect
    if (mqttClient.connect(MQTT_CLIENT_NAME, personalData.mqttUser, personalData.mqttPassword, MQTT_TOPIC_STATUS, 0, 1, "offline")) {   
      //Updated
      if (status_debug) { Serial.println(" - MQTT Connected"); }
      // Once connected, publish an announcement...
      int len = strlen("online") + 1;
      //mqttClient.publish(MQTT_TOPIC_STATUS, "online", len, true);
      mqttClient.publish(MQTT_TOPIC_STATUS, "online", true);  
      // ... and resubscribe
      mqttClient.subscribe(MQTT_TOPIC_CONTROL); 
    } else { 
      if (status_debug) {  
        Serial.print("MQTT connection failed, rc= ");
        Serial.print(mqttClient.state());
        Serial.println(" try again in 2 seconds");
      }
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}
