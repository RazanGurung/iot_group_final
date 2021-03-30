#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
#include<SoftwareSerial.h>
SoftwareSerial s(12,14);
Servo myservo;
Servo uservo;

FirebaseData firebase;

int state;
int fstate;

const char* ssid = "pooja";
const char* password = "12345678";
#define FIREBASE_HOST "iotgroup-9df93-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "rmD2k2TMVkWtaH12bGSm2hvCmnH7Ee5fqvyN2tWs"

void setup() {
 Serial.begin(9600);
 s.begin(9600);
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

 WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
    while (!Serial) continue;
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
      uservo.write(90);
    }
    if(fstate == 0){
       uservo.write(0);
      }
      StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
 
  if (root == JsonObject::invalid())
  {
    return;
  }
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("RFDI ");
  int rfid=root["rfid"];
  Serial.println(rfid);
  Serial.print("Heart Beat    ");
  String heart=root["heartbeat"];
  Serial.println(heart);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");
 String info1 = "Tiger__1267__Chronic_Heart_Problem_" + heart ;
 Serial.println(info1);
 String info2 = "Hippopotamus_374654_Good_Health_Condition_" + heart;
 String data;
 if(rfid == 1){
    data = info1;
  }
   if(rfid == 2){
    data = info2;
  }
   if (Firebase.setString(firebase, "SmartZooControl/RFID_INFO",data )) {
      Serial.println("successful");
    }
  else {
    Serial.println(firebase.errorReason());
  }
}
