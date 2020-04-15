#define MAIN_COMPUTER true
// Here you instansiate all the component/classes you have in your project
// ------ Inputs 
Binary landstrom;
Binary pir;
Binary water;
Binary fuse1;
Binary fuse2;
//Binary fuse3;
Battery mainBattery;
Battery startBattery;
//Battery esp32Battery;
Touch touch;
Hall hall;
Light light;

// ------ Outputs 
// LED is replaced by Relay from version 1.06
//LED onboardLED; // Needed to be defined before MQTT as they are used in the callback function
//LED blueLED;    // Needed to be defined before MQTT as they are used in the callback function
//LED greenLED;   // Needed to be defined before MQTT as they are used in the callback function
//LED redLED;     // Needed to be defined before MQTT as they are used in the callback function   

// ------ Virtual
serialData mainBatterySerial;
serialData startBatterySerial;
serialData mainCurrent;
serialData heaterCurrent;

// ------ NMEA based


// Setup of paramters for ThingSpeak
unsigned long myChannelNumber = THINGSPEAK_CH_ID;     // This is defined in "Personal"
const char * myWriteAPIKey = THINGSPEAK_WRITE_APIKEY; // This is defined in "Personal"
unsigned long TS_postingIntervalDelay = 27 * 1000;    // Intervall Timer for how often to post data to ThingSpeak 
unsigned long TS_postingIntervalTimer = 0;            // Time when data was last sent to ThingSpeak 

unsigned long ALARM_postingIntervalDelay = 3 * 1000;  // Intervall Timer for how often to post alarms 
unsigned long ALARM_postingIntervalTimer = 0;         // Time when last alarm was sent  


// Global message buffers for Serial functions
#define BUF_SIZE  275
char newMessage[BUF_SIZE];
bool newMessageAvailable = false;

void readSerial(void)
{
  static uint8_t  putIndex = 0;
  static uint8_t  bracketCount = 0;
  boolean jsonEnd = false;

  while (Serial2.available())
  {
    newMessage[putIndex] = (char)Serial2.read();
    if (newMessage[putIndex] == '{') {bracketCount++;}
    if (((bracketCount == 1) && (newMessage[putIndex] == '}')) || (bracketCount >= 255) ) {jsonEnd = true;} // end if we find the last bracket or if it wrapped around due to missing the starting bracket 
    if (newMessage[putIndex] == '}') {bracketCount--;}
    if (jsonEnd || (newMessage[putIndex] == '\n') || (putIndex >= BUF_SIZE-3)) // end of message character or full buffer
    {
      // put in a message separator and end the string
//      newMessage[putIndex++] = ' ';
//      newMessage[putIndex] = '\0';
      putIndex++;
      newMessage[putIndex] = ' ';
      putIndex++;
      newMessage[putIndex] = '\0';
      // restart the index for next filling spree and flag we have a message waiting
      putIndex = 0;
      jsonEnd = false; 
      newMessageAvailable = true;
      break;
    }
    else if (newMessage[putIndex] != '\r')
      // Just save the next char in next location
      putIndex++;
  }
  //Serial.println("J:=" + (String) newMessage + "=");  
}

/*
void readSerial(void)
{
  static uint8_t  putIndex = 0;

  while (Serial2.available())
  {
    newMessage[putIndex] = (char)Serial2.read();
    if ((newMessage[putIndex] == '\n') || (putIndex >= BUF_SIZE-3)) // end of message character or full buffer
    {
      // put in a message separator and end the string
      newMessage[putIndex++] = ' ';
      newMessage[putIndex] = '\0';
      // restart the index for next filling spree and flag we have a message waiting
      putIndex = 0;
      newMessageAvailable = true;
    }
    else if (newMessage[putIndex] != '\r')
      // Just save the next char in next location
      putIndex++;
  }
}
*/

