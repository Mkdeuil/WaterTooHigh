
#include <FileIO.h>
#include <Process.h>

const int movementPin = 7;
const int waterLevelPin = A0;
const int ledPinBlue =  11;
const int ledPinGreen =  10;
const int ledPinRed =  9;
int waterLevelValue = 0;
long minMillisSecBetweenEmails = 60000; // 60 sec between emails
int ledState = LOW;
long now = millis();

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
const long interval = 1000;

long lastSendWater = -minMillisSecBetweenEmails;
long lastSendMovement = -minMillisSecBetweenEmails;

void setup() {
  Serial.begin(9600);
  pinMode(ledPinBlue, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(movementPin, INPUT);
  Bridge.begin();
  FileSystem.begin();
}

void loop() {
  long now = millis();
  if (now - previousMillis1 >= interval) {
    waterLevelValue = analogRead(waterLevelPin);
    //Serial.print("waterLevelValue ");
    Serial.println(waterLevelValue-250); // Enlevé 250 pour deplacer 0-500 à -250 to +250 pour mieux afficher sur le plotter (graphique dans Tools > Serial Plotter).
    if (waterLevelValue > 500  ) {
      // Tes dans marde, ya de eau
      digitalWrite(ledPinBlue, HIGH);
      digitalWrite(ledPinGreen, HIGH);
      digitalWrite(ledPinRed, LOW);
      if (now > (lastSendWater + minMillisSecBetweenEmails)) {
        Process p;
        p.runShellCommand("cat /root/watertoohigh.txt | ssmtp Markxdeuil@gmail.com");
        lastSendWater = now;
      } else {
        Serial.println("Too soon");
      }
    } else {
      // Flash les lumieres blue et verte, water level OK
      digitalWrite(ledPinRed, HIGH);
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(ledPinBlue, ledState);
      digitalWrite(ledPinGreen, !ledState);
    }
    // pour le sensor de mouvement
    if (digitalRead(movementPin) == HIGH) {
      if (now > (lastSendMovement + minMillisSecBetweenEmails)) {
        Process p;
        p.runShellCommand("cat /root/test.txt | ssmtp Markxdeuil@gmail.com");
        lastSendMovement = now;
      } else {
        Serial.println("Too soon");
      }
    }
    previousMillis1 = now;
  }
}
