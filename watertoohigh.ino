#include <FileIO.h>
#include <Process.h>

int pirPin = 7;

int minSecsBetweenEmails = 60; // 1 min
 
long lastSend = -minSecsBetweenEmails * 1000l;

void setup() {
Bridge.begin(); 
pinMode(pirPin, INPUT);
Serial.begin(9600);
FileSystem.begin();
}

void loop() {
  
  long now = millis();
  if (digitalRead(pirPin) == HIGH)
  {
    if (now > (lastSend + minSecsBetweenEmails * 1000l))
    {
Process p;
  p.runShellCommand("cat /root/test.txt | ssmtp Markxdeuil@gmail.com");
  lastSend = now;
    }
    else
    {
      Serial.println("Too soon");
    }
  }
  delay(500);
}

