// https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/

// The code below works but could be written much better. Please help improve if you can 

//libraries
#include <WiFi.h>
#include <WebServer.h>
#include <String>

/*Put your SSID & Password*/
//const char* wifi_ssid =     This information is moved to the file personal.ino
//const char* wifi_password = This information is moved to the file personal.ino

WebServer webServer(80);

void webServer_setup();
void webServer_process();
void handle_OnConnect();
void handle_led1on();
void handle_led1off();
void handle_led2on();
void handle_led2off();
void handle_NotFound();


String header;

uint8_t LED1pin = 14;
//bool LED1status = LOW;

uint8_t LED2pin = 13;
//bool LED2status = LOW;



//void setup() {
void webServer_setup() {
  //Serial.begin(115200);
  delay(100);
  //pinMode(LED1pin, OUTPUT);
  //pinMode(LED2pin, OUTPUT);
  if (status_debug) { 
    Serial.println("Connecting to ");
    Serial.println(personalData.wifi_ssid);
  }
  //connect to your local wi-fi network
  //WiFi.begin(wifi_ssid, wifi_password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  if (status_debug) { Serial.print("."); }
  }
  if (status_debug) { 
    Serial.println("");
    Serial.println("WiFi connected..!");
    Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  }
  webServer.on("/", handle_OnConnect);
  webServer.on("/led1on", handle_led1on);
  webServer.on("/led1off", handle_led1off);
  webServer.on("/led2on", handle_led2on);
  webServer.on("/led2off", handle_led2off);
  webServer.onNotFound(handle_NotFound);

  webServer.begin();
  if (status_debug) { Serial.println("HTTP server started"); }
}

//void loop() {
void webServer_process() {
  webServer.handleClient();
  /*
  if(greenLED.state()) //LED1status)
  {
    //digitalWrite(LED1pin, HIGH);
  }
  else
  {
    //digitalWrite(LED1pin, LOW);
  }
  
  if(blueLED.state()) //LED2status)
  {
    //digitalWrite(LED2pin, HIGH);
  }
  else
  {
    //digitalWrite(LED2pin, LOW);
  }
  */
}

void handle_OnConnect() {
  //LED1status = LOW;
  //LED2status = LOW;
  Serial.println("GPIO14 Status: OFF | GPIO13 Status: OFF");
  //webServer.send(200, "text/html", SendHTML(LED1status,LED2status)); 
  //webServer.send(200, "text/html", SendHTML(greenLED.state(),blueLED.state(),batterylevel,temp));
  webServer.send(200, "text/html", SendHTML(lantern.state(),decklight.state(),batterylevel,temp));
}

void handle_led1on() {
  //LED1status = HIGH;
  //greenLED.on();
  lantern.on();
  if (status_debug) { Serial.println("GPIO14 Status: ON"); }
  //webServer.send(200, "text/html", SendHTML(true,LED2status)); 
  //webServer.send(200, "text/html", SendHTML(greenLED.state(),blueLED.state(),batterylevel,temp));
  webServer.send(200, "text/html", SendHTML(lantern.state(),decklight.state(),batterylevel,temp));
}

void handle_led1off() {
  //LED1status = LOW;
  //greenLED.off();
  lantern.off();
  if (status_debug) { Serial.println("GPIO14 Status: OFF"); }
  //webServer.send(200, "text/html", SendHTML(false,LED2status)); 
  //webServer.send(200, "text/html", SendHTML(greenLED.state(),blueLED.state(),batterylevel,temp));
  webServer.send(200, "text/html", SendHTML(lantern.state(),decklight.state(),batterylevel,temp));
}

void handle_led2on() {
  //LED2status = HIGH;
  //blueLED.on();
  decklight.on();
  if (status_debug) { Serial.println("GPIO13 Status: ON"); }
  //webServer.send(200, "text/html", SendHTML(LED1status,LED2status)); 
  //webServer.send(200, "text/html", SendHTML(greenLED.state(),blueLED.state(),batterylevel,temp));
  webServer.send(200, "text/html", SendHTML(lantern.state(),decklight.state(),batterylevel,temp));
}

void handle_led2off() {
  //LED2status = LOW;
  //blueLED.off();
  decklight.off();
  if (status_debug) { Serial.println("GPIO13 Status: OFF"); }
  //webServer.send(200, "text/html", SendHTML(LED1status,LED2status));
  //webServer.send(200, "text/html", SendHTML(greenLED.state(),blueLED.state(),batterylevel,temp));
  webServer.send(200, "text/html", SendHTML(lantern.state(),decklight.state(),batterylevel,temp));
}

void handle_NotFound() {
  webServer.send(404, "text/plain", "Not found");
}
