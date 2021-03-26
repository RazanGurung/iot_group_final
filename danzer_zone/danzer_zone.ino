#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
int trigger = 6;
 int echo = 7;
 int pingTravelTime;
 int buzzer = 9;
 
void setup() {
    lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Welcome To Zoo!");
  
  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print("LCD Tutorial");
 pinMode(6,OUTPUT);
 pinMode(7,INPUT);
 pinMode(9,OUTPUT);
 Serial.begin(9600);
}

void loop() {
    digitalWrite(6,LOW);
    delayMicroseconds(10);
    digitalWrite(6,HIGH);
    delayMicroseconds(10);
    digitalWrite(6,LOW);
    pingTravelTime = pulseIn(7,HIGH);
    delay(1000);
    Serial.print("ping travel distance");
    Serial.println(pingTravelTime);
    if(pingTravelTime <= 500){
        digitalWrite(9,HIGH);
        delay(1000);
        digitalWrite(9,LOW);
      }
}
