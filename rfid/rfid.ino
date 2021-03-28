#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 //RX slave select
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

String card_ID=""; //card UID

//Add as many cards you want 
String Name1="15320982152";//first UID card
String Name2="185194126152";//second UID card
int card_no;
void setup() {
  s.begin(9600); // Initialize serial communications with the PC
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
               
  Serial.println("Swipe your card");

  delay(200);
   }

void loop() {
  //look for new card
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }

 for (byte i = 0; i < mfrc522.uid.size; i++) {
     card_ID += mfrc522.uid.uidByte[i];
 }

 Serial.println("The Card id is " + card_ID);

       if(card_ID==Name1){
       
       card_no=1;
      }
      else if(card_ID==Name2){
       card_no=2;
      }
      else{
         Serial.println("No data found for this card");
     }
     Serial.println(card_no);
if (isnan(card_no)) {
    return;
  }
  StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
      root["rfid"] = card_no;
      root["heartbeat"] = 12;
     
    if(s.available()>0)
    {
     root.printTo(s);
    }
cont:
delay(1000);
card_ID="";

}
