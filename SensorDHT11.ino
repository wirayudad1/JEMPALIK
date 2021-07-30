#include <ESP8266WiFi.h>                                                    // esp8266 library
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
//#include <FirebaseHTTPClient.h>
#include "DHT.h"                                                           // dht11 temperature and humidity sensor library

#define FIREBASE_HOST "datasensorrpl.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "7RhhiscgWBMZJGCBNNDv3ehpFYzb7iGj1Vv6UrTM"            // the secret key generated from firebase

#define WIFI_SSID "oppo"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "berbahaya"                                    //password of wifi ssid
// what digital pin we're connected to
#define DHTTYPE DHT11                                                       // select dht type as DHT 11 or DHT22
DHT dht(D3, DHTTYPE);                                                     

void setup() {
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST);                              // connect to firebase                                                             //Start reading dht sensor
}

void loop() { 
  float h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht.readTemperature();                                           // Read temperature as Celsius (the default)
    
  if (isnan(h) || isnan(t)) {                                                // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print("Humidity: ");  Serial.print(h);
  //int humid=int(h);
  String fireHumid = String(h) + String("%");                                         //convert integer humidity to string humidity 
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("Â°C ");
   //int tempe=int(t);
  String fireTemp = String(t) + String("C"); 
 // Firebase.pushString("/DHT11/Humidity", fireHumid);                                  //setup path and send readings
  Firebase.setString("Temperature", fireTemp);                                //setup path and send readings//convert integer temperature to string temperature
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
 
  delay(1000);
}
