/*
  Analog Input
 Demonstrates analog input by reading the sharp distance sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13.
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead().


 The circuit:
To use, connect black wire to ground, red wire to 5V and white wire to analog input. 
The analog voltage out will range from 3V when an object is only 4" (10 cm) away and 0.4V when the object is 32" (80 cm) away
 
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 * Note: because most Arduinos have a built-in LED attached
 to pin 13 on the board, the LED is optional.

 http://arduino.cc/en/Tutorial/AnalogInput

 */
#include <FileIO.h>
#include <Process.h>

int pirPin = 7;
int sensorPin = A0;    // select the input pin for the potentiometer
const int ledPin =  13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int minSecsBetweenEmails = 60; // 1 min
int ledState = LOW;

unsigned long previousMillis1 = 0;  
unsigned long previousMillis2 = 0; // will store last time LED was updated

// constants won't change :
const long interval = 1000; 

long lastSend = -minSecsBetweenEmails * 1000l;
#include <Console.h>

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Bridge.begin();
  Console.begin();
  while(!Console);
  FileSystem.begin();
}

void loop() {
  long now = millis();
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // print out the value you read:
  Console.println(sensorValue);
  if (sensorValue > 500  )
    {unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis2 >= interval) {
  previousMillis2 = currentMillis; }
    if (now > (lastSend + minSecsBetweenEmails * 1000l))
    {
Process p;
  p.runShellCommand("cat /root/watertoohigh.txt | ssmtp Markxdeuil@gmail.com");
  lastSend = now;
    }
    else
    {
  Serial.println("Too soon");
      }
  }
  {
    if (sensorValue < 500  )
       { unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis1 >= interval) {
    // save the last time you blinked the LED 
    previousMillis1 = currentMillis;   
        if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
  digitalWrite(ledPin, ledState);}}
 
}

}
