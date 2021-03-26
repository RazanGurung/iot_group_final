#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include<SoftwareSerial.h>
SoftwareSerial s(3,1);

FirebaseData firebase;

//String str = "1";
//int in = str.toInt();

const char* ssid = "ryanwifi";
const char* password = "Password@2147";
#define FIREBASE_HOST "iotgroup-9df93-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "rmD2k2TMVkWtaH12bGSm2hvCmnH7Ee5fqvyN2tWs"

void setup() {
 Serial.begin(19200);
  //s.begin(115200);
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

 WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.getString(firebase, "SmartZooControl/Gate_Status")) {
    if (firebase.dataType() == "string") {
      String status = firebase.stringData();
      int state = status.toInt();
      s.write(state);
    }
   }
  else {
    Serial.println(firebase.errorReason());
  }

}
