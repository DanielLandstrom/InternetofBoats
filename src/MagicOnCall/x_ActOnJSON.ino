//void actOnJSON(void);  // Moved first to the sketch_MagicOnCall

void actOnJSON(void) {
    // more examples found at https://arduinojson.org/v6/doc/deserialization/

    // Send JSON also over Serial2 for other devices listening so they can act on this JSON as well
    serializeJson(controlJSON, Serial2);

    // Get a reference to the root object
    JsonObject root = controlJSON.as<JsonObject>();

    // Extract motor RPM form the serial JSON and store it in the motor class
    int   motorrpm    = controlJSON["motorrpm"];   // 2400
    motor.setRPM(motorrpm);
    float motortemp   = controlJSON["motortemp"];  // 75.32
    motor.setTemp(motortemp);

//============================================================================================
    const char* statusKey = root["status"]; // varable have to be declared const to work in JSON
    if (statusKey != nullptr) {
    // status existed in the controlJSON
      if        (String(statusKey) == String("online")) {  
          if (mqtt_debug) {Serial.println("Online!");}
      } else if (String(statusKey) == String("offline")) {  
          if (mqtt_debug) {Serial.println("Offline");}
      } else if (String(statusKey) == String("sync")) {  
          if (mqtt_debug) {Serial.println("Sync");}
          mqtt_sync_int = 0; 
      } 
    } // endif  "statusKey"

//============================================================================================
    const char* lanternKey = root["lant"]; // varable have to be declared const to work in JSON
    if (lanternKey != nullptr) {
    // sensor existed in the controlJSON
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
    // sensor existed in the controlJSON
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
    // sensor existed in the controlJSON
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
    // sensor existed in the controlJSON
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
    // Get the text of the sensor and see if it existed 
    const char* tableKey = root["table"]; // varable have to be declared const to work in JSON
    if (tableKey != nullptr) {
    // sensor existed in the controlJSON
      if        (String(tableKey) == String("up")) {  
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
      } else if (String(tableKey) == String("switchOn")) {
        if (mqtt_debug) {Serial.println("workTable.switch(on);");}
//        tableUpSwitch.on();
//        tableDownSwitch.on();
      } else if (String(tableKey) == String("switchOff")) {
        if (mqtt_debug) {Serial.println("workTable.switch(off);");}
//        tableUpSwitch.off();
//        tableDownSwitch.off();
      }
    } // endif  "table"

//============================================================================================
    const char* onboardLEDKey = root["onboardLED"]; // varable have to be declared const to work in JSON
    if (onboardLEDKey != nullptr) {
      // sensor existed in the controlJSON
      if        (String(onboardLEDKey) == String("on")) {  
          if (mqtt_debug) {Serial.println("onboardLED.on();");}
          onboardLED.on();
      } else if (String(onboardLEDKey) == String("off")) {  
          if (mqtt_debug) {Serial.println("onboardLED.off();");}
          onboardLED.off();
      } else if (String(onboardLEDKey) == String("flash")) {  
          if (mqtt_debug) {Serial.println("onboardLED.flash();");}
          onboardLED.flash();
      } else if (String(onboardLEDKey) == String("quickflash")) {  
          if (mqtt_debug) {Serial.println("onboardLED.quickflash();");}
          onboardLED.quickflash();
      } else if (String(onboardLEDKey) == String("slowflash")) {  
          if (mqtt_debug) {Serial.println("onboardLED.slowflash();");}
          onboardLED.slowflash();
      } else if (String(onboardLEDKey) == String("level")) {  
          if (mqtt_debug) {Serial.println("onboardLED.level();");}
          // onboardLED.level(percentage );  // Needs to be implemented 
      } 
    } // endif  "onboardLED"

//============================================================================================
    const char* redLEDKey = root["redLED"]; // varable have to be declared const to work in JSON
    if (redLEDKey != nullptr) {
      // sensor existed in the controlJSON
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
      // sensor existed in the controlJSON
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
      // sensor existed in the controlJSON
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

} // end actOnJSON    
