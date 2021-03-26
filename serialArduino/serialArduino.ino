#include<Servo.h>
Servo myservo;
int data;
void setup() {
  Serial.begin(115200);
  myservo.attach(9);
  myservo.write(0);
}

void loop() {
  if(Serial.available()){
    data = Serial.read(); 
    Serial.println(data);
    
  }
  if(data == 1){
      myservo.write(180);
    }
    if(data == 0){
      myservo.write(data);
    }
}
