// Litterature:  https://circuits4you.com/2019/01/05/connecting-esp32-to-wifi-network/
// Class responsibles: Daniel Landström

// Class ToDos:

// Load Wi-Fi library
#include <WiFi.h>             // Used for ESP32
// #include <ESP8266WiFi.h>   // Used for ESP8266
//#include <ESP8266WebServer.h>
//#include <WiFiUdp.h>

//const char* wifi_ssid     = This information is moved to the file personal.ino
//const char* wifi_password = This information is moved to the file personal.ino

// Set web server port number to 80
//WiFiServer server(80);

/*
// Setup a Narrowband Connection
// initialize the library instance
NBClient nbClient;
//NBSSLClient nbClient; // Uncomment to use SSL connection
GPRS gprs;
NB nbAccess;

// Setup a Wifi Connection
//WiFiClient wifiClient;
*/

WiFiClient wifiClient;

void wifiReconnect()
{
  if (WiFi.status() != WL_CONNECTED) {
    if (status_debug) { Serial.print("Attempting to reconnect Wifi: "); }
    WiFi.begin(personalData.wifi_ssid, personalData.wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
      if (status_debug) { Serial.print("."); }
      delay(2000);
    }
    //Updated
    if (status_debug) { Serial.println("\n - WiFI Connected"); }

    // Updated
    //WiFi.mode(WIFI_MODE_STA);
    if (status_debug) { 
      Serial.println("WiFi MAC address: " + (String) WiFi.macAddress()); 
      Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
      lcd.setCursor(1,3);
      //lcd.print("IP: " + (String) WiFi.localIP());
      lcd.print("IP: " + WiFi.localIP().toString() );
      lcd.display();
    }
     
  }
}

/*
void thingsSpeakPublish()
{
    WiFiClient wifiClient;
    int retries = 5;
    while(!!!wifiClient.connect(server, 80) && (retries-- > 0)) {
      Serial.print(".");
    }
    Serial.println();
    if(!!!wifiClient.connected()) {
       Serial.println("Failed to connect, going back to sleep");
    }
    
//    Serial.print("Request resource: "); 
//    Serial.println(resource);
//    wifiClient.print(String("GET ") + resource + apiKey + "&field3=" + Lock +
                    " HTTP/1.1\r\n" +
                    "Host: " + server + "\r\n" + 
                    "Connection: close\r\n\r\n");
                    
    int timeout = 5 * 10; // 5 seconds             
    while(!!!wifiClient.available() && (timeout-- > 0)){
      delay(100);
    }
    if(!!!wifiClient.available()) {
       Serial.println("No response, going back to sleep");
    }
    while(wifiClient.available()){
      Serial.write(wifiClient.read());
    }
    
    Serial.println("\nclosing connection");
    wifiClient.stop();
}

*/
