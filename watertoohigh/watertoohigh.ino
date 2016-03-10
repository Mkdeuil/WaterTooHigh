#include <Process.h>
#include <RGB.h>

RGB statusLED;
const int LED_RED_PIN =  13;
const int LED_GRN_PIN =  10;
const int LED_BLU_PIN =  11;

const int movementPin = 7;
const int waterLevelPin = A0;

int waterLevelValue = 0;
long minMillisSecBetweenEmails = 60000; // 60 sec between emails
bool ledState = true;
long now = millis();

unsigned long previousMillis1 = 0;
const long interval = 1000;

long lastSendWater = -minMillisSecBetweenEmails;
long lastSendMovement = -minMillisSecBetweenEmails;

Process p;


void setup() {
  Serial.begin(9600);

  ///--- Initialize Status LED and define digital pins: R, G, B ---///
  statusLED.init(LED_RED_PIN, LED_GRN_PIN, LED_BLU_PIN);

  pinMode(movementPin, INPUT);
  Bridge.begin();
}

void loop() {
  long now = millis();
  if (now - previousMillis1 >= interval) {
    waterLevelValue = analogRead(waterLevelPin);
    
    //Serial.print("waterLevelValue ");
    Serial.println(waterLevelValue-250); // Enlevé 250 pour deplacer 0-500 à -250 to +250 pour mieux afficher sur le plotter (graphique dans Tools > Serial Plotter).
    
    if (waterLevelValue > 500  ) {

      ///--- Tes dans marde, ya de eau (Status RED) ---///
      statusLED.setColor(255, 0, 0);

      if (now > (lastSendWater + minMillisSecBetweenEmails)) { 
        p.runShellCommand("cat /root/watertoohigh.txt | ssmtp Markxdeuil@gmail.com");
        lastSendWater = now;
      }
      
    } else {
      
      // Flash les lumieres bleu et verte, water level OK
      if (ledState) {
        statusLED.setColor(0, 255, 0);
        ledState = false;
      } else {
        statusLED.setColor(0, 0, 255);
      }
    }
    // pour le sensor de mouvement
    if (digitalRead(movementPin) == HIGH) {
      if (now > (lastSendMovement + minMillisSecBetweenEmails)) {
        p.runShellCommand("cat /root/test.txt | ssmtp Markxdeuil@gmail.com");
        lastSendMovement = now;
      }
    }
    previousMillis1 = now;
  }
}
