/*If you want to control any device(load, bulb etc) with blynk app and esp8266, use following code.
this code will develop the communication between blynk app and physical device via esp8266, esp pins will be defined during blynk app development only,
 no need of pin definitions in the code
 
 pin D1 on esp8266 is [GPIO5 , input mode, digital pin on datastreams of blynk app]
 pin D7 on esp8266 is [GPIO13 , output mode, digital pin on datastreams of blynk app]
 
 */

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME "

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Enter your Auth token
char auth[] ="YOUR_BLYNK_APP_AUTH_TOKEN";

//Enter your WIFI SSID and password
char ssid[] = "YOUR_WIFI-SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

void setup(){
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop(){
  Blynk.run();
}