//====================== start of IR receiver ==========================
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>
// Based on the example IRrecvDumpV2 in library IRremoteESP8266 . Read the details there.
extern const boolean IRdebug; 
const boolean IRdebug = true; 
//const uint16_t kRecvPin = 14;
const uint16_t IRpin = 23; // 14;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 15;
const uint16_t kMinUnknownSize = 12;
IRrecv irrecv(IRpin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results
//====================== start of IR receiver ==========================

// Pins to be used for the extra Serial port which communicates between micro-computers 
#define RXD2 16
#define TXD2 17
 
void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200); delay(2000);  // Delay to make the Serial warm up correctly
  //Serial.begin(9600);    delay(2000);  // Delay to make the Serial warm up correctly
  
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  if (status_debug) { 
    Serial.println("Extra Serial Txd is on pin: "+String(TXD2));
    Serial.println("Extra Serial Rxd is on pin: "+String(RXD2));
  }

  // IR receiver
  irrecv.setUnknownThreshold(kMinUnknownSize);
  irrecv.enableIRIn();  // Start the receiver      

  if (status_debug) { 
    Serial.println(" ");
    Serial.println((String) personalData.wifi_ssid );   // This is defined in "Personal"
    Serial.println((String) personalData.mqttUser );    // This is defined in "Personal"
  }
  
  Display_setup();
  Display_welcome();
  //Dabble.begin("SimplyMagic");       //set bluetooth name of your device when controlled via Dabble

// Start MOTOR RPM ============================================================================================

  pinMode(interruptPin, INPUT_PULLUP);                                            // sets pin high
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING); // attaches pin to interrupt on Falling Edge
  timer = timerBegin(0, 80, true);                                                // this returns a pointer to the hw_timer_t global variable
                                                                                  // 0 = first timer
                                                                                  // 80 is prescaler so 80MHZ divided by 80 = 1MHZ signal ie 0.000001 of a second
                                                                                  // true - counts up
  timerStart(timer);                                                              // starts the timer

  // configure PWM functionalities
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPin, ledChannel);

// End   MOTOR RPM ============================================================================================


// ------ Inputs 
  pir.begin(39, false, "pir", 4, 29000);  // Please FIX: inconsistant order in the inparameters for different begin functions
  landstrom.begin(36, true, "landstrom", 3, 27000);
  
//  water.begin(34, true, "water", 5, 27000);
  fuse1.begin(26, true, "fuse1", 0, 27000);
  fuse2.begin(25, true, "fuse2", 0, 27000);
//  fuse3.begin(26, true, "fuse3", 0, 27000);
  mainBattery.begin(32,"mainBattery",1);
  startBattery.begin(33,"startBattery",2);
//  esp32Battery.begin(35,"internalBattery");
  touch.begin(T0,"touch",31000);  // T0 is pin 4
  hall.begin();
  light.begin(34,32000);

/*  
// ------ Outputs 
#if MAIN_COMPUTER
  //This is to be used on the main computer as to mimic the Digital Switching computer 
  lantern.begin(0, "lant", 27000, true);
  decklight.begin(0, "deckl", 27000, true);
  fan.begin(0, "fan", 27000, true);
  outlet.begin(0, "outl", 27000, true);
//  mainBattery.begin( 0,false,"mBat");
//  startBattery.begin(0,false,"sBat"); 
//  esp32Battery.begin(0,false,"iBat");

#else   // not MAIN_COMPUTER  
  // This is to be used for the secondary computer (Digital Switching computer) 
*/
  lantern.debug(26, true, "lant", 27000, true);  // This output is on a secondary microcontroller controlled over serial, 
//  lantern.debug(27, true, "lant", 27000, true);  // This output is on a secondary microcontroller controlled over serial, 
                                                    // it will report back its state to the main computer as to have that recorded in the 
                                                    // virtual version of this output (that mimics the real one in terms of states)
                                                    // as to be able to post questions to the virtual one on the main computer 
                                                    // as it was the real one 
                                                    // The virtual one has pin defined as 0 (zero) to indicate "no pin"
  decklight.begin(14, true, "deckl", 27000, true);
  fan.begin(13, true, "fanV", 27000, true);
  outlet.begin(12, true, "outl", 27000, true);

  mainBattery.begin( 32,true,"mBat");
  startBattery.begin(33,true,"sBat"); 
//  esp32Battery.begin(35,true,"iBat");
//#endif  // MAIN_COMPUTER
 
/*
// This is to be used for the secondary computer (Digital Switching computer) 
  lantern.debug(12, false, "lant", 27000, true);  // This output is on a secondary microcontroller controlled over serial, 
                                                    // it will report back its state to the main computer as to have that recorded in the 
                                                    // virtual version of this output (that mimics the real one in terms of states)
                                                    // as to be able to post questions to the virtual one on the main computer 
                                                    // as it was the real one 
                                                    // The virtual one has pin defined as 0 (zero) to indicate "no pin"
  decklight.begin(13, false, "deckl", 27000, true);
  fan.begin(25, false, "fanV", 27000, true);
  outlet.begin(26, false, "outl", 27000, true);
*/
  onboardLED.debug(LED_BUILTIN, "onboardLED", 27000, true); 
  blueLED.begin(19, "blueLED", 27000, false);
  greenLED.begin(18, "greenLED", 29000, false);
  redLED.begin(5, "redLED");

  //tableUp.debug(13, "tableUp");
  //tableDown.debug(14, "tableDown");


