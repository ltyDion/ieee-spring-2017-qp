
 /////////////////////////////
 int aut=0;
  int gat=0;
 #include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;
int k=1;// variable to store the servo position
 ///////////////////////////
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() {
//////////////////////////////////
myservo.attach(7);
///////////////////////////////////

  //pinMode(2,OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() {
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "D7 F7 AD D5") //change here the UID of the card/cards that you want to give access
  {
    aut=1; 
    //Add the main part here
    
    
    
    
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }

  /////////////////////////////////////////////////
    if (aut==0) {
    if (gat==1) {//if gate is open
      for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
         myservo.write(pos);              // tell servo to go to position in variable 'pos'
         delay(5); 
         gat=0;// waits 15ms for the servo to reach the position
      }
    }}
  else {
    if (gat==1){
       for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
         myservo.write(pos);              // tell servo to go to position in variable 'pos'
         delay(5);
         gat=0;
       }
    }
    else {//open gate
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(5);
        gat=1;
      }
    }
  }
  /////////////////////////////////////////////
} 
