#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
#include <SPI.h>
#include <MFRC522.h>
#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library.

#define SS_PIN 10 //RX slave select
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

String card_ID=""; //card UID

//Add as many cards you want 
String Name1="15320982152";//first UID card
String Name2="185194126152";//second UID card
int card_no;
const int PulseWire = 0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
int Threshold = 550; // Determine which Signal to "count as a beat" and which to ignore.
PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
void setup() {
  s.begin(9600); // Initialize serial communications with the PC
  //Serial.begin(9600);
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
               
  Serial.println("Swipe your card");

  delay(200);
  pulseSensor.analogInput(PulseWire);
pulseSensor.setThreshold(Threshold);
 
// Double-check the "pulseSensor" object was created and "began" seeing a signal.
if (pulseSensor.begin()) {
Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.
 
}
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
     int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
// "myBPM" hold this BPM value now.
if (pulseSensor.sawStartOfBeat()) { // Constantly test to see if "a beat happened".
Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
Serial.print("BPM: "); // Print phrase "BPM: "
Serial.println(myBPM); // Print the value inside of myBPM.
}
delay(20); // considered best practice in a simple sketch.
if (isnan(card_no || isnan(myBPM))) {
    return;
  }
  StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
      root["rfid"] = card_no;
      root["heartbeat"] = myBPM;
     
    if(s.available()>0)
    {
     root.printTo(s);
    }
cont:
delay(1000);
card_ID="";

}