// ------ Virtual
// This is to be used on the main computer as to mimic the Digital Switching computer 
  //lantern.begin(0, "lant", 27000, true);
  //decklight.begin(0, "deckl", 27000, true);
  //fan.begin(0, "fan", 27000, true);
  //outlet.begin(0, "outl", 27000, true);
// This is to be used on the main computer as to mimic the Landström computer 
  // to be replaced with a battery class that also handles virtual-sensors that report via serial 
  mainBatterySerial.begin("mBat_serial");
  startBatterySerial.begin("sBat_serial");
  mainCurrent.begin("Cur1");
  heaterCurrent.begin("Cur2");
// This is to be used on the main computer as to mimic the Motor observer computer   
  motor.begin("motor", 27000);

// ------ NMEA based
  // now setup within the function nmea2k_setup(); below
  // SignalK alike
  environment.begin("environment", 0, 28000);
  watertank.begin("watertank", 0, 30000);
  fueltank.begin("fueltank", 0, 31000);
  // portEngine.begin("Bmotor", 0, 31500);
  // starbEngine.begin("Smotor", 0, 31500);
  engine.begin("motor", 0, 31500);
 

  DS18B20_begin();
//  DISTANCE_setup();
//  LOCK_setup();
//  touch.test();

#if MAIN_COMPUTER
  //Network
  wifiReconnect();
  if (status_debug) { Serial.println((String) "Setup MQTT"); }
  mqttClient.setServer(personalData.mqttServer, personalData.mqttPort);
  mqttClient.setCallback(callback);
  mqttReconnect();

  ThingSpeak.begin(wifiClient);  // Initialize ThingSpeak

  //webserver
  webServer_setup();
  
  Display_welcome();
  lcd.setCursor(0,2);
//  lcd.print("Wind: " + environment.getWindSpeedApparent().toString() + " " + environment.getWindAngleApparent().toString() + "deg");
//  lcd.print("Wind: " + (String)environment.getWindSpeedApparent() + " " + (String)environment.getWindAngleApparent() + "deg");
  lcd.print("Wind: " + (String)environment.getWindSpeedApparent() );
  lcd.setCursor(1,3);
  lcd.print("IP: " + WiFi.localIP().toString() );


  nmea2k_setup(); 
#endif  // MAIN_COMPUTER

  if (status_debug) { Serial.println((String) "Setup done."); }
}  // end Setup


#if MAIN_COMPUTER
#else   // not MAIN_COMPUTER  
#endif  // MAIN_COMPUTER

