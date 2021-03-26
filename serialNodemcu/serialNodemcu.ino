#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
#include<SoftwareSerial.h>
SoftwareSerial s(3,1);
Servo myservo;
Servo uservo;

FirebaseData firebase;

int state;
int fstate;

const char* ssid = "Anil";
const char* password = "123456789";
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
  myservo.attach(5);
  myservo.write(0);
  uservo.attach(16);
  uservo.write(0);
}

void loop() {
  if (Firebase.getString(firebase, "SmartZooControl/Gate_Status")) {
    if (firebase.dataType() == "string") {
      String status = firebase.stringData();
       state = status.toInt();
      Serial.println(state);
    }
   }
  else {
    Serial.println(firebase.errorReason());
  }
    if (Firebase.getString(firebase, "SmartZooControl/Feeder_Status")) {
    if (firebase.dataType() == "string") {
      String fstatus = firebase.stringData();
       fstate = fstatus.toInt();
      Serial.println(fstate);
    }
   }
  else {
    Serial.println(firebase.errorReason());
  }
  if(state == 1 ){
      myservo.write(180);
    }
    if(state == 0){
       myservo.write(0);
      }
if(fstate == 1 ){
      uservo.write(180);
    }
    if(fstate == 0){
       uservo.write(0);
      }
}
