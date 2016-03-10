# WaterTooHigh
http://www.binarypower.com/2014/07/use-arduino-yun-to-send-emails-simple.html

## Get libraries
Copy latest RGB.h from https://github.com/xTianRoy/RGB.git to your Arduino libraries folder (on computer).

## Install apps needed (linux)
Open Terminal and enter:
```
ssh root@arduino.local
```
At password prompt, guess what you should be doing.

Once logged into ssh, enter the following commands on the prompt:
```
opkg update
opkg install ssmtp
mv /etc/ssmtp/ssmtp.conf /etc/ssmtp/ssmtp.bkp

vi /etc/ssmtp/ssmtp.conf
```

When VI opens, type "I" to get into insert mode.
Copy the content of ssmtp.conf file and paste it (CTRL-V) in the VI window.
Hit ESC, type ":wq"

Back at the terminal prompt, type:
```
chmod 640 /etc/ssmtp/ssmtp.conf
```

Arduino pins:
A0 = Signal pin from WaterLevelSensor
D9, D10, D11 = RGB LED
D7 = Signal PIR Movement detector
