#include <SoftwareSerial.h>
#include <Servo.h>

//Servo myservo;
Servo openServo;
Servo front;
SoftwareSerial BT(11, 10); 
// creates a "virtual" serial port/UART
// connect BT module TX to 11
// connect BT module RX to 10
// connect BT Vcc to 5V, GND to GND
void setup()  
{
  //myservo.attach(6); // servo motor
  openServo.attach(5);
  front.attach(4);

  
  // set digital pin to control as an output
  pinMode(13, OUTPUT);
  // set the data rate for the SoftwareSerial port
  BT.begin(38400);
  // Send test message to other device
  BT.println("Hello from Arduino");
}
char a; // stores incoming character from other device
void loop() 
{
  if (BT.available())
  // if text arrived in from BT serial...
  {
    a=(BT.read());
    if (a=='1')
    {
      digitalWrite(13, HIGH);
      BT.println(" LED on");
      BT.println("servo on");
      //myservo.write(180);
      openServo.write(0);
      // delay for turn on 
      delay(1200);
      front.write(100);
    }
    if (a=='2')
    {
      digitalWrite(13, LOW);
      BT.println(" LED off");
      BT.println("servo off");
      //back to the original space
      //myservo.write(0);
      front.write(0);
      delay(1200);
      openServo.write(40);
    }
    if (a=='?')
    {
      BT.println("Send '1' to turn on the xbox");
      BT.println("Send '2' to turn off the xbox");
    }   
    // you can add more "if" statements with other characters to add more commands
  }
}

