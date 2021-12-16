#include <SoftwareSerial.h>
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;
long duration;
int distance;
int safetyDistance;
int info = 0;
int state = 0;


SoftwareSerial mySerial(5, 6);
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer, OUTPUT);
pinMode(ledPin, OUTPUT);
pinMode(A0,INPUT);
pinMode(11,OUTPUT);
 mySerial.begin(9600);
Serial.begin(9600); // Starts the serial communication
}
void loop() {
if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0){
   Serial.write(mySerial.read());}
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
safetyDistance = distance;
if (safetyDistance <= 5){
  digitalWrite(buzzer, HIGH);

}
else{
  digitalWrite(buzzer, LOW);
    

}
int val=analogRead(A0);
Serial.println(val);
Serial.print("Distance: ");
Serial.println(distance);
}
 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919849397968\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("http://maps.google.com/maps?q=");// The SMS text you want to send
  mySerial.println("17.4122998,78.2679573");
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }