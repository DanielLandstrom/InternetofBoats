/*  Function for handeling commands beeing reported over serial from secondary computers 
 *   
 *   Currently support the following JSONs
 *   From Digital Switching central 
 *   lant       : Navigational lantern
 *   lantM      : Motor lantern
 *   lantT      : Top lantern when anchoring
 *   deckl      : Decklight
 *   fan
 *   outlet
 *   
 *   From Landström, 220V 
 *   
 *   
 *   From Motor observer 
 *   motorrpm
 *   motortemp
 *   
 *   To be added: 
 *   horn
 * 
 * 
 */
  
//void actOnReportJSON(void);  // moved first, to sketch_MagicOnCall

void actOnReportJSON(void) {
    // more examples found at https://arduinojson.org/v6/doc/deserialization/

    // Send JSON also over Serial2 for other devices listening so they can act on this JSON as well
    // serializeJson(controlJSON, Serial2);

    // Get a reference to the root object
    JsonObject root = reportJSON.as<JsonObject>();

      int cnt     = reportJSON["cnt"]; // 3
      
      // Extract motor RPM form the serial JSON and store it in the motor class
      int   motorrpm    = reportJSON["motorrpm"];   // 2400
      //motor.setRPM(motorrpm);
      engine.setRPM(motorrpm);
      //engine.setRevolutions(RPMtoHz(motorrpn*1.0)); 
      double motortemp   = reportJSON["motortemp"];  // 75.32
      //motor.setTemp(motortemp);
      engine.setExhaustTemperature(motortemp);

      // Oljetryck (PSI)
      //Girhastighet grad /sec
      //Kulvätaka temp
      //trimplan %
      //fueleconomy
      //Generator Voltage

      // ======== 220 Voltage central  ==========
      
      float mBat  = reportJSON["mBat"]; // 5.79
      //mqttJSON["mBat"] = mBat;
      mainBatterySerial.set(mBat);
      float sBat  = reportJSON["sBat"]; // 18.67
      //mqttJSON["sBat"] = sBat;
      Serial.println("sBat: " + (String) sBat);
      startBatterySerial.set(sBat);
      float Cur1  = reportJSON["Cur1"]; // 0.03
      //mqttJSON["Cur1"] = Cur1;
      mainCurrent.set(Cur1);
      float Cur2  = reportJSON["Cur2"]; // 0.03
      //mqttJSON["Cur2"] = Cur2;
      heaterCurrent.set(Cur2);
      int R1      = reportJSON["R1"]; // 0
      mqttJSON["R1"] = R1;
      int R2      = reportJSON["R2"]; // 0
      mqttJSON["R2"] = R2;
      int R3      = reportJSON["R3"]; // 0
      mqttJSON["R3"] = R3;
      float diff  = reportJSON["diff"]; // 0.3

//============================================================================================
    // Get the text of the sensor and see if it existed 
    const char* irKey = root["ir"]; // varable have to be declared const to work in JSON
    if (irKey != nullptr) {
    // IR meassage existed in the reportJSON
      if (mqtt_debug) {Serial.println("IR message received : " + (String) irKey);}
      actOnIR( irKey ); 
    } // endif  "ir"

//============================================================================================
    // Get the text of the sensor and see if it existed 
    const char* IRKey = root["IR"]; // varable have to be declared const to work in JSON
    if (IRKey != nullptr) {
    // IR meassage existed in the reportJSON
      //if (mqtt_debug) {
        Serial.println("IR message received : " + (String) IRKey); //}
      actOnIR( irKey ); 
    } // endif  "IR"

//============================================================================================
    // Get the text of the sensor and see if it existed 
    const char* tableKey = root["table"]; // varable have to be declared const to work in JSON
    if (tableKey != nullptr) {
    // sensor existed in the reportJSON
      if (String(tableKey) == String("up")) {  
        if (mqtt_debug) {Serial.println("workTable.up();");}
        tableUp.on();
        tableDown.off();
      } else if (String(tableKey) == String("down")) {
        if (mqtt_debug) {Serial.println("workTable.down();");}
        tableUp.off();
        tableDown.on();
      } else if (String(tableKey) == String("stop")) {
        if (mqtt_debug) {Serial.println("workTable.stop();");}
        tableUp.off();
        tableDown.off(); 
      }
    } // endif  "table"

//============================================================================================
    const char* lanternKey = root["lant"]; // varable have to be declared const to work in JSON
    if (lanternKey != nullptr) {
    // sensor existed in the reportJSON
      if        (String(lanternKey) == String("on")) {  
          if (mqtt_debug) {Serial.println("lantern.on();");}
          lantern.on();
      } else if (String(lanternKey) == String("off")) {  
          if (mqtt_debug) {Serial.println("lantern.off();");}
          lantern.off();
      } else if (String(lanternKey) == String("flash")) {  
          if (mqtt_debug) {Serial.println("lantern.flash();");}
          lantern.flash();
      } else if (String(lanternKey) == String("quickflash")) {  
          if (mqtt_debug) {Serial.println("lantern.quickflash();");}
          lantern.quickflash();
      } else if (String(lanternKey) == String("slowflash")) {  
          if (mqtt_debug) {Serial.println("lantern.slowflash();");}
          lantern.slowflash();
      } else if (String(lanternKey) == String("level")) {  
          if (mqtt_debug) {Serial.println("lantern.level();");}
          // lantern.level(percentage );  // Needs to be implemented 
      } 
    } // endif  "lanternKey"

//============================================================================================
    const char* decklightKey = root["deckl"]; // varable have to be declared const to work in JSON
    if (decklightKey != nullptr) {
    // sensor existed in the serialJSON
      if        (String(decklightKey) == String("on")) {  
          if (mqtt_debug) {Serial.println("decklight.on();");}
          decklight.on();
      } else if (String(decklightKey) == String("off")) {  
          if (mqtt_debug) {Serial.println("decklight.off();");}
          decklight.off();
      } else if (String(decklightKey) == String("flash")) {  
          if (mqtt_debug) {Serial.println("decklight.flash();");}
          decklight.flash();
      } else if (String(decklightKey) == String("quickflash")) {  
          if (mqtt_debug) {Serial.println("decklight.quickflash();");}
          decklight.quickflash();
      } else if (String(decklightKey) == String("slowflash")) {  
          if (mqtt_debug) {Serial.println("decklight.slowflash();");}
          decklight.slowflash();
      } else if (String(decklightKey) == String("level")) {  
          if (mqtt_debug) {Serial.println("decklight.level();");}
          // decklight.level(percentage );  // Needs to be implemented 
      } 
    } // endif  "decklightKey"


//============================================================================================
    const char* fanKey = root["fanV"]; // varable have to be declared const to work in JSON
    if (fanKey != nullptr) {
    // sensor existed in the serialJSON
      if        (String(fanKey) == String("on")) {  
          if (mqtt_debug) {Serial.println("fan.on();");}
          fan.on();
      } else if (String(fanKey) == String("off")) {  
          if (mqtt_debug) {Serial.println("fan.off();");}
          fan.off();
      } else if (String(fanKey) == String("level")) {  
          if (mqtt_debug) {Serial.println("fan.level();");}
          // fan.level(percentage );  // Needs to be implemented 
      } 
    } // endif  "fanKey"


//============================================================================================
    const char* outletKey = root["outlet"]; // varable have to be declared const to work in JSON
    if (outletKey != nullptr) {
    // sensor existed in the serialJSON
      if        (String(outletKey) == String("on")) {  
          if (mqtt_debug) {Serial.println("outlet.on();");}
          outlet.on();
      } else if (String(outletKey) == String("off")) {  
          if (mqtt_debug) {Serial.println("outlet.off();");}
          outlet.off();
      } else if (String(outletKey) == String("flash")) {  
          if (mqtt_debug) {Serial.println("outlet.flash();");}
          outlet.flash();
      } else if (String(outletKey) == String("quickflash")) {  
          if (mqtt_debug) {Serial.println("outlet.quickflash();");}
          outlet.quickflash();
      } else if (String(outletKey) == String("slowflash")) {  
          if (mqtt_debug) {Serial.println("outlet.slowflash();");}
          outlet.slowflash();
      } else if (String(outletKey) == String("level")) {  
          if (mqtt_debug) {Serial.println("outlet.level();");}
          // outlet.level(percentage );  // Needs to be implemented 
      } 
    } // endif  "outletKey"

    

//============================================================================================
    const char* redLEDKey = root["redLED"]; // varable have to be declared const to work in JSON
    if (redLEDKey != nullptr) {
      // sensor existed in the reportJSON
      if        (String(redLEDKey) == String("on")) {  
          if (mqtt_debug) {Serial.println("redLED.on();");}
          redLED.on();
      } else if (String(redLEDKey) == String("off")) {  
          if (mqtt_debug) {Serial.println("redLED.off();");}
          redLED.off();
      } else if (String(redLEDKey) == String("flash")) {  
          if (mqtt_debug) {Serial.println("redLED.flash();");}
          redLED.flash();
      } else if (String(redLEDKey) == String("quickflash")) {  
          if (mqtt_debug) {Serial.println("redLED.quickflash();");}
          redLED.quickflash();
      } else if (String(redLEDKey) == String("slowflash")) {  
          if (mqtt_debug) {Serial.println("redLED.slowflash();");}
          redLED.slowflash();
      } else if (String(redLEDKey) == String("level")) {  
          if (mqtt_debug) {Serial.println("redLED.level();");}
          // redLED.level(percentage );  // Needs to be implemented 
      } 
    } // endif  "redLED"

//============================================================================================
    const char* greenLEDKey = root["greenLED"]; // varable have to be declared const to work in JSON
    if (greenLEDKey != nullptr) {
      // sensor existed in the reportJSON
      if        (String(greenLEDKey) == String("on")) {  
          if (mqtt_debug) {Serial.println("greenLED.on();");}
          greenLED.on();
      } else if (String(greenLEDKey) == String("off")) {  
          if (mqtt_debug) {Serial.println("greenLED.off();");}
          greenLED.off();
      } else if (String(greenLEDKey) == String("flash")) {  
          if (mqtt_debug) {Serial.println("greenLED.flash();");}
          greenLED.flash();
      } else if (String(greenLEDKey) == String("quickflash")) {  
          if (mqtt_debug) {Serial.println("greenLED.quickflash();");}
          greenLED.quickflash();
      } else if (String(greenLEDKey) == String("slowflash")) {  
          if (mqtt_debug) {Serial.println("greenLED.slowflash();");}
          greenLED.slowflash();
      } else if (String(greenLEDKey) == String("level")) {  
          if (mqtt_debug) {Serial.println("greenLED.level();");}
          // greenLED.level(percentage );  // Needs to be implemented 
      } 
    } // endif  "greenLED"
    
//============================================================================================
    const char* blueLEDKey = root["blueLED"]; // varable have to be declared const to work in JSON
    if (blueLEDKey != nullptr) {
      // sensor existed in the reportJSON
      if        (String(blueLEDKey) == String("on")) {  
          if (mqtt_debug) {Serial.println("blueLED.on();");}
          blueLED.on();
      } else if (String(blueLEDKey) == String("off")) {  
          if (mqtt_debug) {Serial.println("blueLED.off();");}
          blueLED.off();
      } else if (String(blueLEDKey) == String("flash")) {  
          if (mqtt_debug) {Serial.println("blueLED.flash();");}
          blueLED.flash();
      } else if (String(blueLEDKey) == String("quickflash")) {  
          if (mqtt_debug) {Serial.println("blueLED.quickflash();");}
          blueLED.quickflash();
      } else if (String(blueLEDKey) == String("slowflash")) {  
          if (mqtt_debug) {Serial.println("blueLED.slowflash();");}
          blueLED.slowflash();
      } else if (String(blueLEDKey) == String("level")) {  
          if (mqtt_debug) {Serial.println("blueLED.level();");}
          // blueLED.level(percentage );  // Needs to be implemented 
      }
    } // endif  "blueLED"
    
//============================================================================================
//============================================================================================    

} // end actOnReportJSON 
