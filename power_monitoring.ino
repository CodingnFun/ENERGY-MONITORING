/* This code is for ESP8266 to control a device via blynk App and monitor it's power consumption parameters via thingspeak.
Develop blynk dashbord to control on and off status of the device, keep blynk template name, ID and AUTH TOKEN with you to use in following code, also thingspeak channel ID and Api Key*/

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include<ArduinoJson.h>
#include <PZEM004Tv30.h>

/* 
  GPIO5 (D1) (Connects to the Tx pin on the PZEM)
  GPIO4 (D2) (Connects to the Rx pin on the PZEM)
*/
PZEM004Tv30 pzem(5, 4);   

unsigned long channelID = YOUR_channelID;
const char* apiKey = "YOUR_apiKey";

WiFiClient client;

// Enter your Auth token
char auth[] ="YOUR_BLYNK_AUTH_TOKEN";

//Enter your WIFI SSID and password
char ssid[] = "your wifi ssid";
char pass[] = "yur wifi password";

void setup(){
 
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

   WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ThingSpeak.begin(client);
}

void loop(){

Blynk.run();

float voltage=0;
voltage = pzem.voltage();
if(voltage != NAN){
Serial.print("Voltage:" ); 
Serial.print(voltage); 
Serial.println("V");
} else {
Serial.println("Error reading voltage");
}

float current=0;
current = pzem.current();
if(current != NAN){
Serial.print("Current: "); 
Serial.print(current); 
Serial.println("A");
} else {
Serial.println("Error reading current");
}

float power = 0;
power = pzem.power();
if(current != NAN){
Serial.print("Power: "); 
Serial.print(power); 
Serial.println("W");
} else {
Serial.println("Error reading power");
}

float energy = 0;
energy = pzem.energy();
if(current != NAN){
Serial.print("Energy: "); 
Serial.print(energy,3); 
Serial.println("kWh");
} else {
Serial.println("Error reading energy");
}

float frequency = 0;
frequency = pzem.frequency();
if(current != NAN){
Serial.print("Frequency: "); 
Serial.print(frequency, 1); 
Serial.println("Hz");
} else {
Serial.println("Error reading frequency");
}

float pf = pzem.pf();
if(current != NAN){
Serial.print("PF: "); 
Serial.println(pf);
} else {
Serial.println("Error reading power factor");
}

 if (WiFi.status() == WL_CONNECTED) 
 {
  ThingSpeak.setField(1, voltage);// send voltage readings to field 1 of thingspeak channel
  ThingSpeak.setField(2, current);// send current readings to field 2 of thingspeak channel
  ThingSpeak.setField(3, power);// send power readings to field 3 of thingspeak channel
  ThingSpeak.setField(4, energy);// send energy readings to field 4 of thingspeak channel
  ThingSpeak.setField(5, frequency);// send frequency readings to field 5 of thingspeak channel
  ThingSpeak.setField(6, pf);// send pf readings to field 6 of thingspeak channel

  int response = ThingSpeak.writeFields(channelID, apiKey);

  if (response == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.print("Error sending data to ThingSpeak. Response code: ");
    Serial.println(response);
  }
 }

Serial.println();
delay(200);
}
