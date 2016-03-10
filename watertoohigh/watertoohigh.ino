#include <Process.h>
#include <RGB.h>

RGB statusLED;
const int LED_RED_PIN =  9;
const int LED_GRN_PIN =  10;
const int LED_BLU_PIN =  11;

const int movementPin = 7;
const int waterLevelPin = A0;

int waterLevel = 0;
long minMillisSecBetweenEmails = 60000; // 60 sec between emails
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
  statusLED.setColor(0, 0, 0); // LIGHT OUT

  pinMode(movementPin, INPUT);
  Bridge.begin();
}

void loop() {
  long now = millis();
  if (now - previousMillis1 >= interval) {
    waterLevel = analogRead(waterLevelPin);
    Serial.println(waterLevel);
    postToDataSparkfun();

    if (waterLevel > 350) { // analogRead of 300 is ~6 inches

      ///--- Tes dans marde, ya de eau (Status RED) ---///
      statusLED.setColor(255, 0, 0);

      if (now > (lastSendWater + minMillisSecBetweenEmails)) {
        p.runShellCommand("echo -e \"Subject: Water Too High !!!\" | ssmtp Markxdeuil@gmail.com");

        while (p.available()) {
          char c = p.read();
          Serial.write(c);
        }
        lastSendWater = now;
      }

    } else {
      statusLED.setColor(0, 20, 0); // GREEN for GOOD - water is low
    }

    // pour le sensor de mouvement
    if (digitalRead(movementPin) == HIGH) {
      if (now > (lastSendMovement + minMillisSecBetweenEmails)) {
        Serial.println("Something moved!!");
        p.runShellCommand("echo -e \"Subject: Something moved !!!\" | ssmtp Markxdeuil@gmail.com");
        lastSendMovement = now;
      }
    }
    previousMillis1 = now;
  }
}

void postToDataSparkfun() {
  Process phant;
  String curlCmd;
  curlCmd = "curl --header \"Phant-Private-Key: yz7NgBpWdXS2vgwAaAba\" ";
  curlCmd += "--data \"waterlevel=" + String(waterLevel) + "\" ";
  //curlCmd += "--data \"temp=21\" ";
  //curlCmd += "--data \"humi=35\" ";
  curlCmd += "http://data.sparkfun.com/input/o8yq0G9JRKCK6Mg1O1GO";

  phant.runShellCommand(curlCmd); // Send command through Shell
  //Serial.print(F("Send the curl command: ")); Serial.println(curlCmd);
  //Serial.print(F("Response: "));
  //while (phant.available()) {
  //  char c = phant.read();
  //  Serial.write(c);
  //}
}