//int switch_counter = 0;
void loop(void) 
{

  // Check incoming responses 
#if MAIN_COMPUTER  
  // MQTT 
  // Parses JSONs in the actOnJSON function
  wifiReconnect();
  mqttReconnect();
  mqttClient.loop();
#endif  // MAIN_COMPUTER  

  // Serial  
  readSerial();
  if (newMessageAvailable)  // there is a new message waiting
  {
    newMessageAvailable = false;
    if (status_debug) { 
      Serial.println("=== Received over serial =====");
      Serial.println(newMessage);
      Serial.println("==============================");    
    }


#if MAIN_COMPUTER
    // For the main computer the JSON recived over serial is placed in reportJSON and handled by actOnReportJSON();
    DeserializationError err = deserializeJson(reportJSON, newMessage);
    if (!err) {
      if (status_debug) { 
        Serial.println(" placed in reportJSON as to be processed by actOnReportJSON");
      }
      actOnReportJSON();
      reportJSON.clear();
    }
#else   //  not MAIN_COMPUTER  
    // where as it for a secondary computer the JSON is placed in the controlJSON and handle by actOnJSON();
    DeserializationError err = deserializeJson(controlJSON, newMessage);
    if (!err) {
      if (status_debug) { 
        Serial.println(" placed in controlJSON as to be processed by actOnJSON");
      }
      actOnJSON();
      controlJSON.clear();
    } // !err 
#endif  // MAIN_COMPUTER
  } // newSerialMessageAvailable

  // IR receive
  if (irrecv.decode(&results)) {
    yield();             // Feed the WDT 
    String IRstring =  String(results.decode_type) + ":" + String(resultToHexidecimal(&results));
    String IRSTRING =  String(results.decode_type) + "_" + String(resultToHexidecimal(&results));
    if (IRdebug) { Serial.println("Copy this " + IRstring + " into the actOnIR(); function to add a new remote button"); }
    actOnIR( IRstring ); 
#if MAIN_COMPUTER
#else   // not MAIN_COMPUTER  
    // a secondary computer can report the IR string as to have the main computer act on it as well
    reportJSON["ir"] = IRstring;
    reportJSON["IR"] = IRSTRING;
#endif  // MAIN_COMPUTER
  } // IR code received 

#if MAIN_COMPUTER
  // MQTT 
  // moved first in the loop (delete below)
  // Parses JSONs in the actOnJSON function
//  wifiReconnect();
//  mqttReconnect();
//  mqttClient.loop();

  // Processes data in the NMEA2000 network used in boats 
  // teporary disabled as to not fog the mqtt debugging
  nmea2k_loop();
  winds = nmeaWind.getWindSpeed();
  windd = nmeaWind.getWindDirection();
  SKwinds = environment.getWindSpeedApparent();
  
  winds = environment.getWindSpeedApparent();
  windd = environment.getWindAngleApparent();


  systemDate = nmeaNav.getSystemDate();
  systemTime = nmeaNav.getSystemTime();
  SeaTemp = nmeaBoat.getTempSea();

  // Display data in the LCD display
  lcd.setCursor(0,2);
//  lcd.print("Wind: " + environment.getWindSpeedApparent().toString() + " " + environment.getWindAngleApparent().toString() + "deg");
   lcd.print("Wind: " + (String)environment.getWindSpeedApparent() + " " + (String)environment.getWindAngleApparent() + "deg");
//  lcd.print("Wind: " + (String)environment.getWindSpeedApparent() );
//  lcd.setCursor(1,3);
//  lcd.print("IP: " + WiFi.localIP().toString() );

  // Display data on the webserver in the local WiFi
  webServer_process();

  // BLE via Phone
  //Dabble.processInput();  //this function is used to refresh data obtained from smartphone. Hence calling this function is mandatory in order to get data properly from your mobile.
  //Gamepad_check(); 
#endif  // MAIN_COMPUTER
 
  // Check fast sensors 
  //  mainBatterySerial.check(mqtt_sync_int*0.1);
  //  startBatterySerial.check(mqtt_sync_int*0.1);
  mainCurrent.check(mqtt_sync_int*0.1);
  heaterCurrent.check(mqtt_sync_int*0.1);
  mainBattery.check(mqtt_sync_int*0.1);
  batterylevel = mainBattery.read();
  startBattery.check(mqtt_sync_int*0.1);
  startbatterylevel = startBattery.read(); // * (120+430)/120*2 + 11.062;
  //  esp32Battery.check(mqtt_sync_int*0.1);
  
  // Check inputs
  touch.check(mqtt_sync_int*55);
  //hall.check(mqtt_sync_int*30);
  light.check();
  pir.check(mqtt_sync_int*0.3);
  landstrom.check(mqtt_sync_int*0.3);
  //water.check(mqtt_sync_int*0.3);
  fuse1.check(mqtt_sync_int*0.3);
  fuse2.check(mqtt_sync_int*0.3);
  //  fuse3.check(mqtt_sync_int*0.3);
  
  // Act on inputs 
  if (fuse1.count2()) {
    lantern.on();
  }
  if (fuse1.count3()) {
    decklight.on();
  }
  if (fuse1.count4()) {
    fan.on();
  }

  // Check outputs 
  lantern.checkBin(mqtt_sync_int*0.3);
  decklight.checkBin(mqtt_sync_int*0.3);
  fan.checkBin(mqtt_sync_int*0.3);
  outlet.checkBin(mqtt_sync_int*0.3);

  onboardLED.check2(mqtt_sync_int*0.3);
  blueLED.check(mqtt_sync_int*0.3);
  greenLED.check(mqtt_sync_int*0.3);
  redLED.check2(mqtt_sync_int*0.3);
  //tableUp.checkBin(mqtt_sync_int*0.3);
  //tableDown.checkBin(mqtt_sync_int*0.3);
//  tableUpSwitch.check();
//  tableDownSwitch.check();

// start MOTOR

    ledcWrite(ledChannel, dutyCycle);
    portENTER_CRITICAL(&mux);
    Freg =30.0*1000000.00/PeriodCount;                       // PeriodCount in 0.000001 of a second
    portEXIT_CRITICAL(&mux);
    averageRPM5   = ((4.0  * averageRPM5)  + Freg) /  5.0;
    averageRPM10  = ((9.0  * averageRPM10) + Freg) / 10.0;
    averageRPM20  = ((19.0 * averageRPM20) + Freg) / 20.0;
    if (Freg < 0.9) {
      averageRPM5  = 0.0;
      averageRPM10 = 0.0;
      averageRPM20 = 0.0;
    }

// end MOTOR

  // Check ONE slow sensor or publish (per loop) 
  //Serial.println("switch_counter: " + (String) switch_counter);
  switch (switch_counter) {
    case 0:    // Onewire Temperature
    //  Temperature_check(mqtt_sync_int*0.5);
      //temp = DS18B20_read();
      switch_counter++;
      break;
    case 1:    // Ultra-sonic Distance
      //DISTANCE_check(mqtt_sync_int*10.0);
      switch_counter++;
      break;
    case 2:    // DHT Temperature 
      //DHT_Temperature_check(mqtt_sync_int*0.5);
      switch_counter++;
      break;
    case 3:    // DHT Humidity
      //DHT_Humidity_check(mqtt_sync_int*1.0);
      switch_counter++;
      break;
    case 4:    // 
      // other slow sensor function

      //Serial.println("........................" + (String) touchRead(T1)  + " ......... " + (String) touchRead(T8) );

      switch_counter++;
      break;
    case 5:    // 
      // other slow sensor function

      switch_counter++;
      break;
    case 6:    // 
      // other slow sensor function

      switch_counter++;
      break;
    case 7:    // 
      // other slow sensor function
/*      
 
      if (pirsensor.read()) {
        Serial.println("PIR sensor: HIGH ");
      } else {
        Serial.println("PIR sensor:                                                        LOW" );
      }
*/      
      switch_counter++;
      break;
    case 8:    // 
      // other slow sensor function
      // Is it a good temperature for a swim?
      /*if (DS18B20_read() >= 28.0) 
      {
        greenLED.on();
        mqttClient.publish(MQTT_SUB_PREFIX + "greenLED","on"); 
      } else {
        //greenLED.off();
        //mqttClient.publish(MQTT_SUB_PREFIX + "greenLED","off"); 
      }*/
      switch_counter++;
      break;
    case 9:    // 
      // other slow sensor function
      // battery in bad shape 
      
      if (false) //(mainBattery.read() <= 4.0) 
      {
        if (millis() - ALARM_postingIntervalTimer > ALARM_postingIntervalDelay) {
          miniJSON[ "redLED" ] = "on";
          char mqttPublishJSON[512];
          serializeJson(miniJSON, mqttPublishJSON);

          mqttClient.publish(MQTT_TOPIC_DATA,    mqttPublishJSON);
          mqttClient.publish(MQTT_TOPIC_CONTROL, mqttPublishJSON);
          miniJSON.clear();
          ALARM_postingIntervalTimer = millis();
          //mqttClient.publish( MQTT_TOPIC_CONTROL ,"{\"redLED\":\"on\"}");
          redLED.on();
//        char * topicPrefix = MQTT_SUB_PREFIX + "MQTT_Display/text";
//        mqttClient.publish( topicPrefix ,"WARNING: Battery needs charging");

        }
      }
      
      switch_counter++;
      break;
    case 10:    // Update LCD display 
      // other slow sensor function
      if (!reportJSON.isNull()) { // reportJSON has data and needs to be sent over Serial2 to connected computers 
        Serial.println("reportJSON to be sent over Serial2 ");
        serializeJson(reportJSON, Serial);  
        Serial.println();
         
        serializeJson(reportJSON, Serial2);   // send serialJSON over Serial2
        reportJSON.clear();                   // and empty it 
        Serial.println("reportJSON to be sent over Serial2 now cleared");
        serializeJson(reportJSON, Serial);  
        Serial.println();
        
#if MAIN_COMPUTER
#else   // not MAIN_COMPUTER  
        mqtt_sync_int = 1;
#endif  // MAIN_COMPUTER
      }
      switch_counter++;
      break;
    case 11:    // Send serialJSON 
      if (!serialJSON.isNull()) { // serialJSON has data and needs to be sent over Serial2 to connected computers 
        Serial.println("serialJSON to be sent over Serial2 ");
        serializeJson(serialJSON, Serial);  
        Serial.println();
        serializeJson(serialJSON, Serial2);   // send serialJSON over Serial2
        serialJSON.clear();                   // and empty it 
      }
      switch_counter++;
      break;
    case 12:    // Publish on ThingSpeak
#if MAIN_COMPUTER
      if (millis() - TS_postingIntervalTimer > TS_postingIntervalDelay) {
        // set the status
        String myStatus = "";
        myStatus = String("GSP position: lat:55 lon:13 , MAC: ") + (String) WiFi.macAddress(); 
        ThingSpeak.setStatus(myStatus);
        // Home
        //ThingSpeak.setLatitude(55.6681587);
        //ThingSpeak.setLongitude(13.3383096);
        ThingSpeak.setLatitude(55.6682);
        ThingSpeak.setLongitude(13.3383);

        // Work
        //ThingSpeak.setLatitude(55.7163242);
        //ThingSpeak.setLongitude(13.2270312);
        ThingSpeak.setElevation(0.0);
        //ThingSpeak.setTwitterTweet(Account,Text);

    /*
        // write to the ThingSpeak channel
        int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
        if(x == 200){
          if (status_debug) { Serial.println("Channel update successful."); }
        }
        else{
          if (status_debug) { Serial.println("Problem updating channel. HTTP error code " + String(x)); }
        }
   */
        TS_postingIntervalTimer = millis();
      }
#endif  // MAIN_COMPUTER  
      switch_counter++;
      break;
      
    case 13:    // Publish on MQTT
      //MQTT_publish();
#if MAIN_COMPUTER
      if (!mqttJSON.isNull()) { // (measureJsonPretty(doc) > 0) {
        // Add the "location" object
        JsonObject location = mqttJSON.createNestedObject("loc");
//        location["lat"] = 55.6681587;
//        location["lon"] = 13.3383096;
        location["lat"] = 56;
        location["lon"] = 13;
/*
        JsonObject location = mqttJSON.createNestedObject("location");
        location["lat"] = 55.6681587;
        location["lon"] = 13.3383096;
        
*/
        //mqttJSON["MAC"] =  (String) WiFi.macAddress();
/*
        uint64_t chipid;  
        chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
        Serial.printf("ESP32 Chip ID = %04X",(uint16_t)(chipid>>32));//print High 2 bytes
        Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.
*/
        if (status_debug) { 
          Serial.println("JSON to be sent over MQTT ");
          //serializeJsonPretty(mqttJSON, Serial);
          serializeJson(mqttJSON, Serial);
          Serial.println();
        }
        
        char MqttPublishJSON[512];
        //char buffer[512];
        serializeJson(mqttJSON, MqttPublishJSON);
        if (status_debug) { 
          Serial.println((String) MqttPublishJSON);
        }
        boolean errMQTT = mqttClient.publish(MQTT_TOPIC_DATA, MqttPublishJSON);
        //boolean errMQTT = mqttClient.publish_P(MQTT_TOPIC_DATA, MqttPublishJSON, false);
        if (!errMQTT) { 
          //if (status_debug) { 
            Serial.println("Error when publishing MQTT: " + (String) MqttPublishJSON);
            Serial.println("PubSub: MQTT_MAX_PACKET_SIZE " + (String) MQTT_MAX_PACKET_SIZE  + "  - Payload size: " + (String) strlen(MqttPublishJSON));
          //}
          //unsigned int msgLen = strlen(MqttPublishJSON);
          //mqttClient.beginPublish(MQTT_TOPIC_DATA, msgLen, false);
          //int ii = 0;
          //char tempMessage[102];
          //for (ii=0; ii < 100; ii++) {
          //  tempMessage[ii] = MqttPublishJSON[ii];
          //}
          //tempMessage[ii] = '}';
          //ii++;
          //tempMessage[ii] = '\0';
          //mqttClient.print(tempMessage);
          //mqttClient.print(MqttPublishJSON[100:msgLen-1]);
          //mqttClient.endPublish();
        }          
        mqttJSON.clear();
        mqtt_sync_int = 1;

      } 
#else   // not MAIN_COMPUTER 
        mqttJSON.clear(); 
        mqtt_sync_int = 1;        
#endif  // MAIN_COMPUTER
      switch_counter = 0;
      break;
  }
}
